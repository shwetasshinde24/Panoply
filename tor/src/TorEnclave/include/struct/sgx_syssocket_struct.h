#include <sgx/sys/socket.h>

// #ifndef __SOCKLEN_T
// #define __SOCKLEN_T
// typedef unsigned int socklen_t;
// #endif

// #ifndef SGX_SYSSOCKET_STRUCT_H
// #define SGX_SYSSOCKET_STRUCT_H

// #if !defined(HAVE_NET_LIB)
// /* Absolute file name for network data base files.  */
// #define	_PATH_HEQUIV		"/etc/hosts.equiv"
// #define	_PATH_HOSTS		"/etc/hosts"
// #define	_PATH_NETWORKS		"/etc/networks"
// #define	_PATH_NSSWITCH_CONF	"/etc/nsswitch.conf"
// #define	_PATH_PROTOCOLS		"/etc/protocols"
// #define	_PATH_SERVICES		"/etc/services"

// typedef unsigned int socklen_t;
// typedef unsigned short __kernel_sa_family_t;
// typedef __kernel_sa_family_t sa_family_t;

// /* But these were defined by ISO C without the first `_'.  */
// typedef	unsigned char u_int8_t;
// typedef	unsigned short int u_int16_t;
// typedef	unsigned int u_int32_t;

// struct sockaddr {
//          sa_family_t     sa_family;      /* address family, AF_xxx       */
//          char            sa_data[14];    /* 14 bytes of protocol address */
// };

// struct addrinfo
// {
//   int ai_flags;			/* Input flags.  */
//   int ai_family;		/* Protocol family for socket.  */
//   int ai_socktype;		/* Socket type.  */
//   int ai_protocol;		/* Protocol for socket.  */
//   socklen_t ai_addrlen;		/* Length of socket address.  */
//   void *ai_addr;	/* Socket address for socket. - need to cast back to struct sockaddr* when needed  */
//   char *ai_canonname;		/* Canonical name for service location.  */
//   struct addrinfo *ai_next;	/* Pointer to next in list.  */
// };

// /* Description of data base entry for a single service.  */
// struct servent
// {
//   char *s_name;			/* Official service name.  */
//   char **s_aliases;		/* Alias list.  */
//   int s_port;			/* Port number.  */
//   char *s_proto;		/* Protocol to use.  */
// };


// /* Description of data base entry for a single service.  */
// struct protoent
// {
//   char *p_name;			/* Official protocol name.  */
//   char **p_aliases;		/* Alias list.  */
//   int p_proto;			/* Protocol number.  */
// };

// /* Structure used as control block for asynchronous lookup.  */
// struct gaicb
// {
//   const char *ar_name;		/* Name to look up.  */
//   const char *ar_service;	/* Service name.  */
//   const struct addrinfo *ar_request; /* Additional request specification.  */
//   struct addrinfo *ar_result;	/* Pointer to result.  */
//   /* The following are internal elements.  */
//   int __return;
//   int __glibc_reserved[5];
// };

// struct in_addr {
//     unsigned long s_addr;          // load with inet_pton()
// };

// struct sockaddr_in {
//     short            sin_family;   // e.g. AF_INET, AF_INET6
//     unsigned short   sin_port;     // e.g. htons(3490)
//     struct in_addr   sin_addr;     // see struct in_addr, below
//     char             sin_zero[8];  // zero this if you want to
// };

// struct in6_addr {
//     unsigned char   s6_addr[16];   // load with inet_pton()
// };

// struct sockaddr_in6 {
//     u_int16_t       sin6_family;   // address family, AF_INET6
//     u_int16_t       sin6_port;     // port number, Network Byte Order
//     u_int32_t       sin6_flowinfo; // IPv6 flow information
//     struct in6_addr sin6_addr;     // IPv6 address
//     u_int32_t       sin6_scope_id; // Scope ID
// };

// // struct sockaddr_storage {
// //     sa_family_t  ss_family;     // address family

// //     // all this is padding, implementation specific, ignore it:
// //     char      __ss_pad1[_SS_PAD1SIZE];
// //     int64_t   __ss_align;
// //     char      __ss_pad2[_SS_PAD2SIZE];
// // };

