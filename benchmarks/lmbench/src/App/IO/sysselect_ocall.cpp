/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sys/select.h>
#include <stdio.h>

#include <MyEnclave_u.h>

int ocall_select (int __nfds,  fd_set *__readfds,
    fd_set *__writefds,
    fd_set *__exceptfds,
    void *__timeout, int tvsize)
{
	struct timeval* m_timeout = (struct timeval*)__timeout;
	// printf("ocall_select Timeout struct: %ld --- %ld \n", m_timeout->tv_sec, m_timeout->tv_usec );
	m_timeout->tv_sec = 10;
	return select(__nfds, __readfds, __writefds, __exceptfds, m_timeout);
}