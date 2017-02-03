#include "vrfcert_u.h"
#include <errno.h>

typedef struct ms_test_create_session_t {
	uint32_t ms_retval;
	sgx_enclave_id_t ms_src_enclave_id;
	sgx_enclave_id_t ms_dest_enclave_id;
} ms_test_create_session_t;

typedef struct ms_test_enclave_to_enclave_call_t {
	uint32_t ms_retval;
	sgx_enclave_id_t ms_src_enclave_id;
	sgx_enclave_id_t ms_dest_enclave_id;
} ms_test_enclave_to_enclave_call_t;

typedef struct ms_test_message_exchange_t {
	uint32_t ms_retval;
	sgx_enclave_id_t ms_src_enclave_id;
	sgx_enclave_id_t ms_dest_enclave_id;
} ms_test_message_exchange_t;

typedef struct ms_test_close_session_t {
	uint32_t ms_retval;
	sgx_enclave_id_t ms_src_enclave_id;
	sgx_enclave_id_t ms_dest_enclave_id;
} ms_test_close_session_t;

typedef struct ms_session_request_t {
	uint32_t ms_retval;
	sgx_enclave_id_t ms_src_enclave_id;
	sgx_dh_msg1_t* ms_dh_msg1;
	uint32_t* ms_session_id;
} ms_session_request_t;

typedef struct ms_exchange_report_t {
	uint32_t ms_retval;
	sgx_enclave_id_t ms_src_enclave_id;
	sgx_dh_msg2_t* ms_dh_msg2;
	sgx_dh_msg3_t* ms_dh_msg3;
	uint32_t ms_session_id;
} ms_exchange_report_t;

typedef struct ms_generate_response_t {
	uint32_t ms_retval;
	sgx_enclave_id_t ms_src_enclave_id;
	secure_message_t* ms_req_message;
	size_t ms_req_message_size;
	size_t ms_max_payload_size;
	secure_message_t* ms_resp_message;
	size_t ms_resp_message_size;
} ms_generate_response_t;

typedef struct ms_end_session_t {
	uint32_t ms_retval;
	sgx_enclave_id_t ms_src_enclave_id;
} ms_end_session_t;

typedef struct ms_time_t {
	time_t ms_retval;
	time_t* ms_t;
} ms_time_t;

typedef struct ms_session_request_ocall_t {
	uint32_t ms_retval;
	sgx_enclave_id_t ms_src_enclave_id;
	sgx_enclave_id_t ms_dest_enclave_id;
	sgx_dh_msg1_t* ms_dh_msg1;
	uint32_t* ms_session_id;
} ms_session_request_ocall_t;

typedef struct ms_exchange_report_ocall_t {
	uint32_t ms_retval;
	sgx_enclave_id_t ms_src_enclave_id;
	sgx_enclave_id_t ms_dest_enclave_id;
	sgx_dh_msg2_t* ms_dh_msg2;
	sgx_dh_msg3_t* ms_dh_msg3;
	uint32_t ms_session_id;
} ms_exchange_report_ocall_t;

typedef struct ms_send_request_ocall_t {
	uint32_t ms_retval;
	sgx_enclave_id_t ms_src_enclave_id;
	sgx_enclave_id_t ms_dest_enclave_id;
	secure_message_t* ms_req_message;
	size_t ms_req_message_size;
	size_t ms_max_payload_size;
	secure_message_t* ms_resp_message;
	size_t ms_resp_message_size;
} ms_send_request_ocall_t;

typedef struct ms_end_session_ocall_t {
	uint32_t ms_retval;
	sgx_enclave_id_t ms_src_enclave_id;
	sgx_enclave_id_t ms_dest_enclave_id;
} ms_end_session_ocall_t;

typedef struct ms_sgx_oc_cpuidex_t {
	int* ms_cpuinfo;
	int ms_leaf;
	int ms_subleaf;
} ms_sgx_oc_cpuidex_t;

typedef struct ms_sgx_thread_wait_untrusted_event_ocall_t {
	int ms_retval;
	void* ms_self;
} ms_sgx_thread_wait_untrusted_event_ocall_t;

typedef struct ms_sgx_thread_set_untrusted_event_ocall_t {
	int ms_retval;
	void* ms_waiter;
} ms_sgx_thread_set_untrusted_event_ocall_t;

typedef struct ms_sgx_thread_setwait_untrusted_events_ocall_t {
	int ms_retval;
	void* ms_waiter;
	void* ms_self;
} ms_sgx_thread_setwait_untrusted_events_ocall_t;

