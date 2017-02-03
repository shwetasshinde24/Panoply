/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <ifaddrs.h>
#include "MyEnclave_u.h"

int ocall_getifaddrs(struct ifaddrs **ifap)
{
	return getifaddrs(ifap);
}

void ocall_freeifaddrs(struct ifaddrs *ifa)
{
	freeifaddrs(ifa);
}