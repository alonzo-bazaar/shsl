//// HEADER
//// ----------------------------------------------------------------------------
// SHSL: Single Header Scripting (Library|Language|Layer|Lisp)
// scripting language localized entirely within a C header file
// shsl file is distributed under the GNU LGPL v2.1 (see LICENSE file for details)
// author: Alonzo Bazaar <alonzo.lo.stronzo@protonmail.com>

#ifndef SHSL_H
#define SHSL_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdarg.h>

#include<ctype.h>
#include<string.h>
#include<assert.h>

// dumb utilities
#define defstruct(s) struct s; typedef struct s s

//// DATA DECLARATIONS
//// ----------------------------------------------------------------------------

/// DATA TYPES DECLARATIONS
// type tag for shsl objects
typedef enum SHSL_OBJ_TYPE {
    // atoms
    // nil first so an object initialized as {0} is nil
    SHSL_NIL = 0, SHSL_SYM, 
    SHSL_INT, SHSL_REAL, SHSL_STRING,

    // collections
    SHSL_CONS, SHSL_VEC, SHSL_MAP,

    // functions and macros
    SHSL_BUILTIN_FUN, SHSL_USER_FUN, 
    SHSL_BUILTIN_MACRO, SHSL_USER_MACRO, 

    // error
    SHSL_ERR,
} SHSL_OBJ_TYPE;

// tagged union of all possible shsl objects
defstruct(shsl_obj);
// possible shsl objects
// (outside of primitive types for which we just use the C ones)
defstruct(shsl_sym);
defstruct(shsl_err);
defstruct(shsl_cons);
defstruct(shsl_vec);
// key value pair (for maps)
// kv pairs are not shsl objects, they're defined separately just for ease 
// other than that they're just there to aid in defining maps
defstruct(shsl_kv);
// map as vector of kv pairs
defstruct(shsl_map);
defstruct(shsl_builtin_fun);
defstruct(shsl_user_fun);
// we don't have macro types as macros are just gonna be functions with different
// type tags that we run at a different moment (compile/expand time instead of runtime)

/// DATA CONSTRUCTION DECLARATIONS
// we handle everything through pointers because havnig everything
// on the heap makes it easier to automatically manage
shsl_obj* shsl_mkint(long l);
shsl_obj* shsl_mkreal(double d);
shsl_obj* shsl_mkstr(const char* str);
shsl_obj* shsl_mksym(const char* name);
shsl_obj* shsl_mkerr(shsl_obj* data, const char* msg, ...);
shsl_obj* shsl_vmkerr(shsl_obj* data, const char* msg, va_list args);
    shsl_obj* shsl_mkcons(shsl_obj* car, shsl_obj* cdr);
shsl_obj* shsl_mkmap(size_t initial_capacity);
shsl_obj* shsl_mkvec(size_t initial_capacity);
shsl_obj* shsl_mkbuiltin_fun(shsl_obj* env,
			     shsl_obj*(*apply)(shsl_obj* args,
					       shsl_obj* env));
shsl_obj* shsl_mkbuiltin_macro(shsl_obj* env,
			       shsl_obj*(*apply)(shsl_obj* args,
						 shsl_obj* env));
// this one bit is kinda ugly
struct shsl_expr;
shsl_obj* shsl_mkuser_fun(shsl_obj* env, shsl_obj* lambda_list,
			  struct shsl_expr** body, size_t body_len);
shsl_obj* shsl_mkuser_macro(shsl_obj* env, shsl_obj* lambda_list,
			    struct shsl_expr** body, size_t body_len);

/// DATA OPERATIONS DECLARATIONS
/// GENERIC OPERATIONS DECLARATIONS (copy, delete, refcount shit)
// marks addition of reference to object
// also returns the modified object for convenience
shsl_obj* shsl_add_ref(shsl_obj* obj);
// marks removal of reference to object
// may also delete the object if reference count reaches 0 
void shsl_del_ref(shsl_obj* obj);
// deletes the object and removes reference to any eventual sub-objects
// (cons car and cdr, vector elements, map keys and values, et al.)
void shsl_obj_free(shsl_obj* obj);
// creates fresh (newly allocated) deep copy of obj
// does not copy refcount tho
// fresh objects are initialized with an initial refcount of 0
shsl_obj* shsl_copy(shsl_obj* obj);
bool shsl_eq(shsl_obj* lhs, shsl_obj* rhs);
// sets *dst to src whilst handling refcounting
// (*dst is overwritten so loses a ref, src is what's written, so gains one)
void shsl_set(shsl_obj** dst, shsl_obj* src);

/// CONS MANIPULATIONS DECLARATIONS
void shsl_set_car(shsl_obj* cons_obj, shsl_obj* car);
void shsl_set_cdr(shsl_obj* cons_obj, shsl_obj* cdr);

/// VECTOR MANIPULATIONS DECLARATIONS
void shsl_vec_expand(shsl_obj* vec_obj, size_t new_size);
void shsl_vec_push(shsl_obj* vec_obj, shsl_obj* obj);
shsl_obj* shsl_vec_get(shsl_obj* vec_obj, size_t i);
void shsl_vec_set(shsl_obj* vec_obj, size_t i, shsl_obj* new_val);
size_t shsl_vec_length(shsl_obj* vec_obj);
// bit of shit, but this avoids polluting the body with extra symbols
// although it does introduce a bit of overhead, sorry :|
#define shsl_vec_foreach(i, elt, vec)			\
    for(size_t i = 0; i<shsl_vec_length(vec); ++i)	\
	for(shsl_obj* elt = shsl_vec_get(vec, i);	\
	    elt; elt = NULL)				\

/// MAP MANIPULATIONS DECLARATIONS
void shsl_map_expand(shsl_obj* map_obj, size_t new_size);
// it's ssize_t instead of size_t so we can use -1 to say "hey, didn't find shit"
ssize_t shsl_map_index(shsl_obj* map_obj, shsl_obj* key);

shsl_obj* shsl_map_get(shsl_obj* map_obj, shsl_obj* key);
void shsl_map_set(shsl_obj* map_obj,
		  shsl_obj* key, shsl_obj* new_val);

/// COLLECTION BUILDERS DECLARATIONS
typedef enum SHLS_CB_TYPE {SHSL_CB_LIST, SHSL_CB_VEC, SHSL_CB_MAP} SHSL_CB_TYPE;
defstruct(shsl_cb);
shsl_cb shsl_cb_make(SHSL_CB_TYPE type);
void shsl_cb_add(shsl_cb* cb, shsl_obj* obj);
shsl_obj* shsl_cb_get(shsl_cb);

/// DATA PREDICATES DECLARATIONS
bool shsl_is_nil(const shsl_obj* obj);
bool shsl_is_sym(const shsl_obj* obj);
bool shsl_is_int(const shsl_obj* obj);
bool shsl_is_real(const shsl_obj* obj);
bool shsl_is_num(const shsl_obj* obj);
bool shsl_is_err(const shsl_obj* obj);
bool shsl_is_truthy(const shsl_obj* obj);

bool shsl_is_cons(const shsl_obj* obj);
bool shsl_is_list(const shsl_obj* obj);
bool shsl_is_proper_list(const shsl_obj* list_obj);
bool shsl_is_vec(const shsl_obj* obj);
bool shsl_is_map(const shsl_obj* obj);

/// LIST OPERATIONS DECLARATIONS
shsl_obj* shsl_car(shsl_obj* obj);
shsl_obj* shsl_cdr(shsl_obj* obj);
shsl_obj* shsl_nthcdr(shsl_obj* obj, size_t n);
shsl_obj* shsl_nth(shsl_obj* list_obj, size_t n);
// ssize_t so we can use -1 as "bro what the fuck is this object"
ssize_t shsl_list_len(shsl_obj* list_obj);


//// LEXER DECLARATIONS
//// ----------------------------------------------------------------------------

// possible types a token may assume
typedef enum SHSL_TOKEN_TYPE {
    // literals
    SHSL_TOK_NIL = 0, SHSL_TOK_SYMBOL,
    SHSL_TOK_INTEGER, SHSL_TOK_REAL, SHSL_TOK_STRING,

    // (quasi)quoting
    SHSL_TOK_QUOTE, SHSL_TOK_QUASIQUOTE, SHSL_TOK_COMMA,

    // parentheses
    SHSL_TOK_OPEN_PAREN, SHSL_TOK_CLOSE_PAREN,
    SHSL_TOK_OPEN_SQUARE, SHSL_TOK_CLOSE_SQUARE,
    SHSL_TOK_OPEN_CURLY, SHSL_TOK_CLOSE_CURLY,

    // we then have special token types to express
    // eof
    SHSL_TOK_EOF,
    // error
    SHSL_TOK_ERROR,
} SHSL_TOKEN_TYPE;
// TODO: not a tagged union yet but I'm working on it
defstruct(shsl_token);
// pair of read token/remaining string after token
defstruct(lexer_pair);
// read a token off of string and return the pair of that token plus
// the string after the token
lexer_pair token_off(char* str);

// return a token of a given type with no extra information
shsl_token empty_token(enum SHSL_TOKEN_TYPE token_type);
// return an error message from a token_off call
lexer_pair error_lexer_pair(const char* errmsg);

// is this character special for the lexer?
bool is_special_char(char c);
// can this a character that be be part of a symbol (or number)
bool is_symbol_char(char c);
// parse a non special token (symbol or number) starting at c
shsl_token parse_non_special_token(char*c, size_t len);
// try parsing from c to c+len as an integer and writing that into *into
// returns true if parsing was succesful, false otherwise
bool try_parse_integer(char* c, size_t len, long* into);
// copy characters from c to c+len into a fresh null terminated string
char* slice_to_fresh_str(const char* c, size_t len);


//// PARSER DECLARATIONS
//// ----------------------------------------------------------------------------

// pair of parsed object/remaining string after object
// same logic as lexer_pair
defstruct(parser_pair);
// parse object starting at str and return pair of that object
// plus the string after that object
parser_pair parse_off(char* str);
// parse from str until you meet a token of stop type
// collect the results into a list and return them
// erros out if it meets a token of type error_on[0]...error_on[error_on_len] before
// a token of type stop
// 
// said less abstractly
// if you meet a '(' you parse until ')' and error out if you meet a ']' or '}'
// at the same depth before you meet a ')' at the same depth
parser_pair parse_until(char* str,
			shsl_cb cb,
			enum SHSL_TOKEN_TYPE stop,
			enum SHSL_TOKEN_TYPE* error_on, size_t error_on_len);


