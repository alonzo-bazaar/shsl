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

#include<ctype.h>
#include<string.h>
#include<assert.h>

#define defstruct(s) struct s; typedef struct s s
#define defenum(e) enum e; typedef enum e e

//// DATA DECLARATIONS
//// ----------------------------------------------------------------------------

/// DATA TYPES DECLARATIONS
// type tag for shsl objects
defenum(SHSL_OBJECT_TYPE);
// tagged union of all possible shsl objects
defstruct(shsl_obj);
// possible shsl objects
// (outside of primitive types for which we just use the C ones)
defstruct(shsl_sym);
defstruct(shsl_error);
defstruct(shsl_cons);
defstruct(shsl_vec);
// key value pair (for maps)
// kv pairs are not shsl objects, they're defined separately just for ease 
// other than that they're just there to aid in defining maps
defstruct(shsl_kv);
// map as vector of kv pairs
defstruct(shsl_map);

/// DATA CONSTRUCTION DECLARATIONS
// we handle everything through pointers because havnig everything
// on the heap makes it easier to automatically manage
shsl_obj* shsl_obj_mkint(long l);
shsl_obj* shsl_obj_mkreal(double d);
shsl_obj* shsl_obj_mkstr(const char* str);
shsl_obj* shsl_obj_mksym(const char* name);
shsl_obj* shsl_obj_mkerr(const char* msg, shsl_obj* data);
shsl_obj* shsl_obj_mkcons(shsl_obj* car, shsl_obj* cdr);

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
void shsl_free_obj(shsl_obj* obj);
// creates fresh (newly allocated) deep copy of obj
// does not copy refcount tho
// fresh objects are initialized with an initial refcount of 0
shsl_obj* shsl_obj_copy(shsl_obj* obj);
bool shsl_obj_eq(shsl_obj* lhs, shsl_obj* rhs);

/// CONS MANIPULATIONS DECLARATIONS
void shsl_cons_set_cdr(shsl_obj* cons_obj, shsl_obj* cdr);
void shsl_cons_set_car(shsl_obj* cons_obj, shsl_obj* car);

/// VECTOR MANIPULATIONS DECLARATIONS
void shsl_vec_expand(shsl_obj* vec_obj, size_t new_size);
void shsl_vec_push(shsl_obj* vec_obj, shsl_obj* obj);
shsl_obj* shsl_vec_get(shsl_obj* vec_obj, size_t i);
void shsl_vec_set(shsl_obj* vec_obj, size_t i, shsl_obj* new_val);

/// MAP MANIPULATIONS DECLARATIONS
void shsl_map_expand(shsl_obj* map_obj, size_t new_size);
// it's ssize_t instead of size_t so we can use -1 to say "hey, didn't find shit"
ssize_t shsl_map_index(shsl_obj* map_obj, shsl_obj* key);
shsl_obj* shsl_map_get(shsl_obj* map_obj, shsl_obj* key);
void shsl_map_set(shsl_obj* map_obj,
                  shsl_obj* key, shsl_obj* new_val);

/// DATA PREDICATES DECLARATIONS
bool shsl_is_nil(shsl_obj* obj);
bool shsl_is_cons(shsl_obj* obj);
bool shsl_is_err(shsl_obj* obj);
bool shsl_is_truthy(shsl_obj* obj);
bool shsl_is_list(shsl_obj* obj);
bool shsl_is_well_formed_list(shsl_obj* list_obj);

/// LIST OPERATIONS DECLARATIONS
shsl_obj* shsl_car(shsl_obj* obj);
shsl_obj* shsl_cdr(shsl_obj* obj);
shsl_obj* shsl_nthcdr(shsl_obj* obj, size_t n);
shsl_obj* shsl_nth(shsl_obj* list_obj, size_t n);
// ssize_t so we can use -1 as "bro what the fuck is this object"
ssize_t shsl_list_length(shsl_obj* list_obj);


//// LEXER DECLARATIONS
//// ----------------------------------------------------------------------------

// possible types a token may assume
defenum(SHSL_TOKEN_TYPE);
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
			enum SHSL_TOKEN_TYPE stop,
			enum SHSL_TOKEN_TYPE* error_on, size_t error_on_len);


//// EVALUATOR DECLARATIONS
//// ----------------------------------------------------------------------------

/// EXPRESSION TYPE DECLARATIONS
defenum(SHSL_EXPRESSION_TYPE);
defstruct(if_expr);
defstruct(do_expr);
defstruct(do_poking_expr);
defstruct(def_expr);
defstruct(set_expr);
// tagged union of all possible expression types
// (either the ones above or like, literals and shit)
defstruct(shsl_expression);

