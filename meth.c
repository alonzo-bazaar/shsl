# 0 "tests.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3
# 0 "<command-line>" 2
# 1 "tests.c"
# 1 "/usr/include/stdio.h" 1 3
# 28 "/usr/include/stdio.h" 3
# 1 "/usr/include/bits/libc-header-start.h" 1 3
# 33 "/usr/include/bits/libc-header-start.h" 3
# 1 "/usr/include/features.h" 1 3
# 431 "/usr/include/features.h" 3
# 1 "/usr/include/features-time64.h" 1 3
# 20 "/usr/include/features-time64.h" 3
# 1 "/usr/include/bits/wordsize.h" 1 3
# 21 "/usr/include/features-time64.h" 2 3
# 1 "/usr/include/bits/timesize.h" 1 3
# 19 "/usr/include/bits/timesize.h" 3
# 1 "/usr/include/bits/wordsize.h" 1 3
# 20 "/usr/include/bits/timesize.h" 2 3
# 22 "/usr/include/features-time64.h" 2 3
# 432 "/usr/include/features.h" 2 3
# 540 "/usr/include/features.h" 3
# 1 "/usr/include/sys/cdefs.h" 1 3
# 730 "/usr/include/sys/cdefs.h" 3
# 1 "/usr/include/bits/wordsize.h" 1 3
# 731 "/usr/include/sys/cdefs.h" 2 3
# 1 "/usr/include/bits/long-double.h" 1 3
# 732 "/usr/include/sys/cdefs.h" 2 3
# 541 "/usr/include/features.h" 2 3
# 564 "/usr/include/features.h" 3
# 1 "/usr/include/gnu/stubs.h" 1 3
# 10 "/usr/include/gnu/stubs.h" 3
# 1 "/usr/include/gnu/stubs-64.h" 1 3
# 11 "/usr/include/gnu/stubs.h" 2 3
# 565 "/usr/include/features.h" 2 3
# 34 "/usr/include/bits/libc-header-start.h" 2 3
# 29 "/usr/include/stdio.h" 2 3









# 1 "/usr/lib/gcc/x86_64-redhat-linux/16/include/stddef.h" 1 3
# 229 "/usr/lib/gcc/x86_64-redhat-linux/16/include/stddef.h" 3

# 229 "/usr/lib/gcc/x86_64-redhat-linux/16/include/stddef.h" 3
typedef long unsigned int size_t;
# 39 "/usr/include/stdio.h" 2 3


# 1 "/usr/lib/gcc/x86_64-redhat-linux/16/include/stdarg.h" 1 3
# 40 "/usr/lib/gcc/x86_64-redhat-linux/16/include/stdarg.h" 3
typedef __builtin_va_list __gnuc_va_list;
# 42 "/usr/include/stdio.h" 2 3

# 1 "/usr/include/bits/types.h" 1 3
# 27 "/usr/include/bits/types.h" 3
# 1 "/usr/include/bits/wordsize.h" 1 3
# 28 "/usr/include/bits/types.h" 2 3
# 1 "/usr/include/bits/timesize.h" 1 3
# 19 "/usr/include/bits/timesize.h" 3
# 1 "/usr/include/bits/wordsize.h" 1 3
# 20 "/usr/include/bits/timesize.h" 2 3
# 29 "/usr/include/bits/types.h" 2 3


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;






typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;



typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 141 "/usr/include/bits/types.h" 3
# 1 "/usr/include/bits/typesizes.h" 1 3
# 142 "/usr/include/bits/types.h" 2 3
# 1 "/usr/include/bits/time64.h" 1 3
# 143 "/usr/include/bits/types.h" 2 3


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef long int __suseconds64_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;
# 44 "/usr/include/stdio.h" 2 3
# 1 "/usr/include/bits/types/__fpos_t.h" 1 3




# 1 "/usr/include/bits/types/__mbstate_t.h" 1 3
# 13 "/usr/include/bits/types/__mbstate_t.h" 3
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
# 6 "/usr/include/bits/types/__fpos_t.h" 2 3




typedef struct _G_fpos_t
{
  __off_t __pos;
  __mbstate_t __state;
} __fpos_t;
# 45 "/usr/include/stdio.h" 2 3
# 1 "/usr/include/bits/types/__fpos64_t.h" 1 3
# 10 "/usr/include/bits/types/__fpos64_t.h" 3
typedef struct _G_fpos64_t
{
  __off64_t __pos;
  __mbstate_t __state;
} __fpos64_t;
# 46 "/usr/include/stdio.h" 2 3
# 1 "/usr/include/bits/types/__FILE.h" 1 3



struct _IO_FILE;
typedef struct _IO_FILE __FILE;
# 47 "/usr/include/stdio.h" 2 3
# 1 "/usr/include/bits/types/FILE.h" 1 3



struct _IO_FILE;


typedef struct _IO_FILE FILE;
# 48 "/usr/include/stdio.h" 2 3
# 1 "/usr/include/bits/types/struct_FILE.h" 1 3
# 35 "/usr/include/bits/types/struct_FILE.h" 3
# 1 "/usr/include/bits/wordsize.h" 1 3
# 36 "/usr/include/bits/types/struct_FILE.h" 2 3

struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;




typedef void _IO_lock_t;





struct _IO_FILE
{
  int _flags;


  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;


  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
  int _flags2:24;

  char _short_backupbuf[1];
  __off_t _old_offset;


  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

  _IO_lock_t *_lock;







  __off64_t _offset;

  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  struct _IO_FILE **_prevchain;
  int _mode;

  int _unused3;

  __uint64_t _total_written;




  char _unused2[12 * sizeof (int) - 5 * sizeof (void *)];
};
# 49 "/usr/include/stdio.h" 2 3


# 1 "/usr/include/bits/types/cookie_io_functions_t.h" 1 3
# 27 "/usr/include/bits/types/cookie_io_functions_t.h" 3
typedef __ssize_t cookie_read_function_t (void *__cookie, char *__buf,
                                          size_t __nbytes);







typedef __ssize_t cookie_write_function_t (void *__cookie, const char *__buf,
                                           size_t __nbytes);







typedef int cookie_seek_function_t (void *__cookie, __off64_t *__pos, int __w);


typedef int cookie_close_function_t (void *__cookie);






typedef struct _IO_cookie_io_functions_t
{
  cookie_read_function_t *read;
  cookie_write_function_t *write;
  cookie_seek_function_t *seek;
  cookie_close_function_t *close;
} cookie_io_functions_t;
# 52 "/usr/include/stdio.h" 2 3





typedef __gnuc_va_list va_list;
# 68 "/usr/include/stdio.h" 3
typedef __off_t off_t;
# 82 "/usr/include/stdio.h" 3
typedef __ssize_t ssize_t;






typedef __fpos_t fpos_t;
# 133 "/usr/include/stdio.h" 3
# 1 "/usr/include/bits/stdio_lim.h" 1 3
# 134 "/usr/include/stdio.h" 2 3
# 153 "/usr/include/stdio.h" 3
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;






extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));

extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));



extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));
# 191 "/usr/include/stdio.h" 3
extern int fclose (FILE *__stream) __attribute__ ((__nonnull__ (1)));
# 201 "/usr/include/stdio.h" 3
extern FILE *tmpfile (void)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
# 218 "/usr/include/stdio.h" 3
extern char *tmpnam (char[20]) __attribute__ ((__nothrow__ , __leaf__)) ;




extern char *tmpnam_r (char __s[20]) __attribute__ ((__nothrow__ , __leaf__)) ;
# 235 "/usr/include/stdio.h" 3
extern char *tempnam (const char *__dir, const char *__pfx)
   __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (__builtin_free, 1)));






extern int fflush (FILE *__stream);
# 252 "/usr/include/stdio.h" 3
extern int fflush_unlocked (FILE *__stream);
# 271 "/usr/include/stdio.h" 3
extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;




extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) __attribute__ ((__nonnull__ (3)));
# 306 "/usr/include/stdio.h" 3
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;





extern FILE *fopencookie (void *__restrict __magic_cookie,
     const char *__restrict __modes,
     cookie_io_functions_t __io_funcs) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;




extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
# 341 "/usr/include/stdio.h" 3
extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__nonnull__ (1)));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...) __attribute__ ((__nonnull__ (1)));




extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nonnull__ (1)));




extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));



extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));





extern int vasprintf (char **__restrict __ptr, const char *__restrict __f,
        __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 0))) ;
extern int __asprintf (char **__restrict __ptr,
         const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) ;
extern int asprintf (char **__restrict __ptr,
       const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) ;




extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));







extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) __attribute__ ((__nonnull__ (1)));




extern int scanf (const char *__restrict __format, ...) ;

extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));





# 1 "/usr/include/bits/floatn.h" 1 3
# 131 "/usr/include/bits/floatn.h" 3
# 1 "/usr/include/bits/floatn-common.h" 1 3
# 24 "/usr/include/bits/floatn-common.h" 3
# 1 "/usr/include/bits/long-double.h" 1 3
# 25 "/usr/include/bits/floatn-common.h" 2 3
# 132 "/usr/include/bits/floatn.h" 2 3
# 445 "/usr/include/stdio.h" 2 3




extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc23_fscanf")

                                __attribute__ ((__nonnull__ (1)));
extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc23_scanf")
                              ;
extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc23_sscanf") __attribute__ ((__nothrow__ , __leaf__))

                      ;
# 497 "/usr/include/stdio.h" 3
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) __attribute__ ((__nonnull__ (1)));





extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;


extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));






extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc23_vfscanf")



     __attribute__ ((__format__ (__scanf__, 2, 0))) __attribute__ ((__nonnull__ (1)));
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc23_vscanf")

     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc23_vsscanf") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__format__ (__scanf__, 2, 0)));
# 582 "/usr/include/stdio.h" 3
extern int fgetc (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int getc (FILE *__stream) __attribute__ ((__nonnull__ (1)));





extern int getchar (void);






extern int getc_unlocked (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int getchar_unlocked (void);
# 607 "/usr/include/stdio.h" 3
extern int fgetc_unlocked (FILE *__stream) __attribute__ ((__nonnull__ (1)));







extern int fputc (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern int putc (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));





extern int putchar (int __c);
# 631 "/usr/include/stdio.h" 3
extern int fputc_unlocked (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));







extern int putc_unlocked (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream) __attribute__ ((__nonnull__ (1)));


extern int putw (int __w, FILE *__stream) __attribute__ ((__nonnull__ (2)));







extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     __attribute__ ((__access__ (__write_only__, 1, 2))) __attribute__ ((__nonnull__ (3)));
# 693 "/usr/include/stdio.h" 3
extern __ssize_t __getdelim (char **__restrict __lineptr,
                             size_t *__restrict __n, int __delimiter,
                             FILE *__restrict __stream) __attribute__ ((__nonnull__ (4)));
extern __ssize_t getdelim (char **__restrict __lineptr,
                           size_t *__restrict __n, int __delimiter,
                           FILE *__restrict __stream) __attribute__ ((__nonnull__ (4)));


extern __ssize_t getline (char **__restrict __lineptr,
                          size_t *__restrict __n,
                          FILE *__restrict __stream) __attribute__ ((__nonnull__ (3)));







extern int fputs (const char *__restrict __s, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (2)));





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (4)));




extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s) __attribute__ ((__nonnull__ (4)));
# 760 "/usr/include/stdio.h" 3
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (4)));
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (4)));







extern int fseek (FILE *__stream, long int __off, int __whence)
  __attribute__ ((__nonnull__ (1)));




extern long int ftell (FILE *__stream) __attribute__ ((__nonnull__ (1)));




extern void rewind (FILE *__stream) __attribute__ ((__nonnull__ (1)));
# 797 "/usr/include/stdio.h" 3
extern int fseeko (FILE *__stream, __off_t __off, int __whence)
  __attribute__ ((__nonnull__ (1)));




extern __off_t ftello (FILE *__stream) __attribute__ ((__nonnull__ (1)));
# 823 "/usr/include/stdio.h" 3
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos)
  __attribute__ ((__nonnull__ (1)));




extern int fsetpos (FILE *__stream, const fpos_t *__pos) __attribute__ ((__nonnull__ (1)));
# 854 "/usr/include/stdio.h" 3
extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern void perror (const char *__s) __attribute__ ((__cold__));




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 891 "/usr/include/stdio.h" 3
extern int pclose (FILE *__stream) __attribute__ ((__nonnull__ (1)));





extern FILE *popen (const char *__command, const char *__modes)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (pclose, 1))) ;






extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__access__ (__write_only__, 1)));
# 935 "/usr/include/stdio.h" 3
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 953 "/usr/include/stdio.h" 3
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);
# 977 "/usr/include/stdio.h" 3

# 2 "tests.c" 2
# 1 "/usr/include/assert.h" 1 3
# 92 "/usr/include/assert.h" 3



extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));


extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));






extern _Bool __assert_single_arg (_Bool);



# 3 "tests.c" 2


# 1 "shsl.h" 1
# 12 "shsl.h"
# 1 "/usr/include/stdlib.h" 1 3
# 26 "/usr/include/stdlib.h" 3
# 1 "/usr/include/bits/libc-header-start.h" 1 3
# 27 "/usr/include/stdlib.h" 2 3





# 1 "/usr/lib/gcc/x86_64-redhat-linux/16/include/stddef.h" 1 3
# 344 "/usr/lib/gcc/x86_64-redhat-linux/16/include/stddef.h" 3
typedef int wchar_t;
# 33 "/usr/include/stdlib.h" 2 3


# 44 "/usr/include/stdlib.h" 3
# 1 "/usr/include/bits/waitflags.h" 1 3
# 45 "/usr/include/stdlib.h" 2 3
# 1 "/usr/include/bits/waitstatus.h" 1 3
# 46 "/usr/include/stdlib.h" 2 3
# 63 "/usr/include/stdlib.h" 3
typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;





__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;
# 102 "/usr/include/stdlib.h" 3
extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__ , __leaf__)) ;



extern double atof (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern int atoi (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern long int atol (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



__extension__ extern long long int atoll (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 181 "/usr/include/stdlib.h" 3
extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



__extension__
extern long long int strtoq (const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern long int strtol (const char *__restrict __nptr, char **__restrict __endptr, int __base) __asm__ ("" "__isoc23_strtol") __attribute__ ((__nothrow__ , __leaf__))


     __attribute__ ((__nonnull__ (1)));
extern unsigned long int strtoul (const char *__restrict __nptr, char **__restrict __endptr, int __base) __asm__ ("" "__isoc23_strtoul") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__nonnull__ (1)));

__extension__
extern long long int strtoq (const char *__restrict __nptr, char **__restrict __endptr, int __base) __asm__ ("" "__isoc23_strtoll") __attribute__ ((__nothrow__ , __leaf__))


     __attribute__ ((__nonnull__ (1)));
__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr, char **__restrict __endptr, int __base) __asm__ ("" "__isoc23_strtoull") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__nonnull__ (1)));

__extension__
extern long long int strtoll (const char *__restrict __nptr, char **__restrict __endptr, int __base) __asm__ ("" "__isoc23_strtoll") __attribute__ ((__nothrow__ , __leaf__))


     __attribute__ ((__nonnull__ (1)));
