#ifndef SGX_UTSNAME_UTIL_H
#define SGX_UTSNAME_UTIL_H

#include <struct/sgx_utsname_struct.h>
#include <proxy/sgx_utsname_t.h>


static inline int sgx_wrapper_uname(struct utsname *name)
{
	int retval;
	ocall_uname(&retval, name);
	return retval;
}

#define uname(A) sgx_wrapper_uname(A)

#endif 