// // Define const for socket address // 
// /* Supported address families. */
// #define AF_UNSPEC       0
// #define AF_UNIX         1       /* Unix domain sockets          */
// #define AF_LOCAL        1       /* POSIX name for AF_UNIX       */
// #define AF_INET         2       /* Internet IP Protocol         */
// #define AF_AX25         3       /* Amateur Radio AX.25          */
// #define AF_IPX          4       /* Novell IPX                   */
// #define AF_APPLETALK    5       /* AppleTalk DDP                */
// #define AF_NETROM       6       /* Amateur Radio NET/ROM        */
// #define AF_BRIDGE       7       /* Multiprotocol bridge         */
// #define AF_ATMPVC       8       /* ATM PVCs                     */
// #define AF_X25          9       /* Reserved for X.25 project    */
// #define AF_INET6        10      /* IP version 6                 */
// #define AF_ROSE         11      /* Amateur Radio X.25 PLP       */
// #define AF_DECnet       12      /* Reserved for DECnet project  */
// #define AF_NETBEUI      13      /* Reserved for 802.2LLC project*/
// #define AF_SECURITY     14      /* Security callback pseudo AF */
// #define AF_KEY          15      /* PF_KEY key management API */
// #define AF_NETLINK      16
// #define AF_ROUTE        AF_NETLINK /* Alias to emulate 4.4BSD */
// #define AF_PACKET       17      /* Packet family                */
// #define AF_ASH          18      /* Ash                          */
// #define AF_ECONET       19      /* Acorn Econet                 */
// #define AF_ATMSVC       20      /* ATM SVCs                     */
// #define AF_RDS          21      /* RDS sockets                  */
// #define AF_SNA          22      /* Linux SNA Project (nutters!) */
// #define AF_IRDA         23      /* IRDA sockets                 */
// #define AF_PPPOX        24      /* PPPoX sockets                */
// #define AF_WANPIPE      25      /* Wanpipe API Sockets */
// #define AF_LLC          26      /* Linux LLC                    */
// #define AF_IB           27      /* Native InfiniBand address    */
// #define AF_MPLS         28      /* MPLS */
// #define AF_CAN          29      /* Controller Area Network      */
// #define AF_TIPC         30      /* TIPC sockets                 */
// #define AF_BLUETOOTH    31      /* Bluetooth sockets            */
// #define AF_IUCV         32      /* IUCV sockets                 */
// #define AF_RXRPC        33      /* RxRPC sockets                */
// #define AF_ISDN         34      /* mISDN sockets                */
// #define AF_PHONET       35      /* Phonet sockets               */
// #define AF_IEEE802154   36      /* IEEE802154 sockets           */
// #define AF_CAIF         37      /* CAIF sockets                 */
// #define AF_ALG          38      /* Algorithm sockets            */
// #define AF_NFC          39      /* NFC sockets                  */
// #define AF_VSOCK        40      /* vSockets                     */
// #define AF_MAX          41      /* For now.. */

// /* Protocol families, same as address families. */
// #define PF_UNSPEC       AF_UNSPEC
// #define PF_UNIX         AF_UNIX
// #define PF_LOCAL        AF_LOCAL
// #define PF_INET         AF_INET
// #define PF_AX25         AF_AX25
// #define PF_IPX          AF_IPX
// #define PF_APPLETALK    AF_APPLETALK
// #define PF_NETROM       AF_NETROM
// #define PF_BRIDGE       AF_BRIDGE
// #define PF_ATMPVC       AF_ATMPVC
// #define PF_X25          AF_X25
// #define PF_INET6        AF_INET6
// #define PF_ROSE         AF_ROSE
// #define PF_DECnet       AF_DECnet
// #define PF_NETBEUI      AF_NETBEUI
// #define PF_SECURITY     AF_SECURITY
// #define PF_KEY          AF_KEY
// #define PF_NETLINK      AF_NETLINK
// #define PF_ROUTE        AF_ROUTE
// #define PF_PACKET       AF_PACKET
// #define PF_ASH          AF_ASH
// #define PF_ECONET       AF_ECONET
// #define PF_ATMSVC       AF_ATMSVC
// #define PF_RDS          AF_RDS
// #define PF_SNA          AF_SNA
// #define PF_IRDA         AF_IRDA
// #define PF_PPPOX        AF_PPPOX
// #define PF_WANPIPE      AF_WANPIPE
// #define PF_LLC          AF_LLC
// #define PF_IB           AF_IB
// #define PF_MPLS         AF_MPLS
// #define PF_CAN          AF_CAN
// #define PF_TIPC         AF_TIPC
// #define PF_BLUETOOTH    AF_BLUETOOTH
// #define PF_IUCV         AF_IUCV
// #define PF_RXRPC        AF_RXRPC
// #define PF_ISDN         AF_ISDN
// #define PF_PHONET       AF_PHONET
// #define PF_IEEE802154   AF_IEEE802154
// #define PF_CAIF         AF_CAIF
// #define PF_ALG          AF_ALG
// #define PF_NFC          AF_NFC
// #define PF_VSOCK        AF_VSOCK
// #define PF_MAX          AF_MAX

