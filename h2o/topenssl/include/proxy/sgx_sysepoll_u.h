#ifndef SGX_SYSEPOLL_U_H__
#define SGX_SYSEPOLL_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_sysepoll_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_epoll_create, (int __size));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_epoll_create1, (int __flags));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_epoll_ctl, (int __epfd, int __op, int __fd, void* __event, int event_size));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_epoll_wait, (int __epfd, void* __events, int event_size, int __maxevents, int __timeout));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_epoll_wait1, (int __epfd, void* __events, int event_size, int __maxevents, int __timeout));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_epoll_wait2, (int __epfd, void* __events, int event_size, int __maxevents, int __timeout));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_epoll_wait3, (int __epfd, void* __events, int event_size, int __maxevents, int __timeout));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_epoll_wait4, (int __epfd, void* __events, int event_size, int __maxevents, int __timeout));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_epoll_wait5, (int __epfd, void* __events, int event_size, int __maxevents, int __timeout));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_epoll_wait6, (int __epfd, void* __events, int event_size, int __maxevents, int __timeout));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_epoll_wait7, (int __epfd, void* __events, int event_size, int __maxevents, int __timeout));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_epoll_pwait, (int __epfd, void* __events, int event_size, int __maxevents, int __timeout, void* __ss, int sigset_size));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
