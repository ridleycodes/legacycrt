/* type definitions */
#ifndef wchar_t
typedef unsigned short wchar_t;
#endif

/* GNUC LTO: do not discard entry point and function stubs */
#ifdef __GNUC__
#define CRT_USED __attribute__((used))
#else
#define CRT_USED
#endif

/* MSVC: _fltused on usage of floating point */
#ifdef _MSC_VER
int _fltused = 1;
#endif /* _MSC_VER */

/* GNUC: PEI relocator, still don't know what it's for */
#ifdef __GNUC__
#if defined(__i386) || defined(__i386__) || defined(_M_IX86)
void CRT_USED _pei386_runtime_relocator(void) {}
#endif /* defined(__i386) || defined(__i386__) || defined(_M_IX86) */
#endif /* __GNUC__ */

/*-------DLL ENTRY POINT------*/
#ifdef __LEGACY_CRT_CRT_IS_DLL
extern int __stdcall DllMain(void* hinstDLL, unsigned long fdwReason, void* lpReserved);
int CRT_USED __stdcall DllMainCRTStartup(void* hinstDLL, unsigned long fdwReason, void* lpReserved) {    
    return DllMain(hinstDLL, fdwReason, lpReserved);
}
#else /* __LEGACY_CRT_CRT_IS_DLL */
/*-------CONSOLE ENTRY POINT------*/
#ifdef __LEGACY_CRT_CONSOLE_SUBSYSTEM
extern __declspec(dllimport) void __declspec(noreturn) _exit(int status);
#if defined(UNICODE) || defined(_UNICODE)
int wmain(int argc, wchar_t* argv[]);
#ifndef __LEGACY_CRT_USE_OLD_CRT
extern __declspec(dllimport) int __cdecl __wgetmainargs(int *argc, wchar_t ***argv, wchar_t ***env, int dowildcard, int *startupinfo);
#ifdef __GNUC__
/* GNUC: startup symbol is always non-unicode */
void CRT_USED __cdecl mainCRTStartup(void) {
#else
void CRT_USED __cdecl wmainCRTStartup(void) {
#endif /* __GNUC__ */
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
#ifdef __GNUC__
/* GNUC: startup symbol is always non-unicode */
void CRT_USED __cdecl mainCRTStartup(void) {
#else
void CRT_USED __cdecl wmainCRTStartup(void) {
#endif /* __GNUC__ */
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
void CRT_USED __cdecl mainCRTStartup(void) {
    int argc;
    char** argv;
    char** envp;
    int err;

    MAINARGS_CALL(&argc, &argv, &envp, 0, &err);

    err = main(argc, argv);

    _exit(err);
}
#endif /* defined(UNICODE) || defined(_UNICODE) */
/*-------WINDOWS ENTRY POINT------*/
#elif defined(__LEGACY_CRT_WINDOWS_SUBSYSTEM)
#if defined(UNICODE) || defined(_UNICODE)
extern int __stdcall wWinMain(void* hInstance, void* hPrevInstance, wchar_t* lpCmdLine, int nCmdShow);
extern __declspec(dllimport) void* __stdcall GetModuleHandleW(const wchar_t* lpModuleName);
extern __declspec(dllimport) wchar_t* __stdcall GetCommandLineW(void);
extern __declspec(dllimport) void __stdcall GetStartupInfoW(void* lpStartupInfo);
extern __declspec(dllimport) void __stdcall ExitProcess(unsigned int status);
#ifdef __GNUC__
/* GNUC: startup symbol is always non-unicode */
void CRT_USED __cdecl WinMainCRTStartup(void) {
#else /* __GNUC__ */
void CRT_USED __cdecl wWinMainCRTStartup(void) {
#endif /* __GNUC__ */
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

void CRT_USED __cdecl WinMainCRTStartup(void) {
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