__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr, char **__restrict __endptr, int __base) __asm__ ("" "__isoc23_strtoull") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__nonnull__ (1)));
# 282 "/usr/include/stdlib.h" 3
extern int strfromd (char *__dest, size_t __size, const char *__format,
       double __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));

extern int strfromf (char *__dest, size_t __size, const char *__format,
       float __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));

extern int strfroml (char *__dest, size_t __size, const char *__format,
       long double __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));
# 509 "/usr/include/stdlib.h" 3
extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) ;


extern long int a64l (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;




# 1 "/usr/include/sys/types.h" 1 3
# 27 "/usr/include/sys/types.h" 3






typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;


typedef __loff_t loff_t;




typedef __ino_t ino_t;
# 59 "/usr/include/sys/types.h" 3
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;
# 97 "/usr/include/sys/types.h" 3
typedef __pid_t pid_t;





typedef __id_t id_t;
# 114 "/usr/include/sys/types.h" 3
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;




# 1 "/usr/include/bits/types/clock_t.h" 1 3






typedef __clock_t clock_t;
# 127 "/usr/include/sys/types.h" 2 3

# 1 "/usr/include/bits/types/clockid_t.h" 1 3






typedef __clockid_t clockid_t;
# 129 "/usr/include/sys/types.h" 2 3
# 1 "/usr/include/bits/types/time_t.h" 1 3
# 10 "/usr/include/bits/types/time_t.h" 3
typedef __time_t time_t;
# 130 "/usr/include/sys/types.h" 2 3
# 1 "/usr/include/bits/types/timer_t.h" 1 3






typedef __timer_t timer_t;
# 131 "/usr/include/sys/types.h" 2 3
# 144 "/usr/include/sys/types.h" 3
# 1 "/usr/lib/gcc/x86_64-redhat-linux/16/include/stddef.h" 1 3
# 145 "/usr/include/sys/types.h" 2 3



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;




# 1 "/usr/include/bits/stdint-intn.h" 1 3
# 24 "/usr/include/bits/stdint-intn.h" 3
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 156 "/usr/include/sys/types.h" 2 3


typedef __uint8_t u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;


typedef int register_t __attribute__ ((__mode__ (__word__)));
# 176 "/usr/include/sys/types.h" 3
# 1 "/usr/include/endian.h" 1 3
# 24 "/usr/include/endian.h" 3
# 1 "/usr/include/bits/endian.h" 1 3
# 35 "/usr/include/bits/endian.h" 3
# 1 "/usr/include/bits/endianness.h" 1 3
# 36 "/usr/include/bits/endian.h" 2 3
# 25 "/usr/include/endian.h" 2 3
# 35 "/usr/include/endian.h" 3
# 1 "/usr/include/bits/byteswap.h" 1 3
# 33 "/usr/include/bits/byteswap.h" 3
static __inline __uint16_t
__bswap_16 (__uint16_t __bsx)
{

  return __builtin_bswap16 (__bsx);



}






static __inline __uint32_t
__bswap_32 (__uint32_t __bsx)
{

  return __builtin_bswap32 (__bsx);



}
# 69 "/usr/include/bits/byteswap.h" 3
__extension__ static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{

  return __builtin_bswap64 (__bsx);



}
# 36 "/usr/include/endian.h" 2 3
# 1 "/usr/include/bits/uintn-identity.h" 1 3
# 32 "/usr/include/bits/uintn-identity.h" 3
static __inline __uint16_t
__uint16_identity (__uint16_t __x)
{
  return __x;
}

static __inline __uint32_t
__uint32_identity (__uint32_t __x)
{
  return __x;
}

static __inline __uint64_t
__uint64_identity (__uint64_t __x)
{
  return __x;
}
# 37 "/usr/include/endian.h" 2 3
# 177 "/usr/include/sys/types.h" 2 3


# 1 "/usr/include/sys/select.h" 1 3
# 30 "/usr/include/sys/select.h" 3
# 1 "/usr/include/bits/select.h" 1 3
# 31 "/usr/include/sys/select.h" 2 3


# 1 "/usr/include/bits/types/sigset_t.h" 1 3



# 1 "/usr/include/bits/types/__sigset_t.h" 1 3




typedef struct
{
  unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
} __sigset_t;
# 5 "/usr/include/bits/types/sigset_t.h" 2 3


typedef __sigset_t sigset_t;
# 34 "/usr/include/sys/select.h" 2 3



# 1 "/usr/include/bits/types/struct_timeval.h" 1 3







struct timeval
{




  __time_t tv_sec;
  __suseconds_t tv_usec;

};
# 38 "/usr/include/sys/select.h" 2 3

# 1 "/usr/include/bits/types/struct_timespec.h" 1 3
# 11 "/usr/include/bits/types/struct_timespec.h" 3
struct timespec
{



  __time_t tv_sec;




  __syscall_slong_t tv_nsec;
# 31 "/usr/include/bits/types/struct_timespec.h" 3
};
# 40 "/usr/include/sys/select.h" 2 3



typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
# 59 "/usr/include/sys/select.h" 3
typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;
# 91 "/usr/include/sys/select.h" 3

# 102 "/usr/include/sys/select.h" 3
extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
# 127 "/usr/include/sys/select.h" 3
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);
# 153 "/usr/include/sys/select.h" 3

# 180 "/usr/include/sys/types.h" 2 3





typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 227 "/usr/include/sys/types.h" 3
# 1 "/usr/include/bits/pthreadtypes.h" 1 3
# 23 "/usr/include/bits/pthreadtypes.h" 3
# 1 "/usr/include/bits/thread-shared-types.h" 1 3
# 44 "/usr/include/bits/thread-shared-types.h" 3
# 1 "/usr/include/bits/pthreadtypes-arch.h" 1 3
# 21 "/usr/include/bits/pthreadtypes-arch.h" 3
# 1 "/usr/include/bits/wordsize.h" 1 3
# 22 "/usr/include/bits/pthreadtypes-arch.h" 2 3
# 45 "/usr/include/bits/thread-shared-types.h" 2 3

# 1 "/usr/include/bits/atomic_wide_counter.h" 1 3
# 25 "/usr/include/bits/atomic_wide_counter.h" 3
typedef union
{
  __extension__ unsigned long long int __value64;
  struct
  {
    unsigned int __low;
    unsigned int __high;
  } __value32;
} __atomic_wide_counter;
# 47 "/usr/include/bits/thread-shared-types.h" 2 3




typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;

typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
# 76 "/usr/include/bits/thread-shared-types.h" 3
# 1 "/usr/include/bits/struct_mutex.h" 1 3
# 22 "/usr/include/bits/struct_mutex.h" 3
struct __pthread_mutex_s
{
  int __lock;
  unsigned int __count;
  int __owner;

  unsigned int __nusers;



  int __kind;

  short __spins;
  short __unused;
  __pthread_list_t __list;
# 52 "/usr/include/bits/struct_mutex.h" 3
};
# 77 "/usr/include/bits/thread-shared-types.h" 2 3
# 89 "/usr/include/bits/thread-shared-types.h" 3
# 1 "/usr/include/bits/struct_rwlock.h" 1 3
# 23 "/usr/include/bits/struct_rwlock.h" 3
struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;

  int __cur_writer;
  int __shared;
  unsigned long int __pad1;
  unsigned long int __pad2;


  unsigned int __flags;
# 48 "/usr/include/bits/struct_rwlock.h" 3
};
# 90 "/usr/include/bits/thread-shared-types.h" 2 3




struct __pthread_cond_s
{
  __atomic_wide_counter __wseq;
  __atomic_wide_counter __g1_start;
  unsigned int __g_size[2] ;
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
  unsigned int __unused_initialized_1;
  unsigned int __unused_initialized_2;
};

typedef unsigned int __tss_t;
typedef unsigned long int __thrd_t;

typedef struct
{
  int __data ;
} __once_flag;
# 24 "/usr/include/bits/pthreadtypes.h" 2 3



typedef unsigned long int pthread_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;


union pthread_attr_t
{
  char __size[56];
  long int __align;
};

typedef union pthread_attr_t pthread_attr_t;




typedef union
{
  struct __pthread_mutex_s __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;


typedef union
{
  struct __pthread_cond_s __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;





typedef union
{
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 228 "/usr/include/sys/types.h" 2 3



# 519 "/usr/include/stdlib.h" 2 3






extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));


extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));

extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));

extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));



extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));







extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    __extension__ unsigned long long int __a;

  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern __uint32_t arc4random (void)
     __attribute__ ((__nothrow__ , __leaf__)) ;


extern void arc4random_buf (void *__buf, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern __uint32_t arc4random_uniform (__uint32_t __upper_bound)
     __attribute__ ((__nothrow__ , __leaf__)) ;




extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;

extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (1, 2))) ;






extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__)) __attribute__ ((__alloc_size__ (2)));


extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));
# 702 "/usr/include/stdlib.h" 3
extern void free_sized (void *__ptr, size_t __size) __attribute__ ((__nothrow__ , __leaf__));




extern void free_aligned_sized (void *__ptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__));
# 717 "/usr/include/stdlib.h" 3
extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__))
     __attribute__ ((__alloc_size__ (2, 3)))
    __attribute__ ((__malloc__ (__builtin_free, 1)));


extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__ (reallocarray, 1)));



# 1 "/usr/include/alloca.h" 1 3
# 24 "/usr/include/alloca.h" 3
# 1 "/usr/lib/gcc/x86_64-redhat-linux/16/include/stddef.h" 1 3
# 25 "/usr/include/alloca.h" 2 3







extern void *alloca (size_t __size) __attribute__ ((__nothrow__ , __leaf__));






# 729 "/usr/include/stdlib.h" 2 3





extern void *valloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;




extern void *aligned_alloc (size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_align__ (1)))
     __attribute__ ((__alloc_size__ (2))) ;



extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));



extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int at_quick_exit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));





extern void quick_exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));





extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern char *getenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 808 "/usr/include/stdlib.h" 3
extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int setenv (const char *__name, const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int unsetenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int clearenv (void) __attribute__ ((__nothrow__ , __leaf__));
# 836 "/usr/include/stdlib.h" 3
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 849 "/usr/include/stdlib.h" 3
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
# 871 "/usr/include/stdlib.h" 3
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
# 892 "/usr/include/stdlib.h" 3
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 945 "/usr/include/stdlib.h" 3
extern int system (const char *__command) ;
# 962 "/usr/include/stdlib.h" 3
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) ;






typedef int (*__compar_fn_t) (const void *, const void *);
# 982 "/usr/include/stdlib.h" 3
extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;
# 998 "/usr/include/stdlib.h" 3
extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
# 1008 "/usr/include/stdlib.h" 3
extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
# 1026 "/usr/include/stdlib.h" 3
extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
# 1046 "/usr/include/stdlib.h" 3
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));

extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));





extern int mblen (const char *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int mbtowc (wchar_t *__restrict __pwc,
     const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__ , __leaf__));



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__read_only__, 2)));

extern size_t wcstombs (char *__restrict __s,
   const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__access__ (__write_only__, 1, 3)))
  __attribute__ ((__access__ (__read_only__, 2)));






extern int rpmatch (const char *__response) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 1133 "/usr/include/stdlib.h" 3
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
# 1179 "/usr/include/stdlib.h" 3
extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 1191 "/usr/include/stdlib.h" 3
# 1 "/usr/include/bits/types/once_flag.h" 1 3
# 24 "/usr/include/bits/types/once_flag.h" 3
typedef __once_flag once_flag;
# 1192 "/usr/include/stdlib.h" 2 3



extern void call_once (once_flag *__flag, void (*__func)(void));



extern size_t memalignment (const void *__p);


# 1 "/usr/include/bits/stdlib-float.h" 1 3
# 1203 "/usr/include/stdlib.h" 2 3
# 1214 "/usr/include/stdlib.h" 3

# 13 "shsl.h" 2
# 1 "/usr/lib/gcc/x86_64-redhat-linux/16/include/stdbool.h" 1 3
# 14 "shsl.h" 2
# 1 "/usr/lib/gcc/x86_64-redhat-linux/16/include/stdarg.h" 1 3
# 15 "shsl.h" 2

# 1 "/usr/include/ctype.h" 1 3
# 28 "/usr/include/ctype.h" 3

# 46 "/usr/include/ctype.h" 3
enum
{
  _ISupper = ((0) < 8 ? ((1 << (0)) << 8) : ((1 << (0)) >> 8)),
  _ISlower = ((1) < 8 ? ((1 << (1)) << 8) : ((1 << (1)) >> 8)),
  _ISalpha = ((2) < 8 ? ((1 << (2)) << 8) : ((1 << (2)) >> 8)),
  _ISdigit = ((3) < 8 ? ((1 << (3)) << 8) : ((1 << (3)) >> 8)),
  _ISxdigit = ((4) < 8 ? ((1 << (4)) << 8) : ((1 << (4)) >> 8)),
  _ISspace = ((5) < 8 ? ((1 << (5)) << 8) : ((1 << (5)) >> 8)),
  _ISprint = ((6) < 8 ? ((1 << (6)) << 8) : ((1 << (6)) >> 8)),
  _ISgraph = ((7) < 8 ? ((1 << (7)) << 8) : ((1 << (7)) >> 8)),
  _ISblank = ((8) < 8 ? ((1 << (8)) << 8) : ((1 << (8)) >> 8)),
  _IScntrl = ((9) < 8 ? ((1 << (9)) << 8) : ((1 << (9)) >> 8)),
  _ISpunct = ((10) < 8 ? ((1 << (10)) << 8) : ((1 << (10)) >> 8)),
  _ISalnum = ((11) < 8 ? ((1 << (11)) << 8) : ((1 << (11)) >> 8))
};
# 79 "/usr/include/ctype.h" 3
extern const unsigned short int **__ctype_b_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern const __int32_t **__ctype_tolower_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern const __int32_t **__ctype_toupper_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
# 108 "/usr/include/ctype.h" 3
extern int isalnum (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isalpha (int) __attribute__ ((__nothrow__ , __leaf__));
extern int iscntrl (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isdigit (int) __attribute__ ((__nothrow__ , __leaf__));
extern int islower (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isgraph (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isprint (int) __attribute__ ((__nothrow__ , __leaf__));
extern int ispunct (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isspace (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isupper (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isxdigit (int) __attribute__ ((__nothrow__ , __leaf__));



extern int tolower (int __c) __attribute__ ((__nothrow__ , __leaf__));


extern int toupper (int __c) __attribute__ ((__nothrow__ , __leaf__));




extern int isblank (int) __attribute__ ((__nothrow__ , __leaf__));
# 142 "/usr/include/ctype.h" 3
extern int isascii (int __c) __attribute__ ((__nothrow__ , __leaf__));



extern int toascii (int __c) __attribute__ ((__nothrow__ , __leaf__));



extern int _toupper (int) __attribute__ ((__nothrow__ , __leaf__));
extern int _tolower (int) __attribute__ ((__nothrow__ , __leaf__));
# 237 "/usr/include/ctype.h" 3
# 1 "/usr/include/bits/types/locale_t.h" 1 3
# 22 "/usr/include/bits/types/locale_t.h" 3
# 1 "/usr/include/bits/types/__locale_t.h" 1 3
# 27 "/usr/include/bits/types/__locale_t.h" 3
struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
};

typedef struct __locale_struct *__locale_t;
# 23 "/usr/include/bits/types/locale_t.h" 2 3

typedef __locale_t locale_t;
# 238 "/usr/include/ctype.h" 2 3
# 251 "/usr/include/ctype.h" 3
extern int isalnum_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isalpha_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int iscntrl_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isdigit_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int islower_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isgraph_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isprint_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int ispunct_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isspace_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isupper_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isxdigit_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));

extern int isblank_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));



extern int __tolower_l (int __c, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));
extern int tolower_l (int __c, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));


