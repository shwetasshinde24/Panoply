#include <proxy/util_t.h>

sgx_enclave_id_t enclave_self_id;
bool initiated_self_id = false;


void ecall_set_enclave_id(sgx_enclave_id_t eid)
{
    if (!initiated_self_id) {
        enclave_self_id = eid;
        initiated_self_id = true;
    }
}