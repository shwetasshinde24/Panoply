#include <sys/utsname.h>

#include "TorEnclave_u.h"

int ocall_uname(struct utsname *name)
{
	return uname(name);
}