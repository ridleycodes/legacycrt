#ifndef wchar_t
typedef unsigned short wchar_t;
#endif
#ifdef __GNUC__
#define CRT_USED __attribute__((used))
#else
#define CRT_USED
#endif
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
FILE* (__cdecl * my_imp_iob_func)(void) = __iob_func;
FILE* (__cdecl * my_imp_acrt_iob_func)(unsigned) = __acrt_iob_func;
#ifdef _MSC_VER
#if defined(__i386) || defined(__i386__) || defined(_M_IX86)
#pragma comment(linker, "/include:_my_imp_iob_func")
#pragma comment(linker, "/alternatename:__imp___iob_func=_my_imp_iob_func")
#pragma comment(linker, "/alternatename:__imp____iob_func=_my_imp_iob_func")
#pragma comment(linker, "/alternatename:___imp___iob_func=_my_imp_iob_func")
#pragma comment(linker, "/include:_my_imp_acrt_iob_func")
#pragma comment(linker, "/alternatename:__imp___acrt_iob_func=_my_imp_acrt_iob_func")
#pragma comment(linker, "/alternatename:__imp____acrt_iob_func=_my_imp_acrt_iob_func")
#pragma comment(linker, "/alternatename:___imp___acrt_iob_func=_my_imp_acrt_iob_func")
#else
#pragma comment(linker, "/include:my_imp_iob_func")
#pragma comment(linker, "/alternatename:__imp___iob_func=my_imp_iob_func")
#pragma comment(linker, "/alternatename:__imp____iob_func=my_imp_iob_func")
#pragma comment(linker, "/alternatename:___imp___iob_func=my_imp_iob_func")
#pragma comment(linker, "/include:my_imp_acrt_iob_func")
#pragma comment(linker, "/alternatename:__imp___acrt_iob_func=my_imp_acrt_iob_func")
#pragma comment(linker, "/alternatename:__imp____acrt_iob_func=my_imp_acrt_iob_func")
#pragma comment(linker, "/alternatename:___imp___acrt_iob_func=my_imp_acrt_iob_func")
#endif
#else /* _MSC_VER */
FILE* (__cdecl * CRT_USED _imp___iob_func)(void) = __iob_func;
FILE* (__cdecl * CRT_USED _imp____iob_func)(void) = __iob_func;
FILE* (__cdecl * CRT_USED __imp___iob_func)(void) = __iob_func;
FILE* (__cdecl * CRT_USED __imp____iob_func)(void) = __iob_func;
FILE* (__cdecl * CRT_USED _imp___acrt_iob_func)(unsigned) = __acrt_iob_func;
FILE* (__cdecl * CRT_USED _imp____acrt_iob_func)(unsigned) = __acrt_iob_func;
FILE* (__cdecl * CRT_USED __imp___acrt_iob_func)(unsigned) = __acrt_iob_func;
FILE* (__cdecl * CRT_USED __imp____acrt_iob_func)(unsigned) = __acrt_iob_func;
#endif /* _MSC_VER */
#endif /* !defined (_MSC_VER) || _MSC_VER > 1200 */
#ifdef _MSC_VER
int _fltused = 1;
#endif /* _MSC_VER */
#if defined(__i386) || defined(__i386__) || defined(_M_IX86)
extern __declspec(dllimport) signed int time(signed int *second);
signed int __cdecl __time32(signed int *second) {  return time(second); }
#if defined(_MSC_VER) && _MSC_VER > 1200
signed int (__cdecl * my_imp_time32)(signed int*) = __time32;
#pragma comment(linker, "/include:_my_imp_time32")
#pragma comment(linker, "/alternatename:__imp___time32=_my_imp_time32")
#pragma comment(linker, "/alternatename:__imp____time32=_my_imp_time32")
#pragma comment(linker, "/alternatename:___imp___time32=_my_imp_time32")
#else /* _MSC_VER */
signed int (__cdecl * CRT_USED _imp___time32)(signed int*) = __time32;
signed int (__cdecl * CRT_USED _imp____time32)(signed int*) = __time32;
signed int (__cdecl * CRT_USED __imp___time32)(signed int*) = __time32;
signed int (__cdecl * CRT_USED __imp____time32)(signed int*) = __time32;
#endif /* defined(_MSC_VER) && _MSC_VER > 1200 */
#ifdef __GNUC__
void CRT_USED _pei386_runtime_relocator(void) {}
#endif /* __GNUC__ */
#endif /* defined(__i386) || defined(__i386__) || defined(_M_IX86) */
#ifdef __LEGACY_CRT_CRT_IS_DLL
extern int __stdcall DllMain(void* hinstDLL, unsigned long fdwReason, void* lpReserved);
int __stdcall DllMainCRTStartup(void* hinstDLL, unsigned long fdwReason, void* lpReserved) {    
    return DllMain(hinstDLL, fdwReason, lpReserved);
}
#else /* __LEGACY_CRT_CRT_IS_DLL */
extern __declspec(dllimport) void __declspec(noreturn) _exit(int status);
#ifdef __LEGACY_CRT_CONSOLE_SUBSYSTEM
#if defined(UNICODE) || defined(_UNICODE)
int wmain(int argc, wchar_t* argv[]);
#ifdef __GNUC__
void CRT_USED __wmain(void) {}
#endif /* __GNUC__ */
#ifndef __LEGACY_CRT_USE_OLD_CRT
extern __declspec(dllimport) int __cdecl __wgetmainargs(int *argc, wchar_t ***argv, wchar_t ***env, int dowildcard, int *startupinfo);
void __cdecl wmainCRTStartup(void) {
    int argc;
    wchar_t** argv;
    wchar_t** envp;
    int err = 0;

    __wgetmainargs(&argc, &argv, &envp, 0, &err);

    err = wmain(argc, argv);

    _exit(err);
}
#else /* __LEGACY_CRT_USE_OLD_CRT */
/* crtdll.dll implementation */
extern __declspec(dllimport) wchar_t* __stdcall GetCommandLineW(void);
extern __declspec(dllimport) wchar_t** __stdcall CommandLineToArgvW(const wchar_t* lpCmdLine, int* pNumArgs);
extern __declspec(dllimport) void* __stdcall LocalFree(void* hMem);

