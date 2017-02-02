#ifndef SGX_NETINETIN_T_H__
#define SGX_NETINETIN_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "struct/sgx_netinetin_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_ntohl(uint32_t* retval, uint32_t netlong);
sgx_status_t SGX_CDECL ocall_ntohs(uint16_t* retval, uint16_t netshort);
sgx_status_t SGX_CDECL ocall_htonl(uint32_t* retval, uint32_t hostlong);
sgx_status_t SGX_CDECL ocall_htons(uint16_t* retval, uint16_t hostshort);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
