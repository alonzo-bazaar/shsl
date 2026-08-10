#ifndef SHSL_H
#error "shsl_exec.h should be included after shsl.h"
#endif

#ifndef SHSL_EXEC_H
#define SHSL_EXEC_H
#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<assert.h>
#include<string.h>
#include<errno.h>

#if defined(SHSL_UNIX)
#include<unistd.h>   // fork, exec, pipe &Co.
#include<sys/wait.h> // waitpid &Co.

#elif defined(SHSL_WIN32)
#include<windows.h>  // win32 and a lot of prayers

#else
#error "unsupported platform!"
#endif

// common api between unix and win32 versions of shsl_exec
// shsl facing api
int shsl_exec(int argc, char** argv);
int shsl_exec_into_strs(int argc, char** argv, char** outp, char** errp);

// shsl builtins made from the above (and subroutines thereof)
shsl_ref shsl_fn_assert_arg_strvec(const char* caller, shsl_ref arg);
void shsl_strvec_to_argc_argv(shsl_ref strvec, int* argc_ptr, char*** argv_ptr);

shsl_ref shsl_builtin_exec_vec(shsl_ref args, shsl_ref env);
shsl_ref shsl_builtin_exec_vec_strs(shsl_ref args, shsl_ref env);

// user facing api
shsl_ref shsl_env_add_exec_definitions(shsl_ref env);
shsl_ref shsl_env_eval_execlib(shsl_ref env);

#define shsl_log_errno()                                \
    fprintf(stderr, "at line %d of file %s" SHSL_NL     \
            "errno is %d: meaning %s" SHSL_NL SHSL_NL,  \
            __LINE__, __FILE__, errno, strerror(errno))

// error reporting wrappers
// 'cause I end up always writing the same error reporting code for every posix
// call I have to invoke so might as well make it reusable
#define SHSL_SYSCALL_WARN_ON_FAIL(...) \
    shsl_syscall_warn(__VA_ARGS__, #__VA_ARGS__, __LINE__, __FILE__)
int shsl_syscall_warn(int call_ret, const char* callexpr,
                      int linenum, const char* filename);

// as a convention throughout this library
// the all caps edition of a syscall or sycall equivalent means it's that
// same call, but with error reporting wrapped around it
// 
// shsl_exec and shsl_exec_into_strs are made to have the same error returns
// as posix call, meaning I can reuse my posix targeting error reporting wrappers
#define SHSL_EXEC(...) \
    SHSL_SYSCALL_WARN_ON_FAIL(shsl_exec(__VA_ARGS__))
#define SHSL_EXEC_INTO_STRS(...) \
    SHSL_SYSCALL_WARN_ON_FAIL(shsl_exec_into_strs(__VA_ARGS__))

#if defined(SHSL_UNIX)
// unix specific helper functions for shsl_exec
pid_t shsl_spawn(int argc, char** argv);

// unix specific helper functions for shsl_exec_into_strs
// (we're gonna need pipes)
// 
// when calling pipe on an int[2]
// [0] = read end, [1] = write end
// I never remember these so might as well
#define shsl_pipe_read_end(pipe) (pipe[0]) 
#define shsl_pipe_write_end(pipe) (pipe[1]) 
int shsl_close_pipe(int pipe[2]);
int shsl_grab_stdin_from_pipe(int pipe[2]);  // bind stdin  to read  end of pipe
int shsl_grab_stdout_from_pipe(int pipe[2]); // bind stdout to write end of pipe
int shsl_grab_stderr_from_pipe(int pipe[2]); // bind stderr to write end of pipe

#define SHSL_PIPE(...)    SHSL_SYSCALL_WARN_ON_FAIL(pipe(__VA_ARGS__))
#define SHSL_DUP2(...)    SHSL_SYSCALL_WARN_ON_FAIL(dup2(__VA_ARGS__))
#define SHSL_FORK(...)    SHSL_SYSCALL_WARN_ON_FAIL(fork(__VA_ARGS__))
#define SHSL_WAITPID(...) SHSL_SYSCALL_WARN_ON_FAIL(waitpid(__VA_ARGS__))
#define SHSL_CLOSE(...)   SHSL_SYSCALL_WARN_ON_FAIL(close(__VA_ARGS__))
#define SHSL_READ(...)    SHSL_SYSCALL_WARN_ON_FAIL(read(__VA_ARGS__))
void SHSL_EXECVP(char** argv) {
    SHSL_SYSCALL_WARN_ON_FAIL(execvp(*argv, argv));
    shsl_die(EXIT_FAILURE, "royally fucked some shit up, "
             "child process somehow returned from execvp call");
}

#define SHSL_SPAWN(...) SHSL_SYSCALL_WARN_ON_FAIL(shsl_spawn(__VA_ARGS__))
#define SHSL_CLOSE_PIPE(...) \
    SHSL_SYSCALL_WARN_ON_FAIL(shsl_close_pipe(__VA_ARGS__));
#define SHSL_GRAB_STDIN_FROM_PIPE(...)  \
    SHSL_SYSCALL_WARN_ON_FAIL(shsl_grab_stdin_from_pipe(__VA_ARGS__))
#define SHSL_GRAB_STDOUT_FROM_PIPE(...) \
    SHSL_SYSCALL_WARN_ON_FAIL(shsl_grab_stdout_from_pipe(__VA_ARGS__))
#define SHSL_GRAB_STDERR_FROM_PIPE(...) \
    SHSL_SYSCALL_WARN_ON_FAIL(shsl_grab_stderr_from_pipe(__VA_ARGS__))

#elif defined(SHSL_WIN32)
// win32 specific helper functions for shsl_exec 
// escaping shit! :D
bool shsl_is_char_special_for_cmd_exe(char c);
void shsl_sb_win32_escaped_push(shsl_string_builder* sb, char c, bool cmd_exe);
void shsl_cmd_push_quoted_win32_arg(const char* arg, shsl_string_builder* sb,
                                    bool cmd_exe);
char* shsl_cmd_to_win32_str(int argc, char** argv, bool cmd_exe);
#ifdef __cplusplus
}
#endif
#endif // defined(SHSL_UNIX)
#endif // SHSL_EXEC_H

