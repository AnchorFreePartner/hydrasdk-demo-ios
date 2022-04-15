#ifndef HYDRA_FIRESHIELD_H__
#define HYDRA_FIRESHIELD_H__

#include "hydra_linkage.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint64_t lists_matches; /**< Whitelist/blacklist matches. */
    uint64_t custom_lists_matches; /**< custom whitelist/blacklist matches. */
    uint64_t exception_matches;
    uint64_t cache_matches;

    uint64_t cloud_requests;
    uint64_t cloud_request_timeouts;
    uint64_t cloud_request_errors;

    uint64_t cloud_responses;
    uint64_t cloud_response_errors;

    uint64_t whitelist_requests;
    uint64_t whitelist_request_timeouts;
    uint64_t whitelist_request_errors;

    uint64_t whitelist_responses;
    uint64_t whitelist_response_errors;
    uint64_t whitelist_response_ok;
    uint64_t whitelist_response_trylater;
    uint64_t whitelist_response_notmodified;

} hydra_fireshield_stats_t;

HYDRA_API(void) hydra_fireshield_stats(hydra_fireshield_stats_t *s);

#ifdef __cplusplus
}
#endif

#endif /* HYDRA_FIRESHIELD_H__ */