//// EVALUATOR DECLARATIONS
//// ----------------------------------------------------------------------------

/// EXPRESSION TYPE DECLARATIONS
typedef enum SHSL_EXPR_TYPE {
    SHSL_EXPR_LITERAL,
    SHSL_EXPR_VEC,
    SHSL_EXPR_MAP,
    SHSL_EXPR_LOOKUP,
	
    SHSL_EXPR_IF,
    SHSL_EXPR_LET,
    SHSL_EXPR_WHILE,
    SHSL_EXPR_DO,
    SHSL_EXPR_DO_POKING,

    SHSL_EXPR_DEF,
    SHSL_EXPR_SET,

    SHSL_EXPR_FN,
    SHSL_EXPR_MACRO,

    SHSL_EXPR_FUNCALL,
} SHSL_EXPR_TYPE;
defstruct(shsl_vec_expr);
defstruct(shsl_map_expr);
defstruct(shsl_if_expr);
defstruct(shsl_do_expr);
defstruct(shsl_do_poking_expr);
defstruct(shsl_def_expr);
defstruct(set_expr);
defstruct(shsl_funcall_expr);
// tagged union of all possible expression types
// (either the ones above or like, literals and shit)
defstruct(shsl_expr);

/// FORM TRANSLATION FUNCTIONS DECLARATIONS
shsl_expr* shsl_form_to_expr(shsl_obj* form);
bool shsl_expr_is_error(shsl_expr* expr);
// unrelated to form translation but still related to forms
void shsl_expr_free(shsl_expr* expr);

/// EVALUTATION FUNCTIONS DECLARATIONS
// we don't have a separate shsl_environment type as the enviroment will be
// represented using a cons list of shsl maps
// this should make for easier debuggability, even from within shsl
// and may allow for some funky pythonish introspection
shsl_obj* shsl_eval(shsl_expr* form, shsl_obj* env);
shsl_obj* shsl_eval_many_into_vec(shsl_expr** args, size_t args_len,
				  shsl_obj* env);

/// BUILTIN FUNCTIONS DECLARATIONS
// that is, definition of the functions that will be visible as builtins
// for the shsl code
/// SHSL ARITHMETIC FUNCTIONS DECLARATIONS
shsl_obj* shsl_builtin_all(shsl_obj* args, shsl_obj* env);
shsl_obj* shsl_builtin_sub(shsl_obj* args, shsl_obj* env);
shsl_obj* shsl_builtin_mul(shsl_obj* args, shsl_obj* env);
shsl_obj* shsl_builtin_div(shsl_obj* args, shsl_obj* env);

/// ENVIRONMENT FUNCTIONS DECLARATIONS
// both of these may well be global constants if c had map (and shsl list) literals
shsl_obj* shsl_make_initial_env(void);
// lookup in an environment that's just a list of maps(lol)
shsl_obj* shsl_env_lookup(shsl_obj* env, shsl_obj* key);

//// PRINT DEBUGGING DECLARATIONS
//// ----------------------------------------------------------------------------
void shsl_dbg_fputtok(const shsl_token* tok, FILE* restrict stream);
void shsl_fputobj(const shsl_obj* obj, FILE* restrict stream);

//// USER FACING FUNCTIONS DECLARATIONS
//// ----------------------------------------------------------------------------
shsl_obj* shsl_eval_str(char* c, shsl_obj* env);

#ifdef SHSL_IMPLEMENTATION
//// DATA DEFINITIONS
//// ----------------------------------------------------------------------------

/// DATA TYPES DEFINITIONS
typedef struct shsl_sym {
    shsl_obj* name; // must be string
} shsl_sym ;
typedef struct shsl_err {
    shsl_obj* data; // can be any
    shsl_obj* msg;  // must be string
} shsl_err;
typedef struct shsl_cons {
    shsl_obj* car;
    shsl_obj* cdr;
} shsl_cons ;
typedef struct shsl_vec {
    shsl_obj** buf;
    size_t size;
    size_t capacity;
} shsl_vec;
// map is currently an alist (because fuck me ig)
typedef struct shsl_kv {
    shsl_obj* k;
    shsl_obj* v;
} shsl_kv;
typedef struct shsl_map {
    shsl_kv* buf;
    size_t size;
    size_t capacity;
} shsl_map;
typedef struct shsl_builtin_fun {
    // env must be cons list of frames (maps)
    // args must be a vector
    shsl_obj* env;
    shsl_obj*(*apply)(shsl_obj* args, shsl_obj* env);
} shsl_builtin_fun;
typedef struct shsl_user_fun {
    // env must be cons list of maps
    // lambda_list be vector
    shsl_obj* env;
    shsl_obj* lambda_list;
    shsl_expr** body;
    size_t body_len;
} shsl_user_fun;

typedef struct shsl_obj {
    // header
    int ref_count;
    SHSL_OBJ_TYPE type;

    // data
    union {
	long i;
	double r;
	char* str;

	shsl_sym sym;
	shsl_cons cons;

	shsl_vec vec;
	shsl_map map;

	shsl_builtin_fun builtin_fun;
	shsl_user_fun user_fun;
	shsl_builtin_fun builtin_macro;
	shsl_user_fun user_macro;

	shsl_err err;
    };
} shsl_obj;	

shsl_obj SHSL_GLOBAL_NIL = {0};

/// DATA CONSTRUCTION DEFINITIONS
// the shsl_mk* functions all return references to fresh objects
// although those objects may contain references to pre-existing objects
// if they're cons cells, vectors, or maps, for instance
// 
// all raw C data passed to an shsl_mk* constructor
// (numbers, chars, strings (both for shsl strings and symbol names))
// is copied into the returned object,
// so changes to the object won't change the original data and viceversa
// 
// this, although inefficient, ensures that all the data contained in shsl
// objects can be safely managed by our autoamtic memory management
// and prevents weird data races we may encounter at the language boundary
#define return_mallocd_obj(...) do {				\
	shsl_obj* obj = (shsl_obj*)malloc(sizeof(shsl_obj));	\
	*obj = (shsl_obj){__VA_ARGS__};				\
	return obj;						\
    } while(0)

shsl_obj* shsl_mkint(long l) {
    return_mallocd_obj(.ref_count = 0, .type = SHSL_INT, .i = l);
}
shsl_obj* shsl_mkreal(double d) {
    return_mallocd_obj(.ref_count = 0, .type = SHSL_REAL, .r = d);
}
shsl_obj* shsl_mkstr(const char* str) {
    char* c = calloc(strlen(str), sizeof(char));
    strcpy(c, str);
    return_mallocd_obj(.ref_count = 0, .type = SHSL_STRING, .str = c);
}
shsl_obj* shsl_mksym(const char* name) {
    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_SYM,
		       .sym = (shsl_sym){
			   .name = shsl_add_ref(shsl_mkstr(name)),
		       });
}

#define SHSL_ERR_MAX_LENGTH 1024
shsl_obj* shsl_vmkerr(shsl_obj* data, const char* msg, va_list args) {
    static char buf[SHSL_ERR_MAX_LENGTH] = {0};
    vsprintf(buf, msg, args);

#ifdef SHSL_LOG_ERROR
    fprintf(stderr, "[ERROR] %s\n", buf);
    fprintf(stderr, "[ERROR] with data:");
    shsl_fputobj(data, stderr);
    fputc('\n', stderr);
#endif

    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_ERR,
		       .err = (shsl_err) {
			   .msg = shsl_add_ref(shsl_mkstr(buf)),
			   .data = shsl_add_ref(data),
		       });
}
shsl_obj* shsl_mkerr(shsl_obj* data, const char* msg, ...) {
    va_list args;
    va_start(args, msg);
    shsl_obj* err = shsl_vmkerr(data, msg, args);
    va_end(args);
    return err;
}

shsl_obj* shsl_mkcons(shsl_obj* car, shsl_obj* cdr) {
    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_CONS,
		       .cons = (shsl_cons) { .car = shsl_add_ref(car),
					     .cdr = shsl_add_ref(cdr), }
		      );
}
shsl_obj* shsl_mkvec(size_t initial_capacity) {
    assert(initial_capacity > 0);

    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_VEC,
		       .vec = (shsl_vec) {
			   .buf = calloc(initial_capacity, sizeof(shsl_obj*)),
			   .size = 0,
			   .capacity = initial_capacity,
		       },
		      );
}
shsl_obj* shsl_mkmap(size_t initial_capacity) {
    assert(initial_capacity > 0);
    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_MAP,
		       .map = (shsl_map){
			   .buf = calloc(initial_capacity, sizeof(shsl_kv)),
			   .size = 0,
			   .capacity = initial_capacity,
		       }
		      );
}
shsl_obj* shsl_mkbuiltin_fun(shsl_obj* env,
			     shsl_obj*(*apply)(shsl_obj* args,
					       shsl_obj* env)) {
    assert((!env)
	   || shsl_is_nil(env)
	   || shsl_is_cons(env) && shsl_is_map(env->cons.car)
	   && "if function env is not null it must be a list of maps!");

    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_BUILTIN_FUN,
		       .builtin_fun = (shsl_builtin_fun) {
			   .env = env,
			   .apply = apply,
		       }
		      );
}
shsl_obj* shsl_mkbuiltin_macro(shsl_obj* env,
			       shsl_obj*(*expand)(shsl_obj* args,
						  shsl_obj* env)) {
    assert((!env)
	   || shsl_is_nil(env)
	   || shsl_is_cons(env) && shsl_is_map(env->cons.car)
	   && "if macro env is not null it must be a list of maps!");

    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_BUILTIN_MACRO,
		       .builtin_macro = (shsl_builtin_fun) {
			   .env = env,
			   .apply = expand,
		       }
		      );
}
shsl_obj* shsl_mkuser_fun(shsl_obj* env, shsl_obj* lambda_list,
			  struct shsl_expr** body, size_t body_len) {
    assert((!env)
	   || shsl_is_nil(env)
	   || shsl_is_cons(env) && shsl_is_map(env->cons.car)
	   && "if function env is not null it must be a list of maps!");
    assert(shsl_is_vec(lambda_list) && "function lambda list must be vector!");
    assert(body && "function body cannot be null pointer!");
    assert(body_len > 0 && "function body length cannot be null!");

    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_USER_FUN,
		       .user_fun = (shsl_user_fun) {
			   .env = env,
			   .lambda_list = lambda_list,
			   .body = body,
			   .body_len = body_len,
		       }
		      );
}
shsl_obj* shsl_mkuser_macro(shsl_obj* env, shsl_obj* lambda_list,
			    struct shsl_expr** body, size_t body_len) {
    assert((!env)
	   || shsl_is_nil(env)
	   || shsl_is_cons(env) && shsl_is_map(env->cons.car)
	   && "if function env is not null it must be a list of maps!");
    assert(shsl_is_vec(lambda_list) && "macro lambda list must be list!");
    assert(body && "macro body cannot be null pointer!");
    assert(body_len > 0 && "macro body length cannot be null!");

    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_USER_MACRO,
		       .user_macro = (shsl_user_fun) {
			   .env = env,
			   .lambda_list = lambda_list,
			   .body = body,
			   .body_len = body_len,
		       }
		      );
}

