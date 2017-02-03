/*
 * lat_tcp.c - simple TCP transaction latency test
 *
 * Three programs in one -
 *	server usage:	tcp_xact -s
 *	client usage:	tcp_xact [-m <message size>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>] hostname
 *	shutdown:	tcp_xact -S hostname
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
// char	*id = "$Id$\n";

#include "bench.h"


void	lattcp_client_main(int ac, char **av);
void	doserver(int sock);
void	doclient(int sock);
void	lattcp_server_main(int ac, char **av);
void	doserver(int sock);

int
lattcp_main(int ac, char **av)
{
	if (ac != 2) {
		fprintf(stderr, "Usage: %s -s OR %s [-]serverhost\n",
		    av[0], av[0]);
		exit(1);
	}
	if (!strcmp(av[1], "-s")) {
		if (fork() == 0) {
			lattcp_server_main(ac, av);
		}
		exit(0);
	} else {
		lattcp_client_main(ac, av);
	}
	return(0);
}

void
lattcp_client_main(int ac, char **av)
{
	int     sock;
	char	*server;
	char	buf[100];

	if (ac != 2) {
		fprintf(stderr, "usage: %s host\n", av[0]);
		exit(1);
	}

	char* av1 = strdup(av[1]);

	server = av1[0] == '-' ? &av1[1] : av1;
	sock = tcp_connect(server, TCP_XACT, SOCKOPT_NONE);

	/*
	 * Stop server code.
	 */
	if (av1[0] == '-') {
		close(sock);
		exit(0);
	}

	BENCH(doclient(sock), MEDIUM);
	snprintf(buf, 100, "TCP latency using %s", av1);
	micro(buf, get_n());
	exit(0);
	/* NOTREACHED */
}

void
doclient(int sock)
{
	char    c;

	write(sock, &c, 1);
	read(sock, &c, 1);
//printf("got %c",c);
}


void
lattcp_child()
{
	wait(0);
	signal(SIGCHLD, lattcp_child);
}

void
lattcp_server_main(int ac, char **av)
{
	int     newsock, sock;

	if (ac != 2) {
		fprintf(stderr, "usage: %s -s\n", av[0]);
		exit(1);
	}
	GO_AWAY;
	signal(SIGCHLD, lattcp_child);
	sock = tcp_server(TCP_XACT, SOCKOPT_NONE);
	for (;;) {
		newsock = tcp_accept(sock, SOCKOPT_NONE);
		switch (fork()) {
		    case -1:
			perror("fork");
			break;
		    case 0:
			doserver(newsock);
			exit(0);
		    default:
			close(newsock);
			break;
		}
	}
	/* NOTREACHED */
}

void
doserver(int sock)
{
	char    c;
	int	n = 0;

	while (read(sock, &c, 1) == 1) {
		write(sock, &c, 1);
		n++;
	}

	/*
	 * A connection with no data means shut down.
	 */
	if (n == 0) {
		tcp_done(TCP_XACT);
		kill(getppid(), SIGTERM);
		exit(0);
	}
}
