#ifndef SGX_SYSMMAN_U_H__
#define SGX_SYSMMAN_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "sgx/sys/types.h"
#include "struct/sgx_sysmman_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mmap, (void* __addr, size_t __len, int __prot, int __flags, int __fd, __off_t __offset));
void* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mmap64, (void* __addr, size_t __len, int __prot, int __flags, int __fd, __off64_t __offset));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_munmap, (void* __addr, size_t __len));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mprotect, (void* __addr, size_t __len, int __prot));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_msync, (void* __addr, size_t __len, int __flags));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mlock, (const void* __addr, size_t __len));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_munlock, (const void* __addr, size_t __len));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mlockall, (int __flags));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_munlockall, ());
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mincore, (void* __start, size_t __len, unsigned char* __vec));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_shm_open, (const char* __name, int __oflag, mode_t __mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_shm_unlink, (const char* __name));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