// /* Maximum queue length specifiable by listen.  */
// #define SOMAXCONN       128

// /* Flags we can use with send/ and recv. 
//    Added those for 1003.1g not all are supported yet
//  */
 
// #define MSG_OOB         1
// #define MSG_PEEK        2
// #define MSG_DONTROUTE   4
// #define MSG_TRYHARD     4       /* Synonym for MSG_DONTROUTE for DECnet */
// #define MSG_CTRUNC      8
// #define MSG_PROBE       0x10    /* Do not send. Only probe path f.e. for MTU */
// #define MSG_TRUNC       0x20
// #define MSG_DONTWAIT    0x40    /* Nonblocking io                */
// #define MSG_EOR         0x80    /* End of record */
// #define MSG_WAITALL     0x100   /* Wait for a full request */
// #define MSG_FIN         0x200
// #define MSG_SYN         0x400
// #define MSG_CONFIRM     0x800   /* Confirm path validity */
// #define MSG_RST         0x1000
// #define MSG_ERRQUEUE    0x2000  /* Fetch message from error queue */
// #define MSG_NOSIGNAL    0x4000  /* Do not generate SIGPIPE */
// #define MSG_MORE        0x8000  /* Sender will send more */
// #define MSG_WAITFORONE  0x10000 /* recvmmsg(): block until 1+ packets avail */
// #define MSG_SENDPAGE_NOTLAST 0x20000 /* sendpage() internal : not the last page */
// #define MSG_EOF         MSG_FIN

// #define MSG_FASTOPEN    0x20000000      /* Send data in TCP SYN */
// #define MSG_CMSG_CLOEXEC 0x40000000     /* Set close_on_exec for file
//                                            descriptor received through
//                                            SCM_RIGHTS */
// #if defined(CONFIG_COMPAT)
// #define MSG_CMSG_COMPAT 0x80000000      /* This message needs 32 bit fixups */
// #else
// #define MSG_CMSG_COMPAT 0               /* We never have 32 bit fixups */
// #endif


// /* Setsockoptions(2) level. Thanks to BSD these must match IPPROTO_xxx */
// #define SOL_IP          0
// /* #define SOL_ICMP     1       No-no-no! Due to Linux :-) we cannot use SOL_ICMP=1 */
// #define SOL_TCP         6
// #define SOL_UDP         17
// #define SOL_IPV6        41
// #define SOL_ICMPV6      58
// #define SOL_SCTP        132
// #define SOL_UDPLITE     136     /* UDP-Lite (RFC 3828) */
// #define SOL_RAW         255
// #define SOL_IPX         256
// #define SOL_AX25        257
// #define SOL_ATALK       258
// #define SOL_NETROM      259
// #define SOL_ROSE        260
// #define SOL_DECNET      261
// #define SOL_X25         262
// #define SOL_PACKET      263
// #define SOL_ATM         264     /* ATM layer (cell level) */
// #define SOL_AAL         265     /* ATM Adaption Layer (packet level) */
// #define SOL_IRDA        266
// #define SOL_NETBEUI     267
// #define SOL_LLC         268
// #define SOL_DCCP        269
// #define SOL_NETLINK     270
// #define SOL_TIPC        271
// #define SOL_RXRPC       272
// #define SOL_PPPOL2TP    273
// #define SOL_BLUETOOTH   274
// #define SOL_PNPIPE      275
// #define SOL_RDS         276
// #define SOL_IUCV        277
// #define SOL_CAIF        278
// #define SOL_ALG         279
// #define SOL_NFC         280

// /* IPX options */
// #define IPX_TYPE        1

// /* Lookup mode.  */
// #  define GAI_WAIT	0
// #  define GAI_NOWAIT	1

