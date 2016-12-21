#ifndef SGX_SYSEVENTFD_UTIL_H
#define SGX_SYSEVENTFD_UTIL_H

#include <struct/sgx_syseventfd_struct.h>
#include <proxy/sgx_syseventfd_t.h>

static inline int sgx_wrapper_eventfd(unsigned int initval, int flags)
{
	int retval;
	ocall_eventfd(&retval, initval, flags);
	return retval;
}

#define eventfd(A, B) sgx_wrapper_eventfd(A, B)

#endif

