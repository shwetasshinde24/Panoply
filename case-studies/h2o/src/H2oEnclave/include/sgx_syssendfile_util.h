#ifndef SGX_SYSSENDFILE_UTIL_H
#define SGX_SYSSENDFILE_UTIL_H

#include <proxy/sgx_syssendfile_t.h>

#ifdef __cplusplus
extern "C"	{
#endif 

extern ssize_t sgx_wrapper_sendfile (int out_fd, int in_fd, off_t *offset, size_t count);

#ifdef __cplusplus
}
#endif 

#define sendfile(A, B, C, D) sgx_wrapper_sendfile(A, B, C, D)

#endif