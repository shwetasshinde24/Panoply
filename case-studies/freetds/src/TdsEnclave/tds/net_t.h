#ifndef NET_T_H__
#define NET_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL wrapper_tds_addrinfo2str(char** retval, void* addr, char* name, int namemax);
sgx_status_t SGX_CDECL wrapper_tds_socket_set_nonblocking(int* retval, int sock);
sgx_status_t SGX_CDECL wrapper_setsockopt(int* retval, int sockfd, int level, int optname, const void* optval, unsigned int optlen);
sgx_status_t SGX_CDECL wrapper_connect(int* retval, int socket, void* address, unsigned int address_len);
sgx_status_t SGX_CDECL wrapper_close(int* retval, int sock);
sgx_status_t SGX_CDECL wrapper_recv(int* retval, int sockfd, void* buf, size_t len, int flags);
sgx_status_t SGX_CDECL wrapper_send(int* retval, int sockfd, const void* buf, size_t len, int flags);
sgx_status_t SGX_CDECL wrapper_socket(int* retval, int domain, int type, int protocol);
sgx_status_t SGX_CDECL wrapper_accept(int* retval, int sockfd, void* addr, unsigned int* addrlen);
sgx_status_t SGX_CDECL wrapper_eventfd(int* retval, unsigned int initval, int flags);
sgx_status_t SGX_CDECL wrapper_socketpair(int* retval, int domain, int type, int protocol, int sv[2]);
sgx_status_t SGX_CDECL ocall_poll(int* retval, void* fds, unsigned int nfds, int timeout);
sgx_status_t SGX_CDECL wrapper_htons(unsigned short int* retval, unsigned short int port);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
