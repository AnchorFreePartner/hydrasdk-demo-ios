#pragma once

#include <event2/util.h>
#include <event2/bufferevent.h>
#include <hydra_linkage.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t node_id_t;
typedef uint32_t session_id_t;
typedef uint8_t pool_id_t;
typedef uint8_t route_id_t;
typedef uint32_t rpc_arg_t;
typedef enum {HYDRA_POOL_TYPE_UP, HYDRA_POOL_TYPE_DOWN } pool_type_t;

struct hydra_async_listener;
typedef void (*hydra_async_connect_cb_t)(int err, struct bufferevent *bev, const char *auth_str, void *ctx);
typedef void (*hydra_async_accept_cb_t)(struct bufferevent *bev, struct hydra_async_listener*);

typedef struct hydra_async_listener {
    void *ctx;
    void *user_ctx;
    hydra_async_accept_cb_t accept_cb;

    void (*free)(struct hydra_async_listener*);
} hydra_async_listener_t;

typedef int (*hydra_async_connect_method_t)(const char *endpoint, void *ctx,
                                            hydra_async_connect_cb_t cb,
                                            void *cb_ctx);

typedef hydra_async_listener_t* (*hydra_async_listen_method_t)(const char *endpoint, void *ctx,
                                           hydra_async_accept_cb_t cb);
typedef struct hydra_flow_tuple {
    uint8_t proto;
    uint16_t sport, dport;
    // FIXME: only IPv4 support in afnat atm.
    uint32_t saddr, daddr;
} hydra_flow_tuple_t;

typedef enum hydra_flow_verdict_action {
    HYDRA_FLOW_VERDICT_ALLOW,
    HYDRA_FLOW_VERDICT_DENY,
    HYDRA_FLOW_VERDICT_POSTPONED,
    HYDRA_FLOW_VERDICT_RETRY,
} hydra_flow_verdict_action_t;

typedef struct hydra_flow_verdict {
    hydra_flow_verdict_action_t action;
    route_id_t route_id;
} hydra_flow_verdict_t;

typedef void (*hydra_async_flow_verdict_cb)(hydra_flow_tuple_t *tuple, hydra_flow_verdict_t *verdict);

typedef struct hydra_flow_match {
    uint8_t route_id;

    const char *fqdn;
    hydra_flow_tuple_t tuple;

    hydra_async_flow_verdict_cb async_flow_verdict_cb;

} hydra_flow_match_t;

typedef void (*hydra_flow_interception_method_t)(hydra_flow_match_t *flow, hydra_flow_verdict_t *verdict);

enum {
    HYDRA_REMOTE_ENDPOINT_NAME_LEN = 2048,
};

typedef struct hydra_remote_pool_config {
    uint8_t id;

    uint8_t use_udp : 1; // not supported atm
    uint8_t listening : 1;
    uint8_t reliable_delivery : 1;

    char endpoint[HYDRA_REMOTE_ENDPOINT_NAME_LEN];
    // alternative: set IP/port

    uint32_t prealloc, allocate, preconnect;
} hydra_remote_pool_config_t;

typedef struct hydra_session_desc {
    route_id_t  pool_id;
    node_id_t node_id;
    session_id_t session_id;
    pool_type_t pool_type;
} hydra_session_desc_t;

typedef int (*hydra_rpc_cb)(hydra_session_desc_t *pool,
                            uint32_t arg, const void *data, size_t len);

// TODO: make sure that user info isn't defined completely
// on the client side (e.g. session_id?). For instance, add
// TLS hash info (used in CBCT).
//
typedef struct hydra_user_info {
    route_id_t pool_id;
    node_id_t node_id;
    session_id_t session_id;
} hydra_user_info_t;


typedef int (*hydra_authorize_proxy_resource_1_method_t)(
                const hydra_user_info_t *info,
                const char *hostname,
                int port);


typedef int (*hydra_authorize_proxy_resource_2_method_t)(
                const hydra_user_info_t *info,
                const struct sockaddr*);


typedef struct hydra_extended_callbacks {
    hydra_async_connect_method_t connect_async;
    hydra_async_listen_method_t listen_async;
    hydra_authorize_proxy_resource_1_method_t authorize_host_proxy_request;
    hydra_authorize_proxy_resource_2_method_t authorize_sockaddr_proxy_request;
    hydra_flow_interception_method_t flow_interceptor;
    hydra_rpc_cb rpc_channel_1;
    void* (*getaddrinfo_async)(const char *hostname, const char *service, const struct evutil_addrinfo *hints_in, evdns_getaddrinfo_cb cb, void *arg);
    void* (*getaddrinfo_cancel)(struct evdns_getaddrinfo_request *request);
    const char* (*get_auth_token)(const char *);
    int (*prompt_password)(char *buf, int size, int rwflag, void *u);
    int (*verify_token)(const char *auth_str, const char *origin_hostname, const char *target_hostname);
    void (*report_pool_state)(const hydra_session_desc_t* desc, int state);
} hydra_extended_callbacks_t;

/**
 * @brief  Set an extended callback
 *
 * @param  callback_id The callback name
 * @param  cb The pointer to the callback function
 *
 * @returns On success, zero is returned. On error, non-zero value is returned.
 */
HYDRA_API(int) hydra_set_callbacks(const hydra_extended_callbacks_t* callbacks);

typedef enum hydra_option_id {
    HYDRA_OPTION_DISABLE_OPENSSL_INITIALIZATION
} hydra_option_id_t;

/**
 * @brief  Set an extended option
 *
 * @param  option_id The option name
 * @param  val The pointer to the option value. If len is zero, val is interpreted as an integer (int).
 * @param  len Length of the option value
 *
 * @returns On success, zero is returned. On error, non-zero value is returned.
 */
HYDRA_API(int) hydra_set_option(hydra_option_id_t option_id, uintptr_t val, size_t len);

/**
 * @brief  Events loop base getter
 *
 * @returns The hydra events loop's structs event_base*
 */
HYDRA_API(struct event_base*) hydra_event_base_get();

/**
 * @brief  DNS events loop base getter
 *
 * @returns The hydra DNS events loop's structs evdns_base*
 */
HYDRA_API(struct evdns_base*) hydra_evdns_base_get();

/**
 * @brief This function creates a new remote pool dynamically. It can
 *        be used only by code running in the hydra main event loop.
 *
 * @param id Id of the new pool.
 * @param conf Pool options to override the default ones.
 *
 * @returns 0 on success and a negative value on error.
 */

HYDRA_API(int) hydra_remote_pool_create(uint8_t id, hydra_remote_pool_config_t *conf);
HYDRA_API(int) hydra_remote_pool_close(const struct hydra_session_desc* des, int disconnect_reason);

HYDRA_API(int) hydra_rpc_call(hydra_session_desc_t *pool, uint32_t arg, const void *data, size_t len);

HYDRA_API(int) hydra_remote_pool_export_keying_material(hydra_session_desc_t *pool,
                                                        unsigned char *out, size_t olen,
                                                        const char *label, size_t llen);

HYDRA_API(int) hydra_tranceport_cert_key_use(const char *cert_pem, const char *key_pem);

#ifdef __cplusplus
}
#endif
