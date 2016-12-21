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
#include "proxy/Pthread_t.h"

#include <sgx_thread.h>
#include <sgx_stdio_util.h>
#include <sgx_trts.h>

#include <map>
#include <struct/sgx_pthread_struct.h>
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