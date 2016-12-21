#ifndef SGX_POLL_U_H__
#define SGX_POLL_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_poll_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_poll, (struct pollfd* __fds, nfds_t __nfds, int __timeout));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
