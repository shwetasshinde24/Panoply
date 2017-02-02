#include <sgx_pwd_util.h>
#include <sgx_ocall_util.h>

struct passwd *sgx_wrapper_getpwuid(uid_t uid)
{
	struct passwd *retval;
	sgx_status_t status = ocall_getpwuid(&retval, uid);
	CHECK_STATUS(status);
	return retval;
}

struct passwd *sgx_wrapper_getpwnam(const char *name)
{
	struct passwd *retval;
	sgx_status_t status = ocall_getpwnam(&retval, name);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_getpwnam_r(const char *name, struct passwd *pwd, 
                   char *buf, size_t buflen, struct passwd **result)
{
	int retval;
	sgx_status_t status = ocall_getpwnam_r(&retval, name, pwd, buf, buflen, result);
	CHECK_STATUS(status);
	return retval;
}