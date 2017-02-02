#ifndef SGX_SYSEVENTFD_UTIL_H
#define SGX_SYSEVENTFD_UTIL_H

#ifdef __cplusplus
extern "C"	{
#endif 

extern int sgx_wrapper_eventfd(unsigned int initval, int flags);

#ifdef __cplusplus
}
#endif 


#define eventfd(A, B) sgx_wrapper_eventfd(A, B)

#endif

