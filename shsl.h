//// HEADER
//// ----------------------------------------------------------------------------
// SHSL: Single Header Scripting (Library|Language|Layer|Lisp)
// scripting language localized entirely within a C header file
// shsl is distributed under the GNU LGPL v2.1 (see LICENSE file for details)
// author: Alonzo Bazaar <alonzo.lo.stronzo@protonmail.com>
// (that is indeed a pseudonym)

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
// lambda list is a separate struct because lambda lists get complex rather fast
defstruct(shsl_lambda_list);
defstruct(shsl_user_fun);
// we don't have macro types as macros are just gonna be functions with different
// type tags that we run at a different moment
// (compile/expand time instead of runtime)

// we use references instead of pointers
// references hold extra information, such as, is this a weak reference?
// references are ususally allocated on the stack
defstruct(shsl_ref);

/// DATA CONSTRUCTION DECLARATIONS
// we handle everything through pointers because havnig everything
// on the heap makes it easier to automatically manage
shsl_ref shsl_mkint(long l);
shsl_ref shsl_mkreal(double d);
shsl_ref shsl_mkstr(const char* str);
shsl_ref shsl_mksym(const char* name);
shsl_ref shsl_mkerr(shsl_ref data, const char* msg, ...);
shsl_ref shsl_vmkerr(shsl_ref data, const char* msg, va_list args);
shsl_ref shsl_mkcons(shsl_ref car, shsl_ref cdr);
shsl_ref shsl_mkmap(size_t initial_capacity);
shsl_ref shsl_mkvec(size_t initial_capacity);
shsl_ref shsl_mkbuiltin_fun(shsl_ref env,
			     shsl_ref(*apply)(shsl_ref args,
					       shsl_ref env));
shsl_ref shsl_mkbuiltin_macro(shsl_ref env,
			       shsl_ref(*apply)(shsl_ref args,
                                                shsl_ref env));
// this one bit is kinda ugly
struct shsl_expr;
shsl_ref shsl_mkuser_fun(shsl_ref env, shsl_lambda_list* lambda_list,
			  struct shsl_expr** body, size_t body_len);
shsl_ref shsl_mkuser_macro(shsl_ref env, shsl_lambda_list* lambda_list,
			    struct shsl_expr** body, size_t body_len);

/// DATA OPERATIONS DECLARATIONS
/// GENERIC OPERATIONS DECLARATIONS (copy, delete, refcount shit)
// marks addition of reference to object
// also returns the modified object for convenience
shsl_ref shsl_ref_add(shsl_ref obj);
// marks removal of reference to object
// may also delete the object if reference count reaches 0 
void shsl_ref_del(shsl_ref obj);
// deletes the object and removes reference to any eventual sub-objects
// (cons car and cdr, vector elements, map keys and values, et al.)
void shsl_free(shsl_ref obj);
// creates fresh (newly allocated) deep copy of obj
// does not copy refcount tho
// fresh objects are initialized with an initial refcount of 0
shsl_ref shsl_copy(shsl_ref obj);
bool shsl_eq(shsl_ref lhs, shsl_ref rhs);
// sets *dst to src whilst handling refcounting
// (*dst is overwritten so loses a ref, src is what's written, so gains one)
void shsl_ref_set(shsl_ref* dst, shsl_ref src);

/// CONS MANIPULATIONS DECLARATIONS
void shsl_set_car(shsl_ref cons_obj, shsl_ref car);
void shsl_set_cdr(shsl_ref cons_obj, shsl_ref cdr);

/// VECTOR MANIPULATIONS DECLARATIONS
void shsl_vec_expand(shsl_ref vec_obj, size_t new_size);
void shsl_vec_push(shsl_ref vec_obj, shsl_ref obj);
shsl_ref shsl_vec_get(shsl_ref vec_obj, size_t i);
void shsl_vec_set(shsl_ref vec_obj, size_t i, shsl_ref new_val);
size_t shsl_vec_length(shsl_ref vec_obj);
// bit of shit, but this avoids polluting the body with extra symbols
// although it does introduce a bit of overhead, sorry :|
#define shsl_vec_foreach(i, elt, vec)			\
    for(size_t i = 0; i<shsl_vec_length(vec); ++i)	\
	for(shsl_ref elt = shsl_vec_get(vec, i);	\
	    elt.ptr; elt.ptr = NULL)                    \

/// MAP MANIPULATIONS DECLARATIONS
void shsl_map_expand(shsl_ref map_obj, size_t new_size);
// it's ssize_t instead of size_t so we can use -1 to say "hey, didn't find shit"
ssize_t shsl_map_index(shsl_ref map_obj, shsl_ref key);

shsl_ref shsl_map_get(shsl_ref map_obj, shsl_ref key);
void shsl_map_set(shsl_ref map_obj,
		  shsl_ref key, shsl_ref new_val);

/// COLLECTION BUILDERS DECLARATIONS
typedef enum SHSL_CB_TYPE {SHSL_CB_LIST, SHSL_CB_VEC, SHSL_CB_MAP} SHSL_CB_TYPE;
defstruct(shsl_cb);
shsl_cb shsl_cb_make(SHSL_CB_TYPE type);
void shsl_cb_add(shsl_cb* cb, shsl_ref obj);
shsl_ref shsl_cb_get(shsl_cb);

/// DATA PREDICATES DECLARATIONS
bool shsl_is_nil(const shsl_ref ref);
bool shsl_is_sym(const shsl_ref ref);
bool shsl_is_int(const shsl_ref ref);
bool shsl_is_real(const shsl_ref ref);
bool shsl_is_num(const shsl_ref ref);
bool shsl_is_err(const shsl_ref ref);
bool shsl_is_truthy(const shsl_ref ref);

bool shsl_is_cons(const shsl_ref ref);
bool shsl_is_list(const shsl_ref ref);
bool shsl_is_proper_list(const shsl_ref list_ref);
bool shsl_is_vec(const shsl_ref ref);
bool shsl_is_map(const shsl_ref ref);

/// LIST OPERATIONS DECLARATIONS
shsl_ref shsl_car(shsl_ref ref);
shsl_ref shsl_cdr(shsl_ref ref);
shsl_ref shsl_nthcdr(shsl_ref ref, size_t n);
shsl_ref shsl_nth(shsl_ref list_ref, size_t n);
// ssize_t so we can use -1 as "bro what the fuck is this object"
ssize_t shsl_list_len(shsl_ref list_ref);
char* shsl_sym_name(shsl_ref sym_ref);


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
defstruct(shsl_fn_expr);
defstruct(shsl_macro_expr);
defstruct(shsl_funcall_expr);
// tagged union of all possible expression types
// (either the ones above or like, literals and shit)
defstruct(shsl_expr);

/// FORM TRANSLATION FUNCTIONS DECLARATIONS
shsl_expr* shsl_form_to_expr(shsl_ref form);
bool shsl_expr_is_error(shsl_expr* expr);
// unrelated to form translation but still related to forms
void shsl_expr_free(shsl_expr* expr);

/// EVALUTATION FUNCTIONS DECLARATIONS
// we don't have a separate shsl_environment type as the enviroment will be
// represented using a cons list of shsl maps
// this should make for easier debuggability, even from within shsl
// and may allow for some funky pythonish introspection
shsl_ref shsl_eval(shsl_expr* form, shsl_ref env);
shsl_ref shsl_eval_many_into_vec(shsl_expr** args, size_t args_len,
				  shsl_ref env);

/// BUILTIN FUNCTIONS DECLARATIONS
// that is, definition of the functions that will be visible as builtins
// for the shsl code
/// SHSL ARITHMETIC FUNCTIONS DECLARATIONS
shsl_ref shsl_builtin_add(shsl_ref args, shsl_ref env);
shsl_ref shsl_builtin_sub(shsl_ref args, shsl_ref env);
shsl_ref shsl_builtin_mul(shsl_ref args, shsl_ref env);
shsl_ref shsl_builtin_div(shsl_ref args, shsl_ref env);

/// ENVIRONMENT FUNCTIONS DECLARATIONS
// both of these may well be global constants if c had map (and shsl list) literals
shsl_ref shsl_make_initial_env(void);
// lookup in an environment that's just a list of maps(lol)
shsl_ref shsl_env_lookup(shsl_ref env, shsl_ref key);

//// PRINT DEBUGGING DECLARATIONS
//// ----------------------------------------------------------------------------
void shsl_dbg_fputtok(const shsl_token* tok, FILE* restrict stream);
void shsl_fputobj(const shsl_ref obj, FILE* restrict stream);

//// USER FACING FUNCTIONS DECLARATIONS
//// ----------------------------------------------------------------------------
shsl_ref shsl_eval_str(char* c, shsl_ref env);

#ifdef SHSL_IMPLEMENTATION
//// DATA DEFINITIONS
//// ----------------------------------------------------------------------------

typedef struct shsl_ref {
    shsl_obj* ptr;
    bool is_weak;
} shsl_ref;

