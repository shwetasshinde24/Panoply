#ifndef SGX_SYSSOCKET_UTIL_H
#define SGX_SYSSOCKET_UTIL_H

#include "struct/sgx_syssocket_struct.h"
#include "proxy/sgx_syssocket_t.h"

#ifdef __cplusplus
extern "C"	{
#endif 

extern int sgx_wrapper_shutdown(int fd, int how);
extern ssize_t sgx_wrapper_recv(int fd, void *buf, size_t len, int flags);
extern ssize_t sgx_wrapper_send(int fd, const void *buf, size_t len, int flags);
extern int sgx_wrapper_connect(int soc, const struct sockaddr *address, socklen_t address_len);
extern int sgx_wrapper_socket(int domain, int type, int protocol);
extern int sgx_wrapper_accept(int sockfd, struct sockaddr *address, socklen_t *addrlen);
extern ssize_t sgx_wrapper_sendto(int sockfd, const void *buf, size_t len, int flags, const void *dest_addr_cast, unsigned int addrlen);
extern int sgx_wrapper_socketpair(int domain, int type, int protocol, int sv[2]);
extern int sgx_wrapper_setsockopt(int sockfd, int level, int optname, const void *optval, unsigned int optlen);
extern int sgx_wrapper_getsockopt(int sockfd, int level, int optname, void *optval, unsigned int *optlen);
extern int sgx_wrapper_bind(int sockfd, const struct sockaddr * address, socklen_t addrlen);
extern int sgx_wrapper_listen(int fd, int n);
extern int sgx_wrapper_getsockname(int fd, struct sockaddr * addr, socklen_t *len);
extern int sgx_wrapper_getpeername(int fd, struct sockaddr * addr, socklen_t *len);
extern ssize_t sgx_wrapper_recvfrom(int fd, void *buf, size_t n, int flags, struct sockaddr * addr, socklen_t *addr_len);
extern ssize_t sgx_wrapper_sendmsg(int fd, const struct msghdr *message, int flags);
extern ssize_t sgx_wrapper_recvmsg(int fd, struct msghdr *message, int flags);

#ifdef __cplusplus
}
#endif 

#define shutdown(A, B) sgx_wrapper_shutdown(A,B)
#define recv(A, B, C, D) sgx_wrapper_recv(A, B, C, D)
#define send(A, B, C, D) sgx_wrapper_send(A, B, C, D)
#define connect(A, B, C) sgx_wrapper_connect(A, B, C)
#define socket(A, B, C) sgx_wrapper_socket(A, B, C)
#define accept(A, B, C) sgx_wrapper_accept(A, B, C)
#define sendto(A, B, C, D, E, F) sgx_wrapper_sendto(A, B, C, D, E, F)
#define recvfrom(A, B, C, D, E, F) sgx_wrapper_recvfrom(A, B, C, D, E, F)
#define socketpair(A, B, C, D) sgx_wrapper_socketpair(A, B, C, D)
#define setsockopt(A, B, C, D, E) sgx_wrapper_setsockopt(A, B, C, D, E)
#define getsockopt(A, B, C, D, E) sgx_wrapper_getsockopt(A, B, C, D, E)
#define bind(A, B, C) sgx_wrapper_bind(A, B, C)
#define listen(A, B) sgx_wrapper_listen(A, B)
#define getsockname(A, B, C) sgx_wrapper_getsockname(A, B, C)
#define getpeername(A, B, C) sgx_wrapper_getpeername(A, B, C)
#define sendmsg(A, B, C) sgx_wrapper_sendmsg(A, B, C)
#define recvmsg(A, B, C) sgx_wrapper_recvmsg(A, B, C)

#endif

