#ifndef SGX_GRP_UTIL_H
#define SGX_GRP_UTIL_H

#include <struct/sgx_grp_struct.h>
#include <proxy/sgx_grp_t.h>

#ifdef __cplusplus
extern "C"	{
#endif

extern struct group *sgx_wrapper_getgrgid(gid_t gid) ;
extern int sgx_wrapper_initgroups(const char *user, gid_t group) ;

#ifdef __cplusplus
}
#endif

#define getgrgid(A) sgx_wrapper_getgrgid(A)
#define initgroups(A, B) sgx_wrapper_initgroups(A, B)

#endif