#ifdef SHSL_EXEC_IMPLEMENTATION
// this is mostly posix specific but we use it a bit for the common api
// so it's defined outside of any system specific ifdef
int shsl_syscall_warn(int call_ret, const char* callexpr,
                      int linenum, const char* filename) {
    if(call_ret == -1) {
        shsl_log_warn("system call %s", callexpr);
        shsl_log_warn("at line %d of file %s", linenum, filename);
        shsl_log_warn("returned %d", call_ret);
        shsl_log_warn("errno is %d (%s)"SHSL_NL, errno, strerror(errno));
    }
    return call_ret;
}

// implmentation of the unix specific shit
#if defined(SHSL_UNIX)
pid_t shsl_spawn(int argc, char** argv) {
    if(argc == 0)
        return -1;
    if(argv[argc] != NULL) {
        shsl_log_err("argv not properly null terminated!");
        return -1;
    }

    pid_t pid = SHSL_FORK();
    if(pid == -1)     // parent branch, failed to create child
        return -1;
    else if(pid != 0) // parent branch, child created succesfully
        return pid;
    else {            // child branch
        SHSL_EXECVP(argv);
        exit(EXIT_FAILURE);
    }
}

// runs one command and blocks until command is done
// returns exit code of command, or -1 if a failure occured
int shsl_exec(int argc, char** argv) {
    pid_t child_pid = SHSL_SPAWN(argc, argv);
    if(child_pid == -1)
        return -1;

    int child_ret = -1;
    pid_t p =  SHSL_WAITPID(child_pid, &child_ret, 0);
    if(p == -1)
        return -1;
    return child_ret;
}

