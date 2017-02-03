/*
 * lat_connect.c - simple TCP connection latency test
 *
 * Three programs in one -
 *	server usage:	lat_connect -s
 *	client usage:	lat_connect [-N <repetitions>] hostname
 *	shutdown:	lat_connect -hostname
 *
 * lat_connect may not be parallelized because of idiosyncracies
 * with TCP connection creation.  Basically, if the client tries
 * to create too many connections too quickly, the system fills
 * up the set of available connections with TIME_WAIT connections.
 * We can only measure the TCP connection cost accurately if we
 * do just a few connections.  Since the parallel harness needs
 * each child to run for a second, this guarantees that the 
 * parallel version will generate inaccurate results.
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
// Fix me: id is share now
// char	*id = "$Id$\n";
#include "bench.h"


void	latconnect_server_main(int ac, char **av);
void	latconnect_client_main(int ac, char **av);

void
latconnect_doit(char *server)
{
	int	sock = tcp_connect(server, TCP_CONNECT, SOCKOPT_NONE);
	close(sock);
}

int
latconnect_main(int ac, char **av)
{
	if (ac != 2) {
		fprintf(stderr, "Usage: %s -s OR %s [-]serverhost\n",
		    av[0], av[0]);
		exit(1);
	}
	if (!strcmp(av[1], "-s")) {
		if (fork() == 0) {
			latconnect_server_main(ac, av);
		}
		exit(0);
	} else {
		latconnect_client_main(ac, av);
	}
	exit(0);
	/* NOTREACHED */
}

void
latconnect_client_main(int ac, char **av)
{
	int     sock;
	char	*server;
	char	buf[256];

	if (ac != 2) {
		fprintf(stderr, "usage: %s host\n", av[0]);
		exit(1);
	}

	char* av1 = strdup(av[1]);

	server = av1[0] == '-' ? &av1[1] : av1;

	/*
	 * Stop server code.
	 */
	if (av1[0] == '-') {
		sock = tcp_connect(server, TCP_CONNECT, SOCKOPT_NONE);
		write(sock, "0", 1);
		close(sock);
		exit(0);
		/* NOTREACHED */
	}

	/*
	 * We don't want more than a few of these, they stack up in time wait.
	 * XXX - report an error if the clock is too shitty?
	 */
	BENCH(latconnect_doit(server), 0);
	snprintf(buf, 256, "TCP/IP connection cost to %s", server);
	micro(buf, get_n());
	exit(0);
	/* NOTREACHED */
}

void
latconnect_server_main(int ac, char **av)
{
	int     newsock, sock, n;
	char	c;

	if (ac != 2) {
		fprintf(stderr, "usage: %s -s\n", av[0]);
		exit(1);
	}
	GO_AWAY;
	sock = tcp_server(TCP_CONNECT, SOCKOPT_REUSE);
	for (;;) {
		newsock = tcp_accept(sock, SOCKOPT_NONE);
		c = 0;
		n = read(newsock, &c, 1);
		if (n > 0 && c == '0') {
			tcp_done(TCP_CONNECT);
			exit(0);
		}
		close(newsock);
	}
	/* NOTREACHED */
}
