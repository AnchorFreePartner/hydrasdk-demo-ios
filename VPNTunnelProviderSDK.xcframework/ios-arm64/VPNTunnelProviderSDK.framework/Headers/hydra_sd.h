#ifndef HYDRA_SD_H__
#define HYDRA_SD_H__

#ifdef IS_SERVER
#error Please, include this file on client side only
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "hydra_linkage.h"

#define MAX_IP_STRING   47

enum HYDRA_SD_EVENT {
    /* General SD-related events: sd_general_event_cb() */
    HYDRA_SD_CHANGED                    = 1,
    HYDRA_SD_ROUTE_CONNECTED            = 2,
    HYDRA_SD_ROUTE_FAILED               = 3,
    HYDRA_SD_RECONNECT_REQUESTED        = 4,
    HYDRA_SD_ROUTE_FALLBACK             = 5,
    HYDRA_SD_ROUTE_DISCONNECTED         = 6,
    HYDRA_SD_ROUTE_NOTIFICATION         = 7,

    /* Connection information events: sd_conn_info_event_cb() */
    HYDRA_SD_CONN_INFO                  = 10,
    HYDRA_SD_FAILED_CONN_INFO           = 11,

    /* Bandwidth-related events: sd_bandwidth_event_cb() */
    HYDRA_SD_BANDWIDTH                  = 30
};

enum HYDRA_SD_CHANGE_FLAGS {
    SD_CHANGED_THROUGH_TUNNEL           = 1,
    SD_CHANGED_DIRECT                   = 2,
    SD_CHANGED_SERVER_PUSH              = 3
};

enum HYDRA_SD_ROUTE_RECONNECT_FLAGS {
    SD_RECONNECT_BY_SERVER              = 11,
    SD_RECONNECT_CONNECTIVITY           = 12,
    SD_RECONNECT_ROUTE_FAILED           = 13
};

enum HYDRA_SD_CONN_IP_STATE {
    SD_CONN_IP_SUCCESSFUL               = 0,
    SD_CONN_IP_SOCKET_ERROR             = 1,        
    SD_CONN_IP_UNEXPECTED_CLOSE         = 2,
    SD_CONN_IP_TIMEOUT                  = 3,
    
    SD_CONN_IP_ERROR_SERVER_AUTH        = 4,    /* error_detail may contain HYDRA_ERROR_TIME_SKEW */
    SD_CONN_IP_DISCONNECTED             = 5,     /* error_detail contains HYDRA_DCN_* code */
    SD_CONN_IP_WRONG_SRV                = 6,
    SD_CONN_IP_SESSION_END              = 7
};

enum HYDRA_SD_DOMAIN_ERR {
    SD_DOMAIN_SUCCESS                   = 0,
    SD_DOMAIN_TIMEOUT                   = 1,
    SD_DOMAIN_ADDR_FAMILY               = 2,
    SD_DOMAIN_MEMORY                    = 3,
    SD_DOMAIN_NO_DATA                   = 4,
    SD_DOMAIN_CANCELLED                 = 5,
    SD_DOMAIN_FAIL                      = 20   /* All other failures */
};

/* all errors / details start from positive integer,
   because 0 means "no error"
*/
enum HYDRA_SD_ROUTE_ERROR_DETAIL {
    HYDRA_SD_INTERNAL_ERROR             = 201,
    HYDRA_SD_RECOVERY_TIMEOUT           = 202,
    HYDRA_SD_ROUTE_SEARCH_EXHAUSTED     = 203,
    HYDRA_SD_NO_NETWORK                 = 204,
    HYDRA_SD_UNABLE_TO_SEND             = 205,
    HYDRA_SD_BLOCKED                    = 206
};

/* General events */
typedef struct hydra_sd_general_event_info {
    char *route_name;
    unsigned flags;
    
    char *      fallback_route_name;  /* HYDRA_SD_ROUTE_FALLBACK */
    int         reason;               /* HYDRA_SD_ROUTE_FAILED, HYDRA_SD_ROUTE_DISCONNECTED */  
    const char *reason_details;       /* HYDRA_SD_ROUTE_FAILED, HYDRA_SD_ROUTE_DISCONNECTED */
} hydra_general_event_info_t;

