#ifndef SGX_PWD_U_H__
#define SGX_PWD_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_pwd_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

struct passwd* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getpwuid, (uid_t uid));
struct passwd* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getpwnam, (const char* name));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getpwnam_r, (const char* name, struct passwd* pwd, char* buf, size_t buflen, struct passwd** result));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
