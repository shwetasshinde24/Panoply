#include <sgx_stdio_util.h>
#include <sgx_sysselect_util.h>
#include <sgx_unistd_util.h>

int
select_test_main(void)
{
    fd_set rfds;
    fd_set error_fds;
    struct timeval tv;
    int retval;

   /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_ZERO(&error_fds);
    FD_SET(0, &rfds);
    FD_SET(3, &error_fds);

   /* Wait up to five seconds. */
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    char buf[5];

   retval = select(1, &rfds, NULL, &error_fds, &tv);
    /* Don't rely on the value of tv now! */

   if (retval == -1)
        perror("select()");
    else if (retval)	{
    	printf("Data is available now. %d \n", retval);
    	printf("The return of : FD_ISSET is: %d - %d ", FD_ISSET(0, &rfds), FD_ISSET(3, &error_fds));
    	if (FD_ISSET(0, &rfds))
    		read(0, buf, 5);

    	// if ()

    	printf("%s \n", buf);
    }   
        /* FD_ISSET(0, &rfds) will be true. */
    else
        printf("No data within five seconds.\n");

   return 0;
}