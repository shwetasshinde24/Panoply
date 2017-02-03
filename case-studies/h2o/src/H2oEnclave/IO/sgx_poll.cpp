#include <sgx_poll_util.h>
#include <sgx_ocall_util.h>

int sgx_wrapper_poll(struct pollfd* fds, unsigned int nfds, int timeout)
{
	int ret;
	sgx_status_t status = ocall_poll(&ret, fds, nfds, timeout);
	CHECK_STATUS(status);	
	return ret;
}