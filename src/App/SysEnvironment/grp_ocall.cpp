#include <grp.h>

#include "TopensslEnclave_u.h"

extern void increase_ocall_count();

struct group *ocall_getgrgid(gid_t gid)
{
    increase_ocall_count();
	return getgrgid(gid);
}

int ocall_initgroups(const char *user, gid_t group)
{
    increase_ocall_count();
	return initgroups(user, group);
}
