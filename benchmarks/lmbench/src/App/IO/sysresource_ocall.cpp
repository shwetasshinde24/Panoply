/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sys/resource.h>

#include "MyEnclave_u.h"

int ocall_prlimit (__pid_t pid, enum __rlimit_resource resource, const struct rlimit *new_limit, struct rlimit *old_limit)
{
	return prlimit(pid, resource, new_limit, old_limit);
}

int ocall_getrlimit(int resource, struct rlimit *rlim)
{
	return getrlimit(resource, rlim);
}

int ocall_setrlimit(int resource, const struct rlimit *rlim)
{
	return setrlimit(resource, rlim);
}