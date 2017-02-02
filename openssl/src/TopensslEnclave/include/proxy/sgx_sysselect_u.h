#ifndef SGX_SYSSELECT_U_H__
#define SGX_SYSSELECT_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_sysselect_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_select, (int __nfds, fd_set* __readfds, fd_set* __writefds, fd_set* __exceptfds, struct timeval* __timeout));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
