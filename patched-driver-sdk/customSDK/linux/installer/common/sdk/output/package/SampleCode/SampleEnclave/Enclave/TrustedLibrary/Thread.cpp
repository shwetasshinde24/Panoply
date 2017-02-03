/*
 * Copyright (C) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include "../Enclave.h"
#include "Enclave_t.h"

#include <sgx_thread.h>
#include <sgx_trts.h>
#include <sgx_tseal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
// #include <malloc.h>
typedef unsigned int flag_t;

struct malloc_params {
  size_t magic;
  size_t page_size;
  size_t granularity;
  size_t mmap_threshold;
  size_t trim_threshold;
  flag_t default_mflags;
};

extern void* malloc_mparams_ptr;
extern void* malloc_gm_ptr;
extern size_t mstate_size;
extern size_t mparam_size;
extern int pivot;
static const size_t WORD_SIZE = sizeof(uint64_t);
static char bss[200];
static size_t global_counter = 0;
static sgx_thread_mutex_t global_mutex = SGX_THREAD_MUTEX_INITIALIZER;
static void* unsealed_sync_buffer;
static uint64_t fork_magic;
uint64_t* base_stack_pointer = NULL;
uint64_t* last_fp = NULL;
uint64_t* parent_ret_p = NULL;

#define GET_MS_LEAST_ADDR(m) *((size_t*)(((size_t)m)+2*sizeof(unsigned int)+2*sizeof(size_t)))
#define GET_MS_TOP_ADDR(m) *((size_t*)(((size_t)m)+2*sizeof(unsigned int)+2*sizeof(size_t)+2*sizeof(void *)))

extern uint64_t enc_start_addr;
extern uint64_t sec_data_addr;
extern uint64_t sec_data_size;
extern uint64_t bss_sec_addr;
extern uint64_t bss_sec_size;
extern size_t* hu_ptr;

#define BUFFER_SIZE 50

typedef struct {
    int offset;
    uint64_t newval;
} bss_patch_t;

typedef struct {
    int buf[BUFFER_SIZE];
    int occupied;
    int nextin;
    int nextout;
    sgx_thread_mutex_t mutex;
    sgx_thread_cond_t more;
    sgx_thread_cond_t less;
} cond_buffer_t;

static cond_buffer_t buffer = {{0, 0, 0, 0, 0, 0}, 0, 0, 0,
    SGX_THREAD_MUTEX_INITIALIZER, SGX_THREAD_COND_INITIALIZER, SGX_THREAD_COND_INITIALIZER};

static char end_pivot[500] = "This is the end";
bss_patch_t bss_patch[10];
void* my_address;

// contain_malloc_metadata()
// Parameters:
//      addr - the start address of the buffer
//      size - the size of the buffer
// Return Value:
//      1 - the buffer is partly inside malloc state mem region
//      0 - the whole buffer or part of the buffer is not within malloc state mem region
//
int contain_malloc_metadata(const void *addr, size_t size)
{
    size_t start = reinterpret_cast<size_t>(addr);
    size_t end = 0;
    size_t ms_start = reinterpret_cast<size_t>(malloc_gm_ptr);
    size_t ms_end = ms_start + mstate_size;
    size_t mp_start = reinterpret_cast<size_t>(malloc_mparams_ptr);
    size_t mp_end = mp_start + mparam_size;
    size_t heap_used_addr = reinterpret_cast<size_t>(hu_ptr);

    // so the enclave range is [enclave_start, enclave_end] inclusively
    end = size > 0 ?  start + size : start;

    // Is inside malloc state metadata
    if( (start <= end) && ((start >= ms_start) && (start <= ms_end)) || ((end >= ms_start) && (end <= ms_end)))
    {
        return 1;
    }
    if( (start <= end) && ((start >= mp_start) && (start <= mp_end)) || ((end >= mp_start) && (end <= mp_end)))
    {
        return 1;
    }

    // Contains heap used address
    if (start <= end && heap_used_addr >= start && heap_used_addr <= end )
        return 1;

    return 0;
}

// contain_malloc_metadata()
// Parameters:
//      addr - the start address of the buffer
//      size - the size of the buffer
// Return Value:
//      1 - the buffer is partly inside malloc state mem region
//      0 - the whole buffer or part of the buffer is not within malloc state mem region
//
int inside_malloc_param_struct(const void *addr, size_t size)
{
    size_t start = reinterpret_cast<size_t>(addr);
    size_t end = 0;
    size_t mp_start = reinterpret_cast<size_t>(malloc_mparams_ptr);
    size_t mp_end = mp_start + mparam_size;
    // g_global_data.enclave_end = enclave_base + enclave_size - 1;
    // so the enclave range is [enclave_start, enclave_end] inclusively

    if(size > 0)
    {
        end = start + size - 1;
    }
    else
    {
        end = start;
    }
    if( (start <= end) && (start >= mp_start) && (start <= mp_end) )
    {
        return 1;
    }
    if( (start <= end) && (end >= mp_start) && (end <= mp_end) )
    {
        return 1;
    }
    return 0;
}

/*
 * ecall_increase_counter:
 *   Utilize thread APIs inside the enclave.
 */
