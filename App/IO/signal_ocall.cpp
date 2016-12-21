#include <signal.h>
#include <stdio.h>

#include "TopensslEnclave_u.h"

void increase_ocall_count();

int ocall_sigemptyset(sigset_t *set)
{
	increase_ocall_count();
	return sigemptyset(set);
}

int ocall_sigfillset(sigset_t *set)
{
	increase_ocall_count();
	return sigfillset(set);
}

int ocall_sigaddset(sigset_t *set, int signo)
{
	increase_ocall_count();
	return sigaddset(set, signo);
}

int ocall_sigdelset(sigset_t *set, int signo)
{
	increase_ocall_count();
	return sigdelset(set, signo);
}

int ocall_sigismember(const sigset_t *set, int signo)
{
	increase_ocall_count();
	return sigismember(set, signo);
}

int ocall_sigsuspend(const sigset_t *set)
{
	increase_ocall_count();
	return sigsuspend(set);
}

int ocall_sigaction(int sig, const struct sigaction *act, struct sigaction *oact)
{
	increase_ocall_count();
	return sigaction(sig, act, oact);
}

int ocall_sigpending(sigset_t *set)
{
	increase_ocall_count();
	return sigpending(set);
}

int ocall_sigwait(const sigset_t *set, int *sig)
{
	increase_ocall_count();
	return sigwait(set, sig);
}

__sighandler_t ocall_signal(int __sig, __sighandler_t __handler)
{
	increase_ocall_count();
	// printf("Call the ocall_signal \n");
	return signal(__sig, __handler);
}

int ocall_raise(int sig)
{
	increase_ocall_count();
	return raise(sig);
}