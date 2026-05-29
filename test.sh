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

# operations on collection literals



# evaluating maps and vectors

echo "if you see this and nothing blew up then all tests pass!"
