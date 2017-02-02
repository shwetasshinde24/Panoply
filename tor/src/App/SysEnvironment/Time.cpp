/**
*   Copyright(C) 2011-2015 Intel Corporation All Rights Reserved.
*
*   The source code, information  and  material ("Material") contained herein is
*   owned  by Intel Corporation or its suppliers or licensors, and title to such
*   Material remains  with Intel Corporation  or its suppliers or licensors. The
*   Material  contains proprietary information  of  Intel or  its  suppliers and
*   licensors. The  Material is protected by worldwide copyright laws and treaty
*   provisions. No  part  of  the  Material  may  be  used,  copied, reproduced,
*   modified, published, uploaded, posted, transmitted, distributed or disclosed
*   in any way  without Intel's  prior  express written  permission. No  license
*   under  any patent, copyright  or  other intellectual property rights  in the
*   Material  is  granted  to  or  conferred  upon  you,  either  expressly,  by
*   implication, inducement,  estoppel or  otherwise.  Any  license  under  such
*   intellectual  property  rights must  be express  and  approved  by  Intel in
*   writing.
*
*   *Third Party trademarks are the property of their respective owners.
*
*   Unless otherwise  agreed  by Intel  in writing, you may not remove  or alter
*   this  notice or  any other notice embedded  in Materials by Intel or Intel's
*   suppliers or licensors in any way.
*/

#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include "TorEnclave_u.h"

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
