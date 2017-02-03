#include <sgx_fcntl_util.h>
#include <sgx_ocall_util.h>
#include <sgx_thread.h>

INIT_LOCK(ocall_open2);
INIT_LOCK(ocall_creat);
INIT_LOCK(ocall_openat2);
INIT_LOCK(ocall_fcntl1);
INIT_LOCK(ocall_fcntl2);
INIT_LOCK(ocall_fcntl3);

int sgx_wrapper_open(const char *pathname, int flags, ...)
{
    va_list ap; 
    mode_t mode = 0;
 	va_start(ap, flags); 
    if (flags & O_CREAT)
        mode = va_arg(ap, mode_t); 
    else
        mode = 0777;
    va_end(ap); 	
	int retval;
	sgx_status_t status = SAFE_INVOKE(ocall_open2, &retval, pathname, flags, mode);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_creat(const char *pathname, unsigned int mode)
{
	int retval;
	sgx_status_t status = SAFE_INVOKE(ocall_creat, &retval, pathname, mode);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_openat(int dirfd, const char *pathname, int flags, ...)
{
    va_list ap; 
    mode_t mode = 0;
 	va_start(ap, flags); 
    if (flags & O_CREAT)
        mode = va_arg(ap, mode_t); 
    else
        mode = 0777;
    va_end(ap); 
	int retval;
	sgx_status_t status = SAFE_INVOKE(ocall_openat2, &retval, dirfd, pathname, flags, mode);
	CHECK_STATUS(status);
	return retval;	
}

int sgx_wrapper_fcntl(int fd, int cmd, ...)
{
	sgx_status_t status;
	va_list ap;
	int retval;
	va_start(ap, cmd); 
	long larg = -1;
	struct flock *flarg = NULL;
	// Fix me: Should refer to the linux kernel in order to do it in the right way
	switch(cmd)	{
		case F_GETFD:
		case F_GETFL:
		case F_GETOWN:
			va_end(ap);
			status = SAFE_INVOKE(ocall_fcntl1, &retval, fd, cmd);
			CHECK_STATUS(status);
			return retval;
		case F_DUPFD:
		case F_DUPFD_CLOEXEC:
		case F_SETFD:
		case F_SETFL:
		case F_SETOWN:
			larg = va_arg(ap, long);
			// fprintf(stderr, "fcntl setfd or setfl with flag: %d \n", larg);
			status = SAFE_INVOKE(ocall_fcntl2, &retval, fd, cmd, larg);
			CHECK_STATUS(status);
			return retval;
		case F_SETLK:
		case F_GETLK:
		case F_SETLKW:
			flarg = va_arg(ap, struct flock *);
			status = SAFE_INVOKE(ocall_fcntl3, &retval, fd, cmd, flarg, sizeof(struct flock));
			CHECK_STATUS(status);
			return retval;
		default:
			va_end(ap);
			return -1;
	};
	
	return -1;
}
