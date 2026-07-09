#!/usr/bin/env bash

# some tests are quicker to do here, tho idk how good of an idea this is
# should probably move them to test.c once the time comes lol

SHSL_EXEC="./shsl"
shsl_build_result=

build_clean_shsl() {
    echo "cleaning previous shsl..."
    make clean
    echo "building new shsl..."
    LOG_MEM=no LOG_ERR=yes make shsl
    shsl_build_result=$?
}

if false; then
    build_clean_shsl
    if [[ shsl_build_result ]]; then
        echo ""
        echo "successfully built shsl! now testing it"
    else
        echo ""
        echo "shsl build exited with error! not proceeding further"
        exit "$shsl_build_result"
    fi
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

assert_shsl_equal 'nil' "" "an empty program should return nil"
assert_shsl_equal 'nil' "    " "an program made of only spaces should return nil"
assert_shsl_equal 'nil' $'\t\n \t' "an program made of only spaces should return nil"

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
assert_shsl_equal '[a b c d]' "'[a b c d]" "quoted vector literals"
assert_shsl_equal '{a b c d}' "'{a b c d}" "quoted map literals"

# evaluating maps and vectors
assert_shsl_equal '[1 2 3 4]' "[1 2 3 4]" "unquoted vectors"
assert_shsl_equal '{1 2 3 4}' "{1 2 3 4}" "unquoted maps"
assert_shsl_equal '[1 2 3 10]' "[1 2 3 (+ 5 5)]"\
		  "unquoted vectors with computed elements"
assert_shsl_equal '{1 2 10 4}' "{1 2 (+ 6 4) 4}" "unquoted maps with computed keys"
assert_shsl_equal '{1 2 3 10}' "{1 2 3 (+ 6 4)}" "unquoted maps with computed values"

assert_shsl_equal '[]' "[]" "empty vector"
assert_shsl_equal '[]' "'[]" "empty quoted vector"

assert_shsl_equal '{}' "{}" "empty map"
assert_shsl_equal '{}' "'{}" "empty quoted map"

# operations on collection literals

# def and set
assert_shsl_equal '10' "(def a 10)"
assert_shsl_equal '20' "(def a 10) (set a 20)"
assert_shsl_equal '30' "(def a 10) (set a 20) (set a 30)"

assert_shsl_equal '10' "(def a 10)"
assert_shsl_equal '20' "(def a 10) (def a 20)"
assert_shsl_equal '30' "(def a 10) (def a 20) (def a 30)"

assert_shsl_equal '10' "(set a 10)"
assert_shsl_equal '20' "(set a 10) (set a 20)"
assert_shsl_equal '30' "(set a 10) (set a 20) (set a 30)"

assert_shsl_equal '10' "(set a 10)"
assert_shsl_equal '20' "(set a 10) (def a 20)"
assert_shsl_equal '30' "(set a 10) (def a 20) (def a 30)"

# do blocks
# (newlines in bash are fucking weird bruh)
assert_shsl_equal $'fuckyou\nyou' "(do (print 'fuck) (println 'you))" "do blocks"
assert_shsl_equal $'youfuck\nfuck' "(do (print 'you) (println 'fuck))" "do blocks"
assert_shsl_equal $'fuck\nyou\nyou' "(do (println 'fuck) (println 'you))" "do blocks"
assert_shsl_equal $'you\nfuck\nfuck' "(do (println 'you) (println 'fuck))" "do blocks"

# let blocks
assert_shsl_equal '10' "(def a 10) (let [a [1 2 3]] a) a"
assert_shsl_equal '[1 2 3]' "(def a [1 2 3]) (let [a 10] a) a"
assert_shsl_equal '[1 2 3]' "(def a 10) (let [a [1 2 3]] a)"
assert_shsl_equal '10' "(def a [1 2 3]) (let [a 10] a)"

# if then else
assert_shsl_equal 'nil' "(if nil 'a)"
assert_shsl_equal 'b' "(if nil 'a 'b)"
assert_shsl_equal 'a' "(if t 'a 'b)"
assert_shsl_equal 'a' "(if t 'a)"
assert_shsl_equal 'a' "(if 'a 'a)"
assert_shsl_equal 'nil' "(if (err \"this is a test error don't worry\" \"dwai\") 'a)"

# builtin funs
assert_shsl_equal 'nil' "(> 10 20)"
assert_shsl_equal 't' "(< 10 20)"
assert_shsl_equal 'nil' "(>= 10 20)"
assert_shsl_equal 't' "(<= 10 20)"

assert_shsl_equal 't' "(nil? nil)"
assert_shsl_equal 't' "(nil? '())"
assert_shsl_equal 'nil' "(nil? t)"

assert_shsl_equal 't' "(sym? t)"
assert_shsl_equal 't' "(sym? 'hello)"
assert_shsl_equal 'nil' "(sym? 'nil)"
assert_shsl_equal 'nil' "(sym? 10)"

assert_shsl_equal '(a b)' "(cons 'a (cons 'b nil))"

# lambda fuckery
assert_shsl_equal '10000' "(((fn [a] (fn [b] (a (a b)))) (fn [a] (* a a))) 10)"

echo "if you see this and nothing blew up then all tests pass!"
