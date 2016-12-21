#ifndef SGX_STDLIB_U_H__
#define SGX_STDLIB_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getenv, (const char* name));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_putenv, (char* string));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_clearenv, ());
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_setenv, (const char* name, const char* value, int replace));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_unsetenv, (const char* name));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mkstemp, (char* temp));
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mkdtemp, (char* temp));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
