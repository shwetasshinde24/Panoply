#include <proxy/util_t.h>
#include <sgx_stdio_util.h>
#include <sgx_thread.h>

#include "MyEnclave_t.h"

sgx_enclave_id_t enclave_self_id;
bool initiated_self_id = false;

int ecall_count = 0;
sgx_thread_mutex_t ecall_count_mutex = SGX_THREAD_MUTEX_INITIALIZER;

void ecall_set_enclave_id(sgx_enclave_id_t eid)
{
    if (!initiated_self_id) {
        enclave_self_id = eid;
        initiated_self_id = true;
    }
}

void print_num_of_ecall()
{
	printf("Num of ecall: %d \n", ecall_count);
}

void increase_ecall_count()	{
	sgx_thread_mutex_lock(&ecall_count_mutex);
	ecall_count++;
	sgx_thread_mutex_unlock(&ecall_count_mutex);
}

// void sgx_big_churn_seal(const uint32_t additional_MACtext_length, const uint8_t * p_additional_MACtext, const uint32_t text2encrypt_length, 
// 		const uint8_t * p_text2encrypt, const uint32_t sealed_data_size, sgx_sealed_data_t * p_sealed_data)
// {
	
// }