/// FORM TRANSLATION FUNCTIONS DECLARATIONS
shsl_expression* shsl_form_to_expr(shsl_obj* form);
bool shsl_expr_is_error(shsl_expression* expr);

/// EVALUTATION FUNCTION DECLARATIONS
// we don't have a separate shsl_environment type as the enviroment will be
// represented using a cons list of shsl maps
// this should make for easier debuggability, even from within shsl
// and may allow for some funky pythonish introspection
shsl_obj* shsl_eval(shsl_expression* form, shsl_obj* env);

//// PRINT DEBUGGING DECLARATIONS
//// ----------------------------------------------------------------------------
void shsl_dbg_fputtok(const shsl_token* tok, FILE* restrict stream);
void shsl_dbg_fputobj(const shsl_obj* obj, FILE* restrict stream);

#ifdef SHSL_IMPLEMENTATION
//// DATA DEFINITIONS
//// ----------------------------------------------------------------------------

/// DATA TYPES DEFINITIONS
typedef enum SHSL_OBJECT_TYPE {
    // atoms
    // nil first so an object initialized as {0} is nil
    SHSL_OBJ_NIL = 0, SHSL_OBJ_SYMBOL, 
    SHSL_OBJ_INTEGER, SHSL_OBJ_REAL, SHSL_OBJ_STRING,

    // composite
    SHSL_OBJ_CONS, SHSL_OBJ_MAP, SHSL_OBJ_VECTOR,

    // error
    SHSL_OBJ_ERROR,
} SHSL_OBJECT_TYPE;
typedef struct shsl_sym {
    shsl_obj* name; // must be string
} shsl_sym ;
typedef struct shsl_error {
    shsl_obj* msg; // must be string
    shsl_obj* data;
} shsl_error;
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
typedef struct shsl_obj {
    // header
    int ref_count;
    SHSL_OBJECT_TYPE type;

    // data
    union {
	long i;
	double r;
	char* str;
	shsl_sym sym;
	shsl_cons cons;
	shsl_vec vec;
	shsl_map map;
	shsl_error err;
    };
} shsl_obj;	

shsl_obj SHSL_NIL = {0};

/// DATA CONSTRUCTION DEFINITIONS
// the shsl_obj_mk* functions all return references to fresh objects
// although those objects may contain references to pre-existing objects
// if they're cons cells, vectors, or maps, for instance
// 
// all raw C data passed to an shsl_obj_mk* constructor
// (numbers, chars, strings (both for shsl strings and symbol names))
// is copied into the returned object,
// so changes to the object won't change the original data and viceversa
// 
// this, although inefficient, ensures that all the data contained in shsl
// objects can be safely managed by our autoamtic memory management
// and prevents weird data races we may encounter at the language boundary
shsl_obj* shsl_obj_mkint(long l) {
    shsl_obj* obj_p = (shsl_obj*)malloc(sizeof(shsl_obj));
    *obj_p = (shsl_obj)
	{ .ref_count = 0, .type = SHSL_OBJ_INTEGER, .i = l, };
    return obj_p;
}
shsl_obj* shsl_obj_mkreal(double d) {
    shsl_obj* obj_p = (shsl_obj*)malloc(sizeof(shsl_obj));
    *obj_p = (shsl_obj)
	{ .ref_count = 0, .type = SHSL_OBJ_REAL, .r = d, };
    return obj_p;
}
shsl_obj* shsl_obj_mkstr(const char* str) {
    shsl_obj* obj_p = (shsl_obj*)malloc(sizeof(shsl_obj));
    char* c = (char*)malloc(strlen(str) * sizeof(char));
    strcpy(c, str);
    *obj_p = (shsl_obj)
	{
	    .ref_count = 0,
	    .type = SHSL_OBJ_STRING,
	    .str = c,
	};
    return obj_p;
}
shsl_obj* shsl_obj_mksym(const char* name) {
    shsl_obj* sym_obj = (shsl_obj*)malloc(sizeof(shsl_obj));
    *sym_obj = (shsl_obj) {
	.ref_count = 0,
	.type = SHSL_OBJ_SYMBOL,
	.sym = (shsl_sym) {
	    .name = shsl_add_ref(shsl_obj_mkstr(name)),
	},
    };
    return sym_obj;
}
shsl_obj* shsl_obj_mkerr(const char* msg, shsl_obj* data) {
    shsl_obj* err_obj = (shsl_obj*)malloc(sizeof(shsl_obj));
    *err_obj = (shsl_obj) {
	.ref_count = 0,
	.type = SHSL_OBJ_ERROR,
	.err = (shsl_error) {
	    .msg = shsl_add_ref(shsl_obj_mkstr(msg)),
	    .data = shsl_add_ref(data),
	},
    };
    return err_obj;
}
shsl_obj* shsl_obj_mkcons(shsl_obj* car, shsl_obj* cdr) {
    shsl_obj* cons_obj = (shsl_obj*)(malloc)(sizeof(shsl_obj));
    *cons_obj = (shsl_obj) {
	.ref_count = 0,
	.type = SHSL_OBJ_CONS,
	.cons = (shsl_cons) { .car = shsl_add_ref(car),
			      .cdr = shsl_add_ref(cdr), }
    };
    return cons_obj;
}
shsl_obj* shsl_obj_mkvec(size_t initial_capacity) {
    assert(initial_capacity > 0);

    shsl_obj* obj_p = (shsl_obj*)malloc(sizeof(shsl_obj));
    *obj_p = (shsl_obj) {
	.ref_count = 0,
	.type = SHSL_OBJ_VECTOR,
	.vec = (shsl_vec) {
	    .buf = (shsl_obj**) malloc(initial_capacity * sizeof(shsl_obj*)),
	    .size = 0,
	    .capacity = initial_capacity,
	},
    };
    return obj_p;
}
shsl_obj* shsl_obj_mkmap(size_t initial_capacity) {
    shsl_obj* obj_p = (shsl_obj*)malloc(sizeof(shsl_obj));
    *obj_p = (shsl_obj) {
	.ref_count = 0,
	.type = SHSL_OBJ_MAP,
	.map = (shsl_map){
	    .buf = (shsl_kv*)malloc(initial_capacity * sizeof(shsl_kv)),
	    .size = 0,
	    .capacity = initial_capacity,
	}
    };
    return obj_p;
}

