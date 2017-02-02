#include <sys/utsname.h>

#include "H2oEnclave_u.h"

int ocall_uname(struct utsname *name)
{
	return uname(name);
}