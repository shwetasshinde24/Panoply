#ifndef SGX_FCNTL_UTIL_H
#define SGX_FCNTL_UTIL_H 1

#include "struct/sgx_fcntl_struct.h"
#include "proxy/sgx_fcntl_t.h"
#include "sgx_stdio_util.h"

#ifdef __cplusplus
extern "C"	{
#endif

extern int sgx_wrapper_open(const char *pathname, int flags, ...);
extern int sgx_wrapper_creat(const char *pathname, unsigned int mode);
extern int sgx_wrapper_openat(int dirfd, const char *pathname, int flags, ...);
extern int sgx_wrapper_fcntl(int fd, int cmd, ...);

#ifdef __cplusplus
}
#endif

#define open(A, B, ...) sgx_wrapper_open((A), (B), ##__VA_ARGS__)
#define creat(A, B) sgx_wrapper_creat(A, B)
#define openat(A, B, C, ...) sgx_wrapper_openat((A), (B), (C), ##__VA_ARGS__)
#define fcntl(A, B, ...) sgx_wrapper_fcntl((A),(B), ##__VA_ARGS__)

#endif