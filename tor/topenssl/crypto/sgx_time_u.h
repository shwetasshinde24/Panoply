#ifndef SGX_TIME_U_H__
#define SGX_TIME_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "time.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

time_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_time, (time_t* t));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_gettimeofday, (void* tv, int tv_size, void* tz, int tz_size));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_gettimeofday2, (void* tv, int tv_size));
clock_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_clock, ());
struct tm* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_gmtime_r, (const time_t* timer, struct tm* tp));
struct tm* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_localtime_r, (const time_t* timer, struct tm* tp));
time_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mktime, (struct tm* tp));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
