/* GNUC/MSVC 2002+: redefine file structures for stdstreams */
#if !defined (_MSC_VER) || _MSC_VER > 1200
#ifndef _FILE_DEFINED
#define _FILE_DEFINED
typedef struct _iobuf {
	char *_ptr;
	int   _cnt;
	char *_base;
	int   _flag;
	int   _file;
	int   _charbuf;
	int   _bufsiz;
	char *_tmpfname;
} FILE;
#endif /* _FILE_DEFINED */
extern __declspec(dllimport) FILE _iob[];
FILE* __cdecl __iob_func(void) { return _iob; }
FILE* __cdecl __acrt_iob_func(unsigned i) { return _iob + i; }
FILE* (__cdecl * _imp___iob_func)(void) = __iob_func;
FILE* (__cdecl * _imp____iob_func)(void) = __iob_func;
FILE* (__cdecl * __imp___iob_func)(void) = __iob_func;
FILE* (__cdecl * __imp____iob_func)(void) = __iob_func;
FILE* (__cdecl * _imp___acrt_iob_func)(unsigned) = __acrt_iob_func;
FILE* (__cdecl * _imp____acrt_iob_func)(unsigned) = __acrt_iob_func;
FILE* (__cdecl * __imp___acrt_iob_func)(unsigned) = __acrt_iob_func;
FILE* (__cdecl * __imp____acrt_iob_func)(unsigned) = __acrt_iob_func;
#endif /* !defined (_MSC_VER) || _MSC_VER > 1200 */

/* time is imported as __time32 for most compilers (after ignoring __time64) */
#if defined(__i386) || defined(__i386__) || defined(_M_IX86)
extern __declspec(dllimport) signed int time(signed int *second);
signed int __cdecl __time32(signed int *second) {  return time(second); }
/* GNUC/MSVC 2002+: time imports */
#if !defined(_MSC_VER) || _MSC_VER > 1200
signed int (__cdecl * _imp___time32)(signed int*) = __time32;
signed int (__cdecl * _imp____time32)(signed int*) = __time32;
signed int (__cdecl * __imp___time32)(signed int*) = __time32;
signed int (__cdecl * __imp____time32)(signed int*) = __time32;
#endif /* !defined(_MSC_VER) || _MSC_VER > 1200 */
#endif /* defined(__i386) || defined(__i386__) || defined(_M_IX86) */