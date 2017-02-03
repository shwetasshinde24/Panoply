/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <stdlib.h>

#include "MyEnclave_u.h"	

char *ocall_getenv(const char *name)
{
	return getenv(name);
}

int ocall_putenv(char *string)
{
	return putenv(string);
}

int ocall_clearenv(void)
{
	return clearenv();
}

int ocall_setenv(const char *name, const char *value, int replace)
{
	return setenv(name, value, replace);
}

int ocall_unsetenv (const char *name)
{
	return unsetenv(name);
}

int ocall_mkstemp(char *temp)
{
	return mkstemp(temp);
}

char *ocall_mkdtemp(char *temp)
{
	return mkdtemp(temp);
}