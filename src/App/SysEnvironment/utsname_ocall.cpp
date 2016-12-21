#include <sys/utsname.h>

#include "TopensslEnclave_u.h"

extern void increase_ocall_count();

int ocall_uname(struct utsname *name)
{
    increase_ocall_count();
	return uname(name);
}