size_t ecall_increase_counter(void)
{
    size_t ret = 0;
    for (int i = 0; i < LOOPS_PER_THREAD; i++) {
        sgx_thread_mutex_lock(&global_mutex);
        /* mutually exclusive adding */
        size_t tmp = global_counter;
        global_counter = ++tmp;
        if (4*LOOPS_PER_THREAD == global_counter)
            ret = global_counter;
        sgx_thread_mutex_unlock(&global_mutex);
    }
    return ret;
}

void ecall_producer(void)
{
    for (int i = 0; i < 4*LOOPS_PER_THREAD; i++) {
        cond_buffer_t *b = &buffer;
        sgx_thread_mutex_lock(&b->mutex);
        while (b->occupied >= BUFFER_SIZE)
            sgx_thread_cond_wait(&b->less, &b->mutex);
        b->buf[b->nextin] = b->nextin;
        b->nextin++;
        b->nextin %= BUFFER_SIZE;
        b->occupied++;
        sgx_thread_cond_signal(&b->more);
        sgx_thread_mutex_unlock(&b->mutex);
    }
}

void ecall_consumer(void)
{
    for (int i = 0; i < LOOPS_PER_THREAD; i++) {
        cond_buffer_t *b = &buffer;
        sgx_thread_mutex_lock(&b->mutex);
        while(b->occupied <= 0)
            sgx_thread_cond_wait(&b->more, &b->mutex);
        b->buf[b->nextout++] = 0;
        b->nextout %= BUFFER_SIZE;
        b->occupied--;
        sgx_thread_cond_signal(&b->less);
        sgx_thread_mutex_unlock(&b->mutex);
    }
}

void ecall_dump_data0(int n, size_t size)
{
    unsigned char* buf = (unsigned char*)malloc(size);
    if (buf==NULL)
        abort();

    for (int k=0; k<n; k++) {
        sgx_read_rand(buf, size);
        ocall_write0(buf, size);
    }
    free(buf);
}

void ecall_dump_data1(int n, size_t size)
{
    unsigned char* buf = (unsigned char*)malloc(size);
    if (buf==NULL)
        abort();

    for (int k=0; k<n; k++) {
        sgx_read_rand(buf, size);
        ocall_write1(buf, size);
    }
    free(buf);
}

void ecall_dump_data2(int n, size_t size)
{
    unsigned char* buf = (unsigned char*)malloc(size);
    if (buf==NULL)
        abort();

    for (int k=0; k<n; k++) {
        sgx_read_rand(buf, size);
        ocall_write2(buf, size);
    }
    free(buf);
}

void ecall_dump_data3(int n, size_t size)
{
    unsigned char* buf = (unsigned char*)malloc(size);
    if (buf==NULL)
        abort();

    for (int k=0; k<n; k++) {
        sgx_read_rand(buf, size);
        ocall_write3(buf, size);
    }
    free(buf);
}

