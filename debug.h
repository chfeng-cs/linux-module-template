#define DEBUG
#define PFX "example_mod: "

#ifdef DEBUG
    #define DEBUG_LOG(...)   printk(PFX __VA_ARGS__)
#else
    #define DEBUG_LOG(...) 
#endif

#define CHUANHENG
#if defined(DEBUG) && defined(CHUANHENG)
    #define CH_DEBUG(...)   DEBUG_LOG(PFX __VA_ARGS__)
#else
    #define CH_DEBUG(...) 
#endif
