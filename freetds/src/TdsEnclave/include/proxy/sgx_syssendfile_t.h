#ifndef SGX_SYSSENDFILE_T_H__
#define SGX_SYSSENDFILE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "sgx/sys/types.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_sendfile(ssize_t* retval, int out_fd, int in_fd, off_t* offset, size_t count);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
