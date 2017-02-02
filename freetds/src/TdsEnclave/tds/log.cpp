/* FreeTDS - Library of routines accessing Sybase and Microsoft databases
 * Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005  Brian Bruns
 * Copyright (C) 2006-2015  Frediano Ziglio
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
#include "sgx_stdio_util.h"
#include "TdsEnclave_t.h"
#include <config.h>

#include <stdarg.h>

#include <time.h>

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#ifdef _WIN32
# include <process.h>
#endif

#include <freetds/tds_enclave.h>
#include <freetds/checks.h>
#include "tds_types.h"
#include <sgx_thread.h>

/* for now all messages go to the log */
int tds_debug_flags = TDS_DBGFLAG_ALL | TDS_DBGFLAG_SOURCE;
int tds_g_append_mode = 0;
static char *g_dump_filename = NULL;
/** Tell if TDS debug logging is turned on or off */
int tds_write_dump = 0;
static SGX_WRAPPER_FILE g_dumpfile = 0;	/* file pointer for dump log          */
static sgx_thread_mutex_t g_dump_mutex = SGX_THREAD_MUTEX_INITIALIZER;

static SGX_WRAPPER_FILE tdsdump_append(void);

#ifdef TDS_ATTRIBUTE_DESTRUCTOR
static void __attribute__((destructor))
tds_util_deinit(void)
{
	tdsdump_close();
}
#endif

/**
 * Temporarily turn off logging.
 */
void
tdsdump_off(void)
{
	sgx_thread_mutex_lock(&g_dump_mutex);
	tds_write_dump = 0;
	sgx_thread_mutex_unlock(&g_dump_mutex);
}				/* tdsdump_off()  */


/**
 * Turn logging back on.  You must call tdsdump_open() before calling this routine.
 */
void
tdsdump_on(void)
{
	sgx_thread_mutex_lock(&g_dump_mutex);
	if (tdsdump_isopen())
		tds_write_dump = 1;
	sgx_thread_mutex_unlock(&g_dump_mutex);
}

int
tdsdump_isopen()
{
	return g_dumpfile || g_dump_filename;
}


/**
 * Create and truncate a human readable dump file for the TDS
 * traffic.  The name of the file is specified by the filename
 * parameter.  If that is given as NULL or an empty string,
 * any existing log file will be closed.
 *
 * \return  true if the file was opened, false if it couldn't be opened.
 */
int
tdsdump_open(const char *filename)
{
	printf("Start tdsdump_open \n");
	int result;		/* really should be a boolean, not an int */
	int ocall_ret;

	sgx_thread_mutex_lock(&g_dump_mutex);

	/* same append file */
	if (tds_g_append_mode && filename != NULL && g_dump_filename != NULL && strcmp(filename, g_dump_filename) == 0) {
		sgx_thread_mutex_unlock(&g_dump_mutex);
		return 1;
	}

	tds_write_dump = 0;

	/* free old one */
	if (g_dumpfile >0 && g_dumpfile != SGX_STDOUT && g_dumpfile != SGX_STDERR)	{

		ocall_fclose(&ocall_ret, g_dumpfile);
	}
	g_dumpfile = 0;
	if (g_dump_filename)
		TDS_ZERO_FREE(g_dump_filename);

	/* required to close just log ?? */
	if (filename == NULL || filename[0] == '\0') {
		sgx_thread_mutex_unlock(&g_dump_mutex);
		return 1;
	}

	result = 1;
	if (tds_g_append_mode) {
		g_dump_filename = strdup(filename);
		/* if mutex are available do not reopen file every time */
#ifdef TDS_HAVE_MUTEX
		g_dumpfile = tdsdump_append();
#endif
	} else if (!strcmp(filename, "stdout")) {
		g_dumpfile = SGX_STDOUT;
	} else if (!strcmp(filename, "stderr")) {
		g_dumpfile = SGX_STDERR;
	} else	{
		ocall_fopen(&ocall_ret, filename, "w");
		g_dumpfile = ocall_ret;
		if (FILE_IS_NULL(g_dumpfile)) {
		result = 0;
	}

	if (result)
		tds_write_dump = 1;
	sgx_thread_mutex_unlock(&g_dump_mutex);

	if (result) {
		char today[64];
		struct tm res;
		time_t t;

		// time(&t);
		// today[0] = 0;
		// if (tds_localtime_r(&t, &res))
		// 	strftime(today, sizeof(today), "%Y-%m-%d %H:%M:%S", &res);

		// tdsdump_log(TDS_DBG_INFO1, "Starting log file for FreeTDS %s\n"
		// 	    "\ton %s with debug flags 0x%x.\n", VERSION, today, tds_debug_flags);
	}
	}
	printf("return tdsdump_open \n");
	return result;
}				/* tdsdump_open()  */

