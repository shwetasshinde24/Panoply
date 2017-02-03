#include "bench.h"

int
msleep_main(int ac, char **av)
{
	char *av1 = strdup(av[1]);
#if defined(sgi) || defined(sun) || defined(linux)
	usleep(atoi(av1) * 1000);
	return (0);
#else
	fd_set	set;
	int	fd;
	struct	timeval tv;

	tv.tv_sec = 0;
	// printf("Arg: %s \n", buf);
	tv.tv_usec = atoi(av1) * 1000;
	// printf("Tv usec: %u \n", tv.tv_usec);
	FD_ZERO(&set);
	FD_SET(0, &set);
	select(1, &set, 0, 0, &tv);
	return (0);
#endif
}