/// DATA OPERATIONS DEFINITIONS
/// GENERIC OPERATIONS DEFINITIONS
shsl_obj* shsl_add_ref(shsl_obj* obj) {
#ifdef SHSL_LOG_ADD_REF
    fprintf(stdout, "[SHSL GC]: adding ref to object %p\n", (void*)obj);
    fprintf(stdout, "[SHSL GC]: "); shsl_fputobj(obj, stdout);
    fprintf(stdout, "[SHSL GC]: was at refcount %d\n", obj->ref_count);
    fputc('\n', stdout);
#endif    

    if(obj->type != SHSL_NIL)
	obj->ref_count++;
    return obj;
}
void shsl_del_ref(shsl_obj* obj) {
#ifdef SHSL_LOG_ADD_REF
    fprintf(stdout, "[SHSL GC]: adding ref to object %p\n", (void*)obj);
    fprintf(stdout, "[SHSL GC]: "); shsl_fputobj(obj, stdout);
    fprintf(stdout, "[SHSL GC]: was at refcount %d\n", obj->ref_count);
#endif    

    if(obj->type != SHSL_NIL) {
	obj->ref_count--;
	if(obj->ref_count == 0)
	    shsl_obj_free(obj);
	if(obj->ref_count < 0)
	    fprintf(stderr, "now you fucked up!\n");
    }
}
void shsl_obj_free(shsl_obj *obj) {
#ifdef SHSL_LOG_GC
    fprintf(stdout, "[SHSL GC]: freeing object %p\n", (void*)obj);
    shsl_fputobj(obj, stdout);
    fputc('\n', stdout);
#endif    
    switch(obj->type) {
    case SHSL_NIL:
	fprintf(stderr, "cannot free NIL! You fucked something up!\n");
	break;

    case SHSL_STRING:
	free(obj->str);
	free(obj);
	break;

    case SHSL_SYM:
	shsl_del_ref(obj->sym.name);
	free(obj);
	break;

    case SHSL_ERR:
	shsl_del_ref(obj->err.msg);
	shsl_del_ref(obj->err.data);
	free(obj);
	break;
    case SHSL_CONS:
	shsl_del_ref(obj->cons.car);
	shsl_del_ref(obj->cons.cdr);
	free(obj);
	break;
    case SHSL_VEC:
	for(size_t i = 0; i<obj->vec.size; ++i)
	    shsl_del_ref(obj->vec.buf[i]);
	free(obj->vec.buf);
	free(obj);
	break;
    case SHSL_MAP:
	for(size_t i = 0; i<obj->map.size; ++i) {
	    shsl_del_ref(obj->map.buf[i].k);
	    shsl_del_ref(obj->map.buf[i].v);
	}
	free(obj->map.buf);
	free(obj);
	break;

    case SHSL_BUILTIN_FUN:
	shsl_del_ref(obj->builtin_fun.env);
	free(obj);
	break;
    case SHSL_USER_FUN:
	shsl_del_ref(obj->user_fun.env);
	shsl_obj_free(obj->user_fun.lambda_list);
	for(size_t i = 0; i<obj->user_fun.body_len; ++i)
	    shsl_expr_free(obj->user_fun.body[i]);
	free(obj);
	break;
    case SHSL_BUILTIN_MACRO:
	shsl_del_ref(obj->builtin_macro.env);
	free(obj);
	break;
    case SHSL_USER_MACRO:
	shsl_del_ref(obj->user_fun.env);
	shsl_obj_free(obj->user_fun.lambda_list);
	for(size_t i = 0; i<obj->user_fun.body_len; ++i)
	    shsl_expr_free(obj->user_fun.body[i]);
	free(obj);
	break;

    default:
	free(obj);
	break;
    }

#ifdef SHSL_LOG_GC
    fprintf(stdout, "[SHSL GC]: freed object %p\n", (void*)obj);
#endif    
}
// all C string are copied by shsl_mk* constructors so there is no need to copy them
// in this function, the constructors will do their thing for copying the data
shsl_obj* shsl_copy(shsl_obj* obj) {
    switch(obj->type) {
    case SHSL_NIL:		return obj;
    case SHSL_SYM:		return shsl_mksym(obj->sym.name->str);
    case SHSL_INT:		return shsl_mkint(obj->i);
    case SHSL_REAL:		return shsl_mkint(obj->r);
    case SHSL_STRING:		return shsl_mkstr(obj->str);

    case SHSL_ERR:		return shsl_mkerr(shsl_copy(obj->err.data),
						  obj->err.msg->str);

    case SHSL_CONS:	        return shsl_mkcons(shsl_copy(obj->cons.car),
						   shsl_copy(obj->cons.cdr));
						      
    case SHSL_VEC: {
	shsl_obj* copy = shsl_mkvec(obj->vec.size);
	shsl_vec_foreach(i, elt, obj)
	    shsl_vec_push(copy, shsl_copy(elt));
	return copy;
    }
    case SHSL_MAP: {
	shsl_obj* copy = shsl_mkmap(obj->map.size);
	for(size_t i = 0; i<obj->map.size; ++i) {
	    shsl_map_set(copy,
			 shsl_copy(obj->map.buf[i].k),
			 shsl_copy(obj->map.buf[i].v));
	}
	return copy;
    }

    case SHSL_BUILTIN_FUN:
    case SHSL_USER_FUN:
    case SHSL_BUILTIN_MACRO:
    case SHSL_USER_MACRO:
	fprintf(stderr, "[SHSL WARNING]: function object not copyable!\n");
	return NULL;
    }
}
bool shsl_eq(shsl_obj* lhs, shsl_obj* rhs) {
    if(lhs->type != rhs->type)
	return false;
	
    switch(lhs->type) {
    case SHSL_NIL:
	return true;
    case SHSL_SYM:
	return strcmp(lhs->sym.name->str, rhs->sym.name->str) == 0;
    case SHSL_ERR:
	return strcmp(lhs->err.msg->str, rhs->err.msg->str) == 0
	    && shsl_eq(lhs->err.data, lhs->err.data);

    case SHSL_INT:
	return lhs->i == rhs->i;
    case SHSL_REAL:
	return lhs->r == rhs->r;
    case SHSL_STRING:
	return strcmp(lhs->str, rhs->str) == 0;

    case SHSL_CONS:
	return shsl_eq(lhs->cons.car, rhs->cons.car)
	    && shsl_eq(lhs->cons.cdr, rhs->cons.cdr);

    case SHSL_VEC:
	if(lhs->vec.size != rhs->vec.size)
	    return false;
	for(size_t i = 0; i<lhs->vec.size; ++i)
	    if(!shsl_eq(lhs->vec.buf[i], rhs->vec.buf[i]))
		return false;
	return true;

    case SHSL_MAP:
	if(lhs->map.size != rhs->map.size)
	    return false;
	for(size_t i = 0; i<lhs->map.size; ++i)
	    if(!shsl_eq(shsl_map_get(lhs, lhs->map.buf[i].k),
			shsl_map_get(rhs, lhs->map.buf[i].k)))
		return false;
	return true;
    case SHSL_BUILTIN_FUN:
    case SHSL_USER_FUN:
    case SHSL_BUILTIN_MACRO:
    case SHSL_USER_MACRO:
	fprintf(stderr, "TODO: this comparison's not implemeneted yet!\n");
	return false;
    }
}

// dst = src
// dst loses a ref
// src gains a ref
// only use when overwriting an old value, do not use for initializatin code 
void shsl_set(shsl_obj** dst, shsl_obj* src) {
    shsl_add_ref(src);
    shsl_del_ref(*dst);
    *dst = src;
}

/// CONS MANIPULATIONS DEFINITIONS
void shsl_set_car(shsl_obj* cons_obj, shsl_obj* new_car) {
    assert(cons_obj->type == SHSL_CONS);
    shsl_set(&(cons_obj->cons.car), new_car);
}
void shsl_set_cdr(shsl_obj* cons_obj, shsl_obj* new_cdr) {
    assert(cons_obj->type == SHSL_CONS);
    shsl_set(&(cons_obj->cons.cdr), new_cdr);
}

