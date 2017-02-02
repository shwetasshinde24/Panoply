#include <getopt.h>
#include "TdsEnclave_u.h"

int wrapper_getopt(int argc, char** argv, const char *optstring)
{	
	char* const* argv_cast = (char* const*) argv;
	return getopt(argc, argv_cast, optstring);
}

void set_optind(int oi)
{
	optind = oi;
}

void set_opterr(int oe)
{
	opterr = oe;
}

void set_optopt(int oo)
{
	optopt = oo;
}

void set_optreset(int ors)
{
#ifdef HAVE_GETOPT_OPTRESET
	optreset = ors;
#endif
}

char* get_optarg()
{
	return strdup(optarg);
}