/// DATA OPERATIONS DEFINITIONS
/// GENERIC OPERATIONS DEFINITIONS
shsl_obj* shsl_add_ref(shsl_obj* obj) {
    if(obj->type != SHSL_OBJ_NIL)
	obj->ref_count++;
    return obj;
}
void shsl_del_ref(shsl_obj* obj) {
    if(obj->type != SHSL_OBJ_NIL) {
	obj->ref_count--;
	if(obj->ref_count == 0)
	    shsl_free_obj(obj);
	if(obj->ref_count < 0)
	    fprintf(stderr, "now you fucked up!\n");
    }
}
void shsl_free_obj(shsl_obj *obj) {
    switch(obj->type) {
    case SHSL_OBJ_NIL:
	fprintf(stderr, "cannot free NIL! You fucked something up!\n");
	break;

    case SHSL_OBJ_STRING:
	free(obj->str);
	free(obj);
	break;

    case SHSL_OBJ_SYMBOL:
	shsl_del_ref(obj->sym.name);
	free(obj);
	break;

    case SHSL_OBJ_ERROR:
	shsl_del_ref(obj->err.msg);
	shsl_del_ref(obj->err.data);
	free(obj);
	break;

    case SHSL_OBJ_CONS:
	shsl_del_ref(obj->cons.car);
	shsl_del_ref(obj->cons.cdr);
	free(obj);
	break;

    case SHSL_OBJ_VECTOR:
	for(size_t i = 0; i<obj->vec.size; ++i)
	    shsl_del_ref(obj->vec.buf[i]);
	free(obj->vec.buf);
	free(obj);
	break;

    case SHSL_OBJ_MAP:
	for(size_t i = 0; i<obj->map.size; ++i) {
	    shsl_del_ref(obj->map.buf[i].k);
	    shsl_del_ref(obj->map.buf[i].v);
	}
	free(obj->map.buf);
	free(obj);
	break;

    default:
	free(obj);
	break;
    }
}
shsl_obj* shsl_obj_copy(shsl_obj* obj) {
    // TODO: create fresh copy
    return obj;
}
bool shsl_obj_eq(shsl_obj* lhs, shsl_obj* rhs) {
    if(lhs->type != rhs->type)
	return false;
	
    switch(lhs->type) {
    case SHSL_OBJ_NIL:
	return true;
    case SHSL_OBJ_SYMBOL:
	return strcmp(lhs->sym.name->str, rhs->sym.name->str) == 0;
    case SHSL_OBJ_ERROR:
	return strcmp(lhs->err.msg->str, rhs->err.msg->str) == 0
	    && shsl_obj_eq(lhs->err.data, lhs->err.data);

    case SHSL_OBJ_INTEGER:
	return lhs->i == rhs->i;
    case SHSL_OBJ_REAL:
	return lhs->r == rhs->r;
    case SHSL_OBJ_STRING:
	return strcmp(lhs->str, rhs->str) == 0;

    case SHSL_OBJ_CONS:
	return shsl_obj_eq(lhs->cons.car, rhs->cons.car)
	    && shsl_obj_eq(lhs->cons.cdr, rhs->cons.cdr);

    case SHSL_OBJ_VECTOR:
	if(lhs->vec.size != rhs->vec.size)
	    return false;
	for(size_t i = 0; i<lhs->vec.size; ++i)
	    if(!shsl_obj_eq(lhs->vec.buf[i], rhs->vec.buf[i]))
		return false;
	return true;

    case SHSL_OBJ_MAP:
	if(lhs->map.size != rhs->map.size)
	    return false;
	for(size_t i = 0; i<lhs->map.size; ++i)
	    if(!shsl_obj_eq(shsl_map_get(lhs, lhs->map.buf[i].k),
			    shsl_map_get(rhs, lhs->map.buf[i].k)))
		return false;
	return true;
    }
    assert(0 && "UNREACHABLE");
}

