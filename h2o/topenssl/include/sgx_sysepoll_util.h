#ifndef SGX_SYSEPOLL_UTIL_H
#define SGX_SYSEPOLL_UTIL_H

#include <struct/sgx_sysepoll_struct.h>
#include <proxy/sgx_sysepoll_t.h>
#include "sgx_thread.h"
#include <sgx_stdio_util.h>

#ifdef __cplusplus
extern "C"	{
#endif 

extern int sgx_wrapper_epoll_create(int __size);
extern int sgx_wrapper_epoll_create1(int __flags);
extern int sgx_wrapper_epoll_ctl(int __epfd, int __op, int __fd, struct epoll_event *__event);

extern int sgx_wrapper_epoll_wait(int __epfd, struct epoll_event *__events,
       int __maxevents, int __timeout);
extern int sgx_wrapper_epoll_pwait(int __epfd,  struct epoll_event *__events, int __maxevents, int __timeout,
             const __sigset_t *__ss);

#ifdef __cplusplus
}
#endif 

#define epoll_create(A) sgx_wrapper_epoll_create(A)
#define epoll_create1(A) sgx_wrapper_epoll_create1(A)
#define epoll_ctl(A, B, C, D) sgx_wrapper_epoll_ctl(A, B, C, D)
#define epoll_wait(A, B, C, D) sgx_wrapper_epoll_wait(A, B, C, D)
#define epoll_pwait(A, B, C, D, E) sgx_wrapper_epoll_pwait(A, B, C, D, E)

#endif
