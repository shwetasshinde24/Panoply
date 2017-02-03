#ifndef SGX_SYSEPOLL_T_H__
#define SGX_SYSEPOLL_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "struct/sgx_sysepoll_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_epoll_create(int* retval, int __size);
sgx_status_t SGX_CDECL ocall_epoll_create1(int* retval, int __flags);
sgx_status_t SGX_CDECL ocall_epoll_ctl(int* retval, int __epfd, int __op, int __fd, void* __event, int event_size);
sgx_status_t SGX_CDECL ocall_epoll_wait(int* retval, int __epfd, void* __events, int event_size, int __maxevents, int __timeout);
sgx_status_t SGX_CDECL ocall_epoll_wait1(int* retval, int __epfd, void* __events, int event_size, int __maxevents, int __timeout);
sgx_status_t SGX_CDECL ocall_epoll_wait2(int* retval, int __epfd, void* __events, int event_size, int __maxevents, int __timeout);
sgx_status_t SGX_CDECL ocall_epoll_wait3(int* retval, int __epfd, void* __events, int event_size, int __maxevents, int __timeout);
sgx_status_t SGX_CDECL ocall_epoll_wait4(int* retval, int __epfd, void* __events, int event_size, int __maxevents, int __timeout);
sgx_status_t SGX_CDECL ocall_epoll_wait5(int* retval, int __epfd, void* __events, int event_size, int __maxevents, int __timeout);
sgx_status_t SGX_CDECL ocall_epoll_wait6(int* retval, int __epfd, void* __events, int event_size, int __maxevents, int __timeout);
sgx_status_t SGX_CDECL ocall_epoll_wait7(int* retval, int __epfd, void* __events, int event_size, int __maxevents, int __timeout);
sgx_status_t SGX_CDECL ocall_epoll_pwait(int* retval, int __epfd, void* __events, int event_size, int __maxevents, int __timeout, void* __ss, int sigset_size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
