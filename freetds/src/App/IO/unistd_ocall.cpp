// #include <replacements/sgx_stdio_util.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>

#include "TdsEnclave_u.h"

off_t ocall_read(int fd, void *buf, size_t count)
{
	// // printf ("ocall_read %d, %p, %d\n", fd, buf, count);
    off_t ret = read(fd, buf, count);
    if (ret==-1)	{
    	// printf("The ocall_read error is: %s \n", strerror(errno));
    } 
    // // printf("Ocall return: %d \n", ret);
    return ret;
}

int ocall_geterrno()	{
	return errno;
}

off_t ocall_write(int fd, const void *buf, size_t count)
{
	// // printf ("ocall_write %d, %p, %d\n", fd, buf, count);
    off_t ret = write(fd, buf, count);
    if (ret==-1)	{
    	// printf("The ocall_write error is: %s \n", strerror(errno));
    } 
    // // printf("Ocall return: %d \n", ret);
    return ret;    
}

off_t ocall_lseek(int fd, off_t offset, int whence)
{
	return lseek(fd, offset, whence);
}

int ocall_gethostname(char *name, size_t len)
{
    return gethostname(name, len);
}

int ocall_sethostname(const char *name, size_t len)
{
    return sethostname(name, len);
}

int ocall_close(int sock) 
{
    return close(sock);
}

pid_t ocall_getpid(void)
{
	return getpid();
}

pid_t ocall_getppid(void)
{
	return getppid();
}

ssize_t ocall_pread(int fd, void *buf, size_t nbytes, off_t offset)
{
	return pread(fd, buf, nbytes, offset);
}

ssize_t ocall_pwrite(int fd, const void *buf, size_t n, off_t offset)
{
	return pwrite(fd, buf, n, offset);
}

int ocall_pipe(int pipedes[2])
{
	return pipe(pipedes);
}

int ocall_pipe2(int pipedes[2], int flag)
{
	return pipe2(pipedes, flag);
}

unsigned int ocall_sleep(unsigned int seconds)
{
	return sleep(seconds);
}

unsigned int ocall_usleep(unsigned int seconds)
{
	return usleep(seconds);
}

int ocall_chown(const char *file, uid_t owner, gid_t group)
{
	return chown(file, owner, group);
}

int ocall_fchown(int fd, uid_t owner, gid_t group)
{
	return fchown(fd, owner, group);
}

int ocall_lchown(const char *file, uid_t owner, gid_t group)
{
	return lchown(file, owner, group);
}

int ocall_chdir(const char *path)
{
	return chdir(path);
}

int ocall_fchdir(int fd)
{
	return fchdir(fd);
}

char *ocall_get_current_dir_name(void)
{
	return get_current_dir_name();
}

int ocall_dup(int fd)
{
	return dup(fd);
}

int ocall_dup2(int fd, int fd2)
{
	return dup2(fd, fd2);
}

int ocall_dup3(int fd, int fd2, int flags)
{
	return dup3(fd, fd2, flags);
}
/* Get the real user ID of the calling process.  */
uid_t ocall_getuid(void)
{
	return getuid();
}

/* Get the effective user ID of the calling process.  */
uid_t ocall_geteuid(void)
{
	return geteuid();
}

/* Get the real group ID of the calling process.  */
gid_t ocall_getgid(void)
{
	return getgid();
}

/* Get the effective group ID of the calling process.  */
gid_t ocall_getegid(void)
{
	return getegid();
}

int ocall_getpagesize(void)
{
	return getpagesize();
}

char *ocall_getcwd(char *buf, size_t size)
{
	return getcwd(buf, size);
}

int ocall_unlink(const char *name)
{
	return unlink(name);
}

int ocall_rmdir(const char *name)
{
	return rmdir(name);
}

// Fork is not supported and should be remove from all the code. Call fork will bring enclave to power transition lost state
pid_t ocall_fork(void)
{
	// printf("\n Forking is not supported \n");
	abort();
	// return fork();
}

void ocall__exit(int status)
{
	return _exit(status);
}

long ocall_sysconf(int name)
{
	return sysconf(name);
}

int ocall_setgid(gid_t gid) 
{
	return setgid(gid);
}

int ocall_setuid(uid_t uid) 
{
	return setuid(uid);
}

int ocall_execvp(const char *file, const char **argv)
{
	return execvp(file, (char* const*)argv);
}

int ocall_ftruncate(int fd, off_t len)
{
	return ftruncate(fd, len);
}

void ocall_free(void* p)
{
	free(p);
}