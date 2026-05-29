#include<stdio.h>
#include<assert.h>

#define SHSL_IMPLEMENTATION
#include"shsl.h"

// test utilities:
#ifdef SHSL_LOG_TESTS
#define SHSL_TEST(test) fprintf(stdout, "[SHSL TESTS]: running test "#test"\n"); test;
#else
#define SHSL_TEST(test) test;
#endif

bool sym_eq(const char* s, shsl_obj* sym_obj) {
    return sym_obj->type == SHSL_SYM
	&& strcmp(s, sym_obj->sym.name->str) == 0;
}

bool int_eq(long i, shsl_obj* int_obj) {
    return int_obj->type == SHSL_INT && int_obj->i == i;
}

// tests:
// test collection builders
// TODO: test empty builders?
void test_list_builder(void) {
    shsl_cb cb = shsl_cb_make(SHSL_CB_LIST);
    shsl_cb_add(&cb, shsl_mksym("hello"));
    shsl_cb_add(&cb, shsl_mksym("darkness"));
    shsl_cb_add(&cb, shsl_mksym("my"));
    shsl_cb_add(&cb, shsl_mksym("old"));
    shsl_cb_add(&cb, shsl_mksym("friend"));
    shsl_obj* lst = shsl_cb_get(cb);

    assert(lst->type == SHSL_CONS && "list builder did not return list");
    assert(shsl_list_length(lst) == 5 && "incorrect length of built list!");

    assert(sym_eq("hello", shsl_nth(lst, 0)) && "string symbol has incorrect value!");
    assert(sym_eq("darkness", shsl_nth(lst, 1)) && "string symbol has incorrect value!");
    assert(sym_eq("my", shsl_nth(lst, 2)) && "string symbol has incorrect value!");
    assert(sym_eq("old", shsl_nth(lst, 3)) && "string symbol has incorrect value!");
    assert(sym_eq("friend", shsl_nth(lst, 4)) && "string symbol has incorrect value!");

    shsl_obj_free(lst);
}
void test_vec_builder(void) {
    shsl_cb cb = shsl_cb_make(SHSL_CB_VEC);
    shsl_cb_add(&cb, shsl_mkint(1));
    shsl_cb_add(&cb, shsl_mkint(2));
    shsl_cb_add(&cb, shsl_mkint(3));

    shsl_obj* vec = shsl_cb_get(cb);
    assert(vec->type == SHSL_VEC && "vector builder did not yield vector!");
    assert(vec->vec.size == 3 && "vector builder gave vector of wrong length!");

    assert(int_eq(1, vec->vec.buf[0]) && "vec builder gave vec with wrong values!");
    assert(int_eq(2, vec->vec.buf[1]) && "vec builder gave vec with wrong values!");
    assert(int_eq(3, vec->vec.buf[2]) && "vec builder gave vec with wrong values!");

    shsl_obj_free(vec);
}
void test_map_builder(void) {
    shsl_cb cb0 = shsl_cb_make(SHSL_CB_MAP);
    assert(shsl_cb_get(cb0)->type == SHSL_MAP);

    shsl_cb cb1 = shsl_cb_make(SHSL_CB_MAP);
    shsl_cb_add(&cb1, shsl_mkint(1));
    shsl_cb_add(&cb1, shsl_mkint(2));
    shsl_cb_add(&cb1, shsl_mkint(3));
    shsl_obj* err = shsl_cb_get(cb1);
    assert(err->type == SHSL_ERR
	   && "erroneous map construction did not return error!");
    shsl_obj_free(err);
    // TODO: should map construction error also hold the last key?
    // other than completeness of error recording, that kinda leaks otherwise
    // nothing holds a ref to it after the builder is released, and we don't have
    // builder teardown functions because they're not needed for any case but this
    // FIXME: better way to handle this
    shsl_obj_free(cb1.map_builder.curr_key);

    shsl_cb cb2 = shsl_cb_make(SHSL_CB_MAP);
    shsl_cb_add(&cb2, shsl_mksym("one"));
    shsl_cb_add(&cb2, shsl_mkint(1));
    shsl_cb_add(&cb2, shsl_mksym("two"));
    shsl_cb_add(&cb2, shsl_mkint(2));

    shsl_obj* map = shsl_cb_get(cb2);

    assert(map->map.size == 2 && "map builder gave map of wrong length!");

    assert(sym_eq("one", map->map.buf[0].k));
    assert(int_eq(1, map->map.buf[0].v));
    assert(sym_eq("two", map->map.buf[1].k));
    assert(int_eq(2, map->map.buf[1].v));
}
// calls all the above
void test_collection_builders(void) {
    SHSL_TEST(test_list_builder()); 
    SHSL_TEST(test_vec_builder()); 
    SHSL_TEST(test_map_builder()); 
}

// test collection literals
void test_list_literals(void) {
    shsl_obj* lst = shsl_eval_str("'(a b c)", NULL);
    assert(lst->type == SHSL_CONS);
}
void test_vec_literals(void) {
    shsl_obj* vec = shsl_eval_str("'[a b c]", NULL);
    assert(vec->type == SHSL_VEC);
}
void test_map_literals(void) {
    shsl_obj* map = shsl_eval_str("'{a b c c}", NULL);
    assert(map->type == SHSL_MAP);
}
void test_collection_literals(void) {
    SHSL_TEST(test_list_literals());
    SHSL_TEST(test_vec_literals());
    SHSL_TEST(test_map_literals());
}

// test error generation
void test_error(void) {
    shsl_obj* s = shsl_mkerr(&SHSL_GLOBAL_NIL, "%s",
			     "test error generation");
    assert(strcmp(s->err.msg->str, "test error generation") == 0);
}

void test_some_shit(void) {
    shsl_obj* a = shsl_eval_str("'a", NULL);
    assert(a->type == SHSL_SYM
	   && "symbol literal did not return a symbol");

    shsl_obj* b = shsl_eval_str("(if 'a 'b 'c)", NULL);
    assert(b->type == SHSL_SYM
	   && "conditional returning symbol literal didn't return symbol");

    shsl_obj* env = shsl_make_initial_env();
    shsl_obj* c = shsl_eval_str("(+ 2 2)", env);
    assert(c->type == SHSL_INT && "2+2 didn't return an integer");
    assert(c->i == 4 && "2+2 should equal 4");
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    puts("RUNNING TESTS...");
    SHSL_TEST(test_some_shit());
    SHSL_TEST(test_collection_builders());
    SHSL_TEST(test_collection_literals());
    SHSL_TEST(test_error());
    puts("IF YOU SEE THIS AND NOTHING BLEW UP ALL TESTS PASS!");
    // TODO: make logging flag runtime thing so I can disable it for
    // error generation tests
    puts("(error messages above are likely from test error generation, ignore them)");
    return 0;
}