/// DATA TYPES DEFINITIONS
typedef struct shsl_sym {
    shsl_ref name; // must be string
} shsl_sym ;
typedef struct shsl_err {
    shsl_ref data; // can be any
    shsl_ref msg;  // must be string
} shsl_err;
typedef struct shsl_cons {
    shsl_ref car;
    shsl_ref cdr;
} shsl_cons ;
typedef struct shsl_vec {
    shsl_ref* buf;
    size_t size;
    size_t capacity;
} shsl_vec;
// map is currently an alist (because fuck me ig)
typedef struct shsl_kv {
    shsl_ref k;
    shsl_ref v;
} shsl_kv;
typedef struct shsl_map {
    shsl_kv* buf;
    size_t size;
    size_t capacity;
} shsl_map;
typedef struct shsl_builtin_fun {
    // env must be cons list of frames (maps)
    // args must be a vector
    shsl_ref env;
    shsl_ref(*apply)(shsl_ref args, shsl_ref env);
} shsl_builtin_fun;
typedef struct shsl_lambda_list {
    shsl_ref positional; // must be vector
    shsl_ref optional;   // map of symbol - default value
    shsl_ref keyword;    // map of symbol - default value
} shsl_lambda_list;
typedef struct shsl_user_fun {
    // env must be cons list of maps
    // lambda_list be vector
    shsl_ref env;
    shsl_lambda_list* lambda_list;
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
shsl_ref ref_to_nil() {
    return (shsl_ref) {
        .ptr = &SHSL_GLOBAL_NIL,
        .is_weak = true,
    };
}

/// DATA PREDICATES DEFINITIONS
bool shsl_is_nil(const shsl_ref ref) {
    return ref.ptr->type == SHSL_NIL;
}
bool shsl_is_sym(const shsl_ref ref) {
    return ref.ptr->type == SHSL_SYM;
}
bool shsl_is_int(const shsl_ref ref) {
    return ref.ptr->type == SHSL_INT;
}
bool shsl_is_real(const shsl_ref ref) {
    return ref.ptr->type == SHSL_REAL;
}
bool shsl_is_num(const shsl_ref ref) {
    return shsl_is_int(ref) || shsl_is_real(ref);
}
bool shsl_is_err(const shsl_ref ref) {
    return ref.ptr->type == SHSL_ERR;
}
bool shsl_is_truthy(const shsl_ref ref) {
    return !(shsl_is_nil(ref) || shsl_is_err(ref));
}

bool shsl_is_cons(const shsl_ref ref) {
    return ref.ptr->type == SHSL_CONS;
}
bool shsl_is_list(const shsl_ref ref) {
    return shsl_is_nil(ref) || shsl_is_cons(ref);
}
// TODO: infinite loops on circular lists
// I'm already refcounting so I have accepted those will be a pita
// maybe have a tortoise and hare function that detects circular lists
// bool is_circular_list(const shsl_obj* list_obj)
bool shsl_is_proper_list(const shsl_ref list_ref) {
    shsl_obj* list_obj = list_ref.ptr;
    while(true) {
	switch(list_obj->type) {
	case SHSL_NIL:
	    return true;
	case SHSL_CONS:
	    list_obj = list_obj->cons.cdr.ptr;
	    break;
	default:
	    return false;
	}
    }
}
bool shsl_is_vec(const shsl_ref ref) {
    return ref.ptr->type == SHSL_VEC;
}
bool shsl_is_map(const shsl_ref ref) {
    return ref.ptr->type == SHSL_MAP;
}

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
#define return_mallocd_obj(...) do {                    \
    shsl_ref ref = (shsl_ref){                          \
        .ptr = (shsl_obj*)malloc(sizeof(shsl_obj)),     \
        .is_weak = false,                               \
    };                                                  \
    *(ref.ptr) = (shsl_obj){__VA_ARGS__};               \
    return ref;                                         \
    } while(0)

shsl_ref shsl_ref_from_ptr(shsl_obj* ptr) {
    return (shsl_ref){
        .ptr = ptr,
        .is_weak = false,
    };
}
shsl_ref shsl_weak_ref_from_ptr(shsl_obj* ptr) {
    return (shsl_ref){
        .ptr = ptr,
        .is_weak = true,
    };
}
shsl_ref shsl_ref_add(shsl_ref ref) {
    if(ref.is_weak) {
#ifdef SHSL_LOG_ADD_REF
        printf("[SHSL GC] not adding ref to object %p\n", (void*)(ref.ptr));
        printf("[SHSL GC] "); shsl_fputobj(ref, stdout);
        printf("[SHSL GC] because ref is weak\n");
        printf("[SHSL GC] remains at refcount %d\n", ref.ptr->ref_count);
        putc('\n');
#endif
        return ref;
    }

#ifdef SHSL_LOG_ADD_REF
    printf("[SHSL GC] adding ref to object %p\n", (void*)(ref.ptr));
    printf("[SHSL GC] "); shsl_fputobj(ref, stdout);
    printf("[SHSL GC] was at refcount %d\n", ref.ptr->ref_count);
    putc('\n');
#endif

    if(ref.ptr->type != SHSL_NIL)
	ref.ptr->ref_count++;
    return ref;
}
void shsl_ref_del(shsl_ref ref) {
    if(ref.is_weak) {
#ifdef SHSL_LOG_DEL_REF
        printf("[SHSL GC] not deleting ref to object %p\n", (void*)(ref.ptr));
        printf("[SHSL GC] "); shsl_fputobj(ref, stdout);
        printf("[SHSL GC] because ref is weak\n");
        printf("[SHSL GC] remains at refcount %d\n", ref.ptr->ref_count);
        putc('\n');
#endif
        return;
    }

#ifdef SHSL_LOG_DEL_REF
    fprintf(stdout, "[SHSL GC] deleting ref to object %p\n", (void*)(ref.ptr));
    fprintf(stdout, "[SHSL GC] "); shsl_fputobj(ref, stdout);
    fprintf(stdout, "[SHSL GC] was at refcount %d\n", ref.ptr->ref_count);
#endif    
    if(ref.ptr->type == SHSL_NIL)
	return;

    ref.ptr->ref_count--;
    if(ref.ptr->ref_count == 0)
	shsl_free(ref);
    else if(ref.ptr->ref_count < 0)
	// *else if*, not if
	// having just if here is reading (potentially) freed data
	// and that's no good
	fprintf(stderr, "now you fucked up!\n");
}
void shsl_ref_mark_weak(shsl_ref ref) {
    if(!ref.is_weak) {
        shsl_ref_del(ref);
        ref.is_weak = true;
    }
}

void shsl_free(shsl_ref ref) {
#ifdef SHSL_LOG_GC
    fprintf(stdout, "[SHSL GC] freeing object %p\n", (void*)(ref.ptr));
    shsl_fputobj(ref, stdout);
    fputc('\n', stdout);
#endif
    switch(ref.ptr->type) {
    case SHSL_NIL:
	fprintf(stderr, "cannot free NIL! You fucked something up!\n");
	break;

    case SHSL_STRING:
	free(ref.ptr->str);
	free(ref.ptr);
	break;

    case SHSL_SYM:
	shsl_ref_del(ref.ptr->sym.name);
	free(ref.ptr);
	break;

    case SHSL_ERR:
	shsl_ref_del(ref.ptr->err.msg);
	shsl_ref_del(ref.ptr->err.data);
	free(ref.ptr);
	break;
    case SHSL_CONS:
	shsl_ref_del(ref.ptr->cons.car);
	shsl_ref_del(ref.ptr->cons.cdr);
	free(ref.ptr);
	break;
    case SHSL_VEC:
	for(size_t i = 0; i<ref.ptr->vec.size; ++i)
	    shsl_ref_del(ref.ptr->vec.buf[i]);
	free(ref.ptr->vec.buf);
	free(ref.ptr);
	break;
    case SHSL_MAP:
	for(size_t i = 0; i<ref.ptr->map.size; ++i) {
	    shsl_ref_del(ref.ptr->map.buf[i].k);
	    shsl_ref_del(ref.ptr->map.buf[i].v);
	}
	free(ref.ptr->map.buf);
	free(ref.ptr);
	break;

    case SHSL_BUILTIN_FUN:
	shsl_ref_del(ref.ptr->builtin_fun.env);
	free(ref.ptr);
	break;
    case SHSL_USER_FUN:
	shsl_ref_del(ref.ptr->user_fun.env);
        shsl_ref_del(ref.ptr->user_fun.lambda_list->positional);
        shsl_ref_del(ref.ptr->user_fun.lambda_list->optional);
        shsl_ref_del(ref.ptr->user_fun.lambda_list->keyword);
	for(size_t i = 0; i<ref.ptr->user_fun.body_len; ++i)
	    shsl_expr_free(ref.ptr->user_fun.body[i]);
	free(ref.ptr);
	break;
    case SHSL_BUILTIN_MACRO:
	shsl_ref_del(ref.ptr->builtin_macro.env);
	free(ref.ptr);
	break;
    case SHSL_USER_MACRO:
	shsl_ref_del(ref.ptr->user_macro.env);
        shsl_ref_del(ref.ptr->user_macro.lambda_list->positional);
        shsl_ref_del(ref.ptr->user_macro.lambda_list->optional);
        shsl_ref_del(ref.ptr->user_macro.lambda_list->keyword);
	for(size_t i = 0; i<ref.ptr->user_macro.body_len; ++i)
	    shsl_expr_free(ref.ptr->user_macro.body[i]);
	free(ref.ptr);
	break;

    default:
	free(ref.ptr);
	break;
    }

#ifdef SHSL_LOG_GC
    fprintf(stdout, "[SHSL GC] freed object %p\n", (void*)(ref.ptr));
#endif    
}
// dst = src
// dst loses a ref
// src gains a ref
// only use when overwriting an old value, do not use for initializatin code 
void shsl_ref_set(shsl_ref* dst, shsl_ref src) {
    shsl_ref_add(src);
    shsl_ref_del(*dst);
    dst->ptr = src.ptr;
}