/// CONS MANIPULATIONS DEFINITIONS
void shsl_cons_set_cdr(shsl_obj* cons_obj, shsl_obj* cdr) {
    assert(cons_obj->type == SHSL_OBJ_CONS);
    shsl_add_ref(cdr);
    shsl_del_ref(cons_obj->cons.cdr);
    cons_obj->cons.cdr = cdr;
}
void shsl_cons_set_car(shsl_obj* cons_obj, shsl_obj* car) {
    assert(cons_obj->type == SHSL_OBJ_CONS);
    shsl_add_ref(car);
    shsl_del_ref(cons_obj->cons.car);
    cons_obj->cons.car = car;
}

/// VECTOR MANIPULATIONS DEFINITIONS
void shsl_vec_expand(shsl_obj* vec_obj, size_t new_size) {
    assert(vec_obj->type == SHSL_OBJ_VECTOR);

    if(vec_obj->vec.capacity >= new_size)
	return;
    vec_obj->vec.buf = (shsl_obj**)realloc(vec_obj->vec.buf,
					   new_size*sizeof(shsl_obj*));
    vec_obj->vec.capacity = new_size;
}
void shsl_vec_push(shsl_obj* vec_obj, shsl_obj* obj) {
    assert(vec_obj->type == SHSL_OBJ_VECTOR);

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
    assert(vec_obj->type == SHSL_OBJ_VECTOR);

    if(i >= vec_obj->vec.size)
	return shsl_obj_mkerr("out of bounds array read!", &SHSL_NIL);
    return vec_obj->vec.buf[i];
}
void shsl_vec_set(shsl_obj* vec_obj, size_t i, shsl_obj* new_val) {
    assert(vec_obj->type == SHSL_OBJ_VECTOR);

    // TODO: gestione degli errori un po' di più magari
    if(i >= vec_obj->vec.size)
	fprintf(stderr, "out of bounds array write!\n");

    shsl_add_ref(new_val);
    shsl_del_ref(vec_obj->vec.buf[i]);
    vec_obj->vec.buf[i] = new_val;
}

/// MAP MANIPULATIONS DEFINITIONS
void shsl_map_expand(shsl_obj* map_obj, size_t new_size) {
    assert(map_obj->type == SHSL_OBJ_MAP);

    if (map_obj->map.capacity >= new_size)
	return;
    map_obj->map.buf = (shsl_kv*)realloc(map_obj->map.buf,
					 new_size*sizeof(shsl_kv));
    map_obj->map.capacity = new_size;
}
ssize_t shsl_map_index(shsl_obj* map_obj, shsl_obj* key) {
    assert(map_obj->type == SHSL_OBJ_MAP);

    for(size_t i = 0; i<map_obj->map.size; ++i)
	if(shsl_obj_eq(key, map_obj->map.buf[i].k))
	    return (ssize_t)i;
    return -1;
}
shsl_obj* shsl_map_get(shsl_obj* map_obj, shsl_obj* key) {
    assert(map_obj->type == SHSL_OBJ_MAP);

    ssize_t i = shsl_map_index(map_obj, key);
    if(i>=0) return map_obj->map.buf[i].v;
    return &SHSL_NIL;
}
void shsl_map_set(shsl_obj* map_obj, shsl_obj* key, shsl_obj* new_val) {
    assert(map_obj->type == SHSL_OBJ_MAP);

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
    }
}

