#ifndef HYDRA_PTM_H__
#define HYDRA_PTM_H__

#include "hydra_linkage.h"

#define PTM_VERSION  "0.7"


/****************************************************************************
 * start/stop PTM tests
 ***************************************************************************/

typedef enum {
    PTM_TEST_STARTED = 0,
    PTM_TEST_FINISHED,
    PTM_TEST_INTERRUPTED,
    PTM_TEST_ERROR
} ptm_test_status_t;


typedef void
(*ptm_test_callback_t)(void *arg, ptm_test_status_t status,
                                  const char *json_report);


/**
 * @brief Start a PTM test.
 * @param hss_ip       IP addr of a HSS server hydra-client is connected to.
 * @param json_config  JSON object describing the test.
 * @param callback     User-provided fn to follow the progress of the test.
 * @param arg          User-provided context-dependent arg to pass to @callback
 */
HYDRA_API(int)
ptm_test_start(const char *hss_ip, const char *json_config,
               ptm_test_callback_t callback, void *arg);

HYDRA_API(int)
ptm_test_start_from_file(const char *hss_ip,
                         const char *json_config_file,
                         ptm_test_callback_t callback, void *arg);

/**
 * @brief Stop the PTM test.
 * @param skip_reporting  If 1, the user-specified callback is called with
 *                        json_report=NULL, i.e. no reporting is done.
 */
HYDRA_API(void) ptm_test_stop(void);


/**
 * @brief  Let PTM know the name of a TUN interface. Currently used by Windows
 *         client only.
 */
HYDRA_API(void) ptm_set_tun_interface_ip(const char *ip);



HYDRA_API(void) ptm_set_direct_interface(const char *iface);
HYDRA_API(void) ptm_set_tunnel_interface(const char *iface);
HYDRA_API(void) ptm_set_ipsec_interface(const char *iface);

/**
 * @brief (Another hack) Use a specific destination IP for IPSEC unit tests.
 */
HYDRA_API(void) ptm_set_ipsec_hss_ip(const char *hss_ip);

#endif /* HYDRA_PTM_H__ */

