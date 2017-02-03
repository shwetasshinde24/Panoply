#ifndef SGX_GRP_T_H__
#define SGX_GRP_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "struct/sgx_grp_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_getgrgid(struct group** retval, gid_t gid);
sgx_status_t SGX_CDECL ocall_initgroups(int* retval, const char* user, gid_t group);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