extern int __toupper_l (int __c, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));
extern int toupper_l (int __c, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));
# 327 "/usr/include/ctype.h" 3

# 17 "shsl.h" 2
# 1 "/usr/include/string.h" 1 3
# 26 "/usr/include/string.h" 3
# 1 "/usr/include/bits/libc-header-start.h" 1 3
# 27 "/usr/include/string.h" 2 3


# 37 "/usr/include/string.h" 3
# 1 "/usr/lib/gcc/x86_64-redhat-linux/16/include/stddef.h" 1 3
# 38 "/usr/include/string.h" 2 3
# 47 "/usr/include/string.h" 3
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
    __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__access__ (__write_only__, 1, 4)));




extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




extern void *memset_explicit (void *__s, int __c, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__access__ (__write_only__, 1, 3)));



extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 91 "/usr/include/string.h" 3
extern int __memcmpeq (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 118 "/usr/include/string.h" 3
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 156 "/usr/include/string.h" 3
extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcoll (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
    __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) __attribute__ ((__access__ (__write_only__, 1, 3)));






extern int strcoll_l (const char *__s1, const char *__s2, locale_t __l)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));


extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    locale_t __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)))
     __attribute__ ((__access__ (__write_only__, 1, 3)));





extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
# 261 "/usr/include/string.h" 3
extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 292 "/usr/include/string.h" 3
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 309 "/usr/include/string.h" 3
extern char *strchrnul (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 346 "/usr/include/string.h" 3
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 377 "/usr/include/string.h" 3
extern char *strstr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 388 "/usr/include/string.h" 3
extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));

extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
# 412 "/usr/include/string.h" 3
extern char *strcasestr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));







extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 3)))
    __attribute__ ((__access__ (__read_only__, 1, 2)))
    __attribute__ ((__access__ (__read_only__, 3, 4)));



extern void *__mempcpy (void *__restrict __dest,
   const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *mempcpy (void *__restrict __dest,
        const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern size_t strnlen (const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));
# 464 "/usr/include/string.h" 3
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__xpg_strerror_r") __attribute__ ((__nothrow__ , __leaf__))

                        __attribute__ ((__nonnull__ (2)))
    __attribute__ ((__access__ (__write_only__, 2, 3)));
# 490 "/usr/include/string.h" 3
extern char *strerror_l (int __errnum, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));



# 1 "/usr/include/strings.h" 1 3
# 23 "/usr/include/strings.h" 3
# 1 "/usr/lib/gcc/x86_64-redhat-linux/16/include/stddef.h" 1 3
# 24 "/usr/include/strings.h" 2 3










extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bcopy (const void *__src, void *__dest, size_t __n)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 68 "/usr/include/strings.h" 3
extern char *index (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 96 "/usr/include/strings.h" 3
extern char *rindex (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));






extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int ffsl (long int __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int strcasecmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));






extern int strcasecmp_l (const char *__s1, const char *__s2, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));



extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 4)));



# 495 "/usr/include/string.h" 2 3



extern void explicit_bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));



extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));
# 521 "/usr/include/string.h" 3
extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern size_t strlcpy (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__access__ (__write_only__, 1, 3)));



extern size_t strlcat (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__access__ (__read_write__, 1, 3)));
# 584 "/usr/include/string.h" 3

# 18 "shsl.h" 2
# 1 "/usr/include/assert.h" 1 3
# 92 "/usr/include/assert.h" 3



extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));


extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));






extern _Bool __assert_single_arg (_Bool);



# 19 "shsl.h" 2
# 28 "shsl.h"

# 28 "shsl.h"
typedef enum SHSL_OBJ_TYPE {


    SHSL_NIL = 0, SHSL_SYM,
    SHSL_INT, SHSL_REAL, SHSL_STRING,


    SHSL_CONS, SHSL_VEC, SHSL_MAP,


    SHSL_BUILTIN_FUN, SHSL_USER_FUN,
    SHSL_BUILTIN_MACRO, SHSL_USER_MACRO,


    SHSL_ERR,
} SHSL_OBJ_TYPE;


struct shsl_obj; typedef struct shsl_obj shsl_obj;


struct shsl_sym; typedef struct shsl_sym shsl_sym;
struct shsl_err; typedef struct shsl_err shsl_err;
struct shsl_cons; typedef struct shsl_cons shsl_cons;
struct shsl_vec; typedef struct shsl_vec shsl_vec;



struct shsl_kv; typedef struct shsl_kv shsl_kv;

struct shsl_map; typedef struct shsl_map shsl_map;
struct shsl_builtin_fun; typedef struct shsl_builtin_fun shsl_builtin_fun;
struct shsl_user_fun; typedef struct shsl_user_fun shsl_user_fun;






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

struct shsl_expr;
shsl_obj* shsl_mkuser_fun(shsl_obj* env, shsl_obj* lambda_list,
     struct shsl_expr** body, size_t body_len);
shsl_obj* shsl_mkuser_macro(shsl_obj* env, shsl_obj* lambda_list,
       struct shsl_expr** body, size_t body_len);





shsl_obj* shsl_add_ref(shsl_obj* obj);


void shsl_del_ref(shsl_obj* obj);


void shsl_obj_free(shsl_obj* obj);



shsl_obj* shsl_copy(shsl_obj* obj);
bool shsl_eq(shsl_obj* lhs, shsl_obj* rhs);


void shsl_set(shsl_obj** dst, shsl_obj* src);


void shsl_set_car(shsl_obj* cons_obj, shsl_obj* car);
void shsl_set_cdr(shsl_obj* cons_obj, shsl_obj* cdr);


void shsl_vec_expand(shsl_obj* vec_obj, size_t new_size);
void shsl_vec_push(shsl_obj* vec_obj, shsl_obj* obj);
shsl_obj* shsl_vec_get(shsl_obj* vec_obj, size_t i);
void shsl_vec_set(shsl_obj* vec_obj, size_t i, shsl_obj* new_val);
size_t shsl_vec_length(shsl_obj* vec_obj);
# 127 "shsl.h"
void shsl_map_expand(shsl_obj* map_obj, size_t new_size);

ssize_t shsl_map_index(shsl_obj* map_obj, shsl_obj* key);

shsl_obj* shsl_map_get(shsl_obj* map_obj, shsl_obj* key);
void shsl_map_set(shsl_obj* map_obj,
    shsl_obj* key, shsl_obj* new_val);


typedef enum SHLS_CB_TYPE {SHSL_CB_LIST, SHSL_CB_VEC, SHSL_CB_MAP} SHSL_CB_TYPE;
struct shsl_cb; typedef struct shsl_cb shsl_cb;
shsl_cb shsl_cb_make(SHSL_CB_TYPE type);
void shsl_cb_add(shsl_cb* cb, shsl_obj* obj);
shsl_obj* shsl_cb_get(shsl_cb);


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


shsl_obj* shsl_car(shsl_obj* obj);
shsl_obj* shsl_cdr(shsl_obj* obj);
shsl_obj* shsl_nthcdr(shsl_obj* obj, size_t n);
shsl_obj* shsl_nth(shsl_obj* list_obj, size_t n);

ssize_t shsl_list_len(shsl_obj* list_obj);






typedef enum SHSL_TOKEN_TYPE {

    SHSL_TOK_NIL = 0, SHSL_TOK_SYMBOL,
    SHSL_TOK_INTEGER, SHSL_TOK_REAL, SHSL_TOK_STRING,


    SHSL_TOK_QUOTE, SHSL_TOK_QUASIQUOTE, SHSL_TOK_COMMA,


    SHSL_TOK_OPEN_PAREN, SHSL_TOK_CLOSE_PAREN,
    SHSL_TOK_OPEN_SQUARE, SHSL_TOK_CLOSE_SQUARE,
    SHSL_TOK_OPEN_CURLY, SHSL_TOK_CLOSE_CURLY,



    SHSL_TOK_EOF,

    SHSL_TOK_ERROR,
} SHSL_TOKEN_TYPE;

struct shsl_token; typedef struct shsl_token shsl_token;

struct lexer_pair; typedef struct lexer_pair lexer_pair;


lexer_pair token_off(char* str);


shsl_token empty_token(enum SHSL_TOKEN_TYPE token_type);

lexer_pair error_lexer_pair(const char* errmsg);


bool is_special_char(char c);

bool is_symbol_char(char c);

shsl_token parse_non_special_token(char*c, size_t len);


bool try_parse_integer(char* c, size_t len, long* into);

char* slice_to_fresh_str(const char* c, size_t len);







struct parser_pair; typedef struct parser_pair parser_pair;


parser_pair parse_off(char* str);
# 232 "shsl.h"
parser_pair parse_until(char* str,
   shsl_cb cb,
   enum SHSL_TOKEN_TYPE stop,
   enum SHSL_TOKEN_TYPE* error_on, size_t error_on_len);






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
struct shsl_vec_expr; typedef struct shsl_vec_expr shsl_vec_expr;
struct shsl_map_expr; typedef struct shsl_map_expr shsl_map_expr;
struct shsl_if_expr; typedef struct shsl_if_expr shsl_if_expr;
struct shsl_do_expr; typedef struct shsl_do_expr shsl_do_expr;
struct shsl_do_poking_expr; typedef struct shsl_do_poking_expr shsl_do_poking_expr;
struct shsl_def_expr; typedef struct shsl_def_expr shsl_def_expr;
struct set_expr; typedef struct set_expr set_expr;
struct shsl_funcall_expr; typedef struct shsl_funcall_expr shsl_funcall_expr;


struct shsl_expr; typedef struct shsl_expr shsl_expr;


shsl_expr* shsl_form_to_expr(shsl_obj* form);
bool shsl_expr_is_error(shsl_expr* expr);

void shsl_expr_free(shsl_expr* expr);






shsl_obj* shsl_eval(shsl_expr* form, shsl_obj* env);
shsl_obj* shsl_eval_many_into_vec(shsl_expr** args, size_t args_len,
      shsl_obj* env);





shsl_obj* shsl_builtin_all(shsl_obj* args, shsl_obj* env);
shsl_obj* shsl_builtin_sub(shsl_obj* args, shsl_obj* env);
shsl_obj* shsl_builtin_mul(shsl_obj* args, shsl_obj* env);
shsl_obj* shsl_builtin_div(shsl_obj* args, shsl_obj* env);



shsl_obj* shsl_make_initial_env(void);

shsl_obj* shsl_env_lookup(shsl_obj* env, shsl_obj* key);



void shsl_dbg_fputtok(const shsl_token* tok, FILE* restrict stream);
void shsl_fputobj(const shsl_obj* obj, FILE* restrict stream);



shsl_obj* shsl_eval_str(char* c, shsl_obj* env);






typedef struct shsl_sym {
    shsl_obj* name;
} shsl_sym ;
typedef struct shsl_err {
    shsl_obj* data;
    shsl_obj* msg;
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


    shsl_obj* env;
    shsl_obj*(*apply)(shsl_obj* args, shsl_obj* env);
} shsl_builtin_fun;
typedef struct shsl_user_fun {


    shsl_obj* env;
    shsl_obj* lambda_list;
    shsl_expr** body;
    size_t body_len;
} shsl_user_fun;

typedef struct shsl_obj {

    int ref_count;
    SHSL_OBJ_TYPE type;


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
# 406 "shsl.h"
shsl_obj* shsl_mkint(long l) {
    do { shsl_obj* obj = (shsl_obj*)malloc(sizeof(shsl_obj)); *obj = (shsl_obj){.ref_count = 0, .type = SHSL_INT, .i = l}; return obj; } while(0);
}
shsl_obj* shsl_mkreal(double d) {
    do { shsl_obj* obj = (shsl_obj*)malloc(sizeof(shsl_obj)); *obj = (shsl_obj){.ref_count = 0, .type = SHSL_REAL, .r = d}; return obj; } while(0);
}
shsl_obj* shsl_mkstr(const char* str) {
    char* c = calloc(strlen(str), sizeof(char));
    strcpy(c, str);
    do { shsl_obj* obj = (shsl_obj*)malloc(sizeof(shsl_obj)); *obj = (shsl_obj){.ref_count = 0, .type = SHSL_STRING, .str = c}; return obj; } while(0);
}
shsl_obj* shsl_mksym(const char* name) {
    do { shsl_obj* obj = (shsl_obj*)malloc(sizeof(shsl_obj)); *obj = (shsl_obj){.ref_count = 0, .type = SHSL_SYM, .sym = (shsl_sym){ .name = shsl_add_ref(shsl_mkstr(name)), }}; return obj; } while(0)



           ;
}


shsl_obj* shsl_vmkerr(shsl_obj* data, const char* msg, va_list args) {
    static char buf[1024] = {0};
    vsprintf(buf, msg, args);
# 437 "shsl.h"
    do { shsl_obj* obj = (shsl_obj*)malloc(sizeof(shsl_obj)); *obj = (shsl_obj){.ref_count = 0, .type = SHSL_ERR, .err = (shsl_err) { .msg = shsl_add_ref(shsl_mkstr(buf)), .data = shsl_add_ref(data), }}; return obj; } while(0)




           ;
}
shsl_obj* shsl_mkerr(shsl_obj* data, const char* msg, ...) {
    va_list args;
    
# 446 "shsl.h" 3
   __builtin_c23_va_start(
# 446 "shsl.h"
   args, msg
# 446 "shsl.h" 3
   )
# 446 "shsl.h"
                      ;
    shsl_obj* err = shsl_vmkerr(data, msg, args);
    
# 448 "shsl.h" 3
   __builtin_va_end(
# 448 "shsl.h"
   args
# 448 "shsl.h" 3
   )
# 448 "shsl.h"
               ;
    return err;
}

shsl_obj* shsl_mkcons(shsl_obj* car, shsl_obj* cdr) {
    do { shsl_obj* obj = (shsl_obj*)malloc(sizeof(shsl_obj)); *obj = (shsl_obj){.ref_count = 0, .type = SHSL_CONS, .cons = (shsl_cons) { .car = shsl_add_ref(car), .cdr = shsl_add_ref(cdr), }}; return obj; } while(0)



         ;
}
shsl_obj* shsl_mkvec(size_t initial_capacity) {
    
# 460 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 460 "shsl.h"
   initial_capacity > 0
# 460 "shsl.h" 3
   )), __extension__ ({ if (
# 460 "shsl.h"
   initial_capacity > 0
# 460 "shsl.h" 3
   ) ; else __assert_fail (
# 460 "shsl.h"
   "initial_capacity > 0"
# 460 "shsl.h" 3
   , "shsl.h", 460, __extension__ __PRETTY_FUNCTION__); }))
