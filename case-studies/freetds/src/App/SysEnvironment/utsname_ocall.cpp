#include <sys/utsname.h>

#include "TdsEnclave_u.h"

int ocall_uname(struct utsname *name)
{
	return uname(name);
}