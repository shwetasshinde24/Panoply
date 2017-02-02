#ifndef SGX_NETDB_UTIL_H
#define SGX_NETDB_UTIL_H 1

#include <struct/sgx_netdb_struct.h>

#ifdef __cplusplus
extern "C"	{
#endif 

extern void sgx_wrapper_freeaddrinfo(void * res_cast);
extern int sgx_wrapper_getaddrinfo(const char *node, const char *service, const void *hints_cast, void **res_cast);
extern void sgx_wrapper_sethostent (int stay_open);
extern void sgx_wrapper_endhostent (void);
extern struct hostent *sgx_wrapper_gethostent (void);
extern struct hostent *sgx_wrapper_gethostbyaddr (const void *addr, socklen_t len, int type);
extern struct hostent *sgx_wrapper_gethostbyname (const char *name);
extern void sgx_wrapper_setnetent (int stay_open);
extern void sgx_wrapper_endnetent (void);
extern struct netent *sgx_wrapper_getnetent (void);
extern struct netent *sgx_wrapper_getnetbyaddr (uint32_t net, int type);
extern struct netent *sgx_wrapper_getnetbyname (const char *name);
extern void sgx_wrapper_setservent (int stay_open);
extern void sgx_wrapper_endservent (void);
extern struct servent *sgx_wrapper_getservent (void);
extern struct servent *sgx_wrapper_getservbyname ( const char *name, const char *proto);
extern struct servent *sgx_wrapper_getservbyport (int port, const char *proto);
extern void sgx_wrapper_setprotoent (int stay_open);
extern void sgx_wrapper_endprotoent (void);
extern struct protoent *sgx_wrapper_getprotoent (void);
extern struct protoent *sgx_wrapper_getprotobyname (const char *name);
extern struct protoent *sgx_wrapper_getprotobynumber (int proto);
extern char *sgx_wrapper_gai_strerror (int ecode);
extern int sgx_wrapper_getnameinfo (const struct sockaddr *sa,
	socklen_t salen, char *host,
	socklen_t hostlen, char *serv,
	socklen_t servlen, int flags);

#ifdef __cplusplus
}
#endif 

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
#define getservbyname(A, B) sgx_wrapper_getservbyname(A, B, C)
#define getservbyport(A, B) sgx_wrapper_getservbyport(A, B)
#define setprotoent(A) sgx_wrapper_setprotoent(A)
#define endprotoent() sgx_wrapper_endprotoent()
#define getprotoent() sgx_wrapper_getprotoent()
#define getprotobyname(A) sgx_wrapper_getprotobyname(A)
#define getprotobynumber(A) sgx_wrapper_getprotobynumber(A)
#define gai_strerror(A) sgx_wrapper_gai_strerror(A)
#define getnameinfo(A, B, C, D, E, F, G) sgx_wrapper_getnameinfo(A, B, C, D, E, F, G)

#endif