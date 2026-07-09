// namespacing shit
#define SHSL_SHORT_NAMES
#define SHSL_IMPL_

#ifndef SHSL_SHORT_NAMES
#define SHSL_DEC_FN(ret, name, args)		\
    ret shsl_##name args

#define SHSL_DEC_ENUM(name, ...)			\
    typedef enum SHSL_##name { __VA_ARGS__ } SHSL_##name

#define SHSL_DEC_STRUCT(name)			\
    struct shsl_##name;				\
    typedef struct shsl_##name shsl_##name

#define SHSL_DEC_CONST(type, name, val)		\
    type SHSL_##name = val

#else
#define SHSL_DEC_FN(ret, name, args)		\
    ret shsl_##name args;			\
    const ret(*name)args = shsl_##name

#define SHSL_DEC_STRUCT(name)			\
    struct shsl_##name;				\
    typedef struct shsl_##name shsl_##name;	\
    typedef shsl_##name name

#define SHSL_DEC_ENUM(name, ...)				\
    typedef enum SHSL_##name { __VA_ARGS__ } SHSL_##name;	\
    typedef SHSL_##name name

#define SHSL_DEC_CONST(type, name, val)		\
    type SHSL_##name = val;			\
    type name = SHSL_##name
#endif


#ifndef SHSL_H_
#define SHSL_H_
SHSL_DEC_FN(int, get_int, (int a));

SHSL_DEC_ENUM(TYPE,
	      SHSL_INT,
	      SHSL_REAL,
	      SHSL_KITEMMUORT,);

SHSL_DEC_STRUCT(ref);
SHSL_DEC_STRUCT(obj);
#endif // SHSL_H_

#ifdef SHSL_IMPL_
int shsl_get_int(int a) {
    return a;
}
typedef struct shsl_obj {
    int fuck_you;
} shsl_obj;
typedef struct shsl_ref {
    shsl_obj* ptr;
} shsl_ref;
#endif // SHSL_IMPL_
