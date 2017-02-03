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
#include <sgx_pthread_util.h>
#include <sgx_ocall_util.h>

#include <sgx_thread.h>
#include <sgx_stdio_util.h>
#include <sgx_trts.h>

#include <map>
#include <sgx_eid.h>

static inline unsigned long int get_an_random_id()
{
    unsigned long int rand_number = 0;
    sgx_read_rand((unsigned char*)(&rand_number), sizeof(rand_number));
    return rand_number;
}

sgx_thread_mutex_t job_map_mutex = SGX_THREAD_MUTEX_INITIALIZER;
sgx_thread_mutex_t pthreadid_map_mutex = SGX_THREAD_MUTEX_INITIALIZER;
std::map<unsigned long int, pthread_job_t> id_to_job_info_map;
std::map<sgx_thread_t, pthread_t> sgx_thread_id_to_pthread_id_info_map;
extern sgx_enclave_id_t enclave_self_id;
extern bool initiated_self_id;

unsigned long int put_job(pthread_job_t new_job)
{
    unsigned long int new_id = get_an_random_id();
    sgx_thread_mutex_lock(&job_map_mutex);
    while(id_to_job_info_map.count((new_id))>0)   
    {
        new_id = get_an_random_id();
    }
    id_to_job_info_map.insert(std::pair<unsigned long int, pthread_job_t>(new_id, new_job));
    sgx_thread_mutex_unlock(&job_map_mutex);
    return new_id;
}

bool get_job(unsigned long int job_id, pthread_job_t *pt_job)
{
    //Retreive the job information for the corresponding job id
    // printf("Some one call get_job %d \n", job_id);
    std::map<unsigned long int, pthread_job_t>::iterator it = id_to_job_info_map.find(job_id);
    if(it != id_to_job_info_map.end())
    {
        pthread_job_t *tmp = &it->second;
        *pt_job = *tmp;
        id_to_job_info_map.erase(job_id);
        return true;
    }
    else
    {
        return false;
    }    
}

bool get_pthreadid_from_sgxtheadid(sgx_thread_t sgx_id, pthread_t *pt)
{
    std::map<sgx_thread_t, pthread_t>::iterator it = sgx_thread_id_to_pthread_id_info_map.find(sgx_id);
    if(it != sgx_thread_id_to_pthread_id_info_map.end())
    {
        pthread_t *tmp = &it->second;
        *pt = *tmp;
        return true;
    }
    else
    {
        return false;
    }     
}

void ecall_execute_job(pthread_t pthread_id, unsigned long int job_id)
{
    // printf("ecall_execute_job \n");
    pthread_job_t execute_job = { NULL, NULL };
    sgx_thread_t sgx_id = sgx_thread_self();

    sgx_thread_mutex_lock(&pthreadid_map_mutex);
    sgx_thread_id_to_pthread_id_info_map.insert(std::pair<sgx_thread_t, pthread_t>(sgx_id, pthread_id));
    sgx_thread_mutex_unlock(&pthreadid_map_mutex);

    if (get_job(job_id, &execute_job))
        if (execute_job.start_routine!=NULL)    {
            // printf("Execute start_routine %p by the pthread_id: %d \n", execute_job.start_routine, (unsigned long) pthread_id);
            execute_job.start_routine(execute_job.arg);
        }
}


int sgx_wrapper_pthread_create(pthread_t *newthread,
               SGX_WRAPPER_PTHREAD_ATTRIBUTE attr,
               void *(*start_routine) (void *),
               void *arg)   
{
    // printf("sgx_wrapper_pthread_create \n");
    if (!initiated_self_id)
    {
        /* dangerous situation when enclave id is not initiated before using pthread wrapper  */
        /* need to halt the programme since we cannot make an ecall without eid */
        fprintf(stderr, "The enclave self_id is not set. ");
        abort();
        return -1;
    }

    pthread_job_t new_job = {start_routine, arg};
    unsigned long int job_id = put_job(new_job);
    int retval; 
    sgx_status_t status = ocall_pthread_create(&retval, newthread, attr, job_id, enclave_self_id);
    // printf("done sgx_wrapper_pthread_create \n");
	CHECK_STATUS(status);
    return retval;
}

pthread_t sgx_wrapper_pthread_self(void)
{
    pthread_t retval;
    sgx_status_t status = ocall_pthread_self(&retval);
	CHECK_STATUS(status);
    return retval;
}

int sgx_wrapper_pthread_join(pthread_t pt, void **thread_result)
{
    int retval;
    sgx_status_t status = ocall_pthread_join(&retval, pt, thread_result);
	CHECK_STATUS(status);
    return retval;
}

