#include <sgx_unistd_util.h>

volatile int i;

main()
{

	nice(10);
	for (;;) getppid();
	//for (;;) i++;
	exit(i);
}
