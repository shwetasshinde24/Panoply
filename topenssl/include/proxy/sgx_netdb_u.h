#ifndef SGX_NETDB_U_H__
#define SGX_NETDB_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "sgx/sys/types.h"
#include "struct/sgx_netdb_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_freeaddrinfo, (void* res));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getaddrinfo, (const char* node, const char* service, const void* hints, void** res));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getaddrinfo1, (const char* node, const char* service, const void* hints, void* res));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sethostent, (int stay_open));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_endhostent, ());
struct hostent* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_gethostent, ());
struct hostent* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_gethostbyaddr, (const void* addr, socklen_t len, int type));
struct hostent* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_gethostbyname, (const char* name));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_setnetent, (int stay_open));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_endnetent, ());
struct netent* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getnetent, ());
struct netent* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getnetbyaddr, (uint32_t net, int type));
struct netent* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getnetbyname, (const char* name));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_setservent, (int stay_open));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_endservent, ());
struct servent* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getservent, ());
struct servent* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getservbyname, (const char* name, const char* proto));
struct servent* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getservbyport, (int port, const char* proto));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_setprotoent, (int stay_open));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_endprotoent, ());
struct protoent* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getprotoent, ());
struct protoent* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getprotobyname, (const char* name));
struct protoent* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getprotobynumber, (int proto));
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_gai_strerror, (int ecode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getnameinfo, (const struct sockaddr* sa, socklen_t salen, char* host, socklen_t hostlen, char* serv, socklen_t servlen, int flags));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
