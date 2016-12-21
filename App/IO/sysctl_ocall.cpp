#include <sys/sysctl.h>

#include <TopensslEnclave_u.h>

extern void increase_ocall_count();

int ocall_sysctl (int *name, int nlen, void *oldval, size_t *oldlenp, void *newval, size_t newlen)
{
    increase_ocall_count();
	return sysctl(name, nlen, oldval, oldlenp, newval, newlen);
}