void ecall_dump_data4(int n, size_t size)
{
    unsigned char* buf = (unsigned char*)malloc(size);
    if (buf==NULL)
        abort();

    for (int k=0; k<n; k++) {
        sgx_read_rand(buf, size);
        ocall_write4(buf, size);
    }
    free(buf);
}

void ecall_dump_data5(int n, size_t size)
{
    unsigned char* buf = (unsigned char*)malloc(size);
    if (buf==NULL)
        abort();

    for (int k=0; k<n; k++) {
        sgx_read_rand(buf, size);
        ocall_write5(buf, size);
    }
    free(buf);
}

void ecall_dump_data6(int n, size_t size)
{
    unsigned char* buf = (unsigned char*)malloc(size);
    if (buf==NULL)
        abort();

    for (int k=0; k<n; k++) {
        sgx_read_rand(buf, size);
        ocall_write6(buf, size);
    }
    free(buf);
}

void ecall_dump_data7(int n, size_t size)
{
    unsigned char* buf = (unsigned char*)malloc(size);
    if (buf==NULL)
        abort();

    for (int k=0; k<n; k++) {
        sgx_read_rand(buf, size);
        ocall_write7(buf, size);
    }
    free(buf);
}

int inner_sum(int i, int k)
{
    return i+k;
}

void sub_function1(int n, void *b_addr);
void start_fork();

void ecall_sync_stack(void *buffer, int size);

void ecall_test_ctx_switch(void* buffer, int size)
{
    register size_t sp asm ("sp");
    bool is_base_stack = base_stack_pointer==NULL;
    if (is_base_stack)  {
        base_stack_pointer = (uint64_t*)sp;
        //base_stack_pointer += 50;
    }

    if (size==0)   {
        printf("\n Base stack : %p \n", base_stack_pointer);
        void *ret_addr = __builtin_return_address(0);
        printf("Return pointer: %p \n", ret_addr);    
        sub_function1(size, &size);
        printf("Done ecall_test_ctx_switch with res:  \n");
        printf("The heap used : %p \n", *hu_ptr);
        printf("The least addr is: %p \n", GET_MS_LEAST_ADDR(malloc_gm_ptr));
        printf("The top addr is: %p \n", GET_MS_TOP_ADDR(malloc_gm_ptr));
    } else {
        ecall_sync_stack(buffer, size);
    }

    // return 1;

    if (is_base_stack)
        base_stack_pointer = NULL;

}

void print_some_interesting_thing()
{
    // for (int i=0; i<100; i++)
    //     printf("Lalalalalalala \n");
}

void *tmp_ret_addr;
bool is_origin = false;
static char fillin[100];

void printf_stack_info(char *sp, char* fp)
{
    printf("%p --- %p \n", sp, fp);
    for(uint64_t* p=(uint64_t*)sp; p<(uint64_t*)fp+5; p++)
        printf("%llx ", *p);

    printf("\n");
}

void printf_malloc_param_info(void *malloc_mparams_ptr)
{
    struct malloc_params* ptr = (struct malloc_params*)(malloc_mparams_ptr);
    printf("magic: %llu - page_size: %u - granularity:%u - mmap_threshold:%llu - trim_threshold:%llu \n", 
        ptr->magic, ptr->page_size, ptr->granularity, ptr->mmap_threshold, ptr->trim_threshold );
}