# 460 "shsl.h"
                               ;

    do { shsl_obj* obj = (shsl_obj*)malloc(sizeof(shsl_obj)); *obj = (shsl_obj){.ref_count = 0, .type = SHSL_VEC, .vec = (shsl_vec) { .buf = calloc(initial_capacity, sizeof(shsl_obj*)), .size = 0, .capacity = initial_capacity, },}; return obj; } while(0)






         ;
}
shsl_obj* shsl_mkmap(size_t initial_capacity) {
    
# 472 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 472 "shsl.h"
   initial_capacity > 0
# 472 "shsl.h" 3
   )), __extension__ ({ if (
# 472 "shsl.h"
   initial_capacity > 0
# 472 "shsl.h" 3
   ) ; else __assert_fail (
# 472 "shsl.h"
   "initial_capacity > 0"
# 472 "shsl.h" 3
   , "shsl.h", 472, __extension__ __PRETTY_FUNCTION__); }))
# 472 "shsl.h"
                               ;
    do { shsl_obj* obj = (shsl_obj*)malloc(sizeof(shsl_obj)); *obj = (shsl_obj){.ref_count = 0, .type = SHSL_MAP, .map = (shsl_map){ .buf = calloc(initial_capacity, sizeof(shsl_kv)), .size = 0, .capacity = initial_capacity, }}; return obj; } while(0)






         ;
}
shsl_obj* shsl_mkbuiltin_fun(shsl_obj* env,
        shsl_obj*(*apply)(shsl_obj* args,
            shsl_obj* env)) {
    
# 485 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 485 "shsl.h"
   (!env) || shsl_is_nil(env) || shsl_is_cons(env) && shsl_is_map(env->cons.car) && "if function env is not null it must be a list of maps!"
# 485 "shsl.h" 3
   )), __extension__ ({ if (
# 485 "shsl.h"
   (!env) || shsl_is_nil(env) || shsl_is_cons(env) && shsl_is_map(env->cons.car) && "if function env is not null it must be a list of maps!"
# 485 "shsl.h" 3
   ) ; else __assert_fail (
# 485 "shsl.h"
   "(!env) || shsl_is_nil(env) || shsl_is_cons(env) && shsl_is_map(env->cons.car) && \"if function env is not null it must be a list of maps!\""
# 485 "shsl.h" 3
   , "shsl.h", 485, __extension__ __PRETTY_FUNCTION__); }))


                                                                
# 488 "shsl.h"
                                                               ;

    do { shsl_obj* obj = (shsl_obj*)malloc(sizeof(shsl_obj)); *obj = (shsl_obj){.ref_count = 0, .type = SHSL_BUILTIN_FUN, .builtin_fun = (shsl_builtin_fun) { .env = env, .apply = apply, }}; return obj; } while(0)





         ;
}
shsl_obj* shsl_mkbuiltin_macro(shsl_obj* env,
          shsl_obj*(*expand)(shsl_obj* args,
        shsl_obj* env)) {
    
# 501 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 501 "shsl.h"
   (!env) || shsl_is_nil(env) || shsl_is_cons(env) && shsl_is_map(env->cons.car) && "if macro env is not null it must be a list of maps!"
# 501 "shsl.h" 3
   )), __extension__ ({ if (
# 501 "shsl.h"
   (!env) || shsl_is_nil(env) || shsl_is_cons(env) && shsl_is_map(env->cons.car) && "if macro env is not null it must be a list of maps!"
# 501 "shsl.h" 3
   ) ; else __assert_fail (
# 501 "shsl.h"
   "(!env) || shsl_is_nil(env) || shsl_is_cons(env) && shsl_is_map(env->cons.car) && \"if macro env is not null it must be a list of maps!\""
# 501 "shsl.h" 3
   , "shsl.h", 501, __extension__ __PRETTY_FUNCTION__); }))


                                                             
# 504 "shsl.h"
                                                            ;

    do { shsl_obj* obj = (shsl_obj*)malloc(sizeof(shsl_obj)); *obj = (shsl_obj){.ref_count = 0, .type = SHSL_BUILTIN_MACRO, .builtin_macro = (shsl_builtin_fun) { .env = env, .apply = expand, }}; return obj; } while(0)





         ;
}
shsl_obj* shsl_mkuser_fun(shsl_obj* env, shsl_obj* lambda_list,
     struct shsl_expr** body, size_t body_len) {
    
# 516 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 516 "shsl.h"
   (!env) || shsl_is_nil(env) || shsl_is_cons(env) && shsl_is_map(env->cons.car) && "if function env is not null it must be a list of maps!"
# 516 "shsl.h" 3
   )), __extension__ ({ if (
# 516 "shsl.h"
   (!env) || shsl_is_nil(env) || shsl_is_cons(env) && shsl_is_map(env->cons.car) && "if function env is not null it must be a list of maps!"
# 516 "shsl.h" 3
   ) ; else __assert_fail (
# 516 "shsl.h"
   "(!env) || shsl_is_nil(env) || shsl_is_cons(env) && shsl_is_map(env->cons.car) && \"if function env is not null it must be a list of maps!\""
# 516 "shsl.h" 3
   , "shsl.h", 516, __extension__ __PRETTY_FUNCTION__); }))


                                                                
# 519 "shsl.h"
                                                               ;
    
# 520 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 520 "shsl.h"
   shsl_is_vec(lambda_list) && "function lambda list must be vector!"
# 520 "shsl.h" 3
   )), __extension__ ({ if (
# 520 "shsl.h"
   shsl_is_vec(lambda_list) && "function lambda list must be vector!"
# 520 "shsl.h" 3
   ) ; else __assert_fail (
# 520 "shsl.h"
   "shsl_is_vec(lambda_list) && \"function lambda list must be vector!\""
# 520 "shsl.h" 3
   , "shsl.h", 520, __extension__ __PRETTY_FUNCTION__); }))
# 520 "shsl.h"
                                                                             ;
    
# 521 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 521 "shsl.h"
   body && "function body cannot be null pointer!"
# 521 "shsl.h" 3
   )), __extension__ ({ if (
# 521 "shsl.h"
   body && "function body cannot be null pointer!"
# 521 "shsl.h" 3
   ) ; else __assert_fail (
# 521 "shsl.h"
   "body && \"function body cannot be null pointer!\""
# 521 "shsl.h" 3
   , "shsl.h", 521, __extension__ __PRETTY_FUNCTION__); }))
# 521 "shsl.h"
                                                          ;
    
# 522 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 522 "shsl.h"
   body_len > 0 && "function body length cannot be null!"
# 522 "shsl.h" 3
   )), __extension__ ({ if (
# 522 "shsl.h"
   body_len > 0 && "function body length cannot be null!"
# 522 "shsl.h" 3
   ) ; else __assert_fail (
# 522 "shsl.h"
   "body_len > 0 && \"function body length cannot be null!\""
# 522 "shsl.h" 3
   , "shsl.h", 522, __extension__ __PRETTY_FUNCTION__); }))
# 522 "shsl.h"
                                                                 ;

    do { shsl_obj* obj = (shsl_obj*)malloc(sizeof(shsl_obj)); *obj = (shsl_obj){.ref_count = 0, .type = SHSL_USER_FUN, .user_fun = (shsl_user_fun) { .env = env, .lambda_list = lambda_list, .body = body, .body_len = body_len, }}; return obj; } while(0)







         ;
}
shsl_obj* shsl_mkuser_macro(shsl_obj* env, shsl_obj* lambda_list,
       struct shsl_expr** body, size_t body_len) {
    
# 536 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 536 "shsl.h"
   (!env) || shsl_is_nil(env) || shsl_is_cons(env) && shsl_is_map(env->cons.car) && "if function env is not null it must be a list of maps!"
# 536 "shsl.h" 3
   )), __extension__ ({ if (
# 536 "shsl.h"
   (!env) || shsl_is_nil(env) || shsl_is_cons(env) && shsl_is_map(env->cons.car) && "if function env is not null it must be a list of maps!"
# 536 "shsl.h" 3
   ) ; else __assert_fail (
# 536 "shsl.h"
   "(!env) || shsl_is_nil(env) || shsl_is_cons(env) && shsl_is_map(env->cons.car) && \"if function env is not null it must be a list of maps!\""
# 536 "shsl.h" 3
   , "shsl.h", 536, __extension__ __PRETTY_FUNCTION__); }))


                                                                
# 539 "shsl.h"
                                                               ;
    
# 540 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 540 "shsl.h"
   shsl_is_vec(lambda_list) && "macro lambda list must be list!"
# 540 "shsl.h" 3
   )), __extension__ ({ if (
# 540 "shsl.h"
   shsl_is_vec(lambda_list) && "macro lambda list must be list!"
# 540 "shsl.h" 3
   ) ; else __assert_fail (
# 540 "shsl.h"
   "shsl_is_vec(lambda_list) && \"macro lambda list must be list!\""
# 540 "shsl.h" 3
   , "shsl.h", 540, __extension__ __PRETTY_FUNCTION__); }))
# 540 "shsl.h"
                                                                        ;
    
# 541 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 541 "shsl.h"
   body && "macro body cannot be null pointer!"
# 541 "shsl.h" 3
   )), __extension__ ({ if (
# 541 "shsl.h"
   body && "macro body cannot be null pointer!"
# 541 "shsl.h" 3
   ) ; else __assert_fail (
# 541 "shsl.h"
   "body && \"macro body cannot be null pointer!\""
# 541 "shsl.h" 3
   , "shsl.h", 541, __extension__ __PRETTY_FUNCTION__); }))
# 541 "shsl.h"
                                                       ;
    
# 542 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 542 "shsl.h"
   body_len > 0 && "macro body length cannot be null!"
# 542 "shsl.h" 3
   )), __extension__ ({ if (
# 542 "shsl.h"
   body_len > 0 && "macro body length cannot be null!"
# 542 "shsl.h" 3
   ) ; else __assert_fail (
# 542 "shsl.h"
   "body_len > 0 && \"macro body length cannot be null!\""
# 542 "shsl.h" 3
   , "shsl.h", 542, __extension__ __PRETTY_FUNCTION__); }))
# 542 "shsl.h"
                                                              ;

    do { shsl_obj* obj = (shsl_obj*)malloc(sizeof(shsl_obj)); *obj = (shsl_obj){.ref_count = 0, .type = SHSL_USER_MACRO, .user_macro = (shsl_user_fun) { .env = env, .lambda_list = lambda_list, .body = body, .body_len = body_len, }}; return obj; } while(0)







         ;
}



shsl_obj* shsl_add_ref(shsl_obj* obj) {







    if(obj->type != SHSL_NIL)
 obj->ref_count++;
    return obj;
}
void shsl_del_ref(shsl_obj* obj) {






    if(obj->type != SHSL_NIL) {
 obj->ref_count--;
 if(obj->ref_count == 0)
     shsl_obj_free(obj);
 if(obj->ref_count < 0)
     fprintf(
# 581 "shsl.h" 3
            stderr
# 581 "shsl.h"
                  , "now you fucked up!\n");
    }
}
void shsl_obj_free(shsl_obj *obj) {





    switch(obj->type) {
    case SHSL_NIL:
 fprintf(
# 592 "shsl.h" 3
        stderr
# 592 "shsl.h"
              , "cannot free NIL! You fucked something up!\n");
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




}


shsl_obj* shsl_copy(shsl_obj* obj) {
    switch(obj->type) {
    case SHSL_NIL: return obj;
    case SHSL_SYM: return shsl_mksym(obj->sym.name->str);
    case SHSL_INT: return shsl_mkint(obj->i);
    case SHSL_REAL: return shsl_mkint(obj->r);
    case SHSL_STRING: return shsl_mkstr(obj->str);

    case SHSL_ERR: return shsl_mkerr(shsl_copy(obj->err.data),
        obj->err.msg->str);

    case SHSL_CONS: return shsl_mkcons(shsl_copy(obj->cons.car),
         shsl_copy(obj->cons.cdr));

    case SHSL_VEC: {
 shsl_obj* copy = shsl_mkvec(obj->vec.size);
 for(size_t i = 0; i<shsl_vec_length(obj); ++i) for(shsl_obj* elt = shsl_vec_get(obj, i); elt; elt = 
# 680 "shsl.h" 3
((void *)0)
# 680 "shsl.h"
)
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
 fprintf(
# 698 "shsl.h" 3
        stderr
# 698 "shsl.h"
              , "[SHSL WARNING]: function object not copyable!\n");
 return 
# 699 "shsl.h" 3
       ((void *)0)
# 699 "shsl.h"
           ;
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
 fprintf(
# 746 "shsl.h" 3
        stderr
# 746 "shsl.h"
              , "TODO: this comparison's not implemeneted yet!\n");
 return false;
    }
}





void shsl_set(shsl_obj** dst, shsl_obj* src) {
    shsl_add_ref(src);
    shsl_del_ref(*dst);
    *dst = src;
}


void shsl_set_car(shsl_obj* cons_obj, shsl_obj* new_car) {
    
# 763 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 763 "shsl.h"
   cons_obj->type == SHSL_CONS
# 763 "shsl.h" 3
   )), __extension__ ({ if (
# 763 "shsl.h"
   cons_obj->type == SHSL_CONS
# 763 "shsl.h" 3
   ) ; else __assert_fail (
# 763 "shsl.h"
   "cons_obj->type == SHSL_CONS"
# 763 "shsl.h" 3
   , "shsl.h", 763, __extension__ __PRETTY_FUNCTION__); }))
# 763 "shsl.h"
                                      ;
    shsl_set(&(cons_obj->cons.car), new_car);
}
void shsl_set_cdr(shsl_obj* cons_obj, shsl_obj* new_cdr) {
    
# 767 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 767 "shsl.h"
   cons_obj->type == SHSL_CONS
# 767 "shsl.h" 3
   )), __extension__ ({ if (
# 767 "shsl.h"
   cons_obj->type == SHSL_CONS
# 767 "shsl.h" 3
   ) ; else __assert_fail (
# 767 "shsl.h"
   "cons_obj->type == SHSL_CONS"
# 767 "shsl.h" 3
   , "shsl.h", 767, __extension__ __PRETTY_FUNCTION__); }))
# 767 "shsl.h"
                                      ;
    shsl_set(&(cons_obj->cons.cdr), new_cdr);
}


void shsl_vec_expand(shsl_obj* vec_obj, size_t new_size) {
    
# 773 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 773 "shsl.h"
   vec_obj->type == SHSL_VEC
# 773 "shsl.h" 3
   )), __extension__ ({ if (
# 773 "shsl.h"
   vec_obj->type == SHSL_VEC
# 773 "shsl.h" 3
   ) ; else __assert_fail (
# 773 "shsl.h"
   "vec_obj->type == SHSL_VEC"
# 773 "shsl.h" 3
   , "shsl.h", 773, __extension__ __PRETTY_FUNCTION__); }))
