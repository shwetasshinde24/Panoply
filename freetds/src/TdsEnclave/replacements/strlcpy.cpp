/* FreeTDS - Library of routines accessing Sybase and Microsoft databases
 * Copyright (C) 2005 Ziglio Frediano
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
#include <config.h>

#include <string.h>
#include "sgx_stdio_util.h"

#include <freetds/sysdep_private.h>
#include <stdarg.h>



// #define test_fprintf(format, ...) { va_list ap; va_start(ap, format); int ret; sgx_wrapper_vfprintf(&ret, 3, format, &ap); va_end(ap, format); }

size_t 
tds_strlcpy(char *dest, const char *src, size_t len)
{
	sgx_wrapper_fprintf(SGX_STDERR, "This is a test: %d %d %d \n \n",3,4,5);
	size_t l = strlen(src);

	if (len) {
		--len;
		if (l > len) {
			memcpy(dest, src, len);
			dest[len] = 0;
		} else {
			memcpy(dest, src, l + 1);
		}
	}
	return l;
}
