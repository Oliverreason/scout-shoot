#if defined( KXNA_DLL_BUILD )
    #define _kXNA __declspec(dllexport)
#else
    #define _kXNA __declspec(dllimport)
#endif
