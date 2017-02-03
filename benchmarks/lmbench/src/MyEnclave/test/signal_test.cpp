
#include <sgx_stdio_util.h>
#include <sgx_stdlib_util.h>
#include <sgx_unistd_util.h>
#include <sgx_signal_util.h>
#include <sgx_fork_util.h>


void parent_trap(int sig) {fprintf(stderr, "They got back together!\n");}
void child_trap(int sig) {fprintf(stderr, "Caught signal in CHILD.\n");}

int signal_test_main(int argc, char **argv) {
    if (!fork()) {
        signal(SIGINT, &child_trap);
        // raise(SIGTERM);
        sleep(1000);
        exit(0);
    }
    signal(SIGINT, &parent_trap);
    // raise(uSIGTERM);
    sleep(1000);

	int pid = fork();
	if (pid==0)	{
		fork();
	}
}