# 773 "shsl.h"
                                    ;

    if(vec_obj->vec.capacity >= new_size)
 return;
    vec_obj->vec.buf = (shsl_obj**)realloc(vec_obj->vec.buf,
        new_size*sizeof(shsl_obj*));
    vec_obj->vec.capacity = new_size;
}
void shsl_vec_push(shsl_obj* vec_obj, shsl_obj* obj) {
    
# 782 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 782 "shsl.h"
   vec_obj->type == SHSL_VEC
# 782 "shsl.h" 3
   )), __extension__ ({ if (
# 782 "shsl.h"
   vec_obj->type == SHSL_VEC
# 782 "shsl.h" 3
   ) ; else __assert_fail (
# 782 "shsl.h"
   "vec_obj->type == SHSL_VEC"
# 782 "shsl.h" 3
   , "shsl.h", 782, __extension__ __PRETTY_FUNCTION__); }))
# 782 "shsl.h"
                                    ;

    if(vec_obj->vec.size == vec_obj->vec.capacity)
 shsl_vec_expand(vec_obj,
   vec_obj->vec.capacity
   + (vec_obj->vec.capacity/2)
   + 1);


    shsl_add_ref(obj);
    vec_obj->vec.buf[vec_obj->vec.size] = obj;
    vec_obj->vec.size++;
}
shsl_obj* shsl_vec_get(shsl_obj* vec_obj, size_t i) {
    
# 796 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 796 "shsl.h"
   vec_obj->type == SHSL_VEC
# 796 "shsl.h" 3
   )), __extension__ ({ if (
# 796 "shsl.h"
   vec_obj->type == SHSL_VEC
# 796 "shsl.h" 3
   ) ; else __assert_fail (
# 796 "shsl.h"
   "vec_obj->type == SHSL_VEC"
# 796 "shsl.h" 3
   , "shsl.h", 796, __extension__ __PRETTY_FUNCTION__); }))
# 796 "shsl.h"
                                    ;

    if(i >= vec_obj->vec.size)
 return shsl_mkerr(&SHSL_GLOBAL_NIL, "out of bounds array read!");
    return vec_obj->vec.buf[i];
}
void shsl_vec_set(shsl_obj* vec_obj, size_t i, shsl_obj* new_val) {
    
# 803 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 803 "shsl.h"
   vec_obj->type == SHSL_VEC
# 803 "shsl.h" 3
   )), __extension__ ({ if (
# 803 "shsl.h"
   vec_obj->type == SHSL_VEC
# 803 "shsl.h" 3
   ) ; else __assert_fail (
# 803 "shsl.h"
   "vec_obj->type == SHSL_VEC"
# 803 "shsl.h" 3
   , "shsl.h", 803, __extension__ __PRETTY_FUNCTION__); }))
# 803 "shsl.h"
                                    ;


    if(i >= vec_obj->vec.size)
 fprintf(
# 807 "shsl.h" 3
        stderr
# 807 "shsl.h"
              , "out of bounds array write!\n");

    shsl_add_ref(new_val);
    shsl_del_ref(vec_obj->vec.buf[i]);
    vec_obj->vec.buf[i] = new_val;
}
size_t shsl_vec_length(shsl_obj* vec_obj) {
    
# 814 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 814 "shsl.h"
   vec_obj->type == SHSL_VEC
# 814 "shsl.h" 3
   )), __extension__ ({ if (
# 814 "shsl.h"
   vec_obj->type == SHSL_VEC
# 814 "shsl.h" 3
   ) ; else __assert_fail (
# 814 "shsl.h"
   "vec_obj->type == SHSL_VEC"
# 814 "shsl.h" 3
   , "shsl.h", 814, __extension__ __PRETTY_FUNCTION__); }))
# 814 "shsl.h"
                                    ;
    return vec_obj->vec.size;
}


void shsl_map_expand(shsl_obj* map_obj, size_t new_size) {
    
# 820 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 820 "shsl.h"
   map_obj->type == SHSL_MAP
# 820 "shsl.h" 3
   )), __extension__ ({ if (
# 820 "shsl.h"
   map_obj->type == SHSL_MAP
# 820 "shsl.h" 3
   ) ; else __assert_fail (
# 820 "shsl.h"
   "map_obj->type == SHSL_MAP"
# 820 "shsl.h" 3
   , "shsl.h", 820, __extension__ __PRETTY_FUNCTION__); }))
# 820 "shsl.h"
                                    ;

    if (map_obj->map.capacity >= new_size)
 return;
    map_obj->map.buf = (shsl_kv*)realloc(map_obj->map.buf,
      new_size*sizeof(shsl_kv));
    map_obj->map.capacity = new_size;
}
ssize_t shsl_map_index(shsl_obj* map_obj, shsl_obj* key) {
    
# 829 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 829 "shsl.h"
   map_obj->type == SHSL_MAP
# 829 "shsl.h" 3
   )), __extension__ ({ if (
# 829 "shsl.h"
   map_obj->type == SHSL_MAP
# 829 "shsl.h" 3
   ) ; else __assert_fail (
# 829 "shsl.h"
   "map_obj->type == SHSL_MAP"
# 829 "shsl.h" 3
   , "shsl.h", 829, __extension__ __PRETTY_FUNCTION__); }))
# 829 "shsl.h"
                                    ;

    for(size_t i = 0; i<map_obj->map.size; ++i)
 if(shsl_eq(key, map_obj->map.buf[i].k))
     return (ssize_t)i;
    return -1;
}
shsl_obj* shsl_map_get(shsl_obj* map_obj, shsl_obj* key) {
    
# 837 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 837 "shsl.h"
   map_obj->type == SHSL_MAP
# 837 "shsl.h" 3
   )), __extension__ ({ if (
# 837 "shsl.h"
   map_obj->type == SHSL_MAP
# 837 "shsl.h" 3
   ) ; else __assert_fail (
# 837 "shsl.h"
   "map_obj->type == SHSL_MAP"
# 837 "shsl.h" 3
   , "shsl.h", 837, __extension__ __PRETTY_FUNCTION__); }))
# 837 "shsl.h"
                                    ;

    ssize_t i = shsl_map_index(map_obj, key);
    if(i>=0) return map_obj->map.buf[i].v;
    return &SHSL_GLOBAL_NIL;
}
void shsl_map_set(shsl_obj* map_obj, shsl_obj* key, shsl_obj* new_val) {
    
# 844 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 844 "shsl.h"
   map_obj->type == SHSL_MAP
# 844 "shsl.h" 3
   )), __extension__ ({ if (
# 844 "shsl.h"
   map_obj->type == SHSL_MAP
# 844 "shsl.h" 3
   ) ; else __assert_fail (
# 844 "shsl.h"
   "map_obj->type == SHSL_MAP"
# 844 "shsl.h" 3
   , "shsl.h", 844, __extension__ __PRETTY_FUNCTION__); }))
# 844 "shsl.h"
                                    ;

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
     .map_builder.curr_key = 
# 902 "shsl.h" 3
                            ((void *)0)
# 902 "shsl.h"
                                ,
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



typedef struct shsl_token {
    SHSL_TOKEN_TYPE type;
    shsl_obj* obj;
} shsl_token;
# 1071 "shsl.h"
typedef struct lexer_pair {
    shsl_token token;
    char* remaining;
} lexer_pair;



lexer_pair token_off(char* str) {

    if(!str)
 return error_lexer_pair("cannot read null pointer to string!");




    if(*str == '\0')
 return (lexer_pair) {
     .token = empty_token(SHSL_TOK_EOF),
     .remaining = 
# 1089 "shsl.h" 3
                 ((void *)0)
# 1089 "shsl.h"
                     ,
 };


    while(
# 1093 "shsl.h" 3
         ((*__ctype_b_loc ())[(int) ((
# 1093 "shsl.h"
         *str
# 1093 "shsl.h" 3
         ))] & (unsigned short int) _ISspace)
# 1093 "shsl.h"
                      ) str++;


    switch(*str) {

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


    case '\'':
 return (lexer_pair){ .token = empty_token(SHSL_TOK_QUOTE),
        .remaining = str+1, };
    case '`':
 return (lexer_pair){ .token = empty_token(SHSL_TOK_QUASIQUOTE),
        .remaining = str+1, };
    case ',':
 return (lexer_pair){ .token = empty_token(SHSL_TOK_COMMA),
        .remaining = str+1, };



    case '"': {
 char* c = str+1;
 while (*c!='\0' && *c!='"') c++;

 if(*c=='\0') {
     return error_lexer_pair("unterminated string literal!");
 }
 else {
     size_t len = (c-str);

     char* s = calloc(len, sizeof(char));
     memcpy(s, str+1, len);
     s[len-1] = '\0';
     return (lexer_pair) {
  .token = (shsl_token) {
      .type = SHSL_TOK_STRING,
      .obj = shsl_mkstr(s),
  },
  .remaining = c+1,
     };
 }
    }
    }



    char* c = str;
    while(is_symbol_char(*c)) c++;

    return (lexer_pair){
 .token = parse_non_special_token(str, c-str),
 .remaining = c,
    };
}



shsl_token empty_token(SHSL_TOKEN_TYPE token_type) {
    return (shsl_token) {
 .type = token_type,
 .obj = &SHSL_GLOBAL_NIL,
    };
}


lexer_pair error_lexer_pair(const char* errmsg) {
    return (lexer_pair) {
 .token = (shsl_token) {
     .type = SHSL_TOK_ERROR,
     .obj = shsl_mkstr(errmsg),
 },
 .remaining = 
# 1181 "shsl.h" 3
             ((void *)0)
# 1181 "shsl.h"
                 ,
    };
}



bool is_special_char(char c) {
    char* s = "()[]{}'`,\"";
    while(*s!='\0' && *s!=c) s++;
    return *s!='\0';
}

bool is_symbol_char(char c) {
    return 
# 1194 "shsl.h" 3
          ((*__ctype_b_loc ())[(int) ((
# 1194 "shsl.h"
          c
# 1194 "shsl.h" 3
          ))] & (unsigned short int) _ISprint) 
# 1194 "shsl.h"
                     && (!
# 1194 "shsl.h" 3
                          ((*__ctype_b_loc ())[(int) ((
# 1194 "shsl.h"
                          c
# 1194 "shsl.h" 3
                          ))] & (unsigned short int) _ISspace)
# 1194 "shsl.h"
                                    ) && (!is_special_char(c));
}






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
    shsl_token t = (shsl_token) {
 .type = SHSL_TOK_SYMBOL,
 .obj = shsl_mksym(newstr),
    };
    free(newstr);
    return t;
}



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

char* slice_to_fresh_str(const char* c, size_t len) {
    char* fresh = calloc(len+1, sizeof(char));
    memcpy(fresh, c, len);
    fresh[len] = '\0';
    return fresh;
}






