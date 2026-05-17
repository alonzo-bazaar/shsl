#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include<ctype.h>
#include<string.h>
#include<assert.h>

/* this is a first version of the code where the automatic memory management
 * is done through (some rather naive) reference cocunting
 * 
 * this first version is meant to have a first non leaking version of the
 * interpreter with some support for automatic memory management
 * 
 * once it's developed further we plan to replace the hardcoded refcounting with
 * a more generic gc interface offering greater flexibility in ways to manage
 * memory
 * because generational collectors look cool as fuck
 */

// definitions of shsl values 
// we handle everything through pointers because havnig everything
// on the heap makes it easier to automatically manage
typedef enum {
	// atoms
	// nil first so an object initialized as {0} is nil
	SHSL_OBJ_NIL = 0, SHSL_OBJ_SYMBOL, 
	SHSL_OBJ_INTEGER, SHSL_OBJ_REAL, SHSL_OBJ_STRING,

	SHSL_OBJ_ERROR,

	// composite
	SHSL_OBJ_CONS, SHSL_OBJ_MAP, SHSL_OBJ_VECTOR,
} SHSL_OBJECT_TYPE;

struct shsl_obj;

typedef struct shsl_sym {
	shsl_obj* name; // must be string
} shsl_sym ;

typedef struct shsl_error {
	shsl_obj* msg; // must be string
	shsl_obj* parent;
} shsl_error;

typedef struct shsl_cons {
	struct shsl_obj* car;
	struct shsl_obj* cdr;
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
		// void* nil; // I just need something to mark nil
		long i;
		double r;
		char* str;
		shsl_cons cons;
		shsl_sym sym;
		shsl_vec vec;
		shsl_map map;
	};
} shsl_obj;	

shsl_obj SHSL_NIL = {0};
// shsl_obj shsl_obj_mknil()
// { return (shsl_obj){ .ref_count = 0, .type = SHSL_OBJ_NIL, .nil = 0, }; }

void shsl_add_ref(shsl_obj* obj);
void shsl_del_ref(shsl_obj* obj);
void shsl_free_obj(shsl_obj* obj);

void shsl_add_ref(shsl_obj* obj) {
	if(obj->type != SHSL_OBJ_NIL)
		obj->ref_count++;
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

	case SHSL_OBJ_ERR:
		shsl_del_ref(obj->err.name);
		shsl_del_ref(obj->err.parent);
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

	case SHSL_OBJ_MAP:
		for(size_t i = 0; i<obj->map.size; ++i) {
			shsl_del_ref(obj->map.buf[i]->k);
			shsl_del_ref(obj->map.buf[i]->v);
		}
		free(obj->map.buf);
		free(obj);
		break;

	default:
		free(obj);
		break;
	}
}

// the shsl_obj_mk* functions all return references to fresh objects
// although those objects may contain references to pre-existing objects
// if they're cons cells, vectors, or maps
// 
// all raw C data passed to an shsl_obj_mk* constructor
// (numbers, chars, strings (both strings and symbol names))
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
	*obj_p = (shsl_obj)
		{
			.ref_count = 0,
			.type = SHSL_OBJ_STRING,
			.str = strcpy(str),
		};
	return obj_p;
}

shsl_obj* shsl_obj_mksym(const char* name) {
	shsl_obj* sym_obj = (shsl_obj*)malloc(sizeof(shsl_obj));
	*sym_obj = (shsl_obj) {
		.ref_count = 0,
		.type = SHSL_OBJ_SYMBOL,
		.sym = (shsl_sym) {
			.name = shsl_obj_mkstr(name),
		},
	};
	return sym_obj;
}

shsl_obj* shsl_obj_mkerr(const char* msg, shsl_obj* parent) {
	assert(parent->type == SHSL_OBJ_ERROR);
	shsl_add_ref(parent);

	shsl_obj* err_obj = (shsl_obj*)malloc(sizeof(shsl_obj));
	*err_obj = (shsl_obj) {
		.ref_count = 0,
		.type = SHSL_OBJ_ERROR,
		.err = (shsl_error) {
			.msg = strcpy(msg),
			.parent = parent
		}
	};
	return err_obj;
}

shsl_obj* shsl_obj_mkcons(shsl_obj* car, shsl_obj* cdr) {
	shsl_obj* cons_obj = (shsl_obj*)(malloc)(sizeof(shsl_obj));
	*cons_obj = (shsl_obj) {
		.ref_count = 0,
		.type = SHSL_OBJ_CONS,
		.cons = (shsl_cons) { .car = car, .cdr = cdr, }
	};
	shsl_add_ref(car);
	shsl_add_ref(cdr);
	return cons_obj;
}
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

