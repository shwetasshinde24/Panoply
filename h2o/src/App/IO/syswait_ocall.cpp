#include <sys/wait.h>
#include <stdio.h>
#include <H2oEnclave_u.h>

__pid_t ocall_waitpid (__pid_t __pid, int *__stat_loc, int __options)
{
	// printf("Call ocall_waitpid \n");
	return waitpid(__pid, __stat_loc, __options);
}

int ocall_waitid(idtype_t __idtype, __id_t __id, siginfo_t *__infop, int __options)
{
	// printf("Call ocall_waitid \n");
	return waitid(__idtype, __id, __infop, __options);
}