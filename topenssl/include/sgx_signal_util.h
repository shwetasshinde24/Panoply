#ifndef SGX_SIGNAL_UTIL_H
#define SGX_SIGNAL_UTIL_H

#include <struct/sgx_signal_struct.h>
#include <proxy/sgx_signal_t.h>

static inline int sgx_wrapper_sigemptyset(sigset_t *set)
{
	int retval;
	ocall_sigemptyset(&retval, set);
	return retval;
}

static inline int sgx_wrapper_sigfillset(sigset_t *set)
{
	int retval;
	ocall_sigfillset(&retval, set);
	return retval;
}

static inline int sgx_wrapper_sigaddset(sigset_t *set, int signo)
{
	int retval;
	ocall_sigaddset(&retval, set, signo);
	return retval;
}

static inline int sgx_wrapper_sigdelset(sigset_t *set, int signo)
{
	int retval;
	ocall_sigdelset(&retval, set, signo);
	return retval;
}

static inline int sgx_wrapper_sigismember(const sigset_t *set, int signo)
{
	int retval;
	ocall_sigismember(&retval, set, signo);
	return retval;
}

static inline int sgx_wrapper_sigsuspend(const sigset_t *set)
{
	int retval;
	ocall_sigsuspend(&retval, set);
	return retval;
}

static inline int sgx_wrapper_sigaction(int sig, const struct sigaction *act, struct sigaction *oact)
{
	int retval;
	ocall_sigaction(&retval, sig, act, oact);
	return retval;
}

static inline int sgx_wrapper_sigpending(sigset_t *set)
{
	int retval;
	ocall_sigpending(&retval, set);
	return retval;
}

static inline int sgx_wrapper_sigwait(const sigset_t *set, int *sig)
{
	int retval;
	ocall_sigwait(&retval, set, sig);
	return retval;
}

static inline __sighandler_t sgx_wrapper_signal(int __sig, __sighandler_t __handler)
{
	__sighandler_t retval;
	ocall_signal(&retval, __sig, __handler);
	return retval;
}

static inline int sgx_wrapper_raise(int signal)
{
	int retval;
	ocall_raise(&retval, signal);
	return retval;
}

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

#endif