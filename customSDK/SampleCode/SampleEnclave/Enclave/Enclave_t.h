#ifndef ENCLAVE_T_H__
#define ENCLAVE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "user_types.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

typedef struct struct_foo_t {
	uint32_t struct_foo_0;
	uint64_t struct_foo_1;
} struct_foo_t;

typedef enum enum_foo_t {
	ENUM_FOO_0 = 0,
	ENUM_FOO_1 = 1,
} enum_foo_t;

typedef union union_foo_t {
	uint32_t union_foo_0;
	uint32_t union_foo_1;
	uint64_t union_foo_3;
} union_foo_t;

size_t get_buffer_len(const char* val);

int ecall_set_parsed_section_info(const char* name, int type, uint64_t val);
void ecall_type_char(char val);
void ecall_type_int(int val);
void ecall_type_float(float val);
void ecall_type_double(double val);
void ecall_type_size_t(size_t val);
void ecall_type_wchar_t(wchar_t val);
void ecall_type_struct(struct struct_foo_t val);
void ecall_type_enum_union(enum enum_foo_t val1, union union_foo_t* val2);
size_t ecall_pointer_user_check(void* val, size_t sz);
void ecall_pointer_in(int* val);
void ecall_pointer_out(int* val);
void ecall_pointer_in_out(int* val);
void ecall_pointer_string(char* str);
void ecall_pointer_string_const(const char* str);
void ecall_pointer_size(void* ptr, size_t len);
void ecall_pointer_count(int* arr, int cnt);
void ecall_pointer_isptr_readonly(buffer_t buf, size_t len);
void ecall_pointer_sizefunc(char* buf);
void ocall_pointer_attr();
void ecall_array_user_check(int arr[4]);
void ecall_array_in(int arr[4]);
void ecall_array_out(int arr[4]);
void ecall_array_in_out(int arr[4]);
void ecall_array_isary(array_t arr);
void ecall_function_calling_convs();
void ecall_function_public();
int ecall_function_private();
void ecall_malloc_free();
void ecall_sgx_cpuid(int cpuinfo[4], int leaf);
void ecall_exception();
void ecall_map();
size_t ecall_increase_counter();
void ecall_producer();
void ecall_consumer();
void ecall_dump_data0(int n, size_t size);
void ecall_dump_data1(int n, size_t size);
void ecall_dump_data2(int n, size_t size);
void ecall_dump_data3(int n, size_t size);
void ecall_dump_data4(int n, size_t size);
void ecall_dump_data5(int n, size_t size);
void ecall_dump_data6(int n, size_t size);
void ecall_dump_data7(int n, size_t size);
void ecall_test_ctx_switch(void* buffer, int n);
int ecall_simple_ctx_swich(int n);

sgx_status_t SGX_CDECL ocall_print_string(const char* str);
sgx_status_t SGX_CDECL ocall_write0(void* buffer, int bufsiz);
sgx_status_t SGX_CDECL ocall_write1(void* buffer, int bufsiz);
sgx_status_t SGX_CDECL ocall_write2(void* buffer, int bufsiz);
sgx_status_t SGX_CDECL ocall_write3(void* buffer, int bufsiz);
sgx_status_t SGX_CDECL ocall_write4(void* buffer, int bufsiz);
sgx_status_t SGX_CDECL ocall_write5(void* buffer, int bufsiz);
sgx_status_t SGX_CDECL ocall_write6(void* buffer, int bufsiz);
sgx_status_t SGX_CDECL ocall_write7(void* buffer, int bufsiz);
sgx_status_t SGX_CDECL ocall_write8(void* buffer, int bufsiz);
sgx_status_t SGX_CDECL ocall_write9(void* buffer, int bufsiz);
sgx_status_t SGX_CDECL ocall_context_switch(int* retval, int dummy1, int dummy2);
sgx_status_t SGX_CDECL ocall_dummy_clone_process(int* retval);
sgx_status_t SGX_CDECL ocall_fork(int* retval, void* buffer, int bufsiz);
sgx_status_t SGX_CDECL ocall_pointer_user_check(int* val);
sgx_status_t SGX_CDECL ocall_pointer_in(int* val);
sgx_status_t SGX_CDECL ocall_pointer_out(int* val);
sgx_status_t SGX_CDECL ocall_pointer_in_out(int* val);
sgx_status_t SGX_CDECL memccpy(void** retval, void* dest, const void* src, int val, size_t len);
sgx_status_t SGX_CDECL ocall_function_allow();
sgx_status_t SGX_CDECL sgx_oc_cpuidex(int cpuinfo[4], int leaf, int subleaf);
sgx_status_t SGX_CDECL sgx_thread_wait_untrusted_event_ocall(int* retval, const void* self);
sgx_status_t SGX_CDECL sgx_thread_set_untrusted_event_ocall(int* retval, const void* waiter);
sgx_status_t SGX_CDECL sgx_thread_setwait_untrusted_events_ocall(int* retval, const void* waiter, const void* self);
sgx_status_t SGX_CDECL sgx_thread_set_multiple_untrusted_events_ocall(int* retval, const void** waiters, size_t total);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
