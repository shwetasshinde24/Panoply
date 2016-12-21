#ifndef SGX_DIRENT_T_H__
#define SGX_DIRENT_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "struct/sgx_dirent_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_opendir(void** retval, const char* name);
sgx_status_t SGX_CDECL ocall_fdopendir(void** retval, int fd);
sgx_status_t SGX_CDECL ocall_closedir(int* retval, void* dirp);
sgx_status_t SGX_CDECL ocall_readdir(struct dirent** retval, void* dirp);
sgx_status_t SGX_CDECL ocall_readdir_r(int* retval, void* dirp, struct dirent* entry, struct dirent** result);
sgx_status_t SGX_CDECL ocall_rewinddir(void* dirp);
sgx_status_t SGX_CDECL ocall_seekdir(void* dirp, long int pos);
sgx_status_t SGX_CDECL ocall_telldir(long int* retval, void* dirp);
sgx_status_t SGX_CDECL ocall_dirfd(int* retval, void* dirp);
sgx_status_t SGX_CDECL ocall_alphasort(int* retval, const struct dirent** e1, const struct dirent** e2);
sgx_status_t SGX_CDECL ocall_getdirentries(ssize_t* retval, int fd, char* buf, size_t nbytes, off_t* basep);
sgx_status_t SGX_CDECL ocall_versionsort(int* retval, const struct dirent** e1, const struct dirent** e2);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
