#include <getopt.h>
#include "TopensslEnclave_u.h"

extern void increase_ocall_count();

int wrapper_getopt(int argc, char** argv, const char *optstring)
{
    increase_ocall_count();
	char* const* argv_cast = (char* const*) argv;
	return getopt(argc, argv_cast, optstring);
}

void set_optind(int oi)
{
    increase_ocall_count();
	optind = oi;
}

void set_opterr(int oe)
{
    increase_ocall_count();
	opterr = oe;
}

void set_optopt(int oo)
{
    increase_ocall_count();
	optopt = oo;
}

void set_optreset(int ors)
{
    increase_ocall_count();
#ifdef HAVE_GETOPT_OPTRESET
	optreset = ors;
#endif
}

char* get_optarg()
{
    increase_ocall_count();
	return strdup(optarg);
}