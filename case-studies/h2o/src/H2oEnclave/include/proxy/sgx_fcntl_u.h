#ifndef SGX_FCNTL_U_H__
#define SGX_FCNTL_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_open1, (const char* pathname, int flags));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_open2, (const char* pathname, int flags, unsigned int mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_creat, (const char* pathname, unsigned int mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_openat1, (int dirfd, const char* pathname, int flags));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_openat2, (int dirfd, const char* pathname, int flags, unsigned int mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fcntl1, (int fd, int cmd));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fcntl2, (int fd, int cmd, long int arg));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fcntl3, (int fd, int cmd, void* arg, int flock_size));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
