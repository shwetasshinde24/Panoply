#ifndef SGX_NETIF_T_H__
#define SGX_NETIF_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "struct/sgx_netif_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_if_nametoindex(unsigned int* retval, const char* ifname);
sgx_status_t SGX_CDECL ocall_if_indextoname(char** retval, unsigned int ifindex, char* ifname);
sgx_status_t SGX_CDECL ocall_if_nameindex(struct if_nameindex** retval);
sgx_status_t SGX_CDECL ocall_if_freenameindex(struct if_nameindex* ptr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