/// VECTOR MANIPULATIONS DEFINITIONS
void shsl_vec_expand(shsl_obj* vec_obj, size_t new_size) {
    assert(vec_obj->type == SHSL_VEC);

    if(vec_obj->vec.capacity >= new_size)
	return;
    vec_obj->vec.buf = (shsl_obj**)realloc(vec_obj->vec.buf,
					   new_size*sizeof(shsl_obj*));
    vec_obj->vec.capacity = new_size;
}
void shsl_vec_push(shsl_obj* vec_obj, shsl_obj* obj) {
    assert(vec_obj->type == SHSL_VEC);

    if(vec_obj->vec.size == vec_obj->vec.capacity)
	shsl_vec_expand(vec_obj,
			vec_obj->vec.capacity
			+ (vec_obj->vec.capacity/2)
			+ 1);

    // append
    shsl_add_ref(obj);
    vec_obj->vec.buf[vec_obj->vec.size] = obj;
    vec_obj->vec.size++;
}
shsl_obj* shsl_vec_get(shsl_obj* vec_obj, size_t i) {
    assert(vec_obj->type == SHSL_VEC);

    if(i >= vec_obj->vec.size)
	return shsl_mkerr(&SHSL_GLOBAL_NIL, "out of bounds array read!");
    return vec_obj->vec.buf[i];
}
void shsl_vec_set(shsl_obj* vec_obj, size_t i, shsl_obj* new_val) {
    assert(vec_obj->type == SHSL_VEC);

    // TODO: gestione degli errori un po' di più magari
    if(i >= vec_obj->vec.size)
	fprintf(stderr, "out of bounds array write!\n");

    shsl_add_ref(new_val);
    shsl_del_ref(vec_obj->vec.buf[i]);
    vec_obj->vec.buf[i] = new_val;
}
size_t shsl_vec_length(shsl_obj* vec_obj) {
    assert(vec_obj->type == SHSL_VEC);
    return vec_obj->vec.size;
}

/// MAP MANIPULATIONS DEFINITIONS
void shsl_map_expand(shsl_obj* map_obj, size_t new_size) {
    assert(map_obj->type == SHSL_MAP);

    if (map_obj->map.capacity >= new_size)
	return;
    map_obj->map.buf = (shsl_kv*)realloc(map_obj->map.buf,
					 new_size*sizeof(shsl_kv));
    map_obj->map.capacity = new_size;
}
ssize_t shsl_map_index(shsl_obj* map_obj, shsl_obj* key) {
    assert(map_obj->type == SHSL_MAP);

    for(size_t i = 0; i<map_obj->map.size; ++i)
	if(shsl_eq(key, map_obj->map.buf[i].k))
	    return (ssize_t)i;
    return -1;
}
shsl_obj* shsl_map_get(shsl_obj* map_obj, shsl_obj* key) {
    assert(map_obj->type == SHSL_MAP);

    ssize_t i = shsl_map_index(map_obj, key);
    if(i>=0) return map_obj->map.buf[i].v;
    return &SHSL_GLOBAL_NIL;
}
void shsl_map_set(shsl_obj* map_obj, shsl_obj* key, shsl_obj* new_val) {
    assert(map_obj->type == SHSL_MAP);

    ssize_t i = shsl_map_index(map_obj, key);
    if(i>=0) {
	shsl_add_ref(new_val);
	shsl_del_ref(map_obj->map.buf[i].v);
	map_obj->map.buf[i].v = new_val;
    }
    else {
	if(map_obj->map.size == map_obj->map.capacity)
	    shsl_map_expand(map_obj,
			    map_obj->vec.capacity
			    + (map_obj->vec.capacity/2)
			    + 1);

	shsl_add_ref(key);
	shsl_add_ref(new_val);
	map_obj->map.buf[map_obj->map.size] = (shsl_kv) {
	    .k = key,
	    .v = new_val,
	};
	map_obj->map.size++;
    }
}

/// COLLECTION BUILDERS DEFINITIONS
typedef struct shsl_cb {
    SHSL_CB_TYPE type;
    union {
        struct {
            shsl_obj* first; shsl_obj* last;
        } cons_builder;
        struct {
            shsl_obj* vec;
        } vec_builder;
        struct {
            shsl_obj* map; shsl_obj* curr_key; bool reading_key;
        } map_builder;
    };
} shsl_cb;
shsl_cb shsl_cb_make(SHSL_CB_TYPE type) {
    switch(type) {
    case SHSL_CB_LIST:
	return (shsl_cb) {
	    .type = SHSL_CB_LIST,
	    .cons_builder.first = &SHSL_GLOBAL_NIL,
	    .cons_builder.last = &SHSL_GLOBAL_NIL,
	};
    case SHSL_CB_VEC:
	return (shsl_cb) {
	    .type = SHSL_CB_VEC,
	    .vec_builder.vec = shsl_mkvec(1),
	};
    case SHSL_CB_MAP:
	return (shsl_cb) {
	    .type = SHSL_CB_MAP,
	    .map_builder.map = shsl_mkmap(1),
	    .map_builder.reading_key = true,
	    .map_builder.curr_key = NULL,
	};
    }
}
void shsl_cb_add(shsl_cb* cb, shsl_obj* obj) {
    switch(cb->type) {
    case SHSL_CB_LIST: 
	if(cb->cons_builder.first->type == SHSL_NIL) {
	    cb->cons_builder.first = shsl_mkcons(obj, &SHSL_GLOBAL_NIL);
	    cb->cons_builder.last = cb->cons_builder.first;
	}
	else { 
	    shsl_set_cdr
		(cb->cons_builder.last,
		 shsl_mkcons(obj, &SHSL_GLOBAL_NIL));
	    cb->cons_builder.last = cb->cons_builder.last->cons.cdr;
	}
	break;
    case SHSL_CB_VEC: 
	shsl_vec_push(cb->vec_builder.vec, obj);
	break;
    case SHSL_CB_MAP: 
	if(cb->map_builder.reading_key) {
	    cb->map_builder.curr_key = obj;
	    cb->map_builder.reading_key = false;
	}
	else {
	    shsl_map_set
		(cb->map_builder.map,
		 cb->map_builder.curr_key,
		 obj);
	    cb->map_builder.reading_key = true;
	}
    }
}
shsl_obj* shsl_cb_get(shsl_cb cb) {
    switch (cb.type) {
    case SHSL_CB_LIST:
	return cb.cons_builder.first;
    case SHSL_CB_VEC:
	return cb.vec_builder.vec;
    case SHSL_CB_MAP:
	if(cb.map_builder.reading_key)
	    return cb.map_builder.map;
	else
	    return shsl_mkerr (cb.map_builder.map,
			       "tried building map with with odd number of elements!");
    }
}

/// DATA PREDICATES DEFINITIONS
bool shsl_is_nil(const shsl_obj* obj) {
    return obj->type == SHSL_NIL;
}
bool shsl_is_sym(const shsl_obj* obj) {
    return obj->type == SHSL_SYM;
}
bool shsl_is_int(const shsl_obj* obj) {
    return obj->type == SHSL_INT;
}
bool shsl_is_real(const shsl_obj* obj) {
    return obj->type == SHSL_REAL;
}
bool shsl_is_num(const shsl_obj* obj) {
    return shsl_is_int(obj) || shsl_is_real(obj);
}
bool shsl_is_err(const shsl_obj* obj) {
    return obj->type == SHSL_ERR;
}
bool shsl_is_truthy(const shsl_obj* obj) {
    return !(shsl_is_nil(obj) || shsl_is_err(obj));
}

bool shsl_is_cons(const shsl_obj* obj) {
    return obj->type == SHSL_CONS;
}
bool shsl_is_list(const shsl_obj* obj) {
    return shsl_is_nil(obj) || shsl_is_cons(obj);
}
// TODO: infinite loops on circular lists
// I'm already refcounting so I have accepted those will be a pita
// maybe have a tortoise and hare function that detects circular lists
// bool is_circular_list(const shsl_obj* list_obj)
bool shsl_is_proper_list(const shsl_obj* list_obj) {
    while(true) {
	switch(list_obj->type) {
	case SHSL_NIL:
	    return true;
	case SHSL_CONS:
	    list_obj = list_obj->cons.cdr;
	    break;
	default:
	    return false;
	}
    }
}
bool shsl_is_vec(const shsl_obj* obj) {
    return obj->type == SHSL_VEC;
}
bool shsl_is_map(const shsl_obj* obj) {
    return obj->type == SHSL_MAP;
}

/// LIST OPERATIONS DEFINITIONS
shsl_obj* shsl_car(shsl_obj* obj) {
    switch(obj->type) {
    case SHSL_NIL:
	return &SHSL_GLOBAL_NIL;
    case SHSL_CONS:
	return obj->cons.car;
    default:
	return shsl_mkerr(obj, "CAR: cannot get car as object is not a list");
    }
}
shsl_obj* shsl_cdr(shsl_obj* obj) {
    switch(obj->type) {
    case SHSL_NIL:
	return &SHSL_GLOBAL_NIL;
    case SHSL_CONS:
	return obj->cons.cdr;
    default:
	return shsl_mkerr(obj, "CDR: cannot get car as object is not a list");
    }
}
shsl_obj* shsl_nthcdr(shsl_obj* obj, size_t n) {
    while(n-- && !shsl_is_err(obj))
	obj = shsl_cdr(obj);
    if(shsl_is_err(obj))
	return shsl_mkerr(obj, "NTHCDR: cannot get nthcdr of list :(");
    return obj;
}
shsl_obj* shsl_nth(shsl_obj* list_obj, size_t n) {
    shsl_obj* nth = shsl_car(shsl_nthcdr(list_obj, n));
    if(shsl_is_err(nth))
	return shsl_mkerr(nth, "NTH: can't get nth element of object");
    return nth;
}
ssize_t shsl_list_length(shsl_obj* list_obj) {
    for(ssize_t i = 0; ; ++i) {
	switch(list_obj->type) {
	case SHSL_NIL:
	    return i;
	case SHSL_CONS:
	    list_obj = list_obj->cons.cdr;
	    break;
	default:
	    return -1;
	}
    }
}

//// LEXER DEFINITIONS
//// ----------------------------------------------------------------------------
typedef struct shsl_token {
    SHSL_TOKEN_TYPE type;
    shsl_obj* obj;
} shsl_token;
// pair of read token/remaining string after token
// so we can lex a whole string going like:
// read a token, get the rest of the string after the token
// pass the remaining string to the lexer, and on and on again until EOF

// TODO: update into a "lexer state" or something like that also keeping track of
// line number, column number, position, and file name
// for better error reporting
// this would also imply having to change lexer implementation and signatures a bunch
// since, for instance, token_off would likely become a token_advance receiving 
// an initial lexer state, and you'd pass the starting string not to token_off as is 
// but to the some shsl_lexer_initial_state(filename, str); for instance
typedef struct lexer_pair {
    shsl_token token;
    char* remaining;
} lexer_pair;

