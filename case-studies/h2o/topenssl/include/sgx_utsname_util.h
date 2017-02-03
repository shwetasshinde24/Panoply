#ifndef SGX_UTSNAME_UTIL_H
#define SGX_UTSNAME_UTIL_H

#include <struct/sgx_utsname_struct.h>
#include <proxy/sgx_utsname_t.h>

#ifdef __cplusplus
extern "C"	{
#endif 

extern int sgx_wrapper_uname(struct utsname *name);

#ifdef __cplusplus
}
#endif 

#define uname(A) sgx_wrapper_uname(A)

#endif 