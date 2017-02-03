#ifndef SGX_DIRENT_UTIL_H
#define SGX_DIRENT_UTIL_H

#include "struct/sgx_dirent_struct.h"
#include "sgx/sys/types.h"
#include "proxy/sgx_dirent_t.h"

#ifdef __cplusplus
extern "C"	{
#endif
	
extern void *sgx_wrapper_opendir (const char *name);
extern void *sgx_wrapper_fdopendir (int fd);
extern int sgx_wrapper_closedir (void *dirp_cast);
extern struct dirent *sgx_wrapper_readdir (void *dirp_cast);
extern int sgx_wrapper_readdir_r (void *dirp_cast, struct dirent *entry, struct dirent **result);
extern void sgx_wrapper_rewinddir (void *dirp_cast);
extern void sgx_wrapper_seekdir (void *dirp_cast, long int pos);
extern long int sgx_wrapper_telldir ( void *dirp_cast);
extern int sgx_wrapper_dirfd ( void *dirp_cast);
extern int sgx_wrapper_alphasort ( const struct dirent **e1,  const struct dirent **e2);
extern ssize_t sgx_wrapper_getdirentries (int fd, char *buf, size_t nbytes, off_t *basep);
extern int sgx_wrapper_versionsort (const struct dirent **e1,  const struct dirent **e2);

#ifdef __cplusplus
}
#endif


#define opendir(A) sgx_wrapper_opendir(A)
#define closedir(A) sgx_wrapper_closedir(A)
#define fdopendir(A) sgx_wrapper_fdopendir(A)
#define readdir(A) sgx_wrapper_readdir(A)
#define readdir_r(A, B, C) sgx_wrapper_readdir_r(A, B, C)
#define rewinddir(A) sgx_wrapper_rewinddir(A)
#define seekdir(A) sgx_wrapper_seekdir(A)
#define telldir(A) sgx_wrapper_telldir(A)
#define dirfd(A) sgx_wrapper_dirfd(A)
#define alphasort(A, B) sgx_wrapper_alphasort(A, B)
#define getdirentries(A, B, C) sgx_wrapper_getdirentries(A, B, C)
#define versionsort(A, B) sgx_wrapper_versionsort(A, B)

#endif