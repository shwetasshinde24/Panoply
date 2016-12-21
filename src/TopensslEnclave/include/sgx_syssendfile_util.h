#ifndef SGX_SYSSENDFILE_UTIL_H
#define SGX_SYSSENDFILE_UTIL_H

#include <proxy/sgx_syssendfile_t.h>

ssize_t sgx_wrapper_sendfile (int out_fd, int in_fd, off_t *offset, size_t count)
{
	ssize_t retval;
	ocall_sendfile(&retval, out_fd, in_fd, offset, count);
	return retval;
}

#define sendfile(A, B, C, D) sgx_wrapper_sendfile(A, B, C, D)

#endif