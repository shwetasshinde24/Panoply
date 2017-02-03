#include <sgx_utsname_util.h>
#include <sgx_ocall_util.h>

int sgx_wrapper_uname(struct utsname *name)
{
	int retval;
	sgx_status_t status = ocall_uname(&retval, name);
	CHECK_STATUS(status);	
	return retval;
}