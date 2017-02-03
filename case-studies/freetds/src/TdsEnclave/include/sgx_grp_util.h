#ifndef SGX_GRP_UTIL_H
#define SGX_GRP_UTIL_H

#include <struct/sgx_grp_struct.h>
#include <proxy/sgx_grp_t.h>

static inline struct group *sgx_wrapper_getgrgid(gid_t gid)
{
	struct group *retval;
	ocall_getgrgid(&retval, gid);
	return retval;
}


static inline int sgx_wrapper_initgroups(const char *user, gid_t group)
{
	int retval;
	ocall_initgroups(&retval, user, group);
	return retval;
}


#define getgrgid(A) sgx_wrapper_getgrgid(A)
#define initgroups(A, B) sgx_wrapper_initgroups(A, B)

#endif