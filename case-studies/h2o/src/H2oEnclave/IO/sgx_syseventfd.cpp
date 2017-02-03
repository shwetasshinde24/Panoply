
#include <sgx_syseventfd_util.h>
#include <proxy/sgx_syseventfd_t.h>
#include <sgx_ocall_util.h>

int sgx_wrapper_eventfd(unsigned int initval, int flags)
{
	int retval;
	sgx_status_t status = ocall_eventfd(&retval, initval, flags);
	CHECK_STATUS(status);
	return retval;
}