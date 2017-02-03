/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#ifndef SGX_SYSWAIT_UTIL_H
#define SGX_SYSWAIT_UTIL_H

#include <struct/sgx_syswait_struct.h>

#ifdef __cplusplus
extern "C"	{
#endif 

extern __pid_t sgx_wrapper_waitpid(__pid_t __pid, int *__stat_loc, int __options);
extern int sgx_wrapper_waitid(idtype_t __idtype, __id_t __id, siginfo_t *__infop, int __options);
extern pid_t sgx_wrapper_wait(int *wstatus);

#ifdef __cplusplus
}
#endif 


#define waitpid(A, B, C) sgx_wrapper_waitpid(A, B, C)

// Fix me: wait system call is buggy ????
#define wait(A) sgx_wrapper_wait(A)

#endif 