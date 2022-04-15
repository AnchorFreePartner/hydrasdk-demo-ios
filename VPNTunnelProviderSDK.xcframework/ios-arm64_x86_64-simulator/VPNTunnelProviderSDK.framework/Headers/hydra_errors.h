#ifndef HYDRA_ERRORS_H__
#define HYDRA_ERRORS_H__

#include <stdint.h>
#include <string.h>


#define HYDRA_ERROR_CONFIG          180
#define HYDRA_ERROR_BROKEN          181
#define HYDRA_ERROR_CONNECT         182
#define HYDRA_ERROR_INTERNAL        183
#define HYDRA_ERROR_SERVER_AUTH     184
#define HYDRA_ERROR_CANT_SEND       185
#define HYDRA_ERROR_TIME_SKEW       186

#define HYDRA_DCN_MIN               190
#define HYDRA_DCN_SRV_SWITCH        190
#define HYDRA_DCN_BLOCKED_BW        191
#define HYDRA_DCN_BLOCKED_ABUSE     192
#define HYDRA_DCN_BLOCKED_MALWARE   193
#define HYDRA_DCN_BLOCKED_MISC      194
#define HYDRA_DCN_REQ_BY_CLIAPP     195
#define HYDRA_DCN_BLOCKED_AUTH      196
#define HYDRA_DCN_SRV_FULL          197
#define HYDRA_DCN_MAX               197

/* Notify codes */
#define HYDRA_NOTIFY_AUTH_OK        100

#define dcn_reason_invalid(r)   ((r) < HYDRA_DCN_MIN || (r) > HYDRA_DCN_MAX)
#define dcn_reason_is_valid(r)  (!dcn_reason_invalid((r)))


static inline int str2dcnreason(const char *s, uint8_t *result)
{
    #define streq__(literal,str) (strncmp((literal),(str),sizeof(literal))==0)
    if (streq__("SRV_SWITCH", s)) {
        *result = HYDRA_DCN_SRV_SWITCH;
        return 0;
    }
    if (streq__("BLOCKED_BW", s)) {
        *result = HYDRA_DCN_BLOCKED_BW;
        return 0;
    }
    if (streq__("BLOCKED_ABUSE", s)) {
        *result = HYDRA_DCN_BLOCKED_ABUSE;
        return 0;
    }
    if (streq__("BLOCKED_MALWARE", s)) {
        *result = HYDRA_DCN_BLOCKED_MALWARE;
        return 0;
    }
    if (streq__("BLOCKED_MISC", s)) {
        *result = HYDRA_DCN_BLOCKED_MISC;
        return 0;
    }
    if (streq__("BLOCKED_AUTH", s)) {
        *result = HYDRA_DCN_BLOCKED_AUTH;
        return 0;
    }
    return -1;
}


static inline const char * hydra_client_errcode2str(int code)
{
    switch (code) {
        case HYDRA_ERROR_CONFIG:         return "ERROR_CONFIG";
        case HYDRA_ERROR_BROKEN:         return "ERROR_BROKEN";
        case HYDRA_ERROR_CONNECT:        return "ERROR_CONNECT";
        case HYDRA_ERROR_INTERNAL:       return "ERROR_INTERNAL";
        case HYDRA_ERROR_SERVER_AUTH:    return "ERROR_SERVER_AUTH";
        case HYDRA_ERROR_TIME_SKEW:      return "ERROR_TIME_SKEW";
        case HYDRA_ERROR_CANT_SEND:      return "ERROR_CANT_SEND";
        case HYDRA_DCN_SRV_SWITCH:       return "DCN_SRV_SWITCH";
        case HYDRA_DCN_BLOCKED_BW:       return "DCN_BLOCKED_BW";
        case HYDRA_DCN_BLOCKED_ABUSE:    return "DCN_BLOCKED_ABUSE";
        case HYDRA_DCN_BLOCKED_MALWARE:  return "DCN_BLOCKED_MALWARE";
        case HYDRA_DCN_BLOCKED_MISC:     return "DCN_BLOCKED_MISC";
        case HYDRA_DCN_BLOCKED_AUTH:     return "DCN_BLOCKED_AUTH";
        case HYDRA_DCN_REQ_BY_CLIAPP:    return "DCN_REQ_BY_CLIAPP";
        default:                         break;
    }
    return "UNKNOWN_ERR_CODE";
}


#endif /* HYDRA_ERRORS_H__ */