int shsl_close_pipe(int pipe[2]) {
    int c1 = SHSL_CLOSE(shsl_pipe_read_end(pipe));
    int c2 = SHSL_CLOSE(shsl_pipe_write_end(pipe)); 
    return (c1 == -1 || c2 == -1)?-1:0;
}
int shsl_grab_stdin_from_pipe(int pipe[2]) {
    int c = SHSL_DUP2(shsl_pipe_read_end(pipe), STDIN_FILENO);
    int d = SHSL_CLOSE_PIPE(pipe);
    return (d == -1 || c == -1)?-1:0;
}
int shsl_grab_stdout_from_pipe(int pipe[2]) {
    int d = SHSL_DUP2(shsl_pipe_write_end(pipe), STDOUT_FILENO);
    int c = SHSL_CLOSE_PIPE(pipe);
    return (d == -1 || c == -1)?-1:0;
}
int shsl_grab_stderr_from_pipe(int pipe[2]) {
    int d = SHSL_DUP2(shsl_pipe_write_end(pipe), STDERR_FILENO);
    int c = SHSL_CLOSE_PIPE(pipe);
    return (d == -1 || c == -1)?-1:0;
}


// returns
// negative        (-1) -> some error happened in the fork/exec/read et al.
//                         that is, in the whole infrastructure this code puts
//                         around the child process to exec it into string 
//                         
// zero             (0) -> success
//
// positive (1, 2, ...) -> success in calling and waiting and all but
//                         after all of that the child itself returned
//                         with an error (non zero exit code)
int shsl_exec_into_strs(int argc, char** argv, char** outp, char** errp) {
    if(argv[argc] != NULL) {
        shsl_log_err("argv not properly null terminated!");
        return -1;
    }

    int* out_p = (int*)calloc(2, sizeof(int)); // pipe where child stdout will go
    memset(out_p, 0, 2*sizeof(int));
    int* err_p = (int*)calloc(2, sizeof(int)); // pipe where child stderr will go
    memset(err_p, 0, 2*sizeof(int));

    int ret = -1;
    if(SHSL_PIPE(out_p) == -1)
        goto end;
    if(SHSL_PIPE(err_p) == -1)
        goto end;

    pid_t kid = SHSL_FORK();
    if(kid == -1)
        goto end;
    if(kid == 0) {
        if(SHSL_GRAB_STDOUT_FROM_PIPE(out_p) == -1)
            shsl_die(EXIT_FAILURE,
                     "child failed to bind stdout to pipe output" SHSL_NL);
        if(SHSL_GRAB_STDERR_FROM_PIPE(err_p) == -1)
            shsl_die(EXIT_FAILURE,
                     "child failed to bind stderr to pipe output" SHSL_NL);
        SHSL_EXECVP(argv);
    }
    else {
        if(SHSL_CLOSE(shsl_pipe_write_end(out_p)) == -1) {
            SHSL_CLOSE(shsl_pipe_read_end(out_p));
            SHSL_CLOSE_PIPE(err_p);
            shsl_log_err("error in parent while closing child stdout pipe");
            goto end;
        }
        if(SHSL_CLOSE(shsl_pipe_write_end(err_p)) == -1) {
            SHSL_CLOSE(shsl_pipe_read_end(err_p));
            shsl_log_err("error in parent while closing child stdout pipe");
            goto end;
        }

        int out_pr = shsl_pipe_read_end(out_p);
        int err_pr = shsl_pipe_read_end(err_p);

        char buf[1024];
        ssize_t s;
        
        shsl_string_builder out_sb = {0};
        shsl_string_builder err_sb = {0};

        // read child stdout
        for(s = SHSL_READ(out_pr, buf, 1024);
            s>0;
            s = SHSL_READ(out_pr, buf, 1024))
            shsl_sb_push_sized_str(&out_sb, buf, (size_t)s);

        if(s==-1) {
            shsl_log_err("failure while reading child standard output");
            shsl_log_errno();
            if(out_sb.buf) free(out_sb.buf);
            SHSL_CLOSE(out_pr);
            SHSL_CLOSE(err_pr);
            goto end;
        }

        // read child stderr
        for(s = SHSL_READ(err_pr, buf, 1024);
            s>0;
            s = SHSL_READ(err_pr, buf, 1024))
            shsl_sb_push_sized_str(&err_sb, buf, (size_t)s);

        if(s==-1) {
            shsl_log_err("failure while reading child standard error");
            shsl_log_errno();
            if(out_sb.buf) free(out_sb.buf);
            if(err_sb.buf) free(err_sb.buf);
            SHSL_CLOSE(err_pr);
            SHSL_CLOSE(err_pr);
            goto end;
        }

        SHSL_CLOSE(out_pr);
        SHSL_CLOSE(err_pr);
        shsl_sb_push(&out_sb, '\0');
        shsl_sb_push(&err_sb, '\0');
        *outp = shsl_sb_get(&out_sb);
        *errp = shsl_sb_get(&err_sb);

        // wait child and get child exit code
        int child_exit_code = -1;
        pid_t p =  SHSL_WAITPID(kid, &child_exit_code, 0);

        // if waitpid call somehow failed, return generic failure
        // that is, -1, as the default error value set above
        if(p == -1)
            goto end;
        
        // otherwise return whatever the child exited with
        // this will keep our logic of
        // > it's 0 if it succeds and non zero if it fails
        // but for values greater than 1 it returns the extra information of
        // > what did the child process exit with?
        ret = child_exit_code;
    }
 end:
    free(out_p);
    free(err_p);
    return ret;
}