// /* Possible values for `ai_flags' field in `addrinfo' structure.  */
// # define AI_PASSIVE	0x0001	/* Socket address is intended for `bind'.  */
// # define AI_CANONNAME	0x0002	/* Request for canonical name.  */
// # define AI_NUMERICHOST	0x0004	/* Don't use name resolution.  */
// # define AI_V4MAPPED	0x0008	/* IPv4 mapped addresses are acceptable.  */
// # define AI_ALL		0x0010	/* Return IPv4 mapped and IPv6 addresses.  */
// # define AI_ADDRCONFIG	0x0020	/* Use configuration of this host to choose
// 				   returned address type..  */

// #  define AI_IDN	0x0040	/* IDN encode input (assuming it is encoded
// 				   in the current locale's character set)
// 				   before looking it up. */
// #  define AI_CANONIDN	0x0080	/* Translate canonical name from IDN format. */
// #  define AI_IDN_ALLOW_UNASSIGNED 0x0100 /* Don't reject unassigned Unicode
// 					    code points.  */
// #  define AI_IDN_USE_STD3_ASCII_RULES 0x0200 /* Validate strings according to
// 						STD3 rules.  */

// # define AI_NUMERICSERV	0x0400	/* Don't use name resolution.  */

// /* Error values for `getaddrinfo' function.  */
// # define EAI_BADFLAGS	  -1	/* Invalid value for `ai_flags' field.  */
// # define EAI_NONAME	  -2	/* NAME or SERVICE is unknown.  */
// # define EAI_AGAIN	  -3	/* Temporary failure in name resolution.  */
// # define EAI_FAIL	  -4	/* Non-recoverable failure in name res.  */
// # define EAI_FAMILY	  -6	/* `ai_family' not supported.  */
// # define EAI_SOCKTYPE	  -7	/* `ai_socktype' not supported.  */
// # define EAI_SERVICE	  -8	/* SERVICE not supported for `ai_socktype'.  */
// # define EAI_MEMORY	  -10	/* Memory allocation failure.  */
// # define EAI_SYSTEM	  -11	/* System error returned in `errno'.  */
// # define EAI_OVERFLOW	  -12	/* Argument buffer overflow.  */

// #  define EAI_NODATA	  -5	/* No address associated with NAME.  */
// #  define EAI_ADDRFAMILY  -9	/* Address family for NAME not supported.  */
// #  define EAI_INPROGRESS  -100	/* Processing request in progress.  */
// #  define EAI_CANCELED	  -101	/* Request canceled.  */
// #  define EAI_NOTCANCELED -102	/* Request not canceled.  */
// #  define EAI_ALLDONE	  -103	/* All requests done.  */
// #  define EAI_INTR	  -104	/* Interrupted by a signal.  */
// #  define EAI_IDN_ENCODE  -105	/* IDN encoding failed.  */

// #  define NI_MAXHOST      1025
// #  define NI_MAXSERV      32

// # define NI_NUMERICHOST	1	/* Don't try to look up hostname.  */
// # define NI_NUMERICSERV 2	/* Don't convert port number to name.  */
// # define NI_NOFQDN	4	/* Only return nodename portion.  */
// # define NI_NAMEREQD	8	/* Don't return numeric addresses.  */
// # define NI_DGRAM	16	/* Look up UDP service rather than TCP.  */

// #  define NI_IDN	32	/* Convert name from IDN format.  */
// #  define NI_IDN_ALLOW_UNASSIGNED 64 /* Don't reject unassigned Unicode
// 					code points.  */
// #  define NI_IDN_USE_STD3_ASCII_RULES 128 /* Validate strings according to*/			

// /* Types of sockets.  */
// enum __socket_type
// {
//   SOCK_STREAM = 1,    /* Sequenced, reliable, connection-based
//            byte streams.  */
// #define SOCK_STREAM SOCK_STREAM
//   SOCK_DGRAM = 2,   /* Connectionless, unreliable datagrams
//            of fixed maximum length.  */
// #define SOCK_DGRAM SOCK_DGRAM
//   SOCK_RAW = 3,     /* Raw protocol interface.  */
// #define SOCK_RAW SOCK_RAW
//   SOCK_RDM = 4,     /* Reliably-delivered messages.  */
// #define SOCK_RDM SOCK_RDM
//   SOCK_SEQPACKET = 5,   /* Sequenced, reliable, connection-based,
//            datagrams of fixed maximum length.  */
// #define SOCK_SEQPACKET SOCK_SEQPACKET
//   SOCK_DCCP = 6,    /* Datagram Congestion Control Protocol.  */
// #define SOCK_DCCP SOCK_DCCP
//   SOCK_PACKET = 10,   /* Linux specific way of getting packets
//            at the dev level.  For writing rarp and
//            other similar things on the user level. */
// #define SOCK_PACKET SOCK_PACKET

