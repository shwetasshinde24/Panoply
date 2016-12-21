#ifndef SGX_SYSMMAN_UTIL_H
#define SGX_SYSMMAN_UTIL_H

#include "proxy/sgx_sysmman_t.h"

static inline void *sgx_wrapper_mmap (void *__addr, size_t __len, int __prot, int __flags, int __fd, __off_t __offset)
{
	void* retval;
	ocall_mmap(&retval, __addr, __len, __prot, __flags, __fd, __offset);
	return retval;
}

static inline void *sgx_wrapper_mmap64 (void *__addr, size_t __len, int __prot, int __flags, int __fd, __off64_t __offset)
{
	void* retval;
	ocall_mmap64(&retval, __addr, __len, __prot, __flags, __fd, __offset);
	return retval;
}

static inline int sgx_wrapper_munmap (void *__addr, size_t __len)
{
	int retval;
	ocall_munmap(&retval, __addr, __len);
	return retval;
}

static inline int sgx_wrapper_mprotect (void *__addr, size_t __len, int __prot)
{
	int retval;
	ocall_mprotect(&retval, __addr, __len, __prot);
	return retval;
}

static inline int sgx_wrapper_msync (void *__addr, size_t __len, int __flags)
{
	int retval;
	ocall_msync(&retval, __addr, __len, __flags);
	return retval;
}

static inline int sgx_wrapper_mlock (const void *__addr, size_t __len)
{
	int retval;
	ocall_mlock(&retval, __addr, __len);
	return retval;
}

static inline int sgx_wrapper_munlock (const void *__addr, size_t __len)
{
	int retval;
	ocall_munlock(&retval, __addr, __len);
	return retval;
}

static inline int sgx_wrapper_mlockall (int __flags)
{
	int retval;
	ocall_mlockall(&retval, __flags);
	return retval;
}

static inline int sgx_wrapper_munlockall (void)
{
	int retval;
	ocall_munlockall(&retval);
	return retval;
}

static inline int sgx_wrapper_mincore (void *__start, size_t __len, unsigned char *__vec)
{
	int retval;
	ocall_mincore(&retval, __start, __len, __vec);
	return retval;
}

static inline int sgx_wrapper_shm_open (const char *__name, int __oflag, mode_t __mode)
{
	int retval;
	// fprintf(stderr, "Fix me: Dummy sgx_wrapper_shm_open call \n");
	ocall_shm_open(&retval, __name, __oflag, __mode);
	return retval;
}

static inline int sgx_wrapper_shm_unlink (const char *__name)
{
	int retval;
	// fprintf(stderr, "Fix me: Dummy sgx_wrapper_shm_open call \n");
	ocall_shm_unlink(&retval, __name);
	return retval;
}

#define mmap(A, B, C, D, E, F) sgx_wrapper_mmap(A, B, C, D, E, F)
#define mmap64(A, B, C, D, E, F) sgx_wrapper_mmap64(A, B, C, D, E, F)
#define munmap(A, B) sgx_wrapper_munmap(A, B)
#define mprotect(A, B, C) sgx_wrapper_mprotect(A, B, C)
#define msync(A, B, C) sgx_wrapper_msync(A, B, C)
#define mlock(A, B) sgx_wrapper_mlock(A, B)
#define munlock(A, B) sgx_wrapper_munlock(A, B)
#define mlockall(A) sgx_wrapper_mlockall(A)
#define munlockall() sgx_wrapper_munlockall()
#define mincore(A, B, C) sgx_wrapper_mincore(A, B, C)
#define shm_open(A, B, C) sgx_wrapper_shm_open(A, B, C)
#define shm_unlink(A) sgx_wrapper_shm_unlink(A)

#endif
