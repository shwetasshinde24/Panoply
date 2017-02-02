#ifndef SGX_MEM_UTIL_H
#define SGX_MEM_UTIL_H

#include "sgx_trts.h"

static inline int sgx_wrapper_free (void* p)
{
	if (sgx_is_within_enclave(p, 1))
		free(p);
	else
		ocall_free(p);
}


#endif
