#ifndef SGX_SYSSTAT_UTIL_H
#define SGX_SYSSTAT_UTIL_H
#include "proxy/sgx_sysstat_t.h"

#ifdef __cplusplus
extern "C"	{
#endif 

extern int sgx_wrapper_stat(const char *path, struct stat *buf);
extern int sgx_wrapper_fstat(int fd, struct stat *buf);
extern int sgx_wrapper_lstat(const char *path, struct stat *buf);
extern int sgx_wrapper_chmod(const char *file, mode_t mode);
extern int sgx_wrapper_fchmod(int fd, mode_t mode);
extern int sgx_wrapper_fchmodat(int fd, const char *file, mode_t mode, int flag);
extern mode_t sgx_wrapper_umask(mode_t mask);
extern int sgx_wrapper_mkdir(const char *path, mode_t mode);
extern int sgx_wrapper_mkdirat(int fd, const char *path, mode_t mode);
extern int sgx_wrapper_mkfifo(const char *path, mode_t mode);
extern int sgx_wrapper_mkfifoat(int fd, const char *path, mode_t mode);

#ifdef __cplusplus
}
#endif 

#define stat(A, B) sgx_wrapper_stat(A, B)
#define fstat(A, B) sgx_wrapper_fstat(A, B)
#define lstat(A, B) sgx_wrapper_lstat(A, B)
#define chmod(A, B) sgx_wrapper_chmod(A, B)
#define fchmod(A, B) sgx_wrapper_fchmod(A, B)
#define fchmodat(A, B, C) sgx_wrapper_fchmodat(A, B, C)
#define umask(A) sgx_wrapper_umask(A)
#define mkdir(A, B) sgx_wrapper_mkdir(A, B)
#define mkdirat(A, B, C) sgx_wrapper_mkdirat(A, B, C)
#define mkfifo(A, B) sgx_wrapper_mkfifo(A, B)
#define mkfifoat(A, B, C) sgx_wrapper_mkfifoat(A, B, C)

#endif