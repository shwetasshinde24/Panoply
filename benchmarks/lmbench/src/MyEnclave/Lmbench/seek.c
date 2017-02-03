// char	*id = "$Id$\n";
/*
 * Seek - calculate seeks as a function of distance.
 *
 * Usage: seek file size
 *
 * Copyright (c) 1994,1995,1996 Larry McVoy.  All rights reserved.
 */

#include	"bench.h"

#define	STRIDE	1024*1024

seek_main(int ac, char  	**av)
{
	char	buf[512];
	int	disk;
	off64_t	size;
	off64_t	begin, end;
	int	usecs;

	if (ac != 3) {
		exit(1);
	}
	char argbuf[500];
	if (copy_arg_to_enclave(argbuf, 500, av, 1)<0)	{
			printf("Cannot copy arg in \n");
			return -1;
	}

	if ((disk = open(argbuf, 0)) == -1) {
		exit(1);
	}

	if (copy_arg_to_enclave(argbuf, 500, av, 2)<0)	{
			printf("Cannot copy arg in \n");
			return -1;
	}
	size = bytes(argbuf);

	/*
	 * We flip back and forth, in strides of 1MB.
	 * If we have a 100MB disk, that means we do
	 * 1, 99, 2, 98, etc.
	 */
	end = size;
	begin = 0;
	seekto(disk, begin, SEEK_SET);
	read(disk, buf, sizeof(buf));
	while (end > begin) {
		end -= STRIDE;
		start();
		seekto(disk, end, SEEK_SET);
		read(disk, buf, sizeof(buf));
		usecs = stop();
		printf("%.04f %.04f\n", (end - begin) / 1000000., usecs/1000.);

		begin += STRIDE;
		start();
		seekto(disk, begin, SEEK_SET);
		read(disk, buf, sizeof(buf));
		usecs = stop();
		printf("%.04f %.04f\n", (end - begin) / 1000000., usecs/1000.);
	}
	_exit(0);
}
