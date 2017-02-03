#ifndef SGX_SYSRESOURCE_UTIL_H
#define SGX_SYSRESOURCE_UTIL_H

#include <proxy/sgx_sysresource_t.h>

#ifdef __cplusplus
extern "C"	{
#endif 

extern int sgx_wrapper_prlimit (__pid_t pid, enum __rlimit_resource resource, const struct rlimit *new_limit, struct rlimit *old_limit);
extern int sgx_wrapper_getrlimit (int resource, struct rlimit *new_limit);
extern int sgx_wrapper_setrlimit (int resource, const struct rlimit *new_limit);

#ifdef __cplusplus
}
#endif 

#define prlimit(A, B, C, D) sgx_wrapper_prlimit(A, B, C, D)
#define getrlimit(A,B) sgx_wrapper_getrlimit(A, B)
#define setrlimit(A,B) sgx_wrapper_setrlimit(A, B)

#endif