typedef struct parser_pair {
    shsl_obj* obj;
    char* remaining;
} parser_pair;
parser_pair parse_off(char* str) {
    lexer_pair lp = token_off(str);
    switch(lp.token.type) {

    case SHSL_TOK_NIL:
    case SHSL_TOK_SYMBOL:
    case SHSL_TOK_INTEGER:
    case SHSL_TOK_REAL:
    case SHSL_TOK_STRING:
 return (parser_pair) {
     .obj = lp.token.obj,
     .remaining = lp.remaining,
 };


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


    case SHSL_TOK_QUOTE: {
 parser_pair pp = parse_off(lp.remaining);
 return (parser_pair) {
     .obj = shsl_mkcons(shsl_mksym("quote"),
          shsl_mkcons(pp.obj, &SHSL_GLOBAL_NIL)),
     .remaining = pp.remaining,
 };
    }
    case SHSL_TOK_QUASIQUOTE: {
 parser_pair pp = parse_off(lp.remaining);
 return (parser_pair) {
     .obj = shsl_mkcons(shsl_mksym("quasiquote"),
          shsl_mkcons(pp.obj, &SHSL_GLOBAL_NIL)),
     .remaining = pp.remaining,
 };
    }
    case SHSL_TOK_COMMA: {
 parser_pair pp = parse_off(lp.remaining);
 return (parser_pair) {
     .obj = shsl_mkcons(shsl_mksym("comma"),
          shsl_mkcons(pp.obj, &SHSL_GLOBAL_NIL)),
     .remaining = pp.remaining,
 };
    }


    case SHSL_TOK_CLOSE_PAREN:
 fprintf(
# 1332 "shsl.h" 3
        stderr
# 1332 "shsl.h"
              , "mismatched close parentheses");
 return (parser_pair){0};
    case SHSL_TOK_CLOSE_SQUARE:
 fprintf(
# 1335 "shsl.h" 3
        stderr
# 1335 "shsl.h"
              , "mismatched close square bracket");
 return (parser_pair){0};
    case SHSL_TOK_CLOSE_CURLY:
 fprintf(
# 1338 "shsl.h" 3
        stderr
# 1338 "shsl.h"
              , "mismatched close curly bracket");
 return (parser_pair){0};
    case SHSL_TOK_ERROR:
 fprintf(
# 1341 "shsl.h" 3
        stderr
# 1341 "shsl.h"
              ,
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




    while(true) {
 lexer_pair lp = token_off(str);
 if(lp.token.type == stop)
     return (parser_pair) {
  .obj = shsl_cb_get(cb),
  .remaining = lp.remaining,
     };

 for(size_t i = 0; i<error_on_len; ++i)
     if(lp.token.type == error_on[i]) {
  fprintf(
# 1369 "shsl.h" 3
         stderr
# 1369 "shsl.h"
               ,
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


 parser_pair pp = parse_off(str);
 shsl_cb_add(&cb, pp.obj);
 str = pp.remaining;
    }
}
# 1404 "shsl.h"
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
    shsl_obj* name;
    shsl_expr* value;
} shsl_def_expr;
typedef struct set_expr {
    shsl_obj* name;
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
 shsl_obj* lookup_symbol;

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
# 1465 "shsl.h"
shsl_expr* shsl_error_expr(shsl_obj* form, const char* msg, ...) {
    va_list args;
    
# 1467 "shsl.h" 3
   __builtin_c23_va_start(
# 1467 "shsl.h"
   args, msg
# 1467 "shsl.h" 3
   )
# 1467 "shsl.h"
                      ;
    shsl_obj* err = shsl_vmkerr(form, msg, args);
    
# 1469 "shsl.h" 3
   __builtin_va_end(
# 1469 "shsl.h"
   args
# 1469 "shsl.h" 3
   )
# 1469 "shsl.h"
               ;



    do { shsl_expr* expr = (shsl_expr*)malloc(sizeof(shsl_expr)); *expr = (shsl_expr){.type = SHSL_EXPR_LITERAL, .literal = err}; return expr; } while(0)
                  ;
}





shsl_expr* shsl_form_to_expr(shsl_obj* form) {
    switch(form->type) {
    case SHSL_INT:
    case SHSL_REAL:
    case SHSL_STRING:
    case SHSL_NIL:
 do { shsl_expr* expr = (shsl_expr*)malloc(sizeof(shsl_expr)); *expr = (shsl_expr){.type = SHSL_EXPR_LITERAL, .literal = shsl_add_ref(form)}; return expr; } while(0)
                                     ;

    case SHSL_SYM:
 do { shsl_expr* expr = (shsl_expr*)malloc(sizeof(shsl_expr)); *expr = (shsl_expr){.type = SHSL_EXPR_LOOKUP, .lookup_symbol = shsl_add_ref(form)}; return expr; } while(0)
                                           ;

    case SHSL_VEC: {
 shsl_expr** elt_exprs = calloc(form->vec.size, sizeof(shsl_expr*));

 for(size_t i = 0; i<shsl_vec_length(form); ++i) for(shsl_obj* form_elt = shsl_vec_get(form, i); form_elt; form_elt = 
# 1497 "shsl.h" 3
((void *)0)
# 1497 "shsl.h"
) {
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

 do { shsl_expr* expr = (shsl_expr*)malloc(sizeof(shsl_expr)); *expr = (shsl_expr){.type = SHSL_EXPR_VEC, .vec_expr = (shsl_vec_expr) { .elts = elt_exprs, .size = shsl_vec_length(form), }}; return expr; } while(0)



         ;
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

 do { shsl_expr* expr = (shsl_expr*)malloc(sizeof(shsl_expr)); *expr = (shsl_expr){.type = SHSL_EXPR_MAP, .map_expr = (shsl_map_expr) { .keys = key_exprs, .vals = val_exprs, .size = form->map.size, }}; return expr; } while(0)




         ;
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
  do { shsl_expr* expr = (shsl_expr*)malloc(sizeof(shsl_expr)); *expr = (shsl_expr){.type = SHSL_EXPR_LITERAL, .literal = shsl_add_ref(literal)}; return expr; } while(0)
                                         ;
     }

     else if(strcmp(s, "if") == 0) {
  if(form_length < 3)
      return shsl_error_expr
                        (form, "malformed if statement, too short");
  if(form_length > 4)
      return shsl_error_expr
                        (form, "malformed if statement, too long");





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

  do { shsl_expr* expr = (shsl_expr*)malloc(sizeof(shsl_expr)); *expr = (shsl_expr){.type = SHSL_EXPR_IF, .if_expr = (shsl_if_expr) { .condition = c, .then_part = t, .else_part = e }}; return expr; } while(0)




          ;
     }

     else if(strcmp(s, "do") == 0)
  
# 1628 "shsl.h" 3
 ((void) sizeof (__assert_single_arg (
# 1628 "shsl.h"
 0 && "TODO: DO"
# 1628 "shsl.h" 3
 )), __extension__ ({ if (
# 1628 "shsl.h"
 0 && "TODO: DO"
# 1628 "shsl.h" 3
 ) ; else __assert_fail (
# 1628 "shsl.h"
 "0 && \"TODO: DO\""
# 1628 "shsl.h" 3
 , "shsl.h", 1628, __extension__ __PRETTY_FUNCTION__); }))
# 1628 "shsl.h"
                        ;
     else if(strcmp(s, "do-poking") == 0)
  
# 1630 "shsl.h" 3
 ((void) sizeof (__assert_single_arg (
# 1630 "shsl.h"
 0 && "TODO: DO-POKING"
# 1630 "shsl.h" 3
 )), __extension__ ({ if (
# 1630 "shsl.h"
 0 && "TODO: DO-POKING"
# 1630 "shsl.h" 3
 ) ; else __assert_fail (
# 1630 "shsl.h"
 "0 && \"TODO: DO-POKING\""
# 1630 "shsl.h" 3
 , "shsl.h", 1630, __extension__ __PRETTY_FUNCTION__); }))
# 1630 "shsl.h"
                               ;
     else if(strcmp(s, "set") == 0)
  
# 1632 "shsl.h" 3
 ((void) sizeof (__assert_single_arg (
# 1632 "shsl.h"
 0 && "TODO: SET"
# 1632 "shsl.h" 3
 )), __extension__ ({ if (
# 1632 "shsl.h"
 0 && "TODO: SET"
# 1632 "shsl.h" 3
 ) ; else __assert_fail (
# 1632 "shsl.h"
 "0 && \"TODO: SET\""
# 1632 "shsl.h" 3
 , "shsl.h", 1632, __extension__ __PRETTY_FUNCTION__); }))
# 1632 "shsl.h"
                         ;
     else if(strcmp(s, "def") == 0)
  
# 1634 "shsl.h" 3
 ((void) sizeof (__assert_single_arg (
# 1634 "shsl.h"
 0 && "TODO: DEF"
# 1634 "shsl.h" 3
 )), __extension__ ({ if (
# 1634 "shsl.h"
 0 && "TODO: DEF"
# 1634 "shsl.h" 3
 ) ; else __assert_fail (
# 1634 "shsl.h"
 "0 && \"TODO: DEF\""
# 1634 "shsl.h" 3
 , "shsl.h", 1634, __extension__ __PRETTY_FUNCTION__); }))
# 1634 "shsl.h"
                         ;
 }

 shsl_expr* fun_expr = shsl_form_to_expr(form->cons.car);
 shsl_expr** args_exprs = calloc(form_length, sizeof(shsl_expr*));
 for(size_t i = 0; i<form_length-1; ++i) {
     args_exprs[i] = shsl_form_to_expr(shsl_nth(form, i+1));
 }
 do { shsl_expr* expr = (shsl_expr*)malloc(sizeof(shsl_expr)); *expr = (shsl_expr){.type = SHSL_EXPR_FUNCALL, .funcall_expr = (shsl_funcall_expr) { .fun_expr = fun_expr, .args_exprs = args_exprs, .args_len = form_length - 1, }}; return expr; } while(0)




         ;
    }
 break;




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
 shsl_expr_free(expr);
 break;
    case SHSL_EXPR_LET:
 
# 1703 "shsl.h" 3
((void) sizeof (__assert_single_arg (
# 1703 "shsl.h"
0 && "TODO: free let expr"
# 1703 "shsl.h" 3
)), __extension__ ({ if (
# 1703 "shsl.h"
0 && "TODO: free let expr"
# 1703 "shsl.h" 3
) ; else __assert_fail (
# 1703 "shsl.h"
"0 && \"TODO: free let expr\""
# 1703 "shsl.h" 3
, "shsl.h", 1703, __extension__ __PRETTY_FUNCTION__); }))
# 1703 "shsl.h"
                                  ;
 break;
    case SHSL_EXPR_WHILE:
 
# 1706 "shsl.h" 3
((void) sizeof (__assert_single_arg (
# 1706 "shsl.h"
0 && "TODO: free while expr"
# 1706 "shsl.h" 3
)), __extension__ ({ if (
# 1706 "shsl.h"
0 && "TODO: free while expr"
# 1706 "shsl.h" 3
) ; else __assert_fail (
# 1706 "shsl.h"
"0 && \"TODO: free while expr\""
# 1706 "shsl.h" 3
, "shsl.h", 1706, __extension__ __PRETTY_FUNCTION__); }))
# 1706 "shsl.h"
                                    ;
 break;
    case SHSL_EXPR_DO:
 
# 1709 "shsl.h" 3
((void) sizeof (__assert_single_arg (
# 1709 "shsl.h"
0 && "TODO: free do expr"
# 1709 "shsl.h" 3
)), __extension__ ({ if (
# 1709 "shsl.h"
0 && "TODO: free do expr"
# 1709 "shsl.h" 3
) ; else __assert_fail (
# 1709 "shsl.h"
"0 && \"TODO: free do expr\""
# 1709 "shsl.h" 3
, "shsl.h", 1709, __extension__ __PRETTY_FUNCTION__); }))
# 1709 "shsl.h"
                                 ;
 break;
    case SHSL_EXPR_DO_POKING:
 
# 1712 "shsl.h" 3
((void) sizeof (__assert_single_arg (
# 1712 "shsl.h"
0 && "TODO: free do poking expr"
# 1712 "shsl.h" 3
)), __extension__ ({ if (
# 1712 "shsl.h"
0 && "TODO: free do poking expr"
# 1712 "shsl.h" 3
) ; else __assert_fail (
# 1712 "shsl.h"
"0 && \"TODO: free do poking expr\""
# 1712 "shsl.h" 3
, "shsl.h", 1712, __extension__ __PRETTY_FUNCTION__); }))
# 1712 "shsl.h"
                                        ;
 break;
    case SHSL_EXPR_DEF:
 
# 1715 "shsl.h" 3
((void) sizeof (__assert_single_arg (
# 1715 "shsl.h"
0 && "TODO: free def expr"
# 1715 "shsl.h" 3
)), __extension__ ({ if (
# 1715 "shsl.h"
0 && "TODO: free def expr"
# 1715 "shsl.h" 3
) ; else __assert_fail (
# 1715 "shsl.h"
"0 && \"TODO: free def expr\""
# 1715 "shsl.h" 3
, "shsl.h", 1715, __extension__ __PRETTY_FUNCTION__); }))
# 1715 "shsl.h"
                                  ;
 break;
    case SHSL_EXPR_SET:
 
# 1718 "shsl.h" 3
((void) sizeof (__assert_single_arg (
# 1718 "shsl.h"
0 && "TODO: free set expr"
# 1718 "shsl.h" 3
)), __extension__ ({ if (
# 1718 "shsl.h"
0 && "TODO: free set expr"
# 1718 "shsl.h" 3
) ; else __assert_fail (
# 1718 "shsl.h"
"0 && \"TODO: free set expr\""
# 1718 "shsl.h" 3
, "shsl.h", 1718, __extension__ __PRETTY_FUNCTION__); }))
# 1718 "shsl.h"
                                  ;
 break;
    case SHSL_EXPR_FN:
 
# 1721 "shsl.h" 3
((void) sizeof (__assert_single_arg (
# 1721 "shsl.h"
0 && "TODO: free fn expr"
# 1721 "shsl.h" 3
)), __extension__ ({ if (
# 1721 "shsl.h"
0 && "TODO: free fn expr"
# 1721 "shsl.h" 3
) ; else __assert_fail (
# 1721 "shsl.h"
"0 && \"TODO: free fn expr\""
# 1721 "shsl.h" 3
, "shsl.h", 1721, __extension__ __PRETTY_FUNCTION__); }))
# 1721 "shsl.h"
                                 ;
 break;
    case SHSL_EXPR_MACRO:
 
# 1724 "shsl.h" 3
((void) sizeof (__assert_single_arg (
# 1724 "shsl.h"
0 && "TODO: free macro expr"
# 1724 "shsl.h" 3
)), __extension__ ({ if (
# 1724 "shsl.h"
0 && "TODO: free macro expr"
# 1724 "shsl.h" 3
) ; else __assert_fail (
# 1724 "shsl.h"
"0 && \"TODO: free macro expr\""
# 1724 "shsl.h" 3
, "shsl.h", 1724, __extension__ __PRETTY_FUNCTION__); }))
# 1724 "shsl.h"
                                    ;
 break;
    case SHSL_EXPR_FUNCALL:
 fprintf(
# 1727 "shsl.h" 3
        stderr
# 1727 "shsl.h"
              , "[SHSL WARNING]: TODO free funcall expr\n");
 break;
    }
}

shsl_obj* shsl_env_mkframe(shsl_obj* syms, shsl_obj* vals) {
    
# 1733 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 1733 "shsl.h"
   syms->type == SHSL_VEC
# 1733 "shsl.h" 3
   )), __extension__ ({ if (
# 1733 "shsl.h"
   syms->type == SHSL_VEC
# 1733 "shsl.h" 3
   ) ; else __assert_fail (
# 1733 "shsl.h"
   "syms->type == SHSL_VEC"
# 1733 "shsl.h" 3
   , "shsl.h", 1733, __extension__ __PRETTY_FUNCTION__); }))
# 1733 "shsl.h"
                                 ;
    
# 1734 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 1734 "shsl.h"
   vals->type == SHSL_VEC
# 1734 "shsl.h" 3
   )), __extension__ ({ if (
# 1734 "shsl.h"
   vals->type == SHSL_VEC
# 1734 "shsl.h" 3
   ) ; else __assert_fail (
# 1734 "shsl.h"
   "vals->type == SHSL_VEC"
# 1734 "shsl.h" 3
   , "shsl.h", 1734, __extension__ __PRETTY_FUNCTION__); }))
# 1734 "shsl.h"
                                 ;
    
# 1735 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 1735 "shsl.h"
   syms->vec.size == vals->vec.size
# 1735 "shsl.h" 3
   )), __extension__ ({ if (
# 1735 "shsl.h"
   syms->vec.size == vals->vec.size
# 1735 "shsl.h" 3
   ) ; else __assert_fail (
# 1735 "shsl.h"
   "syms->vec.size == vals->vec.size"
# 1735 "shsl.h" 3
   , "shsl.h", 1735, __extension__ __PRETTY_FUNCTION__); }))
# 1735 "shsl.h"
                                           ;

    shsl_obj* frame = shsl_mkmap(syms->vec.size);
    for(size_t i = 0; i<shsl_vec_length(syms); ++i) for(shsl_obj* sym = shsl_vec_get(syms, i); sym; sym = 
# 1738 "shsl.h" 3
   ((void *)0)
# 1738 "shsl.h"
   ) {
 shsl_obj* val = shsl_vec_get(vals, i);
 shsl_map_set(frame, sym, val);
    }
    return frame;
}



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
 
