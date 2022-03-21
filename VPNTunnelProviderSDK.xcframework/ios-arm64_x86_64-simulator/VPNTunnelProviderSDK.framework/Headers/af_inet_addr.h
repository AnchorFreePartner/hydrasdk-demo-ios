#pragma once

#if defined(_WIN32)
# include <winsock2.h>
# include <ws2ipdef.h>
#else
# include <netinet/in.h>
#endif

#include <stdbool.h>
#include <stdint.h>

#define AF_INET_ADDR_STRLEN INET6_ADDRSTRLEN

#define AF_INET_ADDR_ANY    {{0}}

typedef union af_inet_addr af_inet_addr_t;

union af_inet_addr {
    uint32_t all[4];
    struct in6_addr sin6_addr;
    uint32_t ip6[4];
    struct in_addr sin_addr;
    uint32_t ip4;
};

extern const af_inet_addr_t af_inet_addr_any;

void
af_inet_addr_init(af_inet_addr_t *a);

af_inet_addr_t *
af_inet_addr_new(void);

void
af_inet_addr_free(af_inet_addr_t *a);

bool
af_inet_addr_equal(const af_inet_addr_t *a1, const af_inet_addr_t *a2);

static inline bool
af_inet_addr_is_any(const af_inet_addr_t *a)
{
    return af_inet_addr_equal(&af_inet_addr_any, a);
}

/**
 * Gets IPv6 prefix for IPv4 mapped addresses
 * on IPv6 only network - RFC7050.
 **/
bool
af_inet_addr_synthetize_ipv6(af_inet_addr_t *a);

static inline void
af_inet_addr_v4_map_v6(af_inet_addr_t *a)
{
    a->ip6[3] = a->ip4;
    a->ip6[0] = 0;
    a->ip6[1] = 0;
    a->ip6[2] = htonl(0x0000FFFF);
}

const char *
af_inet_addr_to_str(const af_inet_addr_t *a, char str[AF_INET_ADDR_STRLEN], uint16_t family);
