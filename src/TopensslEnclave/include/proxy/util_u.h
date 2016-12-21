#ifndef UTIL_U_H__
#define UTIL_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "sgx_eid.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


sgx_status_t ecall_set_enclave_id(sgx_enclave_id_t eid, sgx_enclave_id_t self_eid);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
