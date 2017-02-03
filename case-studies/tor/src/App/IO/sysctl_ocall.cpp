#include <sys/sysctl.h>

#include <TorEnclave_u.h>

int ocall_sysctl (int *name, int nlen, void *oldval, size_t *oldlenp, void *newval, size_t newlen)
{
	return sysctl(name, nlen, oldval, oldlenp, newval, newlen);
}