//   /* Flags to be ORed into the type parameter of socket and socketpair and
//      used for the flags parameter of paccept.  */

//   SOCK_CLOEXEC = 02000000,  /* Atomically set close-on-exec flag for the
//            new descriptor(s).  */
// #define SOCK_CLOEXEC SOCK_CLOEXEC
//   SOCK_NONBLOCK = 00004000  /* Atomically mark descriptor(s) as
//            non-blocking.  */
// #define SOCK_NONBLOCK SOCK_NONBLOCK
// };

// #ifndef __ASM_GENERIC_SOCKET_H
// #define __ASM_GENERIC_SOCKET_H

// /* For setsockopt(2) */
// #define SOL_SOCKET  1

// #define SO_DEBUG  1
// #define SO_REUSEADDR  2
// #define SO_TYPE   3
// #define SO_ERROR  4
// #define SO_DONTROUTE  5
// #define SO_BROADCAST  6
// #define SO_SNDBUF 7
// #define SO_RCVBUF 8
// #define SO_SNDBUFFORCE  32
// #define SO_RCVBUFFORCE  33
// #define SO_KEEPALIVE  9
// #define SO_OOBINLINE  10
// #define SO_NO_CHECK 11
// #define SO_PRIORITY 12
// #define SO_LINGER 13
// #define SO_BSDCOMPAT  14
// #define SO_REUSEPORT  15
// #ifndef SO_PASSCRED /* powerpc only differs in these */
// #define SO_PASSCRED 16
// #define SO_PEERCRED 17
// #define SO_RCVLOWAT 18
// #define SO_SNDLOWAT 19
// #define SO_RCVTIMEO 20
// #define SO_SNDTIMEO 21
// #endif

// /* Security levels - as per NRL IPv6 - don't actually do anything */
// #define SO_SECURITY_AUTHENTICATION    22
// #define SO_SECURITY_ENCRYPTION_TRANSPORT  23
// #define SO_SECURITY_ENCRYPTION_NETWORK    24

// #define SO_BINDTODEVICE 25

// /* Socket filtering */
// #define SO_ATTACH_FILTER  26
// #define SO_DETACH_FILTER  27
// #define SO_GET_FILTER   SO_ATTACH_FILTER

// #define SO_PEERNAME   28
// #define SO_TIMESTAMP    29
// #define SCM_TIMESTAMP   SO_TIMESTAMP

// #define SO_ACCEPTCONN   30

// #define SO_PEERSEC    31
// #define SO_PASSSEC    34
// #define SO_TIMESTAMPNS    35
// #define SCM_TIMESTAMPNS   SO_TIMESTAMPNS

// #define SO_MARK     36

// #define SO_TIMESTAMPING   37
// #define SCM_TIMESTAMPING  SO_TIMESTAMPING

// #define SO_PROTOCOL   38
// #define SO_DOMAIN   39

// #define SO_RXQ_OVFL             40

// #define SO_WIFI_STATUS    41
// #define SCM_WIFI_STATUS SO_WIFI_STATUS
// #define SO_PEEK_OFF   42

// /* Instruct lower device to use last 4-bytes of skb data as FCS */
// #define SO_NOFCS    43

// #define SO_LOCK_FILTER    44

// #define SO_SELECT_ERR_QUEUE 45

// #define SO_BUSY_POLL    46

// #define SO_MAX_PACING_RATE  47

// #endif /* __ASM_GENERIC_SOCKET_H */

// #ifndef _LINUX_TCP_H
// #define _LINUX_TCP_H
// /*
//  * TCP general constants
//  */
// #define TCP_MSS_DEFAULT    536U /* IPv4 (RFC1122, RFC2581) */
// #define TCP_MSS_DESIRED   1220U /* IPv6 (tunneled), EDNS0 (RFC3226) */