void sync_the_heap()
{
    if (is_origin) {
        return;
    }

    uint64_t* sec_buff = (uint64_t*)unsealed_sync_buffer;
    uint64_t sync_enc_start_addr = sec_buff[0];
    uint64_t sync_dsec_size = sec_buff[1];
    uint64_t sync_bsec_size = sec_buff[2];
    uint64_t sync_stack_size = sec_buff[3];
    uint64_t sync_heap_size = sec_buff[4];
    uint64_t sync_mlstate_size = sec_buff[5];
    uint64_t sync_mlparam_size = sec_buff[6];

    if (sync_mlstate_size*WORD_SIZE!=mstate_size || sync_mlparam_size*WORD_SIZE!=mparam_size)
    {
        printf("Malloc state struct is not matched \n");
        printf("Ml state size diff: %u - %u \n", sync_mlstate_size*WORD_SIZE, mstate_size);
        printf("Ml para, size diff: %u - %u \n", sync_mlparam_size*WORD_SIZE, mparam_size);
        abort();        
    }

    uint64_t* hsec_buff = sec_buff+7+sync_dsec_size+sync_bsec_size+sync_stack_size;
    uint64_t* mlstate_buff = sec_buff+7+sync_dsec_size+sync_bsec_size+sync_stack_size+sync_heap_size;
    uint64_t* mlparam_buff = sec_buff+7+sync_dsec_size+sync_bsec_size+sync_stack_size+sync_heap_size+sync_mlstate_size;

    // Copy sync_heap to stack and free the heap region
    uint64_t hsec_in_stk[sync_heap_size];
    uint64_t mlstate_in_stk[sync_mlstate_size];
    uint64_t mlparam_in_stk[sync_mlparam_size];

    memcpy(hsec_in_stk, hsec_buff, sync_heap_size*WORD_SIZE);
    memcpy(mlstate_in_stk, mlstate_buff, sync_mlstate_size*WORD_SIZE);
    memcpy(mlparam_in_stk, mlparam_buff, sync_mlparam_size*WORD_SIZE);
    free(unsealed_sync_buffer);

    // Overwrite heap metadata
    memcpy(malloc_mparams_ptr, mlparam_in_stk, mparam_size);
    memcpy(malloc_gm_ptr, mlstate_in_stk, mstate_size);
    *(hu_ptr) = sync_heap_size*WORD_SIZE;

    // Copy back heap to heap
    memcpy((void *)GET_MS_LEAST_ADDR(malloc_gm_ptr), hsec_in_stk, sync_heap_size*WORD_SIZE);
}

int fork()
{
    start_fork();
    sync_the_heap();
    if (is_origin)
        return 0;
    else
        return 9999;
}

void sub_function1(int n, void *b_addr) 
{
    // bool is_base_stack = base_stack_pointer==NULL;
    // if (is_base_stack)
    //     base_stack_pointer = (uint64_t*)sp;

    printf("Base stack : %p \n", base_stack_pointer);
    void *ret_addr = __builtin_return_address(0);
    char *my_str = (char*)malloc(100);
    int k = 999; 
    char my_string2[50];
    char my_string[500];
    char random[345];
    strncpy(my_string2, "Something is missing here 2\n", 30);
    strncpy(my_str, "Something is missing here 1\n", 30);

    int pid = fork();

    printf("My pid is: %d \n", pid);
    printf("Arguments addr : %p - %p \n", &n, &b_addr);
    printf("Arguments value : n - %p \n", n, b_addr);
    printf("In stack pointer my_string: %p \n", my_str);
    printf("In stack pointer my_string2: %p \n", my_string2);

    if (sgx_is_within_enclave(my_str, 1))
        printf(" my_string: %s \n", my_str);
    else
        printf(" my_string: %s \n", my_str);

    if (sgx_is_within_enclave(my_string2, 1))
        printf(" my_string2: %s \n", my_string2);
    else
        printf(" my_string2: %s \n", 0x7fffb850d910);

    printf("K symbol address is %p \n", &k);
    printf("K value is %d \n", k);
    // printf("In stack pointer k: %p \n", &k); 
    printf("Function pointer of: printf: %p - sub_func1: %p - sub-func2: %p \n", &printf, &sub_function1, &sub_function1);
    register size_t sp asm ("sp");
    printf("New stack sp: 0x%llx \n", sp);
    printf("New stack return point: %p \n", __builtin_return_address(0));
    printf("The magic number is: %llu \n", fork_magic);
}


