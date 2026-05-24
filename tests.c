#include<stdio.h>
#include<assert.h>

#define SHSL_IMPLEMENTATION
#include"shsl.h"

shsl_obj* eval_str(char* c, shsl_obj* env) {
    parser_pair p = parse_off(c);
    shsl_expression* expr = shsl_form_to_expr(p.obj);
    return shsl_eval(expr, env); 
}
void test_list_literals() {
    shsl_obj* l = eval_str("'(a b c)", nullptr);
    assert(l->type == SHSL_OBJ_CONS &&
	   "string literal did not return a string!");
    assert(shsl_list_length(l) == 3 && 
	   "vector literal of 3 elements contains wrong number of elements");
    
    assert(shsl_nth(l, 0)->type == SHSL_OBJ_SYMBOL && 
	   "list literal of symbols did not contain symbols");
    assert(shsl_nth(l, 1)->type == SHSL_OBJ_SYMBOL && 
	   "list literal of symbols did not contain symbols");
    assert(shsl_nth(l, 2)->type == SHSL_OBJ_SYMBOL && 
	   "list literal of symbols did not contain symbols");

    assert(shsl_nth(l, 3)->type == SHSL_OBJ_NIL && 
	   "for list literal of 3 symbols, (nth l 3) is not nil");

    assert(strcmp("a", shsl_nth(l, 0)->sym.name->str) == 0 && 
	   "incorrect value in list literal");
    assert(strcmp("b", shsl_nth(l, 1)->sym.name->str) == 0 && 
	   "incorrect value in list literal");
    assert(strcmp("c", shsl_nth(l, 2)->sym.name->str) == 0 && 
	   "incorrect value in list literal");

    shsl_free_obj(l);
}
void test_vector_literals() {
    shsl_obj* a = eval_str("'[a b c]", nullptr);
    assert(a->type == SHSL_OBJ_VECTOR &&
	   "vector literal did not return a vector");
    assert(a->vec.size == 3 && 
	   "vector literal of 3 elements contains wrong number of elements");

    assert(a->vec.buf[0]->type == SHSL_OBJ_SYMBOL && 
	   "vector literal of symbols did not contain symbols");
    assert(a->vec.buf[1]->type == SHSL_OBJ_SYMBOL && 
	   "vector literal of symbols did not contain symbols");
    assert(a->vec.buf[2]->type == SHSL_OBJ_SYMBOL && 
	   "vector literal of symbols did not contain symbols");

    assert(strcmp("a", a->vec.buf[0]->sym.name->str) == 0 && 
	   "incorrect first elelement of vector literal");
    assert(strcmp("b", a->vec.buf[1]->sym.name->str) == 0 && 
	   "incorrect second elelement of vector literal");
    assert(strcmp("c", a->vec.buf[2]->sym.name->str) == 0 && 
	   "incorrect second elelement of vector literal");

    shsl_free_obj(a);
}
void test_map_literals() {
    shsl_obj* b = eval_str("'{a b c d}", nullptr);
    assert(b->type == SHSL_OBJ_MAP &&
	   "map literal did not return a map");
    assert(b->map.size == 2 && 
	   "map literal of 2 kv pairs contains wrong number of elements");

    shsl_obj* k1 = shsl_obj_mksym("a");
    shsl_obj* k2 = shsl_obj_mksym("c");

    assert(shsl_map_get(b, k1)->type == SHSL_OBJ_SYMBOL &&
	   "(mapget '{a b c d} 'a) should return 'b");
    assert(strcmp("b", shsl_map_get(b, k1)->sym.name->str) == 0 &&
	   "(mapget '{a b c d} 'a) should return 'b");

    assert(shsl_map_get(b, k2)->type == SHSL_OBJ_SYMBOL &&
	   "(mapget '{a b c d} 'c) should return 'd");
    assert(strcmp("d", shsl_map_get(b, k2)->sym.name->str) == 0 &&
	   "(mapget '{a b c d} 'c) should return 'd");

    shsl_free_obj(b);

    shsl_free_obj(k1);
    shsl_free_obj(k2);
}
void test_collection_literals() {
    test_list_literals();
    test_vector_literals();
    test_map_literals();
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

void test_setting_global_var() {
    shsl_obj* env = shsl_make_initial_env();
    eval_str("(def a 10)", env);
    shsl_obj* a = eval_str("a", env);
    assert(a->type == SHSL_OBJ_INTEGER);
    assert(a->i == 10);
}

void test_defining_global_var() {
    shsl_obj* env = shsl_make_initial_env();
    eval_str("(set a 10)", env);
    shsl_obj* a = eval_str("a", env);
    assert(a->type == SHSL_OBJ_INTEGER);
    assert(a->i == 10);
}

int main() {
    puts("RUNNING TESTS...");
    test_some_shit();
    test_collection_literals();
    test_setting_global_var();
    test_defining_global_var();
    puts("IF YOU SEE THIS AND NOTHING BLEW UP ALL TESTS PASS!");
    return 0;
}
