#!/usr/bin/env bash

# some tests are quicker to do here, tho idk how good of an idea this is
# should probably move them to test.c once the time comes lol

SHSL_EXEC="./shsl"
shsl_build_result=

build_clean_shsl() {
    echo "cleaning previous shsl..."
    make clean
    echo "building new shsl..."
    LOG_GC=no make shsl
    shsl_build_result=$?
}

build_clean_shsl
if [[ shsl_build_result ]]; then
    echo ""
    echo "successfully built shsl! now testing it"
else
    echo ""
    echo "shsl build exited with error! not proceeding further"
    exit "$shsl_build_result"
fi

assert_shsl_equal() {
    local expected_value="$1"
    local actual_code="$2"
    local errmsg="$3"

    local actual_value=$("$SHSL_EXEC" -e "$actual_code")

    if [[ "$expected_value" != "$actual_value" ]]; then
        echo "assertion failed!"
        [[ -n "$errmsg" ]] && echo "WITH ERROR: \"$errmsg\""
        echo "[$SHSL_EXEC -e $actual_code] was supposed to return [$expected_value]"
        echo "but instead it returned [$actual_value]"
        exit 1
    fi
}

echo "testing shsl..."

# symbols
assert_shsl_equal 'a' "'a" "symbol literal doesn't work"
assert_shsl_equal 'b' "'b" "symbol literal doesn't work"
assert_shsl_equal 't' "t"  "t should be self evaluating"

# operations
assert_shsl_equal  '4' "(+ 2 2)" "addition"
assert_shsl_equal  '4' "(* 2 2)" "multiplication"
assert_shsl_equal  '0' "(- 2 2)" "subtraction"
assert_shsl_equal '-1' "(- 2 3)" "subtraction order"

# literals (warning: depends on pretty printing used)
assert_shsl_equal '(a b c d)' "'(a b c d)" "quoted litst"
assert_shsl_equal '[a, b, c, d]' "'[a b c d]" "quoted vector literals"
assert_shsl_equal '{a:b, c:d}' "'{a b c d}" "quoted map literals"

# evaluating maps and vectors
assert_shsl_equal '[1, 2, 3, 4]' "[1 2 3 4]" "unquoted vectors"
assert_shsl_equal '{1:2, 3:4}' "{1 2 3 4}" "unquoted maps"
assert_shsl_equal '[1, 2, 3, 10]' "[1 2 3 (+ 5 5)]"\
		  "unquoted vectors with computed elements"
assert_shsl_equal '{1:2, 10:4}' "{1 2 (+ 6 4) 4}" "unquoted maps with computed keys"
assert_shsl_equal '{1:2, 3:10}' "{1 2 3 (+ 6 4)}" "unquoted maps with computed values"

assert_shsl_equal '[]' "[]" "empty vector"
assert_shsl_equal '[]' "'[]" "empty quoted vector"

assert_shsl_equal '{}' "{}" "empty map"
assert_shsl_equal '{}' "'{}" "empty quoted map"

# operations on collection literals

# do blocks
# (newlines in bash are fucking weird bruh)
assert_shsl_equal $'fuckyou\nnil' "(do (print 'fuck) (println 'you))" "do blocks"
# assert_shsl_equal $'youfuck\nnil' "(do (print 'you) (println 'fuck))" "do blocks"
# assert_shsl_equal $'fuck\nyou\nnil' "(do (println 'fuck) (println 'you))" "do blocks"
# assert_shsl_equal $'you\nfuck\nnil' "(do (println 'you) (println 'fuck))" "do blocks"

echo "if you see this and nothing blew up then all tests pass!"
