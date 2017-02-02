#include <sgx_unistd_util.h>
#include <sgx_ocall_util.h>
#include <proxy/sgx_unistd_t.h>
#include <sgx_status.h>
#include "sgx_thread.h"

#include "H2oEnclave_t.h"

INIT_LOCK(ocall_gethostname);
INIT_LOCK(ocall_sethostname);
INIT_LOCK(ocall_lseek);
INIT_LOCK(ocall_read);
INIT_LOCK(ocall_read1);
INIT_LOCK(ocall_read2);
INIT_LOCK(ocall_read3);
INIT_LOCK(ocall_read4);
INIT_LOCK(ocall_read5);
INIT_LOCK(ocall_read6);
INIT_LOCK(ocall_read7);
INIT_LOCK(ocall_write);
INIT_LOCK(ocall_write1);
INIT_LOCK(ocall_write2);
INIT_LOCK(ocall_write3);
INIT_LOCK(ocall_write4);
INIT_LOCK(ocall_write5);
INIT_LOCK(ocall_write6);
INIT_LOCK(ocall_write7);
INIT_LOCK(ocall_close);

extern "C"	{

	int sgx_wrapper_gethostname(char *name, size_t len)
	{
		int retval;
		sgx_status_t status = SAFE_INVOKE(ocall_gethostname, &retval, name, len);
		CHECK_STATUS(status);		
		return retval;
	}

	int sgx_wrapper_sethostname(const char *name, size_t len)
	{
		int retval;
		sgx_status_t status = SAFE_INVOKE(ocall_sethostname, &retval, name, len);
		CHECK_STATUS(status);	
		return retval;
	}
	 
	long sgx_wrapper_lseek(int fd, long offset, int whence)
	{
		long retval;
		sgx_status_t status = SAFE_INVOKE(ocall_lseek, &retval, fd, offset, whence);
		CHECK_STATUS(status);
		return retval;
	}

	long sgx_wrapper_read(int fd, void *buf, size_t count)
	{
		sgx_status_t status;
		long tmp = sgx_thread_self()%17;
		int k = tmp%8;
		long retval;
		switch(k)	{
			case 0:
				status = SAFE_INVOKE(ocall_read, &retval, fd, buf, count);
				CHECK_STATUS(status);
				break;
			case 1:
				status = SAFE_INVOKE(ocall_read1, &retval, fd, buf, count);
				CHECK_STATUS(status);				
				break;
			case 2:
				status = SAFE_INVOKE(ocall_read2, &retval, fd, buf, count);
				CHECK_STATUS(status);				
				break;
			case 3:
				status = SAFE_INVOKE(ocall_read3, &retval, fd, buf, count);
				CHECK_STATUS(status);				
				break;			
			case 4:
				status = SAFE_INVOKE(ocall_read4, &retval, fd, buf, count);
				CHECK_STATUS(status);				
				break;
			case 5:
				status = SAFE_INVOKE(ocall_read5, &retval, fd, buf, count);
				CHECK_STATUS(status);				
				break;
			case 6:
				status = SAFE_INVOKE(ocall_read6, &retval, fd, buf, count);
				CHECK_STATUS(status);			
				break;
			case 7:
				status = SAFE_INVOKE(ocall_read7, &retval, fd, buf, count);
				CHECK_STATUS(status);				
				break;
		}
		
		return retval;
	}

	long sgx_wrapper_write(int fd, const void *buf, size_t count)
	{
		sgx_status_t status;
		long tmp = sgx_thread_self()%17;
		int k = tmp%8;
		long retval;
		switch(k)	{
			case 0:
				status = SAFE_INVOKE(ocall_write, &retval, fd, buf, count);
				CHECK_STATUS(status);			
				break;
			case 1:
				status = SAFE_INVOKE(ocall_write1, &retval, fd, buf, count);
				CHECK_STATUS(status);				
				break;
			case 2:
				status = SAFE_INVOKE(ocall_write2, &retval, fd, buf, count);
				CHECK_STATUS(status);
				break;
			case 3:
				status = SAFE_INVOKE(ocall_write3, &retval, fd, buf, count);
				CHECK_STATUS(status);
				break;	
			case 4:
				status = SAFE_INVOKE(ocall_write4, &retval, fd, buf, count);
				CHECK_STATUS(status);
				break;
			case 5:
				status = SAFE_INVOKE(ocall_write5, &retval, fd, buf, count);
				CHECK_STATUS(status);
				break;
			case 6:
				status = SAFE_INVOKE(ocall_write6, &retval, fd, buf, count);
				CHECK_STATUS(status);
				break;
			case 7:
				status = SAFE_INVOKE(ocall_write7, &retval, fd, buf, count);
				CHECK_STATUS(status);
				break;						
		}
		return retval;
	}

	int sgx_wrapper_close(int fd)
	{
		int retval;
		sgx_status_t status = SAFE_INVOKE(ocall_close, &retval, fd);
		CHECK_STATUS(status);
		return retval;
	}

	pid_t sgx_wrapper_getpid(void)
	{
		pid_t retval;
		sgx_status_t status = ocall_getpid(&retval);
		CHECK_STATUS(status);
		return retval;
	}

	pid_t sgx_wrapper_getppid(void)
	{
		pid_t retval;
		sgx_status_t status = ocall_getppid(&retval);
		CHECK_STATUS(status);
		return retval;
	}

	ssize_t sgx_wrapper_pread(int fd, void *buf, size_t nbytes, off_t offset)
	{
		ssize_t retval;
		sgx_status_t status = ocall_pread(&retval, fd, buf, nbytes, offset);
		CHECK_STATUS(status);
		return retval;
	}

	ssize_t sgx_wrapper_pwrite(int fd, const void *buf, size_t n, off_t offset)
	{
		ssize_t retval;
		sgx_status_t status = ocall_pwrite(&retval, fd, buf, n, offset);
		CHECK_STATUS(status);
		return retval;
	}

	char *sgx_wrapper_get_current_dir_name(void)
	{
		char* retval;
		sgx_status_t status = ocall_get_current_dir_name(&retval);
		CHECK_STATUS(status);
		return retval;
	}

	unsigned int sgx_wrapper_sleep(unsigned int seconds)
	{
		unsigned int retval;
		sgx_status_t status = ocall_sleep(&retval, seconds);
		CHECK_STATUS(status);
		return retval;
	}

	unsigned int sgx_wrapper_usleep(unsigned int seconds)
	{
		unsigned int retval;
		sgx_status_t status = ocall_usleep(&retval, seconds);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_pipe(int pipedes[2])
	{
		int retval;
		sgx_status_t status = ocall_pipe(&retval, pipedes);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_pipe2(int pipedes[2], int flag)
	{
		int retval;
		sgx_status_t status = ocall_pipe2(&retval, pipedes, flag);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_chown(const char *file, uid_t owner, gid_t group)
	{
		int retval;
		sgx_status_t status = ocall_chown(&retval, file, owner, group);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_fchown(int fd, uid_t owner, gid_t group)
	{
		int retval;
		sgx_status_t status = ocall_fchown(&retval, fd, owner, group);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_lchown(const char *file, uid_t owner, gid_t group)
	{
		int retval;
		sgx_status_t status = ocall_lchown(&retval, file, owner, group);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_chdir(const char *path)
	{
		int retval;
		sgx_status_t status = ocall_chdir(&retval, path);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_fchdir(int fd)
	{
		int retval;
		sgx_status_t status = ocall_fchdir(&retval, fd);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_dup(int fd)
	{
		int retval;
		sgx_status_t status = ocall_dup(&retval, fd);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_dup2(int fd, int fd2)
	{
		int retval;
		sgx_status_t status = ocall_dup2(&retval, fd, fd2);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_dup3(int fd, int fd2, int flags)
	{
		int retval;
		sgx_status_t status = ocall_dup3(&retval, fd, fd2, flags);
		CHECK_STATUS(status);
		return retval;
	}
	/* Get the real user ID of the calling process.  */
	uid_t sgx_wrapper_getuid(void)
	{
		uid_t retval;
		sgx_status_t status = ocall_getuid(&retval);
		CHECK_STATUS(status);
		return retval;
	}

	/* Get the effective user ID of the calling process.  */
	uid_t sgx_wrapper_geteuid(void)
	{
		uid_t retval;
		sgx_status_t status = ocall_geteuid(&retval);
		CHECK_STATUS(status);
		return retval;
	}

	/* Get the real group ID of the calling process.  */
	gid_t sgx_wrapper_getgid(void)
	{
		gid_t retval;
		sgx_status_t status = ocall_getgid(&retval);
		CHECK_STATUS(status);
		return retval;
	}

	/* Get the effective group ID of the calling process.  */
	gid_t sgx_wrapper_getegid(void)
	{
		gid_t retval;
		sgx_status_t status = ocall_getegid(&retval);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_getpagesize(void)
	{
		int retval;
		sgx_status_t status = ocall_getpagesize(&retval);
		CHECK_STATUS(status);
		return retval;
	}

	char *sgx_wrapper_getcwd(char *buf, size_t size)
	{
		char *retval;
		sgx_status_t status = ocall_getcwd(&retval, buf, size);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_unlink(const char *name)
	{
		int retval;
		sgx_status_t status = ocall_unlink(&retval, name);
		CHECK_STATUS(status);
		return retval;
	}


	int sgx_wrapper_rmdir(const char *name)
	{
		int retval;
		sgx_status_t status = ocall_rmdir(&retval, name);
		CHECK_STATUS(status);
		return retval;
	}


	void sgx_wrapper__exit(int status)
	{

		// int retval;
		// sgx_status_t status = ocall__exit(&retval, status);
		// return retval;
		ocall__exit(status);
	}

	long sgx_wrapper_sysconf(int name)
	{
		long retval;
		sgx_status_t status = ocall_sysconf(&retval, name);
		CHECK_STATUS(status);
		return retval;
	}



	int sgx_wrapper_setuid(uid_t uid)
	{
		int retval;
		sgx_status_t status = ocall_setuid(&retval, uid);
		CHECK_STATUS(status);
		return retval;
	}


	int sgx_wrapper_setgid(gid_t gid)
	{
		int retval;
		sgx_status_t status = ocall_setgid(&retval, gid);
		CHECK_STATUS(status);
		return retval;
	}

}