// implmentation of the win32 specific shit
#elif defined(SHSL_WIN32)
// https://learn.microsoft.com/en-gb/archive/blogs/twistylittlepassagesallalike/everyone-quotes-command-line-arguments-the-wrong-way
// https://github.com/tsoding/nob.h/blob/0a08926d8094fc4ae678155c5d73ae21d1f96f3f/nob.h#L1182
// https://github.com/python/cpython/blob/11a8bdfe4833bbaecba5e4ef04d047d0a979a6ca/Lib/subprocess.py#L697

// the aim of the following bunch of functions is to translate a command
// argc and argv (mainly argv) into a command line string string we can pass to
// the win32 api
// in windows there are many ways to turn an argv into one big string
// we're gonna base our serializing logic on the command line string parsing
// convention of the windows c runtime.
// That is, out of all the ways we can turn an argv into a string, we're gonna
// aim for a way that can be taken by the windows c runtime, and turned back into
// the argv we started with.
bool shsl_is_char_special_for_cmd_exe(char c) {
    return c == '('
        || c == ')'
        || c == '%'
        || c == '!'
        || c == '^'
        || c == '"'
        || c == '<'
        || c == '>'
        || c == '&';
}

// the cmd_exe flag tells us wether the command we're tryna run will be passed to
// cmd.exe before running or not
// if it is, take special care of the characters cmd.exe considers special
void shsl_sb_win32_escaped_push(shsl_string_builder* sb,
                                char c, bool cmd_exe) {
    if(cmd_exe && shsl_is_char_special_for_cmd_exe(c))
        shsl_sb_push(sb, '^');
    shsl_sb_push(sb, c);
}

void shsl_cmd_push_quoted_win32_arg(const char* arg, shsl_string_builder* sb,
                                    bool cmd_exe) {
    // starting quote
    shsl_sb_win32_escaped_push(sb, '"', cmd_exe);

    // handle characters of arg before adding ending quote
    const char* iter = arg;
    while(true) {
        // skip backshasles
        // and  count how many backslashes did you skip
        size_t n_bs = 0;
        while(*iter == '\\') {
            iter++;
            n_bs ++;
        }

        // if the argument ends in backslashes
        // for instance [a\], which should become ["a\\\"]
        // then we escape all the final backslashes, then add an extra backslash
        // to escape ending the quote
        // totaling 2 * n_bs + 1 backslashes
        if(n_bs != 0 && *iter == '\0') {
            // '\\' isn't a special char for cmd.exe
            // so we can we can avoid maybe escaping here
            for(int i = 2*n_bs+1; i!=0; i--)
                shsl_sb_push(sb, '\\');
            break;
        }

        // if the argument ends without any backslashes
        if(n_bs == 0 && *iter == '\0')
            // it still ends so...
            break;

        // quote but not at the end of the argument
        // this if also handles the case with a quote and n_bs=0 backslashes
        if(*iter == '"') {
            for(int i = 2*n_bs+1; i!=0; --i)
                shsl_sb_push(sb, '\\');
            shsl_sb_win32_escaped_push(sb, '"', cmd_exe);
            iter++;
            continue;
        }

        // if there were backslashes, but not at the end of the argument, and not
        // otherwise followed by a quote, add them as is
        // we don't increase iter here, as it's already past the backslashes
        if(n_bs != 0) {
            for(int i = n_bs; i!=0; --i)
                shsl_sb_push(sb, '\\');
            continue;
        }

        // and finally, handle the normal case where it was just a character
        shsl_sb_win32_escaped_push(sb, *iter, cmd_exe);
        iter++;
    }

    // ending quote
    shsl_sb_win32_escaped_push(sb, '"', cmd_exe);
}

