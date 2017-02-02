/* FreeTDS - Library of routines accessing Sybase and Microsoft databases
 * Copyright (C) 1998-1999  Brian Bruns
 * Copyright (C) 2005-2010  Frediano Ziglio
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

#include <enclave_locale_wrapper.h>

#include <stdarg.h>
#include <ctype.h>

#if HAVE_STRING_H
#include <string.h>
#endif /* HAVE_STRING_H */

#if HAVE_STDLIB_H
#include <stdlib.h>
#endif /* HAVE_STDLIB_H */

#include <freetds/tds_enclave.h>
#include <freetds/configs.h>
#include <sgx_stdlib_util.h>

static inline char *setlocale(int category, const char *locale)
{
	char * ret;
	wrapper_setlocale(&ret, category, locale);
	return ret;
}

static void tds_parse_locale(const char *option, const char *value, void *param);

/**
 * Get locale information. 
 * @return allocated structure with all information or NULL if error
 */
TDSLOCALE *
tds_get_locale(void)
{
	TDSLOCALE *locale;
	int ocall_ret;
	char *s;
	SGX_WRAPPER_FILE in;

	/* allocate a new structure with hard coded and build-time defaults */
	locale = tds_alloc_locale();
	if (!locale)
		return NULL;

	tdsdump_log(TDS_DBG_INFO1, "Attempting to read locales.conf file\n");

	ocall_fopen(&in, FREETDS_LOCALECONFFILE, "r");
	if (in > 0) {
		tds_read_conf_section(in, "default", tds_parse_locale, locale);

#if HAVE_LOCALE_H
			s = setlocale(LC_ALL, NULL);	
#else
		s = getenv("LANG");
#endif
		if (s && s[0]) {
			int found;
			char buf[128];
			const char *strip = "@._";

			/* do not change environment !!! */
			strlcpy(buf, s, sizeof(buf));

			/* search full name */
			ocall_rewind(in);
			found = tds_read_conf_section(in, buf, tds_parse_locale, locale);

			/*
			 * Here we try to strip some part of language in order to
			 * catch similar language
			 * LANG is composed by 
			 *   language[_sublanguage][.charset][@modified]
			 * ie it_IT@euro or it_IT.UTF-8 so we strip in order
			 * modifier, charset and sublanguage
			 * ie it_IT@euro -> it_IT -> it
			 */
			for (;!found && *strip; ++strip) {
				s = strrchr(buf, *strip);
				if (!s)
					continue;
				*s = 0;
				ocall_rewind(in);
				found = tds_read_conf_section(in, buf, tds_parse_locale, locale);
			}

		}


		ocall_fclose(&ocall_ret, in);
	}
	return locale;
}

static void
tds_parse_locale(const char *option, const char *value, void *param)
{
	TDSLOCALE *locale = (TDSLOCALE *) param;

	if (!strcmp(option, TDS_STR_CHARSET)) {
		free(locale->server_charset);
		locale->server_charset = strdup(value);
	} else if (!strcmp(option, TDS_STR_LANGUAGE)) {
		free(locale->language);
		locale->language = strdup(value);
	} else if (!strcmp(option, TDS_STR_DATEFMT)) {
		free(locale->date_fmt);
		locale->date_fmt = strdup(value);
	}
}