int sgx_wrapper_pthread_detach(pthread_t pt)
{
    int retval;
    sgx_status_t status = ocall_pthread_detach(&retval, pt);
	CHECK_STATUS(status);
    return retval;
}

int sgx_wrapper_pthread_equal(pthread_t pt1, pthread_t pt2)
{
    int retval;
    sgx_status_t status = ocall_pthread_equal(&retval, pt1, pt2);
	CHECK_STATUS(status);
    return retval;
}

void sgx_wrapper_pthread_exit(void *retval)
{
    sgx_status_t status = ocall_pthread_exit(retval);
}

int sgx_wrapper_pthread_cancel (pthread_t th)
{
    int retval;
    sgx_status_t status = ocall_pthread_cancel(&retval, th);
	CHECK_STATUS(status);
    return retval;
}

void sgx_wrapper_pthread_testcancel (void)
{
    sgx_status_t status = ocall_pthread_testcancel();
}

int sgx_wrapper_pthread_attr_init(SGX_WRAPPER_PTHREAD_ATTRIBUTE *__attr)
{
    int retval;
    sgx_status_t status = ocall_pthread_attr_init(&retval, __attr);
	CHECK_STATUS(status);
    return retval;
}

int sgx_wrapper_pthread_attr_destroy(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr)
{
    int retval;
    sgx_status_t status = ocall_pthread_attr_destroy(&retval, __attr);
	CHECK_STATUS(status);
    return retval;
}

int sgx_wrapper_pthread_attr_getdetachstate(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int *__detachstate)
{
    int retval;
    sgx_status_t status = ocall_pthread_attr_getdetachstate(&retval, __attr, __detachstate);
	CHECK_STATUS(status);
    return retval;
}

int sgx_wrapper_pthread_attr_setdetachstate(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int __detachstate)
{
    int retval;
    sgx_status_t status = ocall_pthread_attr_setdetachstate(&retval, __attr, __detachstate);
	CHECK_STATUS(status);
    return retval;
}

int sgx_wrapper_pthread_attr_getguardsize(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t *__guardsize)
{
    int retval;
    sgx_status_t status = ocall_pthread_attr_getguardsize(&retval, __attr, __guardsize);
	CHECK_STATUS(status);
    return retval;
}

int sgx_wrapper_pthread_attr_setguardsize(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t __guardsize)
{
    int retval;
    sgx_status_t status = ocall_pthread_attr_setguardsize(&retval, __attr, __guardsize);
	CHECK_STATUS(status);
    return retval;
}

int sgx_wrapper_pthread_attr_getschedpolicy(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int *__policy)
{
    int retval;
    sgx_status_t status = ocall_pthread_attr_getschedpolicy(&retval, __attr, __policy);
	CHECK_STATUS(status);
    return retval;
}

int sgx_wrapper_pthread_attr_setschedpolicy(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, int __policy)
{
    int retval;
    sgx_status_t status = ocall_pthread_attr_setschedpolicy(&retval, __attr, __policy);
	CHECK_STATUS(status);
    return retval;
}

int sgx_wrapper_pthread_attr_getstacksize(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t *__stacksize)
{
    int retval;
    sgx_status_t status = ocall_pthread_attr_getstacksize(&retval, __attr, __stacksize);
	CHECK_STATUS(status);
    return retval;
}

int sgx_wrapper_pthread_attr_setstacksize(SGX_WRAPPER_PTHREAD_ATTRIBUTE __attr, size_t __stacksize)
{
    int retval;
    sgx_status_t status = ocall_pthread_attr_setstacksize(&retval, __attr, __stacksize);
	CHECK_STATUS(status);
    return retval;
}


int sgx_wrapper_pthread_setspecific(pthread_key_t key, const void *value)
{
    int retval;
    sgx_status_t status = ocall_pthread_setspecific(&retval, key, value);
	CHECK_STATUS(status);
    return retval;
}

void *sgx_wrapper_pthread_getspecific(pthread_key_t key)
{
    void *retval;
    sgx_status_t status = ocall_pthread_getspecific(&retval, key);
	CHECK_STATUS(status);
    return retval;
    // sgx_status_t status = ocall_pthread_getspecific(key);
}

int sgx_wrapper_pthread_key_create(pthread_key_t *key, void (*destructor)(void*))
{
    int retval;
    sgx_status_t status = ocall_pthread_key_create(&retval, key, destructor);
	CHECK_STATUS(status);
    return retval;
}