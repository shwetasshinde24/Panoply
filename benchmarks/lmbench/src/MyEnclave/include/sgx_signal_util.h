/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#ifndef SGX_SIGNAL_UTIL_H
#define SGX_SIGNAL_UTIL_H

#include <struct/sgx_signal_struct.h>

#ifdef __cplusplus
extern "C"	{
#endif 

extern int sgx_wrapper_sigemptyset(sigset_t *set);
extern int sgx_wrapper_sigfillset(sigset_t *set);
extern int sgx_wrapper_sigaddset(sigset_t *set, int signo);
extern int sgx_wrapper_sigdelset(sigset_t *set, int signo);
extern int sgx_wrapper_sigismember(const sigset_t *set, int signo);
extern int sgx_wrapper_sigsuspend(const sigset_t *set);
extern int sgx_wrapper_sigaction(int sig, struct sigaction *act, struct sigaction *oact);
extern int sgx_wrapper_sigpending(sigset_t *set);
extern int sgx_wrapper_sigwait(const sigset_t *set, int *sig);
extern __sighandler_t sgx_wrapper_signal(int __sig, __sighandler_t __handler);
extern int sgx_wrapper_raise(int signal);
extern int sgx_wrapper_kill(pid_t pid, int sig);

#ifdef __cplusplus
}
#endif 


#define sigemptyset(A) sgx_wrapper_sigemptyset(A) 
#define sigfillset(A) sgx_wrapper_sigfillset(A)
#define sigaddset(A, B) sgx_wrapper_sigaddset(A, B)
#define sigdelset(A, B) sgx_wrapper_sigdelset(A, B)
#define sigismember(A, B) sgx_wrapper_sigismember(A, B)
#define sigsuspend(A) sgx_wrapper_sigsuspend(A)
#define sigaction(A, B, C) sgx_wrapper_sigaction(A, B, C)
#define sigpending(A) sgx_wrapper_sigpending(A)
#define sigwait(A, B) sgx_wrapper_sigwait(A, B)
#define signal(A, B) sgx_wrapper_signal(A, B)
#define raise(A) sgx_wrapper_raise(A)
#define kill(A, B) sgx_wrapper_kill(A, B)

#endif