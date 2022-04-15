/*
 * Copyright (c) 2000-2015 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)route.h	8.3 (Berkeley) 4/19/94
 * $FreeBSD: src/sys/net/route.h,v 1.36.2.1 2000/08/16 06:14:23 jayanth Exp $
 */

#ifndef _NET_ROUTE_H_
#define	_NET_ROUTE_H_
#include <sys/appleapiopts.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>

/*
 * These numbers are used by reliable protocols for determining
 * retransmission behavior and are included in the routing structure.
 */
struct rt_metrics {
    u_int32_t       rmx_locks;      /* Kernel leaves these values alone */
    u_int32_t       rmx_mtu;        /* MTU for this path */
    u_int32_t       rmx_hopcount;   /* max hops expected */
    int32_t         rmx_expire;     /* lifetime for route, e.g. redirect */
    u_int32_t       rmx_recvpipe;   /* inbound delay-bandwidth product */
    u_int32_t       rmx_sendpipe;   /* outbound delay-bandwidth product */
    u_int32_t       rmx_ssthresh;   /* outbound gateway buffer limit */
    u_int32_t       rmx_rtt;        /* estimated round trip time */
    u_int32_t       rmx_rttvar;     /* estimated rtt variance */
    u_int32_t       rmx_pksent;     /* packets sent using this route */
    u_int32_t       rmx_state;      /* route state */
    u_int32_t       rmx_filler[3];  /* will be used for TCP's peer-MSS cache */
};

/*
 * rmx_rtt and rmx_rttvar are stored as microseconds;
 */
#define	RTM_RTTUNIT	1000000	/* units for rtt, rttvar, as units per sec */



#define	RTF_UP		0x1		/* route usable */
#define	RTF_GATEWAY	0x2		/* destination is a gateway */
#define	RTF_HOST	0x4		/* host entry (net otherwise) */
#define	RTF_REJECT	0x8		/* host or net unreachable */
#define	RTF_DYNAMIC	0x10		/* created dynamically (by redirect) */
#define	RTF_MODIFIED	0x20		/* modified dynamically (by redirect) */
#define	RTF_DONE	0x40		/* message confirmed */
#define	RTF_DELCLONE	0x80		/* delete cloned route */
#define	RTF_CLONING	0x100		/* generate new routes on use */
#define	RTF_XRESOLVE	0x200		/* external daemon resolves name */
#define	RTF_LLINFO	0x400		/* generated by link layer (e.g. ARP) */
#define	RTF_STATIC	0x800		/* manually added */
#define	RTF_BLACKHOLE	0x1000		/* just discard pkts (during updates) */
#define	RTF_NOIFREF	0x2000		/* not eligible for RTF_IFREF */
#define	RTF_PROTO2	0x4000		/* protocol specific routing flag */
#define	RTF_PROTO1	0x8000		/* protocol specific routing flag */

#define	RTF_PRCLONING	0x10000		/* protocol requires cloning */
#define	RTF_WASCLONED	0x20000		/* route generated through cloning */
#define	RTF_PROTO3	0x40000		/* protocol specific routing flag */
/* 0x80000 unused */
#define	RTF_PINNED	0x100000	/* future use */
#define	RTF_LOCAL	0x200000	/* route represents a local address */
#define	RTF_BROADCAST	0x400000	/* route represents a bcast address */
#define	RTF_MULTICAST	0x800000	/* route represents a mcast address */
#define	RTF_IFSCOPE	0x1000000	/* has valid interface scope */
#define	RTF_CONDEMNED	0x2000000	/* defunct; no longer modifiable */
#define	RTF_IFREF	0x4000000	/* route holds a ref to interface */
#define	RTF_PROXY	0x8000000	/* proxying, no interface scope */
#define	RTF_ROUTER	0x10000000	/* host is a router */
/* 0x20000000 and up unassigned */

#define	RTF_BITS \
"\020\1UP\2GATEWAY\3HOST\4REJECT\5DYNAMIC\6MODIFIED\7DONE" \
"\10DELCLONE\11CLONING\12XRESOLVE\13LLINFO\14STATIC\15BLACKHOLE" \
"\16NOIFREF\17PROTO2\20PROTO1\21PRCLONING\22WASCLONED\23PROTO3" \
"\25PINNED\26LOCAL\27BROADCAST\30MULTICAST\31IFSCOPE\32CONDEMNED" \
"\33IFREF\34PROXY\35ROUTER"

/*
 * Routing statistics.
 */
struct  rtstat {
    short   rts_badredirect;        /* bogus redirect calls */
    short   rts_dynamic;            /* routes created by redirects */
    short   rts_newgateway;         /* routes modified by redirects */
    short   rts_unreach;            /* lookups which failed */
    short   rts_wildcard;           /* lookups satisfied by a wildcard */
    short   rts_badrtgwroute;       /* route to gateway is not direct */
};

