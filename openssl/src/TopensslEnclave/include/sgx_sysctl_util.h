#ifndef SGX_SYSCTL_UTIL_H
#define SGX_SYSCTL_UTIL_H 1

#include <proxy/sgx_sysctl_t.h>

static inline int sgx_wrapper_sysctl(int *name, int nlen, void *oldval, size_t *oldlenp, void *newval, size_t newlen)
{
	int retval;
	ocall_sysctl(&retval, name, nlen, oldval, oldlenp, newval, newlen);
	return retval;
}

#define sysctl(A, B, C, D, E, F) sgx_wrapper_sysctl(A, B, C, D, E, F)

#endif