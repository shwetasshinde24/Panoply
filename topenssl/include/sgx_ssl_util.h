#ifndef SGX_SSL_UTIL_H
#define SGX_SSL_UTIL_H 1

#include "proxy/ssl_t.h"

static inline long int wrapper_i2d_OCSP_RESPID(void* id, void* d)
{
	long int retval;
	ocall_i2d_OCSP_RESPID(&retval, id, d);
	return retval;
}

static inline void wrapper_OCSP_RESPID_free(void* id)
{
	ocall_OCSP_RESPID_free(id);
}

static inline void* wrapper_d2i_OCSP_RESPID(unsigned char* data, unsigned char** sdata_pointer, int idsize)
{
	void* retval;
	ocall_d2i_OCSP_RESPID(&retval, data, sdata_pointer, idsize);
	return retval;
}

static inline void* wrapper_BIO_s_file_internal()
{
	void* retval;
	ocall_BIO_s_file_internal(&retval);
	return retval;
}

static inline void* wrapper_BIO_s_file()
{
	void* retval;
	ocall_BIO_s_file(&retval);
	return retval;
}

static inline const char* wrapper_OPENSSL_DIR_read(void** ctx, const char* directory)
{
	char* retval;
	ocall_OPENSSL_DIR_read(&retval, ctx, directory);
	return (const char*)retval;
}

static inline int wrapper_OPENSSL_DIR_end(void** ctx)
{
	int retval;
	ocall_OPENSSL_DIR_end(&retval, ctx);
	return retval;
}

#define i2d_OCSP_RESPID(A, B) wrapper_i2d_OCSP_RESPID((void *)(A), (void *)(B))
#define OCSP_RESPID_free(A) wrapper_OCSP_RESPID_free((void*)(A))
#define d2i_OCSP_RESPID(A,B,C) wrapper_d2i_OCSP_RESPID((A),(B),(C))
#define BIO_s_file_internal() ((BIO_METHOD *) wrapper_BIO_s_file_internal())
#define BIO_s_file() ((BIO_METHOD *) wrapper_BIO_s_file())
#define OPENSSL_DIR_read(A,B) wrapper_OPENSSL_DIR_read((void**)(A),(B))
#define OPENSSL_DIR_end(A) wrapper_OPENSSL_DIR_end((void**)(A))



#endif
