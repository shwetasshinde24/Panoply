#ifndef SGX_SYSWAIT_U_H__
#define SGX_SYSWAIT_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_syswait_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

__pid_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_waitpid, (__pid_t __pid, int* __stat_loc, int __options));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_waitid, (idtype_t __idtype, __id_t __id, siginfo_t* __infop, int __options));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
