/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sys/utsname.h>

#include "MyEnclave_u.h"

int ocall_uname(struct utsname *name)
{
	return uname(name);
}