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
typedef enum {
	// atoms
	// nil first so an object initialized as {0} is nil
	SHSL_OBJ_NIL = 0, SHSL_OBJ_SYMBOL, 
	SHSL_OBJ_INTEGER, SHSL_OBJ_REAL, SHSL_OBJ_STRING,

	// composite
	SHSL_OBJ_CONS, SHSL_OBJ_MAP, SHSL_OBJ_VECTOR,
} SHSL_OBJECT_TYPE;

struct shsl_obj;

typedef struct shsl_cons {
	struct shsl_obj* car;
	struct shsl_obj* cdr;
} shsl_cons ;

typedef struct shsl_sym {
	const char* name;
} shsl_sym ;

typedef struct shsl_obj {
	// header
	int ref_count;
	SHSL_OBJECT_TYPE type;

	// data
	union {
		// void* nil; // I just need something to mark nil
		long i;
		double r;
		const char* str;
		struct shsl_cons cons;
		struct shsl_sym sym;
	};
} shsl_obj;	


const shsl_obj SHSL_NIL = {0};
// shsl_obj shsl_obj_mknil()
// { return (shsl_obj){ .ref_count = 0, .type = SHSL_OBJ_NIL, .nil = 0, }; }

void shsl_free_obj(shsl_obj *obj) {
	switch(obj->type) {
	case SHSL_OBJ_NIL:
		fprintf(stderr, "cannot free NIL! You fucked something up!\n");
		break;
	case SHSL_OBJ_CONS:
		if(obj->cons.car->type != SHSL_OBJ_NIL)
			shsl_free_obj(obj->cons.car);
		if(obj->cons.cdr->type != SHSL_OBJ_NIL)
			shsl_free_obj(obj->cons.cdr);
		free(obj);
	default:
		free(obj);
	}
}

void shsl_add_ref(shsl_obj* obj) {
	if(obj->type != SHSL_OBJ_NIL)
		obj->ref_count++;
}
void shsl_del_ref(shsl_obj* obj) {
	if(obj->type != SHSL_OBJ_NIL) {
		obj->ref_count--;
		if(obj->ref_count == 0)
			shsl_free_obj(obj);
	}
}

// the shsl_obj_mk* functions all return references to fresh objects
// although those objects may contain references to pre-existing objects
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
		{ .ref_count = 0, .type = SHSL_OBJ_STRING, .str = str, };
	return obj_p;
}
shsl_obj* shsl_obj_mksym(const char* name) {
	shsl_obj* sym_obj = (shsl_obj*)malloc(sizeof(shsl_obj));
	*sym_obj = (shsl_obj) {
		.ref_count = 0,
		.type = SHSL_OBJ_SYMBOL,
		.sym = (shsl_sym) { .name = name }
	};
	return sym_obj;
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
	const shsl_obj* obj;
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
	
	return (shsl_token) {
		.type = SHSL_TOK_SYMBOL,
		.obj = shsl_obj_mksym(slice_to_fresh_str(c, len)),
	};
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
// the parser returns shsl objects, there is no separate expression type
typedef struct {
	shsl_obj* obj;
	char* remaining;
} parser_pair;
parser_pair parse_off(char* str) {
	assert(false);
}
parser_pair parse_until(char* str,
						SHSL_TOKEN_TYPE stop,
						SHSL_TOKEN_TYPE* error_on, size_t error_on_len) {
	assert(false);
}

// evaluator (also also leaks like a motherfucker)
//

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
	};
}

void shsl_dbg_fputtok(const shsl_token* tok, FILE* restrict stream) {
	fputs("token ", stream);
	switch(tok->type) {
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
		text = "(hello [bois {parte ''lo show";

	printf("tokenizing \"%s\"\n", text);
	lexer_pair p = token_off(text);
	while(p.token.type != SHSL_TOK_EOF) {
		shsl_dbg_fputtok(&p.token, stdout);
		putc(' ', stdout);
		printf("\"%s\"\n", p.remaining);

		p = token_off(p.remaining);
	}

	return 0;
}
