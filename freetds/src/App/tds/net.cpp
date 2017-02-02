/* FreeTDS - Library of routines accessing Sybase and Microsoft databases
 * Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003  Brian Bruns
 * Copyright (C) 2004-2015  Ziglio Frediano
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#include <config.h>
#include <stdarg.h>
#include <stdio.h>
#include <pthread.h>

// #include <sys/time.h>
// #include <time.h>

#if HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif /* HAVE_SYS_TYPES_H */

#if HAVE_ERRNO_H
#include <errno.h>
#endif /* HAVE_ERRNO_H */

#if HAVE_UNISTD_H
#include <unistd.h>
#endif /* HAVE_UNISTD_H */

#if HAVE_STDLIB_H
#include <stdlib.h>
#endif /* HAVE_STDLIB_H */

#if HAVE_STRING_H
#include <string.h>
#endif /* HAVE_STRING_H */

#if HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif /* HAVE_SYS_SOCKET_H */

#include <netdb.h>

#if HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif /* HAVE_NETINET_IN_H */

#if HAVE_NETINET_TCP_H
#include <netinet/tcp.h>
#endif /* HAVE_NETINET_TCP_H */

#if HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif /* HAVE_ARPA_INET_H */

#if HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif /* HAVE_SYS_IOCTL_H */

#if HAVE_SELECT_H
#include <sys/select.h>
#endif /* HAVE_SELECT_H */

#if HAVE_POLL_H
#include <poll.h>
#endif /* HAVE_POLL_H */

#ifdef HAVE_SYS_EVENTFD_H
#include <sys/eventfd.h>
#endif /* HAVE_SYS_EVENTFD_H */

// #include <freetds/tls.h>

#include <signal.h>
#include <assert.h>
#include <getopt.h>
#include <stdio.h>

#include "../App.h"
#include "TdsEnclave_u.h"
#include "../user_types.h"

#define HAVE_NET_LIB 1
#include <freetds/tds_enclave.h>
#include <freetds/string.h>

/* error is always returned */
#define TDSSELERR   0
#define TDSPOLLURG 0x8000u


#if ENABLE_ODBC_MARS
static void tds_check_cancel(TDSCONNECTION *conn);
#endif

// static inline size_t 
// strlcpy(char *dest, const char *src, size_t len)
// {
// 	size_t l = strlen(src);

// 	if (len) {
// 		--len;
// 		if (l > len) {
// 			memcpy(dest, src, len);
// 			dest[len] = 0;
// 		} else {
// 			memcpy(dest, src, l + 1);
// 		}
// 	}
// 	return l;
// }

/**
 * \addtogroup network
 * @{ 
 */

#ifdef _WIN32
int
tds_socket_init(void)
{
	WSADATA wsadata;

	return WSAStartup(MAKEWORD(1, 1), &wsadata);
}

void
tds_socket_done(void)
{
	WSACleanup();
}
#endif

#if !defined(SOL_TCP) && (defined(IPPROTO_TCP) || defined(_WIN32))
/* fix incompatibility between MS headers */
# ifndef IPPROTO_TCP
#  define IPPROTO_TCP IPPROTO_TCP
# endif
# define SOL_TCP IPPROTO_TCP
#endif

/* Optimize the way we send packets */
#undef USE_CORK
#undef USE_NODELAY
/* On early Linux use TCP_CORK if available */
#if defined(__linux__) && defined(TCP_CORK)
#define USE_CORK 1
/* On *BSD try to use TCP_CORK */
/*
 * NOPUSH flag do not behave in the same way
 * cf ML "FreeBSD 5.0 performance problems with TCP_NOPUSH"
 */
#elif (defined(__FreeBSD__) || defined(__GNU_FreeBSD__) || defined(__OpenBSD__)) && defined(TCP_CORK)
#define USE_CORK 1
/* otherwise use NODELAY */
#elif defined(TCP_NODELAY) && defined(SOL_TCP)
#define USE_NODELAY 1
/* under VMS we have to define TCP_NODELAY */
#elif defined(__VMS)
#define TCP_NODELAY 1
#define USE_NODELAY 1
#endif

/**
 * Set socket to non-blocking
 * @param sock socket to set
 * @return 0 on success or error code
 */
int
wrapper_tds_socket_set_nonblocking(TDS_SYS_SOCKET sock)
{
#if !defined(_WIN32)
	unsigned int ioctl_nonblocking = 1;
#else
	u_long ioctl_nonblocking = 1;
#endif

	if (IOCTLSOCKET(sock, FIONBIO, &ioctl_nonblocking) >= 0)
		return 0;
	return sock_errno;
}

char*
wrapper_tds_addrinfo2str(void *addr_cast, char *name, int namemax)
{
struct addrinfo *addr = (struct addrinfo *)addr_cast;
#ifndef NI_NUMERICHOST
#define NI_NUMERICHOST 0
#endif
	if (!name || namemax <= 0)
		return "";
	if (getnameinfo(addr->ai_addr, addr->ai_addrlen, name, namemax, NULL, 0, NI_NUMERICHOST) == 0)
		return name;
	name[0] = 0;
	return name;
}

/** @} */
