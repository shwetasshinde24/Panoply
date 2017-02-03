/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sgx_arpainet_util.h>
#include <sgx_ocall_util.h>
#include <MyEnclave_t.h>
#include <exception>
#include <sgx_status.h>
#include <sgx_thread.h>

INIT_LOCK(ocall_inet_addr);
INIT_LOCK(ocall_inet_lnaof);
INIT_LOCK(ocall_inet_makeaddr);
INIT_LOCK(ocall_inet_netof);
INIT_LOCK(ocall_inet_network);
INIT_LOCK(ocall_inet_ntoa);
INIT_LOCK(ocall_inet_pton);
INIT_LOCK(ocall_inet_ntop);

extern "C"	{

	in_addr_t sgx_wrapper_inet_addr (const char *cp)
	{
		in_addr_t retval;
		sgx_status_t status = SAFE_INVOKE(ocall_inet_addr, &retval, cp);
		CHECK_STATUS(status);
		return retval;
	}

	in_addr_t sgx_wrapper_inet_lnaof (struct in_addr in)
	{
		in_addr_t retval;
		sgx_status_t status = ocall_inet_lnaof(&retval, in);
		CHECK_STATUS(status);
		return retval;
	}

	struct in_addr sgx_wrapper_inet_makeaddr (in_addr_t net, in_addr_t host)
	{
		struct in_addr retval;
		sgx_status_t status = ocall_inet_makeaddr(&retval, net, host);
		CHECK_STATUS(status);
		return retval;
	}

	in_addr_t sgx_wrapper_inet_netof (struct in_addr in)
	{
		in_addr_t retval;
		sgx_status_t status = ocall_inet_netof(&retval, in);
		CHECK_STATUS(status);
		return retval;
	}

	in_addr_t sgx_wrapper_inet_network (const char *cp)
	{
		in_addr_t retval;
		sgx_status_t status = ocall_inet_network(&retval, cp);
		CHECK_STATUS(status);
		return retval;
	}

	char *sgx_wrapper_inet_ntoa (struct in_addr in)
	{
		char *retval;
		sgx_status_t status = ocall_inet_ntoa(&retval, in);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_inet_pton (int af, const char *cp, void *buf)
	{
		int retval;
		sgx_status_t status = SAFE_INVOKE(ocall_inet_pton, &retval, af, cp, buf);
		CHECK_STATUS(status);
		return retval;
	}

	char *sgx_wrapper_inet_ntop (int af,  const void *cp, char *buf, socklen_t len)
	{
		char *retval;
		sgx_status_t status = ocall_inet_ntop(&retval, af, cp, buf, len);
		CHECK_STATUS(status);
		return retval;
	}

}