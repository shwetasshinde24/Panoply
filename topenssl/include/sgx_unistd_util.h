#ifndef SGX_UNISTD_UTIL_H
#define SGX_UNISTD_UTIL_H
#include "struct/sgx_unistd_struct.h"
#include "proxy/sgx_unistd_t.h"

static inline int sgx_wrapper_gethostname(char *name, size_t len)
{
	int retval;
	ocall_gethostname(&retval, name, len);
	return retval;
}
static inline int sgx_wrapper_sethostname(const char *name, size_t len)
{
	int retval;
	ocall_sethostname(&retval, name, len);
	return retval;
}
 
static inline long sgx_wrapper_lseek(int fd, long offset, int whence)
{
	long retval;
	ocall_lseek(&retval, fd, offset, whence);
	return retval;
}

static inline long sgx_wrapper_read(int fd, void *buf, size_t count)
{
	long retval;
	ocall_read(&retval, fd, buf, count);
	return retval;
}

static inline long sgx_wrapper_write(int fd, const void *buf, size_t count)
{
	long retval;
	ocall_write(&retval, fd, buf, count);
	return retval;
}
static inline int sgx_wrapper_close(int fd)
{
	int retval;
	ocall_close(&retval, fd);
	return retval;
}

static inline pid_t sgx_wrapper_getpid(void)
{
	pid_t retval;
	ocall_getpid(&retval);
	return retval;
}

static inline pid_t sgx_wrapper_getppid(void)
{
	pid_t retval;
	ocall_getppid(&retval);
	return retval;
}

static inline ssize_t sgx_wrapper_pread(int fd, void *buf, size_t nbytes, off_t offset)
{
	ssize_t retval;
	ocall_pread(&retval, fd, buf, nbytes, offset);
	return retval;
}

static inline ssize_t sgx_wrapper_pwrite(int fd, const void *buf, size_t n, off_t offset)
{
	ssize_t retval;
	ocall_pwrite(&retval, fd, buf, n, offset);
	return retval;
}

static inline char *sgx_wrapper_get_current_dir_name(void)
{
	char* retval;
	ocall_get_current_dir_name(&retval);
	return retval;
}

static inline unsigned int sgx_wrapper_sleep(unsigned int seconds)
{
	unsigned int retval;
	ocall_sleep(&retval, seconds);
	return retval;
}

static inline unsigned int sgx_wrapper_usleep(unsigned int seconds)
{
	unsigned int retval;
	ocall_usleep(&retval, seconds);
	return retval;
}

static inline int sgx_wrapper_pipe(int pipedes[2])
{
	int retval;
	ocall_pipe(&retval, pipedes);
	return retval;
}

static inline int sgx_wrapper_pipe2(int pipedes[2], int flag)
{
	int retval;
	ocall_pipe2(&retval, pipedes, flag);
	return retval;
}

static inline int sgx_wrapper_chown(const char *file, uid_t owner, gid_t group)
{
	int retval;
	ocall_chown(&retval, file, owner, group);
	return retval;
}

static inline int sgx_wrapper_fchown(int fd, uid_t owner, gid_t group)
{
	int retval;
	ocall_fchown(&retval, fd, owner, group);
	return retval;
}

static inline int sgx_wrapper_lchown(const char *file, uid_t owner, gid_t group)
{
	int retval;
	ocall_lchown(&retval, file, owner, group);
	return retval;
}

static inline int sgx_wrapper_chdir(const char *path)
{
	int retval;
	ocall_chdir(&retval, path);
	return retval;
}

static inline int sgx_wrapper_fchdir(int fd)
{
	int retval;
	ocall_fchdir(&retval, fd);
	return retval;
}

static inline int sgx_wrapper_dup(int fd)
{
	int retval;
	ocall_dup(&retval, fd);
	return retval;
}

static inline int sgx_wrapper_dup2(int fd, int fd2)
{
	int retval;
	ocall_dup2(&retval, fd, fd2);
	return retval;
}

static inline int sgx_wrapper_dup3(int fd, int fd2, int flags)
{
	int retval;
	ocall_dup3(&retval, fd, fd2, flags);
	return retval;
}
/* Get the real user ID of the calling process.  */
static inline uid_t sgx_wrapper_getuid(void)
{
	uid_t retval;
	ocall_getuid(&retval);
	return retval;
}