shsl_ref shsl_mkint(long l) {
    return_mallocd_obj(.ref_count = 0, .type = SHSL_INT, .i = l);
}
shsl_ref shsl_mkreal(double d) {
    return_mallocd_obj(.ref_count = 0, .type = SHSL_REAL, .r = d);
}
shsl_ref shsl_mkstr(const char* str) {
    size_t len = strlen(str);
    char* c = calloc(len+1, sizeof(char));
    strcpy(c, str);
    return_mallocd_obj(.ref_count = 0, .type = SHSL_STRING, .str = c);
}
shsl_ref shsl_mksym(const char* name) {
    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_SYM,
		       .sym = (shsl_sym){
			   .name = shsl_ref_add(shsl_mkstr(name)),
		       });
}

#define SHSL_ERR_MAX_LENGTH 1024
shsl_ref shsl_vmkerr(shsl_ref data, const char* msg, va_list args) {
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
			   .msg = shsl_ref_add(shsl_mkstr(buf)),
			   .data = shsl_ref_add(data),
		       });
}
shsl_ref shsl_mkerr(shsl_ref data, const char* msg, ...) {
    va_list args;
    va_start(args, msg);
    shsl_ref err = shsl_vmkerr(data, msg, args);
    va_end(args);
    return err;
}

shsl_ref shsl_mkcons(shsl_ref car, shsl_ref cdr) {
    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_CONS,
		       .cons = (shsl_cons) { .car = shsl_ref_add(car),
					     .cdr = shsl_ref_add(cdr), }
		      );
}
shsl_ref shsl_mkvec(size_t initial_capacity) {
    assert(initial_capacity > 0);

    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_VEC,
		       .vec = (shsl_vec) {
			   .buf = calloc(initial_capacity, sizeof(shsl_ref)),
			   .size = 0,
			   .capacity = initial_capacity,
		       },
		      );
}
shsl_ref shsl_mkmap(size_t initial_capacity) {
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
shsl_ref shsl_mkbuiltin_fun(shsl_ref env,
			     shsl_ref(*apply)(shsl_ref args,
					       shsl_ref env)) {
    assert(shsl_is_nil(env)
	   || (shsl_is_cons(env) && shsl_is_map(env.ptr->cons.car))
	   && "if function env is not null it must be a list of maps!");


    // TODO: oooh baby, shit just got circular functions hold a ref to an
    // environment, which hold a ref to an environment frame, which holds
    // a ref to an environment
    // 
    // well, if you define a functions in an env then pass that same env to
    // the function, which is what one usually does when defining functions tbh
    // 
    // NOTE: could we make function references to their environment be
    // weak references instead?
    // NOTE: I tried and it segfaulted :(
    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_BUILTIN_FUN,
		       .builtin_fun = (shsl_builtin_fun) {
			   .env = shsl_ref_add(env),
			   .apply = apply,
		       }
		      );
}
shsl_ref shsl_mkbuiltin_macro(shsl_ref env,
                              shsl_ref(*expand)(shsl_ref args,
						  shsl_ref env)) {
    assert(shsl_is_nil(env)
	   || (shsl_is_cons(env) && shsl_is_map(env.ptr->cons.car))
	   && "if macro env is not null it must be a list of maps!");

    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_BUILTIN_MACRO,
		       .builtin_macro = (shsl_builtin_fun) {
			   .env = shsl_ref_add(env),
			   .apply = expand,
		       }
		      );
}
shsl_ref shsl_mkuser_fun(shsl_ref env, shsl_lambda_list* lambda_list,
			  struct shsl_expr** body, size_t body_len) {
    assert(shsl_is_nil(env)
	   || (shsl_is_cons(env) && shsl_is_map(env.ptr->cons.car))
	   && "if function env is not null it must be a list of maps!");
    assert(body && "function body cannot be null pointer!");
    assert(body_len > 0 && "function body length cannot be zero!");

    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_USER_FUN,
		       .user_fun = (shsl_user_fun) {
			   .env = shsl_ref_add(env),
			   .lambda_list = lambda_list,
			   .body = body,
			   .body_len = body_len,
		       }
		      );
}
shsl_ref shsl_mkuser_macro(shsl_ref env, shsl_lambda_list* lambda_list,
			    struct shsl_expr** body, size_t body_len) {
    assert(shsl_is_nil(env)
	   || (shsl_is_cons(env) && shsl_is_map(env.ptr->cons.car))
	   && "if function env is not null it must be a list of maps!");
    assert(body && "macro body cannot be null pointer!");
    assert(body_len > 0 && "macro body length cannot be zero!");

    return_mallocd_obj(.ref_count = 0,
		       .type = SHSL_USER_MACRO,
		       .user_macro = (shsl_user_fun) {
			   .env = shsl_ref_add(env),
			   .lambda_list = lambda_list,
			   .body = body,
			   .body_len = body_len,
		       }
		      );
}

/// DATA OPERATIONS DEFINITIONS
/// GENERIC OPERATIONS DEFINITIONS

// all C string are copied by shsl_mk* constructors so there is no need to copy them
// in this function, the constructors will do their thing for copying the data
shsl_ref shsl_copy(shsl_ref ref) {
    switch(ref.ptr->type) {
    case SHSL_NIL:    return ref_to_nil();
    case SHSL_SYM:    return shsl_mksym(ref.ptr->sym.name.ptr->str);
    case SHSL_INT:    return shsl_mkint(ref.ptr->i);
    case SHSL_REAL:   return shsl_mkint(ref.ptr->r);
    case SHSL_STRING: return shsl_mkstr(ref.ptr->str);

    case SHSL_ERR:    return shsl_mkerr(shsl_copy(ref.ptr->err.data),
						  ref.ptr->err.msg.ptr->str);

    case SHSL_CONS:   return shsl_mkcons(shsl_copy(ref.ptr->cons.car),
                                         shsl_copy(ref.ptr->cons.cdr));
						      
    case SHSL_VEC: {
	shsl_ref copy = shsl_mkvec(ref.ptr->vec.size);
	shsl_vec_foreach(i, elt, ref)
	    shsl_vec_push(copy, shsl_copy(elt));
	return copy;
    }
    case SHSL_MAP: {
	shsl_ref copy = shsl_mkmap(ref.ptr->map.size);
	for(size_t i = 0; i<ref.ptr->map.size; ++i) {
	    shsl_map_set(copy,
			 shsl_copy(ref.ptr->map.buf[i].k),
			 shsl_copy(ref.ptr->map.buf[i].v));
	}
	return copy;
    }

    case SHSL_BUILTIN_FUN:
    case SHSL_USER_FUN:
    case SHSL_BUILTIN_MACRO:
    case SHSL_USER_MACRO:
	fprintf(stderr,
                "[SHSL WARNING] function object not copyable!\n");
	return ref_to_nil();
    }
    assert(0 && "unreachable");
}
bool shsl_eq(shsl_ref lhs_ref, shsl_ref rhs_ref) {
    const shsl_obj* const lhs = lhs_ref.ptr;
    const shsl_obj* const rhs = rhs_ref.ptr;

    if(lhs->type != rhs->type)
	return false;
	
    switch(lhs->type) {
    case SHSL_NIL:
	return true;
    case SHSL_SYM:
	return strcmp(lhs->sym.name.ptr->str, rhs->sym.name.ptr->str) == 0;
    case SHSL_ERR:
	return strcmp(lhs->err.msg.ptr->str, rhs->err.msg.ptr->str) == 0
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
	    if(!shsl_eq(shsl_map_get(lhs_ref, lhs->map.buf[i].k),
			shsl_map_get(rhs_ref, lhs->map.buf[i].k)))
		return false;
	return true;
    case SHSL_BUILTIN_FUN:
    case SHSL_USER_FUN:
    case SHSL_BUILTIN_MACRO:
    case SHSL_USER_MACRO:
	fprintf(stderr, "TODO: this comparison's not implemeneted yet!\n");
	return false;
    }
    assert(0 && "unreachable");
}


/// CONS MANIPULATIONS DEFINITIONS
void shsl_set_car(shsl_ref cons_ref, shsl_ref new_car) {
    assert(cons_ref.ptr->type == SHSL_CONS);
    shsl_ref_set(&(cons_ref.ptr->cons.car), new_car);
}
void shsl_set_cdr(shsl_ref cons_ref, shsl_ref new_cdr) {
    assert(cons_ref.ptr->type == SHSL_CONS);
    shsl_ref_set(&(cons_ref.ptr->cons.cdr), new_cdr);
}