/// DATA PREDICATES DEFINITIONS
bool shsl_is_nil(shsl_obj* obj) {
    return obj->type == SHSL_OBJ_NIL;
}
bool shsl_is_cons(shsl_obj* obj) {
    return obj->type == SHSL_OBJ_CONS;
}
bool shsl_is_err(shsl_obj* obj) {
    return obj->type == SHSL_OBJ_ERROR;
}
bool shsl_is_truthy(shsl_obj* obj) {
    if(shsl_is_nil(obj) || shsl_is_err(obj)) return false;
    return true;
}
bool shsl_is_list(shsl_obj* obj) {
    return shsl_is_nil(obj) || shsl_is_cons(obj);
}
// TODO: infinite loops on circular lists
// I'm already refcounting so I have accepted those will be a pita
bool shsl_is_well_formed_list(shsl_obj* list_obj) {
    while(true) {
	switch(list_obj->type) {
	case SHSL_OBJ_NIL:
	    return true;
	case SHSL_OBJ_CONS:
	    list_obj = list_obj->cons.cdr;
	    break;
	default:
	    return false;
	}
    }
}

/// LIST OPERATIONS DEFINITIONS
#ifdef SHSL_LOG_RETURN_ERROR
#define return_error(data, msg, ...) do{                        \
	fprintf(stderr, "[ERROR] "msg"\n", __VA_ARGS__);        \
	return shsl_obj_mkerr(msg, data);                       \
    } while(0)
#else
// TODO: sprintf
#define return_error(data, msg, ...) return shsl_obj_mkerr(msg, data)
#endif

shsl_obj* shsl_car(shsl_obj* obj) {
    switch(obj->type) {
    case SHSL_OBJ_NIL:
	return obj;
    case SHSL_OBJ_CONS:
	return obj->cons.car;
    default:
	return_error(obj, "CAR: cannot get car as object is not a list");
    }
}
shsl_obj* shsl_cdr(shsl_obj* obj) {
    switch(obj->type) {
    case SHSL_OBJ_NIL:
	return obj;
    case SHSL_OBJ_CONS:
	return obj->cons.cdr;
    default:
	return_error(obj, "CDR: cannot get car as object is not a list");
    }
}
shsl_obj* shsl_nthcdr(shsl_obj* obj, size_t n) {
    while(n-- && !shsl_is_err(obj))
	obj = shsl_cdr(obj);
    if(shsl_is_err(obj))
	return_error(obj, "NTHCDR: cannot get nthcdr of list :(");
    return obj;
}
shsl_obj* shsl_nth(shsl_obj* list_obj, size_t n) {
    shsl_obj* nth = shsl_car(shsl_nthcdr(list_obj, n));
    if(shsl_is_err(nth))
	return_error(nth, "NTH: can't get nth element of object");
    return nth;
}
ssize_t shsl_list_length(shsl_obj* list_obj) {
    for(ssize_t i = 0; ; ++i) {
	switch(list_obj->type) {
	case SHSL_OBJ_NIL:
	    return i;
	case SHSL_OBJ_CONS:
	    list_obj = list_obj->cons.cdr;
	    break;
	default:
	    return -1;
	}
    }
}

