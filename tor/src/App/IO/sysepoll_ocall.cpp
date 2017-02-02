#include <sys/epoll.h>
#include <stdio.h>
#include <pthread.h>

#include <TorEnclave_u.h>


int ocall_epoll_create(int __size)
{
	// printf("Call epoll create by thread: %d \n", pthread_self());
	int ret = epoll_create(__size);
	// printf("result is: %d \n", ret);
	return ret;
}

int ocall_epoll_create1 (int __flags)
{
	return epoll_create1(__flags);
}

int ocall_epoll_ctl (int __epfd, int __op, int __fd, void *__event, int event_size)
{
	struct epoll_event *event = (struct epoll_event *)__event;
	// printf("Call ocall_epoll_ctl: %d by %d \n", __epfd, pthread_self());
	return epoll_ctl(__epfd, __op, __fd, event);
}

int ocall_epoll_wait (int __epfd, void *__events, int event_size,
       int __maxevents, int __timeout)
{
	// struct epoll_event *events = (struct epoll_event *) __events;
	struct epoll_event* events = (struct epoll_event*)malloc(sizeof(struct epoll_event)*__maxevents);
	int maxevents = __maxevents;
	int timeout = __timeout;
	// printf("Call epoll_wait: %d %d %d\n", __epfd, __maxevents, __timeout);
	int ret = epoll_wait(__epfd, events, maxevents, timeout);
	// printf("epoll wait return :%d\n", ret);
	if (ret>0)	{
		// printf("The ptr is: %p \n The type is: %d \n", events[0].data.ptr, events[0].events);
		memcpy(__events, events, event_size*__maxevents);
		// printf("Done memcpy \n");
	}
	return ret;
}

int ocall_epoll_pwait (int __epfd, void *__events, int event_size ,int __maxevents, int __timeout,
             void *__ss, int sigset_size)
{
	struct epoll_event *events = (struct epoll_event *)__events;
	const __sigset_t * ss = (const __sigset_t *)__ss;
	return epoll_pwait(__epfd, events, __maxevents, __timeout, ss);
}