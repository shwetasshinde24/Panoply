// #include <replacements/sgx_stdio_util.h>
#include <fcntl.h>
#include <stdio.h>

#include "TopensslEnclave_u.h"

extern void increase_ocall_count();

int ocall_open1(const char *pathname, int flags)
{
	increase_ocall_count();
	return open(pathname, flags);
}

int ocall_open2(const char *pathname, int flags, unsigned int mode)
{
	increase_ocall_count();
	return open(pathname, flags, mode);
}

int ocall_creat(const char *pathname, unsigned int mode)
{
	increase_ocall_count();
	return creat(pathname, mode);
}

int ocall_openat1(int dirfd, const char *pathname, int flags)
{
	increase_ocall_count();
	return openat(dirfd, pathname, flags);
}

int ocall_openat2(int dirfd, const char *pathname, int flags, unsigned int mode)
{
	increase_ocall_count();
	return openat(dirfd, pathname, flags, mode);
}

int ocall_fcntl1(int fd, int cmd)
{
	increase_ocall_count();
	return fcntl(fd, cmd);
}

int ocall_fcntl2(int fd, int cmd, long arg)
{
	increase_ocall_count();
	// printf("Call ocall_fcntl2 %d, %d, %d \n", fd, cmd, arg);
	// if (arg == O_NONBLOCK)	{
	// 	printf("Warning: set fd to nonblock is not allowed:%d\n", fd);
	// 	return -1;
	// }
	return fcntl(fd, cmd, arg);
}

int ocall_fcntl3(int fd, int cmd, void* arg_cast, int flocksz)
{
	increase_ocall_count();
	struct flock* arg = (struct flock*)arg_cast;
	return fcntl(fd, cmd, arg);
}