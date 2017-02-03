#include <net/if.h>
#include "TdsEnclave_u.h"

unsigned int ocall_if_nametoindex(const char *ifname)
{
	return if_nametoindex(ifname);
}

char *ocall_if_indextoname(unsigned int ifindex, char *ifname)
{
	return if_indextoname(ifindex, ifname);
}

struct if_nameindex *ocall_if_nameindex(void)
{
	return if_nameindex();
}

void ocall_if_freenameindex(struct if_nameindex *ptr)
{
	if_freenameindex(ptr);
}