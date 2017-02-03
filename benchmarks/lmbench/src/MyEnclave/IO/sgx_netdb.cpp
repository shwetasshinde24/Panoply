/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sgx_netdb_util.h>
#include <sgx_ocall_util.h>
#define __OPTIMIZE__ 1
#include <MyEnclave_t.h>
#include <sgx_stdio_util.h>

void sgx_wrapper_freeaddrinfo(void * res_cast)
{
	sgx_status_t status = ocall_freeaddrinfo(res_cast);
	CHECK_STATUS(status);
}

void printAddrInfo(struct addrinfo* addr)
{
	sgx_wrapper_printf_debug("Addrinfo: %d %d %d %d %d \n", addr->ai_flags, addr->ai_family, addr->ai_socktype, addr->ai_protocol, addr->ai_addrlen); 
}

int sgx_wrapper_getaddrinfo(const char *node, const char *service, const void *hints_cast, void **res_cast)
{
	int retval;
	struct addrinfo* my_addrinfo = (struct addrinfo*)malloc(sizeof(struct addrinfo));
	sgx_status_t status = ocall_getaddrinfo(&retval, node, service, hints_cast, res_cast);
	CHECK_STATUS(status);
	printAddrInfo(*res_cast);
	return retval;
}

void sgx_wrapper_sethostent (int stay_open)
{
	sgx_status_t status = ocall_sethostent(stay_open);
	CHECK_STATUS(status);
}

void sgx_wrapper_endhostent (void)
{
	sgx_status_t status = ocall_endhostent();
	CHECK_STATUS(status);
}

struct hostent *sgx_wrapper_gethostent (void)
{
	struct hostent *retval;
	sgx_status_t status = ocall_gethostent(&retval);
	CHECK_STATUS(status);
	return retval;
}

struct hostent *sgx_wrapper_gethostbyaddr (const void *addr, socklen_t len, int type)
{
	struct hostent *retval;
	sgx_status_t status = ocall_gethostbyaddr(&retval, addr, len, type);
	CHECK_STATUS(status);
	return retval;
}

struct hostent *sgx_wrapper_gethostbyname (const char *name)
{
	struct hostent *retval;
	sgx_status_t status = ocall_gethostbyname(&retval, name);
	CHECK_STATUS(status);
	return retval;
}

void sgx_wrapper_setnetent (int stay_open)
{
	sgx_status_t status = ocall_setnetent(stay_open);
	CHECK_STATUS(status);
}

void sgx_wrapper_endnetent (void)
{
	sgx_status_t status = ocall_endnetent();
	CHECK_STATUS(status);
}

struct netent *sgx_wrapper_getnetent (void)
{
	struct netent *retval;
	sgx_status_t status = ocall_getnetent(&retval);
	CHECK_STATUS(status);
	return retval;
}

struct netent *sgx_wrapper_getnetbyaddr (uint32_t net, int type)
{
	struct netent *retval;
	sgx_status_t status = ocall_getnetbyaddr(&retval, net, type);
	CHECK_STATUS(status);
	return retval;
}

struct netent *sgx_wrapper_getnetbyname (const char *name)
{
	struct netent *retval;
	sgx_status_t status = ocall_getnetbyname(&retval, name);
	CHECK_STATUS(status);
	return retval;
}

void sgx_wrapper_setservent (int stay_open)
{
	sgx_status_t status = ocall_setservent(stay_open);
	CHECK_STATUS(status);
}

void sgx_wrapper_endservent (void)
{
	sgx_status_t status = ocall_endservent();
	CHECK_STATUS(status);
}

struct servent *sgx_wrapper_getservent (void)
{
	struct servent* retval;
	sgx_status_t status = ocall_getservent(&retval);
	CHECK_STATUS(status);
	return retval;
}

struct servent *sgx_wrapper_getservbyname ( const char *name, const char *proto)
{
	struct servent* retval;
	sgx_status_t status = ocall_getservbyname(&retval, name, proto);
	CHECK_STATUS(status);
	return retval;
}

struct servent *sgx_wrapper_getservbyport (int port, const char *proto)
{
	struct servent* retval;
	sgx_status_t status = ocall_getservbyport(&retval, port, proto);
	CHECK_STATUS(status);
	return retval;
}

void sgx_wrapper_setprotoent (int stay_open)
{
	sgx_status_t status = ocall_setprotoent(stay_open);
	CHECK_STATUS(status);
}

void sgx_wrapper_endprotoent (void)
{
	sgx_status_t status = ocall_endprotoent();
	CHECK_STATUS(status);
}

struct protoent *sgx_wrapper_getprotoent (void)
{
	struct protoent* retval;
	sgx_status_t status = ocall_getprotoent(&retval);
	CHECK_STATUS(status);
	return retval;
}

struct protoent *sgx_wrapper_getprotobyname (const char *name)
{
	struct protoent* retval;
	sgx_status_t status = ocall_getprotobyname(&retval, name);
	CHECK_STATUS(status);
	return retval;
}

struct protoent *sgx_wrapper_getprotobynumber (int proto)
{
	struct protoent* retval;
	sgx_status_t status = ocall_getprotobynumber(&retval, proto);
	CHECK_STATUS(status);
	return retval;
}

char *sgx_wrapper_gai_strerror (int ecode)
{
	char* retval;
	sgx_status_t status = ocall_gai_strerror(&retval, ecode);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_getnameinfo (const struct sockaddr *sa,
	socklen_t salen, char *host,
	socklen_t hostlen, char *serv,
	socklen_t servlen, int flags)
{
	int retval;
	sgx_status_t status = ocall_getnameinfo(&retval, sa, salen, host, hostlen, serv, servlen, flags);
	CHECK_STATUS(status);
	return retval;
}