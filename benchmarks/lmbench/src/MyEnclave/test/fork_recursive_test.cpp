
#include <sgx_stdio_util.h>
#include <sgx_stdlib_util.h>
#include <sgx_unistd_util.h>
#include <sgx_signal_util.h>
#include <sgx_fork_util.h>


int fork_test_main(int argc, char **argv) {


    // for (int i=0; i<3; i++) {
    //     int pid = fork();
    //     if (pid==0) {
    //         sleep(10);            
    //     }
        
    // }

	int pid = fork();
	if (pid==0)	{
        // sleep(100);
        printf("Ending %d \n", pid);
        return 0;

	}

    pid = fork();
    if (pid==0) {
        printf("Ending %d \n", pid);
        return 0;

    }

    // pid = fork();
    // if (pid==0) {
    //     sleep(100);
    //     printf("Ending %d \n", pid);
    //     return 0;

    // }

     int t = 6789;
 //    // sleep(10);
    // pid = fork();
    // if (pid==0) {
    //     // sleep(100);
    //     return 0;

    // }

    printf("Ending %d \n", pid);

    int pid2 = fork();
    if (pid2==-1)
    {
        printf("Threr is fork that's failed \n");
    }

	printf("Ending %d \n", t);


    return 0;
}