/// VECTOR MANIPULATIONS DEFINITIONS
void shsl_vec_expand(shsl_ref vec_ref, size_t new_size) {
    assert(vec_ref.ptr->type == SHSL_VEC);

    if(vec_ref.ptr->vec.capacity >= new_size) return;
    vec_ref.ptr->vec.buf = reallocarray
        (vec_ref.ptr->vec.buf, new_size, sizeof(shsl_ref));
    vec_ref.ptr->vec.capacity = new_size;
}
void shsl_vec_push(shsl_ref vec_ref, shsl_ref obj) {
    assert(vec_ref.ptr->type == SHSL_VEC);

    if(vec_ref.ptr->vec.size == vec_ref.ptr->vec.capacity)
	shsl_vec_expand(vec_ref,
			vec_ref.ptr->vec.capacity
			+ (vec_ref.ptr->vec.capacity/2)
			+ 1);
    // append
    shsl_ref_add(obj);
    vec_ref.ptr->vec.buf[vec_ref.ptr->vec.size] = obj;
    vec_ref.ptr->vec.size++;
}
shsl_ref shsl_vec_get(shsl_ref vec_ref, size_t i) {
    assert(vec_ref.ptr->type == SHSL_VEC);

    if(i >= vec_ref.ptr->vec.size)
	return shsl_mkerr(ref_to_nil(), "out of bounds array read!");
    return vec_ref.ptr->vec.buf[i];
}
void shsl_vec_set(shsl_ref vec_ref, size_t i, shsl_ref new_val) {
    assert(vec_ref.ptr->type == SHSL_VEC);

    // TODO: gestione degli errori un po' di più magari
    if(i >= vec_ref.ptr->vec.size)
	fprintf(stderr, "out of bounds array write!\n");

    shsl_ref_set(&vec_ref.ptr->vec.buf[i], new_val);
}
size_t shsl_vec_length(shsl_ref vec_ref) {
    assert(vec_ref.ptr->type == SHSL_VEC);
    return vec_ref.ptr->vec.size;
}

/// MAP MANIPULATIONS DEFINITIONS
void shsl_map_expand(shsl_ref map_ref, size_t new_size) {
    assert(map_ref.ptr->type == SHSL_MAP);

    if (map_ref.ptr->map.capacity >= new_size) return;
    map_ref.ptr->map.buf = reallocarray
        (map_ref.ptr->map.buf, new_size, sizeof(shsl_kv));
    map_ref.ptr->map.capacity = new_size;
}
ssize_t shsl_map_index(shsl_ref map_ref, shsl_ref key) {
    assert(map_ref.ptr->type == SHSL_MAP);

    for(size_t i = 0; i<map_ref.ptr->map.size; ++i)
	if(shsl_eq(key, map_ref.ptr->map.buf[i].k))
	    return (ssize_t)i;
    return -1;
}
shsl_ref shsl_map_get(shsl_ref map_ref, shsl_ref key) {
    assert(map_ref.ptr->type == SHSL_MAP);

    ssize_t i = shsl_map_index(map_ref, key);
    if(i>=0) return map_ref.ptr->map.buf[i].v;
    return ref_to_nil();
}
void shsl_map_set(shsl_ref map_ref, shsl_ref key, shsl_ref new_val) {
    assert(map_ref.ptr->type == SHSL_MAP);

    ssize_t i = shsl_map_index(map_ref, key);
    if(i>=0) {
        shsl_ref_set(&(map_ref.ptr->map.buf[i].v), new_val);
    }
    else {
	if(map_ref.ptr->map.size == map_ref.ptr->map.capacity)
	    shsl_map_expand(map_ref,
			    map_ref.ptr->vec.capacity
			    + (map_ref.ptr->vec.capacity/2)
			    + 1);
	shsl_ref_add(key);
	shsl_ref_add(new_val);
	map_ref.ptr->map.buf[map_ref.ptr->map.size] = (shsl_kv) {
	    .k = key,
	    .v = new_val,
	};
	map_ref.ptr->map.size++;
    }
}

/// COLLECTION BUILDERS DEFINITIONS
typedef struct shsl_cb {
    SHSL_CB_TYPE type;
    union {
        struct {
            shsl_ref first; shsl_ref last;
        } cons_builder;
        struct {
            shsl_ref vec;
        } vec_builder;
        struct {
            shsl_ref map; shsl_ref curr_key; bool reading_key;
        } map_builder;
    };
} shsl_cb;
shsl_cb shsl_cb_make(SHSL_CB_TYPE type) {
    switch(type) {
    case SHSL_CB_LIST:
	return (shsl_cb) {
	    .type = SHSL_CB_LIST,
	    .cons_builder.first = ref_to_nil(),
	    .cons_builder.last = ref_to_nil(),
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
	    .map_builder.curr_key = ref_to_nil(),
	};
    }
    assert(0 && "unreachable");
}
void shsl_cb_add(shsl_cb* cb, shsl_ref ref) {
    switch(cb->type) {
    case SHSL_CB_LIST: 
	if(shsl_is_nil(cb->cons_builder.first)) {
	    cb->cons_builder.first = shsl_mkcons(ref, ref_to_nil());
	    cb->cons_builder.last = cb->cons_builder.first;
	}
	else { 
	    shsl_set_cdr
		(cb->cons_builder.last,
		 shsl_mkcons(ref, ref_to_nil()));
	    cb->cons_builder.last.ptr = cb->cons_builder.last.ptr->cons.cdr.ptr;
	}
	break;
    case SHSL_CB_VEC: 
	shsl_vec_push(cb->vec_builder.vec, ref);
	break;
    case SHSL_CB_MAP: 
	if(cb->map_builder.reading_key) {
	    cb->map_builder.curr_key = ref;
	    cb->map_builder.reading_key = false;
	}
	else {
	    shsl_map_set
		(cb->map_builder.map,
		 cb->map_builder.curr_key,
		 ref);
	    cb->map_builder.reading_key = true;
	}
    }
}
shsl_ref shsl_cb_get(shsl_cb cb) {
    switch (cb.type) {
    case SHSL_CB_LIST:
	return cb.cons_builder.first;
    case SHSL_CB_VEC:
	return cb.vec_builder.vec;
    case SHSL_CB_MAP:
	if(cb.map_builder.reading_key)
	    return cb.map_builder.map;
	else
	    return shsl_mkerr
		(cb.map_builder.map,
		 "tried building map with with odd number of elements!");
    }
    assert(0 && "unreachable");
}

/// LIST OPERATIONS DEFINITIONS
shsl_ref shsl_car(shsl_ref ref) {
    switch(ref.ptr->type) {
    case SHSL_NIL:
	return ref_to_nil();
    case SHSL_CONS:
	return ref.ptr->cons.car;
    default:
	return shsl_mkerr(ref, "CAR: cannot get car as object is not a list");
    }
}
shsl_ref shsl_cdr(shsl_ref ref) {
    switch(ref.ptr->type) {
    case SHSL_NIL:
	return ref_to_nil();
    case SHSL_CONS:
	return ref.ptr->cons.cdr;
    default:
	return shsl_mkerr(ref, "CDR: cannot get car as object is not a list");
    }
}
shsl_ref shsl_nthcdr(shsl_ref ref, size_t n) {
    while(n-- && !shsl_is_err(ref))
	ref = shsl_cdr(ref);
    if(shsl_is_err(ref))
	return shsl_mkerr(ref, "NTHCDR: cannot get nthcdr of list :(");
    return ref;
}
shsl_ref shsl_nth(shsl_ref list_ref, size_t n) {
    shsl_ref nth = shsl_car(shsl_nthcdr(list_ref, n));
    if(shsl_is_err(nth))
	return shsl_mkerr(nth, "NTH: can't get nth element of object");
    return nth;
}
ssize_t shsl_list_length(shsl_ref list_ref) {
    for(ssize_t i = 0; ; ++i) {
	switch(list_ref.ptr->type) {
	case SHSL_NIL:
	    return i;
	case SHSL_CONS:
	    list_ref = list_ref.ptr->cons.cdr;
	    break;
	default:
	    return -1;
	}
    }
}
char* shsl_sym_name(shsl_ref sym_ref) {
    return sym_ref.ptr->sym.name.ptr->str;
}

