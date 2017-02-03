#ifndef SGX_SYSSOCKET_T_H__
#define SGX_SYSSOCKET_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "sgx/sys/types.h"
#include "struct/sgx_syssocket_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_socket(int* retval, int domain, int type, int protocol);
sgx_status_t SGX_CDECL ocall_accept(int* retval, int sockfd, struct sockaddr* addr, socklen_t* addrlen);
sgx_status_t SGX_CDECL ocall_connect(int* retval, int socket, const struct sockaddr* address, socklen_t address_len);
sgx_status_t SGX_CDECL ocall_sendto(ssize_t* retval, int sockfd, const void* buf, size_t len, int flags, const void* dest_addr, unsigned int addrlen);
sgx_status_t SGX_CDECL ocall_recv(ssize_t* retval, int fd, void* buf, size_t len, int flags);
sgx_status_t SGX_CDECL ocall_send(ssize_t* retval, int fd, const void* buf, size_t len, int flags);
sgx_status_t SGX_CDECL ocall_socketpair(int* retval, int domain, int type, int protocol, int sv[2]);
sgx_status_t SGX_CDECL ocall_setsockopt(int* retval, int sockfd, int level, int optname, const void* optval, unsigned int optlen);
sgx_status_t SGX_CDECL ocall_getsockopt(int* retval, int sockfd, int level, int optname, void* optval, unsigned int* optlen);
sgx_status_t SGX_CDECL ocall_shutdown(int* retval, int fd, int how);
sgx_status_t SGX_CDECL ocall_bind(int* retval, int fd, const struct sockaddr* addr, socklen_t len);
sgx_status_t SGX_CDECL ocall_listen(int* retval, int fd, int n);
sgx_status_t SGX_CDECL ocall_getsockname(int* retval, int fd, struct sockaddr* addr, socklen_t* len);
sgx_status_t SGX_CDECL ocall_getpeername(int* retval, int fd, struct sockaddr* addr, socklen_t* len);
sgx_status_t SGX_CDECL ocall_recvfrom(ssize_t* retval, int fd, void* buf, size_t n, int flags, struct sockaddr* addr, socklen_t* addr_len);
sgx_status_t SGX_CDECL ocall_sendmsg(ssize_t* retval, int fd, const struct msghdr* message, int flags);
sgx_status_t SGX_CDECL ocall_recvmsg(ssize_t* retval, int fd, struct msghdr* message, int flags);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
