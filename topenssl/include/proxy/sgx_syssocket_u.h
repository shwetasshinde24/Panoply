#ifndef SGX_SYSSOCKET_U_H__
#define SGX_SYSSOCKET_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "sgx/sys/types.h"
#include "struct/sgx_syssocket_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_socket, (int domain, int type, int protocol));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_accept, (int sockfd, struct sockaddr* addr, socklen_t* addrlen));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_connect, (int socket, const struct sockaddr* address, socklen_t address_len));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sendto, (int sockfd, const void* buf, size_t len, int flags, const void* dest_addr, unsigned int addrlen));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_recv, (int fd, void* buf, size_t len, int flags));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_send, (int fd, const void* buf, size_t len, int flags));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_socketpair, (int domain, int type, int protocol, int sv[2]));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_setsockopt, (int sockfd, int level, int optname, const void* optval, unsigned int optlen));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getsockopt, (int sockfd, int level, int optname, void* optval, unsigned int* optlen));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_shutdown, (int fd, int how));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_bind, (int fd, const struct sockaddr* addr, socklen_t len));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_listen, (int fd, int n));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getsockname, (int fd, struct sockaddr* addr, socklen_t* len));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getpeername, (int fd, struct sockaddr* addr, socklen_t* len));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_recvfrom, (int fd, void* buf, size_t n, int flags, struct sockaddr* addr, socklen_t* addr_len));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sendmsg, (int fd, const struct msghdr* message, int flags));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_recvmsg, (int fd, struct msghdr* message, int flags));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
