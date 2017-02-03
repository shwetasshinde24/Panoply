#ifndef SGX_UNISTD_T_H__
#define SGX_UNISTD_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "sgx/sys/types.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_gethostname(int* retval, char* name, size_t len);
sgx_status_t SGX_CDECL ocall_sethostname(int* retval, const char* name, size_t len);
sgx_status_t SGX_CDECL ocall_lseek(off_t* retval, int fd, off_t offset, int whence);
sgx_status_t SGX_CDECL ocall_read(off_t* retval, int fd, void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_write(off_t* retval, int fd, const void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_read1(off_t* retval, int fd, void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_write1(off_t* retval, int fd, const void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_read2(off_t* retval, int fd, void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_write2(off_t* retval, int fd, const void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_read3(off_t* retval, int fd, void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_write3(off_t* retval, int fd, const void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_read4(off_t* retval, int fd, void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_write4(off_t* retval, int fd, const void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_read5(off_t* retval, int fd, void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_write5(off_t* retval, int fd, const void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_read6(off_t* retval, int fd, void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_write6(off_t* retval, int fd, const void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_read7(off_t* retval, int fd, void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_write7(off_t* retval, int fd, const void* buf, size_t count);
sgx_status_t SGX_CDECL ocall_close(int* retval, int fd);
sgx_status_t SGX_CDECL ocall_getpid(pid_t* retval);
sgx_status_t SGX_CDECL ocall_getppid(pid_t* retval);
sgx_status_t SGX_CDECL ocall_pread(ssize_t* retval, int fd, void* buf, size_t nbytes, off_t offset);
sgx_status_t SGX_CDECL ocall_pwrite(ssize_t* retval, int fd, const void* buf, size_t n, off_t offset);
sgx_status_t SGX_CDECL ocall_pipe(int* retval, int pipedes[2]);
sgx_status_t SGX_CDECL ocall_pipe2(int* retval, int pipedes[2], int flag);
sgx_status_t SGX_CDECL ocall_sleep(unsigned int* retval, unsigned int seconds);
sgx_status_t SGX_CDECL ocall_usleep(unsigned int* retval, unsigned int seconds);
sgx_status_t SGX_CDECL ocall_chown(int* retval, const char* file, uid_t owner, gid_t group);
sgx_status_t SGX_CDECL ocall_fchown(int* retval, int fd, uid_t owner, gid_t group);
sgx_status_t SGX_CDECL ocall_lchown(int* retval, const char* file, uid_t owner, gid_t group);
sgx_status_t SGX_CDECL ocall_chdir(int* retval, const char* path);
sgx_status_t SGX_CDECL ocall_fchdir(int* retval, int fd);
sgx_status_t SGX_CDECL ocall_get_current_dir_name(char** retval);
sgx_status_t SGX_CDECL ocall_dup(int* retval, int fd);
sgx_status_t SGX_CDECL ocall_dup2(int* retval, int fd, int fd2);
sgx_status_t SGX_CDECL ocall_dup3(int* retval, int fd, int fd2, int flags);
sgx_status_t SGX_CDECL ocall_getuid(uid_t* retval);
sgx_status_t SGX_CDECL ocall_geteuid(uid_t* retval);
sgx_status_t SGX_CDECL ocall_getgid(gid_t* retval);
sgx_status_t SGX_CDECL ocall_getegid(gid_t* retval);
sgx_status_t SGX_CDECL ocall_getpagesize(int* retval);
sgx_status_t SGX_CDECL ocall_getcwd(char** retval, char* buf, size_t size);
sgx_status_t SGX_CDECL ocall_unlink(int* retval, const char* name);
sgx_status_t SGX_CDECL ocall_rmdir(int* retval, const char* name);
sgx_status_t SGX_CDECL ocall__exit(int stat);
sgx_status_t SGX_CDECL ocall_sysconf(long int* retval, int name);
sgx_status_t SGX_CDECL ocall_setgid(int* retval, gid_t gid);
sgx_status_t SGX_CDECL ocall_setuid(int* retval, uid_t uid);
sgx_status_t SGX_CDECL ocall_execvp(int* retval, const char* file, const char** argv);
sgx_status_t SGX_CDECL ocall_ftruncate(int* retval, int fd, off_t len);
sgx_status_t SGX_CDECL ocall_free(void* p);
sgx_status_t SGX_CDECL ocall_geterrno(int* retval);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
