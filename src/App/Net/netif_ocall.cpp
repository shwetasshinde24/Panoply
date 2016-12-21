#include <net/if.h>
#include "TopensslEnclave_u.h"

extern void increase_ocall_count();

unsigned int ocall_if_nametoindex(const char *ifname)
{
    increase_ocall_count();
	return if_nametoindex(ifname);
}

char *ocall_if_indextoname(unsigned int ifindex, char *ifname)
{
    increase_ocall_count();
	return if_indextoname(ifindex, ifname);
}

struct if_nameindex *ocall_if_nameindex(void)
{
    increase_ocall_count();
	return if_nameindex();
}

void ocall_if_freenameindex(struct if_nameindex *ptr)
{
    increase_ocall_count();
	if_freenameindex(ptr);
}