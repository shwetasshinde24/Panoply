#ifndef VRFCERT_U_H__
#define VRFCERT_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "sgx_eid.h"
#include "time.h"
#include "sgx_eid.h"
#include "datatypes.h"
#include "dh_session_protocol.h"
#include "stdarg.h"
#include "sgx/sys/types.h"
#include "struct/sgx_stdio_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

time_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_time, (time_t* t));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_gettimeofday, (void* tv, int tv_size, void* tz, int tz_size));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_gettimeofday2, (void* tv, int tv_size));
clock_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_clock, ());
struct tm* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_gmtime_r, (const time_t* timer, struct tm* tp));
struct tm* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_localtime_r, (const time_t* timer, struct tm* tp));
time_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mktime, (struct tm* tp));
uint32_t SGX_UBRIDGE(SGX_NOCONVENTION, session_request_ocall, (sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id, sgx_dh_msg1_t* dh_msg1, uint32_t* session_id));
uint32_t SGX_UBRIDGE(SGX_NOCONVENTION, exchange_report_ocall, (sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id, sgx_dh_msg2_t* dh_msg2, sgx_dh_msg3_t* dh_msg3, uint32_t session_id));
uint32_t SGX_UBRIDGE(SGX_NOCONVENTION, send_request_ocall, (sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id, secure_message_t* req_message, size_t req_message_size, size_t max_payload_size, secure_message_t* resp_message, size_t resp_message_size));
uint32_t SGX_UBRIDGE(SGX_NOCONVENTION, end_session_ocall, (sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id));
void SGX_UBRIDGE(SGX_CDECL, sgx_oc_cpuidex, (int cpuinfo[4], int leaf, int subleaf));
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_wait_untrusted_event_ocall, (const void* self));
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_set_untrusted_event_ocall, (const void* waiter));
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_setwait_untrusted_events_ocall, (const void* waiter, const void* self));
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_set_multiple_untrusted_events_ocall, (const void** waiters, size_t total));
SGX_WRAPPER_FILE SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fopen, (const char* filename, const char* mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fclose, (SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fputs, (const char* str, SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_feof, (SGX_WRAPPER_FILE FILESTREAM));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_rewind, (SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fflush, (SGX_WRAPPER_FILE FILESTREAM));
size_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fread, (void* ptr, size_t size, size_t nmemb, SGX_WRAPPER_FILE FILESTREAM));
size_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fwrite, (const void* ptr, size_t size, size_t count, SGX_WRAPPER_FILE FILESTREAM));
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fgets, (char* str, int num, SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getc_unlocked, (SGX_WRAPPER_FILE FILESTREAM));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_flockfile, (SGX_WRAPPER_FILE filehandle));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_funlockfile, (SGX_WRAPPER_FILE filehandle));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_ftello, (SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fseeko, (SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_ftell, (SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fseek, (SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_ferror, (SGX_WRAPPER_FILE FILESTREAM));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_perror, (const char* s));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getc, (SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_putchar, (int c));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_putc, (int c, SGX_WRAPPER_FILE stream));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fputc, (int c, SGX_WRAPPER_FILE stream));
SGX_WRAPPER_FILE SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fdopen, (int fd, const char* modes));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fileno, (SGX_WRAPPER_FILE stream));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_string, (const char* s));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fprint_string, (SGX_WRAPPER_FILE stream, const char* s));

sgx_status_t vrfcert_test_create_session(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id);
sgx_status_t vrfcert_test_enclave_to_enclave_call(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id);
sgx_status_t vrfcert_test_message_exchange(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id);
sgx_status_t vrfcert_test_close_session(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id);
sgx_status_t vrfcert_session_request(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_dh_msg1_t* dh_msg1, uint32_t* session_id);
sgx_status_t vrfcert_exchange_report(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_dh_msg2_t* dh_msg2, sgx_dh_msg3_t* dh_msg3, uint32_t session_id);
sgx_status_t vrfcert_generate_response(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, secure_message_t* req_message, size_t req_message_size, size_t max_payload_size, secure_message_t* resp_message, size_t resp_message_size);
sgx_status_t vrfcert_end_session(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
