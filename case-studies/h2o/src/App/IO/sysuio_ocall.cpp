
#include <sys/uio.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#include "proxy/sgx_sysuio_u.h"

static pthread_mutex_t iovec_table_mutex = PTHREAD_MUTEX_INITIALIZER;
void *iovec_table[300000];
int count = 0;

void *get_iovec_p(int iovec_id)	{
	if (iovec_id<=0)	{
		return NULL;
	}

	return iovec_table[iovec_id];
}

int ocall_init_multiple_iovec_outside(const void* __iovec, int iovec_size, int __count)
{
	// printf("ocall_init_multiple_iovec_outside \n");
	const struct iovec *iovec_p = (const struct iovec *)__iovec;
	struct iovec *dup_iovec = (struct iovec *)calloc(sizeof(struct iovec), __count);
	if (dup_iovec==NULL)	{
		printf("Malloc error in ocall_init_multiple_iovec_outside \n");
		abort();
	}
	assert(dup_iovec);
	pthread_mutex_lock(&iovec_table_mutex);
	for (int i=0; i<__count; i++)	{
		dup_iovec[i].iov_len = iovec_p[i].iov_len;
		dup_iovec[i].iov_base = malloc(iovec_p[i].iov_len);		
		assert(dup_iovec[i].iov_base);
	}
	++count;
	count = count%300000;
	iovec_table[count] = dup_iovec;
	// assert(iovec_table[count]);
	pthread_mutex_unlock(&iovec_table_mutex);
	// printf("Return count: %d \n", count);
	return count;
}

void ocall_copy_base_to_outside(int iovec_id, int i, const void* base, int len)
{
	// printf("ocall_copy_base_to_outside : %d %d %p %d \n", iovec_id, i, base, len);
	pthread_mutex_lock(&iovec_table_mutex);
	const struct iovec *iovec_p = (const struct iovec *)get_iovec_p(iovec_id);
	if (iovec_p==NULL)	{
		printf("\n %d %d \n", iovec_id, count);
		abort();
		// pthread_mutex_unlock(&iovec_table_mutex);
		return ;
	}
	assert(iovec_p);
	memcpy(iovec_p[i].iov_base, base, len);
	pthread_mutex_unlock(&iovec_table_mutex);
}

ssize_t ocall_readv (int __fd, const void *__iovec, int iovec_size, int __count)
{
	const struct iovec *iovec_p = (const struct iovec *)__iovec;
	return readv(__fd, iovec_p, __count);
}

ssize_t ocall_writev (int __fd, int iovec_id, int iovec_size, int __count)
{
	// printf("ocall_writev: %d %p \n", __fd, iovec_id);
	const struct iovec *iovec_p = (const struct iovec *)get_iovec_p(iovec_id);
	assert(iovec_p);
	if (iovec_p==NULL)	{
		abort();
		return -1;
	}
	int ret = writev(__fd, iovec_p, __count);
	// printf("return : %d \n", ret);
	return ret; 
}

void ocall_free_iovec_outside(int iovec_id, int iovec_size, int __count)
{
	// printf("Free stuff: %d \n", iovec_id);
	pthread_mutex_lock(&iovec_table_mutex);
	struct iovec *iovec_p = (struct iovec *)get_iovec_p(iovec_id);
	if (iovec_p==NULL)	{
		// pthread_mutex_unlock(&iovec_table_mutex);
		// assert(iovec_p);
		return;
	}
	int i=0;
	for (i=0; i<__count; i++)	{
		free(iovec_p[i].iov_base);
	}
	free(iovec_p);
	iovec_table[iovec_id]=NULL;
	pthread_mutex_unlock(&iovec_table_mutex);
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