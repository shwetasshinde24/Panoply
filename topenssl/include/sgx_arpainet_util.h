#ifndef SGX_ARPAINET_UTIL_H
#define SGX_ARPAINET_UTIL_H

#include <struct/sgx_arpainet_struct.h>
#include <proxy/sgx_arpainet_t.h>

static inline in_addr_t sgx_wrapper_inet_addr (const char *cp)
{
	in_addr_t retval;
	ocall_inet_addr(&retval, cp);
	return retval;
}

static inline in_addr_t sgx_wrapper_inet_lnaof (struct in_addr in)
{
	in_addr_t retval;
	ocall_inet_lnaof(&retval, in);
	return retval;
}

static inline struct in_addr sgx_wrapper_inet_makeaddr (in_addr_t net, in_addr_t host)
{
	struct in_addr retval;
	ocall_inet_makeaddr(&retval, net, host);
	return retval;
}

static inline in_addr_t sgx_wrapper_inet_netof (struct in_addr in)
{
	in_addr_t retval;
	ocall_inet_netof(&retval, in);
	return retval;
}

static inline in_addr_t sgx_wrapper_inet_network (const char *cp)
{
	in_addr_t retval;
	ocall_inet_network(&retval, cp);
	return retval;
}

static inline char *sgx_wrapper_inet_ntoa (struct in_addr in)
{
	char *retval;
	ocall_inet_ntoa(&retval, in);
	return retval;
}

static inline int sgx_wrapper_inet_pton (int af, const char *cp, void *buf)
{
	int retval;
	ocall_inet_pton(&retval, af, cp, buf);
	return retval;
}

static inline char *sgx_wrapper_inet_ntop (int af,  const void *cp, char *buf, socklen_t len)
{
	char *retval;
	ocall_inet_ntop(&retval, af, cp, buf, len);
	return retval;
}

#define inet_addr(A) sgx_wrapper_inet_addr(A)
#define inet_lnaof(A) sgx_wrapper_inet_lnaof(A)
#define inet_makeaddr(A, B) sgx_wrapper_inet_makeaddr(A, B) 
#define inet_netof(A) sgx_wrapper_inet_netof(A)
#define inet_network(A) sgx_wrapper_inet_network(A)
#define inet_ntoa(A) sgx_wrapper_inet_ntoa(A)
#define inet_pton(A, B, C) sgx_wrapper_inet_pton(A, B, C)
#define inet_ntop(A, B, C, D) sgx_wrapper_inet_ntop(A, B, C, D)

#endif 