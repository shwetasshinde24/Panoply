#ifndef SGX_SYSRESOURCE_UTIL_H
#define SGX_SYSRESOURCE_UTIL_H

#include <proxy/sgx_sysresource_t.h>

static inline int sgx_wrapper_prlimit (__pid_t pid, enum __rlimit_resource resource, const struct rlimit *new_limit, struct rlimit *old_limit)
{
	int retval;
	ocall_prlimit(&retval, pid, resource, new_limit, old_limit);
	return retval;
}

static inline int sgx_wrapper_getrlimit (int resource, struct rlimit *new_limit)
{
	int retval;
	ocall_getrlimit(&retval, resource, new_limit);
	return retval;
}

static inline int sgx_wrapper_setrlimit (int resource, const struct rlimit *new_limit)
{
	int retval;
	ocall_setrlimit(&retval, resource, new_limit);
	return retval;
}

#define prlimit(A, B, C, D) sgx_wrapper_prlimit(A, B, C, D)
#define getrlimit(A,B) sgx_wrapper_getrlimit(A, B)
#define setrlimit(A,B) sgx_wrapper_setrlimit(A, B)

#endif