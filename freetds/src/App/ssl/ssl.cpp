
#include <stdio.h>
#include "../App.h"
#include "TdsEnclave_u.h"
#include <openssl/bio.h>


long ocall_i2d_OCSP_RESPID(void* id, void* d)
{
	printf("Fix me: ocall_i2d_OCSP_RESPID \n");
	return 1;
}

void ocall_OCSP_RESPID_free(void *id)
{
	printf("Fix me: ocall_OCSP_RESPID_free \n");
}

// Return pointer of type OCSP_RESPID8, 
void* ocall_d2i_OCSP_RESPID( unsigned char *data, unsigned char ** sdata_pointer, int idsize )
{
	printf("Fix me: ocall_d2i_OCSP_RESPID \n");
	return NULL;
}

// Return pointer to BIO METHOD function
void * ocall_BIO_s_file_internal(void)
{
	printf("Fix me: ocall_BIO_s_file_internal \n");
	return NULL;
}

void * ocall_BIO_s_file(void)
{
	printf("Fix me: ocall_BIO_s_file \n");
	return NULL;
}

/* The pointer type is OPENSSL_DIR_CTX  */
char * ocall_OPENSSL_DIR_read(void **ctx, const char *directory)
{
	printf("Fix me: ocall_OPENSSL_DIR_read \n");
	return NULL;
}

/* The pointer type is OPENSSL_DIR_CTX returns 1 on success, 0 on error */
int ocall_OPENSSL_DIR_end(void **ctx)
{
	printf("Fix me: ocall_OPENSSL_DIR_end \n");
	return -1;
}

BIO* ocall_BIO_new_file(const char *filename, const char *mode)
{
	printf("Fix me: ocall_BIO_new_file \n");
	return NULL;
}