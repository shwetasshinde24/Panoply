#include <sgx_sysstat_util.h>
#include <sgx_ocall_util.h>

int sgx_wrapper_stat(const char *path, struct stat *buf)
{
	int retval;
	sgx_status_t status = ocall_stat(&retval, path, buf);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_fstat(int fd, struct stat *buf)
{
	int retval;
	sgx_status_t status = ocall_fstat(&retval, fd, buf);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_lstat(const char *path, struct stat *buf)
{
	int retval;
	sgx_status_t status = ocall_lstat(&retval, path, buf);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_chmod(const char *file, mode_t mode)
{
	int retval;
	sgx_status_t status = ocall_chmod(&retval, file, mode);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_fchmod(int fd, mode_t mode)
{
	int retval;
	sgx_status_t status = ocall_fchmod(&retval, fd, mode);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_fchmodat(int fd, const char *file, mode_t mode, int flag)
{
	int retval;
	sgx_status_t status = ocall_fchmodat(&retval, fd, file, mode, flag);
	CHECK_STATUS(status);
	return retval;
}

mode_t sgx_wrapper_umask(mode_t mask)
{
	mode_t retval;
	sgx_status_t status = ocall_umask(&retval, mask);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_mkdir(const char *path, mode_t mode)
{
	int retval;
	sgx_status_t status = ocall_mkdir(&retval, path, mode);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_mkdirat(int fd, const char *path, mode_t mode)
{
	int retval;
	sgx_status_t status = ocall_mkdirat(&retval, fd, path, mode);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_mkfifo(const char *path, mode_t mode)
{
	int retval;
	sgx_status_t status = ocall_mkfifo(&retval, path, mode);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_mkfifoat(int fd, const char *path, mode_t mode)
{
	int retval;
	sgx_status_t status = ocall_mkfifoat(&retval, fd, path, mode);
	CHECK_STATUS(status);
	return retval;
}