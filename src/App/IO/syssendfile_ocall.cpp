#include <sys/sendfile.h>

#include "TopensslEnclave_u.h"

extern void increase_ocall_count();

ssize_t ocall_sendfile (int out_fd, int in_fd, off_t *offset, size_t count)
{
    increase_ocall_count();
	return sendfile(out_fd, in_fd, offset, count);
}