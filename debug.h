#define DEBUG
#define PFX "example_mod: "

#ifdef DEBUG
    #define DEBUG_LOG(x)   printk(PFX x)
#else
    #define DEBUG_LOG(x) 
#endif

#define CHUANHENG
#if defined(DEBUG) && defined(CHUANHENG)
    #define CH_DEBUG(x)   DEBUG_LOG(PFX x)
#else
    #define DEBUG_LOG(x) 
#endif