// /* TCP socket options */
// #define TCP_NODELAY   1 /* Turn off Nagle's algorithm. */
// #define TCP_MAXSEG    2 /* Limit MSS */
// #define TCP_CORK    3 /* Never send partially complete segments */
// #define TCP_KEEPIDLE    4 /* Start keeplives after this period */
// #define TCP_KEEPINTVL   5 /* Interval between keepalives */
// #define TCP_KEEPCNT   6 /* Number of keepalives before death */
// #define TCP_SYNCNT    7 /* Number of SYN retransmits */
// #define TCP_LINGER2   8 /* Life time of orphaned FIN-WAIT-2 state */
// #define TCP_DEFER_ACCEPT  9 /* Wake up listener only when data arrive */
// #define TCP_WINDOW_CLAMP  10  /* Bound advertised window */
// #define TCP_INFO    11  /* Information about this connection. */
// #define TCP_QUICKACK    12  /* Block/reenable quick acks */
// #define TCP_CONGESTION    13  /* Congestion control algorithm */
// #define TCP_MD5SIG    14  /* TCP MD5 Signature (RFC2385) */
// #define TCP_THIN_LINEAR_TIMEOUTS 16      /* Use linear timeouts for thin streams*/
// #define TCP_THIN_DUPACK         17      /* Fast retrans. after 1 dupack */
// #define TCP_USER_TIMEOUT  18  /* How long for loss retry before timeout */
// #define TCP_REPAIR    19  /* TCP sock is under repair right now */
// #define TCP_REPAIR_QUEUE  20
// #define TCP_QUEUE_SEQ   21
// #define TCP_REPAIR_OPTIONS  22
// #define TCP_FASTOPEN    23  /* Enable FastOpen on listeners */
// #define TCP_TIMESTAMP   24
// #define TCP_NOTSENT_LOWAT 25  /* limit number of unsent bytes in write queue */

// enum {
//   TCP_NO_QUEUE,
//   TCP_RECV_QUEUE,
//   TCP_SEND_QUEUE,
//   TCP_QUEUES_NR,
// };

// /* for TCP_INFO socket option */
// #define TCPI_OPT_TIMESTAMPS 1
// #define TCPI_OPT_SACK   2
// #define TCPI_OPT_WSCALE   4
// #define TCPI_OPT_ECN    8 /* ECN was negociated at TCP session init */
// #define TCPI_OPT_ECN_SEEN 16 /* we received at least one packet with ECT */
// #define TCPI_OPT_SYN_DATA 32 /* SYN-ACK acked data in SYN sent or rcvd */

// enum tcp_ca_state {
//   TCP_CA_Open = 0,
// #define TCPF_CA_Open  (1<<TCP_CA_Open)
//   TCP_CA_Disorder = 1,
// #define TCPF_CA_Disorder (1<<TCP_CA_Disorder)
//   TCP_CA_CWR = 2,
// #define TCPF_CA_CWR (1<<TCP_CA_CWR)
//   TCP_CA_Recovery = 3,
// #define TCPF_CA_Recovery (1<<TCP_CA_Recovery)
//   TCP_CA_Loss = 4
// #define TCPF_CA_Loss  (1<<TCP_CA_Loss)
// };

