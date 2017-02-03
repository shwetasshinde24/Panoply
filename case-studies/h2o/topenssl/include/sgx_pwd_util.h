#ifndef SGX_PWD_UTIL_H
#define SGX_PWD_UTIL_H

#include <struct/sgx_pwd_struct.h>
#include <proxy/sgx_pwd_t.h>

#ifdef __cplusplus
extern "C"	{
#endif 

extern struct passwd *sgx_wrapper_getpwuid(uid_t uid);
extern struct passwd *sgx_wrapper_getpwnam(const char *name);
extern int sgx_wrapper_getpwnam_r(const char *name, struct passwd *pwd, 
                   char *buf, size_t buflen, struct passwd **result);

#ifdef __cplusplus
}
#endif 

#define getpwuid(A) sgx_wrapper_getpwuid(A)
#define getpwnam(A) sgx_wrapper_getpwnam(A)
#define getpwnam_r(A, B, C, D, E, ...) sgx_wrapper_getpwnam_r(A, B, C, D, E, ##__VA_ARGS__)

#endif 