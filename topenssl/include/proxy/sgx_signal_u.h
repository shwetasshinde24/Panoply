#ifndef SGX_SIGNAL_U_H__
#define SGX_SIGNAL_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_signal_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sigemptyset, (sigset_t* set));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sigfillset, (sigset_t* set));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sigaddset, (sigset_t* set, int signo));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sigdelset, (sigset_t* set, int signo));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sigismember, (const sigset_t* set, int signo));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sigsuspend, (const sigset_t* set));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sigaction, (int sig, const struct sigaction* act, struct sigaction* oact));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sigpending, (sigset_t* set));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_sigwait, (const sigset_t* set, int* sig));
__sighandler_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_signal, (int __sig, __sighandler_t __handler));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_raise, (int sig));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
