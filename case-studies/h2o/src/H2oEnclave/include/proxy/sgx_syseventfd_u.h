#ifndef SGX_SYSEVENTFD_U_H__
#define SGX_SYSEVENTFD_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_syseventfd_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_eventfd, (unsigned int initval, int flags));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