void start_fork()
{
    register size_t sp asm ("sp");
    bool is_base_stack = base_stack_pointer==NULL;
    if (is_base_stack)
        base_stack_pointer = (uint64_t*)sp;

    // printf("My addr: %p \n", my_address);
    // printf("The enclave start addr I archieve is: ==0x%llx \n", enc_start_addr);
    // printf("The .data start addr I archieve is: ==0x%llx \n", sec_data_addr);
    // printf("The .data size addr I archieve is: ==0x%x \n", sec_data_size);
    // printf("The .bss start addr I archieve is: ==0x%llx \n", bss_sec_addr);
    // printf("The .bss size addr I archieve is: ==0x%x \n", bss_sec_size);      
    
    uint64_t* data_sec_start_addr = (uint64_t*)(enc_start_addr+sec_data_addr);
    uint64_t* data_sec_end_addr = (uint64_t*)(enc_start_addr+sec_data_addr+sec_data_size);
    uint64_t* bss_sec_start_addr = (uint64_t*)(enc_start_addr+bss_sec_addr);
    uint64_t* bss_sec_end_addr = (uint64_t*)(enc_start_addr+bss_sec_addr+bss_sec_size);
    void *ret_addr = __builtin_return_address(0);
    parent_ret_p = (uint64_t*)ret_addr;
    uint64_t *frame_addr = (uint64_t*)__builtin_frame_address(0); 
    last_fp = frame_addr;   
    uint64_t* stack_highest_addr = (uint64_t*)base_stack_pointer;

    int dsec_size = (data_sec_end_addr-data_sec_start_addr);
    int bsec_size = (bss_sec_end_addr-bss_sec_start_addr);
    int stack_size = (stack_highest_addr-frame_addr);
    int heap_size = (*hu_ptr)/WORD_SIZE;
    int mlstate_size = mstate_size/WORD_SIZE;
    int mlparam_size = mparam_size/WORD_SIZE;
    int total_size = dsec_size+bsec_size+stack_size+heap_size + mlstate_size + mlparam_size + 7;

    // printf("\n start_fork Stack size is: %d - Total size: %d \n", stack_size, total_size);

    uint64_t data_sec[dsec_size];
    uint64_t sec_buff[total_size];
    uint64_t magic;

    if (sgx_read_rand((unsigned char*)&fork_magic, sizeof(uint64_t))!=SGX_SUCCESS)
    {
        printf("Cannot random nonce \n");
        abort();
    }

    sec_buff[0] = enc_start_addr;
    sec_buff[1] = dsec_size;
    sec_buff[2] = bsec_size;
    sec_buff[3] = stack_size;
    sec_buff[4] = heap_size;
    sec_buff[5] = mlstate_size;
    sec_buff[6] = mlparam_size;
    uint64_t* dsec_buff = sec_buff+7;
    uint64_t* bsec_buff = sec_buff+7+dsec_size;
    uint64_t* ssec_buff = sec_buff+7+dsec_size+bsec_size;
    uint64_t* hsec_buff = sec_buff+7+dsec_size+bsec_size+stack_size;
    uint64_t* mlstate_buff = sec_buff+7+dsec_size+bsec_size+stack_size+heap_size;
    uint64_t* mlparam_buff = sec_buff+7+dsec_size+bsec_size+stack_size+heap_size+mlstate_size;

    memcpy(dsec_buff, data_sec_start_addr, dsec_size*WORD_SIZE);
    memcpy(bsec_buff, bss_sec_start_addr, bsec_size*WORD_SIZE);
    memcpy(ssec_buff, frame_addr, stack_size*WORD_SIZE);
    memcpy(hsec_buff, (void *)GET_MS_LEAST_ADDR(malloc_gm_ptr), heap_size*WORD_SIZE);
    memcpy(mlstate_buff, malloc_gm_ptr, mlstate_size*WORD_SIZE);
    memcpy(mlparam_buff, malloc_mparams_ptr, mlparam_size*WORD_SIZE);

    memcpy(frame_addr, ssec_buff, stack_size*WORD_SIZE);

    // Sampling all the stacks and heap. Now can create the memory region for seal data
    size_t seal_len = sgx_calc_sealed_data_size(0, total_size*WORD_SIZE);

    uint8_t seal_buf[seal_len];

    if (sgx_seal_data(0, NULL, total_size*WORD_SIZE, (const uint8_t*)sec_buff, seal_len, (sgx_sealed_data_t *)seal_buf))
    {
        printf("seal data error \n");
        abort();
    }

    uint8_t unseal_buf[total_size*WORD_SIZE*4];
    uint32_t plain_size;

    int fork_return;
    int code = ocall_fork(&fork_return, seal_buf, seal_len);
    is_origin = true;

}

