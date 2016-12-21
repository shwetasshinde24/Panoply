#ifndef SGX_SYSUIO_T_H__
#define SGX_SYSUIO_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "sgx/sys/types.h"
#include "struct/sgx_sysuio_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_readv(ssize_t* retval, int __fd, const void* __iovec, int iovec_size, int __count);
sgx_status_t SGX_CDECL ocall_writev(ssize_t* retval, int __fd, int iovec_id, int iovec_size, int __count);
sgx_status_t SGX_CDECL ocall_init_multiple_iovec_outside(int* retval, const void* __iovec, int iovec_size, int __count);
sgx_status_t SGX_CDECL ocall_copy_base_to_outside(int iovec_id, int i, const void* base, int len);
sgx_status_t SGX_CDECL ocall_free_iovec_outside(int iovec_id, int iovec_size, int __count);
sgx_status_t SGX_CDECL ocall_process_vm_readv(ssize_t* retval, pid_t __pid, const struct iovec* __lvec, unsigned long int __liovcnt, const struct iovec* __rvec, unsigned long int __riovcnt, unsigned long int __flags);
sgx_status_t SGX_CDECL ocall_process_vm_writev(ssize_t* retval, pid_t __pid, const struct iovec* __lvec, unsigned long int __liovcnt, const struct iovec* __rvec, unsigned long int __riovcnt, unsigned long int __flags);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