// /* Standard well-defined IP protocols.  */
// enum
//   {
//     IPPROTO_IP = 0,    /* Dummy protocol for TCP.  */
// #define IPPROTO_IP    IPPROTO_IP
//     IPPROTO_ICMP = 1,    /* Internet Control Message Protocol.  */
// #define IPPROTO_ICMP    IPPROTO_ICMP
//     IPPROTO_IGMP = 2,    /* Internet Group Management Protocol. */
// #define IPPROTO_IGMP    IPPROTO_IGMP
//     IPPROTO_IPIP = 4,    /* IPIP tunnels (older KA9Q tunnels use 94).  */
// #define IPPROTO_IPIP    IPPROTO_IPIP
//     IPPROTO_TCP = 6,     /* Transmission Control Protocol.  */
// #define IPPROTO_TCP   IPPROTO_TCP
//     IPPROTO_EGP = 8,     /* Exterior Gateway Protocol.  */
// #define IPPROTO_EGP   IPPROTO_EGP
//     IPPROTO_PUP = 12,    /* PUP protocol.  */
// #define IPPROTO_PUP   IPPROTO_PUP
//     IPPROTO_UDP = 17,    /* User Datagram Protocol.  */
// #define IPPROTO_UDP   IPPROTO_UDP
//     IPPROTO_IDP = 22,    /* XNS IDP protocol.  */
// #define IPPROTO_IDP   IPPROTO_IDP
//     IPPROTO_TP = 29,     /* SO Transport Protocol Class 4.  */
// #define IPPROTO_TP    IPPROTO_TP
//     IPPROTO_DCCP = 33,     /* Datagram Congestion Control Protocol.  */
// #define IPPROTO_DCCP    IPPROTO_DCCP
//     IPPROTO_IPV6 = 41,     /* IPv6 header.  */
// #define IPPROTO_IPV6    IPPROTO_IPV6
//     IPPROTO_RSVP = 46,     /* Reservation Protocol.  */
// #define IPPROTO_RSVP    IPPROTO_RSVP
//     IPPROTO_GRE = 47,    /* General Routing Encapsulation.  */
// #define IPPROTO_GRE   IPPROTO_GRE
//     IPPROTO_ESP = 50,      /* encapsulating security payload.  */
// #define IPPROTO_ESP   IPPROTO_ESP
//     IPPROTO_AH = 51,       /* authentication header.  */
// #define IPPROTO_AH    IPPROTO_AH
//     IPPROTO_MTP = 92,    /* Multicast Transport Protocol.  */
// #define IPPROTO_MTP   IPPROTO_MTP
//     IPPROTO_BEETPH = 94,   /* IP option pseudo header for BEET.  */
// #define IPPROTO_BEETPH    IPPROTO_BEETPH
//     IPPROTO_ENCAP = 98,    /* Encapsulation Header.  */
// #define IPPROTO_ENCAP   IPPROTO_ENCAP
//     IPPROTO_PIM = 103,     /* Protocol Independent Multicast.  */
// #define IPPROTO_PIM   IPPROTO_PIM
//     IPPROTO_COMP = 108,    /* Compression Header Protocol.  */
// #define IPPROTO_COMP    IPPROTO_COMP
//     IPPROTO_SCTP = 132,    /* Stream Control Transmission Protocol.  */
// #define IPPROTO_SCTP    IPPROTO_SCTP
//     IPPROTO_UDPLITE = 136, /* UDP-Lite protocol.  */
// #define IPPROTO_UDPLITE   IPPROTO_UDPLITE
//     IPPROTO_RAW = 255,     /* Raw IP packets.  */
// #define IPPROTO_RAW   IPPROTO_RAW
//     IPPROTO_MAX
//   };

// /* If __USE_KERNEL_IPV6_DEFS is defined then the user has included the kernel
//    network headers first and we should use those ABI-identical definitions
//    instead of our own.  */
// #ifndef __USE_KERNEL_IPV6_DEFS
// enum
//   {
//     IPPROTO_HOPOPTS = 0,   /* IPv6 Hop-by-Hop options.  */
// #define IPPROTO_HOPOPTS   IPPROTO_HOPOPTS
//     IPPROTO_ROUTING = 43,  /* IPv6 routing header.  */
// #define IPPROTO_ROUTING   IPPROTO_ROUTING
//     IPPROTO_FRAGMENT = 44, /* IPv6 fragmentation header.  */
// #define IPPROTO_FRAGMENT  IPPROTO_FRAGMENT
//     IPPROTO_ICMPV6 = 58,   /* ICMPv6.  */
// #define IPPROTO_ICMPV6    IPPROTO_ICMPV6
//     IPPROTO_NONE = 59,     /* IPv6 no next header.  */
// #define IPPROTO_NONE    IPPROTO_NONE
//     IPPROTO_DSTOPTS = 60,  /* IPv6 destination options.  */
// #define IPPROTO_DSTOPTS   IPPROTO_DSTOPTS
//     IPPROTO_MH = 135       /* IPv6 mobility header.  */
// #define IPPROTO_MH    IPPROTO_MH
//   };
// #endif /* !__USE_KERNEL_IPV6_DEFS */

// /* Internet address.  */
// typedef uint32_t in_addr_t;

// /* Type to represent a port.  */
// typedef uint16_t in_port_t;

// /* Standard well-known ports.  */
// enum
//   {
//     IPPORT_ECHO = 7,    /* Echo service.  */
//     IPPORT_DISCARD = 9,   /* Discard transmissions service.  */
//     IPPORT_SYSTAT = 11,   /* System status service.  */
//     IPPORT_DAYTIME = 13,  /* Time of day service.  */
//     IPPORT_NETSTAT = 15,  /* Network status service.  */
//     IPPORT_FTP = 21,    /* File Transfer Protocol.  */
//     IPPORT_TELNET = 23,   /* Telnet protocol.  */
//     IPPORT_SMTP = 25,   /* Simple Mail Transfer Protocol.  */
//     IPPORT_TIMESERVER = 37, /* Timeserver service.  */
//     IPPORT_NAMESERVER = 42, /* Domain Name Service.  */
//     IPPORT_WHOIS = 43,    /* Internet Whois service.  */
//     IPPORT_MTP = 57,

