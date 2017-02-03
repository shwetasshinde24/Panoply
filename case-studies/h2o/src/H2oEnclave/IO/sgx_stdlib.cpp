#include <sgx_stdlib_util.h>
#include <stdlib.h>
#include <sgx_ocall_util.h>


char *sgx_wrapper_getenv(const char *name)
{
	char* retval;
	sgx_status_t status = ocall_getenv(&retval, name);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_putenv(char *string)
{
	int retval;
	sgx_status_t status = ocall_putenv(&retval, string);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_clearenv(void)
{
	int retval;
	sgx_status_t status = ocall_clearenv(&retval);
	CHECK_STATUS(status);
	return retval;
}

void sgx_wrapper_exit(int status)
{
	printf("Dummy exit call \n");
	abort();
} 


int sgx_wrapper_setenv(const char *name, const char *value, int replace)
{
	int retval;
	sgx_status_t status = ocall_setenv(&retval, name, value, replace);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_unsetenv (const char *name)
{
	int retval;
	sgx_status_t status = ocall_unsetenv(&retval, name);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_random()
{
	int ran;
	sgx_status_t status =sgx_read_rand((unsigned char*)&ran, sizeof(int));
	CHECK_STATUS(status);
	return ran;
} 

void sgx_wrapper_srandom (unsigned int seed)
{
	fprintf(stdout, "Dummy srandom call \n");
}


int sgx_wrapper_mkstemp(char *string)
{
	int retval;
	sgx_status_t status = ocall_mkstemp(&retval, string);
	CHECK_STATUS(status);
	return retval;
}

char *sgx_wrapper_mkdtemp(char *temp)
{
	char* retval;
	sgx_status_t status = ocall_mkdtemp(&retval, temp);
	CHECK_STATUS(status);
	return retval;
}
