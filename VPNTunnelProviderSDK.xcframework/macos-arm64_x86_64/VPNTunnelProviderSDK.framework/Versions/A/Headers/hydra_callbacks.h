#ifndef HYDRA_CALLBACKS_H__
#define HYDRA_CALLBACKS_H__

#include <stdint.h>
#include "hydra_linkage.h"
#include "af_inet_addr.h"

/* Compatible with libevent's evutil_socket_t */
#if defined(WIN32) || defined(_WIN32) || defined(_WINDOWS)
    #define hydra_sock_t intptr_t
#else
    #define hydra_sock_t int
# ifndef INVALID_SOCKET
    #define INVALID_SOCKET  (int)-1
# endif
#endif

typedef enum {
    HYDRA_DIRECT_SOCKET,      /* for sending data outside of the tunnel    */
    HYDRA_TUNNEL_SOCKET,      /* for sending data through the tunnel       */
    HYDRA_IPSEC_SOCKET        /* for sending data through the IPSEC tunnel */
} hydra_sock_type_t;

typedef hydra_sock_t
(*hydra_create_socket_cb_t) (hydra_sock_type_t sktype,
                             int domain, int type, int protocol,
                             void *ctx);
 
typedef void (*hydra_release_socket_cb_t) (hydra_sock_t s, void *ctx);

/* client provides the callbacks below to get notified by hydra */
struct hydra_callbacks {
    void (*state_cb)(void *arg, int state);
    void *state_cb_arg;
    void (*error_cb)(void *arg, int code);
    void *error_cb_arg;
    void (*bytecount_cb)(void *arg, uint64_t bytes_in, uint64_t bytes_out);
    void *bytecount_cb_arg;
    void (*notify_cb)(void *arg, int state);
    void *notify_cb_arg;

    /* Register a platform specific create-socket method. */
    hydra_create_socket_cb_t create_socket;
    /* Register a platform specific release-socket method.
     *
     * Hydra calls hydra_release_socket_cb_t for sockets created with
     * hydra_create_socket_cb_t when they are no longer required. However,
     * this callback must NOT close a socket. */
    hydra_release_socket_cb_t release_socket;

    /* Client-supplied value to be passed to hydra-socket callbacks. */
    void *socket_ctx;
};



/* callback to allow platform add/remove routing rules to
 * bypass hydra basing on destination address.
 *
 * @param addr destination address bypassing hydra.
 * @param family socket inet family: AF_INET or AF_INET6
 * @param ctx user context to be sent as parameter to callbacks
 * @return zero or positive in case of success. Otherwirse it's a failure.
 */
typedef int (*hydra_bypass_rule_per_ip_cb_t)(af_inet_addr_t *addr, uint16_t family, void *ctx);

typedef enum hydra_bypass_rule_per_ip_request {
   HYDRA_BYPASS_RULE_INVALID =          0x00, /**< invalid request */
   HYDRA_BYPASS_RULE_LOCAL_CONN =       0x01, /**< requesting bypass rules for viper conns */
   HYDRA_BYPASS_RULE_LOCAL_RESOLUTION = 0x02, /**< requesting bypass rules for viper dns resolution */
   HYDRA_BYPASS_RULE_REMOTE_CONN =      0x04, /**< requesting bypass rules for remote conns */
   HYDRA_BYPASS_RULE_SD_RESOLUTION =    0x08  /**< requesting bypass rules for sd dns resolution */
} hydra_bypass_rule_per_ip_request_t;

typedef struct hydra_bypass_rule_per_ip {
    hydra_bypass_rule_per_ip_cb_t insert_cb; /**< triggered whenever rule should be inserted */
    hydra_bypass_rule_per_ip_cb_t delete_cb; /**< triggered whenever rule should be deleted */
    uint16_t request_flags;                  /**< OR of afvpn_bypass_rule_per_ip_request_t values */
    void *ctx; /**< user context to be sent to callbacks when they are triggered */ 
} hydra_bypass_rule_per_ip_t;

typedef enum hydra_callback_id {
    HYDRA_CB_ID_DOMAIN_BLOCKED = 0,
    HYDRA_CB_ID_UNSAFE_RESOURCE,
    HYDRA_CB_ID_SAFE_RESOURCE,
    HYDRA_CB_ID_CATEG_TIMEOUT,
    HYDRA_CB_ID_COUNT
} hydra_callback_id_t;

typedef struct hydra_domain_blocked_arg {
    char *fqdn;
    int type;
} hydra_domain_blocked_arg_t;

typedef enum hydra_resource_type {
    HYDRA_RESOURCE_NONE,
    HYDRA_RESOURCE_URL,
    HYDRA_RESOURCE_IP,
    HYDRA_RESOURCE_DOMAIN
} hydra_resource_type_t;

typedef enum hydra_resource_action {
    HYD_RESOURCE_ACT_PROXY,
    HYD_RESOURCE_ACT_VPN,
    HYD_RESOURCE_ACT_BYPASS,
    HYD_RESOURCE_ACT_BLOCK,
    HYD_RESOURCE_ACT_VPNX
} hydra_resource_action_t;

typedef struct hydra_resource_arg {
    char *resource;
    int proto, port;
    hydra_resource_type_t type;
    char *category_label;
    int category_id;
    char **sources; /**< names of sources used for categorization (array of pointer to names) */
    int n_sources; /**< size of array of sources */
    char **custom_labels; /**< custom specific category labels (not always set) */
    int n_custom_labels; /**< size of array of custom labels */
    hydra_resource_action_t action;
} hydra_resource_arg_t;


typedef void (*hydra_callback_t)(void *);


/**
* Platform specific callback to retrieve path to directory where Hydra can
* create files needed for persistent storage purposes.
*
* If path is NULL or *path_size is too small to keep entire path, *path_size
* contains size of array required to store directory path.
*
* @param
*      path - char array where client will store directory path or NULL (input
*             order to get size required)
*      path_size - pointer to (unsigned) size of array provided (input).
* @returns
*      0  on success (path was filled)
*      !0 on failure (path was not filled, including the case when *path_size
*         is too small to keep entire path)
*/
typedef int (*hydra_persistent_storage_req_cb_t) (char *path,
                                                  unsigned *path_size);

/**
 * Platform specific callback that returns current network type
 * @returns
 * -1 - No network
 *  0 - Cellular
 *  1 - WiFi
 *  2 - Ethernet
 */
typedef int (*hydra_network_type_req_cb_t)(void);


/**
 * @brief  Hydra calls this function to notify client app after a (listening)
 *         port was chosen for a local service (listening pool).
 *         This callback is used at least on iOS (when hydra working in
 *         proxy mode).
 *
 * @param  poolid - local pool id provided in the hydra json configuration
 * @param  port   - port number which was chosen by OS for this local pool
 */
typedef void (*hydra_local_port_chosen_cb_t)(uint8_t poolid, uint16_t port);

#endif /* HYDRA_CALLBACKS_H__ */