//// LEXER DEFINITIONS
//// ----------------------------------------------------------------------------
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
	    .remaining = nullptr,
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
	    size_t len = (c-str) - 2 + 1; // remove beginning and ending '"'
	    // and add null terminator
	    char* s = (char*)malloc(len * sizeof(char));
	    memcpy(s, str+1, len);
	    s[len-1] = '\0';
	    return (lexer_pair) {
		.token = (shsl_token) {
		    .type = SHSL_TOK_STRING,
		    .obj = shsl_obj_mkstr(s),
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
	.obj = &SHSL_NIL,
    };
}
// since we return errors as special token pairs, might as well have an
// ad hoc function for that
lexer_pair error_lexer_pair(const char* errmsg) {
    return (lexer_pair) {
	.token = (shsl_token) {
	    .type = SHSL_TOK_ERROR,
	    .obj = shsl_obj_mkstr(errmsg),
	},
	.remaining = nullptr,
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
	    .obj = shsl_obj_mkint(l),
	};

    if (len == 3 && c[0] == 'n' && c[1] == 'i' && c[2] == 'l')
	return (shsl_token) {
	    .type = SHSL_TOK_NIL,
	    .obj = &SHSL_NIL,
	};
	
    char* newstr = slice_to_fresh_str(c, len);
    shsl_token t =  (shsl_token) {
	.type = SHSL_TOK_SYMBOL,
	.obj = shsl_obj_mksym(newstr),
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
    char* fresh = (char*)malloc(len+1);
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
			   SHSL_TOK_CLOSE_PAREN,
			   (SHSL_TOKEN_TYPE[]){SHSL_TOK_CLOSE_SQUARE,
					       SHSL_TOK_CLOSE_CURLY},
			   2);
    case SHSL_TOK_OPEN_SQUARE: {
	parser_pair pp =
	    parse_until(lp.remaining,
			SHSL_TOK_CLOSE_SQUARE,
			(SHSL_TOKEN_TYPE[]){SHSL_TOK_CLOSE_PAREN,
					    SHSL_TOK_CLOSE_CURLY},
			2);
	return (parser_pair) {
	    .obj = shsl_obj_mkcons(shsl_obj_mksym("quotevec"),
				   shsl_obj_mkcons(pp.obj, &SHSL_NIL)),
	    .remaining = pp.remaining,
	};
    }
    case SHSL_TOK_OPEN_CURLY: {
	parser_pair pp =
	    parse_until(lp.remaining,
			SHSL_TOK_CLOSE_CURLY,
			(SHSL_TOKEN_TYPE[]){SHSL_TOK_CLOSE_PAREN,
					    SHSL_TOK_CLOSE_SQUARE},
			2);
	return (parser_pair) {
	    .obj = shsl_obj_mkcons(shsl_obj_mksym("quotemap"),
				   shsl_obj_mkcons(pp.obj, &SHSL_NIL)),
	    .remaining = pp.remaining,
	};
    }
	
	// handle quotes
    case SHSL_TOK_QUOTE: {
	parser_pair pp = parse_off(lp.remaining);
	return (parser_pair) {
	    .obj = shsl_obj_mkcons(shsl_obj_mksym("quote"),
				   shsl_obj_mkcons(pp.obj, &SHSL_NIL)),
	    .remaining = pp.remaining,
	};
    }
    case  SHSL_TOK_QUASIQUOTE: {
	parser_pair pp = parse_off(lp.remaining);
	return (parser_pair) {
	    .obj = shsl_obj_mkcons(shsl_obj_mksym("quasiquote"),
				   shsl_obj_mkcons(pp.obj, &SHSL_NIL)),
	    .remaining = pp.remaining,
	};
    }
    case  SHSL_TOK_COMMA: {
	parser_pair pp = parse_off(lp.remaining);
	return (parser_pair) {
	    .obj = shsl_obj_mkcons(shsl_obj_mksym("comma"),
				   shsl_obj_mkcons(pp.obj, &SHSL_NIL)),
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
    assert(0 && "unreachable");
}
parser_pair parse_until(char* str,
			SHSL_TOKEN_TYPE stop,
			SHSL_TOKEN_TYPE* error_on, size_t error_on_len) {
    shsl_obj* acc = &SHSL_NIL;
    shsl_obj* tail;

    // we only use this lexer_pair to peek the next token
    // if the next token is our stop token, we stop
    // if it's one of our error tokens, we error
    // otherwise we parse the next object on until we reach a stop token
    while(true) {
	lexer_pair lp = token_off(str);
	if(lp.token.type == stop)
	    return (parser_pair) {
		.obj = acc,
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
	if(acc->type == SHSL_OBJ_NIL) {
	    acc = shsl_obj_mkcons(pp.obj, &SHSL_NIL);
	    tail = acc;
	}
	else {
	    shsl_cons_set_cdr(tail, shsl_obj_mkcons(pp.obj, &SHSL_NIL));
	    tail = tail->cons.cdr;
	}

	str = pp.remaining;
    }
}


//// EVALUATOR DEFINITIONS
//// ----------------------------------------------------------------------------

/// EXPRESSION TYPE DEFINITIONS
typedef enum SHSL_EXPRESSION_TYPE {
    SHSL_EXPR_LITERAL,
    SHSL_EXPR_MAP,
    SHSL_EXPR_VECTOR,
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
} SHSL_EXPRESSION_TYPE;
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
typedef struct if_expr {
    shsl_expression* condition;
    shsl_expression* then_part;
    shsl_expression* else_part;
} if_expr;
typedef struct do_expr {
    shsl_expression* body;
    size_t body_length;
} do_expr;
typedef struct do_poking_expr {
    shsl_expression* body;
    size_t body_length;
} do_poking_expr;
typedef struct def_expr {
    shsl_obj* name;           // must be symbol
    shsl_expression* value;
} def_expr;
typedef struct set_expr {
    shsl_obj* name;           // must be symbol
    shsl_expression* value;
} set_expr;
typedef struct shsl_expression {
    SHSL_EXPRESSION_TYPE type;
    union {
	shsl_obj* literal;
	shsl_obj* lookup_symbol; // must be symbol
	shsl_obj* vec;           // must be vector
	shsl_obj* map;           // must be map

	if_expr if_expr;
	do_expr do_expr;
	do_poking_expr do_poking_expr;
	def_expr def_expr;
	set_expr set_expr;
    };
} shsl_expression;

/// EXPRESSION FUNCTION DEFINITIONS
// https://stackoverflow.com/questions/6750512/gcc-warning-iso-c-does-not-permit-named-variadic-macros
#define return_mallocd_expr(...) do {				\
	shsl_expression* expr =					\
	    (shsl_expression*)malloc(sizeof(shsl_expression));	\
	*expr = (shsl_expression){__VA_ARGS__};			\
	return expr;						\
    } while(0)

#ifdef SHSL_LOG_RETURN_ERROR_EXPR
#define return_error_expr(form, msg, ...) do{                           \
	fprintf(stderr, "[ERROR] WHILE PARSING: "msg"\n", __VA_ARGS__); \
	return &(shsl_expression) {                                     \
	    .type = SHSL_EXPR_LITERAL,                                  \
	    .literal = shsl_obj_mkerr(msg, form),                       \
	};                                                              \
    }while(0)
#else
// TODO, sprintf
#define return_error_expr(form, msg, ...) do{                           \
	return &(shsl_expression) {                                     \
	    .type = SHSL_EXPR_LITERAL,                                  \
	    .literal = shsl_obj_mkerr(msg, form),                       \
	};                                                              \
    }while(0)
