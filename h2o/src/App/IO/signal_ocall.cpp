#include <signal.h>
#include <stdio.h>

#include "H2oEnclave_u.h"

int ocall_sigemptyset(sigset_t *set)
{
	return sigemptyset(set);
}

int ocall_sigfillset(sigset_t *set)
{
	return sigfillset(set);
}

int ocall_sigaddset(sigset_t *set, int signo)
{
	return sigaddset(set, signo);
}

int ocall_sigdelset(sigset_t *set, int signo)
{
	return sigdelset(set, signo);
}

int ocall_sigismember(const sigset_t *set, int signo)
{
	return sigismember(set, signo);
}

int ocall_sigsuspend(const sigset_t *set)
{
	return sigsuspend(set);
}

int ocall_sigaction(int sig, const struct sigaction *act, struct sigaction *oact)
{
	return sigaction(sig, act, oact);
}

int ocall_sigpending(sigset_t *set)
{
	return sigpending(set);
}

int ocall_sigwait(const sigset_t *set, int *sig)
{
	return sigwait(set, sig);
}

__sighandler_t ocall_signal(int __sig, __sighandler_t __handler)
{
	printf("Call the ocall_signal \n");
	return signal(__sig, __handler);
}

int ocall_raise(int sig)
{
	return raise(sig);
}