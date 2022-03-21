#ifndef HYDRA_NETWORK_TYPES_H_
#define HYDRA_NETWORK_TYPES_H_

enum NetworkType {
    NET_TYPE_NONE = -1,
    NET_TYPE_CELL = 0,
    NET_TYPE_WIFI = 1,
    NET_TYPE_ETH  = 2,
    NUM_NETWORK_TYPES = 3
};

#endif
