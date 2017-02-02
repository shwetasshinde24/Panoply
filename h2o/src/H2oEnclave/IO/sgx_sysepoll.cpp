#include <sgx_sysepoll_util.h>
#include <sgx_ocall_util.h>

int sgx_wrapper_epoll_create(int __size)
{
	int ret;
	sgx_status_t status = ocall_epoll_create(&ret, __size);
	CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_epoll_create1(int __flags)
{
	int ret;
	sgx_status_t status = ocall_epoll_create1(&ret, __flags);
	CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_epoll_ctl(int __epfd, int __op, int __fd, struct epoll_event *__event)
{
	int ret;
	sgx_status_t status = ocall_epoll_ctl(&ret, __epfd, __op, __fd, __event, sizeof(struct epoll_event));
	CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_epoll_wait(int __epfd, struct epoll_event *__events,
       int __maxevents, int __timeout)
{
	sgx_status_t status;
	long tmp = sgx_thread_self()%17;
	int k = tmp%8;
	// sgx_wrapper_printf_debug("%d hold token : %d \n", tmp, k);
	int ret;
	switch(k)	{
		case 0:
			status = ocall_epoll_wait(&ret, __epfd, __events, sizeof(struct epoll_event), __maxevents, __timeout);
			break;
		case 1:
			status = ocall_epoll_wait1(&ret, __epfd, __events, sizeof(struct epoll_event), __maxevents, __timeout);
			break;
		case 2:
			status = ocall_epoll_wait2(&ret, __epfd, __events, sizeof(struct epoll_event), __maxevents, __timeout);
			break;
		case 3:
			status = ocall_epoll_wait3(&ret, __epfd, __events, sizeof(struct epoll_event), __maxevents, __timeout);
			break;	
		case 4:
			status = ocall_epoll_wait4(&ret, __epfd, __events, sizeof(struct epoll_event), __maxevents, __timeout);
			break;						
		case 5:
			status = ocall_epoll_wait5(&ret, __epfd, __events, sizeof(struct epoll_event), __maxevents, __timeout);
			break;	
		case 6:
			status = ocall_epoll_wait6(&ret, __epfd, __events, sizeof(struct epoll_event), __maxevents, __timeout);
			break;	
		case 7:
			status = ocall_epoll_wait7(&ret, __epfd, __events, sizeof(struct epoll_event), __maxevents, __timeout);
			break;	
	}
	CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_epoll_pwait(int __epfd,  struct epoll_event *__events, int __maxevents, int __timeout,
             const __sigset_t *__ss)
{
	int ret;
	sgx_status_t status = ocall_epoll_pwait(&ret, __epfd, __events, sizeof(struct epoll_event), __maxevents, __timeout, __ss, sizeof(__sigset_t));
	CHECK_STATUS(status);
	return ret;
}