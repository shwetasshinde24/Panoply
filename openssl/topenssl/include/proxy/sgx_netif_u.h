#ifndef SGX_NETIF_U_H__
#define SGX_NETIF_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_netif_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

unsigned int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_if_nametoindex, (const char* ifname));
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_if_indextoname, (unsigned int ifindex, char* ifname));
struct if_nameindex* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_if_nameindex, ());
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_if_freenameindex, (struct if_nameindex* ptr));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
