#ifndef SGX_SELECT_UTIL_H
#define SGX_SELECT_UTIL_H

#include "proxy/sgx_sysselect_t.h"

#ifdef __cplusplus
extern "C"	{
#endif 

extern int sgx_wrapper_select (int __nfds,  fd_set *__readfds,
    fd_set *__writefds,
    fd_set *__exceptfds,
    struct timeval *__timeout);

#ifdef __cplusplus
}
#endif 

#define select(A, B, C, D, E) sgx_wrapper_select(A, B, C, D, E)

#endif
