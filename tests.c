#include<stdio.h>
#include<assert.h>

#define SHSL_IMPLEMENTATION
#include"shsl.h"

shsl_obj* eval_str(char* c, shsl_obj* env) {
    parser_pair p = parse_off(c);
    shsl_expression* expr = shsl_form_to_expr(p.obj);
    return shsl_eval(expr, env); 
}

void test_some_shit() {
    shsl_obj* a = eval_str("'a", nullptr);
    assert(a->type == SHSL_OBJ_SYMBOL &&
	   "symbol literal did not return a symbol");

    shsl_obj* b = eval_str("(if 'a 'b 'c)", nullptr);
    assert(b->type == SHSL_OBJ_SYMBOL &&
	   "conditional returning symbol literal didn't return symbol");

    shsl_obj* env = shsl_make_initial_env();
    shsl_obj* c = eval_str("(+ 2 2)", env);
    assert(c->type == SHSL_OBJ_INTEGER && "2+2 didn't return an integer");
    assert(c->i == 4 && "2+2 should equal 4");
}

int main() {
    puts("RUNNING TESTS...");
    test_some_shit();
    puts("IF YOU SEE THIS AND NOTHING BLEW UP ALL TESTS PASS!");
    return 0;
}
