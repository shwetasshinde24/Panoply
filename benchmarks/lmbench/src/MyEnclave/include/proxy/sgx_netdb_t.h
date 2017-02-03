#ifndef SGX_NETDB_T_H__
#define SGX_NETDB_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "sgx/sys/types.h"
#include "struct/sgx_netdb_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_freeaddrinfo(void* res);
sgx_status_t SGX_CDECL ocall_getaddrinfo(int* retval, const char* node, const char* service, const void* hints, void** res);
sgx_status_t SGX_CDECL ocall_getaddrinfo1(int* retval, const char* node, const char* service, const void* hints, void* res);
sgx_status_t SGX_CDECL ocall_sethostent(int stay_open);
sgx_status_t SGX_CDECL ocall_endhostent();
sgx_status_t SGX_CDECL ocall_gethostent(struct hostent** retval);
sgx_status_t SGX_CDECL ocall_gethostbyaddr(struct hostent** retval, const void* addr, socklen_t len, int type);
sgx_status_t SGX_CDECL ocall_gethostbyname(struct hostent** retval, const char* name);
sgx_status_t SGX_CDECL ocall_setnetent(int stay_open);
sgx_status_t SGX_CDECL ocall_endnetent();
sgx_status_t SGX_CDECL ocall_getnetent(struct netent** retval);
sgx_status_t SGX_CDECL ocall_getnetbyaddr(struct netent** retval, uint32_t net, int type);
sgx_status_t SGX_CDECL ocall_getnetbyname(struct netent** retval, const char* name);
sgx_status_t SGX_CDECL ocall_setservent(int stay_open);
sgx_status_t SGX_CDECL ocall_endservent();
sgx_status_t SGX_CDECL ocall_getservent(struct servent** retval);
sgx_status_t SGX_CDECL ocall_getservbyname(struct servent** retval, const char* name, const char* proto);
sgx_status_t SGX_CDECL ocall_getservbyport(struct servent** retval, int port, const char* proto);
sgx_status_t SGX_CDECL ocall_setprotoent(int stay_open);
sgx_status_t SGX_CDECL ocall_endprotoent();
sgx_status_t SGX_CDECL ocall_getprotoent(struct protoent** retval);
sgx_status_t SGX_CDECL ocall_getprotobyname(struct protoent** retval, const char* name);
sgx_status_t SGX_CDECL ocall_getprotobynumber(struct protoent** retval, int proto);
sgx_status_t SGX_CDECL ocall_gai_strerror(char** retval, int ecode);
sgx_status_t SGX_CDECL ocall_getnameinfo(int* retval, const struct sockaddr* sa, socklen_t salen, char* host, socklen_t hostlen, char* serv, socklen_t servlen, int flags);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
