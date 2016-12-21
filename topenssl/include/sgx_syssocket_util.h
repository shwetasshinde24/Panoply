#ifndef SGX_SYSSOCKET_UTIL_H
#define SGX_SYSSOCKET_UTIL_H

#include "struct/sgx_syssocket_struct.h"
#include "proxy/sgx_syssocket_t.h"
#include <sgx_stdio_util.h>
#include <string.h>
#include "sgx_trts.h"
#include "sgx_status.h"

static inline int sgx_wrapper_shutdown(int fd, int how)
{
	int retval;
	ocall_shutdown(&retval, fd, how);
	return retval;
}
static inline ssize_t sgx_wrapper_recv(int fd, void *buf, size_t len, int flags)
{
	ssize_t retval;
	ocall_recv(&retval, fd, buf, len, flags);
	return retval;
}
static inline ssize_t sgx_wrapper_send(int fd, const void *buf, size_t len, int flags)
{
	ssize_t retval;
	ocall_send(&retval, fd, buf, len, flags);
	return retval;
}  

static inline int sgx_wrapper_connect(int soc, const struct sockaddr *address, socklen_t address_len)
{
	// printf("Call sgx_wrapper_connect: %d \n", soc);
	int retval = -1;
	sgx_status_t status;

	if (!sgx_is_within_enclave(address, sizeof(struct sockaddr)))	{
		printf("\n WARNING: Call ocall_connect with sockaddr pointer outside enclave \n");
		struct sockaddr *dup = (struct sockaddr *)malloc(sizeof(struct sockaddr));
		memcpy(dup, address, sizeof(struct sockaddr));
		status = ocall_connect(&retval, soc, dup, address_len);
	    free(dup);
	} else	{
		status = ocall_connect(&retval, soc, address, address_len);
	}

    if (status != SGX_SUCCESS) {
        printf("Ret error code: %x\n", status);
    }
	
	// printf("Return sgx_wrapper_connect: %d \n", retval);
	return retval;
}

static inline int sgx_wrapper_socket(int domain, int type, int protocol)
{
	// printf("Call sgx_wrapper_socket: %d \n", domain);
	int retval;
	ocall_socket(&retval, domain, type, protocol);
	return retval;
}

static inline int sgx_wrapper_accept(int sockfd, struct sockaddr *address, socklen_t *addrlen)
{
	// printf("Call sgx_wrapper_accept \n");
	int retval;
	sgx_status_t status;

	if (address!=NULL)	{
		// printf("\n WARNING: Call ocall_connect with sockaddr pointer outside enclave \n");
		struct sockaddr *dup = (struct sockaddr *)malloc(sizeof(struct sockaddr));
		memcpy(dup, address, sizeof(struct sockaddr));
		status = ocall_accept(&retval, sockfd, dup, addrlen);
		memcpy(address, dup, sizeof(struct sockaddr));
	    free(dup);
	} else	{
		// printf("right before ocall_accept\n");
		status = ocall_accept(&retval, sockfd, address, addrlen);
	}

    if (status != SGX_SUCCESS) {
        printf("Ret error code: %x\n", status);
    }

	// printf("Return sgx_wrapper_accept: %d \n", retval);
	return retval;
}

static inline ssize_t sgx_wrapper_sendto(int sockfd, const void *buf, size_t len, int flags, const void *dest_addr_cast, unsigned int addrlen)
{
	ssize_t retval;
	ocall_sendto(&retval, sockfd, buf, len, flags, dest_addr_cast, addrlen);
	return retval;
}

static inline int sgx_wrapper_socketpair(int domain, int type, int protocol, int sv[2])
{
	int retval;
	ocall_socketpair(&retval, domain, type, protocol, sv);
	return retval;
}

static inline int sgx_wrapper_setsockopt(int sockfd, int level, int optname, const void *optval, unsigned int optlen)
{
	int retval;
	printf("The len is : %d - %d\n", optlen, sizeof(int));
	printf("original opt value : %d \n", *((int*)optval));
	ocall_setsockopt(&retval, sockfd, level, optname, optval, optlen);
	return retval;
}

static inline int sgx_wrapper_getsockopt(int sockfd, int level, int optname, void *optval, unsigned int *optlen)
{
	int retval;
	ocall_getsockopt(&retval, sockfd, level, optname, optval, optlen);
	return retval;
}

static inline int sgx_wrapper_bind(int sockfd, const struct sockaddr * address, socklen_t addrlen)
{
	// printf("Call sgx_wrapper_bind \n");
	int retval = -1;
	sgx_status_t status;

	if (!sgx_is_within_enclave(address, sizeof(struct sockaddr)))	{
		printf("\n WARNING: Call ocall_bind with sockaddr pointer outside enclave \n");
		struct sockaddr *dup = (struct sockaddr *)malloc(sizeof(struct sockaddr));
		memcpy(dup, address, sizeof(struct sockaddr));
		status = ocall_bind(&retval, sockfd, dup, addrlen);
	    free(dup);
	} else	{
		// printf("Address before ocall: %p", address);
		status = ocall_bind(&retval, sockfd, address, addrlen);
	}

    if (status != SGX_SUCCESS) {
        printf("Ret error code: %x\n", status);
    }

	// printf("Return sgx_wrapper_bind: %d \n", retval);
	return retval;
}

static inline int sgx_wrapper_listen(int fd, int n)
{
	int retval;
	ocall_listen(&retval, fd, n);
	return retval;
}

static inline int sgx_wrapper_getsockname(int fd, struct sockaddr * addr, socklen_t *len)
{
	int retval;
	ocall_getsockname(&retval, fd, addr, len);
	return retval;
}

static inline int sgx_wrapper_getpeername(int fd, struct sockaddr * addr, socklen_t *len)
{
	int retval;
	ocall_getpeername(&retval, fd, addr, len);
	return retval;
}

static inline ssize_t sgx_wrapper_recvfrom(int fd, void *buf, size_t n, int flags, struct sockaddr * addr, socklen_t *addr_len)
{
	ssize_t retval;
	ocall_recvfrom(&retval, fd, buf, n, flags, addr, addr_len);
	return retval;
}

static inline ssize_t sgx_wrapper_sendmsg(int fd, const struct msghdr *message, int flags)
{
	ssize_t retval;
	ocall_sendmsg(&retval, fd, message, flags);
	return retval;
}

static inline ssize_t sgx_wrapper_recvmsg(int fd, struct msghdr *message, int flags)
{
	ssize_t retval;
	ocall_recvmsg(&retval, fd, message, flags);
	return retval;
}

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