typedef struct ms_sgx_thread_set_multiple_untrusted_events_ocall_t {
	int ms_retval;
	void** ms_waiters;
	size_t ms_total;
} ms_sgx_thread_set_multiple_untrusted_events_ocall_t;

typedef struct ms_ocall_fopen_t {
	SGX_WRAPPER_FILE ms_retval;
	char* ms_filename;
	char* ms_mode;
} ms_ocall_fopen_t;

typedef struct ms_ocall_fclose_t {
	int ms_retval;
	SGX_WRAPPER_FILE ms_FILESTREAM;
} ms_ocall_fclose_t;

typedef struct ms_ocall_fputs_t {
	int ms_retval;
	char* ms_str;
	SGX_WRAPPER_FILE ms_FILESTREAM;
} ms_ocall_fputs_t;

typedef struct ms_ocall_feof_t {
	int ms_retval;
	SGX_WRAPPER_FILE ms_FILESTREAM;
} ms_ocall_feof_t;

typedef struct ms_ocall_rewind_t {
	SGX_WRAPPER_FILE ms_FILESTREAM;
} ms_ocall_rewind_t;

typedef struct ms_ocall_fflush_t {
	int ms_retval;
	SGX_WRAPPER_FILE ms_FILESTREAM;
} ms_ocall_fflush_t;

typedef struct ms_ocall_fread_t {
	size_t ms_retval;
	void* ms_ptr;
	size_t ms_size;
	size_t ms_nmemb;
	SGX_WRAPPER_FILE ms_FILESTREAM;
} ms_ocall_fread_t;

typedef struct ms_ocall_fwrite_t {
	size_t ms_retval;
	void* ms_ptr;
	size_t ms_size;
	size_t ms_count;
	SGX_WRAPPER_FILE ms_FILESTREAM;
} ms_ocall_fwrite_t;

typedef struct ms_ocall_vfprintf_t {
	int ms_retval;
	SGX_WRAPPER_FILE ms_FILESTREAM;
	char* ms_format;
	void* ms_val;
} ms_ocall_vfprintf_t;

typedef struct ms_ocall_vprintf_t {
	int ms_retval;
	char* ms_format;
	void* ms_val;
} ms_ocall_vprintf_t;

typedef struct ms_ocall_fgets_t {
	char* ms_retval;
	char* ms_str;
	int ms_num;
	SGX_WRAPPER_FILE ms_FILESTREAM;
} ms_ocall_fgets_t;

typedef struct ms_ocall_getc_unlocked_t {
	int ms_retval;
	SGX_WRAPPER_FILE ms_FILESTREAM;
} ms_ocall_getc_unlocked_t;

typedef struct ms_ocall_flockfile_t {
	SGX_WRAPPER_FILE ms_filehandle;
} ms_ocall_flockfile_t;

typedef struct ms_ocall_funlockfile_t {
	SGX_WRAPPER_FILE ms_filehandle;
} ms_ocall_funlockfile_t;

typedef struct ms_ocall_vsprintf_t {
	int ms_retval;
	char* ms_string;
	char* ms_format;
	void* ms_val;
} ms_ocall_vsprintf_t;

typedef struct ms_ocall_vasprintf_t {
	int ms_retval;
	char** ms_string;
	char* ms_format;
	void* ms_val;
} ms_ocall_vasprintf_t;

typedef struct ms_ocall_ftello_t {
	long int ms_retval;
	SGX_WRAPPER_FILE ms_FILESTREAM;
} ms_ocall_ftello_t;

typedef struct ms_ocall_fseeko_t {
	int ms_retval;
	SGX_WRAPPER_FILE ms_FILESTREAM;
	long int ms_offset;
	int ms_whence;
} ms_ocall_fseeko_t;

typedef struct ms_ocall_ftell_t {
	long int ms_retval;
	SGX_WRAPPER_FILE ms_FILESTREAM;
} ms_ocall_ftell_t;

typedef struct ms_ocall_fseek_t {
	int ms_retval;
	SGX_WRAPPER_FILE ms_FILESTREAM;
	long int ms_offset;
	int ms_whence;
} ms_ocall_fseek_t;

typedef struct ms_ocall_ferror_t {
	int ms_retval;
	SGX_WRAPPER_FILE ms_FILESTREAM;
} ms_ocall_ferror_t;

