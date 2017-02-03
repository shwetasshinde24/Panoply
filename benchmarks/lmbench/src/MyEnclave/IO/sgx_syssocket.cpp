/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sgx_syssocket_util.h>
#include <sgx_ocall_util.h>
#include <sgx_stdio_util.h>
#include <sgx_unistd_util.h>
#include <string.h>
#include "sgx_trts.h"
#include "sgx_status.h"
#include "MyEnclave_t.h"

int sgx_wrapper_shutdown(int fd, int how)
{
	int retval;
	sgx_status_t status = ocall_shutdown(&retval, fd, how);
	CHECK_STATUS(status);
	return retval;
}

ssize_t sgx_wrapper_recv(int fd, void *buf, size_t len, int flags)
{
	ssize_t retval;
	sgx_status_t status = ocall_recv(&retval, fd, buf, len, flags);
	CHECK_STATUS(status);
	return retval;
}

ssize_t sgx_wrapper_send(int fd, const void *buf, size_t len, int flags)
{
	ssize_t retval;
	sgx_status_t status = ocall_send(&retval, fd, buf, len, flags);
	CHECK_STATUS(status);
	return retval;
}  

int sgx_wrapper_connect(int soc, const struct sockaddr *address, socklen_t address_len)
{
	// printf("Call sgx_wrapper_connect: %d \n", soc);
	int retval = -1;
	sgx_status_t status;

	if (!sgx_is_within_enclave(address, sizeof(struct sockaddr)))	{
		sgx_wrapper_printf_debug("\n WARNING: Call sgx_status_t status = ocall_connect with sockaddr pointer outside enclave \n");
		struct sockaddr *dup = (struct sockaddr *)malloc(sizeof(struct sockaddr));
		memcpy(dup, address, sizeof(struct sockaddr));
		status = ocall_connect(&retval, soc, dup, address_len);
	    free(dup);
	} else	{
		status = ocall_connect(&retval, soc, address, address_len);
	}

    CHECK_STATUS(status);
	
	return retval;
}

int sgx_wrapper_socket(int domain, int type, int protocol)
{
	int retval;
	sgx_status_t status = ocall_socket(&retval, domain, type, protocol);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_accept(int sockfd, struct sockaddr *address, socklen_t *addrlen)
{
	// printf("sgx_wrapper_accept \n");
	int retval;
	sgx_status_t status;

	if (address!=NULL)	{
		struct sockaddr *dup = (struct sockaddr *)malloc(sizeof(struct sockaddr));
		memcpy(dup, address, sizeof(struct sockaddr));
		status = ocall_accept(&retval, sockfd, dup, addrlen);
		memcpy(address, dup, sizeof(struct sockaddr));
	    free(dup);
	} else	{
		if (address==NULL && addrlen==NULL)	{
			struct sockaddr tmpaddr;
			socklen_t tmplen;
			address = &tmpaddr; addrlen=&tmplen;
		}
		status = ocall_accept(&retval, sockfd, address, addrlen);
	}

    CHECK_STATUS(status);
	return retval;
}

ssize_t sgx_wrapper_sendto(int sockfd, const void *buf, size_t len, int flags, const void *dest_addr_cast, unsigned int addrlen)
{
	ssize_t retval;
	sgx_status_t status = ocall_sendto(&retval, sockfd, buf, len, flags, dest_addr_cast, addrlen);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_socketpair(int domain, int type, int protocol, int sv[2])
{
	int retval;
	sgx_status_t status = ocall_socketpair(&retval, domain, type, protocol, sv);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_setsockopt(int sockfd, int level, int optname, const void *optval, unsigned int optlen)
{
	int retval;
	sgx_status_t status = ocall_setsockopt(&retval, sockfd, level, optname, optval, optlen);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_getsockopt(int sockfd, int level, int optname, void *optval, unsigned int *optlen)
{
	int retval;
	sgx_status_t status = ocall_getsockopt(&retval, sockfd, level, optname, optval, optlen);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_bind(int sockfd, const struct sockaddr * address, socklen_t addrlen)
{
	// printf("Call sgx_wrapper_bind \n");
	int retval = -1;
	sgx_status_t status;

	if (!sgx_is_within_enclave(address, sizeof(struct sockaddr)))	{
		sgx_wrapper_printf_debug("\n WARNING: Call sgx_status_t status = ocall_bind with sockaddr pointer outside enclave \n");
		// struct sockaddr *dup = (struct sockaddr *)malloc(sizeof(struct sockaddr));
		// memcpy(dup, address, sizeof(struct sockaddr));
		status = ocall_bind_untrusted(&retval, sockfd, address, addrlen);
	    // free(dup);
	} else	{
		// printf("Address before ocall: %p", address);
		status = ocall_bind(&retval, sockfd, address, addrlen);
	}

    CHECK_STATUS(status);
	// printf("Return sgx_wrapper_bind: %d \n", retval);
	return retval;
}

int sgx_wrapper_listen(int fd, int n)
{
	int retval;
	sgx_status_t status = ocall_listen(&retval, fd, n);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_getsockname(int fd, struct sockaddr * addr, socklen_t *len)
{
	int retval;
	sgx_status_t status = ocall_getsockname(&retval, fd, addr, len);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_getpeername(int fd, struct sockaddr * addr, socklen_t *len)
{
	int retval;
	sgx_status_t status = ocall_getpeername(&retval, fd, addr, len);
	CHECK_STATUS(status);
	return retval;
}

ssize_t sgx_wrapper_recvfrom(int fd, void *buf, size_t n, int flags, struct sockaddr * addr, socklen_t *addr_len)
{
	ssize_t retval;

	// This buffer is outside the enclave and serve only for recv from to speed up.
	static void* untrusted_buf = untrusted_malloc(BUFSIZ);
	static void* untrusted_addr = untrusted_malloc(30);

	if (n>BUFSIZ)	{
		sgx_debug("Increase untrusted buf siz for your case \n");
	}

	sgx_status_t status = ocall_recvfrom(&retval, fd, untrusted_buf, n, flags, untrusted_addr, addr_len);
	CHECK_STATUS(status);

	if (*addr_len>30)	{
		sgx_debug("Untrusted buffer overflow");
	}

	memcpy(addr, untrusted_addr, *addr_len);
	memcpy(buf, untrusted_buf, n);
	return retval;
}

ssize_t sgx_wrapper_sendmsg(int fd, const struct msghdr *message, int flags)
{
	ssize_t retval;
	sgx_status_t status = ocall_sendmsg(&retval, fd, message, flags);
	CHECK_STATUS(status);
	return retval;
}

ssize_t sgx_wrapper_recvmsg(int fd, struct msghdr *message, int flags)
{
	ssize_t retval;
	sgx_status_t status = ocall_recvmsg(&retval, fd, message, flags);
	CHECK_STATUS(status);
	return retval;
}