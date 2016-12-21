#include <sys/resource.h>

#include "TopensslEnclave_u.h"

extern void increase_ocall_count();

int ocall_prlimit (__pid_t pid, enum __rlimit_resource resource, const struct rlimit *new_limit, struct rlimit *old_limit)
{
    increase_ocall_count();
	return prlimit(pid, resource, new_limit, old_limit);
}

int ocall_getrlimit(int resource, struct rlimit *rlim)
{
    increase_ocall_count();
	return getrlimit(resource, rlim);
}

int ocall_setrlimit(int resource, const struct rlimit *rlim)
{
    increase_ocall_count();
	return setrlimit(resource, rlim);
}