static sgx_status_t SGX_CDECL vrfcert_time(void* pms)
{
	ms_time_t* ms = SGX_CAST(ms_time_t*, pms);
	ms->ms_retval = time(ms->ms_t);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_session_request_ocall(void* pms)
{
	ms_session_request_ocall_t* ms = SGX_CAST(ms_session_request_ocall_t*, pms);
	ms->ms_retval = session_request_ocall(ms->ms_src_enclave_id, ms->ms_dest_enclave_id, ms->ms_dh_msg1, ms->ms_session_id);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_exchange_report_ocall(void* pms)
{
	ms_exchange_report_ocall_t* ms = SGX_CAST(ms_exchange_report_ocall_t*, pms);
	ms->ms_retval = exchange_report_ocall(ms->ms_src_enclave_id, ms->ms_dest_enclave_id, ms->ms_dh_msg2, ms->ms_dh_msg3, ms->ms_session_id);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_send_request_ocall(void* pms)
{
	ms_send_request_ocall_t* ms = SGX_CAST(ms_send_request_ocall_t*, pms);
	ms->ms_retval = send_request_ocall(ms->ms_src_enclave_id, ms->ms_dest_enclave_id, ms->ms_req_message, ms->ms_req_message_size, ms->ms_max_payload_size, ms->ms_resp_message, ms->ms_resp_message_size);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_end_session_ocall(void* pms)
{
	ms_end_session_ocall_t* ms = SGX_CAST(ms_end_session_ocall_t*, pms);
	ms->ms_retval = end_session_ocall(ms->ms_src_enclave_id, ms->ms_dest_enclave_id);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_sgx_oc_cpuidex(void* pms)
{
	ms_sgx_oc_cpuidex_t* ms = SGX_CAST(ms_sgx_oc_cpuidex_t*, pms);
	sgx_oc_cpuidex(ms->ms_cpuinfo, ms->ms_leaf, ms->ms_subleaf);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_sgx_thread_wait_untrusted_event_ocall(void* pms)
{
	ms_sgx_thread_wait_untrusted_event_ocall_t* ms = SGX_CAST(ms_sgx_thread_wait_untrusted_event_ocall_t*, pms);
	ms->ms_retval = sgx_thread_wait_untrusted_event_ocall((const void*)ms->ms_self);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_sgx_thread_set_untrusted_event_ocall(void* pms)
{
	ms_sgx_thread_set_untrusted_event_ocall_t* ms = SGX_CAST(ms_sgx_thread_set_untrusted_event_ocall_t*, pms);
	ms->ms_retval = sgx_thread_set_untrusted_event_ocall((const void*)ms->ms_waiter);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_sgx_thread_setwait_untrusted_events_ocall(void* pms)
{
	ms_sgx_thread_setwait_untrusted_events_ocall_t* ms = SGX_CAST(ms_sgx_thread_setwait_untrusted_events_ocall_t*, pms);
	ms->ms_retval = sgx_thread_setwait_untrusted_events_ocall((const void*)ms->ms_waiter, (const void*)ms->ms_self);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_sgx_thread_set_multiple_untrusted_events_ocall(void* pms)
{
	ms_sgx_thread_set_multiple_untrusted_events_ocall_t* ms = SGX_CAST(ms_sgx_thread_set_multiple_untrusted_events_ocall_t*, pms);
	ms->ms_retval = sgx_thread_set_multiple_untrusted_events_ocall((const void**)ms->ms_waiters, ms->ms_total);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_fopen(void* pms)
{
	ms_ocall_fopen_t* ms = SGX_CAST(ms_ocall_fopen_t*, pms);
	ms->ms_retval = ocall_fopen((const char*)ms->ms_filename, (const char*)ms->ms_mode);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_fclose(void* pms)
{
	ms_ocall_fclose_t* ms = SGX_CAST(ms_ocall_fclose_t*, pms);
	ms->ms_retval = ocall_fclose(ms->ms_FILESTREAM);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_fputs(void* pms)
{
	ms_ocall_fputs_t* ms = SGX_CAST(ms_ocall_fputs_t*, pms);
	ms->ms_retval = ocall_fputs((const char*)ms->ms_str, ms->ms_FILESTREAM);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_feof(void* pms)
{
	ms_ocall_feof_t* ms = SGX_CAST(ms_ocall_feof_t*, pms);
	ms->ms_retval = ocall_feof(ms->ms_FILESTREAM);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_rewind(void* pms)
{
	ms_ocall_rewind_t* ms = SGX_CAST(ms_ocall_rewind_t*, pms);
	ocall_rewind(ms->ms_FILESTREAM);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_fflush(void* pms)
{
	ms_ocall_fflush_t* ms = SGX_CAST(ms_ocall_fflush_t*, pms);
	ms->ms_retval = ocall_fflush(ms->ms_FILESTREAM);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_fread(void* pms)
{
	ms_ocall_fread_t* ms = SGX_CAST(ms_ocall_fread_t*, pms);
	ms->ms_retval = ocall_fread(ms->ms_ptr, ms->ms_size, ms->ms_nmemb, ms->ms_FILESTREAM);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_fwrite(void* pms)
{
	ms_ocall_fwrite_t* ms = SGX_CAST(ms_ocall_fwrite_t*, pms);
	ms->ms_retval = ocall_fwrite((const void*)ms->ms_ptr, ms->ms_size, ms->ms_count, ms->ms_FILESTREAM);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_vfprintf(void* pms)
{
	ms_ocall_vfprintf_t* ms = SGX_CAST(ms_ocall_vfprintf_t*, pms);
	ms->ms_retval = ocall_vfprintf(ms->ms_FILESTREAM, (const char*)ms->ms_format, ms->ms_val);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_vprintf(void* pms)
{
	ms_ocall_vprintf_t* ms = SGX_CAST(ms_ocall_vprintf_t*, pms);
	ms->ms_retval = ocall_vprintf((const char*)ms->ms_format, ms->ms_val);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_fgets(void* pms)
{
	ms_ocall_fgets_t* ms = SGX_CAST(ms_ocall_fgets_t*, pms);
	ms->ms_retval = ocall_fgets(ms->ms_str, ms->ms_num, ms->ms_FILESTREAM);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_getc_unlocked(void* pms)
{
	ms_ocall_getc_unlocked_t* ms = SGX_CAST(ms_ocall_getc_unlocked_t*, pms);
	ms->ms_retval = ocall_getc_unlocked(ms->ms_FILESTREAM);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_flockfile(void* pms)
{
	ms_ocall_flockfile_t* ms = SGX_CAST(ms_ocall_flockfile_t*, pms);
	ocall_flockfile(ms->ms_filehandle);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_funlockfile(void* pms)
{
	ms_ocall_funlockfile_t* ms = SGX_CAST(ms_ocall_funlockfile_t*, pms);
	ocall_funlockfile(ms->ms_filehandle);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_vsprintf(void* pms)
{
	ms_ocall_vsprintf_t* ms = SGX_CAST(ms_ocall_vsprintf_t*, pms);
	ms->ms_retval = ocall_vsprintf(ms->ms_string, (const char*)ms->ms_format, ms->ms_val);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_vasprintf(void* pms)
{
	ms_ocall_vasprintf_t* ms = SGX_CAST(ms_ocall_vasprintf_t*, pms);
	ms->ms_retval = ocall_vasprintf(ms->ms_string, (const char*)ms->ms_format, ms->ms_val);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_ftello(void* pms)
{
	ms_ocall_ftello_t* ms = SGX_CAST(ms_ocall_ftello_t*, pms);
	ms->ms_retval = ocall_ftello(ms->ms_FILESTREAM);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_fseeko(void* pms)
{
	ms_ocall_fseeko_t* ms = SGX_CAST(ms_ocall_fseeko_t*, pms);
	ms->ms_retval = ocall_fseeko(ms->ms_FILESTREAM, ms->ms_offset, ms->ms_whence);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_ftell(void* pms)
{
	ms_ocall_ftell_t* ms = SGX_CAST(ms_ocall_ftell_t*, pms);
	ms->ms_retval = ocall_ftell(ms->ms_FILESTREAM);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_fseek(void* pms)
{
	ms_ocall_fseek_t* ms = SGX_CAST(ms_ocall_fseek_t*, pms);
	ms->ms_retval = ocall_fseek(ms->ms_FILESTREAM, ms->ms_offset, ms->ms_whence);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL vrfcert_ocall_ferror(void* pms)
{
	ms_ocall_ferror_t* ms = SGX_CAST(ms_ocall_ferror_t*, pms);
	ms->ms_retval = ocall_ferror(ms->ms_FILESTREAM);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[31];
} ocall_table_vrfcert = {
	31,
	{
		(void*)vrfcert_time,
		(void*)vrfcert_session_request_ocall,
		(void*)vrfcert_exchange_report_ocall,
		(void*)vrfcert_send_request_ocall,
		(void*)vrfcert_end_session_ocall,
		(void*)vrfcert_sgx_oc_cpuidex,
		(void*)vrfcert_sgx_thread_wait_untrusted_event_ocall,
		(void*)vrfcert_sgx_thread_set_untrusted_event_ocall,
		(void*)vrfcert_sgx_thread_setwait_untrusted_events_ocall,
		(void*)vrfcert_sgx_thread_set_multiple_untrusted_events_ocall,
		(void*)vrfcert_ocall_fopen,
		(void*)vrfcert_ocall_fclose,
		(void*)vrfcert_ocall_fputs,
		(void*)vrfcert_ocall_feof,
		(void*)vrfcert_ocall_rewind,
		(void*)vrfcert_ocall_fflush,
		(void*)vrfcert_ocall_fread,
		(void*)vrfcert_ocall_fwrite,
		(void*)vrfcert_ocall_vfprintf,
		(void*)vrfcert_ocall_vprintf,
		(void*)vrfcert_ocall_fgets,
		(void*)vrfcert_ocall_getc_unlocked,
		(void*)vrfcert_ocall_flockfile,
		(void*)vrfcert_ocall_funlockfile,
		(void*)vrfcert_ocall_vsprintf,
		(void*)vrfcert_ocall_vasprintf,
		(void*)vrfcert_ocall_ftello,
		(void*)vrfcert_ocall_fseeko,
		(void*)vrfcert_ocall_ftell,
		(void*)vrfcert_ocall_fseek,
		(void*)vrfcert_ocall_ferror,
	}
};
sgx_status_t vrfcert_test_create_session(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id)
{
	sgx_status_t status;
	ms_test_create_session_t ms;
	ms.ms_src_enclave_id = src_enclave_id;
	ms.ms_dest_enclave_id = dest_enclave_id;
	status = sgx_ecall(eid, 0, &ocall_table_vrfcert, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t vrfcert_test_enclave_to_enclave_call(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id)
{
	sgx_status_t status;
	ms_test_enclave_to_enclave_call_t ms;
	ms.ms_src_enclave_id = src_enclave_id;
	ms.ms_dest_enclave_id = dest_enclave_id;
	status = sgx_ecall(eid, 1, &ocall_table_vrfcert, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t vrfcert_test_message_exchange(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id)
{
	sgx_status_t status;
	ms_test_message_exchange_t ms;
	ms.ms_src_enclave_id = src_enclave_id;
	ms.ms_dest_enclave_id = dest_enclave_id;
	status = sgx_ecall(eid, 2, &ocall_table_vrfcert, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t vrfcert_test_close_session(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id)
{
	sgx_status_t status;
	ms_test_close_session_t ms;
	ms.ms_src_enclave_id = src_enclave_id;
	ms.ms_dest_enclave_id = dest_enclave_id;
	status = sgx_ecall(eid, 3, &ocall_table_vrfcert, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t vrfcert_session_request(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_dh_msg1_t* dh_msg1, uint32_t* session_id)
{
	sgx_status_t status;
	ms_session_request_t ms;
	ms.ms_src_enclave_id = src_enclave_id;
	ms.ms_dh_msg1 = dh_msg1;
	ms.ms_session_id = session_id;
	status = sgx_ecall(eid, 4, &ocall_table_vrfcert, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t vrfcert_exchange_report(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, sgx_dh_msg2_t* dh_msg2, sgx_dh_msg3_t* dh_msg3, uint32_t session_id)
{
	sgx_status_t status;
	ms_exchange_report_t ms;
	ms.ms_src_enclave_id = src_enclave_id;
	ms.ms_dh_msg2 = dh_msg2;
	ms.ms_dh_msg3 = dh_msg3;
	ms.ms_session_id = session_id;
	status = sgx_ecall(eid, 5, &ocall_table_vrfcert, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t vrfcert_generate_response(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id, secure_message_t* req_message, size_t req_message_size, size_t max_payload_size, secure_message_t* resp_message, size_t resp_message_size)
{
	sgx_status_t status;
	ms_generate_response_t ms;
	ms.ms_src_enclave_id = src_enclave_id;
	ms.ms_req_message = req_message;
	ms.ms_req_message_size = req_message_size;
	ms.ms_max_payload_size = max_payload_size;
	ms.ms_resp_message = resp_message;
	ms.ms_resp_message_size = resp_message_size;
	status = sgx_ecall(eid, 6, &ocall_table_vrfcert, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t vrfcert_end_session(sgx_enclave_id_t eid, uint32_t* retval, sgx_enclave_id_t src_enclave_id)
{
	sgx_status_t status;
	ms_end_session_t ms;
	ms.ms_src_enclave_id = src_enclave_id;
	status = sgx_ecall(eid, 7, &ocall_table_vrfcert, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

