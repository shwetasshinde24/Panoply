#ifndef SGX_SELECT_UTIL_H
#define SGX_SELECT_UTIL_H

#include "proxy/sgx_sysselect_t.h"

static inline int sgx_wrapper_select (int __nfds,  fd_set *__readfds,
    fd_set *__writefds,
    fd_set *__exceptfds,
    struct timeval *__timeout)
{
	int retval;
	ocall_select(&retval, __nfds, __readfds, __writefds, __exceptfds, __timeout);
	return retval;
}

#define select(A, B, C, D, E) sgx_wrapper_select(A, B, C, D, E)

#endif
