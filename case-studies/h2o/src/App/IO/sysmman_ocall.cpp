#include <sys/mman.h>
#include <stdio.h>
#include "proxy/sgx_sysmman_u.h"

void *ocall_mmap (void *__addr, size_t __len, int __prot, int __flags, int __fd, __off_t __offset)
{
	return mmap(__addr, __len, __prot, __flags, __fd, __offset);
}

void *ocall_mmap64 (void *__addr, size_t __len, int __prot, int __flags, int __fd, __off64_t __offset)
{
	return mmap64(__addr, __len, __prot, __flags, __fd, __offset);
}

int ocall_munmap (void *__addr, size_t __len)
{
	return munmap(__addr, __len);
}

int ocall_mprotect (void *__addr, size_t __len, int __prot)
{
	return mprotect(__addr, __len, __prot);
}

int ocall_msync (void *__addr, size_t __len, int __flags)
{
	return msync(__addr, __len, __flags);
}

int ocall_mlock (const void *__addr, size_t __len)
{
	return mlock(__addr, __len);
}

int ocall_munlock (const void *__addr, size_t __len)
{
	return munlock(__addr, __len);
}

int ocall_mlockall (int __flags)
{
	return mlockall(__flags);
}

int ocall_munlockall (void)
{
	return munlockall();
}

int ocall_mincore (void *__start, size_t __len, unsigned char *__vec)
{
	return mincore(__start, __len, __vec);
}

int ocall_shm_open (const char *__name, int __oflag, mode_t __mode)
{
	fprintf(stderr, "Fix me: Dummy ocall_shm_open call \n");
	return -1;
	//return shm_open(__name, __oflag, __mode);
}

int ocall_shm_unlink (const char *__name)
{
	fprintf(stderr, "Fix me: Dummy ocall_shm_open call \n");
	return -1;
	//return shm_unlink(__name);
}