//     IPPORT_TFTP = 69,   /* Trivial File Transfer Protocol.  */
//     IPPORT_RJE = 77,
//     IPPORT_FINGER = 79,   /* Finger service.  */
//     IPPORT_TTYLINK = 87,
//     IPPORT_SUPDUP = 95,   /* SUPDUP protocol.  */


//     IPPORT_EXECSERVER = 512,  /* execd service.  */
//     IPPORT_LOGINSERVER = 513, /* rlogind service.  */
//     IPPORT_CMDSERVER = 514,
//     IPPORT_EFSSERVER = 520,

//     /* UDP ports.  */
//     IPPORT_BIFFUDP = 512,
//     IPPORT_WHOSERVER = 513,
//     IPPORT_ROUTESERVER = 520,

//     /* Ports less than this value are reserved for privileged processes.  */
//     IPPORT_RESERVED = 1024,

//     /* Ports greater this value are reserved for (non-privileged) servers.  */
//     IPPORT_USERRESERVED = 5000
//   };

// /* Definitions of the bits in an Internet address integer.

//    On subnets, host and network parts are found according to
//    the subnet mask, not these masks.  */

// #define IN_CLASSA(a)    ((((in_addr_t)(a)) & 0x80000000) == 0)
// #define IN_CLASSA_NET   0xff000000
// #define IN_CLASSA_NSHIFT  24
// #define IN_CLASSA_HOST    (0xffffffff & ~IN_CLASSA_NET)
// #define IN_CLASSA_MAX   128

// #define IN_CLASSB(a)    ((((in_addr_t)(a)) & 0xc0000000) == 0x80000000)
// #define IN_CLASSB_NET   0xffff0000
// #define IN_CLASSB_NSHIFT  16
// #define IN_CLASSB_HOST    (0xffffffff & ~IN_CLASSB_NET)
// #define IN_CLASSB_MAX   65536

// #define IN_CLASSC(a)    ((((in_addr_t)(a)) & 0xe0000000) == 0xc0000000)
// #define IN_CLASSC_NET   0xffffff00
// #define IN_CLASSC_NSHIFT  8
// #define IN_CLASSC_HOST    (0xffffffff & ~IN_CLASSC_NET)

// #define IN_CLASSD(a)    ((((in_addr_t)(a)) & 0xf0000000) == 0xe0000000)
// #define IN_MULTICAST(a)   IN_CLASSD(a)

// #define IN_EXPERIMENTAL(a)  ((((in_addr_t)(a)) & 0xe0000000) == 0xe0000000)
// #define IN_BADCLASS(a)    ((((in_addr_t)(a)) & 0xf0000000) == 0xf0000000)

// /* Address to accept any incoming messages.  */
// #define INADDR_ANY    ((in_addr_t) 0x00000000)
// /* Address to send to all hosts.  */
// #define INADDR_BROADCAST  ((in_addr_t) 0xffffffff)
// /* Address indicating an error return.  */
// #define INADDR_NONE   ((in_addr_t) 0xffffffff)

// /* Network number for local host loopback.  */
// #define IN_LOOPBACKNET    127
// /* Address to loopback in software to local host.  */
// #ifndef INADDR_LOOPBACK
// # define INADDR_LOOPBACK  ((in_addr_t) 0x7f000001) /* Inet 127.0.0.1.  */
// #endif

// /* Defines for Multicast INADDR.  */
// #define INADDR_UNSPEC_GROUP ((in_addr_t) 0xe0000000) /* 224.0.0.0 */
// #define INADDR_ALLHOSTS_GROUP ((in_addr_t) 0xe0000001) /* 224.0.0.1 */
// #define INADDR_ALLRTRS_GROUP    ((in_addr_t) 0xe0000002) /* 224.0.0.2 */
// #define INADDR_MAX_LOCAL_GROUP  ((in_addr_t) 0xe00000ff) /* 224.0.0.255 */

// #endif

// #endif
// #endif