// read a token off of string and return the pair of that token plus
// the string after the token
lexer_pair token_off(char* str) {
    // handle null pointer string
    if(!str)
	return error_lexer_pair("cannot read null pointer to string!");

    // handle empty string (we reached the null terminator)
    // once we read SHSL_TOK_EOF we don't need to read any more chars, so we 
    // purposefully return an invalid string to ensure that
    if(*str == '\0')
	return (lexer_pair) {
	    .token = empty_token(SHSL_TOK_EOF),
	    .remaining = NULL,
	};

    // skip whitespace
    while(isspace(*str)) str++;

    // handle special chars
    switch(*str) {
	// parentheses
    case '(':
	return (lexer_pair){ .token = empty_token(SHSL_TOK_OPEN_PAREN),
			     .remaining = str+1, };
    case ')':
	return (lexer_pair){ .token = empty_token(SHSL_TOK_CLOSE_PAREN),
			     .remaining = str+1, };
    case '[':
	return (lexer_pair){ .token = empty_token(SHSL_TOK_OPEN_SQUARE),
			     .remaining = str+1, };
    case ']':
	return (lexer_pair){ .token = empty_token(SHSL_TOK_CLOSE_SQUARE),
			     .remaining = str+1, };
    case '{':
	return (lexer_pair){ .token = empty_token(SHSL_TOK_OPEN_CURLY),
			     .remaining = str+1, };
    case '}':
	return (lexer_pair){ .token = empty_token(SHSL_TOK_CLOSE_CURLY),
			     .remaining = str+1, };

	// quotes and quasiquotes 
    case '\'':
	return (lexer_pair){ .token = empty_token(SHSL_TOK_QUOTE),
			     .remaining = str+1, };
    case '`':
	return (lexer_pair){ .token = empty_token(SHSL_TOK_QUASIQUOTE),
			     .remaining = str+1, };
    case ',':
	return (lexer_pair){ .token = empty_token(SHSL_TOK_COMMA),
			     .remaining = str+1, };

	// string literals
	// TODO: we currently don't handle escape sequences
    case '"': {
	char* c = str+1;
	while (*c!='\0' && *c!='"') c++;
	// handle unterminated string literal
	if(*c=='\0') {
	    return error_lexer_pair("unterminated string literal!");
	}
	else {
	    size_t len = (c-str);
	    // remove beginning and ending '"' and add null terminator
	    char* s = calloc(len, sizeof(char));
	    memcpy(s, str+1, len);
	    s[len-1] = '\0';
	    return (lexer_pair) {
		.token = (shsl_token) {
		    .type = SHSL_TOK_STRING,
		    .obj = shsl_mkstr(s),
		},
		.remaining = c+1, // skip final delimiting '"'
	    };
	}
    }
    }

    // if we got here then it's not a special char
    // it's either a symbol or a number
    char* c = str;
    while(is_symbol_char(*c)) c++;

    return (lexer_pair){
	.token = parse_non_special_token(str, c-str),
	.remaining = c,
    };
}
// for a lot of token types (parens, quotes, et al) we only need to know the type
// of the token and don't really need the object the token carries,
// return a token with that type and no underlying object that we care about
shsl_token empty_token(SHSL_TOKEN_TYPE token_type) {
    return (shsl_token) {
	.type = token_type,
	.obj = &SHSL_GLOBAL_NIL,
    };
}
// since we return errors as special token pairs, might as well have an
// ad hoc function for that
lexer_pair error_lexer_pair(const char* errmsg) {
    return (lexer_pair) {
	.token = (shsl_token) {
	    .type = SHSL_TOK_ERROR,
	    .obj = shsl_mkstr(errmsg),
	},
	.remaining = NULL,
    };
}

// special characters are chars that once encountered you go like
// "ok, I'm done with the current thing, this character starts the next thing"
bool is_special_char(char c) {
    char* s = "()[]{}'`,\"";
    while(*s!='\0' && *s!=c) s++;
    return *s!='\0';
}
// character that can be part of a symbol (or number)
bool is_symbol_char(char c) {
    return isprint(c) && (!isspace(c)) && (!is_special_char(c));
}
// parse a non special token starting at c
// a non special token is a token not made of/delimited by special chars
// can be either symbol or a number
// if from c onwards is a valid integer, returns an integer token
// otherwise same with floats
// otherwise returns a symbol, if the symbol is nil it returns a nil token
shsl_token parse_non_special_token(char*c, size_t len) {
    long l;
    if (try_parse_integer(c, len, &l))
	return (shsl_token) {
	    .type = SHSL_TOK_INTEGER,
	    .obj = shsl_mkint(l),
	};

    if (len == 3 && c[0] == 'n' && c[1] == 'i' && c[2] == 'l')
	return (shsl_token) {
	    .type = SHSL_TOK_NIL,
	    .obj = &SHSL_GLOBAL_NIL,
	};
	
    char* newstr = slice_to_fresh_str(c, len);
    shsl_token t =  (shsl_token) {
	.type = SHSL_TOK_SYMBOL,
	.obj = shsl_mksym(newstr),
    };
    free(newstr);
    return t;
}
// try parsing from c to c+len as an integer
// if success, return true and write the result into the *into pointer
// if failure (it wasn't an integer), return false and leave *into unaltered
bool try_parse_integer(char* c, size_t len, long* into) {
    long acc = 0;
    bool neg = false;
    if(len == 1 && (*c == '-' || *c == '+')) return false;
    if(*c=='+') {
	len--;
	c++;
    }
    if(*c=='-') {
	neg = true;
	len--;
	c++;
    }
    while(len--) {
	if(*c > '9' || *c < '0')
	    return false;
	acc = (acc*10) + (*c-'0');
	c++;
    }
    if(neg) acc = -acc;
    *into = acc;
    return true;
}
// copy characters from c to c+len into a fresh null terminated string
char* slice_to_fresh_str(const char* c, size_t len) {
    char* fresh = calloc(len+1, sizeof(char));
    memcpy(fresh, c, len);
    fresh[len] = '\0';
    return fresh;
}

//// PARSER DEFINITIONS
//// ----------------------------------------------------------------------------

// same logic as lexer_pair
// TODO: update into parser state?
typedef struct parser_pair {
    shsl_obj* obj;
    char* remaining;
} parser_pair;
parser_pair parse_off(char* str) {
    lexer_pair lp = token_off(str);
    switch(lp.token.type) {
	// handle literals
    case SHSL_TOK_NIL:
    case SHSL_TOK_SYMBOL:
    case SHSL_TOK_INTEGER:
    case SHSL_TOK_REAL:
    case SHSL_TOK_STRING:
	return (parser_pair) {
	    .obj = lp.token.obj,
	    .remaining = lp.remaining,
	};

	// handle parens	
    case SHSL_TOK_OPEN_PAREN:
	return parse_until(lp.remaining,
			   shsl_cb_make(SHSL_CB_LIST),
			   SHSL_TOK_CLOSE_PAREN,
			   (SHSL_TOKEN_TYPE[]){SHSL_TOK_CLOSE_SQUARE,
					       SHSL_TOK_CLOSE_CURLY},
			   2);
    case SHSL_TOK_OPEN_SQUARE:
	return parse_until(lp.remaining,
			   shsl_cb_make(SHSL_CB_VEC),
			   SHSL_TOK_CLOSE_SQUARE,
			   (SHSL_TOKEN_TYPE[]){SHSL_TOK_CLOSE_PAREN,
					       SHSL_TOK_CLOSE_CURLY},
			   2);
    case SHSL_TOK_OPEN_CURLY:
	return parse_until(lp.remaining,
			   shsl_cb_make(SHSL_CB_MAP),
			   SHSL_TOK_CLOSE_CURLY,
			   (SHSL_TOKEN_TYPE[]){SHSL_TOK_CLOSE_PAREN,
					       SHSL_TOK_CLOSE_SQUARE},
			   2);
	
	// handle quotes
    case SHSL_TOK_QUOTE: {
	parser_pair pp = parse_off(lp.remaining);
	return (parser_pair) {
	    .obj = shsl_mkcons(shsl_mksym("quote"),
			       shsl_mkcons(pp.obj, &SHSL_GLOBAL_NIL)),
	    .remaining = pp.remaining,
	};
    }
    case  SHSL_TOK_QUASIQUOTE: {
	parser_pair pp = parse_off(lp.remaining);
	return (parser_pair) {
	    .obj = shsl_mkcons(shsl_mksym("quasiquote"),
			       shsl_mkcons(pp.obj, &SHSL_GLOBAL_NIL)),
	    .remaining = pp.remaining,
	};
    }
    case  SHSL_TOK_COMMA: {
	parser_pair pp = parse_off(lp.remaining);
	return (parser_pair) {
	    .obj = shsl_mkcons(shsl_mksym("comma"),
			       shsl_mkcons(pp.obj, &SHSL_GLOBAL_NIL)),
	    .remaining = pp.remaining,
	};
    }

	// TODO: better error/finish return
    case SHSL_TOK_CLOSE_PAREN:
	fprintf(stderr, "mismatched close parentheses");
	return (parser_pair){0};
    case SHSL_TOK_CLOSE_SQUARE:
	fprintf(stderr, "mismatched close square bracket");
	return (parser_pair){0};
    case SHSL_TOK_CLOSE_CURLY:
	fprintf(stderr, "mismatched close curly bracket");
	return (parser_pair){0};
    case SHSL_TOK_ERROR:
	fprintf(stderr,
		"cannot parse further, "
		"lexer exited with the following error\n%s\n",
		lp.token.obj->str);
	return (parser_pair){0};

    case SHSL_TOK_EOF:
	return (parser_pair){0};
    }
}
parser_pair parse_until(char* str,
			shsl_cb cb,
			SHSL_TOKEN_TYPE stop,
			SHSL_TOKEN_TYPE* error_on, size_t error_on_len) {
    // we only use this lexer_pair to peek the next token
    // if the next token is our stop token, we stop
    // if it's one of our error tokens, we error
    // otherwise we parse the next object on until we reach a stop token
    while(true) {
	lexer_pair lp = token_off(str);
	if(lp.token.type == stop)
	    return (parser_pair) {
		.obj = shsl_cb_get(cb),
		.remaining = lp.remaining,
	    };

	for(size_t i = 0; i<error_on_len; ++i)
	    if(lp.token.type == error_on[i]) {
		fprintf(stderr,
			"error: open parentheses \"%s\" closed by \"%s\"\n",
			stop == SHSL_TOK_CLOSE_PAREN ? "("
			: stop == SHSL_TOK_CLOSE_SQUARE ? "["
			: stop == SHSL_TOK_CLOSE_CURLY ? "{"
			: "wtf bro",
			error_on[i] == SHSL_TOK_CLOSE_PAREN ? ")"
			: error_on[i] == SHSL_TOK_CLOSE_SQUARE ? "]"
			: error_on[i] == SHSL_TOK_CLOSE_CURLY ? "}"
			: "WTF BRO");
		return (parser_pair){0};
	    }

	// append parsed object to acc list
	parser_pair pp = parse_off(str);
	shsl_cb_add(&cb, pp.obj);
	str = pp.remaining;
    }
}

