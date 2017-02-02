/* FreeTDS - Library of routines accessing Sybase and Microsoft databases
 * Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003, 2004  Brian Bruns
 * Copyright (C) 2005-2015  Frediano Ziglio
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

#include "../TdsEnclave.h"
#include "TdsEnclave_t.h"
#include "../user_types.h"
#include <config.h>

#include <stdarg.h>
#include <stdio.h>

#include <unistd.h>

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <freetds/tds_enclave.h>
#include <freetds/thread_enclave.h>


/*
 * If reentrant code was not requested, we don't care reentrancy, so
 * just assume the standard BSD netdb interface is reentrant and use it.
 */
#ifndef _REENTRANT
# undef NETDB_REENTRANT
# define NETDB_REENTRANT 1
#endif /* _REENTRANT */

#if !defined(HAVE_GETADDRINFO)

#if defined(NETDB_REENTRANT)
struct hostent *
tds_gethostbyname_r(const char *servername, struct hostent *result, char *buffer, int buflen, int *h_errnop)
{
	return gethostbyname(servername);
}

#elif defined(HAVE_GETIPNODEBYNAME) || defined(HAVE_GETIPNODEBYADDR)
/**
 * Copy a hostent structure to an allocated buffer
 * @return 0 on success, -1 otherwise
 */
static int
tds_copy_hostent(struct hostent *he, struct hostent *result, char *buffer, int buflen)
{
#define CHECK_BUF(len) \
	if (p + sizeof(struct hostent) - buffer > buflen) return -1;
#define ALIGN_P do { p += TDS_ALIGN_SIZE - 1; p -= (p-buffer) % TDS_ALIGN_SIZE; } while(0)

	int n, i;
	char *p = buffer;
	struct hostent *he2;

	/* copy structure */
	he2 = result;
	memcpy(he2, he, sizeof(struct hostent));

	if (he->h_addr_list) {
		int len;
		char **addresses;

		/* count addresses */
		for (n = 0; he->h_addr_list[n]; ++n)
			continue;

		/* copy addresses */
		addresses = (char **) p;
		he2->h_addr_list = (char **) p;
		len = sizeof(char *) * (n + 1);
		CHECK_BUF(len);
		p += len;
		ALIGN_P;
		for (i = 0; i < n; ++i) {
			addresses[i] = p;

			CHECK_BUF(he->h_length);
			memcpy(p, he->h_addr_list[i], he->h_length);
			p += he->h_length;
			ALIGN_P;
		}
		addresses[n] = NULL;
	}

	/* copy name */
	if (he->h_name) {
		n = strlen(he->h_name) + 1;
		he2->h_name = p;
		CHECK_BUF(n);
		memcpy(p, he->h_name, n);
		p += n;
		ALIGN_P;
	}

	if (he->h_aliases) {
		int len;
		char **aliases;

		/* count aliases */
		for (n = 0; he->h_aliases[n]; ++n)
			continue;

		/* copy aliases */
		aliases = (char **) p;
		he2->h_aliases = (char **) p;
		len = sizeof(char *) * (n + 1);
		CHECK_BUF(len);
		p += len;
		for (i = 0; i < n; ++i) {
			len = strlen(he->h_aliases[i]) + 1;
			aliases[i] = p;

			CHECK_BUF(len);
			memcpy(p, he->h_aliases[i], len);
			p += len;
		}
		aliases[n] = NULL;
	}
	return 0;
}

struct hostent *
tds_gethostbyname_r(const char *servername, struct hostent *result, char *buffer, int buflen, int *h_errnop)
{
	struct hostent *he = getipnodebyname(servername, AF_INET, 0, h_errnop);

	if (!he)
		return NULL;
	if (tds_copy_hostent(he, result, buffer, buflen)) {
		errno = ENOMEM;
		if (h_errnop)
			*h_errnop = NETDB_INTERNAL;
		freehostent(he);
		return NULL;
	}
	freehostent(he);
	return result;
}

#elif defined(HAVE_FUNC_GETHOSTBYNAME_R_6)
struct hostent *
tds_gethostbyname_r(const char *servername, struct hostent *result, char *buffer, int buflen, int *h_errnop)
{
	if (gethostbyname_r(servername, result, buffer, buflen, &result, h_errnop))
		return NULL;
	return result;
}

#elif defined(HAVE_FUNC_GETHOSTBYNAME_R_5)
struct hostent *
tds_gethostbyname_r(const char *servername, struct hostent *result, char *buffer, int buflen, int *h_errnop)
{
	result = gethostbyname_r(servername, result, buffer, buflen, h_errnop);
	return result;
}

#elif defined(HAVE_FUNC_GETHOSTBYNAME_R_3)
struct hostent *
tds_gethostbyname_r(const char *servername, struct hostent *result, char *buffer, int buflen, int *h_errnop)
{
	struct hostent_data *data = (struct hostent_data *) buffer;

	memset(buffer, 0, buflen);
	if (gethostbyname_r(servername, result, data)) {
		*h_errnop = 0;
		result = NULL;
	}
	return result;
}

#elif defined(TDS_NO_THREADSAFE)
struct hostent *
tds_gethostbyname_r(const char *servername, struct hostent *result, char *buffer, int buflen, int *h_errnop)
{
	return gethostbyname(servername);
}

#else
#error gethostbyname_r style unknown
#endif

#endif


#if 0
#undef HAVE_GETADDRINFO
#undef NETDB_REENTRANT
#undef HAVE_FUNC_GETSERVBYNAME_R_6
#undef HAVE_FUNC_GETSERVBYNAME_R_5
#undef HAVE_FUNC_GETSERVBYNAME_R_4
#undef TDS_NO_THREADSAFE

# if 0
#  define HAVE_FUNC_GETSERVBYNAME_R_6 1
int test_getservbyname_r(const char *name, const char *proto,
			 struct servent *result_buf, char *buffer,
			 size_t buflen, struct servent **result);
#  define getservbyname_r test_getservbyname_r
# elif 0
#  define HAVE_FUNC_GETSERVBYNAME_R_5 1
struct servent *
test_getservbyname_r(const char *name, const char *proto,
		     struct servent *result_buf, char *buffer,
		     size_t buflen);
#  define getservbyname_r test_getservbyname_r
# else
#  define HAVE_FUNC_GETSERVBYNAME_R_4 1
struct servent_data { int dummy; };
int
test_getservbyname_r(const char *name, const char *proto,
		     struct servent *result_buf,
		     struct servent_data *data);
#  define getservbyname_r test_getservbyname_r
# endif
#endif