static SGX_WRAPPER_FILE
tdsdump_append(void)
{
	if (!g_dump_filename)
		return NULL;

	if (!strcmp(g_dump_filename, "stdout")) {
		return SGX_STDOUT;
	} else if (!strcmp(g_dump_filename, "stderr")) {
		return SGX_STDERR;
	}
	int ocall_ret;
	ocall_fopen(&ocall_ret, g_dump_filename, "a");
	return ocall_ret;
}


/**
 * Close the TDS dump log file.
 */
void
tdsdump_close(void)
{
	int ocall_ret;
	sgx_thread_mutex_lock(&g_dump_mutex);
	tds_write_dump = 0;
	if (g_dumpfile >=0 && g_dumpfile != SGX_STDOUT && g_dumpfile != SGX_STDERR)
		ocall_fclose(&ocall_ret, g_dumpfile);
	g_dumpfile = 0;
	if (g_dump_filename)
		TDS_ZERO_FREE(g_dump_filename);
	sgx_thread_mutex_unlock(&g_dump_mutex);
}				/* tdsdump_close()  */

static void
tdsdump_start(SGX_WRAPPER_FILE file, const char *fname, int line)
{
	char buf[128], *pbuf;
	int started = 0;
	int ocall_ret;

	/* write always time before log */
	if (tds_debug_flags & TDS_DBGFLAG_TIME) {
		char *res = NULL;
		tds_timestamp_str(&res, buf, 127);
		ocall_fputs(&ocall_ret, res, file);
		started = 1;
	}

	pbuf = buf;
	if (tds_debug_flags & TDS_DBGFLAG_PID) {
		if (started)
			*pbuf++ = ' ';
		pbuf += snprintf(pbuf, 128, "%d", (int) sgx_thread_self());
		started = 1;
	}

	if ((tds_debug_flags & TDS_DBGFLAG_SOURCE) && fname && line) {
		const char *p;
		p = strrchr(fname, '/');
		if (p)
			fname = p + 1;
		p = strrchr(fname, '\\');
		if (p)
			fname = p + 1;
		if (started)
			pbuf += snprintf(pbuf, 128, " (%s:%d)", fname, line);
		else
			pbuf += snprintf(pbuf, 128, "%s:%d", fname, line);
		started = 1;
	}
	if (started)
		*pbuf++ = ':';
	*pbuf = 0;
	ocall_fputs(&ocall_ret, buf, file);
}

#undef tdsdump_dump_buf
/**
 * Dump the contents of data into the log file in a human readable format.
 * \param file       source file name
 * \param level_line line and level combined. This and file are automatically computed by
 *                   TDS_DBG_* macros.
 * \param msg        message to print before dump
 * \param buf        buffer to dump
 * \param length     number of bytes in the buffer
 */
void
tdsdump_dump_buf(const char* file, unsigned int level_line, const char *msg, const void *buf, size_t length)
{
	size_t i, j;
	int ocall_ret;
#define BYTES_PER_LINE 16
	const unsigned char *data = (const unsigned char *) buf;
	const int debug_lvl = level_line & 15;
	const int line = level_line >> 4;
	int line_buf_size = BYTES_PER_LINE * 8 + 16;
	char line_buf[line_buf_size], *p;
	SGX_WRAPPER_FILE dumpfile;

	if (((tds_debug_flags >> debug_lvl) & 1) == 0 || !tds_write_dump)
		return;

	if (!g_dumpfile && !g_dump_filename)
		return;

	sgx_thread_mutex_lock(&g_dump_mutex);

	dumpfile = g_dumpfile;
#ifdef TDS_HAVE_MUTEX
	if (tds_g_append_mode && dumpfile >0 )
		dumpfile = g_dumpfile = tdsdump_append();
#else
	if (tds_g_append_mode)
		dumpfile = tdsdump_append();
#endif

	if (dumpfile > 0) {
		sgx_thread_mutex_unlock(&g_dump_mutex);
		return;
	}

	tdsdump_start(dumpfile, file, line);

	sgx_wrapper_fprintf(dumpfile, "%s\n", msg);

	for (i = 0; i < length; i += BYTES_PER_LINE) {
		p = line_buf;
		/*
		 * print the offset as a 4 digit hex number
		 */
		p += snprintf(p, line_buf_size, "%04x", ((unsigned int) i) & 0xffffu);

		/*
		 * print each byte in hex
		 */
		for (j = 0; j < BYTES_PER_LINE; j++) {
			if (j == BYTES_PER_LINE / 2)
				*p++ = '-';
			else
				*p++ = ' ';
			if (j + i >= length)
				p += snprintf(p, line_buf_size, "  ");
			else
				p += snprintf(p, line_buf_size, "%02x", data[i + j]);
		}

		/*
		 * skip over to the ascii dump column
		 */
		p += snprintf(p, line_buf_size, " |");

		/*
		 * print each byte in ascii
		 */
		for (j = i; j < length && (j - i) < BYTES_PER_LINE; j++) {
			if (j - i == BYTES_PER_LINE / 2)
				*p++ = ' ';
			p += snprintf(p, line_buf_size, "%c", (isprint(data[j])) ? data[j] : '.');
		}
		strncpy(p, "|\n", strlen("|\n"));
		ocall_fputs(&ocall_ret, line_buf, dumpfile);
	}
	ocall_fputs(&ocall_ret, "\n", dumpfile);

	ocall_fflush(&ocall_ret, dumpfile);

#ifndef TDS_HAVE_MUTEX
	if (tds_g_append_mode) {
		if (dumpfile != SGX_STDOUT && dumpfile != SGX_STDERR)
			ocall_fclose(&ocall_ret, dumpfile);
	}
#endif

	sgx_thread_mutex_unlock(&g_dump_mutex);

}				/* tdsdump_dump_buf()  */
#define tdsdump_dump_buf TDSDUMP_BUF_FAST


