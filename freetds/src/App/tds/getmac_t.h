#ifndef GETMAC_T_H__
#define GETMAC_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "freetds/tds_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL tds_getmac(TDS_SYS_SOCKET s, unsigned char mac[6]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