shsl_obj* shsl_obj_mkvec(size_t initial_capacity) {
	assert(initial_capacity > 0);

	shsl_obj* obj_p = (shsl_obj*)malloc(sizeof(shsl_obj));
	*obj_p = (shsl_obj) {
		.ref_count = 0,
		.type = SHSL_OBJ_VECTOR,
		.vec = (shsl_vec) {
			.buf = (shsl_obj**) malloc(initial_capacity * sizeof(shsl_obj*)),
			.size = 0,
			.capacity = initial_capacity
		};
	}
	return obj_p;
}
void shsl_vec_expand(shsl_obj* vec_obj, size_t new_size) {
	assert(cons_obj->type == SHSL_OBJ_VECTOR);

	if(vec_obj->vec.capacity >= new_size) return;

	vec_obj->vec.buf = (shsl_obj**)realloc(vec_obj->vec.buf,
										   new_size*sizeof(shsl_obj*));
	vec_obj->vec.capacity = new_size;
}
void shsl_vec_push(shsl_obj* vec_obj, shsl_obj* obj) {
	assert(cons_obj->type == SHSL_OBJ_VECTOR);

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
shsl_obj* shsl_vec_ref(shsl_obj* vec_obj, size_t i) {
	assert(cons_obj->type == SHSL_OBJ_VECTOR);

	if(i >= vec_obj->vec.size)
		return shsl_obj_mkerr("out of bounds array read!", nullptr);

	return vec_obj->vec[i];
}
void shsl_vec_set(shsl_obj* vec_obj, size_t i, shsl_obj* new_val) {
	assert(cons_obj->type == SHSL_OBJ_VECTOR);

	if(i >= vec_obj->vec.size)
		return shsl_obj_mkerr("out of bounds array write!", nullptr);

	shsl_add_ref(new_val);
	shsl_del_ref(vec_obj->vec[i]);
	vec_obj->vec[i] = new_val;
}

shsl_obj* shsl_obj_mkmap_empty(size_t initial_capacity) {
	shsl_obj* obj_p = (shsl_obj*)malloc(sizeof(shsl_obj));
	*obj_p = (shsl_obj) {
		.ref_count = 0,
		.type = SHSL_OBJ_MAP,
		.map = (shsl_map){
			.buf = (shsl_kv*)malloc(initial_capacity * sizeof(shsl_kv));,
			.size = 0,
			.capacity = initial_capacity,
		}
	};
	return obj_p;
}
void shsl_map_expand(shsl_obj* map_obj, size_t new_size) {
	assert(cons_obj->type == SHSL_OBJ_MAP);

	if (map_obj->map.capacity >= new_size) return;

	map_obj->map.buf = (shsl_obj**)realloc(map_obj->map.buf,
										   new_size*sizeof(shsl_kv));
	map_obj->map.capacity = new_size;
}

bool shsl_obj_eq(shsl_obj* lhs, shsl_obj* rhs);

ssize_t shsl_map_index(shsl_obj* map_obj, shsl_obj* key) {
	assert(cons_obj->type == SHSL_OBJ_MAP);

	for(ssize_t i = 0; i<map_obj->map.size; ++i)
		if(shsl_obj_eq(key, map_obj->map.buf[i].k))
			return i;
	return -1;
}

shsl_obj* shsl_map_get(shsl_obj* map_obj, shsl_obj* key) {
	assert(cons_obj->type == SHSL_OBJ_MAP);

	ssize_t i = shsl_map_index(map_obj, key);
	if(i>=0) return map_obj->map.buf[i];
	return &SHSL_NIL;
}
shsl_obj* shsl_map_set(shsl_obj* map_obj, shsl_obj* key, shsl_obj* new_val) {
	assert(cons_obj->type == SHSL_OBJ_MAP);

	ssize_t i = shsl_map_index(map_obj, key);
	if(i>=0) {
		shsl_add_ref(new_val);
		shsl_del_ref(map_obj->buf[i].v);
		map_obj->buf[i].v = new_val;
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
			.key = key;
			.val = new_val;
		}
	}
}

bool shsl_obj_eq(shsl_obj* lhs, shsl_obj* rhs) {
	if(lhs->type != rhs->type) return false;
	switch(lhs->type) {
	case SHSL_OBJ_NIL:
		return true;
	case SHSL_OBJ_SYMBOL:
		return strcmp(lhs->sym.name, rhs->sym.name) == 0;

	case SHSL_OBJ_INTEGER:
		return lhs->i == rhs->i;
	case SHSL_OBJ_REAL:
		return lhs->r == rhs->r;
	case SHSL_OBJ_STRING:
		return strcmp(lhs->s, rhs->s) == 0;

	case SHSL_OBJ_CONS:
		return shsl_obj_eq(lhs->cons.car, rhs->cons.car)
			&& shsl_obj_eq(lhs->cons.cdr, rhs->cons.cdr);

	case SHSL_OBJ_VECTOR:
		if(lhs->vec.size != rhs->vec.size) return false;
		for(size_t i = 0; i<lhs->vec.size; ++i)
			if(!shsl_obj_eq(lhs->vec[i], rhs->vec[i])) return false;
		return true

	case SHSL_OBJ_MAP:
		if(lhs->map.size != rhs->map.size) return false;
	}
}

