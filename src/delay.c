typedef struct _IMAGE_DOS_HEADER {
    unsigned short e_magic;
    unsigned short e_cblp;
    unsigned short e_cp;
    unsigned short e_crlc;
    unsigned short e_cparhdr;
    unsigned short e_minalloc;
    unsigned short e_maxalloc;
    unsigned short e_ss;
    unsigned short e_sp;
    unsigned short e_csum;
    unsigned short e_ip;
    unsigned short e_cs;
    unsigned short e_lfarlc;
    unsigned short e_ovno;
    unsigned short e_res[4];
    unsigned short e_oemid;
    unsigned short e_oeminfo;
    unsigned short e_res2[10];
    long   		   e_lfanew;
} IMAGE_DOS_HEADER;

#if defined(__i386) || defined(__i386__) || defined(_M_IX86)
typedef struct _IMAGE_THUNK_DATA {
    union {
        unsigned long ForwarderString;
        unsigned long Function;
        unsigned long Ordinal;
        unsigned long AddressOfData;
    } u1;
} IMAGE_THUNK_DATA;
#define IMAGE_SNAP_BY_ORDINAL(Ordinal) ((Ordinal & 0x80000000) != 0)
typedef unsigned long ULONG_PTR;
#else /* defined(__i386) || defined(__i386__) || defined(_M_IX86) */
typedef struct _IMAGE_THUNK_DATA {
    union {
        unsigned long long ForwarderString;
        unsigned long long Function;
        unsigned long long Ordinal;
        unsigned long long AddressOfData;
    } u1;
} IMAGE_THUNK_DATA;
#define IMAGE_SNAP_BY_ORDINAL(Ordinal) ((Ordinal & 0x8000000000000000) != 0)
typedef unsigned __int64 ULONG_PTR;
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

typedef struct _IMAGE_IMPORT_BY_NAME {
    unsigned short Hint;
    char Name[1];
} IMAGE_IMPORT_BY_NAME;

extern const IMAGE_DOS_HEADER __ImageBase;
extern void __stdcall RaiseException(unsigned long dwExceptionCode, unsigned long dwExceptionFlags, unsigned long nNumberOfArguments, const ULONG_PTR *lpArguments);
extern void * __stdcall LoadLibraryA(const char *lpLibFileName);
extern int * __stdcall GetProcAddress(void *hModule, const char *lpProcName);
extern unsigned long __stdcall GetLastError(void);

typedef int* (__stdcall *PfnDliHook)(unsigned dliNotify, DelayLoadInfo *pdli);
#if defined(_MSC_VER) && _MSC_VER <= 1300
extern PfnDliHook __pfnDliNotifyHook2;
extern PfnDliHook __pfnDliFailureHook2;
#define PFN_NOTIFY __pfnDliNotifyHook2
#define PFN_FAILURE __pfnDliFailureHook2
#else /* defined(_MSC_VER) && _MSC_VER <= 1300 */
extern PfnDliHook __pfnDliNotifyHook;
extern PfnDliHook __pfnDliFailureHook;
#define PFN_NOTIFY __pfnDliNotifyHook
#define PFN_FAILURE __pfnDliFailureHook
#endif /* defined(_MSC_VER) && _MSC_VER <= 1300 */

