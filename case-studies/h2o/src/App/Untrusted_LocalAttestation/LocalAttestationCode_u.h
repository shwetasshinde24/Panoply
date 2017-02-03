#ifndef LOCALATTESTATIONCODE_U_H__
#define LOCALATTESTATIONCODE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "sgx_eid.h"
#include "datatypes.h"
#include "dh_session_protocol.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

uint32_t SGX_UBRIDGE(SGX_NOCONVENTION, session_request_ocall, (sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id, sgx_dh_msg1_t* dh_msg1, uint32_t* session_id));
uint32_t SGX_UBRIDGE(SGX_NOCONVENTION, exchange_report_ocall, (sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id, sgx_dh_msg2_t* dh_msg2, sgx_dh_msg3_t* dh_msg3, uint32_t session_id));
uint32_t SGX_UBRIDGE(SGX_NOCONVENTION, send_request_ocall, (sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id, secure_message_t* req_message, size_t req_message_size, size_t max_payload_size, secure_message_t* resp_message, size_t resp_message_size));
uint32_t SGX_UBRIDGE(SGX_NOCONVENTION, end_session_ocall, (sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id));

sgx_status_t LocalAttestationCode_session_request(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_dh_msg1_t* dh_msg1, uint32_t* session_id);
sgx_status_t LocalAttestationCode_exchange_report(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_dh_msg2_t* dh_msg2, sgx_dh_msg3_t* dh_msg3, uint32_t session_id);
sgx_status_t LocalAttestationCode_generate_response(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, secure_message_t* req_message, size_t req_message_size, size_t max_payload_size, secure_message_t* resp_message, size_t resp_message_size);
sgx_status_t LocalAttestationCode_end_session(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