// this is the big function which will turn an argv into a string we can pass to
// the win32 api
// concatenates arguments into a big string, quoting them if needed
// uses the functions above to handle escaping
char* shsl_cmd_to_win32_str(int argc, char** argv, bool cmd_exe) {
    shsl_string_builder sb = {0};
    for(int i = 0; i<argc; ++i) {
        // add whitespace separators
        if(i!=0)
            shsl_sb_push(&sb, ' ');

        const char* arg = argv[i];

        // handle empty string
        if(strlen(arg) == 0)
            shsl_sb_push_nullt_str(&sb, "\"\"");

        // can we avoid quoting the string?
        else if(strpbrk(arg, " \t\n\v\"") == NULL)
            for(const char* c = arg; *c; c++)
                shsl_sb_win32_escaped_push(&sb, *c, cmd_exe);

        // if we can't, add it with quotes
        else
            shsl_cmd_push_quoted_win32_arg(arg, &sb, cmd_exe);
    }
    shsl_sb_push(&sb, '\0');
    return shsl_sb_get(&sb);
}

#ifdef SHSL_WIN32_WARN_ON_NO_EXTENSION
void maybe_warn_no_extension(const char* exename) {
    shsl_log_warn
        ("running executable without specifying file extension!");
    shsl_log_warn
        ("cannot determine wether to treat executable as batch file!");
    shsl_log_warn
        ("this operation can be dangerous, please make sure you're");
    shsl_log_warn
        ("not passing any unsanitized user input to this function.");
    shsl_log_warn("okthxbye <3"SHSL_NL);
}
#else
#define maybe_warn_no_extension()
#endif // SHSL_WIN32_WARN_ON_NO_EXTENSION

void shsl_log_win32_error(DWORD error, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    shsl_vlog(stderr, SHSL_LOG_LEVEL_ERROR, fmt, args);
    va_end(args);

    // think of error as errno
    // and of the following code as puts(strerror(errno))
    // just... more microsofty

    // https://stackoverflow.com/questions/1387064/how-to-get-the-error-message-from-the-error-code-returned-by-getlasterror
    // https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-getlasterror#syntax
    // https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-formatmessage#syntax
    char buf[1024] = {0};
    FormatMessageA
        (FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL,
         error,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
         buf, 1024,
         NULL);
    shsl_log_err("%s"SHSL_NL, buf);
}

// https://learn.microsoft.com/en-us/windows/win32/procthread/creating-processes
int shsl_exec(int argc, char** argv) {
    if(argc == 0) {
        shsl_log_err("cannot execute empty command!"SHSL_NL);
        return -1;
    }

    bool should_escape_cmd_exe = false;
    if(shsl_string_ends_with(argv[0], ".cmd") ||
       shsl_string_ends_with(argv[0], ".bat"))
        should_escape_cmd_exe = true;

    if(strpbrk(argv[0], ".") == NULL) {
        should_escape_cmd_exe = false;
        maybe_warn_no_extension();
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char* cmd_str = shsl_cmd_to_win32_str(argc, argv,
                                          should_escape_cmd_exe);

    BOOL created_successfully = CreateProcessA
        (NULL,                             // no module name
         cmd_str,                          // command line string
         NULL, NULL, FALSE, 0, NULL, NULL, // buncha shit 'n flags
         &si, &pi);                        // output params

    if(!created_successfully) {
        shsl_log_win32_error
            (GetLastError(),
             "an error occured while creating child process!"SHSL_NL);
        return -1;
    }

    // if we're not in the if then it's all fine and dandy
    // process creation succeded, process exists and is doing its thing
    // wait for process to exit
    WaitForSingleObject(pi.hProcess, INFINITE);

    // LPDWORD is just a pointer to DWORD
    // DWORD is just uint32_t
    // https://learn.microsoft.com/en-us/windows/win32/winprog/windows-data-types
    // which means when calling GetExitCodeProcess...
    // https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-getexitcodeprocess
    DWORD exit_code;
    if(!GetExitCodeProcess(pi.hProcess, &exit_code)) {
        shsl_log_win32_error
            (GetLastError(),
             "failed to obtain return value of process!"SHSL_NL);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread); 
        return -1;
    }

    // close handles to process and to process main thread
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread); 

    // I'm making the BIG assumption that exit_code can be reinterpreted as an int
    // which, being what you return from int main(), I don't see why not
    return (int)exit_code;
}

