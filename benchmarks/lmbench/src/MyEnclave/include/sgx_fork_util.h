/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#ifndef SGX_FORK_UTIL_H
#define SGX_FORK_UTIL_H

#include <sgx_thread.h>
#include <sgx_trts.h>
#include <sgx_tseal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sgx_unistd_util.h>
#include <sgx_stdio_util.h>

extern void* malloc_mparams_ptr;
extern void* malloc_gm_ptr;
extern size_t mstate_size;
extern size_t mparam_size;

extern size_t* hu_ptr;

#ifdef __cplusplus
extern "C"	{
#endif 

extern int sgx_wrapper_fork();
int ecall_set_pipe_fd(int _parentfd[2], int _childfd[2]);
int ecall_set_parsed_section_info(const char* name, int type, size_t val);

#ifdef __cplusplus
}
#endif 

#define GET_MS_LEAST_ADDR(m) *((size_t*)(((size_t)m)+2*sizeof(unsigned int)+2*sizeof(size_t)))
#define GET_MS_TOP_ADDR(m) *((size_t*)(((size_t)m)+2*sizeof(unsigned int)+2*sizeof(size_t)+2*sizeof(void *)))
#define fork() sgx_wrapper_fork()

// typedef unsigned int flag_t;

// struct malloc_params {
//   size_t magic;
//   size_t page_size;
//   size_t granularity;
//   size_t mmap_threshold;
//   size_t trim_threshold;
//   flag_t default_mflags;
// };

// void printf_malloc_param_info(void *malloc_mparams_ptr)
// {
//     struct malloc_params* ptr = (struct malloc_params*)(malloc_mparams_ptr);
//     printf("magic: %llu - page_size: %u - granularity:%u - mmap_threshold:%llu - trim_threshold:%llu \n", 
//         ptr->magic, ptr->page_size, ptr->granularity, ptr->mmap_threshold, ptr->trim_threshold );
// }

#endif