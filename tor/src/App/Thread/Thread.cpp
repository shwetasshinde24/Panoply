/**
*   Copyright(C) 2011-2015 Intel Corporation All Rights Reserved.
*
*   The source code, information  and  material ("Material") contained herein is
*   owned  by Intel Corporation or its suppliers or licensors, and title to such
*   Material remains  with Intel Corporation  or its suppliers or licensors. The
*   Material  contains proprietary information  of  Intel or  its  suppliers and
*   licensors. The  Material is protected by worldwide copyright laws and treaty
*   provisions. No  part  of  the  Material  may  be  used,  copied, reproduced,
*   modified, published, uploaded, posted, transmitted, distributed or disclosed
*   in any way  without Intel's  prior  express written  permission. No  license
*   under  any patent, copyright  or  other intellectual property rights  in the
*   Material  is  granted  to  or  conferred  upon  you,  either  expressly,  by
*   implication, inducement,  estoppel or  otherwise.  Any  license  under  such
*   intellectual  property  rights must  be express  and  approved  by  Intel in
*   writing.
*
*   *Third Party trademarks are the property of their respective owners.
*
*   Unless otherwise  agreed  by Intel  in writing, you may not remove  or alter
*   this  notice or  any other notice embedded  in Materials by Intel or Intel's
*   suppliers or licensors in any way.
*/

#include <thread>
#include <stdio.h>
using namespace std;

#include "../App.h"
#include "TorEnclave_u.h"
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

static size_t counter = 0;

void* increase_counter(void *)
{
    size_t cnr = 0;
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    // printf("This is the untrusted thread with thread id is: %u \n", pthread_self());
    ret = TorEnclave_ecall_increase_counter(global_eid, &cnr);
    if (cnr != 0) counter = cnr; 
    if (ret != SGX_SUCCESS)
        abort();
}

void data_producer(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = TorEnclave_ecall_producer(global_eid);
    if (ret != SGX_SUCCESS)
        abort();
}

void data_consumer(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = TorEnclave_ecall_consumer(global_eid);
    if (ret != SGX_SUCCESS)
        abort();
}

void print_ocall_thread_id(void)
{
    printf("This is id of the ocall thread: %u \n", pthread_self());
}

/* ecall_thread_functions:
 *   Invokes thread functions including mutex, condition variable, etc.
 */
void ecall_thread_functions(void)
{
    // pthread_t p1, p2, p3, p4;
    // void *ret1, *ret2, *ret3, *ret4;
    // // pthread_t *p1, *p2, *p3, *p4;
    // pthread_create(&p1, NULL, increase_counter, NULL);
    // pthread_create(&p2, NULL, increase_counter, NULL);
    // pthread_create(&p3, NULL, increase_counter, NULL);
    // pthread_create(&p4, NULL, increase_counter, NULL);

    // pthread_join(p1, &ret1);
    // pthread_join(p2, &ret2);
    // pthread_join(p3, &ret3);
    // pthread_join(p4, &ret4);
    // thread adder1(increase_counter);
    // thread adder2(increase_counter);
    // thread adder3(increase_counter);
    // thread adder4(increase_counter);

    // adder1.join();
    // adder2.join();
    // adder3.join();
    // adder4.join();

    TorEnclave_ecall_set_enclave_id(global_eid, global_eid);
    TorEnclave_ecall_test_pthread_create_and_join(global_eid);

    // assert(counter == 4*LOOPS_PER_THREAD);

    printf("Info: executing thread synchronization, please wait...  \n");
    /* condition variable */
    // thread consumer1(data_consumer);
    // thread producer0(data_producer);
    // thread consumer2(data_consumer);
    // thread consumer3(data_consumer);
    // thread consumer4(data_consumer);
    
    // consumer1.join();
    // consumer2.join();
    // consumer3.join();
    // consumer4.join();
    // producer0.join();
}