int ecall_simple_ctx_swich(int n)
{
    // get_thread_data();
    // for (int i=0; i<n; i++)
    // {
    //     // int m = i+1;
    //     int ret;
    //     ocall_context_switch(&ret, i, i+1);
    //     // int m = i + i + 1;
    // }    
    int stk;
    printf("New enclave: .data %p ---- %p \n  .bss: %p \n .text: %p \n", &pivot, &buffer, bss, &ecall_simple_ctx_swich);
    return 1;    
}

bool check_stack_integrity(void *buffer, int size)
{
    return true;
}

int compute_stack_gap(void* sta, int stack_size)
{
    uint64_t *frame_addr = (uint64_t*)__builtin_frame_address(0); 
    return last_fp - frame_addr;
}

void inner_overwrite_stack(void* sta, int stack_size)    
{
    uint64_t *frame_addr = (uint64_t*)__builtin_frame_address(0); 
    int offset = last_fp - frame_addr;

    if (offset!=0)  {
        printf("two stacks don't have the same size \n");
        abort();
    }

    memcpy(last_fp, sta, stack_size*WORD_SIZE);
    void *ret_addr = __builtin_return_address(0);
    if (ret_addr!=parent_ret_p) {
        printf("overwritten stack error\n");
        abort();
    }
}

void* unseal_stack_data(void *seal_buff, int size, uint32_t *unseal_buff_size)
{
    uint8_t *unseal_buff = (uint8_t *)malloc(2*size);
    *unseal_buff_size = 2*size;

    int error_code = sgx_unseal_data((const sgx_sealed_data_t *)seal_buff, NULL, NULL, unseal_buff, unseal_buff_size);
    if (error_code!=SGX_SUCCESS)
    {
        printf("Cannot unseal data, error is: %x \n", error_code);
        abort();
    } 

    return unseal_buff;
}

