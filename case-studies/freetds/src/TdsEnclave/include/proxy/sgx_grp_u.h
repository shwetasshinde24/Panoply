#ifndef SGX_GRP_U_H__
#define SGX_GRP_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_grp_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

struct group* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getgrgid, (gid_t gid));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_initgroups, (const char* user, gid_t group));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