#endif

/// FORM TRANSLATION FUNCTIONS DEFINITIONS
shsl_expression* shsl_form_to_expr(shsl_obj* form) {
    switch(form->type) {
    case SHSL_OBJ_INTEGER:
    case SHSL_OBJ_REAL:
    case SHSL_OBJ_STRING:
    case SHSL_OBJ_NIL:
	return_mallocd_expr(.type = SHSL_EXPR_LITERAL,
			    .literal = shsl_add_ref(form));

    case SHSL_OBJ_SYMBOL:
	return_mallocd_expr(.type = SHSL_EXPR_LOOKUP,
			    .lookup_symbol = shsl_add_ref(form));

    case SHSL_OBJ_VECTOR:
	return_mallocd_expr(.type = SHSL_EXPR_VECTOR,
			    .vec = shsl_add_ref(form));

    case SHSL_OBJ_MAP:
	return_mallocd_expr(.type = SHSL_EXPR_MAP,
			    .map = shsl_add_ref(form));

    case SHSL_OBJ_ERROR:
	return_error_expr
            (form, "an error object was passed to the parser");

    case SHSL_OBJ_CONS:
	if(form->cons.car->type == SHSL_OBJ_SYMBOL) {
	    if(!shsl_is_well_formed_list(form))
		return_error_expr
                    (form, "not well formed list, cannot parse into expression");

	    size_t form_length = (size_t)shsl_list_length(form);

	    char* s = form->cons.car->sym.name->str;
	    if(strcmp(s, "quote") == 0) {
		if(form_length != 2)
		    return_error_expr
			(form,
                         "malformed quote form, length of quote form must be "
			 "exactly 2, just the 'quote symbol and the quoted "
			 "datum");
		shsl_obj* literal = shsl_nth(form, 1);
		if(shsl_is_err(literal))
		    return_error_expr
                        (literal,
                         "cannot parse quote expression because"
                         "literal in quote was malformed");
		return_mallocd_expr(.type = SHSL_EXPR_LITERAL,
				    .literal = literal); 
	    }

	    else if(strcmp(s, "if") == 0) {
		if(form_length < 3)
		    return_error_expr
                        (form, "malformed if statement, too short");
		if(form_length > 4)
		    return_error_expr
                        (form, "malformed if statement, too long");
				
                // error expressions store the error value in the literal
                // field of their union
                // TODO: find a way to return propagating parser errors
                // that doesn't expose this detail this hard :( 
		shsl_expression* c = shsl_form_to_expr(shsl_nth(form, 1));
		if(shsl_expr_is_error(c))
		    return_error_expr
			(c->literal,
                         "cannot parse if form, malformed conditional!");
		shsl_expression* t = shsl_form_to_expr(shsl_nth(form, 2));
		if(shsl_expr_is_error(t))
		    return_error_expr
			(t->literal,
                         "cannot parse if form, malformed then part!");
		shsl_expression* e = shsl_form_to_expr(shsl_nth(form, 3));
		if(shsl_expr_is_error(e))
		    return_error_expr
			(e->literal,
                         "cannot parse if form, malformed else part!");

		return_mallocd_expr(.type = SHSL_EXPR_IF,
				    .if_expr = (if_expr) {
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
	    else
		assert(0 && "TODO: FUNCALL (symbol)");

	}
	// else if lambda_expr_p(c->cons.car)
	// { compile to immediate lambda call }
	// else
	// { error }
    }
    assert(0 && "UNREACHABLE");
}
bool shsl_expr_is_error(shsl_expression* expr) {
    return expr->type == SHSL_EXPR_LITERAL
	&& expr->literal->type == SHSL_OBJ_ERROR;
}

/// EVALUATION FUNCTION DEFINITIONS
shsl_obj* shsl_eval(shsl_expression* form, shsl_obj* env) {
    switch(form->type) {
    case SHSL_EXPR_LITERAL:
	return shsl_obj_copy(form->literal);
    case SHSL_EXPR_IF:
	if(shsl_is_truthy(shsl_eval(form->if_expr.condition, env)))
	    return shsl_eval(form->if_expr.then_part, env);
	else
	    return shsl_eval(form->if_expr.else_part, env);
    default:
	assert(0 && "TODO");
    }
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
    shsl_dbg_fputobj(tok->obj, stream);
}
void shsl_dbg_fputobj(const shsl_obj* obj, FILE* restrict stream) {
    switch(obj->type) {
    case SHSL_OBJ_INTEGER:
	fprintf(stream, "%ld_i", obj->i);
	break;
    case SHSL_OBJ_REAL:
	fprintf(stream, "%f_r", obj->r);
	break;
    case SHSL_OBJ_STRING:
	fprintf(stream, "%s_s", obj->str);
	break;
    case SHSL_OBJ_SYMBOL:
	fprintf(stream, "%s_sym", obj->sym.name->str);
	break;
    case SHSL_OBJ_NIL:
	fprintf(stream, "%s", "nil");
	break;
    case SHSL_OBJ_ERROR:
	fprintf(stream, "%s_err", obj->err.msg->str);
	break;
    case SHSL_OBJ_CONS:
	fputc('(', stream);
	shsl_dbg_fputobj(obj->cons.car, stream);
	fputc(' ', stream); fputc('.', stream); fputc(' ', stream); 
	shsl_dbg_fputobj(obj->cons.cdr, stream);
	fputc(')', stream);
	break;
    case SHSL_OBJ_VECTOR:
    case SHSL_OBJ_MAP:
	fprintf(stderr, "NOT HANDLED YET");
    };
}

#ifdef SHSL_MAIN
int main(int argc, char** argv) {
    // main is currently just testing the lexer
    // it will soon be just testing the parser
    // and when I have enough of a soul to throw at the wind
    // I'll move this shit into some unit tests
    char* text;
    if(argc > 1)
	text = argv[1];
    else
	// text = "(hello [goodbye] {{hello}} \"goodbye\") {{}} (+ 1 2)";
	text = "(if 'a 'b 'c)";

    printf("parsing \"%s\"\n", text);
    parser_pair p = parse_off(text);

    while(p.obj != (shsl_obj*){0} && p.remaining != (char*){0}) {
	shsl_dbg_fputobj(p.obj, stdout);
	putc('\n', stdout);

	shsl_expression* exp = shsl_form_to_expr(p.obj);
	(void)exp;

	shsl_obj* obj = shsl_eval(exp, &SHSL_NIL);
	// (void)obj;
	shsl_dbg_fputobj(obj, stdout);

	parser_pair pp = parse_off(p.remaining);
	p.obj = pp.obj;
	p.remaining = pp.remaining;
    }

    return 0;
}
#endif // SHSL_MAIN

#endif // SHSL_IMPLEMENTATION
#endif // SHSL_H
