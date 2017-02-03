
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "TopensslEnclave_u.h"

extern void increase_ocall_count();

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
    increase_ocall_count();
    return shutdown(sockfd, how);
}

ssize_t ocall_recv(int sockfd, void *buf, size_t len, int flags)
{
    increase_ocall_count();
    return recv(sockfd, buf, len, flags);
}

ssize_t ocall_send(int sockfd, const void *buf, size_t len, int flags)
{
    increase_ocall_count();
    return send(sockfd, buf, len, flags);
}

int ocall_connect(int soc, const struct sockaddr *address, socklen_t address_len)
{
    increase_ocall_count();
	// const struct sockaddr *address = (struct sockaddr *) address_cast;
	// const struct sockaddr_in* addr_in = (struct sockaddr_in*) address_cast;

	// int len=20;
	// char buffer[len];
	// printf("Call ocall_connect %d by thread: %d \n", soc, pthread_self());
	printSockAddrInfo((struct sockaddr *)address);
	int ret = connect(soc, address, address_len);
	// printf("ocall_connect return this: %d \n", ret);
	if (ret<0)	{
		// printf("Oh dear, something went wrong with connect()! %s\n", strerror(errno));
	}
	return ret;
}

int ocall_socket(int domain, int type, int protocol)
{
    increase_ocall_count();
	// // printf("Call ocall_socket %d, %d %d \n", domain, type, protocol);
	int sockfd = socket(domain, type, protocol);
	if (sockfd<0)	{
		// printf("Oh dear, something went wrong with socket()! %s\n", strerror(errno));
	}
	// // printf("The return socket is: %d \n", sockfd);
	return sockfd;
}

int ocall_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    increase_ocall_count();
	// struct sockaddr *addr = (struct sockaddr *)addr_cast;
	*addrlen = 16;
	// // printf("Call ocall_accept %d, %p, %d \n", sockfd, addr, *addrlen);
	// printSockAddrInfo(addr);
	struct sockaddr *tmp = (struct sockaddr *)malloc(sizeof(struct sockaddr));
	memset(tmp, 1, sizeof(struct sockaddr));
	int ret = accept(sockfd, tmp, addrlen);
	// printSockAddrInfo(tmp);
	memcpy(addr, tmp, sizeof(struct sockaddr));
	if (ret<0)	{
		// // printf("Oh dear, something went wrong with accept()! %s\n", strerror(errno));
	}	
	// // printf("The return accept is: %d with socklen_t is: %d ", ret, *addrlen);
	return ret;
}

ssize_t ocall_sendto(int sockfd, const void *buf, size_t len, int flags, const void *dest_addr_cast, unsigned int addrlen)
{
    increase_ocall_count();
	const struct sockaddr *dest_addr = (const struct sockaddr *)dest_addr_cast;
	return sendto(sockfd, buf, len, flags, dest_addr, addrlen);
}

int ocall_socketpair(int domain, int type, int protocol, int sv[2])
{
    increase_ocall_count();
	// // printf("Call ocall_socketpair %d, %d \n", domain, type);
	return socketpair(domain, type, protocol, sv);
}

int ocall_setsockopt(int sockfd, int level, int optname, const void *optval, unsigned int optlen)
{
    increase_ocall_count();
	// printf("Call ocall_setsockopt with sockfd: %d %d %d %p, %u \n", sockfd, level, optname, optval, optlen);
	// printf("Sent opt value is: %d \n", *((int*)optval));
	int value = 0;
	// void *optval_dup = malloc(optlen);
	// memcpy(optval_dup, optval, optlen);
	// int ret = setsockopt(sockfd, level, optname, optval_dup, optlen);
	// free(optval_dup);
	setsockopt(sockfd, level, optname, &value, optlen);
	return value;
}

int ocall_getsockopt(int sockfd, int level, int optname, void *optval, unsigned int *optlen)
{
    increase_ocall_count();
	// printf("Call ocall_getsockopt \n");
	return getsockopt(sockfd, level, optname, optval, optlen);
}

int ocall_bind(int fd, const struct sockaddr * addr, socklen_t len)
{
    increase_ocall_count();
	// printf("Call ocall_bind %d, %p by thread %d \n", fd, addr, pthread_self());
	printSockAddrInfo((struct sockaddr * )addr);
	printSockAddrUnInfo((struct sockaddr * )addr);

	int ret = -1;
	ret = bind(fd, addr, len);
	if (ret!=0)
		// printf("The error code to string is: %s", strerror(errno));

	return ret;
}

int ocall_listen(int fd, int n)
{
    increase_ocall_count();
	// printf("Call ocall_listen %d %d by thread %d \n", fd, n, pthread_self());
	return listen(fd, n);
}

int ocall_getsockname(int fd, struct sockaddr * addr, socklen_t *len)
{
    increase_ocall_count();
	*len = sizeof(struct sockaddr);
	// printf("Call ocall_getsockname %d %p %d\n", fd, addr, *len);
	int ret = getsockname(fd, addr, len);
	// printf("Return addr is %p \n", addr);
	// printf("The family addr return is :%d , %s \n", ((struct sockaddr_in*)addr)->sin_family);
	//printSockAddrInfo(addr);
	// printf("Return %d with len %d \n", ret, *len);
	return ret;
}

int ocall_getpeername(int fd, struct sockaddr * addr, socklen_t *len)
{
    increase_ocall_count();
	// // printf("Call ocall_getpeername %d %p \n", fd, addr);
	return getpeername(fd, addr, len);
}

ssize_t ocall_recvfrom(int fd, void *buf, size_t n, int flags, struct sockaddr * addr, socklen_t *addr_len)
{
    increase_ocall_count();
	return recvfrom(fd, buf, n, flags, addr, addr_len);
}

ssize_t ocall_sendmsg(int fd, const struct msghdr *message, int flags)
{
    increase_ocall_count();
	return sendmsg(fd, message, flags);
}

ssize_t ocall_recvmsg(int fd, struct msghdr *message, int flags)
{
    increase_ocall_count();
	return recvmsg(fd, message, flags);
}