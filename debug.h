#define DEBUG
#define PFX "example_mod: "

#ifdef DEBUG
    #define DEBUG_LOG(format, ...)   printk(PFX "[%s:%d]: " format, __func__, __LINE__, ##__VA_ARGS__)
#else
    #define DEBUG_LOG(...) 
#endif

#define CHUANHENG
#if defined(DEBUG) && defined(CHUANHENG)
    #define CH_DEBUG(format, ...)   DEBUG_LOG(PFX format, ##__VA_ARGS__)
#else
    #define CH_DEBUG(...) 
#endif

#define print_value(val, format) DEBUG_LOG(#val": "#format, val)
#define PRINT_MACRO(macro) DEBUG_LOG(#macro": %d", macro)