#ifndef SGX_SYSUIO_U_H__
#define SGX_SYSUIO_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "sgx/sys/types.h"
#include "struct/sgx_sysuio_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_readv, (int __fd, const struct iovec* __iovec, int __count));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_writev, (int __fd, const struct iovec* __iovec, int __count));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_process_vm_readv, (pid_t __pid, const struct iovec* __lvec, unsigned long int __liovcnt, const struct iovec* __rvec, unsigned long int __riovcnt, unsigned long int __flags));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_process_vm_writev, (pid_t __pid, const struct iovec* __lvec, unsigned long int __liovcnt, const struct iovec* __rvec, unsigned long int __riovcnt, unsigned long int __flags));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
