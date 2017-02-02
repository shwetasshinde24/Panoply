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

#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sgx_eid.h>
#include <stdio.h>
#include "sgx_status.h"
#include "struct/sgx_pthread_struct.h"

#include "TdsEnclave_u.h"

#define MAX_PTHREAD_ATTR_BUFF 65000

pthread_attr_t * att_tables[MAX_PTHREAD_ATTR_BUFF];

static int count = 0;

typedef struct {
    unsigned long int job_id;
    sgx_enclave_id_t eid;
} internal_ecall_arg;

int ocall_pthread_attr_init(SGX_WRAPPER_PTHREAD_ATTRIBUTE *__attr)
{
    att_tables[++count] = (pthread_attr_t *)malloc(sizeof(pthread_attr_t));
    int ret = pthread_attr_init(att_tables[count]);
    *__attr = ret<0 ?  PTHREAD_ATTRIBUTE_NULL : count;
    return ret;
}

pthread_attr_t* getAttribute(SGX_WRAPPER_PTHREAD_ATTRIBUTE attr)   
{
    if (attr<=0)
        return NULL;

    return att_tables[attr];
}

int ocall_pthread_attr_destroy(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr)
{
    int ret = -1;
    pthread_attr_t* attr = getAttribute(__attr);
    att_tables[__attr]=NULL;
    if (attr!=NULL) {
        ret = pthread_attr_destroy(attr);
        free(attr);
    }
    return ret;
}

void *generic_ecall_routine(void* arguments)  
{
    internal_ecall_arg *ecall_arg = (internal_ecall_arg *)arguments;
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = TdsEnclave_ecall_execute_job(ecall_arg->eid, pthread_self(), ecall_arg->job_id);
    free(arguments);
}

int ocall_pthread_create(pthread_t *new_thread, SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, unsigned long int job_id, sgx_enclave_id_t eid)
{
    internal_ecall_arg* arguments = (internal_ecall_arg*)malloc(sizeof(internal_ecall_arg));
    arguments->job_id = job_id;
    arguments->eid = eid;
    pthread_attr_t* attr = getAttribute(__attr);
    return pthread_create(new_thread, attr, generic_ecall_routine, (void *)arguments);
}

pthread_t ocall_pthread_self()
{
    return pthread_self();
}

int ocall_pthread_join(pthread_t pt, void **thread_result)
{
    // printf("Call ocall_pthread_join %d \n", pt);
    return pthread_join(pt, thread_result);
}

int ocall_pthread_detach(pthread_t pt)
{
    return pthread_detach(pt);
}

int ocall_pthread_equal(pthread_t pt1, pthread_t pt2)
{
    return pthread_equal(pt1, pt2);
}

void ocall_pthread_exit(void *retval)
{
    pthread_exit(retval);
}

int ocall_pthread_cancel (pthread_t th)
{
    return pthread_cancel(th);
}

void ocall_pthread_testcancel (void)
{
    pthread_testcancel();
}

int ocall_pthread_attr_getdetachstate(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int *__detachstate)
{
    int ret = -1;
    pthread_attr_t* attr = getAttribute(__attr);
    if (attr!=NULL) {
        int buff;
        ret = pthread_attr_getdetachstate(attr, &buff);
        *__detachstate = buff;
    }
    return ret;    
}

int ocall_pthread_attr_setdetachstate(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int __detachstate)
{
    int ret = -1;
    pthread_attr_t* attr = getAttribute(__attr);
    if (attr!=NULL) {
        ret = pthread_attr_setdetachstate(attr, __detachstate);
    }
    return ret; 
}

int ocall_pthread_attr_getguardsize(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t *__guardsize)
{
    int ret = -1;
    pthread_attr_t* attr = getAttribute(__attr);
    if (attr!=NULL) {
        size_t buff;
        ret = pthread_attr_getguardsize(attr, &buff);
        *__guardsize = buff;
    }
    return ret;     
}

int ocall_pthread_attr_setguardsize(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t __guardsize)
{
    int ret = -1;
    pthread_attr_t* attr = getAttribute(__attr);
    if (attr!=NULL) {
        ret = pthread_attr_setguardsize(attr, __guardsize);
    }
    return ret;     
}

int ocall_pthread_attr_getschedpolicy(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int *__policy)
{
    int ret = -1;
    pthread_attr_t* attr = getAttribute(__attr);
    if (attr!=NULL) {
        int buff;
        ret = pthread_attr_getschedpolicy(attr, &buff);
        *__policy = buff;
    }
    return ret;        
}

int ocall_pthread_attr_setschedpolicy(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int __policy)
{
    int ret = -1;
    pthread_attr_t* attr = getAttribute(__attr);
    if (attr!=NULL) {
        ret = pthread_attr_setschedpolicy(attr, __policy);
    }
    return ret;      
}

int ocall_pthread_attr_getstacksize(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t *__stacksize)
{
    int ret = -1;
    pthread_attr_t* attr = getAttribute(__attr);
    if (attr!=NULL) {
        size_t buff;
        ret = pthread_attr_getstacksize(attr, &buff);
        *__stacksize = buff;
    }
    return ret;       
}

int ocall_pthread_attr_setstacksize(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t __stacksize)
{
    int ret = -1;
    pthread_attr_t* attr = getAttribute(__attr);
    if (attr!=NULL) {
        ret = pthread_attr_setschedpolicy(attr, __stacksize);
    }
    return ret;      
}

int ocall_pthread_setspecific(pthread_key_t key, const void *value)
{
    return pthread_setspecific(key, value);
}

void * ocall_pthread_getspecific(pthread_key_t key)
{
    return pthread_getspecific(key);
}

int ocall_pthread_key_create(pthread_key_t *key, void* destructor)
{
    return 1;
    // return pthread_key_create(key, destructor);
}