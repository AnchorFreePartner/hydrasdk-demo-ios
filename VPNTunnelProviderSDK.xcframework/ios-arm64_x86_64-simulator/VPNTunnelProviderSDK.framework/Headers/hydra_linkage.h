#ifndef HYDRA_LINKAGE_H__
#define HYDRA_LINKAGE_H__

/* TODO: hide if KL API enabled */
#ifdef _MSC_VER
#    if __HYDRA__
#        if HYDRA_LINK_STATIC_LIB
#            define HYDRA_LINKAGE extern
#        elif HYDRA_LINK_DYNAMIC_LIB
#            define HYDRA_LINKAGE __declspec(dllexport)
#        else
#            define HYDRA_LINKAGE
#        endif

#    else
#        if HYDRA_LINK_STATIC_LIB
#            define HYDRA_LINKAGE extern
#        elif HYDRA_LINK_DYNAMIC_LIB
#            define HYDRA_LINKAGE __declspec(dllimport)
#        else
#            define HYDRA_LINKAGE
#        endif
#    endif

#    define HYDRA_API(type) HYDRA_LINKAGE type __stdcall
#else
#    define HYDRA_API(type) extern type
#endif

#if defined(_MSC_VER)
#    define HYDRA_VISIBLE __declspec(dllexport)

#elif defined(__GNUC__)
#    define HYDRA_VISIBLE __attribute__((visibility("default")))
#endif

#define HYDRA_CONSTANT(type) HYDRA_VISIBLE volatile type

#endif /* HYDRA_LINKAGE_H__ */
