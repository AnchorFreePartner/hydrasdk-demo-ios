#ifndef _HYDRA_SD_COMPAT_H_
#define _HYDRA_SD_COMPAT_H_

#ifdef IS_SERVER
#error Please, include this file on client side only
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "hydra_linkage.h"

HYDRA_API(int)      hydra_sd_compat_init(const char *cfgstr,
                                const struct hydra_callbacks *hc,
                                const char *platform);
HYDRA_API(int)      hydra_sd_compat_init_with_cert(const char *cfgstr,
                                const struct hydra_callbacks *hc,
                                const char *pem_cert,
                                unsigned pem_cert_len,
                                const char *platform);
HYDRA_API(void)     hydra_sd_compat_fini(void);
HYDRA_API(int)      hydra_sd_compat_config(const char *config_string);
HYDRA_API(int)      hydra_sd_compat_stop(void);
HYDRA_API(void)     hydra_sd_compat_restart(void);

enum HYDRA_SD_COMPAT_CONN_INFO_TYPE {
    HYDRA_CONN_INFO_SUCCEEDED = 1,
    HYDRA_CONN_INFO_FAILED = 2
};
HYDRA_API(hydra_conn_info_t*)   hydra_sd_compat_get_main_conn_info(int network_type, int type);
HYDRA_API(void)                 hydra_sd_compat_free_conn_info(hydra_conn_info_t *ci);

#ifdef __cplusplus
}
#endif

#endif /* _HYDRA_SD_COMPAT_H_ */
