#ifndef SGX_ARPAINET_UTIL_H
#define SGX_ARPAINET_UTIL_H

#include <struct/sgx_arpainet_struct.h>

#ifdef __cplusplus
extern "C"	{
#endif

extern in_addr_t sgx_wrapper_inet_addr (const char *cp);
extern in_addr_t sgx_wrapper_inet_lnaof (struct in_addr in);
extern struct in_addr sgx_wrapper_inet_makeaddr (in_addr_t net, in_addr_t host);
extern in_addr_t sgx_wrapper_inet_netof (struct in_addr in);
extern in_addr_t sgx_wrapper_inet_network (const char *cp);
extern char *sgx_wrapper_inet_ntoa (struct in_addr in);
extern int sgx_wrapper_inet_pton (int af, const char *cp, void *buf);
extern char *sgx_wrapper_inet_ntop (int af,  const void *cp, char *buf, socklen_t len);

#ifdef __cplusplus
}
#endif

#define inet_addr(A) sgx_wrapper_inet_addr(A)
#define inet_lnaof(A) sgx_wrapper_inet_lnaof(A)
#define inet_makeaddr(A, B) sgx_wrapper_inet_makeaddr(A, B) 
#define inet_netof(A) sgx_wrapper_inet_netof(A)
#define inet_network(A) sgx_wrapper_inet_network(A)
#define inet_ntoa(A) sgx_wrapper_inet_ntoa(A)
#define inet_pton(A, B, C) sgx_wrapper_inet_pton(A, B, C)
#define inet_ntop(A, B, C, D) sgx_wrapper_inet_ntop(A, B, C, D)

#endif 