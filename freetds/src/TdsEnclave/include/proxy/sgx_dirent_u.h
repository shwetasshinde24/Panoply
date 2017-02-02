#ifndef SGX_DIRENT_U_H__
#define SGX_DIRENT_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_dirent_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_opendir, (const char* name));
void* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fdopendir, (int fd));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_closedir, (void* dirp));
struct dirent* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_readdir, (void* dirp));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_readdir_r, (void* dirp, struct dirent* entry, struct dirent** result));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_rewinddir, (void* dirp));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_seekdir, (void* dirp, long int pos));
long int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_telldir, (void* dirp));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_dirfd, (void* dirp));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_alphasort, (const struct dirent** e1, const struct dirent** e2));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getdirentries, (int fd, char* buf, size_t nbytes, off_t* basep));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_versionsort, (const struct dirent** e1, const struct dirent** e2));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
