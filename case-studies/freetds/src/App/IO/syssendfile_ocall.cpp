#include <sys/sendfile.h>

#include "TdsEnclave_u.h"

ssize_t ocall_sendfile (int out_fd, int in_fd, off_t *offset, size_t count)
{
	return sendfile(out_fd, in_fd, offset, count);
}