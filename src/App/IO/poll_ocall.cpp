// #include <replacements/sgx_stdio_util.h>
#include <poll.h>
#include <stdio.h>
#include "TopensslEnclave_u.h"

extern void increase_ocall_count();

int ocall_poll(struct pollfd *__fds, nfds_t __nfds, int __timeout)
{
	increase_ocall_count();
	// printf("Do ocall poll \n");
	return poll(__fds, __nfds, __timeout);
}