//// EVALUATOR DEFINITIONS
//// ----------------------------------------------------------------------------

/// EXPRESSION TYPE DEFINITIONS
// NOTE
// literals don't own the expression they're literals of, they hold a ref to it
// when deleting literals, only decrease the refcount of the ref
// (shit gets weird with symbols so...)
// that said, when evaluated literals will return a safe copy of the object they
// hold
// so that setting something to a literal and changint it doesn't alter
// the literal
// 
// expressions do own their subexpressions tho
// when deleting an expression, delete its subexpressions as well
typedef struct shsl_vec_expr {
    shsl_expr** elts;
    size_t size;
} shsl_vec_expr;
typedef struct shsl_map_expr {
    shsl_expr** keys;
    shsl_expr** vals;
    size_t size;
} shsl_map_expr;
typedef struct shsl_if_expr {
    shsl_expr* condition;
    shsl_expr* then_part;
    shsl_expr* else_part;
} shsl_if_expr;
typedef struct shsl_do_expr {
    shsl_expr* body;
    size_t body_length;
} shsl_do_expr;
typedef struct shsl_do_poking_expr {
    shsl_expr* body;
    size_t body_length;
} shsl_do_poking_expr;
typedef struct shsl_def_expr {
    shsl_obj* name;           // must be symbol
    shsl_expr* value;
} shsl_def_expr;
typedef struct set_expr {
    shsl_obj* name;           // must be symbol
    shsl_expr* value;
} set_expr;
typedef struct shsl_funcall_expr {
    shsl_expr* fun_expr;
    shsl_expr** args_exprs;
    size_t args_len;
} shsl_funcall_expr;
typedef struct shsl_expr {
    SHSL_EXPR_TYPE type;
    union {
	shsl_obj* literal;
	shsl_obj* lookup_symbol; // must be symbol

	shsl_vec_expr vec_expr;
	shsl_map_expr map_expr;

	shsl_if_expr if_expr;
	shsl_do_expr do_expr;
	shsl_do_poking_expr do_poking_expr;
	shsl_def_expr def_expr;
	set_expr set_expr;
	shsl_funcall_expr funcall_expr;
    };
} shsl_expr;

/// EXPRESSION FUNCTION DEFINITIONS
// https://stackoverflow.com/questions/6750512/gcc-warning-iso-c-does-not-permit-named-variadic-macros
#define return_mallocd_expr(...) do {			\
	shsl_expr* expr =				\
	    (shsl_expr*)malloc(sizeof(shsl_expr));	\
	*expr = (shsl_expr){__VA_ARGS__};		\
	return expr;					\
    } while(0)
shsl_expr* shsl_error_expr(shsl_obj* form, const char* msg, ...) {
    va_list args;
    va_start(args, msg);
    shsl_obj* err = shsl_vmkerr(form, msg, args);
    va_end(args);
#ifdef SHSL_LOG_ERROR_EXPR
    fprintf(stderr, "[EXPRESSION PARSING ERROR]: %s\n", err->msg);
#endif
    return_mallocd_expr(.type = SHSL_EXPR_LITERAL,
			.literal = err);
}

/// FORM TRANSLATION FUNCTIONS DEFINITIONS
// TODO: when returning an error we should free any temporary forms we allocated
// and didn't use in the returned error
// TODO: we need a function to free expression objects
shsl_expr* shsl_form_to_expr(shsl_obj* form) {
    switch(form->type) {
    case SHSL_INT:
    case SHSL_REAL:
    case SHSL_STRING:
    case SHSL_NIL:
	return_mallocd_expr(.type = SHSL_EXPR_LITERAL,
			    .literal = shsl_add_ref(form));

    case SHSL_SYM:
	return_mallocd_expr(.type = SHSL_EXPR_LOOKUP,
			    .lookup_symbol = shsl_add_ref(form));

    case SHSL_VEC: {
	shsl_expr** elt_exprs = calloc(form->vec.size, sizeof(shsl_expr*));

	shsl_vec_foreach(i, form_elt, form) {
	    shsl_expr* next = shsl_form_to_expr(form_elt);
	    if(!shsl_expr_is_error(next)) {
		elt_exprs[i] = next;
	    }
	    else {
		for(size_t j = 0; j<i; ++j)
		    shsl_expr_free(elt_exprs[j]);
		free(elt_exprs);
		return shsl_error_expr(form,
				       "cannot parse vector because item at position "
				       "%zu of vector was malformed!", i);
	    }
	}

	return_mallocd_expr(.type = SHSL_EXPR_VEC,
			    .vec_expr = (shsl_vec_expr) {
				.elts = elt_exprs,
				.size = shsl_vec_length(form),
			    });
    }

    case SHSL_MAP: {
	shsl_expr** key_exprs = calloc(form->map.size, sizeof(shsl_expr*));
	shsl_expr** val_exprs = calloc(form->map.size, sizeof(shsl_expr*));

	for(size_t i = 0; i<form->map.size; ++i) {
	    shsl_expr* next_key = shsl_form_to_expr(form->map.buf[i].k);
	    shsl_expr* next_val = shsl_form_to_expr(form->map.buf[i].v);

	    if(!(shsl_expr_is_error(next_key) || shsl_expr_is_error(next_val))) {
		key_exprs[i] = next_key;
		val_exprs[i] = next_val;
	    }
	    else {
		for(size_t j = 0; j<i; ++j) {
		    shsl_expr_free(key_exprs[j]);
		    shsl_expr_free(val_exprs[j]);
		}
		free(key_exprs);
		free(val_exprs);
		if(shsl_expr_is_error(next_key))
		    return shsl_error_expr
			(next_key->literal,
			 "cannot parse map literal because key at position "
			 "%zu of literal was malformed!", i);
		else
		    return shsl_error_expr
			(next_val->literal,
			 "cannot parse map literal because value at position "
			 "%zu of literal was malformed!", i);
	    }
	}

	return_mallocd_expr(.type = SHSL_EXPR_MAP,
			    .map_expr = (shsl_map_expr) {
				.keys = key_exprs,
				.vals = val_exprs,
				.size = form->map.size,
			    });
    }

    case SHSL_ERR:
	return shsl_error_expr
            (form, "an error object was passed to the parser");

    case SHSL_CONS: {
	if(!shsl_is_proper_list(form))
	    return shsl_error_expr
		(form,
		 "not well formed list, cannot parse into expression");

	size_t form_length = (size_t)shsl_list_length(form);

	if(form->cons.car->type == SHSL_SYM) {
	    char* s = form->cons.car->sym.name->str;
	    if(strcmp(s, "quote") == 0) {
		if(form_length != 2)
		    return
			shsl_error_expr
			(form,
                         "malformed quote form, length of quote form must be "
			 "exactly 2, just the 'quote symbol and the quoted "
			 "datum");
		shsl_obj* literal = shsl_nth(form, 1);
		if(shsl_is_err(literal))
		    return shsl_error_expr
                        (literal,
                         "cannot parse quote expression because"
                         "literal in quote was malformed");
		return_mallocd_expr(.type = SHSL_EXPR_LITERAL,
				    .literal = shsl_add_ref(literal)); 
	    }

	    else if(strcmp(s, "if") == 0) {
		if(form_length < 3)
		    return shsl_error_expr
                        (form, "malformed if statement, too short");
		if(form_length > 4)
		    return shsl_error_expr
                        (form, "malformed if statement, too long");
				
                // error expressions store the error value in the literal
                // field of their union
                // TODO: find a way to return propagating parser errors
                // that doesn't expose this detail this hard :( 
		shsl_expr* c = shsl_form_to_expr(shsl_nth(form, 1));
		if(shsl_expr_is_error(c))
		    return shsl_error_expr
			(c->literal,
                         "cannot parse if form, malformed conditional!");
		shsl_expr* t = shsl_form_to_expr(shsl_nth(form, 2));
		if(shsl_expr_is_error(t))
		    return shsl_error_expr
			(t->literal,
                         "cannot parse if form, malformed then part!");
		shsl_expr* e = shsl_form_to_expr(shsl_nth(form, 3));
		if(shsl_expr_is_error(e))
		    return shsl_error_expr
			(e->literal,
                         "cannot parse if form, malformed else part!");

		return_mallocd_expr(.type = SHSL_EXPR_IF,
				    .if_expr = (shsl_if_expr) {
					.condition = c,
					.then_part = t,
					.else_part = e
				    });
	    }
	    
	    else if(strcmp(s, "do") == 0)
		assert(0 && "TODO: DO");
	    else if(strcmp(s, "do-poking") == 0)
		assert(0 && "TODO: DO-POKING");
	    else if(strcmp(s, "set") == 0)
		assert(0 && "TODO: SET");
	    else if(strcmp(s, "def") == 0)
		assert(0 && "TODO: DEF");
	}

	shsl_expr* fun_expr = shsl_form_to_expr(form->cons.car);
	shsl_expr** args_exprs = calloc(form_length, sizeof(shsl_expr*));
	for(size_t i = 0; i<form_length-1; ++i) {
	    args_exprs[i] = shsl_form_to_expr(shsl_nth(form, i+1));
	}
	return_mallocd_expr(.type = SHSL_EXPR_FUNCALL,
			    .funcall_expr = (shsl_funcall_expr) {
				.fun_expr = fun_expr,
				.args_exprs = args_exprs,
				.args_len = form_length - 1,
			    });
    }
	break;
	// else if lambda_expr_p(c->cons.car)
	// { compile to immediate lambda call }
	// else
	// { error }
    case SHSL_BUILTIN_FUN:
    case SHSL_USER_FUN:
    case SHSL_BUILTIN_MACRO:
    case SHSL_USER_MACRO:
	return shsl_error_expr
	    (form,
	     "cannot include function object in source code of expression!"); 
    }
}
bool shsl_expr_is_error(shsl_expr* expr) {
    return expr->type == SHSL_EXPR_LITERAL
	&& expr->literal->type == SHSL_ERR;
}
void shsl_expr_free(shsl_expr* expr) {
    // recall
    // expressions don't own any shsl_obj they might contain
    // they only hold a reference to it
    // only delete references to objects they hold, don't free them outright
    // expressions *do* own their subexpressions
    // free any subexpression of the expression you're freeing rn
    switch(expr->type) {
    case SHSL_EXPR_LITERAL:
	shsl_del_ref(expr->literal);
	free(expr);
	break;
    case SHSL_EXPR_LOOKUP:
	shsl_del_ref(expr->lookup_symbol);
	free(expr);
	break;
    case SHSL_EXPR_VEC:
	for(size_t i = 0; i<expr->vec_expr.size; ++i) {
	    shsl_expr_free(expr->vec_expr.elts[i]);
	}
	free(expr);
	break;
    case SHSL_EXPR_MAP:
	for(size_t i = 0; i<expr->map_expr.size; ++i) {
	    shsl_expr_free(expr->map_expr.keys[i]);
	    shsl_expr_free(expr->map_expr.vals[i]);
	}
	free(expr);
	break;
    case SHSL_EXPR_IF:
	shsl_expr_free(expr->if_expr.condition);
	shsl_expr_free(expr->if_expr.then_part);
	shsl_expr_free(expr->if_expr.else_part);
	free(expr);
	break;
    case SHSL_EXPR_LET:
	assert(0 && "TODO: free let expr");
	break;
    case SHSL_EXPR_WHILE:
	assert(0 && "TODO: free while expr");
	break;
    case SHSL_EXPR_DO:
	assert(0 && "TODO: free do expr");
	break;
    case SHSL_EXPR_DO_POKING:
	assert(0 && "TODO: free do poking expr");
	break;
    case SHSL_EXPR_DEF:
	assert(0 && "TODO: free def expr");
	break;
    case SHSL_EXPR_SET:
	assert(0 && "TODO: free set expr");
	break;
    case SHSL_EXPR_FN:
	assert(0 && "TODO: free fn expr");
	break;
    case SHSL_EXPR_MACRO:
	assert(0 && "TODO: free macro expr");
	break;
    case SHSL_EXPR_FUNCALL:
	fprintf(stderr, "[SHSL WARNING]: TODO free funcall expr\n");
	break;
    }
}

