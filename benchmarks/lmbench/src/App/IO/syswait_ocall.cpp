/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sys/wait.h>
#include <stdio.h>
#include <MyEnclave_u.h>

__pid_t ocall_waitpid (__pid_t __pid, int *__stat_loc, int __options)
{
	// printf("Call ocall_waitpid \n");
	pid_t ret = waitpid(__pid, __stat_loc, __options);
	// printf("ocall_waitpid: %d \n", ret);
	return ret;
}

int ocall_waitid(idtype_t __idtype, __id_t __id, siginfo_t *__infop, int __options)
{
	// printf("Call ocall_waitid \n");
	return waitid(__idtype, __id, __infop, __options);
}

pid_t ocall_wait(int *wstatus)
{
	int my_wstatus;
	pid_t ret = wait(&my_wstatus);
	*wstatus = my_wstatus;
	return ret;
}