// lexer
typedef enum {
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

typedef struct {
	SHSL_TOKEN_TYPE type;
	shsl_obj* obj;
} shsl_token;
typedef struct {
	shsl_token token;
	char* remaining;
} lexer_pair;

// we're gonna return a lot of tokens where we only care about the type
// and the underlying object is of little use
// so...
shsl_token empty_token(SHSL_TOKEN_TYPE token_type) {
	return (shsl_token) {
		.type = token_type,
		.obj = &SHSL_NIL,
	};
}

// and since we return errors as special token pairs, might as well have an
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
// as of now it's any non whitespace printable character
// that's not a special char for the language
bool is_symbol_char(char c) {
	return isprint(c) && (!isspace(c)) && (!is_special_char(c));
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
const char* slice_to_fresh_str(const char* c, size_t len) {
	char* fresh = (char*)malloc(len+1);
	memcpy(fresh, c, len);
	fresh[len] = '\0';
	return fresh;
}

// non special tokens are either symbols or numbers
// (we only support integers rn)
// try parsing (c - c+len) as a number, if it fails return it as a symobol
// a symbol named nil will not return a symbol but a special nil token
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
	
	char* c = slice_to_fresh_str(c, len);
	shsl_token t =  (shsl_token) {
		.type = SHSL_TOK_SYMBOL,
		.obj = shsl_obj_mksym(c),
	};
	free(c);
	return t;
}

lexer_pair token_off(char* str) {
	// handle null pointer string
	if(!str)
		return error_lexer_pair("cannot read null pointer to string!");

	// handle empty string (we reached the null terminator)
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
	};

	// if we got here then it's not a special char
	// it's either a symbol or a number
	char* c = str;
	while(is_symbol_char(*c)) c++;

	return (lexer_pair){
		.token = parse_non_special_token(str, c-str),
		.remaining = c,
	};
}

// parser (also leaks like a motherfucker)
// the parser returns shsl objects
typedef struct {
	shsl_obj* obj;
	char* remaining;
} parser_pair;

parser_pair parse_off(char* str);
parser_pair parse_until(char* str,
						SHSL_TOKEN_TYPE stop,
						SHSL_TOKEN_TYPE* error_on, size_t error_on_len);

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

// evaluator (also also leaks like a motherfucker)
//
typedef enum {
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

struct shsl_expressoin {
	SHSL_EXPRESSION_TYPE type;
	union {
		shsl_obj* literal;
		shsl_obj* lookup_symbol; // must be symbol
		shsl_obj* vec;           // must be vector
		shsl_obj* map;           // must be map

		struct {
			shsl_expression conditoin;
			shsl_expression then_part;
			shsl_expression else_part;
		} if_expr;

		struct {
			shsl_expression* body;
			size_t body_length;
		} do_expr;

		struct {
			shsl_expression* body;
			size_t body_length;
		} do_poking_expr;

		struct {
			shsl_obj* name;           // must be symbol
			shsl_exppression* value;
		} def_expr;

		struct {
			shsl_obj* name;           // must be symbol
			shsl_exppression* value;
		} set_expr;
	}
}


// print debugging
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
		fprintf(stream, "%s_sym", obj->sym.name);
		break;
	case SHSL_OBJ_NIL:
		fprintf(stream, "%s", "nil");
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

int main(int argc, char** argv) {
	// main is currently just testing the lexer
	// it will soon be just testing the parser
	// and when I have enough of a soul to throw at the wind
	// I'll move this shit into some unit tests
	char* text;
	if(argc > 1)
		text = argv[1];
	else
		text = "(hello [goodbye] {{hello}} \"goodbye\") {{}} (+ 1 2)";

	printf("parsing \"%s\"\n", text);
	parser_pair p = parse_off(text);

	while(p.obj != (shsl_obj*){0} && p.remaining != (char*){0}) {
		shsl_dbg_fputobj(p.obj, stdout);
		putc('\n', stdout);
		parser_pair pp = parse_off(p.remaining);
		p.obj = pp.obj;
		p.remaining = pp.remaining;
	}

	return 0;
}