void ecall_sync_stack(void *seal_buff, int seal_buff_size)
{
    register size_t sp asm ("sp");
    bool is_base_stack = base_stack_pointer==NULL;
    if (is_base_stack)
        base_stack_pointer = (uint64_t*)sp;

    printf("The base stack is: %p \n", base_stack_pointer);
    uint32_t buffer_size;

    void* buffer = unseal_stack_data(seal_buff, seal_buff_size, &buffer_size);

    // Since we cannot sync the heap for now, save it for later
    unsealed_sync_buffer = buffer;

    uint64_t* sec_buff = (uint64_t*)buffer;
    uint64_t sync_enc_start_addr = sec_buff[0];
    uint64_t sync_dsec_size = sec_buff[1];
    uint64_t sync_bsec_size = sec_buff[2];
    uint64_t sync_stack_size = sec_buff[3];

    printf("sync_stack_size: %d \n", sync_stack_size);

    printf("ecall_sync_stack with buf size: %d  -- size is: %d \n", (sync_dsec_size+sync_bsec_size+sync_stack_size+4)*WORD_SIZE, buffer_size);

    // if ((sync_dsec_size+sync_bsec_size+sync_stack_size)*4)

    printf("The enclave start addr I archieve is: ==0x%llx \n", enc_start_addr);
    printf("The .data start addr I archieve is: ==0x%llx \n", sec_data_addr);
    printf("The .data size addr I archieve is: ==0x%x \n", sec_data_size);
    printf("The .bss start addr I archieve is: ==0x%llx \n", bss_sec_addr);
    printf("The .bss size addr I archieve is: ==0x%x \n", bss_sec_size); 

    // Save the value to function stack. Since we are gonna sync the whole
    // .data and .bss section whichc contains these value
    // Dont need this after we sync the base address
    // uint64_t dup_enc_start_addr = enc_start_addr;
    // uint64_t dup_sec_data_addr = sec_data_addr; 
    // uint64_t dup_sec_data_size = sec_data_size; 
    // uint64_t dup_bss_sec_addr = bss_sec_addr; 
    // uint64_t dup_bss_sec_size = bss_sec_size;  

    uint64_t offset = enc_start_addr - sync_enc_start_addr;

    if (!check_stack_integrity(buffer, buffer_size) || offset!=0)   {
        abort();
    }

    uint64_t* data_sec_start_addr = (uint64_t*)(enc_start_addr+sec_data_addr);
    uint64_t* data_sec_end_addr = (uint64_t*)(enc_start_addr+sec_data_addr+sec_data_size);

    uint64_t* bss_sec_start_addr = (uint64_t*)(enc_start_addr+bss_sec_addr);
    uint64_t* bss_sec_end_addr = (uint64_t*)(enc_start_addr+bss_sec_addr+bss_sec_size);

    int dsec_size = (data_sec_end_addr-data_sec_start_addr);
    int bsec_size = (bss_sec_end_addr-bss_sec_start_addr);
    
    if (sync_dsec_size!=dsec_size || sync_bsec_size!=bsec_size) 
    {
        printf("Size is not matched \n");
        abort();
    }

    uint64_t* dsec_buff = sec_buff+7;
    uint64_t* bsec_buff = sec_buff+7+dsec_size;
    uint64_t* ssec_buff = sec_buff+7+dsec_size+bsec_size;

    printf("Before memcpy: bss: %s - pivot: %d - global counter: %d - end pivot: %s - my addr: %p \n", bss, pivot, global_counter, end_pivot, my_address);

    memcpy(data_sec_start_addr, dsec_buff, dsec_size);

    printf("The bsec_size is: %d \n", bsec_size);

    printf("The offset is: %u \n", offset);

    printf("Do the check \n");
    int p_count = 0;
    for (int i=0; i<bsec_size; i++) {
        if(bss_sec_start_addr[i]!=bsec_buff[i]) {
            uint64_t diff = bss_sec_start_addr[i]-bsec_buff[i];

            // If the bss addr is not zero, it is definitely system variable use by the sdk.
            if (bss_sec_start_addr[i]==0)   {
                bss_sec_start_addr[i] = bsec_buff[i];
            } else {
                printf("%p  --  %p \n", bss_sec_start_addr+i, hu_ptr);
                printf("%d : 0x%llx-0x%llx : %u \n", i, bsec_buff[i], bss_sec_start_addr[i], diff);
            }
        }
    }

    printf("After memcpy: bss: %s - pivot: %d - global counter: %d - end pivot: %s - my addr: %p \n", bss, pivot, global_counter, end_pivot, my_address);

    // memcpy(malloc_mparams_ptr, mlparam_buff, mparam_size);
    // memcpy(malloc_gm_ptr, mlstate_buff, mstate_size);
    // *(hu_ptr) = sync_heap_size*WORD_SIZE;

    // Copy back heap to heap
    // memcpy((void *)GET_MS_LEAST_ADDR(malloc_gm_ptr), hsec_buff, sync_heap_size*WORD_SIZE);

    printf("Patch count: %d \n", p_count);
    printf("My addr access: %s \n", my_address);
    printf("The stack size is: %d \n", sync_stack_size);
    void *to_sync_stack = malloc(sync_stack_size*WORD_SIZE);
    memcpy(to_sync_stack, ssec_buff, sync_stack_size*WORD_SIZE);

    // We should fill the stack so that the parent and child stack with the same size
    int stack_gap = compute_stack_gap(to_sync_stack, sync_stack_size);

    if (stack_gap>0)    {
        printf("Bug child stack is larger than parent stack before sync\n");
        abort();
    }

    char fill_in_stack[abs(stack_gap)*8];
    stack_gap = compute_stack_gap(to_sync_stack, sync_stack_size);

    if (stack_gap!=0)   {
        printf("Bug, the gap should be 0. The real gap is: %d \n", stack_gap);
        abort();
    }

    inner_overwrite_stack(to_sync_stack, sync_stack_size);
}