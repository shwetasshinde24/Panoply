#ifndef SGX_ARPAINET_T_H__
#define SGX_ARPAINET_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "struct/sgx_arpainet_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_inet_addr(in_addr_t* retval, const char* cp);
sgx_status_t SGX_CDECL ocall_inet_lnaof(in_addr_t* retval, struct in_addr in);
sgx_status_t SGX_CDECL ocall_inet_makeaddr(struct in_addr* retval, in_addr_t net, in_addr_t host);
sgx_status_t SGX_CDECL ocall_inet_netof(in_addr_t* retval, struct in_addr in);
sgx_status_t SGX_CDECL ocall_inet_network(in_addr_t* retval, const char* cp);
sgx_status_t SGX_CDECL ocall_inet_ntoa(char** retval, struct in_addr in);
sgx_status_t SGX_CDECL ocall_inet_pton(int* retval, int af, const char* cp, void* buf);
sgx_status_t SGX_CDECL ocall_inet_ntop(char** retval, int af, const void* cp, char* buf, socklen_t len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
