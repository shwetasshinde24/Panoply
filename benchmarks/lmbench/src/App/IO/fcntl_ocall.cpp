/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <fcntl.h>
#include <stdio.h>

#include "MyEnclave_u.h"


int ocall_open1(const char *pathname, int flags)
{
	return open(pathname, flags);
}

int ocall_open2(const char *pathname, int flags, unsigned int mode)
{
	return open(pathname, flags, mode);
}

int ocall_creat(const char *pathname, unsigned int mode)
{
	return creat(pathname, mode);
}

int ocall_openat1(int dirfd, const char *pathname, int flags)
{
	return openat(dirfd, pathname, flags);
}

int ocall_openat2(int dirfd, const char *pathname, int flags, unsigned int mode)
{
	return openat(dirfd, pathname, flags, mode);
}

int ocall_fcntl1(int fd, int cmd)
{
	return fcntl(fd, cmd);
}

int ocall_fcntl2(int fd, int cmd, long arg)
{
	// printf("Call ocall_fcntl2 %d, %d, %d \n", fd, cmd, arg);
	// if (arg == O_NONBLOCK)	{
	// 	printf("Warning: set fd to nonblock is not allowed:%d\n", fd);
	// 	return -1;
	// }
	return fcntl(fd, cmd, arg);
}

int ocall_fcntl3(int fd, int cmd, void* arg_cast, int flock_size)
{
	struct flock* arg = (struct flock*)arg_cast;
	return fcntl(fd, cmd, arg);
}