/* Get the effective user ID of the calling process.  */
static inline uid_t sgx_wrapper_geteuid(void)
{
	uid_t retval;
	ocall_geteuid(&retval);
	return retval;
}

/* Get the real group ID of the calling process.  */
static inline gid_t sgx_wrapper_getgid(void)
{
	gid_t retval;
	ocall_getgid(&retval);
	return retval;
}

/* Get the effective group ID of the calling process.  */
static inline gid_t sgx_wrapper_getegid(void)
{
	gid_t retval;
	ocall_getegid(&retval);
	return retval;
}

static inline int sgx_wrapper_getpagesize(void)
{
	int retval;
	ocall_getpagesize(&retval);
	return retval;
}

static inline char *sgx_wrapper_getcwd(char *buf, size_t size)
{
	char *retval;
	ocall_getcwd(&retval, buf, size);
	return retval;
}

static inline int sgx_wrapper_unlink(const char *name)
{
	int retval;
	ocall_unlink(&retval, name);
	return retval;
}


static inline int sgx_wrapper_rmdir(const char *name)
{
	int retval;
	ocall_rmdir(&retval, name);
	return retval;
}


static inline void sgx_wrapper__exit(int status)
{

	// int retval;
	// ocall__exit(&retval, status);
	// return retval;
	ocall__exit(status);
}

static inline long sgx_wrapper_sysconf(int name)
{
	long retval;
	ocall_sysconf(&retval, name);
	return retval;
}



static inline int sgx_wrapper_setuid(uid_t uid)
{
	int retval;
	ocall_setuid(&retval, uid);
	return retval;
}


static inline int sgx_wrapper_setgid(gid_t gid)
{
	int retval;
	ocall_setgid(&retval, gid);
	return retval;
}


/* Standard file descriptors.  */
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */


#define gethostname(A, B) sgx_wrapper_gethostname(A, B)
#define sethostname(A, B) sgx_wrapper_sethostname(A, B)
#define read(A, B, C) sgx_wrapper_read(A, B, C)
#define write(A, B, C) sgx_wrapper_write(A, B, C)
#define close(A) sgx_wrapper_close(A)
#define lseek(A, B, C) sgx_wrapper_lseek(A, B, C)
#define getpid() sgx_wrapper_getpid()
#define getppid() sgx_wrapper_getppid()
#define pread(A, B, C, D) sgx_wrapper_pread(A, B, C, D)
#define pwrite(A, B, C, D) sgx_wrapper_pwrite(A, B, C, D)
#define pipe(A) sgx_wrapper_pipe(A)
#define pipe2(A,B) sgx_wrapper_pipe2(A,B)
#define sleep(A) sgx_wrapper_sleep(A)
#define usleep(A) sgx_wrapper_usleep(A)
#define chown(A, B, C) sgx_wrapper_chown(A, B, C)
#define fchown(A, B, C) sgx_wrapper_fchown(A, B, C)
#define lchown(A, B, C) sgx_wrapper_lchown(A, B, C)
#define chdir(A) sgx_wrapper_chdir(A)
#define fchdir(A) sgx_wrapper_fchdir(A)
#define get_current_dir_name() sgx_wrapper_get_current_dir_name()
#define dup(A) sgx_wrapper_dup(A)
#define dup2(A, B) sgx_wrapper_dup2(A, B)
#define dup3(A, B, C) sgx_wrapper_dup3(A, B, C)
#define getuid() sgx_wrapper_getuid()
#define geteuid() sgx_wrapper_geteuid()
#define getgid() sgx_wrapper_getgid()
#define getegid() sgx_wrapper_getegid()
#define getpagesize() sgx_wrapper_getpagesize()
#define getcwd(A, B) sgx_wrapper_getcwd(A, B)
#define unlink(A) sgx_wrapper_unlink(A)
#define rmdir(A) sgx_wrapper_rmdir(A)
#define _exit(A) sgx_wrapper__exit(A)
#define sysconf(A) sgx_wrapper_sysconf(A)
#define setuid(A) sgx_wrapper_setuid(A)
#define setgid(A) sgx_wrapper_setgid(A)

#endif

