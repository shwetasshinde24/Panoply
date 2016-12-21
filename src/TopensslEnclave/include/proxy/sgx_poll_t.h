#ifndef SGX_POLL_T_H__
#define SGX_POLL_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "struct/sgx_poll_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_poll(int* retval, struct pollfd* __fds, nfds_t __nfds, int __timeout);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
