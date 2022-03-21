#ifndef HYDRA_STATES_H__
#define HYDRA_STATES_H__

#define HYDRA_STATE_IDLE            0
#define HYDRA_STATE_CONNECTING      1
#define HYDRA_STATE_CONNECTED       2
#define HYDRA_STATE_DISCONNECTED    3
#define HYDRA_STATE_RECOVERING      4
#define HYDRA_STATE_FINISHED        5
/* Following states are informational only */
#define HYDRA_STATE_INITIALIZED     6
#define HYDRA_STATE_FINALIZED       7

static inline const char *hydra_client_state2str(int code)
{
    switch (code) {
        case HYDRA_STATE_IDLE:           return "IDLE";
        case HYDRA_STATE_CONNECTING:     return "CONNECTING";
        case HYDRA_STATE_CONNECTED:      return "CONNECTED";
        case HYDRA_STATE_DISCONNECTED:   return "DISCONNECTED";
        case HYDRA_STATE_RECOVERING:     return "RECOVERING";
        case HYDRA_STATE_FINISHED:       return "FINISHED";
        case HYDRA_STATE_INITIALIZED:    return "INITIALIZED";
        case HYDRA_STATE_FINALIZED:      return "FINALIZED";
        default:                         break;
    }
    return "UNEXPECTED_HYDRA_CLIENT_STATE";
}


#endif /* HYDRA_STATES_H__ */

