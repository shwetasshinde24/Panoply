#ifndef SGX_SYSIOCTL_UTIL_H
#define SGX_SYSIOCTL_UTIL_H

#include "proxy/sgx_sysioctl_t.h"

static inline int sgx_wrapper_ioctl(int fd, unsigned long int request, void* arguments)
{
	int retval;
	ocall_ioctl(&retval, fd, request, arguments);
	return retval;
}

#define ioctl(A, B, ...) sgx_wrapper_ioctl(A, B, ##__VA_ARGS__)

#endif
