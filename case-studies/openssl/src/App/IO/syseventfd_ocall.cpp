#include <sys/eventfd.h>

#include "proxy/sgx_syseventfd_u.h"

extern void increase_ocall_count();

int ocall_eventfd(unsigned int initval, int flags)
{
    increase_ocall_count();
    return eventfd(initval, flags);
}
