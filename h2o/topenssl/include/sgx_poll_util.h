#ifndef SGX_POLL_UTIL_H
#define SGX_POLL_UTIL_H

#include <struct/sgx_poll_struct.h>
#include <proxy/sgx_poll_t.h>

#ifdef __cplusplus
extern "C"	{
#endif 

extern int sgx_wrapper_poll(struct pollfd* fds, unsigned int nfds, int timeout);

#ifdef __cplusplus
}
#endif 

#define poll(A, B, C) sgx_wrapper_poll(A, B, C)

#endif