int shsl_exec_into_strs(int argc, char** argv, char** outp, char** errp) {
    // business as usual
    if(argc == 0) {
        shsl_log_err("cannot execute empty command!"SHSL_NL);
        return -1;
    }

    bool should_escape_cmd_exe = false;
    if(shsl_string_ends_with(argv[0], ".cmd") ||
       shsl_string_ends_with(argv[0], ".bat"))
        should_escape_cmd_exe = true;

    if(strpbrk(argv[0], ".") == NULL) {
        should_escape_cmd_exe = false;
        maybe_warn_no_extension();
    }

    char* cmd_str = shsl_cmd_to_win32_str(argc, argv,
                                          should_escape_cmd_exe);

    // now for the redirect part:
    // win32 api doesn't have fork exec
    // which means you can't fork, set shit up, then exec
    // which means you have to create the process and have all the shit already
    // set up
    // 
    // in the code you gotta write, this translates to having to prepopulate
    // a whole bunch of metadata structs and shit and already knowing 
    // everything the starting child process must know before you call
    // CreateProcess
    // 
    // you can't do the setup in the child process like in fork exec, you have
    // to do all the setup in the parent process

    // to pass pipes to child we must have the child inherit the stream handles
    // when creating a pipe, the inheritance of the stream handles that pipe
    // connects are controlled by a SECURITY_ATTRIBUTES you pass to CreatePipe
    // so let's create a SECURITY_ATTRIBUTES that tells CreatePipe to make
    // the pipe handles inheritable by child processes
    SECURITY_ATTRIBUTES sec_attrs = {};
    sec_attrs.nLength = sizeof(SECURITY_ATTRIBUTES);
    sec_attrs.bInheritHandle = TRUE;
    sec_attrs.lpSecurityDescriptor = NULL;
    
    // and create the handles to pipe the child's stdout (and stderr) to 
    // handles that we control
    HANDLE child_stdout_write = NULL; // child output goes here
    HANDLE child_stdout_read = NULL;  // and we'll read it from here

    HANDLE child_stderr_write = NULL; // child error goes here
    HANDLE child_stderr_read = NULL;  // and we'll read it from here

    if(!CreatePipe(&child_stdout_read, &child_stdout_write, &sec_attrs, 0)) {
        shsl_log_win32_error
            (GetLastError(),
            "failed to create pipe to child process standard output");
        return -1;
    }
    if(!SetHandleInformation(child_stdout_read, HANDLE_FLAG_INHERIT, 0)) {
        shsl_log_win32_error
            (GetLastError(),
            "failed to set handle information for child process standard output");
        return -1;
    }
    if(!CreatePipe(&child_stderr_read, &child_stderr_write, &sec_attrs, 0)) {
        shsl_log_win32_error
            (GetLastError(),
            "failed to create pipe to child process standard error");
        return -1;
    }

    if(!SetHandleInformation(child_stderr_read, HANDLE_FLAG_INHERIT, 0)) {
        shsl_log_win32_error
            (GetLastError(),
            "failed to set handle information for child process standard error");
        return -1;
    }

    // now that we created the stream handles we have to write somewhere that the
    // child process should use these stream handles as its stdout and stderr 
    // we do this in a STARTUPINFO that we're gonna pass to CreateProcess
    // create a STARTUPINFO that tells the child to use the stdout and stderr we control
    STARTUPINFO startup_info;
    ZeroMemory(&startup_info, sizeof(STARTUPINFO)); // hygene first
    startup_info.cb = sizeof(STARTUPINFO);
    startup_info.hStdOutput = child_stdout_write;
    startup_info.hStdError  = child_stderr_write;
    startup_info.dwFlags |= STARTF_USESTDHANDLES;

    // CreateProcess also takes a PROCESS_INFORMATION which it uses as an out parameter
    // since C doesn't have multiple returns you give it a pointer to a 
    // PROCESS_INFORMATION and CreateProcess will populate it with a bunch of info
    // about the child process which the parent may need to wait on it, disown it, or 
    // whatever it is parents do
    PROCESS_INFORMATION process_info;
    ZeroMemory(&process_info, sizeof(PROCESS_INFORMATION));

    BOOL success = CreateProcessA
        (NULL,           // always NULL, a module or something
         cmd_str,        // child command line
         NULL,           // security attributes for child process
         NULL,           // security attributes for child process primary thread
         TRUE,           // flag for controlling wether handles are inherited
         0,              // flags for process creation
         NULL,           // child environment variables (if NULL use parent's)
         NULL,           // child initial working directory (if NULL use parent's)
         &startup_info,  // child process startup info
         &process_info); // struct to populate with info about the child process
    if(!success) {
        shsl_log_win32_error
            (GetLastError(),
            "failed to create child process");
        return -1;
    }

    // we don't need the child stdout and stderr handles, and keeping them open could
    // lead to a lot of problems 'cause processes reading from them can't tell when
    // are they done if the child closes them but we keep them open
    // so we should not keep them open
    CloseHandle(child_stderr_write);
    CloseHandle(child_stdout_write);

    // collect child output
    DWORD n_read = 0;
    const size_t BUFSIZE = 4096;
    char buf[BUFSIZE]; ZeroMemory(buf, sizeof(buf));

    shsl_string_builder out_sb = {0};
    shsl_string_builder err_sb = {0};

    // collect standard out
    while(true) {
        BOOL read_success = ReadFile(child_stdout_read, buf,
                                     BUFSIZE, &n_read, NULL);
        if(!read_success) {
            shsl_log_win32_error
                (GetLastError(),
                 "failed read from process stdout");
            if(out_sb.buf) free(out_sb.buf);
            return -1;
        }
        if(n_read == 0)
            break;
        shsl_sb_push_sized_str(&out_sb, buf, n_read);
    }

    // collect standard err
    while(true) {
        BOOL read_success = ReadFile(child_stderr_read, buf,
                                     BUFSIZE, &n_read, NULL);
        if(!read_success) {
            shsl_log_win32_error
                (GetLastError(),
                 "failed read from process stderr");
            if(out_sb.buf) free(out_sb.buf);
            if(err_sb.buf) free(err_sb.buf);
            return -1;
        }
        if(n_read == 0)
            break;
        shsl_sb_push_sized_str(&err_sb, buf, n_read);
    }

    shsl_sb_push(&out_sb, '\0');
    shsl_sb_push(&err_sb, '\0');
    *outp = shsl_sb_get(&out_sb);
    *errp = shsl_sb_get(&err_sb);

    return 0;
}
#endif // defined(SHSL_UNIX)

