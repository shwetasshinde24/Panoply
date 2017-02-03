/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sgx_sysselect_util.h>
#include <struct/sgx_time_struct.h>
#include <sgx_ocall_util.h>

extern sgx_enclave_id_t enclave_self_id;

int sgx_wrapper_select (int __nfds,  fd_set *__readfds,
    fd_set *__writefds,
    fd_set *__exceptfds,
    struct timeval *__timeout)
{
	int retval;
	// printf("sgx_wrapper_select Timeout struct: %ld --- %ld \n", __timeout->tv_sec, __timeout->tv_usec );
	//printf("")

	// if (__timeout->tv_sec==0)	{
	// 	abort();
	// }

	sgx_status_t status = ocall_select(&retval, __nfds, __readfds, __writefds, __exceptfds, __timeout, sizeof(struct timeval));
	CHECK_STATUS(status);
	return retval;
}