/*
 * Structures for routing messages.
 */
struct rt_msghdr {
    u_short	rtm_msglen;	/* to skip over non-understood messages */
    u_char	rtm_version;	/* future binary compatibility */
    u_char	rtm_type;	/* message type */
    u_short	rtm_index;	/* index for associated ifp */
    int	rtm_flags;	/* flags, incl. kern & message, e.g. DONE */
    int	rtm_addrs;	/* bitmask identifying sockaddrs in msg */
    pid_t	rtm_pid;	/* identify sender */
    int	rtm_seq;	/* for sender to identify action */
    int	rtm_errno;	/* why failed */
    int	rtm_use;	/* from rtentry */
    u_int32_t rtm_inits;	/* which metrics we are initializing */
    struct rt_metrics rtm_rmx; /* metrics themselves */
};

struct rt_msghdr2 {
    u_short	rtm_msglen;	/* to skip over non-understood messages */
    u_char	rtm_version;	/* future binary compatibility */
    u_char	rtm_type;	/* message type */
    u_short	rtm_index;	/* index for associated ifp */
    int	rtm_flags;	/* flags, incl. kern & message, e.g. DONE */
    int	rtm_addrs;	/* bitmask identifying sockaddrs in msg */
    int32_t	rtm_refcnt;	/* reference count */
    int	rtm_parentflags; /* flags of the parent route */
    int	rtm_reserved;	/* reserved field set to 0 */
    int	rtm_use;	/* from rtentry */
    u_int32_t rtm_inits;	/* which metrics we are initializing */
    struct rt_metrics rtm_rmx; /* metrics themselves */
};


#define	RTM_VERSION	5	/* Up the ante and ignore older versions */

/*
 * Message types.
 */
#define	RTM_ADD		0x1	/* Add Route */
#define	RTM_DELETE	0x2	/* Delete Route */
#define	RTM_CHANGE	0x3	/* Change Metrics or flags */
#define	RTM_GET		0x4	/* Report Metrics */
#define	RTM_LOSING	0x5	/* RTM_LOSING is no longer generated by xnu
and is deprecated */
#define	RTM_REDIRECT	0x6	/* Told to use different route */
#define	RTM_MISS	0x7	/* Lookup failed on this address */
#define	RTM_LOCK	0x8	/* fix specified metrics */
#define	RTM_OLDADD	0x9	/* caused by SIOCADDRT */
#define	RTM_OLDDEL	0xa	/* caused by SIOCDELRT */
#define	RTM_RESOLVE	0xb	/* req to resolve dst to LL addr */
#define	RTM_NEWADDR	0xc	/* address being added to iface */
#define	RTM_DELADDR	0xd	/* address being removed from iface */
#define	RTM_IFINFO	0xe	/* iface going up/down etc. */
#define	RTM_NEWMADDR	0xf	/* mcast group membership being added to if */
#define	RTM_DELMADDR	0x10	/* mcast group membership being deleted */
#define	RTM_IFINFO2	0x12	/* */
#define	RTM_NEWMADDR2	0x13	/* */
#define	RTM_GET2	0x14	/* */

/*
 * Bitmask values for rtm_inits and rmx_locks.
 */
#define	RTV_MTU		0x1	/* init or lock _mtu */
#define	RTV_HOPCOUNT	0x2	/* init or lock _hopcount */
#define	RTV_EXPIRE	0x4	/* init or lock _expire */
#define	RTV_RPIPE	0x8	/* init or lock _recvpipe */
#define	RTV_SPIPE	0x10	/* init or lock _sendpipe */
#define	RTV_SSTHRESH	0x20	/* init or lock _ssthresh */
#define	RTV_RTT		0x40	/* init or lock _rtt */
#define	RTV_RTTVAR	0x80	/* init or lock _rttvar */

/*
 * Bitmask values for rtm_addrs.
 */
#define	RTA_DST		0x1	/* destination sockaddr present */
#define	RTA_GATEWAY	0x2	/* gateway sockaddr present */
#define	RTA_NETMASK	0x4	/* netmask sockaddr present */
#define	RTA_GENMASK	0x8	/* cloning mask sockaddr present */
#define	RTA_IFP		0x10	/* interface name sockaddr present */
#define	RTA_IFA		0x20	/* interface addr sockaddr present */
#define	RTA_AUTHOR	0x40	/* sockaddr for author of redirect */
#define	RTA_BRD		0x80	/* for NEWADDR, broadcast or p-p dest addr */

/*
 * Index offsets for sockaddr array for alternate internal encoding.
 */