shsl_obj* shsl_env_mkframe(shsl_obj* syms, shsl_obj* vals) {
    assert(syms->type == SHSL_VEC);
    assert(vals->type == SHSL_VEC);
    assert(syms->vec.size == vals->vec.size);

    shsl_obj* frame = shsl_mkmap(syms->vec.size);
    shsl_vec_foreach(i, sym, syms) {
	shsl_obj* val = shsl_vec_get(vals, i);
	shsl_map_set(frame, sym, val);
    }
    return frame;
}

/// EVALUATION FUNCTIONS DEFINITIONS
// TODO: it
shsl_obj* shsl_eval(shsl_expr* expr, shsl_obj* env) {
    switch(expr->type) {
    case SHSL_EXPR_LITERAL:
	return shsl_copy(expr->literal);
    case SHSL_EXPR_LOOKUP:
	return shsl_env_lookup(env, expr->lookup_symbol);

    case SHSL_EXPR_VEC: {
	size_t size = expr->vec_expr.size;
	shsl_obj* vec = shsl_mkvec(size);
	for(size_t i = 0; i<size; ++i)
	    shsl_vec_push(vec, shsl_eval(expr->vec_expr.elts[i], env));
	return vec;
    }
	
    case SHSL_EXPR_MAP: {
	size_t size = expr->map_expr.size;
	shsl_obj* map = shsl_mkmap(size);
	for(size_t i = 0; i<size; ++i)
	    shsl_map_set(map,
			 shsl_eval(expr->map_expr.keys[i], env),
			 shsl_eval(expr->map_expr.vals[i], env));
	return map;
    }

    case SHSL_EXPR_IF:
	if(shsl_is_truthy(shsl_eval(expr->if_expr.condition, env)))
	    return shsl_eval(expr->if_expr.then_part, env);
	else
	    return shsl_eval(expr->if_expr.else_part, env);
    case SHSL_EXPR_FUNCALL: {
	shsl_obj* fun = shsl_eval(expr->funcall_expr.fun_expr, env);
	switch(fun->type) {
	case SHSL_BUILTIN_FUN: {
	    shsl_obj* args = shsl_eval_many_into_vec
		(expr->funcall_expr.args_exprs,
		 expr->funcall_expr.args_len,
		 env);
	    // TODO: bit of a dick move, but as of now builtin funs
	    // are evaluated within the calling environment
	    // making them a gross violation of lexical binding
	    shsl_obj* res = fun->builtin_fun.apply(args, env);
	    shsl_obj_free(args);
	    return res;
	}
	case SHSL_USER_FUN:
	    return shsl_mkerr(fun, "not implemented yet!"); 
	case SHSL_BUILTIN_MACRO:
	    return shsl_mkerr(fun, "not implemented yet!"); 
	case SHSL_USER_MACRO:
	    return shsl_mkerr(fun, "not implemented yet!"); 
	default:
	    return shsl_mkerr(fun, "object is not callable!"); 
	}
    }
    case SHSL_EXPR_WHILE:
    case SHSL_EXPR_DO:
    case SHSL_EXPR_DO_POKING:
    case SHSL_EXPR_LET:
    case SHSL_EXPR_DEF:
    case SHSL_EXPR_SET:
    case SHSL_EXPR_FN:
    case SHSL_EXPR_MACRO:
	assert(0 && "TODO");
    }
}
shsl_obj* shsl_eval_many_into_vec(shsl_expr** args, size_t args_len,
				  shsl_obj* env) {
    shsl_obj* vec_obj = shsl_mkvec(args_len);
    for(size_t i = 0; i<args_len; ++i) {
	shsl_vec_push(vec_obj, shsl_eval(args[i], env));
    }
    return vec_obj;
}

/// BUILTIN FUNCTIONS DEFINITIONS

// macros to aid in defining a builtin function to call from shsl code
// nothing fancy, just factoring out the boring work
// I might have committed "make a dsl with the c preprocessor" :(, sory
#define shsl_defun(c_name, shsl_name, args_name, env_name, ...)		\
    shsl_obj* c_name(shsl_obj* args_name, shsl_obj* env_name)		\
    {									\
	const char* shsl_fun_name = shsl_name;	/* used by macros */	\
	shsl_fun_assert_vec((args_name));				\
	do __VA_ARGS__ while(0);					\
    }									\

#define shsl_fun_assert(ass) do {				\
	if(!(ass))						\
	    return shsl_mkerr(&SHSL_GLOBAL_NIL,			\
			      "in function %s, assertion "	\
			      #ass "failed!", shsl_fun_name);	\
    } while(0)

#define shsl_fun_assert_vec(args)		\
    shsl_fun_assert(shsl_is_vec(args))

#define shsl_fun_assert_size(args, pred)		\
    shsl_fun_assert((shsl_vec_length(args)) pred)

#define shsl_fun_assert_type(args, i, t)		\
    shsl_fun_assert(shsl_vec_get(args, i)->type == (t))

#define shsl_fun_assert_type_either(args, i, t1, t2)		\
    shsl_fun_assert(shsl_vec_get(args, i)->type == (t1) ||	\
		    shsl_vec_get(args, i)->type == (t2))

shsl_defun(shsl_builtin_vecget, "vecget", args, env, {
	(void)env;
	shsl_fun_assert_size(args, == 2);
	shsl_fun_assert_type(args, 0, SHSL_VEC);
	shsl_fun_assert_type(args, 1, SHSL_INT);
	return shsl_vec_get(args, (size_t)shsl_vec_get(args, 1)->i);
    })

/// SHSL ARITHMETIC FUNCTIONS DEFINITIONS
shsl_defun(shsl_builtin_add, "+", args, env, {
	(void)env;
	shsl_vec_foreach(i, elt, args)
	    shsl_fun_assert_type_either(args, i, SHSL_INT, SHSL_REAL);

	long intsum = 0;
	double longsum = 0.0;
	shsl_vec_foreach(i, elt, args) {
	    if(elt->type == SHSL_REAL)
		goto longsum;
	    else
		intsum += elt->i;
	}
	return shsl_mkint(intsum);

    longsum:
	shsl_vec_foreach(i, elt, args)
	    longsum += shsl_is_int(elt)?(double)elt->i:elt->r;
	return shsl_mkreal(longsum);
    })

shsl_defun(shsl_builtin_sub, "-", args, env, {
	(void)env;
	shsl_vec_foreach(i, elt, args)
	    shsl_fun_assert_type_either(args, i, SHSL_INT, SHSL_REAL);

	if(args->vec.size == 0)
	    return shsl_mkint(0);
	if(args->vec.size == 1)
	    return shsl_mkint(shsl_vec_get(args, 0)->i);

	long acc = args->vec.buf[0]->i;
	for(size_t i = 1; i<shsl_vec_length(args); ++i) {
	    acc -= shsl_vec_get(args, i)->i;
	}

	return shsl_mkint(acc);
    })
shsl_defun(shsl_builtin_mul, "*", args, env, {
	(void)env;
	// we don't support floats yet :|
	shsl_vec_foreach(i, elt, args)
	    shsl_fun_assert_type(args, i, SHSL_INT);

	long acc = 1;
	shsl_vec_foreach(i, elt, args)
	    acc *= elt->i;

	return shsl_mkint(acc);
    })
