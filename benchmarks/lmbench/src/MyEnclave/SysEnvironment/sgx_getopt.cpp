/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sgx_getopt_util.h>
#include <sgx_ocall_util.h>

#include <MyEnclave_t.h>

int sgx_wrapper_getopt(int argc, char** argv, const char *optstring)
{
	int retval;
	sgx_status_t status = wrapper_getopt(&retval, argc, argv, optstring);
	CHECK_STATUS(status);
	return retval;
}

char * sgx_wrapper_get_optarg()
{
	char * retval;
	sgx_status_t status = get_optarg(&retval);
	CHECK_STATUS(status);
	// printf("Str len of retval is: %d \n", strlen(retval));
	char *dup = malloc(strlen(retval)+1);
	memcpy(dup, retval, strlen(retval)+1);
	return dup;
}

int sgx_wrapper_get_optind()
{
	int retval;
	sgx_status_t status = ocall_get_optind(&retval);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_get_opterr()
{
	int retval;
	sgx_status_t status = ocall_get_opterr(&retval);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_get_optopt()
{
	int retval;
	sgx_status_t status = ocall_get_optopt(&retval);
	CHECK_STATUS(status);
	return retval;
}