#define	RTAX_DST	0	/* destination sockaddr present */
#define	RTAX_GATEWAY	1	/* gateway sockaddr present */
#define	RTAX_NETMASK	2	/* netmask sockaddr present */
#define	RTAX_GENMASK	3	/* cloning mask sockaddr present */
#define	RTAX_IFP	4	/* interface name sockaddr present */
#define	RTAX_IFA	5	/* interface addr sockaddr present */
#define	RTAX_AUTHOR	6	/* sockaddr for author of redirect */
#define	RTAX_BRD	7	/* for NEWADDR, broadcast or p-p dest addr */
#define	RTAX_MAX	8	/* size of array to allocate */

struct rt_addrinfo {
    int	rti_addrs;
    struct	sockaddr *rti_info[RTAX_MAX];
};


#endif /* _NET_ROUTE_H_ */


/*
 * IPv6 interface statistics, as defined in RFC2465 Ipv6IfStatsEntry (p12).
 */
struct in6_ifstat {
    u_quad_t ifs6_in_receive;       /* # of total input datagram */
    u_quad_t ifs6_in_hdrerr;        /* # of datagrams with invalid hdr */
    u_quad_t ifs6_in_toobig;        /* # of datagrams exceeded MTU */
    u_quad_t ifs6_in_noroute;       /* # of datagrams with no route */
    u_quad_t ifs6_in_addrerr;       /* # of datagrams with invalid dst */
    u_quad_t ifs6_in_protounknown;  /* # of datagrams with unknown proto */
                                    /* NOTE: increment on final dst if */
    u_quad_t ifs6_in_truncated;     /* # of truncated datagrams */
    u_quad_t ifs6_in_discard;       /* # of discarded datagrams */
                                    /* NOTE: fragment timeout is not here */
    u_quad_t ifs6_in_deliver;       /* # of datagrams delivered to ULP */
                                    /* NOTE: increment on final dst if */
    u_quad_t ifs6_out_forward;      /* # of datagrams forwarded */
                                    /* NOTE: increment on outgoing if */
    u_quad_t ifs6_out_request;      /* # of outgoing datagrams from ULP */
                                    /* NOTE: does not include forwrads */
    u_quad_t ifs6_out_discard;      /* # of discarded datagrams */
    u_quad_t ifs6_out_fragok;       /* # of datagrams fragmented */
    u_quad_t ifs6_out_fragfail;     /* # of datagrams failed on fragment */
    u_quad_t ifs6_out_fragcreat;    /* # of fragment datagrams */
                                    /* NOTE: this is # after fragment */
    u_quad_t ifs6_reass_reqd;       /* # of incoming fragmented packets */
                                    /* NOTE: increment on final dst if */
    u_quad_t ifs6_reass_ok;         /* # of reassembled packets */
                                    /* NOTE: this is # after reass */
                                    /* NOTE: increment on final dst if */
    u_quad_t ifs6_atmfrag_rcvd;     /* # of atomic fragments received */
    u_quad_t ifs6_reass_fail;       /* # of reass failures */
                                    /* NOTE: may not be packet count */
                                    /* NOTE: increment on final dst if */
    u_quad_t ifs6_in_mcast;         /* # of inbound multicast datagrams */
    u_quad_t ifs6_out_mcast;        /* # of outbound multicast datagrams */

    u_quad_t ifs6_cantfoward_icmp6; /* # of ICMPv6 packets received for unreachable dest */
    u_quad_t ifs6_addr_expiry_cnt;  /* # of address expiry events (excluding privacy addresses) */
    u_quad_t ifs6_pfx_expiry_cnt;   /* # of prefix expiry events */
    u_quad_t ifs6_defrtr_expiry_cnt;        /* # of default router expiry events */
};

