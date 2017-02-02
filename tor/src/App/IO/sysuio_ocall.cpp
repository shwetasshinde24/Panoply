
#include <sys/uio.h>
#include <stdio.h>

#include "proxy/sgx_sysuio_u.h"

void *iovec_table[10000];
int count = 0;

void *get_iovec_p(int iovec_id)	{
	if (iovec_id<=0)	{
		return NULL;
	}

	return iovec_table[iovec_id];
}

int ocall_init_multiple_iovec_outside(const void* __iovec, int iovec_size, int __count)
{
	const struct iovec *iovec_p = (const struct iovec *)__iovec;
	struct iovec *dup_iovec = (struct iovec *)malloc(sizeof(struct iovec)*__count);
	for (int i=0; i<__count; i++)	{
		dup_iovec[i].iov_len = iovec_p[i].iov_len;
		dup_iovec[i].iov_base = malloc(iovec_p[i].iov_len);		
	}
	iovec_table[++count] = dup_iovec;
	return count;
}

void ocall_copy_base_to_outside(int iovec_id, int i, const void* base, int len)
{
	// printf("ocall_copy_base_to_outside : %d %d %p %d \n", iovec_id, i, base, len);
	const struct iovec *iovec_p = (const struct iovec *)get_iovec_p(iovec_id);
	memcpy(iovec_p[i].iov_base, base, len);
}

ssize_t ocall_readv (int __fd, const void *__iovec, int iovec_size, int __count)
{
	const struct iovec *iovec_p = (const struct iovec *)__iovec;
	return readv(__fd, iovec_p, __count);
}

ssize_t ocall_writev (int __fd, int iovec_id, int iovec_size, int __count)
{
	// // printf("ocall_writev: %d %p \n", __fd, iovec_id);
	const struct iovec *iovec_p = (const struct iovec *)get_iovec_p(iovec_id);
	int ret = writev(__fd, iovec_p, __count);
	// // printf("return : %d \n", ret);
	return ret; 
}

void ocall_free_iovec_outside(int iovec_id, int iovec_size, int __count)
{
	struct iovec *iovec_p = (struct iovec *)get_iovec_p(iovec_id);
	for (int i=0; i<__count; i++)	{
		free(iovec_p[i].iov_base);
	}
	free(iovec_p);
	iovec_table[iovec_id]=NULL;
}

ssize_t ocall_process_vm_readv (pid_t __pid, const struct iovec *__lvec, unsigned long int __liovcnt, 
	const struct iovec *__rvec, unsigned long int __riovcnt, unsigned long int __flags)
{
	return process_vm_readv(__pid, __lvec, __liovcnt, __rvec, __riovcnt, __flags);
}

ssize_t ocall_process_vm_writev (pid_t __pid, const struct iovec *__lvec, unsigned long int __liovcnt,
	const struct iovec *__rvec, unsigned long int __riovcnt, unsigned long int __flags)
{
	return process_vm_writev(__pid, __lvec, __liovcnt, __rvec, __riovcnt, __flags);
}