# 1810 "shsl.h" 3
((void) sizeof (__assert_single_arg (
# 1810 "shsl.h"
0 && "TODO"
# 1810 "shsl.h" 3
)), __extension__ ({ if (
# 1810 "shsl.h"
0 && "TODO"
# 1810 "shsl.h" 3
) ; else __assert_fail (
# 1810 "shsl.h"
"0 && \"TODO\""
# 1810 "shsl.h" 3
, "shsl.h", 1810, __extension__ __PRETTY_FUNCTION__); }))
# 1810 "shsl.h"
                   ;
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
# 1855 "shsl.h"
shsl_obj* shsl_builtin_vecget(shsl_obj* args, shsl_obj* env) { const char* shsl_fun_name = "vecget"; do { if(!(shsl_is_vec((args)))) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "shsl_is_vec((args))" "failed!", shsl_fun_name); } while(0); do { (void)env; do { if(!((shsl_vec_length(args)) == 2)) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "(shsl_vec_length(args)) == 2" "failed!", shsl_fun_name); } while(0); do { if(!(shsl_vec_get(args, 0)->type == (SHSL_VEC))) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "shsl_vec_get(args, 0)->type == (SHSL_VEC)" "failed!", shsl_fun_name); } while(0); do { if(!(shsl_vec_get(args, 1)->type == (SHSL_INT))) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "shsl_vec_get(args, 1)->type == (SHSL_INT)" "failed!", shsl_fun_name); } while(0); return shsl_vec_get(args, (size_t)shsl_vec_get(args, 1)->i); } while(0); }
# 1864 "shsl.h"
shsl_obj* shsl_builtin_add(shsl_obj* args, shsl_obj* env) { const char* shsl_fun_name = "+"; do { if(!(shsl_is_vec((args)))) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "shsl_is_vec((args))" "failed!", shsl_fun_name); } while(0); do { (void)env; for(size_t i = 0; i<shsl_vec_length(args); ++i) for(shsl_obj* elt = shsl_vec_get(args, i); elt; elt = 
# 1864 "shsl.h" 3
((void *)0)
# 1864 "shsl.h"
) do { if(!(shsl_vec_get(args, i)->type == (SHSL_INT) || shsl_vec_get(args, i)->type == (SHSL_REAL))) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "shsl_vec_get(args, i)->type == (SHSL_INT) || shsl_vec_get(args, i)->type == (SHSL_REAL)" "failed!", shsl_fun_name); } while(0); long intsum = 0; double longsum = 0.0; for(size_t i = 0; i<shsl_vec_length(args); ++i) for(shsl_obj* elt = shsl_vec_get(args, i); elt; elt = 
# 1864 "shsl.h" 3
((void *)0)
# 1864 "shsl.h"
) { if(elt->type == SHSL_REAL) goto longsum; else intsum += elt->i; } return shsl_mkint(intsum); longsum: for(size_t i = 0; i<shsl_vec_length(args); ++i) for(shsl_obj* elt = shsl_vec_get(args, i); elt; elt = 
# 1864 "shsl.h" 3
((void *)0)
# 1864 "shsl.h"
) longsum += shsl_is_int(elt)?(double)elt->i:elt->r; return shsl_mkreal(longsum); } while(0); }
# 1885 "shsl.h"
shsl_obj* shsl_builtin_sub(shsl_obj* args, shsl_obj* env) { const char* shsl_fun_name = "-"; do { if(!(shsl_is_vec((args)))) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "shsl_is_vec((args))" "failed!", shsl_fun_name); } while(0); do { (void)env; for(size_t i = 0; i<shsl_vec_length(args); ++i) for(shsl_obj* elt = shsl_vec_get(args, i); elt; elt = 
# 1885 "shsl.h" 3
((void *)0)
# 1885 "shsl.h"
) do { if(!(shsl_vec_get(args, i)->type == (SHSL_INT) || shsl_vec_get(args, i)->type == (SHSL_REAL))) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "shsl_vec_get(args, i)->type == (SHSL_INT) || shsl_vec_get(args, i)->type == (SHSL_REAL)" "failed!", shsl_fun_name); } while(0); if(args->vec.size == 0) return shsl_mkint(0); if(args->vec.size == 1) return shsl_mkint(shsl_vec_get(args, 0)->i); long acc = args->vec.buf[0]->i; for(size_t i = 1; i<shsl_vec_length(args); ++i) { acc -= shsl_vec_get(args, i)->i; } return shsl_mkint(acc); } while(0); }
# 1902 "shsl.h"
shsl_obj* shsl_builtin_mul(shsl_obj* args, shsl_obj* env) { const char* shsl_fun_name = "*"; do { if(!(shsl_is_vec((args)))) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "shsl_is_vec((args))" "failed!", shsl_fun_name); } while(0); do { (void)env; for(size_t i = 0; i<shsl_vec_length(args); ++i) for(shsl_obj* elt = shsl_vec_get(args, i); elt; elt = 
# 1902 "shsl.h" 3
((void *)0)
# 1902 "shsl.h"
) do { if(!(shsl_vec_get(args, i)->type == (SHSL_INT))) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "shsl_vec_get(args, i)->type == (SHSL_INT)" "failed!", shsl_fun_name); } while(0); long acc = 1; for(size_t i = 0; i<shsl_vec_length(args); ++i) for(shsl_obj* elt = shsl_vec_get(args, i); elt; elt = 
# 1902 "shsl.h" 3
((void *)0)
# 1902 "shsl.h"
) acc *= elt->i; return shsl_mkint(acc); } while(0); }
# 1914 "shsl.h"
shsl_obj* shsl_builtin_div(shsl_obj* args, shsl_obj* env) { const char* shsl_fun_name = "/"; do { if(!(shsl_is_vec((args)))) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "shsl_is_vec((args))" "failed!", shsl_fun_name); } while(0); do { (void)env; do { if(!((shsl_vec_length(args)) == 2)) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "(shsl_vec_length(args)) == 2" "failed!", shsl_fun_name); } while(0); do { if(!(shsl_vec_get(args, 0)->type == (SHSL_INT) || shsl_vec_get(args, 0)->type == (SHSL_REAL))) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "shsl_vec_get(args, 0)->type == (SHSL_INT) || shsl_vec_get(args, 0)->type == (SHSL_REAL)" "failed!", shsl_fun_name); } while(0); do { if(!(shsl_vec_get(args, 1)->type == (SHSL_INT) || shsl_vec_get(args, 1)->type == (SHSL_REAL))) return shsl_mkerr(&SHSL_GLOBAL_NIL, "in function %s, assertion " "shsl_vec_get(args, 1)->type == (SHSL_INT) || shsl_vec_get(args, 1)->type == (SHSL_REAL)" "failed!", shsl_fun_name); } while(0); if(args->vec.buf[0]->type == SHSL_INT && args->vec.buf[1]->type == SHSL_INT && args->vec.buf[1]->i != 0 && (args->vec.buf[0]->i % args->vec.buf[1]->i) == 0) return shsl_mkint(args->vec.buf[0]->i/args->vec.buf[1]->i); double a = args->vec.buf[0]->type == SHSL_INT ? args->vec.buf[0]->i : args->vec.buf[0]->r; double b = args->vec.buf[1]->type == SHSL_INT ? args->vec.buf[1]->i : args->vec.buf[1]->r; if(b == 0.0) return shsl_mkerr(args, "in function /: division by zero!"); return shsl_mkreal(a/b); } while(0); }
# 1941 "shsl.h"
shsl_obj* shsl_make_initial_env(void) {
    shsl_obj* frame_obj = shsl_mkmap(20);
    shsl_obj* env_obj = shsl_mkcons(frame_obj, &SHSL_GLOBAL_NIL);

    shsl_obj* t = shsl_mksym("t");
    shsl_map_set(frame_obj, t, t);




    shsl_map_set(frame_obj, shsl_mksym("+"),
   shsl_mkbuiltin_fun(env_obj, shsl_builtin_add));
    shsl_map_set(frame_obj, shsl_mksym("-"),
   shsl_mkbuiltin_fun(env_obj, shsl_builtin_sub));
    shsl_map_set(frame_obj, shsl_mksym("*"),
   shsl_mkbuiltin_fun(env_obj, shsl_builtin_mul));
    shsl_map_set(frame_obj, shsl_mksym("/"),
   shsl_mkbuiltin_fun(env_obj, shsl_builtin_div));
# 1981 "shsl.h"
    return env_obj;
}
shsl_obj* shsl_env_lookup(shsl_obj* env, shsl_obj* key) {
    
# 1984 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 1984 "shsl.h"
   key->type == SHSL_SYM
# 1984 "shsl.h" 3
   )), __extension__ ({ if (
# 1984 "shsl.h"
   key->type == SHSL_SYM
# 1984 "shsl.h" 3
   ) ; else __assert_fail (
# 1984 "shsl.h"
   "key->type == SHSL_SYM"
# 1984 "shsl.h" 3
   , "shsl.h", 1984, __extension__ __PRETTY_FUNCTION__); }))
# 1984 "shsl.h"
                                ;
    if(shsl_is_nil(env))
 return shsl_mkerr(key, "symbol not found!");

    
# 1988 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 1988 "shsl.h"
   env->type == SHSL_CONS
# 1988 "shsl.h" 3
   )), __extension__ ({ if (
# 1988 "shsl.h"
   env->type == SHSL_CONS
# 1988 "shsl.h" 3
   ) ; else __assert_fail (
# 1988 "shsl.h"
   "env->type == SHSL_CONS"
# 1988 "shsl.h" 3
   , "shsl.h", 1988, __extension__ __PRETTY_FUNCTION__); }))
# 1988 "shsl.h"
                                 ;
    
# 1989 "shsl.h" 3
   ((void) sizeof (__assert_single_arg (
# 1989 "shsl.h"
   env->cons.car->type == SHSL_MAP
# 1989 "shsl.h" 3
   )), __extension__ ({ if (
# 1989 "shsl.h"
   env->cons.car->type == SHSL_MAP
# 1989 "shsl.h" 3
   ) ; else __assert_fail (
# 1989 "shsl.h"
   "env->cons.car->type == SHSL_MAP"
# 1989 "shsl.h" 3
   , "shsl.h", 1989, __extension__ __PRETTY_FUNCTION__); }))
# 1989 "shsl.h"
                                          ;

    ssize_t i = shsl_map_index(env->cons.car, key);
    if(i>=0)
 return env->cons.car->map.buf[i].v;
    return shsl_env_lookup(env->cons.cdr, key);
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
 fprintf(
# 2114 "shsl.h" 3
        stdout
# 2114 "shsl.h"
              , "SHSL_BUILTIN_FUN_%p", (void*)obj);
 break;
    case SHSL_USER_FUN:
 fprintf(
# 2117 "shsl.h" 3
        stdout
# 2117 "shsl.h"
              , "SHSL_USER_FUN_%p", (void*)obj);
 break;
    case SHSL_BUILTIN_MACRO:
 fprintf(
# 2120 "shsl.h" 3
        stdout
# 2120 "shsl.h"
              , "SHSL_BUILTIN_MACRO_%p", (void*)obj);
 break;
    case SHSL_USER_MACRO:
 fprintf(
# 2123 "shsl.h" 3
        stdout
# 2123 "shsl.h"
              , "SHSL_USER_MACRO_%p", (void*)obj);
 break;
    };
}



shsl_obj* shsl_eval_str(char* c, shsl_obj* env) {
    parser_pair p = parse_off(c);


    shsl_add_ref(p.obj);
    shsl_expr* expr = shsl_form_to_expr(p.obj);
    shsl_del_ref(p.obj);

    shsl_obj* res = shsl_eval(expr, env);
    shsl_expr_free(expr);
    return res;
}
# 6 "tests.c" 2
# 14 "tests.c"
bool sym_eq(const char* s, shsl_obj* sym_obj) {
    return sym_obj->type == SHSL_SYM
 && strcmp(s, sym_obj->sym.name->str) == 0;
}

bool int_eq(long i, shsl_obj* int_obj) {
    return int_obj->type == SHSL_INT && int_obj->i == i;
}




void test_list_builder(void) {
    shsl_cb cb = shsl_cb_make(SHSL_CB_LIST);
    shsl_cb_add(&cb, shsl_mksym("hello"));
    shsl_cb_add(&cb, shsl_mksym("darkness"));
    shsl_cb_add(&cb, shsl_mksym("my"));
    shsl_cb_add(&cb, shsl_mksym("old"));
    shsl_cb_add(&cb, shsl_mksym("friend"));
    shsl_obj* lst = shsl_cb_get(cb);

    
# 35 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 35 "tests.c"
   lst->type == SHSL_CONS && "list builder did not return list"
# 35 "tests.c" 3
   )), __extension__ ({ if (
# 35 "tests.c"
   lst->type == SHSL_CONS && "list builder did not return list"
# 35 "tests.c" 3
   ) ; else __assert_fail (
# 35 "tests.c"
   "lst->type == SHSL_CONS && \"list builder did not return list\""
# 35 "tests.c" 3
   , "tests.c", 35, __extension__ __PRETTY_FUNCTION__); }))
# 35 "tests.c"
                                                                       ;
    
# 36 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 36 "tests.c"
   shsl_list_length(lst) == 5 && "incorrect length of built list!"
# 36 "tests.c" 3
   )), __extension__ ({ if (
# 36 "tests.c"
   shsl_list_length(lst) == 5 && "incorrect length of built list!"
# 36 "tests.c" 3
   ) ; else __assert_fail (
# 36 "tests.c"
   "shsl_list_length(lst) == 5 && \"incorrect length of built list!\""
# 36 "tests.c" 3
   , "tests.c", 36, __extension__ __PRETTY_FUNCTION__); }))
# 36 "tests.c"
                                                                          ;

    
# 38 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 38 "tests.c"
   sym_eq("hello", shsl_nth(lst, 0)) && "string symbol has incorrect value!"
# 38 "tests.c" 3
   )), __extension__ ({ if (
# 38 "tests.c"
   sym_eq("hello", shsl_nth(lst, 0)) && "string symbol has incorrect value!"
# 38 "tests.c" 3
   ) ; else __assert_fail (
# 38 "tests.c"
   "sym_eq(\"hello\", shsl_nth(lst, 0)) && \"string symbol has incorrect value!\""
# 38 "tests.c" 3
   , "tests.c", 38, __extension__ __PRETTY_FUNCTION__); }))
# 38 "tests.c"
                                                                                    ;
    
# 39 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 39 "tests.c"
   sym_eq("darkness", shsl_nth(lst, 1)) && "string symbol has incorrect value!"
# 39 "tests.c" 3
   )), __extension__ ({ if (
# 39 "tests.c"
   sym_eq("darkness", shsl_nth(lst, 1)) && "string symbol has incorrect value!"
# 39 "tests.c" 3
   ) ; else __assert_fail (
# 39 "tests.c"
   "sym_eq(\"darkness\", shsl_nth(lst, 1)) && \"string symbol has incorrect value!\""
# 39 "tests.c" 3
   , "tests.c", 39, __extension__ __PRETTY_FUNCTION__); }))
# 39 "tests.c"
                                                                                       ;
    
# 40 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 40 "tests.c"
   sym_eq("my", shsl_nth(lst, 2)) && "string symbol has incorrect value!"
# 40 "tests.c" 3
   )), __extension__ ({ if (
# 40 "tests.c"
   sym_eq("my", shsl_nth(lst, 2)) && "string symbol has incorrect value!"
# 40 "tests.c" 3
   ) ; else __assert_fail (
# 40 "tests.c"
   "sym_eq(\"my\", shsl_nth(lst, 2)) && \"string symbol has incorrect value!\""
# 40 "tests.c" 3
   , "tests.c", 40, __extension__ __PRETTY_FUNCTION__); }))
# 40 "tests.c"
                                                                                 ;
    
# 41 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 41 "tests.c"
   sym_eq("old", shsl_nth(lst, 3)) && "string symbol has incorrect value!"
# 41 "tests.c" 3
   )), __extension__ ({ if (
# 41 "tests.c"
   sym_eq("old", shsl_nth(lst, 3)) && "string symbol has incorrect value!"
# 41 "tests.c" 3
   ) ; else __assert_fail (
# 41 "tests.c"
   "sym_eq(\"old\", shsl_nth(lst, 3)) && \"string symbol has incorrect value!\""
# 41 "tests.c" 3
   , "tests.c", 41, __extension__ __PRETTY_FUNCTION__); }))
# 41 "tests.c"
                                                                                  ;
    
# 42 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 42 "tests.c"
   sym_eq("friend", shsl_nth(lst, 4)) && "string symbol has incorrect value!"
# 42 "tests.c" 3
   )), __extension__ ({ if (
# 42 "tests.c"
   sym_eq("friend", shsl_nth(lst, 4)) && "string symbol has incorrect value!"
# 42 "tests.c" 3
   ) ; else __assert_fail (
# 42 "tests.c"
   "sym_eq(\"friend\", shsl_nth(lst, 4)) && \"string symbol has incorrect value!\""
# 42 "tests.c" 3
   , "tests.c", 42, __extension__ __PRETTY_FUNCTION__); }))
# 42 "tests.c"
                                                                                     ;

    shsl_obj_free(lst);
}
void test_vec_builder(void) {
    shsl_cb cb = shsl_cb_make(SHSL_CB_VEC);
    shsl_cb_add(&cb, shsl_mkint(1));
    shsl_cb_add(&cb, shsl_mkint(2));
    shsl_cb_add(&cb, shsl_mkint(3));

    shsl_obj* vec = shsl_cb_get(cb);
    
# 53 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 53 "tests.c"
   vec->type == SHSL_VEC && "vector builder did not yield vector!"
# 53 "tests.c" 3
   )), __extension__ ({ if (
# 53 "tests.c"
   vec->type == SHSL_VEC && "vector builder did not yield vector!"
# 53 "tests.c" 3
   ) ; else __assert_fail (
# 53 "tests.c"
   "vec->type == SHSL_VEC && \"vector builder did not yield vector!\""
# 53 "tests.c" 3
   , "tests.c", 53, __extension__ __PRETTY_FUNCTION__); }))
