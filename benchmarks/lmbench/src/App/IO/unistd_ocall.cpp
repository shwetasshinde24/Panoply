/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include "sgx_urts.h"
#include <thpool.h>
#include <pthread.h>

#include "MyEnclave_u.h"

int ocall_geterrno()	{
	return errno;
}

#define SGXBUFSIZ 20480000
static char readbuf[SGXBUFSIZ];
static char writebuf[SGXBUFSIZ];

threadpool socket_thpool = thpool_init(2);

int get_buff_addr(size_t arr[2])
{
    arr[0] = (size_t)readbuf;
    arr[1] = (size_t)writebuf;
}

off_t ocall_fast_read(int fd, size_t count)
{
    if (count > SGXBUFSIZ)  {
        fprintf(stderr, "Need more readbuf \n");
        return -1;
    }
    off_t ret = read(fd, readbuf, count);
    return ret;
}

off_t ocall_fast_write(int fd, size_t count)
{
    off_t ret = write(fd, writebuf, count);
    return ret;
}

off_t ocall_read(int fd, void *buf, size_t count)
{
	// printf ("ocall_read %d, %p, %d\n", fd, buf, count);
    off_t ret = read(fd, buf, count);
    if (ret==-1)	{
    	printf("The ocall_read error is: %s \n", strerror(errno));
    } 
    return ret;
}

off_t ocall_write(int fd, const void *buf, size_t count)
{
	// printf ("ocall_write %d, %p, %d\n", fd, buf, count);
    off_t ret = write(fd, buf, count);
    return ret;    
}

off_t ocall_read1(int fd, void *buf, size_t count)
{
	// printf ("ocall_read1 %d, %p, %d\n", fd, buf, count);
    off_t ret = read(fd, buf, count);
    if (ret==-1)	{
    	printf("The ocall_read error is: %s \n", strerror(errno));
    } 
    return ret;
}

off_t ocall_write1(int fd, const void *buf, size_t count)
{
	// printf ("ocall_write1 %d, %p, %d\n", fd, buf, count);
    off_t ret = write(fd, buf, count);
    return ret;    
}

off_t ocall_read2(int fd, void *buf, size_t count)
{
	// printf ("ocall_read2 %d, %p, %d\n", fd, buf, count);
    off_t ret = read(fd, buf, count);
    if (ret==-1)	{
    	printf("The ocall_read error is: %s \n", strerror(errno));
    } 
    return ret;
}

off_t ocall_write2(int fd, const void *buf, size_t count)
{
	// printf ("ocall_write2 %d, %p, %d\n", fd, buf, count);
    off_t ret = write(fd, buf, count);
    return ret;    
}

off_t ocall_read3(int fd, void *buf, size_t count)
{
	// printf ("ocall_read3 %d, %p, %d\n", fd, buf, count);
    off_t ret = read(fd, buf, count);
    if (ret==-1)	{
    	printf("The ocall_read error is: %s \n", strerror(errno));
    } 
    return ret;
}

off_t ocall_write3(int fd, const void *buf, size_t count)
{
	// printf ("ocall_write3 %d, %p, %d\n", fd, buf, count);
    off_t ret = write(fd, buf, count);
    return ret;    
}

off_t ocall_read4(int fd, void *buf, size_t count)
{
	// printf ("ocall_read3 %d, %p, %d\n", fd, buf, count);
    off_t ret = read(fd, buf, count);
    if (ret==-1)	{
    	printf("The ocall_read error is: %s \n", strerror(errno));
    } 
    return ret;
}

off_t ocall_write4(int fd, const void *buf, size_t count)
{
	// printf ("ocall_write3 %d, %p, %d\n", fd, buf, count);
    off_t ret = write(fd, buf, count);
    return ret;    
}

off_t ocall_read5(int fd, void *buf, size_t count)
{
	// printf ("ocall_read3 %d, %p, %d\n", fd, buf, count);
    off_t ret = read(fd, buf, count);
    if (ret==-1)	{
    	printf("The ocall_read error is: %s \n", strerror(errno));
    } 
    return ret;
}

off_t ocall_write5(int fd, const void *buf, size_t count)
{
	// printf ("ocall_write3 %d, %p, %d\n", fd, buf, count);
    off_t ret = write(fd, buf, count);
    return ret;    
}

off_t ocall_read6(int fd, void *buf, size_t count)
{
	// printf ("ocall_read3 %d, %p, %d\n", fd, buf, count);
    off_t ret = read(fd, buf, count);
    if (ret==-1)	{
    	printf("The ocall_read error is: %s \n", strerror(errno));
    } 
    return ret;
}

off_t ocall_write6(int fd, const void *buf, size_t count)
{
	// printf ("ocall_write3 %d, %p, %d\n", fd, buf, count);
    off_t ret = write(fd, buf, count);
    return ret;    
}

off_t ocall_read7(int fd, void *buf, size_t count)
{
	// printf ("ocall_read3 %d, %p, %d\n", fd, buf, count);
    off_t ret = read(fd, buf, count);
    if (ret==-1)	{
    	printf("The ocall_read error is: %s \n", strerror(errno));
    } 
    return ret;
}

off_t ocall_write7(int fd, const void *buf, size_t count)
{
	// printf ("ocall_write3 %d, %p, %d\n", fd, buf, count);
    off_t ret = write(fd, buf, count);
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
    pid_t mypid = getpid();
    // printf("ocall_getpid is: %d \n", mypid);
	return mypid;
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
    int ret = pipe(pipedes);
    return ret;
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

void ocall__exit(int status, int eid)
{
    sgx_destroy_enclave(eid);
    exit(status);
	// return _exit(status);
}

void ocall_exit(int status, int eid)
{
    sgx_destroy_enclave(eid);
    exit(status);
    // return _exit(status);
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
    printf("Call ocall_execvp - %s \n", file);
	int m = execvp(file, (char* const*)argv);

    if (m<0)    {
        printf("Execvp does not suceed %d \n", m);
        printf("The error is: %s \n", strerror(errno));
    }

    return m;
}

int ocall_ftruncate(int fd, off_t len)
{
	return ftruncate(fd, len);
}

void ocall_free(void* p)
{
	free(p);
}

int ocall_fsync(int fd)
{
    return fsync(fd);
}

unsigned int ocall_alarm(unsigned int seconds)
{
    return alarm(seconds);
}

int ocall_copy_arg(void* buff, int buff_size, char **argv, int index)
{
    char* s = argv[index];
    int len = strlen(s)+1;
    printf("Copy arg should return: %s -- %d \n", s, index);
    if (strlen(s)>buff_size || buff_size<=0)
        return -1;

    strncpy((char *)buff, s, len);

    return len;
}

int ocall_mknod(const char *pathname, mode_t mode, dev_t dev)
{
    return mknod(pathname, mode, dev);
}

void* ocall_malloc(int n)
{
    return malloc(n);
}

void printf_string(char* s)
{
    printf("%s \n", s);
}