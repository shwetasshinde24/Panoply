#include <sgx_sysmman_util.h>
#include <sgx_ocall_util.h>


void *sgx_wrapper_mmap (void *__addr, size_t __len, int __prot, int __flags, int __fd, __off_t __offset)
{
	void* retval;
	sgx_status_t status = ocall_mmap(&retval, __addr, __len, __prot, __flags, __fd, __offset);
	CHECK_STATUS(status);
	return retval;
}

void *sgx_wrapper_mmap64 (void *__addr, size_t __len, int __prot, int __flags, int __fd, __off64_t __offset)
{
	void* retval;
	sgx_status_t status = ocall_mmap64(&retval, __addr, __len, __prot, __flags, __fd, __offset);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_munmap (void *__addr, size_t __len)
{
	int retval;
	sgx_status_t status = ocall_munmap(&retval, __addr, __len);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_mprotect (void *__addr, size_t __len, int __prot)
{
	int retval;
	sgx_status_t status = ocall_mprotect(&retval, __addr, __len, __prot);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_msync (void *__addr, size_t __len, int __flags)
{
	int retval;
	sgx_status_t status = ocall_msync(&retval, __addr, __len, __flags);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_mlock (const void *__addr, size_t __len)
{
	int retval;
	sgx_status_t status = ocall_mlock(&retval, __addr, __len);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_munlock (const void *__addr, size_t __len)
{
	int retval;
	sgx_status_t status = ocall_munlock(&retval, __addr, __len);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_mlockall (int __flags)
{
	int retval;
	sgx_status_t status = ocall_mlockall(&retval, __flags);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_munlockall (void)
{
	int retval;
	sgx_status_t status = ocall_munlockall(&retval);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_mincore (void *__start, size_t __len, unsigned char *__vec)
{
	int retval;
	sgx_status_t status = ocall_mincore(&retval, __start, __len, __vec);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_shm_open (const char *__name, int __oflag, mode_t __mode)
{
	int retval;
	// fprintf(stderr, "Fix me: Dummy sgx_wrapper_shm_open call \n");
	sgx_status_t status = ocall_shm_open(&retval, __name, __oflag, __mode);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_shm_unlink (const char *__name)
{
	int retval;
	// fprintf(stderr, "Fix me: Dummy sgx_wrapper_shm_open call \n");
	sgx_status_t status = ocall_shm_unlink(&retval, __name);
	CHECK_STATUS(status);
	return retval;
}
