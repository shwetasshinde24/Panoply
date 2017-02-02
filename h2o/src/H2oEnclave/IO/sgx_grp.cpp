#include <sgx_grp_util.h>
#include <sgx_ocall_util.h>


struct group *sgx_wrapper_getgrgid(gid_t gid)
{
	struct group *retval;
	sgx_status_t status = ocall_getgrgid(&retval, gid);
	CHECK_STATUS(status);
	return retval;
}


int sgx_wrapper_initgroups(const char *user, gid_t group)
{
	int retval;
	sgx_status_t status = ocall_initgroups(&retval, user, group);
	CHECK_STATUS(status);
	return retval;
}