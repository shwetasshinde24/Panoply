#include <sgx_netif_util.h>
#include <sgx_ocall_util.h>

unsigned int sgx_wrapper_if_nametoindex(const char *ifname)
{
	unsigned int retval;
	sgx_status_t status = ocall_if_nametoindex(&retval, ifname);
	CHECK_STATUS(status);
	return retval;
}

char *sgx_wrapper_if_indextoname(unsigned int ifindex, char *ifname)
{
	char* retval;
	sgx_status_t status = ocall_if_indextoname(&retval, ifindex, ifname);
	CHECK_STATUS(status);
	return retval;
}

struct if_nameindex *sgx_wrapper_if_nameindex(void)
{
	struct if_nameindex *retval;
	sgx_status_t status = ocall_if_nameindex(&retval);
	CHECK_STATUS(status);
	return retval;
}

void sgx_wrapper_if_freenameindex(struct if_nameindex *ptr)
{
	sgx_status_t status = ocall_if_freenameindex(ptr);
	CHECK_STATUS(status);
}