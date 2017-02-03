
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "H2oEnclave_u.h"

static inline void printSockAddrInfo(struct sockaddr* addr)
{
	struct sockaddr_in* addrin = (struct sockaddr_in*)addr;
	// printf("sockaddr_in: family: %d port: %d addr: %s \n", addrin->sin_family, addrin->sin_port, inet_ntoa(addrin->sin_addr) ); 
}

static inline void printSockAddrUnInfo(const struct sockaddr* addr)
{
	struct sockaddr_un* addrun = (struct sockaddr_un*)addr;
	// printf("sockaddr_un info: %s \n", addrun->sun_path);
}

int ocall_shutdown(int sockfd, int how)
{
    return shutdown(sockfd, how);
}

ssize_t ocall_recv(int sockfd, void *buf, size_t len, int flags)
{
    return recv(sockfd, buf, len, flags);
}

ssize_t ocall_send(int sockfd, const void *buf, size_t len, int flags)
{
    return send(sockfd, buf, len, flags);
}

int ocall_connect(int soc, const struct sockaddr *address, socklen_t address_len)
{
	int ret = connect(soc, address, address_len);
	if (ret<0)	{

	}
	return ret;
}

int ocall_socket(int domain, int type, int protocol)
{
	int sockfd = socket(domain, type, protocol);
	return sockfd;
}

int ocall_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	*addrlen = 16;
	struct sockaddr *tmp = (struct sockaddr *)malloc(sizeof(struct sockaddr));
	memset(tmp, 1, sizeof(struct sockaddr));
	int ret = accept(sockfd, tmp, addrlen);
	memcpy(addr, tmp, sizeof(struct sockaddr));
	return ret;
}

ssize_t ocall_sendto(int sockfd, const void *buf, size_t len, int flags, const void *dest_addr_cast, unsigned int addrlen)
{
	const struct sockaddr *dest_addr = (const struct sockaddr *)dest_addr_cast;
	return sendto(sockfd, buf, len, flags, dest_addr, addrlen);
}

int ocall_socketpair(int domain, int type, int protocol, int sv[2])
{
	// printf("Call ocall_socketpair %d, %d \n", domain, type);
	return socketpair(domain, type, protocol, sv);
}

int ocall_setsockopt(int sockfd, int level, int optname, const void *optval, unsigned int optlen)
{
	int value = 0;
	setsockopt(sockfd, level, optname, &value, optlen);
	return 0;
}

int ocall_getsockopt(int sockfd, int level, int optname, void *optval, unsigned int *optlen)
{
	return getsockopt(sockfd, level, optname, optval, optlen);
}

int ocall_bind(int fd, const struct sockaddr * addr, socklen_t len)
{
	printSockAddrInfo((struct sockaddr * )addr);
	printSockAddrUnInfo((struct sockaddr * )addr);

	int ret = -1;
	ret = bind(fd, addr, len);
	if (ret!=0)
		printf("Bind socket error: %s \n", strerror(errno));

	return ret;
}

int ocall_bind_untrusted(int fd, const struct sockaddr * addr, socklen_t len)
{
	int ret = -1;
	ret = bind(fd, addr, len);
	if (ret!=0)
		printf("Bind socket error: %s \n", strerror(errno));

	return ret;	
}

int ocall_listen(int fd, int n)
{
	return listen(fd, n);
}

int ocall_getsockname(int fd, struct sockaddr * addr, socklen_t *len)
{
	*len = sizeof(struct sockaddr);
	int ret = getsockname(fd, addr, len);
	return ret;
}

int ocall_getpeername(int fd, struct sockaddr * addr, socklen_t *len)
{
	return getpeername(fd, addr, len);
}

ssize_t ocall_recvfrom(int fd, void *buf, size_t n, int flags, struct sockaddr * addr, socklen_t *addr_len)
{
	return recvfrom(fd, buf, n, flags, addr, addr_len);
}

ssize_t ocall_sendmsg(int fd, const struct msghdr *message, int flags)
{
	return sendmsg(fd, message, flags);
}

ssize_t ocall_recvmsg(int fd, struct msghdr *message, int flags)
{
	return recvmsg(fd, message, flags);
}