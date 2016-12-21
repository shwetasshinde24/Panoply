#ifndef UNISTD_T_H__
#define UNISTD_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL wrapper_gethostname(int* retval, char* name, size_t len);
sgx_status_t SGX_CDECL wrapper_sethostname(int* retval, const char* name, size_t len);
sgx_status_t SGX_CDECL wrapper_eventfd(int* retval, unsigned int initval, int flags);
sgx_status_t SGX_CDECL wrapper_recv(int* retval, int fd, void* buf, size_t len, int flags);
sgx_status_t SGX_CDECL wrapper_send(int* retval, int fd, const void* buf, size_t len, int flags);
sgx_status_t SGX_CDECL wrapper_read(long int* retval, int fd, void* buf, size_t count);
sgx_status_t SGX_CDECL wrapper_write(long int* retval, int fd, const void* buf, size_t count);
sgx_status_t SGX_CDECL wrapper_shutdown(int* retval, int fd, int how);
sgx_status_t SGX_CDECL wrapper_close(int* retval, int fd);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
