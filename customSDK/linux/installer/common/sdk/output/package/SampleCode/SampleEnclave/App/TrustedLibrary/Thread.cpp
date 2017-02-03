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

#include <thread>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
using namespace std;

#include "../App.h"
#include "Enclave_u.h"

static size_t counter = 0;

void ocall_write0(void* buffer, int bufsiz)
{
    // printf("ocall_write0 \n");
    int dummy = 0;
    dummy++;
}

void ocall_write1(void* buffer, int bufsiz)
{
    int dummy = 0;
    dummy++;
}

void ocall_write2(void* buffer, int bufsiz)
{
    int dummy = 0;
    dummy++;
}

void ocall_write3(void* buffer, int bufsiz)
{
    int dummy = 0;
    dummy++;
}

void ocall_write4(void* buffer, int bufsiz)
{
    int dummy = 0;
    dummy++;
}

void ocall_write5(void* buffer, int bufsiz)
{
    int dummy = 0;
    dummy++;
}

void ocall_write6(void* buffer, int bufsiz)
{
    int dummy = 0;
    dummy++;
}

void ocall_write7(void* buffer, int bufsiz)
{
    int dummy = 0;
    dummy++;
}

void ocall_write8(void* buffer, int bufsiz)
{
    int dummy = 0;
    dummy++;
}

void ocall_write9(void* buffer, int bufsiz)
{
    int dummy = 0;
    dummy++;
}

void increase_counter(void)
{
    size_t cnr = 0;
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = ecall_increase_counter(global_eid, &cnr);
    if (cnr != 0) counter = cnr; 
    if (ret != SGX_SUCCESS)
        abort();
}

void data_producer(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = ecall_producer(global_eid);
    if (ret != SGX_SUCCESS)
        abort();
}

void data_consumer(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = ecall_consumer(global_eid);
    if (ret != SGX_SUCCESS)
        abort();
}

pthread_mutex_t lock;
int count = 0;

void* data_bump(void*)
{
    pthread_mutex_lock(&lock);
    // count++;
    int k = count;
    count++;
    pthread_mutex_unlock(&lock);
    printf("ecall_dump_data: %d \n", k);
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    int loop_num = 5000000;
    int data_size = 1;

    switch(k)   {
        case 0:
            ret = ecall_dump_data0(global_eid, loop_num, data_size);
            break;        
        case 1:
            ret = ecall_dump_data1(global_eid, loop_num, data_size);
            break;        
        case 2:
            ret = ecall_dump_data2(global_eid, loop_num, data_size);
            break;        
        case 3:
            ret = ecall_dump_data3(global_eid, loop_num, data_size);
            break;
        case 4:
            ret = ecall_dump_data4(global_eid, loop_num, data_size);
            break;
        case 5:
            ret = ecall_dump_data5(global_eid, loop_num, data_size);
            break;   
        case 6:
            ret = ecall_dump_data6(global_eid, loop_num, data_size);
            break;   
        case 7:
            ret = ecall_dump_data7(global_eid, loop_num, data_size);
            break;                                                
    }
    
    // printf("ecall_dump_data: %d \n", count-1);
    if (ret != SGX_SUCCESS) {
        printf("Error code: %x \n", ret);
        abort();    
    }
} 

void ecall_test_sgx_limit(void)
{
    pthread_t tid[8];
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    pthread_mutex_init(&lock, NULL);

    for (int i=0; i<8; i++) {
        pthread_create(&(tid[i]), NULL, &data_bump, NULL);

    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);    
    pthread_join(tid[5], NULL);
    pthread_join(tid[6], NULL);
    pthread_join(tid[7], NULL);
    pthread_join(tid[8], NULL);        

    gettimeofday(&tp, NULL);
    long int ms2 = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    printf("Time to complete: %ld \n", ms2-ms);
}

/* ecall_thread_functions:
 *   Invokes thread functions including mutex, condition variable, etc.
 */
void ecall_thread_functions(void)
{
    thread adder1(increase_counter);
    thread adder2(increase_counter);
    thread adder3(increase_counter);
    thread adder4(increase_counter);

    adder1.join();
    adder2.join();
    adder3.join();
    adder4.join();

    assert(counter == 4*LOOPS_PER_THREAD);

    printf("Info: executing thread synchronization, please wait...  \n");
    /* condition variable */
    thread consumer1(data_consumer);
    thread producer0(data_producer);
    thread consumer2(data_consumer);
    thread consumer3(data_consumer);
    thread consumer4(data_consumer);
    
    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();
    producer0.join();
}
