#ifndef HYDRA_SD_SRC_ROUTING_H__
#define HYDRA_SD_SRC_ROUTING_H__

#ifdef IS_SERVER
#error Please, include this file on client side only
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "hydra_linkage.h"

HYDRA_API(int)      hydra_sd_add_src_rule(const char *src_ip, const char *route_name);
HYDRA_API(int)      hydra_sd_remove_src_rule(const char *src_ip);

#ifdef __cplusplus
}
#endif

#endif /* HYDRA_SD_SRC_ROUTING_H__ */
