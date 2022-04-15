/**
 * @file afvpn_cmd_public.h
 * @brief Hydra afvpn command interface, part that is exported to hydra.h and end users (clients)
 *
 * @date 16 March 2018 01:52:48 PM
 *
 * 
 */
#pragma once

#ifndef HYDRA_CMD_PUBLIC_H__
#define HYDRA_CMD_PUBLIC_H__


/** Callback type for the external callbacks */
typedef void (*afvpn_cmd_ext_cb_t)(int cmd_code, int cmd_arg, const void *data, size_t data_len, const void *user_cmd_ctx);

#define AFVPN_REQ_NOOP      0
#define AFVPN_REQ_INFO      1
#define AFVPN_RES_INFO      4
#define AFVPN_REQ_RESTART   2
#define AFVPN_REQ_TERM      3
#define AFVPN_REQ_ERR_INFO  5
#define AFVPN_RES_ERR_INFO  6
#define AFVPN_REQ_CONFIG    7
#define AFVPN_RES_CONFIG    8
/** Sticky connection feature, when application connection
 * sticks to one of transport channels (HYD-859) */
#define AFVPN_REQ_STICKY_ON   9
#define AFVPN_REQ_STICKY_OFF  10
#define AFVPN_REQ_STATS     11
#define AFVPN_RES_STATS     12
#define AFVPN_REQ_CUSTOM_CATEG_RULES    13
#define AFVPN_RES_CUSTOM_CATEG_RULES    14

/** SRC IP routes modification request/response */
#define AFVPN_REQ_SRC_IP      20
#define AFVPN_RES_SRC_IP      21


/* These flags are used within AFVPN CMD interface;
 * in addition to AFVPN_REQ_SRC_IP, AFVPN_RES_SRC_IP command codes */
#define SD_SRC_IP_RULE_ADD     1
#define SD_SRC_IP_RULE_REMOVE  2

#endif /* HYDRA_CMD_PUBLIC_H__ */