shsl_defun(shsl_builtin_div, "/", args, env, {
	(void)env;
	shsl_fun_assert_size(args, == 2);
	shsl_fun_assert_type_either(args, 0, SHSL_INT, SHSL_REAL);
	shsl_fun_assert_type_either(args, 1, SHSL_INT, SHSL_REAL);

	// handle case where it returns integer
	if(args->vec.buf[0]->type == SHSL_INT &&
	   args->vec.buf[1]->type == SHSL_INT &&
	   args->vec.buf[1]->i != 0 &&
	   (args->vec.buf[0]->i % args->vec.buf[1]->i) == 0)
	    return shsl_mkint(args->vec.buf[0]->i/args->vec.buf[1]->i);

	double a = args->vec.buf[0]->type == SHSL_INT
	    ? args->vec.buf[0]->i
	    : args->vec.buf[0]->r;
	double b = args->vec.buf[1]->type == SHSL_INT
	    ? args->vec.buf[1]->i
	    : args->vec.buf[1]->r;

	if(b == 0.0)
	    return shsl_mkerr(args, "in function /: division by zero!");

	return shsl_mkreal(a/b);
    })

/// ENVIRONMENT FUNCTIONS DEFINITIONS
shsl_obj* shsl_make_initial_env(void) {
    shsl_obj* frame_obj = shsl_mkmap(20);
    shsl_obj* env_obj = shsl_mkcons(frame_obj, &SHSL_GLOBAL_NIL);
    // t
    shsl_obj* t = shsl_mksym("t");
    shsl_map_set(frame_obj, t, t); // t is self evaluating

    // arithmetic operations 
    // + - * / > < >= <=
    // I might make == generic compairison (a synonim for eq/equal)
    shsl_map_set(frame_obj, shsl_mksym("+"),
		 shsl_mkbuiltin_fun(env_obj, shsl_builtin_add));
    shsl_map_set(frame_obj, shsl_mksym("-"),
		 shsl_mkbuiltin_fun(env_obj, shsl_builtin_sub));
    shsl_map_set(frame_obj, shsl_mksym("*"),
		 shsl_mkbuiltin_fun(env_obj, shsl_builtin_mul));
    shsl_map_set(frame_obj, shsl_mksym("/"),
		 shsl_mkbuiltin_fun(env_obj, shsl_builtin_div));

    // list operations
    // cons, iscons, list, islist, isproper, car, cdr, null

    // vector operations
    // isvec, vecget, vecset, veclen

    // map operations
    // ismap, mapget, mapset, maphas

    // error functions
    // iserror, error

    // collection operations
    // map, filter, reduce

    // introspection functions
    // get the environment as a list lol
    // wait I cannot do that with lexical scoping
    // this is gonna have to be a special form :| 

    // TODO: ctypes equivalent
    return env_obj;
}
shsl_obj* shsl_env_lookup(shsl_obj* env, shsl_obj* key) {
    assert(key->type == SHSL_SYM);
    if(shsl_is_nil(env))
	return shsl_mkerr(key, "symbol not found!");

    assert(env->type == SHSL_CONS);
    assert(env->cons.car->type == SHSL_MAP);

    ssize_t i = shsl_map_index(env->cons.car, key);
    if(i>=0)
	return env->cons.car->map.buf[i].v;
    return shsl_env_lookup(env->cons.cdr, key);
}

//// PRINT DEBUGGING DEFINITIONS
//// ----------------------------------------------------------------------------
void shsl_dbg_fputtok(const shsl_token* tok, FILE* restrict stream) {
    fputs("token ", stream);
    switch(tok->type) {
    case SHSL_TOK_NIL:
	fputs("SHSL_TOK_NIL: ", stream);
	break;
    case SHSL_TOK_INTEGER:
	fputs("SHSL_TOK_INTEGER: ", stream);
	break;
    case SHSL_TOK_REAL:
	fputs("SHSL_TOK_REAL: ", stream);
	break;
    case SHSL_TOK_STRING:
	fputs("SHSL_TOK_STRING: ", stream);
	break;
    case SHSL_TOK_SYMBOL:
	fputs("SHSL_TOK_SYMBOL: ", stream);
	break;
    case SHSL_TOK_QUOTE:
	fputs("SHSL_TOK_QUOTE: ", stream);
	break;
    case SHSL_TOK_QUASIQUOTE:
	fputs("SHSL_TOK_QUASIQUOTE: ", stream);
	break;
    case SHSL_TOK_COMMA:
	fputs("SHSL_TOK_COMMA: ", stream);
	break;
    case SHSL_TOK_OPEN_PAREN:
	fputs("SHSL_TOK_OPEN_PAREN: ", stream);
	break;
    case SHSL_TOK_CLOSE_PAREN:
	fputs("SHSL_TOK_CLOSE_PAREN: ", stream);
	break;
    case SHSL_TOK_OPEN_SQUARE:
	fputs("SHSL_TOK_OPEN_SQUARE: ", stream);
	break;
    case SHSL_TOK_CLOSE_SQUARE:
	fputs("SHSL_TOK_CLOSE_SQUARE: ", stream);
	break;
    case SHSL_TOK_OPEN_CURLY:
	fputs("SHSL_TOK_OPEN_CURLY: ", stream);
	break;
    case SHSL_TOK_CLOSE_CURLY:
	fputs("SHSL_TOK_CLOSE_CURLY: ", stream);
	break;
    case SHSL_TOK_EOF:
	fputs("SHSL_TOK_EOF: ", stream);
	break;
    case SHSL_TOK_ERROR:
	fputs("SHSL_TOK_ERROR: ", stream);
    };
    shsl_fputobj(tok->obj, stream);
}
void shsl_fputobj(const shsl_obj* obj, FILE* restrict stream) {
    switch(obj->type) {
    case SHSL_INT:
	fprintf(stream, "%ld", obj->i);
	break;
    case SHSL_REAL:
	fprintf(stream, "%f", obj->r);
	break;
    case SHSL_STRING:
	fprintf(stream, "\"%s\"", obj->str);
	break;
    case SHSL_SYM:
	fprintf(stream, "%s", obj->sym.name->str);
	break;
    case SHSL_NIL:
	fputs("nil", stream);
	break;
    case SHSL_ERR:
	fprintf(stream, "(ERROR: \"%s\" WITH DATA ", obj->err.msg->str);
	shsl_fputobj(obj->err.data, stream);
	fprintf(stream, ")");
	break;
    case SHSL_CONS:
	if(shsl_is_proper_list(obj)) {
	    fputc('(', stream);
	    while(shsl_is_cons(obj)) {
		shsl_fputobj(obj->cons.car, stream);
		if(shsl_is_cons(obj->cons.cdr))
		    fputs(" ", stream);
		obj = obj->cons.cdr;
	    }
	    fputc(')', stream);
	}
	else {
	    fputc('(', stream);
	    shsl_fputobj(obj->cons.car, stream);
	    fputs(" . ", stream);
	    shsl_fputobj(obj->cons.cdr, stream);
	    fputc(')', stream);
	}
	break;
    case SHSL_VEC:
	fputc('[', stream);
	for(size_t i = 0; i<obj->vec.size; ++i) {
	    shsl_fputobj(obj->vec.buf[i], stream);
	    if(i != obj->vec.size -1)
		fputs(", ", stream);
	}
	fputc(']', stream);
	break;
    case SHSL_MAP:
	fputc('{', stream);
	for(size_t i = 0; i<obj->map.size; ++i) {
	    shsl_fputobj(obj->map.buf[i].k, stream);
	    fputs(":", stream);
	    shsl_fputobj(obj->map.buf[i].v, stream);
	    if(i != obj->vec.size -1)
		fputs(", ", stream);
	}
	fputc('}', stream);
	break;
    case SHSL_BUILTIN_FUN:
	fprintf(stdout, "SHSL_BUILTIN_FUN_%p", (void*)obj);
	break;
    case SHSL_USER_FUN:
	fprintf(stdout, "SHSL_USER_FUN_%p", (void*)obj);
	break;
    case SHSL_BUILTIN_MACRO:
	fprintf(stdout, "SHSL_BUILTIN_MACRO_%p", (void*)obj);
	break;
    case SHSL_USER_MACRO:
	fprintf(stdout, "SHSL_USER_MACRO_%p", (void*)obj);
	break;
    };
}

//// USER FACING FUNCTIONS DEFINITIONS
//// ----------------------------------------------------------------------------
shsl_obj* shsl_eval_str(char* c, shsl_obj* env) {
    parser_pair p = parse_off(c);
    // TODO: make form_to_expr accept an environment so we can do macro expansion
    // during form "compilation"?
    shsl_add_ref(p.obj);
    shsl_expr* expr = shsl_form_to_expr(p.obj);
    shsl_del_ref(p.obj);

    shsl_obj* res = shsl_eval(expr, env);
    shsl_expr_free(expr);
    return res; 
}
#endif // SHSL_IMPLEMENTATION

#ifdef SHSL_MAIN
int main(int argc, char** argv) {
    // usage
    // -e 'str' evals that string
    // -f 'file' evals that file
    // -r starts a repl
    // -h prints a help message
    // flags can be put one after the other and are evaluated in order
    int i = 1;
    shsl_obj* env = shsl_make_initial_env();
    while(i<argc) {
	if(strcmp(argv[i], "-e") == 0) {
	    shsl_fputobj(shsl_eval_str(argv[i+1], env), stdout);
	    puts("");
	    i+=2;
	}
	else if(strcmp(argv[i], "-f") == 0) {
	    fputs("-f flag not implemented yet!\n", stderr);
	    i+=2;
	}
	else if(strcmp(argv[i], "-r") == 0) {
	    fputs("-r flag not implemented yet!\n", stderr);
	    i++;
	}
	else if(strcmp(argv[i], "-h") == 0) {
	    fputs("-h flag not implemented yet!\n", stderr);
	    return 0;
	}
	else {
	    fprintf(stderr, "'%s' unrecognized flag!!\n", argv[i]);
	    return 1;
	}
    }
    return 0;
}
#endif // SHSL_MAIN

#endif // SHSL_H
