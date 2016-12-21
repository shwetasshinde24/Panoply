#ifndef SSL_T_H__
#define SSL_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_i2d_OCSP_RESPID(long int* retval, void* id, void* d);
sgx_status_t SGX_CDECL ocall_OCSP_RESPID_free(void* id);
sgx_status_t SGX_CDECL ocall_d2i_OCSP_RESPID(void** retval, unsigned char* data, unsigned char** sdata_pointer, int idsize);
sgx_status_t SGX_CDECL ocall_BIO_s_file_internal(void** retval);
sgx_status_t SGX_CDECL ocall_BIO_s_file(void** retval);
sgx_status_t SGX_CDECL ocall_OPENSSL_DIR_read(char** retval, void** ctx, const char* directory);
sgx_status_t SGX_CDECL ocall_OPENSSL_DIR_end(int* retval, void** ctx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
