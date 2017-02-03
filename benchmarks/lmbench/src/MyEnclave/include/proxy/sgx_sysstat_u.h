#ifndef SGX_SYSSTAT_U_H__
#define SGX_SYSSTAT_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "sgx/sys/types.h"
#include "sgx/sys/stat.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_stat, (const char* path, struct stat* buf));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fstat, (int fd, struct stat* buf));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_lstat, (const char* path, struct stat* buf));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_chmod, (const char* file, mode_t mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fchmod, (int fd, mode_t mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fchmodat, (int fd, const char* file, mode_t mode, int flag));
mode_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_umask, (mode_t mask));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mkdir, (const char* path, mode_t mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mkdirat, (int fd, const char* path, mode_t mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mkfifo, (const char* path, mode_t mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mkfifoat, (int fd, const char* path, mode_t mode));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
