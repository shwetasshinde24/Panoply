#include <stdlib.h>

#include "TopensslEnclave_u.h"	

extern void increase_ocall_count();

char *ocall_getenv(const char *name)
{
    increase_ocall_count();
	return getenv(name);
}

int ocall_putenv(char *string)
{
    increase_ocall_count();
	return putenv(string);
}

int ocall_clearenv(void)
{
    increase_ocall_count();
	return clearenv();
}

int ocall_setenv(const char *name, const char *value, int replace)
{
    increase_ocall_count();
	return setenv(name, value, replace);
}

int ocall_unsetenv (const char *name)
{
    increase_ocall_count();
	return unsetenv(name);
}

int ocall_mkstemp(char *temp)
{
    increase_ocall_count();
	return mkstemp(temp);
}

char *ocall_mkdtemp(char *temp)
{
    increase_ocall_count();
	return mkdtemp(temp);
}