//// LEXER DEFINITIONS
//// ----------------------------------------------------------------------------
typedef struct shsl_token {
    SHSL_TOKEN_TYPE type;
    shsl_ref ref;
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

// for a lot of token types (parens, quotes, et al) we only need to know the type
// of the token and don't really need the object the token carries,
// return a token with that type and no underlying object that we care about
shsl_token empty_token(SHSL_TOKEN_TYPE token_type) {
    return (shsl_token) {
	.type = token_type,
	.ref = ref_to_nil(),
    };
}
// since we return errors as special token pairs, might as well have an
// ad hoc function for that
lexer_pair error_lexer_pair(const char* errmsg) {
    return (lexer_pair) {
	.token = (shsl_token) {
	    .type = SHSL_TOK_ERROR,
	    .ref = shsl_mkerr(ref_to_nil(), "[SHSL LEXER] ERROR: %s", errmsg),
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
// parse a non special token starting at c
// a non special token is a token not made of/delimited by special chars
// can be either symbol or a number
// if from c onwards is a valid integer, returns an integer token
// otherwise same with floats
// TODO: parsing floats
// otherwise returns a symbol, if the symbol is nil it returns a nil token
shsl_token parse_non_special_token(char*c, size_t len) {
    long l;
    if (try_parse_integer(c, len, &l))
	return (shsl_token) {
	    .type = SHSL_TOK_INTEGER,
	    .ref = shsl_mkint(l),
	};

    if (len == 3 && c[0] == 'n' && c[1] == 'i' && c[2] == 'l')
	return (shsl_token) {
	    .type = SHSL_TOK_NIL,
	    .ref = ref_to_nil(),
	};
	
    char* newstr = slice_to_fresh_str(c, len);
    shsl_token t =  (shsl_token) {
	.type = SHSL_TOK_SYMBOL,
	.ref = shsl_mksym(newstr),
    };
    // shsl_mksym already copies the string we pass to it
    // so we don't need this one after the symbol is made
    free(newstr);
    return t;
}

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
		    .ref = shsl_mkstr(s),
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

//// PARSER DEFINITIONS
//// ----------------------------------------------------------------------------

// same logic as lexer_pair
// TODO: update into parser state?
typedef struct parser_pair {
    shsl_ref ref;
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
	    .ref = lp.token.ref,
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
	    .ref = shsl_mkcons(shsl_mksym("quote"),
			       shsl_mkcons(pp.ref, ref_to_nil())),
	    .remaining = pp.remaining,
	};
    }
    case  SHSL_TOK_QUASIQUOTE: {
	parser_pair pp = parse_off(lp.remaining);
	return (parser_pair) {
	    .ref = shsl_mkcons(shsl_mksym("quasiquote"),
			       shsl_mkcons(pp.ref, ref_to_nil())),
	    .remaining = pp.remaining,
	};
    }
    case  SHSL_TOK_COMMA: {
	parser_pair pp = parse_off(lp.remaining);
	return (parser_pair) {
	    .ref = shsl_mkcons(shsl_mksym("comma"),
			       shsl_mkcons(pp.ref, ref_to_nil())),
	    .remaining = pp.remaining,
	};
    }

	// TODO: better error/finish return
    case SHSL_TOK_CLOSE_PAREN:
	return (parser_pair) {
	    .ref = shsl_mkerr (ref_to_nil(),
			       "[SHSL PARSER] ERROR: "
			       "unmatched close parentheses!"),
	    .remaining = NULL,
	};
    case SHSL_TOK_CLOSE_SQUARE:
	return (parser_pair) {
	    .ref = shsl_mkerr (ref_to_nil(),
			       "[SHSL PARSER] ERROR: "
			       "unmatched close square bracket!"),
	    .remaining = NULL,
	};
    case SHSL_TOK_CLOSE_CURLY:
	return (parser_pair) {
	    .ref = shsl_mkerr (ref_to_nil(),
			       "[SHSL PARSER] ERROR: "
			       "unmatched close curly bracket!"),
	    .remaining = NULL,
	};
    case SHSL_TOK_ERROR:
	return (parser_pair) {
	    .ref = shsl_mkerr (lp.token.ref,
			       "[SHSL PARSER] ERROR: "
			       "cannot proceed further, received error "
			       "from lexer!"),
	    .remaining = NULL,
	};

    case SHSL_TOK_EOF:
	return (parser_pair){0};
    }
    assert(0 && "unreachable");
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
		.ref = shsl_cb_get(cb),
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
	shsl_cb_add(&cb, pp.ref);
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
    shsl_expr** body;
    size_t body_length;
} shsl_do_expr;
typedef struct shsl_do_poking_expr {
    shsl_expr** body;
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
typedef struct shsl_fn_expr {
    shsl_lambda_list* lambda_list;
    shsl_expr** body;
    size_t body_length;
} shsl_fn_expr;
typedef struct shsl_macro_expr {
    shsl_lambda_list* lambda_list;
    shsl_expr** body;
    shsl_expr** body_length;
} shsl_macro_expr;

typedef struct shsl_funcall_expr {
    shsl_expr* fun_expr;
    shsl_expr** args;
    size_t args_length;
} shsl_funcall_expr;
typedef struct shsl_expr {
    SHSL_EXPR_TYPE type;
    union {
	shsl_ref literal;
	shsl_ref lookup_symbol; // must be symbol

	shsl_vec_expr vec_expr;
	shsl_map_expr map_expr;

	shsl_if_expr if_expr;
	shsl_do_expr do_expr;
	shsl_do_poking_expr do_poking_expr;
	shsl_def_expr def_expr;
	set_expr set_expr;

        shsl_fn_expr fn_expr;
        shsl_macro_expr macro_expr;

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

// this is how we represent parsing errors
bool shsl_expr_is_error(shsl_expr* expr) {
    return expr->type == SHSL_EXPR_LITERAL
	&& expr->literal.ptr->type == SHSL_ERR;
}
// this is how we return parsing errors
shsl_expr* shsl_vexpr_error(shsl_ref form, const char* msg, va_list args) {
    shsl_ref err = shsl_vmkerr(form, msg, args);
#ifdef SHSL_LOG_ERROR_EXPR
    fprintf(stderr, "[SHSL PARSER ERROR] %s\n", err->msg);
    fprintf(stderr, "[SHSL PARSER ERROR] with data: ");
    shsl_fputobj(form, stderr); fputc('\n', stderr)
#endif
    return_mallocd_expr(.type = SHSL_EXPR_LITERAL,
			.literal = err);
}
shsl_expr* shsl_expr_error(shsl_ref form, const char* msg, ...) {
    va_list args;
    va_start(args, msg);
    shsl_expr* err_expr = shsl_vexpr_error(form, msg, args);
    va_end(args);

    return err_expr;
}
// this is how we propagate errors
// (return an error with a reference to the error that caused it)
shsl_expr* shsl_expr_further_error(shsl_expr* orig, const char* msg, ...) {
    assert(shsl_expr_is_error(orig));
    va_list args;
    va_start(args, msg);
    shsl_ref err = shsl_vmkerr(orig->literal, msg, args);
    va_end(args);
    return_mallocd_expr(.type = SHSL_EXPR_LITERAL,
			.literal = err);
}

/// parsing utilities
shsl_expr** shsl_form_list_to_expr_arr(shsl_ref form) {
    // returns an array of forms parsed starting from form onwards until nil
    // ie: parses the whole subtree starting at form
    // if it encounters an error form while parsing it adds it to the array and
    // stops at the error, so you can grab the error then free everything that came
    // before the error

    // other than error handling basically acts as
    // (map 'vector #'form-to-expr form)
    assert(shsl_is_list(form));
    size_t len = shsl_list_length(form);
    shsl_expr** res = calloc(len, sizeof(shsl_expr*));
    for(size_t i = 0; i<len; ++i) {
	res[i] = shsl_form_to_expr(shsl_nth(form, i));
    }
    return res;
}
ssize_t shsl_expr_arr_find_err(shsl_expr** arr, size_t len) {
    // returns index of first element in arr that is an error
    // if no error is found returns -1
    for(size_t i = 0; i<len; ++i) {
	if(shsl_expr_is_error(arr[i])) return (ssize_t)i;
    }
    return -1;
}
void shsl_free_expr_arr(shsl_expr** arr, size_t len) {
    // frees every expression in from arr to arr+len, then frees arr
    for(size_t i = 0; i<len; ++i) {
	shsl_expr_free(arr[i]);
    }
    free(arr);
}

/// FORM TRANSLATION FUNCTIONS DEFINITIONS
shsl_expr* shsl_form_to_expr(shsl_ref form) {
    switch(form.ptr->type) {
    case SHSL_INT:
    case SHSL_REAL:
    case SHSL_STRING:
    case SHSL_NIL:
	return_mallocd_expr(.type = SHSL_EXPR_LITERAL,
			    .literal = shsl_ref_add(form));

    case SHSL_SYM:
	return_mallocd_expr(.type = SHSL_EXPR_LOOKUP,
			    .lookup_symbol = shsl_ref_add(form));

    case SHSL_VEC: {
	shsl_expr** elt_exprs = calloc(shsl_vec_length(form), sizeof(shsl_expr*));

	// can't use shsl_form_list_to_expr_arr as vector forms aren't lists
	shsl_vec_foreach(i, form_elt, form) {
	    shsl_expr* next = shsl_form_to_expr(form_elt);
	    if(!shsl_expr_is_error(next)) {
		elt_exprs[i] = next;
	    }
	    else {
		for(size_t j = 0; j<i; ++j)
		    shsl_expr_free(elt_exprs[j]);
		free(elt_exprs);
		return shsl_expr_error(form,
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
	shsl_expr** key_exprs = calloc(form.ptr->map.size, sizeof(shsl_expr*));
	shsl_expr** val_exprs = calloc(form.ptr->map.size, sizeof(shsl_expr*));

	for(size_t i = 0; i<form.ptr->map.size; ++i) {
	    shsl_expr* next_key = shsl_form_to_expr(form.ptr->map.buf[i].k);
	    shsl_expr* next_val = shsl_form_to_expr(form.ptr->map.buf[i].v);

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
		    return shsl_expr_error
			(next_key->literal,
			 "cannot parse map literal because key at position "
			 "%zu of literal was malformed!", (size_t)i);
		else
		    return shsl_expr_error
			(next_val->literal,
			 "cannot parse map literal because value at position "
			 "%zu of literal was malformed!", (size_t)i);
	    }
	}

	return_mallocd_expr(.type = SHSL_EXPR_MAP,
			    .map_expr = (shsl_map_expr) {
				.keys = key_exprs,
				.vals = val_exprs,
				.size = form.ptr->map.size,
			    });
    }

    case SHSL_ERR:
	return shsl_expr_error
            (form, "an error object was passed to the parser");

    case SHSL_CONS: {
	if(!shsl_is_proper_list(form))
	    return shsl_expr_error
		(form, "not well formed list, cannot parse into expression");

	size_t form_length = (size_t)shsl_list_length(form);

	if(form.ptr->cons.car.ptr->type == SHSL_SYM) {
	    char* s = shsl_sym_name(shsl_car(form));
	    if(strcmp(s, "quote") == 0) {
		if(form_length != 2)
		    return
			shsl_expr_error
			(form,
                         "malformed quote form, length of quote form must be "
			 "exactly 2, just the 'quote symbol and the quoted "
			 "datum");
		shsl_ref literal = shsl_nth(form, 1);
		if(shsl_is_err(literal))
		    return shsl_expr_error
                        (literal,
                         "cannot parse quote expression because"
                         "literal in quote was malformed");
		return_mallocd_expr(.type = SHSL_EXPR_LITERAL,
				    .literal = shsl_ref_add(literal)); 
	    }

	    else if(strcmp(s, "if") == 0) {
		if(form_length < 3)
		    return shsl_expr_error
			(form, "malformed if expression, too short");
		if(form_length > 4)
		    return shsl_expr_error
			(form, "malformed if expression, too long");
				
		shsl_expr** body = shsl_form_list_to_expr_arr(shsl_cdr(form));
		ssize_t  err_ind = shsl_expr_arr_find_err(body, form_length-1);
		if(err_ind != -1) {
		    // get error
		    shsl_expr* err_expr = body[err_ind];
		    // free everything we allocated that was not the error
		    shsl_free_expr_arr(body, err_ind);
		    // return propagated error to caller
		    switch(err_ind) {
		    case 0:
			return shsl_expr_further_error
			    (err_expr,
			     "cannot parse if expression, malfomed condition!");
		    case 1:
			return shsl_expr_further_error
			    (err_expr,
			     "cannot parse if expression, malfomed then part!");
		    case 2:
			return shsl_expr_further_error
			    (err_expr,
			     "cannot parse if expression, malfomed else part!");
		    default:
			assert(0 && "unreachable");
		    }
		}

		shsl_expr* c = body[0];
		shsl_expr* t = body[1];
		shsl_expr* e = body[2];
		free(body);

		return_mallocd_expr(.type = SHSL_EXPR_IF,
				    .if_expr = (shsl_if_expr) {
					.condition = c,
					.then_part = t,
					.else_part = e
				    });
	    }
	    
	    else if(strcmp(s, "do") == 0) {
		shsl_expr** body = shsl_form_list_to_expr_arr(shsl_cdr(form));
		ssize_t  err_ind = shsl_expr_arr_find_err(body, form_length-1);
		if(err_ind != -1) {
		    shsl_expr* err_expr = body[err_ind];
		    shsl_free_expr_arr(body, err_ind);
		    err_ind++; // use 1 based indexing for the error reporting 
		    return shsl_expr_further_error
			(err_expr,
			 "cannot parse do expression because expression at "
			 "position %zu in body was malformed", (size_t)err_ind);
		}
		return_mallocd_expr(.type = SHSL_EXPR_DO,
				    .do_expr = (shsl_do_expr) {
					.body = body,
					.body_length = (form_length-1),
				    });
	    }
	    else if(strcmp(s, "do-poking") == 0) {
		shsl_expr** body = shsl_form_list_to_expr_arr(shsl_cdr(form));
		ssize_t  err_ind = shsl_expr_arr_find_err(body, form_length-1);
		if(err_ind != -1) {
		    shsl_expr* err_expr = body[err_ind];
		    shsl_free_expr_arr(body, err_ind);
		    err_ind++; // use 1 based indexing for the error reporting 
		    return shsl_expr_further_error
			(err_expr,
			 "cannot parse do-poking expression because expression "
			 "at position %zu in body was malformed", (size_t)err_ind);
		}
		return_mallocd_expr(.type = SHSL_EXPR_DO,
				    .do_expr = (shsl_do_expr) {
					.body = body,
					.body_length = (form_length-1),
				    });
	    }
	    else if(strcmp(s, "fn") == 0) {
                // malformed lambda list non lo possiamo dare a eval time quindi
                // la creazione della lambd list va fatta qua (parse don't validate)
                // ma, visto che vogliamo garantire che eval poi renda oggetti
                // che non hanno memoria in comune con form/expression passate
                // (per non segfaultare malissimo durante il free)
                // questa lambda list va poi copiata quando famo l'eval
                // 
                // idem per il body il che è un po' una rottura di coglioni
                // a dirla tutta :/
                // 
                // (fn [things] body)
                // we don't support multimethods for now :/
                if(!shsl_is_vec(shsl_nth(form, 1)))
                    return shsl_expr_error
                        (form,
                         "malformed fn expression, second element of function "
                         "definition must be a symbol array!");

                shsl_vec_foreach(i, elt, shsl_nth(form, 1))
                    if(!shsl_is_sym(elt)) {
                        // use 1-indexing for error reporting
			// altering the index is not a problem since we're
			// not gona use it after this anyway
			i++; 
                        return shsl_expr_error
                            (form,
                             "malformed function definition, function arguments "
                             "must all be symbols, but %zu%s argument of "
                             "function definition was not a symbol!",
                             (size_t)i, i==1?"st":i==2?"nd":i==3?"rd":"th");
                    }

                // we currently only support positional shit so...
                shsl_lambda_list* ll = malloc(sizeof(shsl_lambda_list));
                ll->positional = shsl_ref_add(shsl_nth(form, 1));
                ll->optional = shsl_ref_add(shsl_mkmap(1));
                ll->keyword = shsl_ref_add(shsl_mkmap(1));

                shsl_expr** body = shsl_form_list_to_expr_arr
                    (shsl_nthcdr(form, 2));
		ssize_t err_ind = shsl_expr_arr_find_err(body, form_length-2);
		if(err_ind != -1) {
		    shsl_expr* err_expr = body[err_ind];
		    shsl_free_expr_arr(body, err_ind);
		    err_ind++; // use 1 based indexing for the error reporting 
		    return shsl_expr_further_error
                        (err_expr,
                         "cannot parse function expressioned, %zu%s expression in "
                         "function body was malformed!",
                         (size_t)err_ind,
                         err_ind==1?"st":err_ind==2?"nd":err_ind==3?"rd":"th");
                }
                return_mallocd_expr(.type = SHSL_EXPR_FN,
                                    .fn_expr = (shsl_fn_expr) {
                                        .lambda_list = ll,
                                        .body = body,
                                        .body_length = form_length-2,
                                    });
            }
	    else if(strcmp(s, "set") == 0)
		assert(0 && "TODO: SET");
	    else if(strcmp(s, "def") == 0)
		assert(0 && "TODO: DEF");
	}

	// if none of the above then it's a funcall
	shsl_expr* fun_expr = shsl_form_to_expr(form.ptr->cons.car);
	shsl_expr** args = shsl_form_list_to_expr_arr(shsl_cdr(form));
	ssize_t  err_ind = shsl_expr_arr_find_err(args, form_length-1);
	if(err_ind != -1) {
	    shsl_expr* err_arg = args[err_ind];
	    shsl_free_expr_arr(args, err_ind);
	    err_ind++; // use 1 based indexing for the error reporting 
	    return shsl_expr_further_error
		(err_arg,
		 "cannot parse function call because functions's "
		 "%zu%s argument was a malformed expression",
		 (size_t)err_ind,
		 err_ind==1?"st":err_ind==2?"nd":err_ind==3?"rd":"th");
	    // this printing logic doesn't handle things like 32nd
	    // but if you pass 32 args to a function that's a you problem, sorry
	}

	return_mallocd_expr(.type = SHSL_EXPR_FUNCALL,
			    .funcall_expr = (shsl_funcall_expr) {
				.fun_expr = fun_expr,
				.args = args,
				.args_length = form_length - 1,
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
	return shsl_expr_error
	    (form,
	     "cannot include function object in source code of expression!"); 
    }
    assert(0 && "unreachable");
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
	shsl_ref_del(expr->literal);
	free(expr);
	break;
    case SHSL_EXPR_LOOKUP:
	shsl_ref_del(expr->lookup_symbol);
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
    case SHSL_EXPR_DEF:
	assert(0 && "TODO: free def expr");
	break;
    case SHSL_EXPR_SET:
	assert(0 && "TODO: free set expr");
	break;

    case SHSL_EXPR_FN: // anonymous/first class function
	assert(0 && "TODO: free fn expr");
	break;
    case SHSL_EXPR_MACRO: // anonymous/first class macro
	assert(0 && "TODO: free macro expr");
	break;

    case SHSL_EXPR_DO:
	shsl_free_expr_arr(expr->do_expr.body, expr->do_expr.body_length);
	free(expr);
	break;
    case SHSL_EXPR_DO_POKING:
	shsl_free_expr_arr(expr->do_poking_expr.body,
			   expr->do_poking_expr.body_length);
	free(expr);
	break;
    case SHSL_EXPR_FUNCALL:
	shsl_expr_free(expr->funcall_expr.fun_expr);
	shsl_free_expr_arr(expr->funcall_expr.args,
			   expr->funcall_expr.args_length);
	free(expr);
	break;
    }
}
// we need this function because I want function literals to return a fresh
// function that won't be affected by deleting the expression that originated it
// which means function literals must copy their body into that of the function
// they return
shsl_expr* shsl_expr_copy(shsl_expr* orig) {
    switch(orig->type) {
    case SHSL_EXPR_LITERAL:
        return_mallocd_expr
            (.type = SHSL_EXPR_LITERAL,
             .literal = shsl_ref_add(shsl_copy(orig->literal)));
    case SHSL_EXPR_LOOKUP:
        return_mallocd_expr
            (.type = SHSL_EXPR_LOOKUP,
             .lookup_symbol = shsl_ref_add(shsl_copy(orig->literal)));
    case SHSL_EXPR_VEC: {
        size_t size = orig->vec_expr.size;
        shsl_expr** elts = calloc(size, sizeof(shsl_expr*));
        for(size_t i = 0; i<size; ++i)
            elts[i] = shsl_expr_copy(orig->vec_expr.elts[i]);
        return_mallocd_expr(.type = SHSL_EXPR_VEC,
                            .vec_expr = (shsl_vec_expr) {
                                .elts = elts,
                                .size = size,
                            });
    }
    case SHSL_EXPR_MAP: {
        size_t size = orig->map_expr.size;
        shsl_expr** keys = calloc(size, sizeof(shsl_expr*));
        shsl_expr** vals = calloc(size, sizeof(shsl_expr*));
        for(size_t i = 0; i<size; ++i) {
            keys[i] = shsl_expr_copy(orig->map_expr.keys[i]);
            vals[i] = shsl_expr_copy(orig->map_expr.vals[i]);
        }
        return_mallocd_expr(.type = SHSL_EXPR_VEC,
                            .map_expr = (shsl_map_expr) {
                                .keys = keys,
                                .vals = vals,
                                .size = size,
                            });
    }
    case SHSL_EXPR_IF:
        return_mallocd_expr
            (.type = SHSL_EXPR_IF,
             .if_expr = (shsl_if_expr) {
                 .condition = shsl_expr_copy(orig->if_expr.condition),
                 .then_part = shsl_expr_copy(orig->if_expr.then_part),
                 .else_part = shsl_expr_copy(orig->if_expr.else_part),
             });
    case SHSL_EXPR_DO: {
        size_t body_length = orig->do_expr.body_length;
        shsl_expr** body = calloc(body_length, sizeof(shsl_expr*));
        for(size_t i = 0; i<body_length; ++i) {
            body[i] = shsl_expr_copy(orig->do_expr.body[i]);
        }
        return_mallocd_expr
            (.type = SHSL_EXPR_DO,
             .do_expr = (shsl_do_expr) {
                .body = body,
                .body_length = body_length,
             });
    }
    case SHSL_EXPR_DO_POKING: {
        size_t body_length = orig->do_poking_expr.body_length;
        shsl_expr** body = calloc(body_length, sizeof(shsl_expr*));
        for(size_t i = 0; i<body_length; ++i) {
            body[i] = shsl_expr_copy(orig->do_poking_expr.body[i]);
        }
        return_mallocd_expr
            (.type = SHSL_EXPR_DO_POKING,
             .do_poking_expr = (shsl_do_poking_expr) {
                .body = body,
                .body_length = body_length,
             });
    }
    case SHSL_EXPR_LET:
        assert(0 && "TODO: copy let expression");
    case SHSL_EXPR_WHILE:
        assert(0 && "TODO: copy while expression");
    case SHSL_EXPR_DEF:
        assert(0 && "TODO: copy def expression");
    case SHSL_EXPR_SET:
        assert(0 && "TODO: copy set expression");
    case SHSL_EXPR_FN:
        assert(0 && "TODO: copy fn expression");
    case SHSL_EXPR_MACRO:
        assert(0 && "TODO: copy macro expression");
    case SHSL_EXPR_FUNCALL:
        assert(0 && "TODO: copy funcall expression");
    }
    assert(0 && "UNREACHABLE");
}

shsl_ref shsl_env_mkframe(shsl_ref syms, shsl_ref vals) {
    assert(syms.ptr->type == SHSL_VEC);
    assert(vals.ptr->type == SHSL_VEC);
    assert(shsl_vec_length(syms) == shsl_vec_length(vals));

    shsl_ref frame = shsl_mkmap(shsl_vec_length(syms));
    shsl_vec_foreach(i, sym, syms) {
	shsl_ref val = shsl_vec_get(vals, i);
	shsl_map_set(frame, sym, val);
    }
    return frame;
}

/// EVALUATION FUNCTIONS DEFINITIONS
// TODO: it
shsl_ref shsl_eval(shsl_expr* expr, shsl_ref env) {
    switch(expr->type) {
    case SHSL_EXPR_LITERAL:
	return shsl_copy(expr->literal);
    case SHSL_EXPR_LOOKUP:
	return shsl_env_lookup(env, expr->lookup_symbol);
    case SHSL_EXPR_VEC: {
	size_t size = expr->vec_expr.size;
	shsl_ref vec = shsl_mkvec(size);
	for(size_t i = 0; i<size; ++i)
	    shsl_vec_push(vec, shsl_eval(expr->vec_expr.elts[i], env));
	return vec;
    }
    case SHSL_EXPR_MAP: {
	size_t size = expr->map_expr.size;
	shsl_ref map = shsl_mkmap(size);
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
    case SHSL_EXPR_DO: {
	size_t len = expr->do_expr.body_length;
	if(len == 0)
	    return ref_to_nil();

	shsl_ref inner_env = shsl_mkcons(shsl_mkmap(1), env);
	// TODO: if a function is defined inside the inner env and gets a ref to it
	// then how do we ensure the env is freed correctly if the function becomes
	// unreachable but still holds a ref to the env?
	shsl_ref_add(inner_env);
	for(size_t i = 0; i<len-1; ++i)
	    shsl_eval(expr->do_expr.body[i], inner_env);
	shsl_ref_del(inner_env);
	return shsl_eval(expr->do_expr.body[len-1], env);
    }
    case SHSL_EXPR_DO_POKING: {
	size_t len = expr->do_poking_expr.body_length;
	if(len == 0)
	    return ref_to_nil();
	for(size_t i = 0; i<len-1; ++i)
	    shsl_eval(expr->do_poking_expr.body[i], env);
	return shsl_eval(expr->do_expr.body[len-1], env);
    }

    case SHSL_EXPR_FUNCALL: {
	shsl_ref fun = shsl_eval(expr->funcall_expr.fun_expr, env);
	switch(fun.ptr->type) {
	case SHSL_BUILTIN_FUN: {
	    shsl_ref args = shsl_eval_many_into_vec
		(expr->funcall_expr.args,
		 expr->funcall_expr.args_length,
		 env);
	    // TODO: bit of a dick move, but as of now builtin funs
	    // are evaluated within the calling environment
	    // making them a gross violation of lexical binding
	    shsl_ref res = fun.ptr->builtin_fun.apply(args, env);
	    shsl_free(args);
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
    case SHSL_EXPR_LET:
    case SHSL_EXPR_DEF:
    case SHSL_EXPR_SET:
    case SHSL_EXPR_FN:
    case SHSL_EXPR_MACRO:
	assert(0 && "TODO");
    }
    assert(0 && "unreachable");
}
shsl_ref shsl_eval_many_into_vec(shsl_expr** args, size_t args_len,
				  shsl_ref env) {
    shsl_ref vec_obj = shsl_mkvec(args_len);
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
    shsl_ref c_name(shsl_ref args_name, shsl_ref env_name)		\
    {									\
	const char* shsl_fun_name = shsl_name;	/* used by macros */	\
	shsl_fun_assert_vec((args_name));				\
	do __VA_ARGS__ while(0);					\
    }									\

#define shsl_fun_assert(ass) do {				\
	if(!(ass))						\
	    return shsl_mkerr(ref_to_nil(),			\
			      "in function %s, assertion "	\
			      #ass "failed!", shsl_fun_name);	\
    } while(0)

#define shsl_fun_assert_vec(args)		\
    shsl_fun_assert(shsl_is_vec(args))

#define shsl_fun_assert_size(args, pred)		\
    shsl_fun_assert((shsl_vec_length(args)) pred)

#define shsl_fun_assert_type(args, i, t)		\
    shsl_fun_assert(shsl_vec_get(args, i).ptr->type == (t))

#define shsl_fun_assert_type_either(args, i, t1, t2)		\
    shsl_fun_assert(shsl_vec_get(args, i).ptr->type == (t1) ||	\
		    shsl_vec_get(args, i).ptr->type == (t2))

shsl_defun(shsl_builtin_vecget, "vecget", args, env, {
	(void)env;
	shsl_fun_assert_size(args, == 2);
	shsl_fun_assert_type(args, 0, SHSL_VEC);
	shsl_fun_assert_type(args, 1, SHSL_INT);
	return shsl_vec_get(args, (size_t)shsl_vec_get(args, 1).ptr->i);
    })

/// SHSL ARITHMETIC FUNCTIONS DEFINITIONS
SHSL_OBJ_TYPE shsl_type(shsl_ref ref) {
    return ref.ptr->type;
}
long shsl_int(shsl_ref ref) {
    assert(shsl_type(ref) == SHSL_INT);
    return ref.ptr->i;
}
double shsl_real(shsl_ref ref) {
    assert(shsl_is_int(ref) || shsl_is_real(ref));
    return shsl_is_int(ref)?(double)ref.ptr->i:ref.ptr->r;
}
shsl_defun(shsl_builtin_add, "+", args, env, {
	(void)env;
	shsl_vec_foreach(i, elt, args)
	    shsl_fun_assert_type_either(args, i, SHSL_INT, SHSL_REAL);

	long intsum = 0;
	shsl_vec_foreach(i, elt, args) {
	    if(!shsl_is_int(elt))
		goto realsum;
	    else
		intsum += shsl_int(elt);
	}
	return shsl_mkint(intsum);
    realsum:
	double realsum = 0.0;
	shsl_vec_foreach(i, elt, args)
	    realsum += shsl_real(elt);
	return shsl_mkreal(realsum);
    })
shsl_defun(shsl_builtin_sub, "-", args, env, {
	(void)env;
	shsl_vec_foreach(i, elt, args)
	    shsl_fun_assert_type_either(args, i, SHSL_INT, SHSL_REAL);

	switch(shsl_vec_length(args)) {
	case 0:
	    return shsl_mkint(0);
	case 1:
	    return shsl_copy(shsl_vec_get(args, 0));
	default: {
	    long intdiff = 0;
	    if(!shsl_is_int(shsl_vec_get(args, 0)))
		goto realdiff;
	    intdiff = shsl_int(shsl_vec_get(args, 0));
	    for(size_t i = 1; i<shsl_vec_length(args); ++i)
		if(!shsl_is_int(shsl_vec_get(args, i)))
		    goto realdiff;
		else
		    intdiff -= shsl_int(shsl_vec_get(args, i));
	    return shsl_mkint(intdiff);

	    realdiff:
	    double realdiff = shsl_real(shsl_vec_get(args, 0));
	    for(size_t i = 1; i<shsl_vec_length(args); ++i)
		realdiff -= shsl_real(shsl_vec_get(args, i)); 
	    return shsl_mkreal(realdiff);
	}
	}
    })
shsl_defun(shsl_builtin_mul, "*", args, env, {
	(void)env;
	shsl_vec_foreach(i, elt, args)
	    shsl_fun_assert_type_either(args, i, SHSL_INT, SHSL_REAL);

	long intprod = 1;
	shsl_vec_foreach(i, elt, args) {
	    if(!shsl_is_int(elt))
		goto realprod;
	    else
		intprod *= shsl_int(elt);
	}
	return shsl_mkint(intprod);
    realprod:
	double realprod = 1.0;
	shsl_vec_foreach(i, elt, args)
	    realprod *= shsl_real(elt);
	return shsl_mkreal(realprod);
    })
shsl_defun(shsl_builtin_div, "/", args, env, {
	(void)env;
	shsl_fun_assert_size(args, == 2);
	shsl_fun_assert_type_either(args, 0, SHSL_INT, SHSL_REAL);
	shsl_fun_assert_type_either(args, 1, SHSL_INT, SHSL_REAL);

	// handle case where it returns integer
	if(shsl_is_int(shsl_vec_get(args, 0))
	   && shsl_is_int(shsl_vec_get(args, 1))
	   && shsl_int(shsl_vec_get(args, 1)) != 0
	   && ((shsl_int(shsl_vec_get(args, 1))
		% shsl_int(shsl_vec_get(args, 1))) == 0))
	    return shsl_mkint(shsl_int(shsl_vec_get(args, 0))
			      / shsl_int(shsl_vec_get(args, 1)));

	double a = shsl_real(shsl_vec_get(args, 0));
	double b = shsl_real(shsl_vec_get(args, 1));
	if(b == 0.0)
	    return shsl_mkerr(args, "in function /: division by zero!");
	return shsl_mkreal(a/b);
    })
/// SHSL OTHER FUNCTIONS DEFINITIONS
shsl_defun(shsl_builtin_print, "print", args, env, {
	(void)env;
	shsl_vec_foreach(i, elt, args) {
	    shsl_fputobj(elt, stdout);
	    if(i+1 != shsl_vec_length(args))
		fputc(' ', stdout);
	}
	return ref_to_nil();
    })
shsl_defun(shsl_builtin_println, "println", args, env, {
	shsl_builtin_print(args, env);
	fputc('\n', stdout);
	return ref_to_nil();
    })

/// ENVIRONMENT FUNCTIONS DEFINITIONS
shsl_ref shsl_make_initial_env(void) {
    shsl_ref frame_obj = shsl_mkmap(20);
    shsl_ref env_obj = shsl_mkcons(frame_obj, ref_to_nil());

    // globals
    shsl_map_set(frame_obj, shsl_mksym("nil"), ref_to_nil());
    shsl_ref t = shsl_mksym("t");
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
    // isnil, cons, iscons, list, islist, isproper, car, cdr, null

    // vector operations
    // isvec, vecget, vecset, veclen

    // map operations
    // ismap, mapget, mapset, maphas

    // error functions
    // iserror, error

    // collection operations
    // map, filter, reduce

    // other functions
    // print... mostly print
    shsl_map_set(frame_obj, shsl_mksym("print"),
		 shsl_mkbuiltin_fun(env_obj, shsl_builtin_print));
    shsl_map_set(frame_obj, shsl_mksym("println"),
		 shsl_mkbuiltin_fun(env_obj, shsl_builtin_println));
    // introspection functions
    // get the environment as a list lol
    // wait I cannot do that with lexical scoping
    // this is gonna have to be a special form :| 

    // TODO: ctypes equivalent
    return env_obj;
}
shsl_kv shsl_env_find_kv(shsl_ref env, shsl_ref key) {
    (void)env; (void)key;
    assert(0 && "TODO");
}
shsl_ref shsl_env_lookup(shsl_ref env, shsl_ref key) {
    assert(shsl_type(key) == SHSL_SYM);
    if(shsl_is_nil(env))
	return shsl_mkerr(key, "symbol not found!");

    assert(shsl_type(env) == SHSL_CONS);
    assert(shsl_type(shsl_car(env)) == SHSL_MAP);

    ssize_t i = shsl_map_index(shsl_car(env), key);
    if(i>=0)
	return env.ptr->cons.car.ptr->map.buf[i].v;
    return shsl_env_lookup(shsl_cdr(env), key);
}
shsl_ref shsl_env_set(shsl_ref env, shsl_ref key) {
    (void)env; (void)key;
    assert(0 && "TODO");
}
shsl_ref shsl_env_def(shsl_ref env, shsl_ref key) {
    (void)env; (void)key;
    assert(0 && "TODO");
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
    shsl_fputobj(tok->ref, stream);
}
void shsl_fputobj(const shsl_ref ref, FILE* restrict stream) {
    switch(ref.ptr->type) {
    case SHSL_INT:
	fprintf(stream, "%ld", ref.ptr->i);
	break;
    case SHSL_REAL:
	fprintf(stream, "%f", ref.ptr->r);
	break;
    case SHSL_STRING:
	fprintf(stream, "\"%s\"", ref.ptr->str);
	break;
    case SHSL_SYM:
	fprintf(stream, "%s", shsl_sym_name(ref));
	break;
    case SHSL_NIL:
	fputs("nil", stream);
	break;
    case SHSL_ERR:
	fprintf(stream, "(ERROR: \"%s\" WITH DATA ", ref.ptr->err.msg.ptr->str);
	shsl_fputobj(ref.ptr->err.data, stream);
	fprintf(stream, ")");
	break;
    case SHSL_CONS:
	if(shsl_is_proper_list(ref)) {
	    fputc('(', stream);
	    shsl_ref iter = ref;
	    while(shsl_is_cons(iter)) {
		shsl_fputobj(iter.ptr->cons.car, stream);
		if(shsl_is_cons(iter.ptr->cons.cdr))
		    fputs(" ", stream);
		iter = iter.ptr->cons.cdr;
	    }
	    fputc(')', stream);
	}
	else {
	    fputc('(', stream);
	    shsl_fputobj(ref.ptr->cons.car, stream);
	    fputs(" . ", stream);
	    shsl_fputobj(ref.ptr->cons.cdr, stream);
	    fputc(')', stream);
	}
	break;
    case SHSL_VEC:
	fputc('[', stream);
	shsl_vec_foreach(i, elt, ref) {
	    shsl_fputobj(elt, stream);
	    if(i != shsl_vec_length(ref)-1)
		fputs(", ", stream);
	}
	fputc(']', stream);
	break;
    case SHSL_MAP:
	fputc('{', stream);
	for(size_t i = 0; i<ref.ptr->map.size; ++i) {
	    shsl_fputobj(ref.ptr->map.buf[i].k, stream);
	    fputs(":", stream);
	    shsl_fputobj(ref.ptr->map.buf[i].v, stream);
	    if(i != ref.ptr->vec.size -1)
		fputs(", ", stream);
	}
	fputc('}', stream);
	break;
    case SHSL_BUILTIN_FUN:
	fprintf(stdout, "SHSL_BUILTIN_FUN_%p", (void*)(ref.ptr));
	break;
    case SHSL_USER_FUN:
	fprintf(stdout, "SHSL_USER_FUN_%p", (void*)(ref.ptr));
	break;
    case SHSL_BUILTIN_MACRO:
	fprintf(stdout, "SHSL_BUILTIN_MACRO_%p", (void*)(ref.ptr));
	break;
    case SHSL_USER_MACRO:
	fprintf(stdout, "SHSL_USER_MACRO_%p", (void*)(ref.ptr));
	break;
    };
}

//// USER FACING FUNCTIONS DEFINITIONS
//// ----------------------------------------------------------------------------
shsl_ref shsl_eval_str(char* c, shsl_ref env) {
    parser_pair p = parse_off(c);
    // TODO: make form_to_expr accept an environment so we can do macro expansion
    // during form "compilation"?
    shsl_ref_add(p.ref);
    shsl_expr* expr = shsl_form_to_expr(p.ref);
    shsl_ref_del(p.ref);

    shsl_ref res = shsl_eval(expr, env);
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
    shsl_ref env = shsl_make_initial_env();
    shsl_ref_add(env);
    while(i<argc) {
	if(strcmp(argv[i], "-e") == 0) {
            shsl_ref ref = shsl_ref_add(shsl_eval_str(argv[i+1], env));
	    shsl_fputobj(ref, stdout);
            shsl_ref_del(ref);
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
    shsl_ref_del(env);
    return 0;
}
#endif // SHSL_MAIN

#endif // SHSL_H
