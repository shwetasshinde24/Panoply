#include <grp.h>

#include "H2oEnclave_u.h"

struct group *ocall_getgrgid(gid_t gid)
{
	return getgrgid(gid);
}

int ocall_initgroups(const char *user, gid_t group)
{
	return initgroups(user, group);
}
