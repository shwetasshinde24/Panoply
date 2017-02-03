/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include "MyEnclave_u.h"

time_t ocall_time(time_t *t)  
{
    return time(t);
}

int ocall_gettimeofday(void *tv_cast, int tv_size, void *tz_cast, int tz_size)	
{
	struct timeval *tv = (struct timeval*)tv_cast;
	struct timezone *tz = (struct timezone*)tz_cast;
	return gettimeofday(tv, tz);
}

int ocall_gettimeofday2(void *tv_cast, int tv_size)	
{
	struct timeval tv; // (struct timeval*)tv_cast;
	int ret = gettimeofday(&tv, NULL);
	memcpy(tv_cast, &tv, sizeof(struct timeval));
	return ret;
}


clock_t ocall_clock(void)	
{
	return clock();
}

time_t ocall_mktime(struct tm *tp)	
{
	return mktime(tp);
}

struct tm *ocall_gmtime_r(const time_t *timer, struct tm *tp)
{
	return gmtime_r(timer, tp);
}

struct tm *ocall_localtime_r(const time_t *timer, struct tm *tp)
{
	return localtime_r(timer, tp);
}

int ocall_getitimer(int which, struct itimerval *curr_value)
{
	return getitimer(which, curr_value);
}

int ocall_setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value)
{
	return setitimer(which, new_value, old_value);
}

int ocall_nanosleep(const struct timespec *req, struct timespec *rem)
{
	return nanosleep(req, rem);
}