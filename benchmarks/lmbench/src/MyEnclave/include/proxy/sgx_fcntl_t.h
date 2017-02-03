#ifndef SGX_FCNTL_T_H__
#define SGX_FCNTL_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_open1(int* retval, const char* pathname, int flags);
sgx_status_t SGX_CDECL ocall_open2(int* retval, const char* pathname, int flags, unsigned int mode);
sgx_status_t SGX_CDECL ocall_creat(int* retval, const char* pathname, unsigned int mode);
sgx_status_t SGX_CDECL ocall_openat1(int* retval, int dirfd, const char* pathname, int flags);
sgx_status_t SGX_CDECL ocall_openat2(int* retval, int dirfd, const char* pathname, int flags, unsigned int mode);
sgx_status_t SGX_CDECL ocall_fcntl1(int* retval, int fd, int cmd);
sgx_status_t SGX_CDECL ocall_fcntl2(int* retval, int fd, int cmd, long int arg);
sgx_status_t SGX_CDECL ocall_fcntl3(int* retval, int fd, int cmd, void* arg, int flock_size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
