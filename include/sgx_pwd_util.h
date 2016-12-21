#ifndef SGX_PWD_UTIL_H
#define SGX_PWD_UTIL_H

#include <struct/sgx_pwd_struct.h>
#include <proxy/sgx_pwd_t.h>

static inline struct passwd *sgx_wrapper_getpwuid(uid_t uid)
{
	struct passwd *retval;
	ocall_getpwuid(&retval, uid);
	return retval;
}

static inline struct passwd *sgx_wrapper_getpwnam(const char *name)
{
	struct passwd *retval;
	ocall_getpwnam(&retval, name);
	return retval;
}

static inline int sgx_wrapper_getpwnam_r(const char *name, struct passwd *pwd, 
                   char *buf, size_t buflen, struct passwd **result)
{
	int retval;
	ocall_getpwnam_r(&retval, name, pwd, buf, buflen, result);
	return retval;
}
      

#define getpwuid(A) sgx_wrapper_getpwuid(A)
#define getpwnam(A) sgx_wrapper_getpwnam(A)
#define getpwnam_r(A, B, C, D, E, ...) sgx_wrapper_getpwnam_r(A, B, C, D, E, ##__VA_ARGS__)

#endif 