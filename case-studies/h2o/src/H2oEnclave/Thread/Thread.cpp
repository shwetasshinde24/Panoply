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

#include "../H2oEnclave.h"
#include "H2oEnclave_t.h"
#include "../user_types.h"
#include <sgx_thread.h>
#include <sgx_stdio_util.h>
#include <sgx_pthread_util.h>

static size_t global_counter = 0;
static sgx_thread_mutex_t global_mutex = SGX_THREAD_MUTEX_INITIALIZER;

#define BUFFER_SIZE 50

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

static size_t counter = 0;

/*
 * ecall_increase_counter:
 *   Utilize thread APIs inside the enclave.
 */
size_t ecall_increase_counter(void)
{
    printf("Some one call ecall_increase_counter \n");
    size_t ret = 0;
    for (int i = 0; i < LOOPS_PER_THREAD; i++) {
        sgx_thread_mutex_lock(&global_mutex);
        // print_ocall_thread_id();
        /* mutually exclusive adding */
        size_t tmp = global_counter;
        global_counter = ++tmp;
        if (4*LOOPS_PER_THREAD == global_counter)
            ret = global_counter;
        sgx_thread_mutex_unlock(&global_mutex);
    }
    return ret;
}

void* increase_counter(void* arg)
{
    ecall_increase_counter();
}

void ecall_test_pthread_create_and_join()
{
    pthread_t p1, p2, p3, p4;
    void *ret1, *ret2, *ret3, *ret4;
    // pthread_t *p1, *p2, *p3, *p4;
    pthread_create(&p1, NULL, increase_counter, NULL);
    pthread_create(&p2, NULL, increase_counter, NULL);
    pthread_create(&p3, NULL, increase_counter, NULL);
    pthread_create(&p4, NULL, increase_counter, NULL);

    printf("ecall_test_pthread_create_and_join after create %d %d %d %d \n", p1, p2 ,p3 ,p4);

    pthread_join(p1, &ret1);
    pthread_join(p2, &ret2);
    pthread_join(p3, &ret3);
    pthread_join(p4, &ret4);

    printf("The final result is : %d \n", global_counter);
    // thread adder1(increase_counter);
    // thread adder2(increase_counter);
    // thread adder3(increase_counter);
    // thread adder4(increase_counter);

    // adder1.join();
    // adder2.join();
    // adder3.join();
    // adder4.join();
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
