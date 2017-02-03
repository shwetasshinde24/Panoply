#ifndef SGX_SYSRESOURCE_U_H__
#define SGX_SYSRESOURCE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_sysresource_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_prlimit, (__pid_t pid, enum __rlimit_resource resource, const struct rlimit* new_limit, struct rlimit* old_limit));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getrlimit, (int resource, struct rlimit* rlim));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_setrlimit, (int resource, const struct rlimit* rlim));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
