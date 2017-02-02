#ifndef GETMAC_U_H__
#define GETMAC_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "freetds/tds_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void SGX_UBRIDGE(SGX_NOCONVENTION, tds_getmac, (TDS_SYS_SOCKET s, unsigned char mac[6]));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
