#ifndef SGX_DIRENT_UTIL_H
#define SGX_DIRENT_UTIL_H

#include "struct/sgx_dirent_struct.h"
#include "sgx/sys/types.h"
#include "proxy/sgx_dirent_t.h"

static inline void *sgx_wrapper_opendir (const char *name)
{
	void *retval;
	ocall_opendir(&retval, name);
	return retval;
}

static inline void *sgx_wrapper_fdopendir (int fd)
{
	void *retval;
	ocall_fdopendir(&retval, fd);
	return retval;
}

static inline int sgx_wrapper_closedir (void *dirp_cast)
{
	int retval;
	ocall_closedir(&retval, dirp_cast);
	return retval;
}

static inline struct dirent *sgx_wrapper_readdir (void *dirp_cast)
{
	struct dirent *retval;
	ocall_readdir(&retval, dirp_cast);
	return retval;
}

static inline int sgx_wrapper_readdir_r (void *dirp_cast, struct dirent *entry, struct dirent **result)
{
	int retval;
	ocall_readdir_r(&retval, dirp_cast, entry, result);
	return retval;
}

static inline void sgx_wrapper_rewinddir (void *dirp_cast)
{
	ocall_rewinddir(dirp_cast);
}

static inline void sgx_wrapper_seekdir (void *dirp_cast, long int pos)
{
	ocall_seekdir(dirp_cast, pos);
}

static inline long int sgx_wrapper_telldir ( void *dirp_cast)
{
	long int retval;
	ocall_telldir(&retval, dirp_cast);
	return retval;
}

static inline int sgx_wrapper_dirfd ( void *dirp_cast)
{
	int retval;
	ocall_dirfd(&retval, dirp_cast);
	return retval;
}

static inline int sgx_wrapper_alphasort ( const struct dirent **e1,  const struct dirent **e2)
{
	int retval;
	ocall_alphasort(&retval, e1, e2);
	return retval;
}

static inline ssize_t sgx_wrapper_getdirentries (int fd, char *buf, size_t nbytes, off_t *basep)
{
	ssize_t retval;
	ocall_getdirentries(&retval,fd, buf, nbytes, basep);
	return retval;
}

static inline int sgx_wrapper_versionsort (const struct dirent **e1,  const struct dirent **e2)
{
	int retval;
	ocall_versionsort(&retval,e1, e2);
	return retval;
}

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