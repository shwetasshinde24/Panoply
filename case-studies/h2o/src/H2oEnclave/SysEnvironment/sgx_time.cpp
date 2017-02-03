#include <sgx_time_util.h>
#include <sgx_ocall_util.h>


time_t sgx_wrapper_time(time_t * tim)
{
	time_t retval;
	sgx_status_t status = ocall_time(&retval, tim);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_gettimeofday(void * tv, void * tz)
{
	int retval;
	sgx_status_t status;
	if (tz!=NULL)
		status = ocall_gettimeofday(&retval, tv, sizeof(struct timeval), tz, sizeof(struct timezone));
	else	{
		status = ocall_gettimeofday2(&retval, tv, sizeof(struct timeval));
	}
	CHECK_STATUS(status);
	return retval;
}

struct tm *sgx_wrapper_gmtime_r(const time_t *timer, struct tm *tp)
{
	struct tm * retval;
	sgx_status_t status = ocall_gmtime_r(&retval, timer, tp);
	CHECK_STATUS(status);
	return tp;
}

struct tm *sgx_wrapper_localtime_r(const time_t *timer, struct tm *tp)
{
	struct tm * retval;
	sgx_status_t status = ocall_localtime_r(&retval, timer, tp);
	CHECK_STATUS(status);
	return tp;
}

time_t sgx_wrapper_mktime(struct tm *tp)	
{
	time_t retval;
	sgx_status_t status = ocall_mktime(&retval, tp);
	CHECK_STATUS(status);
	return tp;
}