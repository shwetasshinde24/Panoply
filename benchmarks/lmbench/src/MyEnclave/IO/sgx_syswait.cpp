/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sgx_syswait_util.h>
#include <sgx_ocall_util.h>

#include <MyEnclave_t.h>

__pid_t sgx_wrapper_waitpid(__pid_t __pid, int *__stat_loc, int __options)
{
	__pid_t retval;
	sgx_status_t status = ocall_waitpid(&retval, __pid, __stat_loc, __options);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_waitid(idtype_t __idtype, __id_t __id, siginfo_t *__infop, int __options)
{
	int retval;
	sgx_status_t status = ocall_waitid(&retval, __idtype, __id, __infop, __options);
	CHECK_STATUS(status);
	return retval;
}

pid_t sgx_wrapper_wait(int *wstatus)
{
	pid_t retval;
	sgx_status_t status = ocall_wait(&retval, wstatus);
	CHECK_STATUS(status);
	return retval;
}