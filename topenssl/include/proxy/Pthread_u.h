#ifndef PTHREAD_U_H__
#define PTHREAD_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "struct/sgx_pthread_struct.h"
#include "sgx_eid.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_create, (pthread_t* new_thread, SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, unsigned long int job_id, sgx_enclave_id_t eid));
pthread_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_self, ());
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_join, (pthread_t pt, void** thread_result));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_detach, (pthread_t pt));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_equal, (pthread_t pt1, pthread_t pt2));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_exit, (void* retval));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_cancel, (pthread_t th));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_testcancel, ());
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_attr_init, (SGX_WRAPPER_PTHREAD_ATTRIBUTE* __attr));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_attr_destroy, (SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_attr_getdetachstate, (SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int* __detachstate));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_attr_setdetachstate, (SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int __detachstate));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_attr_getguardsize, (SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t* __guardsize));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_attr_setguardsize, (SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t __guardsize));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_attr_getschedpolicy, (SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int* __policy));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_attr_setschedpolicy, (SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int __policy));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_attr_getstacksize, (SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t* __stacksize));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_attr_setstacksize, (SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t __stacksize));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_setspecific, (pthread_key_t key, const void* value));
void* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_getspecific, (pthread_key_t key));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_pthread_key_create, (pthread_key_t* key, void* destructor));

sgx_status_t ecall_set_enclave_id(sgx_enclave_id_t eid, sgx_enclave_id_t self_eid);
sgx_status_t ecall_execute_job(sgx_enclave_id_t eid, pthread_t pthread_self_id, unsigned long int job_id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
