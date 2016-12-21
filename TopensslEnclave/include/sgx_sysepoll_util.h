#ifndef SGX_SYSEPOLL_UTIL_H
#define SGX_SYSEPOLL_UTIL_H

#include <struct/sgx_sysepoll_struct.h>
#include <proxy/sgx_sysepoll_t.h>

static inline int sgx_wrapper_epoll_create(int __size)
{
	int ret;
	ocall_epoll_create(&ret, __size);
	return ret;
}

static inline int sgx_wrapper_epoll_create1(int __flags)
{
	int ret;
	ocall_epoll_create1(&ret, __flags);
	return ret;
}

static inline int sgx_wrapper_epoll_ctl(int __epfd, int __op, int __fd, struct epoll_event *__event)
{
	int ret;
	ocall_epoll_ctl(&ret, __epfd, __op, __fd, __event, sizeof(struct epoll_event));
	return ret;
}

static inline int sgx_wrapper_epoll_wait(int __epfd, struct epoll_event *__events,
       int __maxevents, int __timeout)
{
	int ret;
	ocall_epoll_wait(&ret, __epfd, __events, sizeof(struct epoll_event), __maxevents, __timeout);
	return ret;
}

static inline int sgx_wrapper_epoll_pwait(int __epfd,  struct epoll_event *__events, int __maxevents, int __timeout,
             const __sigset_t *__ss)
{
	int ret;
	ocall_epoll_pwait(&ret, __epfd, __events, sizeof(struct epoll_event), __maxevents, __timeout, __ss, sizeof(__sigset_t));
	return ret;
}

#define epoll_create(A) sgx_wrapper_epoll_create(A)
#define epoll_create1(A) sgx_wrapper_epoll_create1(A)
#define epoll_ctl(A, B, C, D) sgx_wrapper_epoll_ctl(A, B, C, D)
#define epoll_wait(A, B, C, D) sgx_wrapper_epoll_wait(A, B, C, D)
#define epoll_pwait(A, B, C, D, E) sgx_wrapper_epoll_pwait(A, B, C, D, E)

#endif
