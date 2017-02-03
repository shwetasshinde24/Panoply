#ifndef SGX_SYSSENDFILE_U_H__
#define SGX_SYSSENDFILE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "sgx/sys/types.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sendfile, (int out_fd, int in_fd, off_t* offset, size_t count));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
