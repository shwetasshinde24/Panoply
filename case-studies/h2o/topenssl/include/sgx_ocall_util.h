#ifndef SGX_OCALL_UTIL_H
#define SGX_OCALL_UTIL_H

#include <sgx_stdio_util.h>

#define sgx_debug(A) sgx_wrapper_printf_debug("Sgx error code: %x - in line %d of file %s (function %s)\n",\
                      A, __LINE__, __FILE__, __func__)

# define CHECK_STATUS(status)             \
	do {    \
	    if (status!=SGX_SUCCESS) {             \
	        sgx_debug(status);\
	        abort();    \
	    } 		\
	}			\
	while (0)

# define INIT_LOCK(name)	\
	sgx_thread_mutex_t mt_lock_##name = SGX_THREAD_MUTEX_INITIALIZER

# define LOCK(name)	\
	sgx_thread_mutex_lock(&mt_lock_##name)

# define UNLOCK(name)	\
	sgx_thread_mutex_unlock(&mt_lock_##name)	

#define SAFE_INVOKE(name, ...)                     \
    ({                                              \
        sgx_status_t tmp = SGX_ERROR_UNEXPECTED;    \
        LOCK(name);     \
        tmp = name(__VA_ARGS__);       \
        UNLOCK(name);        \
        tmp;                                     \
    })

#endif