#include <pwd.h>
#include "TorEnclave_u.h"

struct passwd *ocall_getpwuid(uid_t uid)
{
	return getpwuid(uid);
}

struct passwd *ocall_getpwnam(const char *name)
{
	return getpwnam(name);
}

int ocall_getpwnam_r(const char *name, struct passwd *pwd, 
                   char *buf, size_t buflen, struct passwd **result)
{
	return getpwnam_r(name, pwd, buf, buflen, result);
}
      
