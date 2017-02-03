#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "TopensslEnclave_u.h"


extern void increase_ocall_count();

static inline void printSockAddrInfo(const struct sockaddr* addr)
{
	struct sockaddr_in* addrin = (struct sockaddr_in*)addr;
	// printf("sockaddr_in: family: %d port: %d addr: %s \n", addrin->sin_family, addrin->sin_port, inet_ntoa(addrin->sin_addr) ); 
}

static inline void printAddrInfo(struct addrinfo* addr)
{
	// printf("Addrinfo: %d %d %d %d %d \n", addr->ai_flags, addr->ai_family, addr->ai_socktype, addr->ai_protocol, addr->ai_addrlen); 
}

void ocall_freeaddrinfo(void * res_cast)
{
	increase_ocall_count();
	struct addrinfo *res = (struct addrinfo *)res_cast;
	freeaddrinfo(res);
}

int ocall_getaddrinfo(const char *node, const char *service, const void *hints_cast, void **res_cast)
{
	increase_ocall_count();
	// printf("ocall_getaddrinfo \n");
	// const struct addrinfo *hints = (const struct addrinfo *)hints_cast;
	// struct addrinfo **res = (struct addrinfo **)res_cast;
	const struct addrinfo *hints = NULL;
	struct addrinfo *res = NULL;

	int ret = getaddrinfo(node, service, hints, &res);
	printAddrInfo(res);
	if (ret==0)	{
		memcpy(res_cast, &res, sizeof(struct addrinfo **));
	}
	return ret;
}

int ocall_getaddrinfo1(const char *node, const char *service, const void *hints_cast, void *res_cast)
{
	increase_ocall_count();
	// printf("ocall_getaddrinfo \n");
	// const struct addrinfo *hints = (const struct addrinfo *)hints_cast;
	// struct addrinfo **res = (struct addrinfo **)res_cast;
	const struct addrinfo *hints = NULL;
	struct addrinfo *res = NULL;

	int ret = getaddrinfo(node, service, hints, &res);
	// printf("done getaddrinfo: %d\n", ret);
	printAddrInfo(res);
	if (ret==0)	{
		// printf("do the memcpy \n");
		memcpy(res_cast, res, sizeof(struct addrinfo));
	}
	return ret;
}

void ocall_sethostent (int stay_open)
{
	increase_ocall_count();
	sethostent(stay_open);
}

void ocall_endhostent (void)
{
	increase_ocall_count();
	endhostent();
}

struct hostent *ocall_gethostent (void)
{
	increase_ocall_count();
	return gethostent();
}

struct hostent *ocall_gethostbyaddr (const void *addr, socklen_t len, int type)
{
	increase_ocall_count();
	return gethostbyaddr(addr, len, type);
}

struct hostent *ocall_gethostbyname (const char *name)
{
	increase_ocall_count();
	return gethostbyname(name);
}

void ocall_setnetent (int stay_open)
{
	increase_ocall_count();
	setnetent(stay_open);
}

void ocall_endnetent (void)
{
	increase_ocall_count();
	endnetent();
}

struct netent *ocall_getnetent (void)
{
	increase_ocall_count();
	return getnetent();
}

struct netent *ocall_getnetbyaddr (uint32_t net, int type)
{
	increase_ocall_count();
	return getnetbyaddr(net, type);
}

struct netent *ocall_getnetbyname (const char *name)
{
	increase_ocall_count();
	return getnetbyname(name);
}

void ocall_setservent (int stay_open)
{
	increase_ocall_count();
	setservent(stay_open);
}

void ocall_endservent (void)
{
	increase_ocall_count();
	endservent();
}

struct servent *ocall_getservent (void)
{
	increase_ocall_count();
	return getservent();
}

struct servent *ocall_getservbyname ( const char *name, const char *proto)
{
	increase_ocall_count();
	return getservbyname(name, proto);
}

struct servent *ocall_getservbyport (int port, const char *proto)
{
	increase_ocall_count();
	return getservbyport(port, proto);
}

void ocall_setprotoent (int stay_open)
{
	increase_ocall_count();
	setprotoent(stay_open);
}

void ocall_endprotoent (void)
{
	increase_ocall_count();
	endprotoent();
}

struct protoent *ocall_getprotoent (void)
{
	increase_ocall_count();
	return getprotoent();
}

struct protoent *ocall_getprotobyname (const char *name)
{
	increase_ocall_count();
	return getprotobyname(name);
}

struct protoent *ocall_getprotobynumber (int proto)
{
	increase_ocall_count();
	return getprotobynumber(proto);
}

char *ocall_gai_strerror (int ecode)
{
	increase_ocall_count();
	return (char*) gai_strerror(ecode);
}

int ocall_getnameinfo (const struct sockaddr *sa,
	socklen_t salen, char *host,
	socklen_t hostlen, char *serv,
	socklen_t servlen, int flags)
{
	increase_ocall_count();
	printSockAddrInfo(sa);
	return getnameinfo(sa, salen, host, hostlen, serv, servlen, flags);
}