#undef tdsdump_log
/**
 * Write a message to the debug log.  
 * \param file name of the log file
 * \param level_line kind of detail to be included
 * \param fmt       printf-like format string
 */
void
tdsdump_log(const char* file, unsigned int level_line, const char *fmt, ...)
{
	/* Disable debug log, apply the same to standard version */
	// printf("Done tdsdump_log %s \n", fmt);
	// Fix me: Temporary disable tdsdump_log
// 	int ocall_ret;
// 	const int debug_lvl = level_line & 15;
// 	const int line = level_line >> 4;
// 	va_list ap;
// 	SGX_WRAPPER_FILE dumpfile;

	// if (((tds_debug_flags >> debug_lvl) & 1) == 0 || !tds_write_dump)
	// 	return;

	// if (!g_dumpfile && !g_dump_filename)
	// 	return;

	// printf("Don't lock me down ");

// 	sgx_thread_mutex_lock(&g_dump_mutex);

// 	dumpfile = g_dumpfile;
// #ifdef TDS_HAVE_MUTEX
// 	if (tds_g_append_mode && dumpfile <= 0)
// 		dumpfile = g_dumpfile = tdsdump_append();
// #else
// 	if (tds_g_append_mode)
// 		dumpfile = tdsdump_append();
// #endif
	
// 	if (dumpfile <= 0) { 
// 		sgx_thread_mutex_unlock(&g_dump_mutex);
// 		return;
// 	}

// 	tdsdump_start(dumpfile, file, line);

// 	va_start(ap, fmt);

// 	ocall_vfprintf(&ocall_ret, dumpfile, fmt, ap);
// 	// ocall_vfprintf(&ocall_ret, 3, fmt, ap);
// 	va_end(ap);

// 	ocall_fflush(&ocall_ret, dumpfile);

// #ifndef TDS_HAVE_MUTEX
// 	if (tds_g_append_mode) {
// 		if (dumpfile != SGX_STDOUT && dumpfile != SGX_STDERR)
// 			ocall_fclose(&ocall_ret, dumpfile);
// 	}
// #endif
// 	sgx_thread_mutex_unlock(&g_dump_mutex);
}				/* tdsdump_log()  */
#define tdsdump_log TDSDUMP_LOG_FAST


/**
 * Write a column value to the debug log.  
 * \param col column to dump
 */
void
tdsdump_col(const TDSCOLUMN *col)
{
	const char* type_name;
	char* data;
	TDS_SMALLINT type;
	
	assert(col);
	assert(col->column_data);
	
	type_name = tds_prtype(col->column_type);
	type = tds_get_conversion_type(col->column_type, col->column_size);
	
	switch(type) {
	case SYBCHAR: 
	case SYBVARCHAR:
		if (col->column_cur_size >= 0) {
			data = (char*) calloc(1, 1 + col->column_cur_size);
			if (!data) {
				tdsdump_log(TDS_DBG_FUNC, "no memory to log data for type %s\n", type_name);
				return;
			}
			memcpy(data, col->column_data, col->column_cur_size);
			tdsdump_log(TDS_DBG_FUNC, "type %s has value \"%s\"\n", type_name, data);
			free(data);
		} else {
			tdsdump_log(TDS_DBG_FUNC, "type %s has value NULL\n", type_name);
		}
		break;
	case SYBINT1:
		tdsdump_log(TDS_DBG_FUNC, "type %s has value %d\n", type_name, (int)*(TDS_TINYINT*)col->column_data);
		break;
	case SYBINT2:
		tdsdump_log(TDS_DBG_FUNC, "type %s has value %d\n", type_name, (int)*(TDS_SMALLINT*)col->column_data);
		break;
	case SYBINT4:
		tdsdump_log(TDS_DBG_FUNC, "type %s has value %d\n", type_name, (int)*(TDS_INT*)col->column_data);
		break;
	case SYBREAL:
		tdsdump_log(TDS_DBG_FUNC, "type %s has value %f\n", type_name, (double)*(TDS_REAL*)col->column_data);
		break;
	case SYBFLT8:
		tdsdump_log(TDS_DBG_FUNC, "type %s has value %f\n", type_name, (double)*(TDS_FLOAT*)col->column_data);
		break;
	default:
		tdsdump_log(TDS_DBG_FUNC, "cannot log data for type %s\n", type_name);
		break;
	}
}