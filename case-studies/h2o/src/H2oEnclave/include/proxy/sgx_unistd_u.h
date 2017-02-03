#ifndef SGX_UNISTD_U_H__
#define SGX_UNISTD_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "sgx/sys/types.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_gethostname, (char* name, size_t len));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sethostname, (const char* name, size_t len));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_lseek, (int fd, off_t offset, int whence));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_read, (int fd, void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_write, (int fd, const void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_read1, (int fd, void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_write1, (int fd, const void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_read2, (int fd, void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_write2, (int fd, const void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_read3, (int fd, void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_write3, (int fd, const void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_read4, (int fd, void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_write4, (int fd, const void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_read5, (int fd, void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_write5, (int fd, const void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_read6, (int fd, void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_write6, (int fd, const void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_read7, (int fd, void* buf, size_t count));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_write7, (int fd, const void* buf, size_t count));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_close, (int fd));
pid_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getpid, ());
pid_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getppid, ());
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pread, (int fd, void* buf, size_t nbytes, off_t offset));
ssize_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pwrite, (int fd, const void* buf, size_t n, off_t offset));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pipe, (int pipedes[2]));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pipe2, (int pipedes[2], int flag));
unsigned int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sleep, (unsigned int seconds));
unsigned int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_usleep, (unsigned int seconds));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_chown, (const char* file, uid_t owner, gid_t group));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fchown, (int fd, uid_t owner, gid_t group));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_lchown, (const char* file, uid_t owner, gid_t group));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_chdir, (const char* path));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fchdir, (int fd));
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_get_current_dir_name, ());
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_dup, (int fd));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_dup2, (int fd, int fd2));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_dup3, (int fd, int fd2, int flags));
uid_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getuid, ());
uid_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_geteuid, ());
gid_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getgid, ());
gid_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getegid, ());
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getpagesize, ());
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getcwd, (char* buf, size_t size));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_unlink, (const char* name));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_rmdir, (const char* name));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall__exit, (int stat));
long int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sysconf, (int name));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_setgid, (gid_t gid));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_setuid, (uid_t uid));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_execvp, (const char* file, const char** argv));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_ftruncate, (int fd, off_t len));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_free, (void* p));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_geterrno, ());


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
