#ifndef SGX_NETINETIN_U_H__
#define SGX_NETINETIN_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_netinetin_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

uint32_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_ntohl, (uint32_t netlong));
uint16_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_ntohs, (uint16_t netshort));
uint32_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_htonl, (uint32_t hostlong));
uint16_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_htons, (uint16_t hostshort));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
