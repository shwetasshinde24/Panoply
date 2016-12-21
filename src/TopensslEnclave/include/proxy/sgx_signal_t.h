#ifndef SGX_SIGNAL_T_H__
#define SGX_SIGNAL_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "struct/sgx_signal_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_sigemptyset(int* retval, sigset_t* set);
sgx_status_t SGX_CDECL ocall_sigfillset(int* retval, sigset_t* set);
sgx_status_t SGX_CDECL ocall_sigaddset(int* retval, sigset_t* set, int signo);
sgx_status_t SGX_CDECL ocall_sigdelset(int* retval, sigset_t* set, int signo);
sgx_status_t SGX_CDECL ocall_sigismember(int* retval, const sigset_t* set, int signo);
sgx_status_t SGX_CDECL ocall_sigsuspend(int* retval, const sigset_t* set);
sgx_status_t SGX_CDECL ocall_sigaction(int* retval, int sig, const struct sigaction* act, struct sigaction* oact);
sgx_status_t SGX_CDECL ocall_sigpending(int* retval, sigset_t* set);
sgx_status_t SGX_CDECL ocall_sigwait(int* retval, const sigset_t* set, int* sig);
sgx_status_t SGX_CDECL ocall_signal(__sighandler_t* retval, int __sig, __sighandler_t __handler);
sgx_status_t SGX_CDECL ocall_raise(int* retval, int sig);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
