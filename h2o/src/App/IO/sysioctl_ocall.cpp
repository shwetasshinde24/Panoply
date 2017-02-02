#include <sys/ioctl.h>

#include "proxy/sgx_sysioctl_u.h"

int ocall_ioctl(int fd, unsigned long request, void* arguments)
{
	if (arguments!=NULL)
	{
		return ioctl(fd, request);
	} else {
		return ioctl(fd, request, arguments);
	}
}