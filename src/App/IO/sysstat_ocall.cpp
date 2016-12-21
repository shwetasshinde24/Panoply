// #include <replacements/sgx_stdio_util.h>
#include <sys/stat.h>
#include <unistd.h>

#include "TopensslEnclave_u.h"

extern void increase_ocall_count();

int ocall_stat(const char *path, struct stat *buf)
{
    increase_ocall_count();
	return stat(path, buf);
}

int ocall_fstat(int fd, struct stat *buf)
{
    increase_ocall_count();
	return fstat(fd, buf);
}

int ocall_lstat(const char *path, struct stat *buf)
{
    increase_ocall_count();
	return lstat(path, buf);
}

int ocall_chmod (const char *file, mode_t mode)
{
    increase_ocall_count();
	return chmod(file, mode);
}

// int ocall_lchmod (const char *file, mode_t mode)
// {
// 	return lchmod(file, mode);
// }

int ocall_fchmod (int fd, mode_t mode)
{
    increase_ocall_count();
	return fchmod(fd, mode);
}

int ocall_fchmodat (int fd, const char *file, mode_t mode, int flag)
{
    increase_ocall_count();
	return fchmodat(fd, file, mode, flag);
}

mode_t ocall_umask (mode_t mask)
{
    increase_ocall_count();
	return umask(mask);
}

// mode_t ocall_getumask (void)
// {
// 	return getumask();
// }

int ocall_mkdir (const char *path, mode_t mode)
{
    increase_ocall_count();
	return mkdir(path, mode);
}

int ocall_mkdirat (int fd, const char *path, mode_t mode)
{
    increase_ocall_count();
	return mkdirat(fd, path, mode);
}

int ocall_mkfifo (const char *path, mode_t mode)
{
    increase_ocall_count();
	return mkfifo(path, mode);
}

int ocall_mkfifoat (int fd, const char *path, mode_t mode)
{
    increase_ocall_count();
	return mkfifoat(fd, path, mode);
}
