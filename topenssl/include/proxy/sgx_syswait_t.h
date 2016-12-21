#ifndef SGX_SYSWAIT_T_H__
#define SGX_SYSWAIT_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "struct/sgx_syswait_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_waitpid(__pid_t* retval, __pid_t __pid, int* __stat_loc, int __options);
sgx_status_t SGX_CDECL ocall_waitid(int* retval, idtype_t __idtype, __id_t __id, siginfo_t* __infop, int __options);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
