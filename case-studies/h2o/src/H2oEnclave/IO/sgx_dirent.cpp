#include <sgx_dirent_util.h>
#include <sgx_ocall_util.h>

extern "C"	{

	void *sgx_wrapper_opendir (const char *name)
	{
		void *retval;
		sgx_status_t status = ocall_opendir(&retval, name);
		CHECK_STATUS(status);
		return retval;
	}

	void *sgx_wrapper_fdopendir (int fd)
	{
		void *retval;
		sgx_status_t status = ocall_fdopendir(&retval, fd);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_closedir (void *dirp_cast)
	{
		int retval;
		sgx_status_t status = ocall_closedir(&retval, dirp_cast);
		CHECK_STATUS(status);
		return retval;
	}

	struct dirent *sgx_wrapper_readdir (void *dirp_cast)
	{
		struct dirent *retval;
		sgx_status_t status = ocall_readdir(&retval, dirp_cast);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_readdir_r (void *dirp_cast, struct dirent *entry, struct dirent **result)
	{
		int retval;
		sgx_status_t status = ocall_readdir_r(&retval, dirp_cast, entry, result);
		CHECK_STATUS(status);
		return retval;
	}

	void sgx_wrapper_rewinddir (void *dirp_cast)
	{
		sgx_status_t status = ocall_rewinddir(dirp_cast);
		CHECK_STATUS(status);
	}

	void sgx_wrapper_seekdir (void *dirp_cast, long int pos)
	{
		sgx_status_t status = ocall_seekdir(dirp_cast, pos);
		CHECK_STATUS(status);
	}

	long int sgx_wrapper_telldir ( void *dirp_cast)
	{
		long int retval;
		sgx_status_t status = ocall_telldir(&retval, dirp_cast);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_dirfd ( void *dirp_cast)
	{
		int retval;
		sgx_status_t status = ocall_dirfd(&retval, dirp_cast);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_alphasort ( const struct dirent **e1,  const struct dirent **e2)
	{
		int retval;
		sgx_status_t status = ocall_alphasort(&retval, e1, e2);
		CHECK_STATUS(status);
		return retval;
	}

	ssize_t sgx_wrapper_getdirentries (int fd, char *buf, size_t nbytes, off_t *basep)
	{
		ssize_t retval;
		sgx_status_t status = ocall_getdirentries(&retval,fd, buf, nbytes, basep);
		CHECK_STATUS(status);
		return retval;
	}

	int sgx_wrapper_versionsort (const struct dirent **e1,  const struct dirent **e2)
	{
		int retval;
		sgx_status_t status = ocall_versionsort(&retval,e1, e2);
		CHECK_STATUS(status);
		return retval;
	}

}