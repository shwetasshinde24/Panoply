#ifndef SSL_U_H__
#define SSL_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

long int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_i2d_OCSP_RESPID, (void* id, void* d));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_OCSP_RESPID_free, (void* id));
void* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_d2i_OCSP_RESPID, (unsigned char* data, unsigned char** sdata_pointer, int idsize));
void* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_BIO_s_file_internal, ());
void* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_BIO_s_file, ());
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_OPENSSL_DIR_read, (void** ctx, const char* directory));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_OPENSSL_DIR_end, (void** ctx));


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