#if defined(_MSC_VER) && _MSC_VER <= 1300
int * __stdcall __delayLoadHelper(const ImgDelayDescr *pidd, IMAGE_THUNK_DATA *pIATEntry) {
#else /* defined(_MSC_VER) && _MSC_VER <= 1300 */
int * __stdcall __delayLoadHelper2(const ImgDelayDescr *pidd, IMAGE_THUNK_DATA *pIATEntry) {
#endif /* defined(_MSC_VER) && _MSC_VER <= 1300 */
    DelayLoadInfo dli = {0};
    int index;
    IMAGE_THUNK_DATA *pIAT;
    IMAGE_THUNK_DATA *pINT;
    void **phMod;

#if defined(_MSC_VER) && _MSC_VER <= 1300
    pIAT = pidd->pIAT;
    pINT = pidd->pINT;
    phMod = pidd->phmod;
    index = (int)(pIATEntry - pIAT);

    dli.szDll = pidd->szName;
    dli.dlp.fImportByName = !IMAGE_SNAP_BY_ORDINAL(pINT[index].u1.Ordinal);
    if (dli.dlp.fImportByName) {
        IMAGE_IMPORT_BY_NAME *piibn = (IMAGE_IMPORT_BY_NAME *)(ULONG_PTR)pINT[index].u1.AddressOfData;
#else /* defined(_MSC_VER) && _MSC_VER <= 1300 */
    pIAT = ((IMAGE_THUNK_DATA*) (((ULONG_PTR) (pidd->rvaIAT)) + ((ULONG_PTR) &__ImageBase)));
    pINT = ((IMAGE_THUNK_DATA*) (((ULONG_PTR) (pidd->rvaINT)) + ((ULONG_PTR) &__ImageBase)));
    phMod = ((void**) (((ULONG_PTR) (pidd->rvaHmod)) + ((ULONG_PTR) &__ImageBase)));
    index = (int)(pIATEntry - pIAT);

    dli.szDll = ((void*) (((ULONG_PTR) (pidd->rvaDLLName)) + ((ULONG_PTR) &__ImageBase)));
    dli.dlp.fImportByName = !IMAGE_SNAP_BY_ORDINAL(pINT[index].u1.Ordinal);
    if (dli.dlp.fImportByName) {
        /* u1.AddressOfData points to a IMAGE_IMPORT_BY_NAME struct */
        IMAGE_IMPORT_BY_NAME *piibn = ((IMAGE_IMPORT_BY_NAME*) (((ULONG_PTR) (pINT[index].u1.AddressOfData)) + ((ULONG_PTR) &__ImageBase)));
#endif /* defined(_MSC_VER) && _MSC_VER <= 1300 */
        dli.dlp.u1.szProcName = (const char*) &piibn->Name;
    } else {
        dli.dlp.u1.dwOrdinal = pINT[index].u1.Ordinal & 0xffff;
    }

    dli.cb = sizeof(dli);
    dli.pidd = pidd;
    dli.ppfn = (int**) &pIAT[index].u1.Function;

    if (PFN_NOTIFY != 0) {
        dli.pfnCur = PFN_NOTIFY(0, &dli);
        if (dli.pfnCur != 0) {
            pIAT[index].u1.Function = (ULONG_PTR) dli.pfnCur;
            if (PFN_NOTIFY != 0)
                PFN_NOTIFY(5, &dli);

            return dli.pfnCur;
        }
    }
    dli.hmodCur = *phMod;

    if (dli.hmodCur == 0)
    {
        if (PFN_NOTIFY != 0)
            dli.hmodCur = (void*)PFN_NOTIFY(1, &dli);
        if (dli.hmodCur == 0)
        {
            dli.hmodCur = LoadLibraryA(dli.szDll);
            if (dli.hmodCur == 0)
            {
                dli.dwLastError = GetLastError();
                if (PFN_FAILURE)
                    dli.hmodCur = (void*) PFN_FAILURE(3, &dli);

                if (dli.hmodCur == 0)
                {
                    ULONG_PTR args[1];
                    args[0] = (ULONG_PTR)&dli;
                    RaiseException(0xC06D007E, 0, 1, args);
                    return dli.pfnCur; /* handled */
                }
            }
        }
        *phMod = dli.hmodCur;
    }

    dli.dwLastError = 0L;

    if (PFN_NOTIFY != 0)
        dli.pfnCur = (int*) PFN_NOTIFY(2, &dli);
    if (dli.pfnCur == 0)
    {
        /* ordinal */
        dli.pfnCur = GetProcAddress(dli.hmodCur, dli.dlp.u1.szProcName);
        if (dli.pfnCur == 0)
        {
            dli.dwLastError = GetLastError();
            if (PFN_FAILURE != 0)
               dli.pfnCur = PFN_FAILURE(4, &dli);

            if (dli.pfnCur == 0)
            {
                ULONG_PTR args[1];
                args[0] = (ULONG_PTR)&dli;
                RaiseException(0xC06D007F, 0, 1, args);
            }
         }
    }

    pIAT[index].u1.Function = (ULONG_PTR) dli.pfnCur;
    dli.dwLastError = 0L;

    if (PFN_NOTIFY != 0)
        PFN_NOTIFY(5, &dli);

    return dli.pfnCur;
}