# 53 "tests.c"
                                                                          ;
    
# 54 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 54 "tests.c"
   vec->vec.size == 3 && "vector builder gave vector of wrong length!"
# 54 "tests.c" 3
   )), __extension__ ({ if (
# 54 "tests.c"
   vec->vec.size == 3 && "vector builder gave vector of wrong length!"
# 54 "tests.c" 3
   ) ; else __assert_fail (
# 54 "tests.c"
   "vec->vec.size == 3 && \"vector builder gave vector of wrong length!\""
# 54 "tests.c" 3
   , "tests.c", 54, __extension__ __PRETTY_FUNCTION__); }))
# 54 "tests.c"
                                                                              ;

    
# 56 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 56 "tests.c"
   int_eq(1, vec->vec.buf[0]) && "vec builder gave vec with wrong values!"
# 56 "tests.c" 3
   )), __extension__ ({ if (
# 56 "tests.c"
   int_eq(1, vec->vec.buf[0]) && "vec builder gave vec with wrong values!"
# 56 "tests.c" 3
   ) ; else __assert_fail (
# 56 "tests.c"
   "int_eq(1, vec->vec.buf[0]) && \"vec builder gave vec with wrong values!\""
# 56 "tests.c" 3
   , "tests.c", 56, __extension__ __PRETTY_FUNCTION__); }))
# 56 "tests.c"
                                                                                  ;
    
# 57 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 57 "tests.c"
   int_eq(2, vec->vec.buf[1]) && "vec builder gave vec with wrong values!"
# 57 "tests.c" 3
   )), __extension__ ({ if (
# 57 "tests.c"
   int_eq(2, vec->vec.buf[1]) && "vec builder gave vec with wrong values!"
# 57 "tests.c" 3
   ) ; else __assert_fail (
# 57 "tests.c"
   "int_eq(2, vec->vec.buf[1]) && \"vec builder gave vec with wrong values!\""
# 57 "tests.c" 3
   , "tests.c", 57, __extension__ __PRETTY_FUNCTION__); }))
# 57 "tests.c"
                                                                                  ;
    
# 58 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 58 "tests.c"
   int_eq(3, vec->vec.buf[2]) && "vec builder gave vec with wrong values!"
# 58 "tests.c" 3
   )), __extension__ ({ if (
# 58 "tests.c"
   int_eq(3, vec->vec.buf[2]) && "vec builder gave vec with wrong values!"
# 58 "tests.c" 3
   ) ; else __assert_fail (
# 58 "tests.c"
   "int_eq(3, vec->vec.buf[2]) && \"vec builder gave vec with wrong values!\""
# 58 "tests.c" 3
   , "tests.c", 58, __extension__ __PRETTY_FUNCTION__); }))
# 58 "tests.c"
                                                                                  ;

    shsl_obj_free(vec);
}
void test_map_builder(void) {
    shsl_cb cb0 = shsl_cb_make(SHSL_CB_MAP);
    
# 64 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 64 "tests.c"
   shsl_cb_get(cb0)->type == SHSL_MAP
# 64 "tests.c" 3
   )), __extension__ ({ if (
# 64 "tests.c"
   shsl_cb_get(cb0)->type == SHSL_MAP
# 64 "tests.c" 3
   ) ; else __assert_fail (
# 64 "tests.c"
   "shsl_cb_get(cb0)->type == SHSL_MAP"
# 64 "tests.c" 3
   , "tests.c", 64, __extension__ __PRETTY_FUNCTION__); }))
# 64 "tests.c"
                                             ;

    shsl_cb cb1 = shsl_cb_make(SHSL_CB_MAP);
    shsl_cb_add(&cb1, shsl_mkint(1));
    shsl_cb_add(&cb1, shsl_mkint(2));
    shsl_cb_add(&cb1, shsl_mkint(3));
    shsl_obj* err = shsl_cb_get(cb1);
    
# 71 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 71 "tests.c"
   err->type == SHSL_ERR && "erroneous map construction did not return error!"
# 71 "tests.c" 3
   )), __extension__ ({ if (
# 71 "tests.c"
   err->type == SHSL_ERR && "erroneous map construction did not return error!"
# 71 "tests.c" 3
   ) ; else __assert_fail (
# 71 "tests.c"
   "err->type == SHSL_ERR && \"erroneous map construction did not return error!\""
# 71 "tests.c" 3
   , "tests.c", 71, __extension__ __PRETTY_FUNCTION__); }))
                                                          
# 72 "tests.c"
                                                         ;
    shsl_obj_free(err);





    shsl_obj_free(cb1.map_builder.curr_key);

    shsl_cb cb2 = shsl_cb_make(SHSL_CB_MAP);
    shsl_cb_add(&cb2, shsl_mksym("one"));
    shsl_cb_add(&cb2, shsl_mkint(1));
    shsl_cb_add(&cb2, shsl_mksym("two"));
    shsl_cb_add(&cb2, shsl_mkint(2));

    shsl_obj* map = shsl_cb_get(cb2);

    
# 89 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 89 "tests.c"
   map->map.size == 2 && "map builder gave map of wrong length!"
# 89 "tests.c" 3
   )), __extension__ ({ if (
# 89 "tests.c"
   map->map.size == 2 && "map builder gave map of wrong length!"
# 89 "tests.c" 3
   ) ; else __assert_fail (
# 89 "tests.c"
   "map->map.size == 2 && \"map builder gave map of wrong length!\""
# 89 "tests.c" 3
   , "tests.c", 89, __extension__ __PRETTY_FUNCTION__); }))
# 89 "tests.c"
                                                                        ;

    
# 91 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 91 "tests.c"
   sym_eq("one", map->map.buf[0].k)
# 91 "tests.c" 3
   )), __extension__ ({ if (
# 91 "tests.c"
   sym_eq("one", map->map.buf[0].k)
# 91 "tests.c" 3
   ) ; else __assert_fail (
# 91 "tests.c"
   "sym_eq(\"one\", map->map.buf[0].k)"
# 91 "tests.c" 3
   , "tests.c", 91, __extension__ __PRETTY_FUNCTION__); }))
# 91 "tests.c"
                                           ;
    
# 92 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 92 "tests.c"
   int_eq(1, map->map.buf[0].v)
# 92 "tests.c" 3
   )), __extension__ ({ if (
# 92 "tests.c"
   int_eq(1, map->map.buf[0].v)
# 92 "tests.c" 3
   ) ; else __assert_fail (
# 92 "tests.c"
   "int_eq(1, map->map.buf[0].v)"
# 92 "tests.c" 3
   , "tests.c", 92, __extension__ __PRETTY_FUNCTION__); }))
# 92 "tests.c"
                                       ;
    
# 93 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 93 "tests.c"
   sym_eq("two", map->map.buf[1].k)
# 93 "tests.c" 3
   )), __extension__ ({ if (
# 93 "tests.c"
   sym_eq("two", map->map.buf[1].k)
# 93 "tests.c" 3
   ) ; else __assert_fail (
# 93 "tests.c"
   "sym_eq(\"two\", map->map.buf[1].k)"
# 93 "tests.c" 3
   , "tests.c", 93, __extension__ __PRETTY_FUNCTION__); }))
# 93 "tests.c"
                                           ;
    
# 94 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 94 "tests.c"
   int_eq(2, map->map.buf[1].v)
# 94 "tests.c" 3
   )), __extension__ ({ if (
# 94 "tests.c"
   int_eq(2, map->map.buf[1].v)
# 94 "tests.c" 3
   ) ; else __assert_fail (
# 94 "tests.c"
   "int_eq(2, map->map.buf[1].v)"
# 94 "tests.c" 3
   , "tests.c", 94, __extension__ __PRETTY_FUNCTION__); }))
# 94 "tests.c"
                                       ;
}

void test_collection_builders(void) {
    fprintf("[SHSL TESTS]: running test ""test_list_builder()""\n"); test_list_builder();;
    fprintf("[SHSL TESTS]: running test ""test_vec_builder()""\n"); test_vec_builder();;
    fprintf("[SHSL TESTS]: running test ""test_map_builder()""\n"); test_map_builder();;
}


void test_list_literals(void) {
    shsl_obj* lst = shsl_eval_str("'(a b c)", 
# 105 "tests.c" 3
                                             ((void *)0)
# 105 "tests.c"
                                                 );
    
# 106 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 106 "tests.c"
   lst->type == SHSL_CONS
# 106 "tests.c" 3
   )), __extension__ ({ if (
# 106 "tests.c"
   lst->type == SHSL_CONS
# 106 "tests.c" 3
   ) ; else __assert_fail (
# 106 "tests.c"
   "lst->type == SHSL_CONS"
# 106 "tests.c" 3
   , "tests.c", 106, __extension__ __PRETTY_FUNCTION__); }))
# 106 "tests.c"
                                 ;
}
void test_vec_literals(void) {
    shsl_obj* vec = shsl_eval_str("'[a b c]", 
# 109 "tests.c" 3
                                             ((void *)0)
# 109 "tests.c"
                                                 );
    
# 110 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 110 "tests.c"
   vec->type == SHSL_VEC
# 110 "tests.c" 3
   )), __extension__ ({ if (
# 110 "tests.c"
   vec->type == SHSL_VEC
# 110 "tests.c" 3
   ) ; else __assert_fail (
# 110 "tests.c"
   "vec->type == SHSL_VEC"
# 110 "tests.c" 3
   , "tests.c", 110, __extension__ __PRETTY_FUNCTION__); }))
# 110 "tests.c"
                                ;
}
void test_map_literals(void) {
    shsl_obj* map = shsl_eval_str("'{a b c c}", 
# 113 "tests.c" 3
                                               ((void *)0)
# 113 "tests.c"
                                                   );
    
# 114 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 114 "tests.c"
   map->type == SHSL_MAP
# 114 "tests.c" 3
   )), __extension__ ({ if (
# 114 "tests.c"
   map->type == SHSL_MAP
# 114 "tests.c" 3
   ) ; else __assert_fail (
# 114 "tests.c"
   "map->type == SHSL_MAP"
# 114 "tests.c" 3
   , "tests.c", 114, __extension__ __PRETTY_FUNCTION__); }))
# 114 "tests.c"
                                ;
}
void test_collection_literals(void) {
    fprintf("[SHSL TESTS]: running test ""test_list_literals()""\n"); test_list_literals();;
    fprintf("[SHSL TESTS]: running test ""test_vec_literals()""\n"); test_vec_literals();;
    fprintf("[SHSL TESTS]: running test ""test_map_literals()""\n"); test_map_literals();;
}


void test_error(void) {
    shsl_obj* s = shsl_mkerr(&SHSL_GLOBAL_NIL, "%s",
        "test error generation");
    
# 126 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 126 "tests.c"
   strcmp(s->err.msg->str, "test error generation") == 0
# 126 "tests.c" 3
   )), __extension__ ({ if (
# 126 "tests.c"
   strcmp(s->err.msg->str, "test error generation") == 0
# 126 "tests.c" 3
   ) ; else __assert_fail (
# 126 "tests.c"
   "strcmp(s->err.msg->str, \"test error generation\") == 0"
# 126 "tests.c" 3
   , "tests.c", 126, __extension__ __PRETTY_FUNCTION__); }))
# 126 "tests.c"
                                                                ;
}

void test_some_shit(void) {
    shsl_obj* a = shsl_eval_str("'a", 
# 130 "tests.c" 3
                                     ((void *)0)
# 130 "tests.c"
                                         );
    
# 131 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 131 "tests.c"
   a->type == SHSL_SYM && "symbol literal did not return a symbol"
# 131 "tests.c" 3
   )), __extension__ ({ if (
# 131 "tests.c"
   a->type == SHSL_SYM && "symbol literal did not return a symbol"
# 131 "tests.c" 3
   ) ; else __assert_fail (
# 131 "tests.c"
   "a->type == SHSL_SYM && \"symbol literal did not return a symbol\""
# 131 "tests.c" 3
   , "tests.c", 131, __extension__ __PRETTY_FUNCTION__); }))
                                                
# 132 "tests.c"
                                               ;

    shsl_obj* b = shsl_eval_str("(if 'a 'b 'c)", 
# 134 "tests.c" 3
                                                ((void *)0)
# 134 "tests.c"
                                                    );
    
# 135 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 135 "tests.c"
   b->type == SHSL_SYM && "conditional returning symbol literal didn't return symbol"
# 135 "tests.c" 3
   )), __extension__ ({ if (
# 135 "tests.c"
   b->type == SHSL_SYM && "conditional returning symbol literal didn't return symbol"
# 135 "tests.c" 3
   ) ; else __assert_fail (
# 135 "tests.c"
   "b->type == SHSL_SYM && \"conditional returning symbol literal didn't return symbol\""
# 135 "tests.c" 3
   , "tests.c", 135, __extension__ __PRETTY_FUNCTION__); }))
                                                                   
# 136 "tests.c"
                                                                  ;

    shsl_obj* env = shsl_make_initial_env();
    shsl_obj* c = shsl_eval_str("(+ 2 2)", env);
    
# 140 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 140 "tests.c"
   c->type == SHSL_INT && "2+2 didn't return an integer"
# 140 "tests.c" 3
   )), __extension__ ({ if (
# 140 "tests.c"
   c->type == SHSL_INT && "2+2 didn't return an integer"
# 140 "tests.c" 3
   ) ; else __assert_fail (
# 140 "tests.c"
   "c->type == SHSL_INT && \"2+2 didn't return an integer\""
# 140 "tests.c" 3
   , "tests.c", 140, __extension__ __PRETTY_FUNCTION__); }))
# 140 "tests.c"
                                                                ;
    
# 141 "tests.c" 3
   ((void) sizeof (__assert_single_arg (
# 141 "tests.c"
   c->i == 4 && "2+2 should equal 4"
# 141 "tests.c" 3
   )), __extension__ ({ if (
# 141 "tests.c"
   c->i == 4 && "2+2 should equal 4"
# 141 "tests.c" 3
   ) ; else __assert_fail (
# 141 "tests.c"
   "c->i == 4 && \"2+2 should equal 4\""
# 141 "tests.c" 3
   , "tests.c", 141, __extension__ __PRETTY_FUNCTION__); }))
# 141 "tests.c"
                                            ;
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    puts("RUNNING TESTS...");
    fprintf("[SHSL TESTS]: running test ""test_some_shit()""\n"); test_some_shit();;
    fprintf("[SHSL TESTS]: running test ""test_collection_builders()""\n"); test_collection_builders();;
    fprintf("[SHSL TESTS]: running test ""test_collection_literals()""\n"); test_collection_literals();;
    fprintf("[SHSL TESTS]: running test ""test_error()""\n"); test_error();;
    puts("IF YOU SEE THIS AND NOTHING BLEW UP ALL TESTS PASS!");


    puts("(error messages above are likely from test error generation, ignore them)");
    return 0;
}
