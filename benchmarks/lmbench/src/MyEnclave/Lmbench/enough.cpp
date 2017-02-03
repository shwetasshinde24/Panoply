#include <sgx_stdio_util.h>
#include <sgx_stdlib_util.h>

extern	int	get_enough(int);

int
enough_main()
{
	putenv("LOOP_O=0.0");
	putenv("TIMING_O=0.0");
	printf("%u\n", get_enough(0));
	return (0);
}
