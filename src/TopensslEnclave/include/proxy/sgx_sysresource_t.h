#ifndef SGX_SYSRESOURCE_T_H__
#define SGX_SYSRESOURCE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "struct/sgx_sysresource_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_prlimit(int* retval, __pid_t pid, enum __rlimit_resource resource, const struct rlimit* new_limit, struct rlimit* old_limit);
sgx_status_t SGX_CDECL ocall_getrlimit(int* retval, int resource, struct rlimit* rlim);
sgx_status_t SGX_CDECL ocall_setrlimit(int* retval, int resource, const struct rlimit* rlim);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
