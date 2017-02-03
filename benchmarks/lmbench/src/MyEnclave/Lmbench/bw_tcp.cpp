/*
 * bw_tcp.c - simple TCP bandwidth test
 *
 * Three programs in one -
 *	server usage:	bw_tcp -s
 *	client usage:	bw_tcp [-m <message size>] [-M <total bytes>] [-P <parallelism>] [-W <warmup>] [-N <repetitions>] hostname 
 *	shutdown:	bw_tcp -hostname
 *
 * Copyright (c) 2000 Carl Staelin.
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
// char	*id = "$Id$\n";
#define LIBTCP_VERBOSE
#include "bench.h"
#include <MyEnclave_t.h>
// #include "bench.h"

int	bwtcp_server_main(int ac, char **av);
int	bwtcp_client_main(int ac, char **av);
void	bwtcp_source(int data);

void
transfer(uint64 msgsize, int server, char *buf)
{
	int	c;

	while ((c = read(server, buf, msgsize)) > 0) {
		msgsize -= c;
	}
	if (c < 0) {
		perror("bw_tcp: transfer: read failed");
		exit(4);
	}
}

/* ARGSUSED */
int
bwtcp_client_main(int ac, char **av)
{
	int	server;
	uint64	msgsize = XFERSIZE;
	uint64	usecs;
	char	t[512];
	char*	buf;
	char*	usage = "usage: %s -remotehost OR %s remotehost [msgsize]\n";
	int	byte;

	if (ac != 2 && ac != 3) {
		(void)fprintf(stderr, usage, av[0], av[0]);
		exit(0);
	}
	if (ac == 3) {
		msgsize = bytes(av[2]);
	}

	char* av1 = strdup(av[1]);
	/*
	 * Disabler message to other side.
	 */
	if (av1[0] == '-') {
		server = tcp_connect(&av1[1], TCP_DATA, SOCKOPT_REUSE);
		if (write(server, "0", 1) < 0) {
			perror("tcp write");
			exit(1);
		}
		exit(0);
	}

	buf = valloc(msgsize);
	touch(buf, msgsize);
	if (!buf) {
		perror("valloc");
		exit(1);
	}

	
	server = tcp_connect(av1, TCP_DATA, SOCKOPT_READ|SOCKOPT_REUSE);
	if (server < 0) {
		perror("bw_tcp: could not open socket to server");
		exit(2);
	}

	(void) snprintf(t, 512, "%lu", msgsize);
	if (write(server, t, strlen(t) + 1) != strlen(t) + 1) {
		perror("control write");
		exit(3);
	}

	/*
	 * Send data over socket for at least 7 seconds.
	 * This minimizes the effect of connect & opening TCP windows.
	 */
	BENCH1(transfer(msgsize, server, buf), LONGER);

	BENCH(transfer(msgsize, server, buf), 0);
out:	(void) fprintf(stderr, "Socket bandwidth using %s: ", av[1]);
	mb(msgsize * get_n());
	close(server);
	exit(0);
	/*NOTREACHED*/
}

void
child()
{
	wait(0);
	signal(SIGCHLD, child);
}

/* ARGSUSED */
int
bwtcp_server_main(int ac, char **av)
{
	int	data, newdata;

	GO_AWAY;

	signal(SIGCHLD, child);
	data = tcp_server(TCP_DATA, SOCKOPT_READ|SOCKOPT_WRITE|SOCKOPT_REUSE);
	// printf("Tcp server done \n");
	for ( ;; ) {
		newdata = tcp_accept(data, SOCKOPT_WRITE|SOCKOPT_READ);
		switch (fork()) {
		    case -1:
			perror("fork");
			break;
		    case 0:
			bwtcp_source(newdata);
			exit(0);
		    default:
			close(newdata);
			break;
		}
	}
}

/*
 * Read the number of bytes to be transfered.
 * Write that many bytes on the data socket.
 */
void
bwtcp_source(int data)
{
	int	n;
	char	t[512];
	char*	buf;
	uint64	msgsize;

	bzero((void*)t, 512);
	if (read(data, t, 511) <= 0) {
		perror("control nbytes");
		exit(7);
	}
	sscanf(t, "%lu", &msgsize);
	printf("Msg size: %lu \n", msgsize);

	buf = valloc(msgsize);
	touch(buf, msgsize);
	if (!buf) {
		perror("valloc");
		exit(1);
	}

	/*
	 * A hack to allow turning off the absorb daemon.
	 */
     	if (msgsize == 0) {
		tcp_done(TCP_DATA);
		kill(getppid(), SIGTERM);
		exit(0);
	}
	/*
	fprintf(stderr, "server: msgsize=%llu, t=%s\n", msgsize, t); fflush(stderr);
	/* XXX */
	while ((n = write(data, buf, msgsize)) > 0) {
		// printf("write smth \n");
#ifdef	TOUCH
		touch(buf, msgsize);
#endif
		;
	}
	free(buf);
}


int
bwtcp_main(int ac, char **av)
{
	char*	usage = "Usage: %s -s OR %s -serverhost OR %s serverhost [msgsize]\n";
	if (ac < 2 || 3 < ac) {
		fprintf(stderr, usage, av[0], av[0], av[0]);
		exit(1);
	}
	if (ac == 2 && !strcmp(av[1], "-s")) {
		if (fork() == 0) {
			bwtcp_server_main(ac, av);
		}
		// sleep(500);
		exit(0);
	} else {
		bwtcp_client_main(ac, av);
	}
	return(0);
}
