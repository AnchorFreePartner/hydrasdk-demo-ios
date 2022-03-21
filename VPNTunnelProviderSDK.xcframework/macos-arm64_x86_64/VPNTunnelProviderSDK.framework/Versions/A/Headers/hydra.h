#ifndef HYDRA_H__
#define HYDRA_H__

/****************************************************************************
 * hydra.h - this file is included by client app and hydra library to
 *           share declaration of API exported by Hydra
 ***************************************************************************/

#ifdef IS_SERVER
#error Please, include this file on client side only
#endif


#ifdef __cplusplus
extern "C" {
#endif


/****************************************************************************
 * Declaration Of API Provided By Hydra - To Be Used/Called By Client App
 ***************************************************************************/

#include <stdint.h>
#include "hydra_linkage.h"
#include "hydra_loglevels.h"
#include "hydra_states.h"
#include "hydra_errors.h"
#include "hydra_callbacks.h"
#include "hydra_ptm.h"
#include "hydra_cmd_public.h"
#include "hydra_fireshield.h"


#define HYDRA_DEFAULT_ROUTE_ID        0
#define HYDRA_DEFAULT_UDP_ROUTE_ID    1


HYDRA_API(int)   hydra_init_with_cert(const char *cfgstr, const struct hydra_callbacks *hc,
                                     const char *pem_cert, unsigned len);
HYDRA_API(int)   hydra_init(const char *cfgstr, const struct hydra_callbacks *hc);
HYDRA_API(void)  hydra_fini(void);

HYDRA_API(int)   hydra_config(const char *config_string);

HYDRA_API(void)  hydra_main_loop(void);

HYDRA_API(void)  hydra_main_loop_run_header(void);
HYDRA_API(int)   hydra_main_loop_run_iteration(void);
HYDRA_API(void)  hydra_main_loop_run_footer(void);

HYDRA_API(int)   hydra_stop(void);
HYDRA_API(void)  hydra_restart(void);

HYDRA_API(int)   hydra_running(void);

HYDRA_API(int)   hydra_cmd_request(int cmd_code, int cmd_arg, const void *data, size_t data_len, const void *user_cmd_ctx);

HYDRA_API(char*) hydra_get_status(char *buf, size_t buflen);
HYDRA_API(void)  hydra_get_global_session_id(uint8_t global_session_id[16]);
HYDRA_API(int)   hydra_info(void);
HYDRA_API(char*) hydra_info_cold(void);
HYDRA_API(int)   hydra_err_info(void);
HYDRA_API(void)  hydra_version_info(char **build_target, char **version);
HYDRA_API(void)  hydra_free(void *ptr);

HYDRA_API(int)   hydra_sticky_conns_set(uint32_t is_on);
HYDRA_API(void)  hydra_client_disconnect_all_rpools(uint8_t dcn_reason);

typedef struct hydra_package_info {
    char * package_name;
    unsigned long uid;
    struct hydra_package_info *next;
} hydra_package_info_t;

HYDRA_API(void)  hydra_update_package_info(hydra_package_info_t *package_list);

/*
 * Summarize statistics from all connector pools (SIDE_UP)
 */
typedef struct hydra_stats_bytecount {
    uint64_t rcvd;    /* bytes received */
    uint64_t sent;    /* bytes sent */
} hydra_stats_bytecount_t;

enum hydra_stats_type {
    HYDRA_STATS_BYTECOUNT = 0
};

/**
 * Returns one of statistics structures depending on stats_type
 *
 * Response will be issued using a callback set in hydra_cmd_setcb(ext_read_cb)
 * with correct user_ctx for this particular request
 */
HYDRA_API(int) hydra_stats_request(enum hydra_stats_type stats_type, void *user_ctx);

/**
 * Returns total number of scanned connections for the last
 * window time length every window precison, both configurable
 * in viper categorization section.
 *
 * It should be functional only when fireshield is in place.
 *
 * It's thread-safe function.
 */
HYDRA_API(int) hydra_total_scanned_conns(void);

/**
 * Returns total number of scanned connections
 * for current hydra session.
 *
 * It's thread-safe function.
 */
HYDRA_API(int) hydra_current_scanned_conns(void);

/**
 * Allows to read scanned connections counter from persistence storage,
 * even before calling hydra_init.
 *
 * It should be called only before starting hydra or when hydra is not
 * running. 
 *
 * @param filename persistence storage file storing wnd counter state
 * @return total scanned connections stored in the file or -1 upon
 *         error 
 */
HYDRA_API(int) hydra_total_scanned_conns_from_file(const char *filename);

/**
 * Reset current state of scanned connections. 
 *
 * It's thread-safe function.
 */
HYDRA_API(void) hydra_total_scanned_conns_reset(void);


/**
 * Requests insertion/removal of block of resources in hydra custom list.
 *
 * This list will be used to categorize (safe/unsafe) respective resource and
 * it takes priority over any other rule present in static whitelists/blacklists.
 * 
 * Hydra keeps these resources in volatile memory therefore it needs to be managed
 * by clients and provided to hydra on every hydra initialization.
 *
 * This is an asynchronouslly processed request. Meaning that it will return
 * immediatelly and do the actual processing later on in hydra thread.
 *
 * Client application should dynamically allocate request object by calling 
 * function @hydra_resource_request_new and send this pointer as a parameter
 * to this function (hydra will NOT make any deep copy of its content and will
 * send back this address to client for deallocation as soon as operation finishes).
 * Request object will be deallocated latter on by hydra.
 *
 * This function is a wrapper around hydra_cmd interface and will call back
 * client (through function registered with hydra_cmd_setcb) with following parameters:
 *
 * - cmd_code = AFVPN_RES_CUSTOM_CATEG_RULES
 * - data = pointer to original request object 
 * - data_len = size of pointer
 * - user_cmd_ctx = the one originally passed by client when calling this function
 *
 *
 * Client might verify request results by inspecting hydra_resource_request_result
 * object. It can be obtained by calling hydra_resource_request_result_get function.
 *
 * It's a tread-safe function.
 *
 * @param req pointer to request object containing list of resources and
 *            respective operation and categorization.
 * @param user_cmd_ctx user context to be sent back to client as soon as operation
 *                     is finished.
 * @return 0, if operation was successfully scheduled to be executed in hydra thread.
 *         1,  otherwise. 
 */
struct hydra_resource_request;
HYDRA_API(int) hydra_custom_categ_rules_apply(struct hydra_resource_request *req, const void *user_cmd_ctx);

typedef struct hydra_resource_request_result {
    int n_failures; /**< number of unsuccessfull requests */
    int *failures; /**< array having indexes of unsuccessfull requests (NULL if n_failures is zero) */
} hydra_resource_request_result_t;

typedef enum hydra_resource_request_op {
    HYD_RESOURCE_REQ_ADD,
    HYD_RESOURCE_REQ_REMOVE
} hydra_resource_request_op_t;

typedef struct hydra_resource_request hydra_resource_request_t;

/**
 * Allocate request object.
 *
 * @param n_resources # of resources inside this request
 * @param type type of resource (@see hydra_resource_type_t)
 * @param op request operation
 * @param category_label category label as seen in json category section
 * @return request object or NULL if error.
 */
HYDRA_API(hydra_resource_request_t *)
hydra_resource_request_new(size_t n_resources, hydra_resource_type_t type, hydra_resource_request_op_t op, const char *category_label);

/**
 * Deallocate request object
 *
 * Client application might call this function if it needs to deallocate
 * request object before sending it to hydra.
 * Hydra itself will call automatically this function after client
 * processes afvpn_cmd callback.
 */ 
HYDRA_API(void)
hydra_resource_request_free(hydra_resource_request_t *req);

/**
 * Set i-th resource in the request object.
 *
 * @param req request object
 * @param index resource index
 * @param resource resource to be set (should be NULL-terminated string)
 * @return 0 upon success. -1 otherwise.
 */
HYDRA_API(int)
hydra_resource_request_set(hydra_resource_request_t *req, size_t index, const char *resource);

/**
 * Get i-th resource in the request object.
 *
 * Returned object is read-only object.
 */
HYDRA_API(const char *)
hydra_resource_request_get(const hydra_resource_request_t *req, size_t index);

/**
 * Return number of requested resources.
 */
HYDRA_API(size_t)
hydra_resource_request_count(const hydra_resource_request_t *req);

/**
 * Return requested resource type.
 */
HYDRA_API(hydra_resource_type_t)
hydra_resource_request_type(const hydra_resource_request_t *req);

/**
 * Return requested operation.
 */
HYDRA_API(hydra_resource_request_op_t)
hydra_resource_request_op(const hydra_resource_request_t *req);

/**
 * Return requested category label.
 */
HYDRA_API(const char*)
hydra_resource_request_categ(const hydra_resource_request_t *req);

/**
 * Return request object send as a parameter to afvpn_cmd_reply callback
 *
 * Clients should use this function to recover request object if
 * they want to handle reply callback for custom categorization rules.
 *
 * @param data pointer received as argument for afvpm_cmd_reply callback.
 * @return resource request object.
 */
HYDRA_API(hydra_resource_request_t *)
hydra_resource_request_pointer(const void *data);

/**
 * Return request result
 */
HYDRA_API(const hydra_resource_request_result_t *)
hydra_resource_request_result_get(const hydra_resource_request_t *req);

/****************************************************************************
 * 'setter' methods for Hydra callbacks - To be called BEFORE hydra_init()
 ***************************************************************************/

HYDRA_API(void)  hydra_set_persistent_storage_req_cb(
                                       hydra_persistent_storage_req_cb_t cb);

HYDRA_API(void)  hydra_set_local_port_chosen_cb(hydra_local_port_chosen_cb_t cb);

/****************************************************************************
 * 'setter' methods for Hydra callbacks - To be called AFTER hydra_init()
 ***************************************************************************/

HYDRA_API(int)   hydra_add_client_callback(hydra_callback_id_t id,
                                         hydra_callback_t cb);

/**
 * Set insert and delete callbacks.
 *
 * @see hydra_bypass_rule_per_ip_t in hydra_callbcks.h
 *
 * If cbs argument is NULL, delete callback is called for each active ip address
 * previously added and callbacks are deregistered.
 */
HYDRA_API(void)  hydra_bypass_rule_per_ip_set(hydra_bypass_rule_per_ip_t *cbs);

/**
 * Fill cbs with active ip rule callbacks.
 */ 
HYDRA_API(void)  hydra_bypass_rule_per_ip_get(hydra_bypass_rule_per_ip_t *cbs);

HYDRA_API(void)  hydra_set_network_type_req_cb(hydra_network_type_req_cb_t cb);

HYDRA_API(int)   hydra_cmd_setcb(afvpn_cmd_ext_cb_t ext_read_cb);

HYDRA_API(int)   hydra_log_method_set(int (*log_fn)(int level, const char *str, void *userctx), void *userctx);

/***************************************************************************/
#if defined(__APPLE__) || defined(__MACH__)
/***************************************************************************/
#include <stdbool.h>
typedef bool (*hydra_inject_pkt_cb_t)(void *pkt, size_t sz, int pkt_type);
HYDRA_API(void)  hydra_set_inject_pkt_cb(hydra_inject_pkt_cb_t cb);
HYDRA_API(void)  nevpn_deliver_data_to_hydra(char *packet, uint16_t len);

/* FIXME: obsolete, please see hydra_create_socket_cb_t in hydra_callbacks.h */
HYDRA_API(void) hydra_set_direct_interface(const char *iface);
HYDRA_API(void) hydra_set_tunnel_interface(const char *iface);
HYDRA_API(void) hydra_set_ipsec_interface(const char *iface);

/***************************************************************************/
#elif defined(WIN32) || defined(_WIN32) || defined(_WINDOWS)
/***************************************************************************/
HYDRA_API(void)  hydra_set_std_streams(void *in, void *out, void *err);

/* FIXME: obsolete, please see hydra_create_socket_cb_t in hydra_callbacks.h */
HYDRA_API(void) hydra_set_tun_interface_ip(const char *ip);

/***************************************************************************/
#endif
/***************************************************************************/

#ifdef __cplusplus
}
#endif



#endif /* #ifndef HYDRA_H__ */
