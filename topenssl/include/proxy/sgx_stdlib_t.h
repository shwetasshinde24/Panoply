#ifndef SGX_STDLIB_T_H__
#define SGX_STDLIB_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_getenv(char** retval, const char* name);
sgx_status_t SGX_CDECL ocall_putenv(int* retval, char* string);
sgx_status_t SGX_CDECL ocall_clearenv(int* retval);
sgx_status_t SGX_CDECL ocall_setenv(int* retval, const char* name, const char* value, int replace);
sgx_status_t SGX_CDECL ocall_unsetenv(int* retval, const char* name);
sgx_status_t SGX_CDECL ocall_mkstemp(int* retval, char* temp);
sgx_status_t SGX_CDECL ocall_mkdtemp(char** retval, char* temp);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
