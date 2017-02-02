#include <freetds/compilemode.h>

#if defined(PORT_DEBUG)

#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

#else

#ifndef FREETDS_TIME_H
#define FREETDS_TIME_H
// struct timeval	{
//   	long         tv_sec;      
//   	long long    tv_usec;     	
// };
#include <time.h>
#endif

#endif


