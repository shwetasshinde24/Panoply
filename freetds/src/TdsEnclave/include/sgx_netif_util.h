#ifndef SGX_NETIF_UTIL_H
#define SGX_NETIF_UTIL_H

#include <struct/sgx_netif_struct.h>
#include <proxy/sgx_netif_t.h>

static inline unsigned int sgx_wrapper_if_nametoindex(const char *ifname)
{
	unsigned int retval;
	ocall_if_nametoindex(&retval, ifname);
	return retval;
}

static inline char *sgx_wrapper_if_indextoname(unsigned int ifindex, char *ifname)
{
	char* retval;
	ocall_if_indextoname(&retval, ifindex, ifname);
	return retval;
}

static inline struct if_nameindex *sgx_wrapper_if_nameindex(void)
{
	struct if_nameindex *retval;
	ocall_if_nameindex(&retval);
	return retval;
}

static inline void sgx_wrapper_if_freenameindex(struct if_nameindex *ptr)
{
	ocall_if_freenameindex(ptr);
}

#define if_nametoindex(A) sgx_wrapper_if_nametoindex(A)
#define if_indextoname(A, B) sgx_wrapper_if_indextoname(A, B)
#define if_nameindex() sgx_wrapper_if_nameindex()
#define if_freenameindex(A) sgx_wrapper_if_freenameindex(A)

#endif