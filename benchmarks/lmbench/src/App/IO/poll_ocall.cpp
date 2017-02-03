/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <poll.h>

#include "MyEnclave_u.h"


int ocall_poll(struct pollfd *__fds, nfds_t __nfds, int __timeout)
{
	return poll(__fds, __nfds, __timeout);
}