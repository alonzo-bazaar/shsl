// api for calling shsl_main is a bit hairy atm
// the workflow this api is designed for is
// 
// # shsl env creation
// shsl_main() takes a reference to an environment object which represents the
// state of the runtime within which shsl_main will launch and within which the
// all the various bits of code and command line arguments you pass to shsl_main()
// will run and do their thing
// 
// int main(), or whatever subroutine in its stead, are responsible for creating
// and populating this shsl runtime environment before passing it to shsl_main()
// 
// to do int main() should initially create an empty environment then populate it
// as it sees fit, shsl provides various shsl_env_add_... functions that take an
// environment and add a bunch of definitions to that environment, this same
// mechanism may also be used by other C or lisp libraries built on top of shsl
// to provide a way for their user to add that library to shsl's runtime before
// launching the shsl interpreter
// 
// # command line argument parsing
// to avoid being too constraining as to what command line flags a program calling
// shsl_main() can take, shsl_main() takes the cli flags it's gonna parse as 
// - argc and argv, with the original argv[0] shifted out
// - program name (argv[0]), as a separate parameter
//
// this is to allow int main() to parse its own flags and do whatever it needs do
// with then, get to the part of argv meant for shsl, shift everything else 
// out, then pass the shifted flags to shsl_main()

#define SHSL_IMPLEMENTATION
#include "shsl.h"

// #define SHSL_EXEC_IMPLEMENTATION
// #include "shsl_exec.h"

// #define SHSL_FS_IMPLEMENTATION
// #include "shsl_fs.h"

#define ARGS_SHIFT(argc, argv) do { argv++; argc--; } while(0)
#define ARGS_SHIFT_BY(argc, argv, n) do { argv+=n; argc-=n; } while(0)

int main(int argc, char** argv) {
    shsl_ref env = shsl_ref_add(shsl_env_mkempty());
    shsl_env_add_initial_definitions(env);
    shsl_env_eval_stdlib(env);
    // shsl_add_exec_defs(env);
    // shsl_add_fs_defs(env);

    const char* shsl_program_name = argv[0];
    ARGS_SHIFT(argc, argv);
    int ret = shsl_main(env, shsl_program_name, argc, argv);
    shsl_ref_drop(env);
    // shsl_free(env);
    return ret;
}
