#ifndef SGX_NETIF_UTIL_H
#define SGX_NETIF_UTIL_H

#include <struct/sgx_netif_struct.h>
#include <proxy/sgx_netif_t.h>

#ifdef __cplusplus
extern "C"	{
#endif 

extern unsigned int sgx_wrapper_if_nametoindex(const char *ifname);
extern char *sgx_wrapper_if_indextoname(unsigned int ifindex, char *ifname);
extern struct if_nameindex *sgx_wrapper_if_nameindex(void);
extern void sgx_wrapper_if_freenameindex(struct if_nameindex *ptr);

#ifdef __cplusplus
}
#endif 

#define if_nametoindex(A) sgx_wrapper_if_nametoindex(A)
#define if_indextoname(A, B) sgx_wrapper_if_indextoname(A, B)
#define if_nameindex() sgx_wrapper_if_nameindex()
#define if_freenameindex(A) sgx_wrapper_if_freenameindex(A)

#endif