void __cdecl wmainCRTStartup(void) {
    int argc;
    wchar_t** argv;
    int err;

    argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    err = wmain(argc, argv);

    LocalFree(argv);
    _exit(err);
}
#endif /* __LEGACY_CRT_USE_OLD_CRT */
#else /* defined(UNICODE) || defined(_UNICODE) */
int main(int argc, char* argv[]);
#ifdef __GNUC__
void CRT_USED __main(void) {}
#endif /* __GNUC__ */
#ifdef __LEGACY_CRT_USE_OLD_CRT
extern __declspec(dllimport) void __cdecl __GetMainArgs(int *argc, char ***argv, char ***env, int dowildcard);
#define MAINARGS_CALL(argc, argv, envp, wild, startup) __GetMainArgs(argc, argv, envp, wild)
#else /* __LEGACY_CRT_USE_OLD_CRT */
extern __declspec(dllimport) int __cdecl __getmainargs(int *argc, char ***argv, char ***env, int dowildcard, int *startupinfo);
#define MAINARGS_CALL(argc, argv, envp, wild, startup) __getmainargs(argc, argv, envp, wild, startup)
#endif /* __LEGACY_CRT_USE_OLD_CRT */

void __cdecl mainCRTStartup(void) {
    int argc;
    char** argv;
    char** envp;
    int err;

    MAINARGS_CALL(&argc, &argv, &envp, 0, &err);

    err = main(argc, argv);

    _exit(err);
}
#endif /* defined(UNICODE) || defined(_UNICODE) */
#elif defined(__LEGACY_CRT_WINDOWS_SUBSYSTEM)
#if defined(UNICODE) || defined(_UNICODE)
extern int __stdcall wWinMain(void* hInstance, void* hPrevInstance, wchar_t* lpCmdLine, int nCmdShow);
extern __declspec(dllimport) void* __stdcall GetModuleHandleW(const wchar_t* lpModuleName);
extern __declspec(dllimport) wchar_t* __stdcall GetCommandLineW(void);
extern __declspec(dllimport) void __stdcall GetStartupInfoW(void* lpStartupInfo);
extern __declspec(dllimport) void __stdcall ExitProcess(unsigned int status);

