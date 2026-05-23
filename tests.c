#include<stdio.h>
#include<assert.h>
#include"shsl.h"

shsl_obj* eval_str(char* c) {
    shsl_obj* env = nullptr; // dummy env, we still don't eval shit
    parser_pair p = parse_off(c);
    shsl_expression* expr = shsl_form_to_expr(p.obj);
    return shsl_eval(expr, env); 
}

void test_some_shit() {
    shsl_obj* a = eval_str("'a");
    assert(a->type == SHSL_OBJ_SYMBOL && "symbol literal did not return a symbol");

    shsl_obj* b = eval_str("(if 'a 'b 'c)");
    assert(b->type == SHSL_OBJ_SYMBOL && "conditional returning symbol literal didn't return symbol");
}

int main() {
    puts("RUNNING TESTS...");
    test_some_shit();
    puts("IF YOU SEE THIS AND NOTHING BLEW UP ALL TESTS PASS!");
    return 0;
}
