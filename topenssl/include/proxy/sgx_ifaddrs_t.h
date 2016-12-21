#ifndef SGX_IFADDRS_T_H__
#define SGX_IFADDRS_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "struct/sgx_ifaddrs_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_getifaddrs(int* retval, struct ifaddrs** ifap);
sgx_status_t SGX_CDECL ocall_freeifaddrs(struct ifaddrs* ifa);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
