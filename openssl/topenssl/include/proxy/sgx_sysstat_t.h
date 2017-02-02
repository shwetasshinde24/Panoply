#ifndef SGX_SYSSTAT_T_H__
#define SGX_SYSSTAT_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "sgx/sys/types.h"
#include "sgx/sys/stat.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_stat(int* retval, const char* path, struct stat* buf);
sgx_status_t SGX_CDECL ocall_fstat(int* retval, int fd, struct stat* buf);
sgx_status_t SGX_CDECL ocall_lstat(int* retval, const char* path, struct stat* buf);
sgx_status_t SGX_CDECL ocall_chmod(int* retval, const char* file, mode_t mode);
sgx_status_t SGX_CDECL ocall_fchmod(int* retval, int fd, mode_t mode);
sgx_status_t SGX_CDECL ocall_fchmodat(int* retval, int fd, const char* file, mode_t mode, int flag);
sgx_status_t SGX_CDECL ocall_umask(mode_t* retval, mode_t mask);
sgx_status_t SGX_CDECL ocall_mkdir(int* retval, const char* path, mode_t mode);
sgx_status_t SGX_CDECL ocall_mkdirat(int* retval, int fd, const char* path, mode_t mode);
sgx_status_t SGX_CDECL ocall_mkfifo(int* retval, const char* path, mode_t mode);
sgx_status_t SGX_CDECL ocall_mkfifoat(int* retval, int fd, const char* path, mode_t mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
