#ifndef SGX_IFADDRS_UTIL_H
#define SGX_IFADDRS_UTIL_H

#include <struct/sgx_ifaddrs_struct.h>
#include <proxy/sgx_ifaddrs_t.h>


static inline int sgx_wrapper_getifaddrs(struct ifaddrs **ifap)
{
	int retval;
	ocall_getifaddrs(&retval, ifap);
	return retval;
}

static inline void sgx_wrapper_freeifaddrs(struct ifaddrs *ifa)
{
	ocall_freeifaddrs(ifa);
}

#define getifaddrs(A) sgx_wrapper_getifaddrs(A)
#define freeifaddrs(A) sgx_wrapper_freeifaddrs(A)

#endif