#ifndef SGX_UNISTD_UTIL_H
#define SGX_UNISTD_UTIL_H
#include "struct/sgx_unistd_struct.h"
#include "proxy/sgx_unistd_t.h"
#include "sgx_thread.h"

#ifdef __cplusplus
extern "C"	{
#endif 

extern int sgx_wrapper_gethostname(char *name, size_t len);
extern int sgx_wrapper_sethostname(const char *name, size_t len);
extern long sgx_wrapper_lseek(int fd, long offset, int whence);
extern long sgx_wrapper_read(int fd, void *buf, size_t count);
extern long sgx_wrapper_write(int fd, const void *buf, size_t count);
extern int sgx_wrapper_close(int fd);
extern pid_t sgx_wrapper_getpid(void);
extern pid_t sgx_wrapper_getppid(void);
extern ssize_t sgx_wrapper_pread(int fd, void *buf, size_t nbytes, off_t offset);
extern ssize_t sgx_wrapper_pwrite(int fd, const void *buf, size_t n, off_t offset);
extern char *sgx_wrapper_get_current_dir_name(void);
extern unsigned int sgx_wrapper_sleep(unsigned int seconds);
extern unsigned int sgx_wrapper_usleep(unsigned int seconds);
extern int sgx_wrapper_pipe(int pipedes[2]);
extern int sgx_wrapper_pipe2(int pipedes[2], int flag);
extern int sgx_wrapper_chown(const char *file, uid_t owner, gid_t group);
extern int sgx_wrapper_fchown(int fd, uid_t owner, gid_t group);
extern int sgx_wrapper_lchown(const char *file, uid_t owner, gid_t group);
extern int sgx_wrapper_chdir(const char *path);
extern int sgx_wrapper_fchdir(int fd);
extern int sgx_wrapper_dup(int fd);
extern int sgx_wrapper_dup2(int fd, int fd2);
extern int sgx_wrapper_dup3(int fd, int fd2, int flags);
/* Get the real user ID of the calling process.  */
extern uid_t sgx_wrapper_getuid(void);
/* Get the effective user ID of the calling process.  */
extern uid_t sgx_wrapper_geteuid(void);
/* Get the real group ID of the calling process.  */
extern gid_t sgx_wrapper_getgid(void);
/* Get the effective group ID of the calling process.  */
extern gid_t sgx_wrapper_getegid(void);
extern int sgx_wrapper_getpagesize(void);
extern char *sgx_wrapper_getcwd(char *buf, size_t size);
extern int sgx_wrapper_unlink(const char *name);
extern int sgx_wrapper_rmdir(const char *name);
extern void sgx_wrapper__exit(int status);
extern long sgx_wrapper_sysconf(int name);
extern int sgx_wrapper_setuid(uid_t uid);
extern int sgx_wrapper_setgid(gid_t gid);

#ifdef __cplusplus
}
#endif 


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

