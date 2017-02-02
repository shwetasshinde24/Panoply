#ifndef NET_U_H__
#define NET_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

char* SGX_UBRIDGE(SGX_NOCONVENTION, wrapper_tds_addrinfo2str, (void* addr, char* name, int namemax));
int SGX_UBRIDGE(SGX_NOCONVENTION, wrapper_tds_socket_set_nonblocking, (int sock));
int SGX_UBRIDGE(SGX_NOCONVENTION, wrapper_setsockopt, (int sockfd, int level, int optname, const void* optval, unsigned int optlen));
int SGX_UBRIDGE(SGX_NOCONVENTION, wrapper_connect, (int socket, void* address, unsigned int address_len));
int SGX_UBRIDGE(SGX_NOCONVENTION, wrapper_close, (int sock));
int SGX_UBRIDGE(SGX_NOCONVENTION, wrapper_recv, (int sockfd, void* buf, size_t len, int flags));
int SGX_UBRIDGE(SGX_NOCONVENTION, wrapper_send, (int sockfd, const void* buf, size_t len, int flags));
int SGX_UBRIDGE(SGX_NOCONVENTION, wrapper_socket, (int domain, int type, int protocol));
int SGX_UBRIDGE(SGX_NOCONVENTION, wrapper_accept, (int sockfd, void* addr, unsigned int* addrlen));
int SGX_UBRIDGE(SGX_NOCONVENTION, wrapper_eventfd, (unsigned int initval, int flags));
int SGX_UBRIDGE(SGX_NOCONVENTION, wrapper_socketpair, (int domain, int type, int protocol, int sv[2]));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_poll, (void* fds, unsigned int nfds, int timeout));
unsigned short int SGX_UBRIDGE(SGX_NOCONVENTION, wrapper_htons, (unsigned short int port));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
