#include <sgx_syssendfile_util.h>
#include <sgx_ocall_util.h>

ssize_t sgx_wrapper_sendfile (int out_fd, int in_fd, off_t *offset, size_t count)
{
	ssize_t retval;
	sgx_status_t status = ocall_sendfile(&retval, out_fd, in_fd, offset, count);
	CHECK_STATUS(status);
	return retval;
}