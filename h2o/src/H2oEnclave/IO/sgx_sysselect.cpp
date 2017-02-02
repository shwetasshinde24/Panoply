#include <sgx_sysselect_util.h>
#include <struct/sgx_time_struct.h>
#include <sgx_ocall_util.h>

int sgx_wrapper_select (int __nfds,  fd_set *__readfds,
    fd_set *__writefds,
    fd_set *__exceptfds,
    struct timeval *__timeout)
{
	int retval;
	sgx_status_t status = ocall_select(&retval, __nfds, __readfds, __writefds, __exceptfds, __timeout);
	CHECK_STATUS(status);
	return retval;
}