void __cdecl wWinMainCRTStartup(void) {
    void* hInstance;
    wchar_t* lpszCommandLine;
    int nShowCmd;
    int result;

    struct {
        unsigned long cb;
        wchar_t* lpReserved;
        wchar_t* lpDesktop;
        wchar_t* lpTitle;
        unsigned long dwX;
        unsigned long dwY;
        unsigned long dwXSize;
        unsigned long dwYSize;
        unsigned long dwXCountChars;
        unsigned long dwYCountChars;
        unsigned long dwFillAttribute;
        unsigned long dwFlags;
        unsigned short wShowWindow;
        unsigned short cbReserved2;
        unsigned char* lpReserved2;
        void* hStdInput;
        void* hStdOutput;
        void* hStdError;
    } startupInfo;

    hInstance = GetModuleHandleW(0);
    lpszCommandLine = GetCommandLineW();
    
    if (*lpszCommandLine == L'"') {
        lpszCommandLine++;
        while (*lpszCommandLine && *lpszCommandLine != L'"') lpszCommandLine++;
        if (*lpszCommandLine == L'"') lpszCommandLine++;
    } else {
        while (*lpszCommandLine > L' ') lpszCommandLine++;
    }
    
    while (*lpszCommandLine && *lpszCommandLine <= L' ') lpszCommandLine++;

    startupInfo.cb = sizeof(startupInfo);
    GetStartupInfoW(&startupInfo);
    nShowCmd = (startupInfo.dwFlags & 1) ? startupInfo.wShowWindow : 10;

    result = wWinMain(hInstance, 0, lpszCommandLine, nShowCmd);

    ExitProcess(result);
}
#else /* defined(UNICODE) || defined(_UNICODE) */
extern int __stdcall WinMain(void* hInstance, void* hPrevInstance, const char *lpCmdLine, int nCmdShow);
extern __declspec(dllimport) void* __stdcall GetModuleHandleA(const char* lpModuleName);
extern __declspec(dllimport) char* __stdcall GetCommandLineA(void);
extern __declspec(dllimport) void __stdcall GetStartupInfoA(void* lpStartupInfo);
extern __declspec(dllimport) void __stdcall ExitProcess(unsigned int status);

void __cdecl WinMainCRTStartup(void) {
	void* hInstance;
    char* lpszCommandLine;
    int nShowCmd;
    int result;

    struct {
        unsigned long cb;
        char* lpReserved;
        char* lpDesktop;
        char* lpTitle;
        unsigned long dwX;
        unsigned long dwY;
        unsigned long dwXSize;
        unsigned long dwYSize;
        unsigned long dwXCountChars;
        unsigned long dwYCountChars;
        unsigned long dwFillAttribute;
        unsigned long dwFlags;
        unsigned short wShowWindow;
        unsigned short cbReserved2;
        unsigned char* lpReserved2;
        void* hStdInput;
        void* hStdOutput;
        void* hStdError;
    } startupInfo;

    hInstance = GetModuleHandleA(0);
    lpszCommandLine = GetCommandLineA();
    if (*lpszCommandLine == '"') {
        lpszCommandLine++;
        while (*lpszCommandLine && *lpszCommandLine != '"') lpszCommandLine++;
        if (*lpszCommandLine == '"') lpszCommandLine++;
    } else
        while (*lpszCommandLine > ' ') lpszCommandLine++;
    while (*lpszCommandLine && *lpszCommandLine <= ' ') lpszCommandLine++;

    startupInfo.cb = sizeof(startupInfo);
    GetStartupInfoA(&startupInfo);
    nShowCmd = (startupInfo.dwFlags & 1) ? startupInfo.wShowWindow : 10;

    result = WinMain(hInstance, 0, lpszCommandLine, nShowCmd);

    ExitProcess(result);
}
#endif /* defined(UNICODE) || defined(_UNICODE) */
#endif /* __LEGACY_CRT_WINDOWS_SUBSYSTEM */
#endif /* __LEGACY_CRT_CRT_IS_DLL */