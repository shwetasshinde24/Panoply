// #include <replacements/sgx_stdio_util.h>
#include <poll.h>

#include "H2oEnclave_u.h"


int ocall_poll(struct pollfd *__fds, nfds_t __nfds, int __timeout)
{
	return poll(__fds, __nfds, __timeout);
}