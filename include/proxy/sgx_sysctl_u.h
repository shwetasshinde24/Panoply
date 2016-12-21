#ifndef SGX_SYSCTL_U_H__
#define SGX_SYSCTL_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "sgx/sys/types.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sysctl, (int* name, int nlen, void* oldval, size_t* oldlenp, void* newval, size_t newlen));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