struct icmp6_ifstat {
    /*
     * Input statistics
     */
    /* ipv6IfIcmpInMsgs, total # of input messages */
    u_quad_t ifs6_in_msg;
    /* ipv6IfIcmpInErrors, # of input error messages */
    u_quad_t ifs6_in_error;
    /* ipv6IfIcmpInDestUnreachs, # of input dest unreach errors */
    u_quad_t ifs6_in_dstunreach;
    /* ipv6IfIcmpInAdminProhibs, # of input admin. prohibited errs */
    u_quad_t ifs6_in_adminprohib;
    /* ipv6IfIcmpInTimeExcds, # of input time exceeded errors */
    u_quad_t ifs6_in_timeexceed;
    /* ipv6IfIcmpInParmProblems, # of input parameter problem errors */
    u_quad_t ifs6_in_paramprob;
    /* ipv6IfIcmpInPktTooBigs, # of input packet too big errors */
    u_quad_t ifs6_in_pkttoobig;
    /* ipv6IfIcmpInEchos, # of input echo requests */
    u_quad_t ifs6_in_echo;
    /* ipv6IfIcmpInEchoReplies, # of input echo replies */
    u_quad_t ifs6_in_echoreply;
    /* ipv6IfIcmpInRouterSolicits, # of input router solicitations */
    u_quad_t ifs6_in_routersolicit;
    /* ipv6IfIcmpInRouterAdvertisements, # of input router advertisements */
    u_quad_t ifs6_in_routeradvert;
    /* ipv6IfIcmpInNeighborSolicits, # of input neighbor solicitations */
    u_quad_t ifs6_in_neighborsolicit;
    /* ipv6IfIcmpInNeighborAdvertisements, # of input neighbor advs. */
    u_quad_t ifs6_in_neighboradvert;
    /* ipv6IfIcmpInRedirects, # of input redirects */
    u_quad_t ifs6_in_redirect;
    /* ipv6IfIcmpInGroupMembQueries, # of input MLD queries */
    u_quad_t ifs6_in_mldquery;
    /* ipv6IfIcmpInGroupMembResponses, # of input MLD reports */
    u_quad_t ifs6_in_mldreport;
    /* ipv6IfIcmpInGroupMembReductions, # of input MLD done */
    u_quad_t ifs6_in_mlddone;

    /*
     * Output statistics. We should solve unresolved routing problem...
     */
    /* ipv6IfIcmpOutMsgs, total # of output messages */
    u_quad_t ifs6_out_msg;
    /* ipv6IfIcmpOutErrors, # of output error messages */
    u_quad_t ifs6_out_error;
    /* ipv6IfIcmpOutDestUnreachs, # of output dest unreach errors */
    u_quad_t ifs6_out_dstunreach;
    /* ipv6IfIcmpOutAdminProhibs, # of output admin. prohibited errs */
    u_quad_t ifs6_out_adminprohib;
    /* ipv6IfIcmpOutTimeExcds, # of output time exceeded errors */
    u_quad_t ifs6_out_timeexceed;
    /* ipv6IfIcmpOutParmProblems, # of output parameter problem errors */
    u_quad_t ifs6_out_paramprob;
    /* ipv6IfIcmpOutPktTooBigs, # of output packet too big errors */
    u_quad_t ifs6_out_pkttoobig;
    /* ipv6IfIcmpOutEchos, # of output echo requests */
    u_quad_t ifs6_out_echo;
    /* ipv6IfIcmpOutEchoReplies, # of output echo replies */
    u_quad_t ifs6_out_echoreply;
    /* ipv6IfIcmpOutRouterSolicits, # of output router solicitations */
    u_quad_t ifs6_out_routersolicit;
    /* ipv6IfIcmpOutRouterAdvertisements, # of output router advs. */
    u_quad_t ifs6_out_routeradvert;
    /* ipv6IfIcmpOutNeighborSolicits, # of output neighbor solicitations */
    u_quad_t ifs6_out_neighborsolicit;
    /* ipv6IfIcmpOutNeighborAdvertisements, # of output neighbor advs. */
    u_quad_t ifs6_out_neighboradvert;
    /* ipv6IfIcmpOutRedirects, # of output redirects */
    u_quad_t ifs6_out_redirect;
    /* ipv6IfIcmpOutGroupMembQueries, # of output MLD queries */
    u_quad_t ifs6_out_mldquery;
    /* ipv6IfIcmpOutGroupMembResponses, # of output MLD reports */
    u_quad_t ifs6_out_mldreport;
    /* ipv6IfIcmpOutGroupMembReductions, # of output MLD done */
    u_quad_t ifs6_out_mlddone;
};

struct in6_addrlifetime {
    time_t ia6t_expire;     /* valid lifetime expiration time */
    time_t ia6t_preferred;  /* preferred lifetime expiration time */
    u_int32_t ia6t_vltime;  /* valid lifetime */
    u_int32_t ia6t_pltime;  /* prefix lifetime */
};

struct in6_aliasreq {
    char    ifra_name[IFNAMSIZ];
    struct  sockaddr_in6 ifra_addr;
    struct  sockaddr_in6 ifra_dstaddr;
    struct  sockaddr_in6 ifra_prefixmask;
    int     ifra_flags;
    struct in6_addrlifetime ifra_lifetime;
};


struct in6_ifreq {
    char    ifr_name[IFNAMSIZ];
    union {
        struct  sockaddr_in6 ifru_addr;
        struct  sockaddr_in6 ifru_dstaddr;
        int     ifru_flags;
        int     ifru_flags6;
        int     ifru_metric;
        int     ifru_intval;
        caddr_t ifru_data;
        struct in6_addrlifetime ifru_lifetime;
        struct in6_ifstat ifru_stat;
        struct icmp6_ifstat ifru_icmp6stat;
        u_int32_t ifru_scope_id[16];
    } ifr_ifru;
};
