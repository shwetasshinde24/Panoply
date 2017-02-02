#ifndef SGX_SYSMMAN_UTIL_H
#define SGX_SYSMMAN_UTIL_H

#include "proxy/sgx_sysmman_t.h"

#ifdef __cplusplus
extern "C"	{
#endif 

extern void *sgx_wrapper_mmap (void *__addr, size_t __len, int __prot, int __flags, int __fd, __off_t __offset);
extern void *sgx_wrapper_mmap64 (void *__addr, size_t __len, int __prot, int __flags, int __fd, __off64_t __offset);
extern int sgx_wrapper_munmap (void *__addr, size_t __len);
extern int sgx_wrapper_mprotect (void *__addr, size_t __len, int __prot);
extern int sgx_wrapper_msync (void *__addr, size_t __len, int __flags);
extern int sgx_wrapper_mlock (const void *__addr, size_t __len);
extern int sgx_wrapper_munlock (const void *__addr, size_t __len);
extern int sgx_wrapper_mlockall (int __flags);
extern int sgx_wrapper_munlockall (void);
extern int sgx_wrapper_mincore (void *__start, size_t __len, unsigned char *__vec);
extern int sgx_wrapper_shm_open (const char *__name, int __oflag, mode_t __mode);
extern int sgx_wrapper_shm_unlink (const char *__name);

#ifdef __cplusplus
}
#endif 


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