/* Connection information events */
typedef struct hydra_conn_ip {
    char ip[MAX_IP_STRING];
    enum HYDRA_SD_CONN_IP_STATE vpn_state;
    int error_detail;

    struct hydra_conn_ip *next;
} hydra_conn_ip_t;

typedef struct hydra_conn_info {
    char *domain;
    enum HYDRA_SD_DOMAIN_ERR err;

    struct hydra_conn_ip *ips;

    struct hydra_conn_info *next;
} hydra_conn_info_t;

/* Bandwidth events */
typedef struct bandwidth_value {
    unsigned upstream;
    unsigned downstream;
} bandwidth_value_t;

typedef struct hydra_bandwidth_info {
    char *route_name;
    unsigned data_interval;             /* in ms */
    unsigned n_points;
    bandwidth_value_t *points;

    struct hydra_bandwidth_info *next;
} hydra_bandwidth_info_t;


/**
 * Callback to retrieve application key for SD config decryption
 *
 * @returns
 *     0  on success (key was filled)
 *     !0 on failure (key was not filled, including the case when *key_size
 *        is too small to keep entire path)
 */
typedef int (*sd_app_key_req_cb_t)(char *key,
                                   unsigned *key_size);

typedef
struct hydra_sd_callbacks {
    /* Existing callbacks that are currently specified with help from special functions. All of them are required */
    hydra_persistent_storage_req_cb_t ps_cb;
    hydra_network_type_req_cb_t       net_type_cb;
    
    /* Register a platform specific create-socket method. */
    hydra_create_socket_cb_t          create_socket_cb;
    /* Register a platform specific release-socket method.
     *
     * Hydra calls hydra_release_socket_cb_t for sockets created with
     * hydra_create_socket_cb_t when they are no longer required. However,
     * this callback must NOT close a socket. */
    hydra_release_socket_cb_t         release_socket_cb;
    /* Client-supplied value to be passed to hydra-socket callbacks. */
    void *                            socket_ctx;

    /* SD callbacks */
    sd_app_key_req_cb_t               sd_app_key_cb; /* Optional */

    void (*sd_general_event_cb)(enum HYDRA_SD_EVENT e, hydra_general_event_info_t *info, void *arg);    /* Required */
    void *sd_general_event_arg;

    void (*sd_conn_info_event_cb)(enum HYDRA_SD_EVENT e, const char *route_name, hydra_conn_info_t *ci, void *arg); /* Can be NULL */
    void *sd_conn_info_event_arg;

    void (*sd_bandwidth_event_cb)(enum HYDRA_SD_EVENT e, hydra_bandwidth_info_t *info, void *arg); /* Can be NULL */
    void *sd_bandwidth_event_arg;
} hydra_sd_callbacks_t;

HYDRA_API(int)     hydra_sd_init(hydra_sd_callbacks_t *cbs);
HYDRA_API(void)    hydra_sd_cleanup();

HYDRA_API(int)     hydra_sd_use_custom_config(const char *cfg);

enum HYDRA_SD_MODE {
    MODE_NORMAL = 1,
    MODE_PROXY = 2
};

HYDRA_API(int)     hydra_sd_start(enum HYDRA_SD_MODE mode, const char *json_params);
HYDRA_API(int)     hydra_sd_stop();

enum HYDRA_SD_TYPE {
    HYDRA_SD_CURRENT = 1,
    HYDRA_SD_NEXT = 2
};

HYDRA_API(char*)    hydra_sd_get_exports(enum HYDRA_SD_TYPE type, hydra_persistent_storage_req_cb_t ps_cb, sd_app_key_req_cb_t app_key_req_cb);
HYDRA_API(char*)    hydra_sd_get_conn_log(void);
HYDRA_API(void)     hydra_sd_free_conn_log(char*);

HYDRA_API(char*)    hydra_sd_get_virtual_locations(hydra_persistent_storage_req_cb_t ps_cb);

#ifdef __cplusplus
}
#endif

#endif /* HYDRA_SD_H__ */
