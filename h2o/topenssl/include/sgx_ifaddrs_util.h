#ifndef SGX_IFADDRS_UTIL_H
#define SGX_IFADDRS_UTIL_H

#include <struct/sgx_ifaddrs_struct.h>
#include <proxy/sgx_ifaddrs_t.h>

#ifdef __cplusplus
extern "C"	{
#endif 

extern int sgx_wrapper_getifaddrs(struct ifaddrs **ifap);
extern void sgx_wrapper_freeifaddrs(struct ifaddrs *ifa);

#ifdef __cplusplus
}
#endif 

#define getifaddrs(A) sgx_wrapper_getifaddrs(A)
#define freeifaddrs(A) sgx_wrapper_freeifaddrs(A)

#endif