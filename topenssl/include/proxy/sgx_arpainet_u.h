#ifndef SGX_ARPAINET_U_H__
#define SGX_ARPAINET_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_arpainet_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

in_addr_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_inet_addr, (const char* cp));
in_addr_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_inet_lnaof, (struct in_addr in));
struct in_addr SGX_UBRIDGE(SGX_NOCONVENTION, ocall_inet_makeaddr, (in_addr_t net, in_addr_t host));
in_addr_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_inet_netof, (struct in_addr in));
in_addr_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_inet_network, (const char* cp));
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_inet_ntoa, (struct in_addr in));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_inet_pton, (int af, const char* cp, void* buf));
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_inet_ntop, (int af, const void* cp, char* buf, socklen_t len));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
