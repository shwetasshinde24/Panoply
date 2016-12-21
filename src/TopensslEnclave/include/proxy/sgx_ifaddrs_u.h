#ifndef SGX_IFADDRS_U_H__
#define SGX_IFADDRS_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_ifaddrs_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getifaddrs, (struct ifaddrs** ifap));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_freeifaddrs, (struct ifaddrs* ifa));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
