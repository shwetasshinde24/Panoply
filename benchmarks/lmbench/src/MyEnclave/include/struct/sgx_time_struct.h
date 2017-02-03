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

#ifndef _SYS_TIME_H
struct timezone {
   int tz_minuteswest;     /* minutes west of Greenwich */
   int tz_dsttime;         /* type of DST correction */
};
#endif 

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

#ifndef _SYS_TIME_H
#define _SYS_TIME_H	1
/* Values for the first argument to `getitimer' and `setitimer'.  */
enum __itimer_which
  {
    /* Timers run in real time.  */
    ITIMER_REAL = 0,
#define ITIMER_REAL ITIMER_REAL
    /* Timers run only when the process is executing.  */
    ITIMER_VIRTUAL = 1,
#define ITIMER_VIRTUAL ITIMER_VIRTUAL
    /* Timers run when the process is executing and when
       the system is executing on behalf of the process.  */
    ITIMER_PROF = 2
#define ITIMER_PROF ITIMER_PROF
  };

/* Type of the second argument to `getitimer' and
   the second and third arguments `setitimer'.  */
struct itimerval
  {
    /* Value to put into `it_value' when the timer expires.  */
    struct timeval it_interval;
    /* Time to the next timer expiration.  */
    struct timeval it_value;
  };

typedef enum __itimer_which __itimer_which_t;

#endif

#endif