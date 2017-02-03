#ifndef SGX_NETDB_UTIL_H
#define SGX_NETDB_UTIL_H 1

#include <proxy/sgx_netdb_t.h>
// #define __OPTIMIZE__ 1
#// include <H2oEnclave_t.h>
#include <sgx_stdio_util.h>

static inline void sgx_wrapper_freeaddrinfo(void * res_cast)
{
	ocall_freeaddrinfo(res_cast);
}

static inline void printAddrInfo(struct addrinfo* addr)
{
	// printf("Addrinfo: %d %d %d %d %d \n", addr->ai_flags, addr->ai_family, addr->ai_socktype, addr->ai_protocol, addr->ai_addrlen); 
	// printf("The return address is: %p", addr);
	// print_string("Right after printAddrInfo \n");
	// print_int(addr->ai_family);
	// print_int(addr->ai_socktype);
	// print_int(addr->ai_protocol);
}

static inline int sgx_wrapper_getaddrinfo(const char *node, const char *service, const void *hints_cast, void **res_cast)
{
	int retval;
	struct addrinfo* my_addrinfo = (struct addrinfo*)malloc(sizeof(struct addrinfo));
	int err = ocall_getaddrinfo(&retval, node, service, hints_cast, res_cast);
	// int err = ocall_getaddrinfo1(&retval, node, service, hints_cast, my_addrinfo);
	print_int(sizeof(struct addrinfo));
	printAddrInfo(*res_cast);
	// *res_cast = my_addrinfo;
	//printAddrInfo(*res_cast);
	return retval;
}

static inline void sgx_wrapper_sethostent (int stay_open)
{
	ocall_sethostent(stay_open);
}

static inline void sgx_wrapper_endhostent (void)
{
	ocall_endhostent();
}

static inline struct hostent *sgx_wrapper_gethostent (void)
{
	struct hostent *retval;
	ocall_gethostent(&retval);
	return retval;
}

static inline struct hostent *sgx_wrapper_gethostbyaddr (const void *addr, socklen_t len, int type)
{
	struct hostent *retval;
	ocall_gethostbyaddr(&retval, addr, len, type);
	return retval;
}

static inline struct hostent *sgx_wrapper_gethostbyname (const char *name)
{
	struct hostent *retval;
	ocall_gethostbyname(&retval, name);
	return retval;
}

static inline void sgx_wrapper_setnetent (int stay_open)
{
	ocall_setnetent(stay_open);
}

static inline void sgx_wrapper_endnetent (void)
{
	ocall_endnetent();
}

static inline struct netent *sgx_wrapper_getnetent (void)
{
	struct netent *retval;
	ocall_getnetent(&retval);
	return retval;
}

static inline struct netent *sgx_wrapper_getnetbyaddr (uint32_t net, int type)
{
	struct netent *retval;
	ocall_getnetbyaddr(&retval, net, type);
	return retval;
}

static inline struct netent *sgx_wrapper_getnetbyname (const char *name)
{
	struct netent *retval;
	ocall_getnetbyname(&retval, name);
	return retval;
}

static inline void sgx_wrapper_setservent (int stay_open)
{
	ocall_setservent(stay_open);
}

static inline void sgx_wrapper_endservent (void)
{
	ocall_endservent();
}

static inline struct servent *sgx_wrapper_getservent (void)
{
	struct servent* retval;
	ocall_getservent(&retval);
	return retval;
}

static inline struct servent *sgx_wrapper_getservbyname ( const char *name, const char *proto)
{
	struct servent* retval;
	ocall_getservbyname(&retval, name, proto);
	return retval;
}

static inline struct servent *sgx_wrapper_getservbyport (int port, const char *proto)
{
	struct servent* retval;
	ocall_getservbyport(&retval, port, proto);
	return retval;
}

static inline void sgx_wrapper_setprotoent (int stay_open)
{
	ocall_setprotoent(stay_open);
}

static inline void sgx_wrapper_endprotoent (void)
{
	ocall_endprotoent();
}

static inline struct protoent *sgx_wrapper_getprotoent (void)
{
	struct protoent* retval;
	ocall_getprotoent(&retval);
	return retval;
}

static inline struct protoent *sgx_wrapper_getprotobyname (const char *name)
{
	struct protoent* retval;
	ocall_getprotobyname(&retval, name);
	return retval;
}

static inline struct protoent *sgx_wrapper_getprotobynumber (int proto)
{
	struct protoent* retval;
	ocall_getprotobynumber(&retval, proto);
	return retval;
}

static inline char *sgx_wrapper_gai_strerror (int ecode)
{
	char* retval;
	ocall_gai_strerror(&retval, ecode);
	return retval;
}

static inline int sgx_wrapper_getnameinfo (const struct sockaddr *sa,
	socklen_t salen, char *host,
	socklen_t hostlen, char *serv,
	socklen_t servlen, int flags)
{
	int retval;
	ocall_getnameinfo(&retval, sa, salen, host, hostlen, serv, servlen, flags);
	return retval;
}

#define freeaddrinfo(A) sgx_wrapper_freeaddrinfo(A)
#define getaddrinfo(A, B, C, D) sgx_wrapper_getaddrinfo(A, B, C, D)
#define sethostent(A) sgx_wrapper_sethostent(A)
#define endhostent() sgx_wrapper_endhostent()
#define gethostent() sgx_wrapper_gethostent()
#define gethostbyaddr(A, B, C) sgx_wrapper_gethostbyaddr(A, B, C)
#define gethostbyname(A) sgx_wrapper_gethostbyname(A)
#define setnetent(A) sgx_wrapper_setnetent(A)
#define endnetent() sgx_wrapper_endnetent()
#define getnetent() sgx_wrapper_getnetent()
#define getnetbyaddr(A, B) sgx_wrapper_getnetbyaddr(A, B)
#define getnetbyname(A) sgx_wrapper_getnetbyname(A)
#define setservent(A) sgx_wrapper_setservent(A)
#define endservent() sgx_wrapper_endservent()
#define getservent() sgx_wrapper_getservent()
#define getservbyname(A, B) sgx_wrapper_getservbyname(A, B)
#define getservbyport(A, B) sgx_wrapper_getservbyport(A, B)
#define setprotoent(A) sgx_wrapper_setprotoent(A)
#define endprotoent() sgx_wrapper_endprotoent()
#define getprotoent() sgx_wrapper_getprotoent()
#define getprotobyname(A) sgx_wrapper_getprotobyname(A)
#define getprotobynumber(A) sgx_wrapper_getprotobynumber(A)
#define gai_strerror(A) sgx_wrapper_gai_strerror(A)
#define getnameinfo(A, B, C, D, E, F, G) sgx_wrapper_getnameinfo(A, B, C, D, E, F, G)

#endif