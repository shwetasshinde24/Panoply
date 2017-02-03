#ifndef SGX_SYSUIO_UTIL_H
#define SGX_SYSUIO_UTIL_H

#include "proxy/sgx_sysuio_t.h"

#ifdef __cplusplus
extern "C"	{
#endif 

extern ssize_t sgx_wrapper_readv (int __fd, const struct iovec *__iovec, int __count);
extern ssize_t sgx_wrapper_writev (int __fd, const struct iovec *__iovec, int __count);
extern ssize_t sgx_wrapper_process_vm_readv (pid_t __pid, const struct iovec *__lvec, unsigned long int __liovcnt, 
	const struct iovec *__rvec, unsigned long int __riovcnt, unsigned long int __flags);
extern ssize_t sgx_wrapper_process_vm_writev (pid_t __pid, const struct iovec *__lvec, unsigned long int __liovcnt,
	const struct iovec *__rvec, unsigned long int __riovcnt, unsigned long int __flags);

#ifdef __cplusplus
}
#endif 

#define readv(A, B, C) sgx_wrapper_readv(A, B, C)
#define writev(A, B, C) sgx_wrapper_writev(A, B, C)
#define process_vm_readv(A, B, C, D, E, F) sgx_wrapper_process_vm_readv(A, B, C, D, E, F)
#define process_vm_writev(A, B, C, D, E, F) sgx_wrapper_process_vm_writev(A, B, C, D, E, F)

#endif
