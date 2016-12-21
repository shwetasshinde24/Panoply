// #include <replacements/sgx_stdio_util.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>

#include "TopensslEnclave_u.h"

extern void increase_ocall_count();

off_t ocall_read(int fd, void *buf, size_t count)
{
    increase_ocall_count();
	// // printf ("ocall_read %d, %p, %d\n", fd, buf, count);
    off_t ret = read(fd, buf, count);
    if (ret==-1)	{
    	// printf("The ocall_read error is: %s \n", strerror(errno));
    } 
    // // printf("Ocall return: %d \n", ret);
    return ret;
}

int ocall_geterrno()	
{
    increase_ocall_count();
	return errno;
}

off_t ocall_write(int fd, const void *buf, size_t count)
{
    increase_ocall_count();
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
    increase_ocall_count();
	return lseek(fd, offset, whence);
}

int ocall_gethostname(char *name, size_t len)
{
    increase_ocall_count();
    return gethostname(name, len);
}

int ocall_sethostname(const char *name, size_t len)
{
    increase_ocall_count();
    return sethostname(name, len);
}

int ocall_close(int sock) 
{
    increase_ocall_count();
    return close(sock);
}

pid_t ocall_getpid(void)
{
    increase_ocall_count();
	return getpid();
}

pid_t ocall_getppid(void)
{
    increase_ocall_count();
	return getppid();
}

ssize_t ocall_pread(int fd, void *buf, size_t nbytes, off_t offset)
{
    increase_ocall_count();
	return pread(fd, buf, nbytes, offset);
}

ssize_t ocall_pwrite(int fd, const void *buf, size_t n, off_t offset)
{
    increase_ocall_count();
	return pwrite(fd, buf, n, offset);
}

int ocall_pipe(int pipedes[2])
{
    increase_ocall_count();
	return pipe(pipedes);
}

int ocall_pipe2(int pipedes[2], int flag)
{
    increase_ocall_count();
	return pipe2(pipedes, flag);
}

unsigned int ocall_sleep(unsigned int seconds)
{
    increase_ocall_count();
	return sleep(seconds);
}

unsigned int ocall_usleep(unsigned int seconds)
{
    increase_ocall_count();
	return usleep(seconds);
}

int ocall_chown(const char *file, uid_t owner, gid_t group)
{
    increase_ocall_count();
	return chown(file, owner, group);
}

int ocall_fchown(int fd, uid_t owner, gid_t group)
{
    increase_ocall_count();
	return fchown(fd, owner, group);
}

int ocall_lchown(const char *file, uid_t owner, gid_t group)
{
    increase_ocall_count();
	return lchown(file, owner, group);
}

int ocall_chdir(const char *path)
{
    increase_ocall_count();
	return chdir(path);
}

int ocall_fchdir(int fd)
{
    increase_ocall_count();
	return fchdir(fd);
}

char *ocall_get_current_dir_name(void)
{
    increase_ocall_count();
	return get_current_dir_name();
}

int ocall_dup(int fd)
{
    increase_ocall_count();
	return dup(fd);
}

int ocall_dup2(int fd, int fd2)
{
    increase_ocall_count();
	return dup2(fd, fd2);
}

int ocall_dup3(int fd, int fd2, int flags)
{
    increase_ocall_count();
	return dup3(fd, fd2, flags);
}
/* Get the real user ID of the calling process.  */
uid_t ocall_getuid(void)
{
    increase_ocall_count();
	return getuid();
}

/* Get the effective user ID of the calling process.  */
uid_t ocall_geteuid(void)
{
    increase_ocall_count();
	return geteuid();
}

/* Get the real group ID of the calling process.  */
gid_t ocall_getgid(void)
{
    increase_ocall_count();
	return getgid();
}

/* Get the effective group ID of the calling process.  */
gid_t ocall_getegid(void)
{
    increase_ocall_count();
	return getegid();
}

int ocall_getpagesize(void)
{
    increase_ocall_count();
	return getpagesize();
}

char *ocall_getcwd(char *buf, size_t size)
{
    increase_ocall_count();
	return getcwd(buf, size);
}

int ocall_unlink(const char *name)
{
    increase_ocall_count();
	return unlink(name);
}

int ocall_rmdir(const char *name)
{
    increase_ocall_count();
	return rmdir(name);
}

// Fork is not supported and should be remove from all the code. Call fork will bring enclave to power transition lost state
pid_t ocall_fork(void)
{
    increase_ocall_count();
	// printf("\n Forking is not supported \n");
	abort();
	// return fork();
}

void ocall__exit(int status)
{
    increase_ocall_count();
	return _exit(status);
}

long ocall_sysconf(int name)
{
    increase_ocall_count();
	return sysconf(name);
}

int ocall_setgid(gid_t gid) 
{
    increase_ocall_count();
	return setgid(gid);
}

int ocall_setuid(uid_t uid) 
{
    increase_ocall_count();
	return setuid(uid);
}

int ocall_execvp(const char *file, const char **argv)
{
    increase_ocall_count();
	return execvp(file, (char* const*)argv);
}

int ocall_ftruncate(int fd, off_t len)
{
    increase_ocall_count();
	return ftruncate(fd, len);
}

void ocall_free(void* p)
{
    increase_ocall_count();
	free(p);
}