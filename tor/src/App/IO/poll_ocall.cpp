// #include <replacements/sgx_stdio_util.h>
#include <poll.h>
#include <stdio.h>
#include "TorEnclave_u.h"


int ocall_poll(struct pollfd *__fds, nfds_t __nfds, int __timeout)
{
	// printf("Do ocall poll \n");
	return poll(__fds, __nfds, __timeout);
}