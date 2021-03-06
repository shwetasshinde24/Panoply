/*
 * udp_xact.c - simple UDP transaction latency test
 *
 * Three programs in one -
 *	server usage:	lat_udp -s
 *	client usage:	lat_udp [-P <parallelism>] [-W <warmup>] [-N <repetitions>] hostname
 *	shutdown:	lat_udp -S hostname
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
// char	*id = "$Id$\n";
#include "bench.h"
#include 	"lib_udp.h"
#include "MyEnclave_t.h"

void	latudp_client_main(int ac, char **av);
void	latudp_server_main(int ac, char **av);

/*
 * Unadvertise the socket
 */
void
udp_done(int prog)
{
	(void)pmap_unset((u_long)prog, (u_long)1);
}

void
timeout()
{
	fprintf(stderr, "Recv timed out\n");
	exit(1);
}

void
latudp_doit(int sock, int seq)
{
	int net = htonl(seq);
	int ret;

	if (send(sock, &net, sizeof(net), 0) != sizeof(net)) {
		perror("lat_udp client: send failed");
		exit(5);
	}
	if (recv(sock, &ret, sizeof(ret), 0) != sizeof(ret)) {
		perror("lat_udp client: recv failed");
		exit(5);
	}
}

int
latudp_main(int ac, char **av)
{
	if (sizeof(int) != 4) {
		fprintf(stderr, "lat_udp: Wrong sequence size\n");
		return(1);
	}
	if (ac != 2 && ac != 3) {
		fprintf(stderr, "Usage: %s -s OR %s [-]serverhost [proto]\n",
		    av[0], av[0]);
		return(1);
	}

	char* dupav[ac];

	for (int i=0; i<ac; i++)
		dupav[i] = strdup(av[i]);

	if (!strcmp(av[1], "-s")) {
		if (fork() == 0) {
			latudp_server_main(ac, dupav);
		}
		return(0);
	} else {
		latudp_client_main(ac, dupav);
	}
	return(0);
}

void
latudp_client_main(int ac, char **av)
{
	int     sock;
	int     seq = -1;
	char   *server;
	char	buf[256];

	if (ac != 2) {
		fprintf(stderr, "Usage: %s hostname\n", av[0]);
		exit(1);
	}

	server = av[1][0] == '-' ? &av[1][1] : av[1];
	sock = udp_connect(server, UDP_XACT, SOCKOPT_NONE);

	/*
	 * Stop server code.
	 */
	if (av[1][0] == '-') {
		while (seq-- > -5) {
			int	net = htonl(seq);

			(void) send(sock, &net, sizeof(net), 0);
		}
		exit(0);
	}
	signal(SIGALRM, timeout);
	alarm(200);
	BENCH(latudp_doit(sock, ++seq), MEDIUM);
	snprintf(buf, 256, "UDP latency using %s", server);
	micro(buf, get_n());
	exit(0);
}

/* ARGSUSED */
void
latudp_server_main(int ac, char **av)
{
	int     net, sent, seq = 0;
	socklen_t namelen;
	struct sockaddr_in it;
	int sock;

	GO_AWAY;

	sock = udp_server(UDP_XACT, SOCKOPT_NONE);

	// do_udp_server(sock);
	while (1) {
		namelen = sizeof(it);
		if (recvfrom(sock, (void*)&sent, sizeof(sent), 0, 
		    (struct sockaddr*)&it, &namelen) < 0) {
			fprintf(stderr, "lat_udp server: recvfrom: got wrong size\n");
			exit(9);
		}
		
		sent = ntohl(sent);
		if (sent < 0) {
			udp_done(UDP_XACT);
			exit(0);
		}
		if (sent != ++seq) {
			seq = sent;
		}

		net = htonl(seq);
		if (sendto(sock, (void*)&net, sizeof(net), 0, 
		    (struct sockaddr*)&it, sizeof(it)) < 0) {
			perror("lat_udp sendto");
			// exit(9);
		}
	}
}
