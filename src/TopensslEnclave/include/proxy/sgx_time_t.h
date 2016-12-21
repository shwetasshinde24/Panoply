#ifndef SGX_TIME_T_H__
#define SGX_TIME_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "time.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_time(time_t* retval, time_t* t);
sgx_status_t SGX_CDECL ocall_gettimeofday(int* retval, void* tv, int tv_size, void* tz, int tz_size);
sgx_status_t SGX_CDECL ocall_gettimeofday2(int* retval, void* tv, int tv_size);
sgx_status_t SGX_CDECL ocall_clock(clock_t* retval);
sgx_status_t SGX_CDECL ocall_gmtime_r(struct tm** retval, const time_t* timer, struct tm* tp);
sgx_status_t SGX_CDECL ocall_localtime_r(struct tm** retval, const time_t* timer, struct tm* tp);
sgx_status_t SGX_CDECL ocall_mktime(time_t* retval, struct tm* tp);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
