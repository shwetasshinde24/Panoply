#include <sys/eventfd.h>

#include "proxy/sgx_syseventfd_u.h"

int ocall_eventfd(unsigned int initval, int flags)
{
    return eventfd(initval, flags);
}
