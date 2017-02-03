#ifndef SGX_STDLIB_UTIL_H
#define SGX_STDLIB_UTIL_H

#include <proxy/sgx_stdlib_t.h>
#include <sgx_trts.h>
#include <stdlib.h>
#include <sgx_stdio_util.h>

#ifdef __cplusplus
extern "C"	{
#endif 

extern char *sgx_wrapper_getenv(const char *name);
extern int sgx_wrapper_putenv(char *string);
extern int sgx_wrapper_clearenv(void);
extern void sgx_wrapper_exit(int status);
extern int sgx_wrapper_setenv(const char *name, const char *value, int replace);
extern int sgx_wrapper_unsetenv (const char *name);
extern int sgx_wrapper_random();
extern void sgx_wrapper_srandom (unsigned int seed);
extern int sgx_wrapper_mkstemp(char *string);
extern char *sgx_wrapper_mkdtemp(char *temp);

#ifdef __cplusplus
}
#endif 


#define getenv(A) sgx_wrapper_getenv(A)
#define putenv(A) sgx_wrapper_putenv(A)
#define clearenv() sgx_wrapper_clearenv()
#define exit(A) sgx_wrapper_exit(A)
#define random() sgx_wrapper_random()
#define rand() sgx_wrapper_random()
#define srandom(A) sgx_wrapper_srandom(A)
#define setenv(A, B, C) sgx_wrapper_setenv(A, B, C)
#define unsetenv(A) sgx_wrapper_unsetenv(A)
#define mkdtemp(A) sgx_wrapper_mkdtemp(A)
#define mkstemp(A) sgx_wrapper_mkstemp(A)
#endif 