// and now that, one way or the other, shsl_exec&Co. have been implemnted, we can
// use them to provide an exec api to the shsl code
shsl_ref shsl_fn_assert_cmd_strvec(const char* caller, shsl_ref arg) {
    shsl_vec_foreach(i, elt, arg) {
        if(!shsl_is_str(elt))
            return shsl_mkerr
                (shsl_kwmap_fromelts
                 (":command-vector", arg,
                  ":culprit", elt,
                  ":culprit-index", shsl_mkint(i),
                  ":culprit-type", shsl_mkstr(shsl_stringify_ref_type(arg))),

                 "%s: expected all elements of the command "
                 "to be strings, received invalid command: "
                 "argument at index %zu of command vector is not a string",
                 caller, (size_t)i);
    }
    return shsl_ref_to_nil();
}

void shsl_strvec_to_argc_argv(shsl_ref strvec, int* argc_ptr, char*** argv_ptr) {
    int argc; char** argv;
    argc = shsl_vec_length(strvec);
    argv = SHSL_ARR_ALLOC(char*, argc+1);
    shsl_vec_foreach(i, elt, strvec)
        argv[i] = elt.ptr->str.buf;
    argv[argc] = NULL;

    *argc_ptr = argc;
    *argv_ptr = argv;
}

shsl_defun(shsl_builtin_exec_vec, "exec-vec", args, env, {
        (void)env;
        // validate
        shsl_fn_assert_argslen(== 1);
        shsl_fn_assert_argtype(0, SHSL_VEC);

        shsl_ref invalid = shsl_fn_assert_cmd_strvec("exec-vec",
                                                     shsl_fn_arg(0));
        if(!shsl_is_nil(invalid))
            return invalid;
        
        // create argc and argv
        int argc; char** argv;
        shsl_strvec_to_argc_argv(shsl_fn_arg(0), &argc, &argv);
        int ret = shsl_exec(argc, argv);
        free(argv);

        return ret == EXIT_SUCCESS
            ?shsl_mkint(ret)
            :shsl_mkerr(shsl_kwmap_fromelts
                        (":command", (shsl_vec_get(args, 0)),
                         ":command-exit-code", shsl_mkint(ret)),
                        "exec-vec: child process exited with failure status %d",
                        ret);
    })

