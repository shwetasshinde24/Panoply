#ifndef PTHREAD_T_H__
#define PTHREAD_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "struct/sgx_pthread_struct.h"
#include "sgx_eid.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


void ecall_set_enclave_id(sgx_enclave_id_t self_eid);
void ecall_execute_job(pthread_t pthread_self_id, unsigned long int job_id);

sgx_status_t SGX_CDECL ocall_pthread_create(int* retval, pthread_t* new_thread, SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, unsigned long int job_id, sgx_enclave_id_t eid);
sgx_status_t SGX_CDECL ocall_pthread_self(pthread_t* retval);
sgx_status_t SGX_CDECL ocall_pthread_join(int* retval, pthread_t pt, void** thread_result);
sgx_status_t SGX_CDECL ocall_pthread_detach(int* retval, pthread_t pt);
sgx_status_t SGX_CDECL ocall_pthread_equal(int* retval, pthread_t pt1, pthread_t pt2);
sgx_status_t SGX_CDECL ocall_pthread_exit(void* retval);
sgx_status_t SGX_CDECL ocall_pthread_cancel(int* retval, pthread_t th);
sgx_status_t SGX_CDECL ocall_pthread_testcancel();
sgx_status_t SGX_CDECL ocall_pthread_attr_init(int* retval, SGX_WRAPPER_PTHREAD_ATTRIBUTE* __attr);
sgx_status_t SGX_CDECL ocall_pthread_attr_destroy(int* retval, SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr);
sgx_status_t SGX_CDECL ocall_pthread_attr_getdetachstate(int* retval, SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int* __detachstate);
sgx_status_t SGX_CDECL ocall_pthread_attr_setdetachstate(int* retval, SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int __detachstate);
sgx_status_t SGX_CDECL ocall_pthread_attr_getguardsize(int* retval, SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t* __guardsize);
sgx_status_t SGX_CDECL ocall_pthread_attr_setguardsize(int* retval, SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t __guardsize);
sgx_status_t SGX_CDECL ocall_pthread_attr_getschedpolicy(int* retval, SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int* __policy);
sgx_status_t SGX_CDECL ocall_pthread_attr_setschedpolicy(int* retval, SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int __policy);
sgx_status_t SGX_CDECL ocall_pthread_attr_getstacksize(int* retval, SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t* __stacksize);
sgx_status_t SGX_CDECL ocall_pthread_attr_setstacksize(int* retval, SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t __stacksize);
sgx_status_t SGX_CDECL ocall_pthread_setspecific(int* retval, pthread_key_t key, const void* value);
sgx_status_t SGX_CDECL ocall_pthread_getspecific(void** retval, pthread_key_t key);
sgx_status_t SGX_CDECL ocall_pthread_key_create(int* retval, pthread_key_t* key, void* destructor);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
