/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#ifndef SGX_GETOPT_UTIL_H
#define SGX_GETOPT_UTIL_H

#ifdef __cplusplus
extern "C"	{
#endif

extern int sgx_wrapper_getopt(int argc, char** argv, const char *optstring);
extern char * sgx_wrapper_get_optarg();
extern int sgx_wrapper_get_optind();
extern int sgx_wrapper_get_opterr();
extern int sgx_wrapper_get_optopt();

#ifdef __cplusplus
}
#endif

#define getopt(A, B, C) sgx_wrapper_getopt(A, B, C)
#define optarg() sgx_wrapper_get_optarg()
#define optind() sgx_wrapper_get_optind()
#define opterr() sgx_wrapper_get_opterr()
#define optopt() sgx_wrapper_get_optopt()

#endif