shsl_defun(shsl_builtin_exec_vec_strs, "exec-vec-strs", args, env, {
        (void)env;
        // most of this logic is duplicated from "exec-vec"
        // which is... rather sadge :(
        shsl_fn_assert_argslen(== 1);
        shsl_fn_assert_argtype(0, SHSL_VEC);

        shsl_ref invalid = shsl_fn_assert_cmd_strvec("exec-vec-strs",
                                                     shsl_fn_arg(0));
        if(!shsl_is_nil(invalid))
            return invalid;

        int argc; char** argv;
        shsl_strvec_to_argc_argv(shsl_fn_arg(0), &argc, &argv);
        char* out = NULL;
        char* err = NULL;
        int exec_child = SHSL_EXEC_INTO_STRS(argc, argv, &out, &err);

        free(argv);

        // failure in shsl_exec_into_strs
        if(exec_child < 0) {
            if(out) free(out); 
            if(err) free(err); 
            return shsl_mkerr(shsl_kwmap_fromelts
                    (":command", shsl_fn_arg(0),
                     ":errno", shsl_mkint(errno),
                     ":errno-msg", shsl_mkstr(strerror(errno))),
                    "exec-vec-strs: some error occured while running "
                    "child process");
        }

        return shsl_kwmap_fromelts(":stdout", shsl_mkstr_nocopy(out),
                                   ":stderr", shsl_mkstr_nocopy(err),
                                   ":exit-code", shsl_mkint(exec_child));
    })

shsl_ref shsl_env_add_exec_defs(shsl_ref env) {
    shsl_env_def(env, shsl_mksym("exec-vec"),
                 shsl_mkbuiltin_fn(env, shsl_builtin_exec_vec));
    shsl_env_def(env, shsl_mksym("exec-vec-strs"),
                 shsl_mkbuiltin_fn(env, shsl_builtin_exec_vec_strs));
    shsl_env_def(env, shsl_mksym("exit-success"),
                 shsl_mkint(EXIT_SUCCESS));
    shsl_env_def(env, shsl_mksym("exit-failure"),
                 shsl_mkint(EXIT_FAILURE));
    return env;
}
shsl_ref shsl_env_eval_execlib(shsl_ref env) {
    shsl_eval_str("(defn exec [& args] (exec-vec args))", env);
    shsl_eval_str("(defn exec-strs [& args] (exec-vec-strs args))", env);
    return env;
}
#endif // SHSL_EXEC_IMPLEMENTATION
