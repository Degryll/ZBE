// TODO _FORTIFY_SOURCE could be higher. Its set to 2 to avoid incompativility with some systems.
#ifdef _FORTIFY_SOURCE
#if _FORTIFY_SOURCE < 2
#undef _FORTIFY_SOURCE
#define _FORTIFY_SOURCE 2
#endif
#else
#define _FORTIFY_SOURCE 2
#endif
