#ifndef SGX_TIME_STRUCT_H
#define SGX_TIME_STRUCT_H

#include <time.h>

# ifndef _STRUCT_TIMEVAL
# define _STRUCT_TIMEVAL 1
struct timeval   {
 time_t tv_sec;
 long int tv_usec;
};
# endif  /* struct timeval */

#if (!defined __timespec_defined					\
     && ((defined _TIME_H						\
	  && (defined __USE_POSIX199309 || defined __USE_MISC		\
	      || defined __USE_ISOC11))					\
	 || defined __need_timespec))
# define __timespec_defined	1

# include <sgx/bits/types.h>	/* This defines __time_t for us.  */

/* POSIX.1b structure for a time value.  This is like a `struct timeval' but
   has nanoseconds instead of microseconds.  */
struct timespec
  {
    __time_t tv_sec;		/* Seconds.  */
    __syscall_slong_t tv_nsec;	/* Nanoseconds.  */
  };

#endif /* timespec not defined and <time.h> or need timespec.  */
#undef	__need_timespec

#endif