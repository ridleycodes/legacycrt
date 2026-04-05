#if defined(__i386) || defined(__i386__) || defined(_M_IX86)
typedef struct _IMAGE_THUNK_DATA {
    union {
        unsigned long ForwarderString;
        unsigned long Function;
        unsigned long Ordinal;
        unsigned long AddressOfData;
    } u1;
} IMAGE_THUNK_DATA;
#else /* defined(__i386) || defined(__i386__) || defined(_M_IX86) */
typedef struct _IMAGE_THUNK_DATA {
    union {
        unsigned long long ForwarderString;
        unsigned long long Function;
        unsigned long long Ordinal;
        unsigned long long AddressOfData;
    } u1;
} IMAGE_THUNK_DATA;
#endif /* defined(__i386) || defined(__i386__) || defined(_M_IX86) */

#if defined(_MSC_VER) && _MSC_VER <= 1300
typedef struct ImgDelayDescr {
    unsigned long grAttrs;
    const char *szName;
    void **phmod;
    IMAGE_THUNK_DATA *pIAT;
    const IMAGE_THUNK_DATA *pINT;
    const IMAGE_THUNK_DATA *pBoundIAT;
    const IMAGE_THUNK_DATA *pUnloadIAT;
    unsigned long dwTimeStamp;
} ImgDelayDescr;
#else /* defined(_MSC_VER) && _MSC_VER <= 1300 */
typedef struct ImgDelayDescr {
    unsigned long grAttrs;
    unsigned long rvaDLLName;
    unsigned long rvaHmod;
    unsigned long rvaIAT;
    unsigned long rvaINT;
    unsigned long rvaBoundIAT;
    unsigned long rvaUnloadIAT;
    unsigned long dwTimeStamp;
} ImgDelayDescr;
#endif /* defined(_MSC_VER) && _MSC_VER <= 1300 */

typedef struct DelayLoadProc {
    int fImportByName;
    union {
        const char *szProcName;
        unsigned long dwOrdinal;
    } u1;
} DelayLoadProc;

typedef struct DelayLoadInfo {
    unsigned long cb;
    const ImgDelayDescr *pidd;
    int **ppfn;
    const char *szDll;
    DelayLoadProc dlp;
    void* hmodCur;
    int* pfnCur;
    unsigned long dwLastError;
} DelayLoadInfo;

typedef int* (__stdcall *PfnDliHook)(unsigned dliNotify, DelayLoadInfo *pdli);
#if defined(_MSC_VER) && _MSC_VER <= 1300
PfnDliHook __pfnDliFailureHook2 = 0;
#else /* defined(_MSC_VER) && _MSC_VER <= 1300 */
PfnDliHook __pfnDliFailureHook = 0;
#endif /* defined(_MSC_VER) && _MSC_VER <= 1300 */