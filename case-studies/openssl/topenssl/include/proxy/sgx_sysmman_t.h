#ifndef SGX_SYSMMAN_T_H__
#define SGX_SYSMMAN_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "sgx/sys/types.h"
#include "struct/sgx_sysmman_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_mmap(void** retval, void* __addr, size_t __len, int __prot, int __flags, int __fd, __off_t __offset);
sgx_status_t SGX_CDECL ocall_mmap64(void** retval, void* __addr, size_t __len, int __prot, int __flags, int __fd, __off64_t __offset);
sgx_status_t SGX_CDECL ocall_munmap(int* retval, void* __addr, size_t __len);
sgx_status_t SGX_CDECL ocall_mprotect(int* retval, void* __addr, size_t __len, int __prot);
sgx_status_t SGX_CDECL ocall_msync(int* retval, void* __addr, size_t __len, int __flags);
sgx_status_t SGX_CDECL ocall_mlock(int* retval, const void* __addr, size_t __len);
sgx_status_t SGX_CDECL ocall_munlock(int* retval, const void* __addr, size_t __len);
sgx_status_t SGX_CDECL ocall_mlockall(int* retval, int __flags);
sgx_status_t SGX_CDECL ocall_munlockall(int* retval);
sgx_status_t SGX_CDECL ocall_mincore(int* retval, void* __start, size_t __len, unsigned char* __vec);
sgx_status_t SGX_CDECL ocall_shm_open(int* retval, const char* __name, int __oflag, mode_t __mode);
sgx_status_t SGX_CDECL ocall_shm_unlink(int* retval, const char* __name);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
