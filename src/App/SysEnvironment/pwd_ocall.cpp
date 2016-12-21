#include <pwd.h>
#include "TopensslEnclave_u.h"

extern void increase_ocall_count();

struct passwd *ocall_getpwuid(uid_t uid)
{
    increase_ocall_count();
	return getpwuid(uid);
}

struct passwd *ocall_getpwnam(const char *name)
{
    increase_ocall_count();
	return getpwnam(name);
}

int ocall_getpwnam_r(const char *name, struct passwd *pwd, 
                   char *buf, size_t buflen, struct passwd **result)
{
    increase_ocall_count();
	return getpwnam_r(name, pwd, buf, buflen, result);
}
      
