#ifndef SGX_PWD_T_H__
#define SGX_PWD_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "struct/sgx_pwd_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_getpwuid(struct passwd** retval, uid_t uid);
sgx_status_t SGX_CDECL ocall_getpwnam(struct passwd** retval, const char* name);
sgx_status_t SGX_CDECL ocall_getpwnam_r(int* retval, const char* name, struct passwd* pwd, char* buf, size_t buflen, struct passwd** result);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
