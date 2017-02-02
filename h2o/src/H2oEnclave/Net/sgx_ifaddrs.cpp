#include <sgx_ifaddrs_util.h>
#include <sgx_ocall_util.h>

int sgx_wrapper_getifaddrs(struct ifaddrs **ifap)
{
	int retval;
	sgx_status_t status = ocall_getifaddrs(&retval, ifap);
	CHECK_STATUS(status);
	return retval;
}

void sgx_wrapper_freeifaddrs(struct ifaddrs *ifa)
{
	sgx_status_t status = ocall_freeifaddrs(ifa);
	CHECK_STATUS(status);
}