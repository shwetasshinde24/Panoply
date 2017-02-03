#include <sgx_sysresource_util.h>
#include <sgx_ocall_util.h>

int sgx_wrapper_prlimit (__pid_t pid, enum __rlimit_resource resource, const struct rlimit *new_limit, struct rlimit *old_limit)
{
	int retval;
	sgx_status_t status = ocall_prlimit(&retval, pid, resource, new_limit, old_limit);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_getrlimit (int resource, struct rlimit *new_limit)
{
	int retval;
	sgx_status_t status = ocall_getrlimit(&retval, resource, new_limit);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_setrlimit (int resource, const struct rlimit *new_limit)
{
	int retval;
	sgx_status_t status = ocall_setrlimit(&retval, resource, new_limit);
	CHECK_STATUS(status);
	return retval;
}