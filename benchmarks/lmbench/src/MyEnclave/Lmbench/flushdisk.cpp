#ifdef	linux
/*
 * flushdisk() - linux block cache clearing
 */

#include	<sgx_stdio_util.h>
#include	<sgx/sys/types.h>
#include	<sgx_fcntl_util.h>
#include	<sgx_unistd_util.h>
#include	<sgx_stdlib_util.h>
#include	<sgx_sysioctl_util.h>
// #include	<sys/mount.h>

int
flushdisk(int fd)
{
	int	ret = ioctl(fd, BLKFLSBUF, 0);
	usleep(100000);
	return (ret);
}

#endif

#ifdef	MAIN
int
flushdisk_main(int ac, char **av)
{
#ifdef	linux
	int	fd;
	int	i;

	for (i = 1; i < ac; ++i) {
		char abuf[512];
		copy_arg_to_enclave(abuf, 512, av, i);
		fd = open(abuf, 0);
		if (flushdisk(fd)) {
			exit(1);
		}
		close(fd);
	}
#endif
	return(0);
}
#endif
