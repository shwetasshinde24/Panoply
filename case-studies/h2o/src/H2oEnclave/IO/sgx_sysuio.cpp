#include <sgx_sysuio_util.h>
#include <sgx_unistd_util.h>
#include <string.h>
#include <sgx_stdio_util.h>
#include "sgx_thread.h"

sgx_thread_mutex_t writev_mutex = SGX_THREAD_MUTEX_INITIALIZER;
sgx_thread_mutex_t init_mutex = SGX_THREAD_MUTEX_INITIALIZER;

ssize_t sgx_wrapper_readv (int __fd, const struct iovec *__iovec, int __count)
{
	ssize_t retval;
	ocall_readv(&retval, __fd, __iovec, sizeof(struct iovec), __count);
	return retval;
}

ssize_t sgx_wrapper_writev (int __fd, const struct iovec *__iovec, int __count)
{
	// Converted to ocall_write implementation
	ssize_t retval;
	int* outsize_iovec_id = (int*)malloc(sizeof(int));
	int perm_iovec_id = -1;

	size_t total_len = 0;

	int i=0;
	for (i=0; i<__count; i++)
		total_len += __iovec[i].iov_len;

	void* merge_mem = malloc(total_len);
	if (merge_mem==NULL)	{
		sgx_wrapper_printf_debug("Malloc error in wrapper_writev \n");
		abort();
	}

	void* p = merge_mem;

	for (i=0; i<__count; i++)	{
		memcpy(p, __iovec[i].iov_base, __iovec[i].iov_len);
		p += __iovec[i].iov_len;
	}

	retval = sgx_wrapper_write(__fd, merge_mem, total_len);
	free(merge_mem);

	return retval;

	// ssize_t retval;
	// int* outsize_iovec_id = (int*)malloc(sizeof(int));
	// int perm_iovec_id = -1;
	
	// sgx_thread_mutex_lock(&init_mutex);
	// int errorcode = ocall_init_multiple_iovec_outside(outsize_iovec_id, __iovec, sizeof(struct iovec), __count);
	// perm_iovec_id = *outsize_iovec_id;
	// sgx_thread_mutex_unlock(&init_mutex);
	
	// if (errorcode!=0)	{
	// 	// sgx_wrapper_printf_special("ocall_init_multiple_iovec_outside bug: %x \n");
	// 	abort();
	// }

	// // sgx_wrapper_printf_special("sgx_wrapper_writev %d \n", perm_iovec_id);

	// int i=0;
	// for (i=0; i<__count; i++)	{
	// 	errorcode = ocall_copy_base_to_outside( perm_iovec_id, i, __iovec[i].iov_base, __iovec[i].iov_len);
	// 	if (errorcode!=0)	{
	// 		// sgx_wrapper_printf_special("ocall_copy_base_to_outside bug: %x \n");
	// 		abort();
	// 	}	
	// }

	// sgx_thread_mutex_lock(&writev_mutex);
	// errorcode = ocall_writev(&retval, __fd,  perm_iovec_id, sizeof(struct iovec), __count);
	// sgx_thread_mutex_unlock(&writev_mutex);

	// if (errorcode!=0)	{
	// 	// sgx_wrapper_printf_special("ocall_writev bug: %x \n");
	// 	abort();
	// }		
	// // sgx_wrapper_printf_special("call free %d %d \n", __fd, i);
	// errorcode = ocall_free_iovec_outside(perm_iovec_id, sizeof(struct iovec), __count);
	// if (errorcode!=0)	{
	// 	// sgx_wrapper_printf_special("ocall_writev bug: %x \n");
	// 	abort();
	// }	
	// free(outsize_iovec_id);
	// return retval;
}

ssize_t sgx_wrapper_process_vm_readv (pid_t __pid, const struct iovec *__lvec, unsigned long int __liovcnt, 
	const struct iovec *__rvec, unsigned long int __riovcnt, unsigned long int __flags)
{
	ssize_t retval;
	ocall_process_vm_readv(&retval, __pid, __lvec, __liovcnt, __rvec, __riovcnt, __flags);
	return retval;
}

ssize_t sgx_wrapper_process_vm_writev (pid_t __pid, const struct iovec *__lvec, unsigned long int __liovcnt,
	const struct iovec *__rvec, unsigned long int __riovcnt, unsigned long int __flags)
{
	ssize_t retval;
	ocall_process_vm_writev(&retval, __pid, __lvec, __liovcnt, __rvec, __riovcnt, __flags);
	return retval;
}