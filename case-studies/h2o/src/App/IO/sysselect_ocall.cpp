#include <sys/select.h>

#include <H2oEnclave_u.h>

int ocall_select (int __nfds,  fd_set *__readfds,
    fd_set *__writefds,
    fd_set *__exceptfds,
    struct timeval *__timeout)
{
	return select(__nfds, __readfds, __writefds, __exceptfds, __timeout);
}