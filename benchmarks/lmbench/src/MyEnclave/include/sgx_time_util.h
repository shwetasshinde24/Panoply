/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#ifndef SGX_TIME_UTIL_H
#define SGX_TIME_UTIL_H

#include "struct/sgx_time_struct.h"

#ifdef __cplusplus
extern "C"	{
#endif 

extern time_t sgx_wrapper_time(time_t * tim);
extern int sgx_wrapper_gettimeofday(void * tv, void * tz);
extern struct tm *sgx_wrapper_gmtime_r(const time_t *timer, struct tm *tp);
extern struct tm *sgx_wrapper_localtime_r(const time_t *timer, struct tm *tp);
extern time_t sgx_wrapper_mktime(struct tm *tp);
extern int sgx_wrapper_getitimer(int which, struct itimerval *curr_value);
extern int sgx_wrapper_setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
extern int sgx_wrapper_nanosleep(const struct timespec *req, struct timespec *rem);

#ifdef __cplusplus
}
#endif 

#define time(A) sgx_wrapper_time(A)
#define gettimeofday(A, B) sgx_wrapper_gettimeofday(A, B)
#define gmtime_r(A, B) sgx_wrapper_gmtime_r(A, B)
#define localtime_r(A, B) sgx_wrapper_localtime_r(A, B)
#define mktime(A) sgx_wrapper_mktime(A)
#define getitimer(A, B) sgx_wrapper_getitimer(A, B)
#define setitimer(A, B, C) sgx_wrapper_setitimer(A, B, C)
#define nanosleep(A, B) sgx_wrapper_nanosleep(A, B)


#endif
