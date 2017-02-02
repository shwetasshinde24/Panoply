#ifndef SGX_SYSLOG_UTIL_H
#define SGX_SYSLOG_UTIL_H

#include <struct/sgx_syslog_struct.h>
#include <sgx_stdio_util.h>

static inline void sgx_wrapper_closelog (void)
{
	fprintf(stderr, "Fix me: Call dummy sgx_wrapper_closelog \n");
}

/* Open connection to system logger.

   This function is a possible cancellation point and therefore not
   marked with THROW.  */
static inline void sgx_wrapper_openlog (const char *ident, int option, int facility)
{
	fprintf(stderr, "Fix me: Call dummy sgx_wrapper_closelog \n");
}

/* Set the log mask level.  */
static inline int sgx_wrapper_setlogmask (int mask)
{
	fprintf(stderr, "Fix me: Call dummy sgx_wrapper_closelog \n");
	return -1;
}

/* Generate a log message using FMT string and option arguments.

   This function is a possible cancellation point and therefore not
   marked with THROW.  */
static inline void sgx_wrapper_syslog (int pri, const char *fmt, ...)
{
	fprintf(stderr, "Fix me: Call dummy sgx_wrapper_closelog \n");
}

#define closelog() sgx_wrapper_closelog()
#define openlog(A, B, C) sgx_wrapper_openlog(A, B, C)
#define setlogmask(A) sgx_wrapper_setlogmask(A)
#define syslog(A, B, ...) sgx_wrapper_syslog(A, B, ##__VA_ARGS__)

#endif