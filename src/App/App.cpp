#include <string.h>
#include <assert.h>

#include <unistd.h>
#include <pwd.h>
#include <libgen.h>
#include <stdlib.h>

# define MAX_PATH FILENAME_MAX


#include <sgx_urts.h>
#include <sgx_status.h>
#include "App.h"

#include "TopensslEnclave_u.h"

void print_string(const char* string)   {
    printf("print_string%s\n", string);
}

void print_int(int n)   {
    printf("print_int%d\n", n);
}

/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;

typedef struct _sgx_errlist_t {
    sgx_status_t err;
    const char *msg;
    const char *sug; /* Suggestion */
} sgx_errlist_t;

/* Error code returned by sgx_create_enclave */
static sgx_errlist_t sgx_errlist[] = {
    {
        SGX_ERROR_UNEXPECTED,
        "Unexpected error occurred.",
        NULL
    },
    {
        SGX_ERROR_INVALID_PARAMETER,
        "Invalid parameter.",
        NULL
    },
    {
        SGX_ERROR_OUT_OF_MEMORY,
        "Out of memory.",
        NULL
    },
    {
        SGX_ERROR_ENCLAVE_LOST,
        "Power transition occurred.",
        "Please refer to the sample \"PowerTransition\" for details."
    },
    {
        SGX_ERROR_INVALID_ENCLAVE,
        "Invalid enclave image.",
        NULL
    },
    {
        SGX_ERROR_INVALID_ENCLAVE_ID,
        "Invalid enclave identification.",
        NULL
    },
    {
        SGX_ERROR_INVALID_SIGNATURE,
        "Invalid enclave signature.",
        NULL
    },
    {
        SGX_ERROR_OUT_OF_EPC,
        "Out of EPC memory.",
        NULL
    },
    {
        SGX_ERROR_NO_DEVICE,
        "Invalid SGX device.",
        "Please make sure SGX module is enabled in the BIOS, and install SGX driver afterwards."
    },
    {
        SGX_ERROR_MEMORY_MAP_CONFLICT,
        "Memory map conflicted.",
        NULL
    },
    {
        SGX_ERROR_INVALID_METADATA,
        "Invalid enclave metadata.",
        NULL
    },
    {
        SGX_ERROR_DEVICE_BUSY,
        "SGX device was busy.",
        NULL
    },
    {
        SGX_ERROR_INVALID_VERSION,
        "Enclave version was invalid.",
        NULL
    },
    {
        SGX_ERROR_INVALID_ATTRIBUTE,
        "Enclave was not authorized.",
        NULL
    },
    {
        SGX_ERROR_ENCLAVE_FILE_ACCESS,
        "Can't open enclave file.",
        NULL
    },
};

/* Check error conditions for loading enclave */
void print_error_message(sgx_status_t ret)
{
    size_t idx = 0;
    size_t ttl = sizeof sgx_errlist/sizeof sgx_errlist[0];

    for (idx = 0; idx < ttl; idx++) {
        if(ret == sgx_errlist[idx].err) {
            if(NULL != sgx_errlist[idx].sug)
                printf("Info: %s\n", sgx_errlist[idx].sug);
            printf("Error: %s\n", sgx_errlist[idx].msg);
            break;
        }
    }
    
    if (idx == ttl)
        printf("Error: Unexpected error occurred. Error code: %x\n", ret);
}

/* Initialize the enclave:
 *   Step 1: retrive the launch token saved by last transaction
 *   Step 2: call sgx_create_enclave to initialize an enclave instance
 *   Step 3: save the launch token if it is updated
 */
int initialize_enclave_h2o(void)
{
    char token_path[MAX_PATH] = {'\0'};
    sgx_launch_token_t token = {0};
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    int updated = 0;
    /* Step 1: retrive the launch token saved by last transaction */

    /* try to get the token saved in $HOME */
    const char *home_dir = getpwuid(getuid())->pw_dir;
    if (home_dir != NULL && 
        (strlen(home_dir)+strlen("/")+sizeof(TOKEN_FILENAME)+1) <= MAX_PATH) {
        /* compose the token path */
        strncpy(token_path, home_dir, strlen(home_dir));
        strncat(token_path, "/", strlen("/"));
        strncat(token_path, TOKEN_FILENAME, sizeof(TOKEN_FILENAME)+1);
    } else {
        /* if token path is too long or $HOME is NULL */
        strncpy(token_path, TOKEN_FILENAME, sizeof(TOKEN_FILENAME));
    }

    FILE *fp = fopen(token_path, "rb");
    if (fp == NULL && (fp = fopen(token_path, "wb")) == NULL) {
        printf("Warning: Failed to create/open the launch token file \"%s\".\n", token_path);
    }
    printf("token_path: %s\n", token_path);
    if (fp != NULL) {
        /* read the token from saved file */
        size_t read_num = fread(token, 1, sizeof(sgx_launch_token_t), fp);
        if (read_num != 0 && read_num != sizeof(sgx_launch_token_t)) {
            /* if token is invalid, clear the buffer */
            memset(&token, 0x0, sizeof(sgx_launch_token_t));
            printf("Warning: Invalid launch token read from \"%s\".\n", token_path);
        }
    }

    /* Step 2: call sgx_create_enclave to initialize an enclave instance */
    /* Debug Support: set 2nd parameter to 1 */

    ret = sgx_create_enclave(H2O_FILENAME, SGX_DEBUG_FLAG, &token, &updated, &global_eid, NULL);

    if (ret != SGX_SUCCESS) {
        print_error_message(ret);
        if (fp != NULL) fclose(fp);

        return -1;
    }

    /* Step 3: save the launch token if it is updated */

    if (updated == FALSE || fp == NULL) {
        /* if the token is not updated, or file handler is invalid, do not perform saving */
        if (fp != NULL) fclose(fp);
        return 0;
    }

    /* reopen the file with write capablity */
    fp = freopen(token_path, "wb", fp);
    if (fp == NULL) return 0;
    size_t write_num = fwrite(token, 1, sizeof(sgx_launch_token_t), fp);
    if (write_num != sizeof(sgx_launch_token_t))
        printf("Warning: Failed to save launch token to \"%s\".\n", token_path);
    fclose(fp);

    return 0;
}

/* OCall functions */
void ocall_neverbleed_sample(const char *str)
{
    /* Proxy/Bridge will check the length and null-terminate 
     * the input string to prevent buffer overflow. 
     */
    printf("%s", str);
}


/* Application entry */
int SGX_CDECL main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);

    /* Changing dir to where the executable is.*/
    char absolutePath [MAX_PATH];
    char *ptr = NULL;
    char buf[500];

    ptr = realpath(dirname(argv[0]),absolutePath);

    if( chdir(absolutePath) != 0)
    		abort();

    int ecall_return = 0;
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    if(initialize_enclave_h2o() < 0){

                return -1; 
    }

    printf("Topenssl enclave id is: %d \n", global_eid);
    ret = TopensslEnclave_ecall_set_enclave_id(global_eid, global_eid);
    if (ret != SGX_SUCCESS)
        abort();

    // ret = TopensslEnclave_ecall_test_bm_ssl(global_eid, &ecall_return, argc, argv);
    ret = TopensslEnclave_ecall_test_speed_crypto(global_eid, &ecall_return, argc, argv);
    // if (ret != SGX_SUCCESS)
    //     abort();

    if (ecall_return == 0) {
      printf("From child Application ran with success\n");
    }
    else
    {
        printf("From child Application failed %d \n", ecall_return);
    }  

    sgx_destroy_enclave(global_eid);


    // int readpipe[2];
    // int writepipe[2];
    
    // if (pipe(readpipe)<0 || pipe(writepipe)<0)   {
    //     printf("Create read pipe failed \n");
    //     abort();
    // }

    // pid_t pid = fork();                  

    // switch(pid) {
    //     case -1:
    //         printf("Forking child process failed \n");
    //         abort();
    //     case 0: // Child process 
    //         close(readpipe[1]);
    //         close(writepipe[0]);

    //         /* Initialize the enclave */
            

    //         // char msg[500];
    //         // snprintf(msg, 500, "%d", global_eid);
    //         // if(write(writepipe[1],msg,strlen(msg)+1) < 0)
    //         // {
    //         //     // sgx_destroy_enclave(global_eid);
    //         //     // break;
    //         // }
            
    //         break;
    //     default: // Parent process
    //         break;
    //         // close(readpipe[0]);
    //         // close(writepipe[1]);   

    //         // if(read(writepipe[0],buf,sizeof(buf)) < 0)
    //         // {
    //         //     break;
    //         // }
    //         // // printf("\nParent Process Read: %s\n",buf);

    //         // int child_eid = 0;
    //         // char str[30];
    //         // sscanf(buf, "%d", &child_eid);
    //         // printf("After scanf: %d \n", child_eid);

    //         // if (child_eid>0)    {
    //         //     sgx_enclave_id_t parent_eid = child_eid;
    //         //     printf("TopensslEnclave_ecall_h2o_main: %d \n", parent_eid);
    //         //     ret = TopensslEnclave_ecall_h2o_main(parent_eid, &ecall_return, argc, argv); 
    //         //     if (ret != SGX_SUCCESS) {
    //         //         printf("The return code is: %x \n", ret);
    //         //         abort();                
    //         //     }
    //         // }

    //         // if (ecall_return == 0) {
    //         //   printf("From parent Application ran with success\n");
    //         // }
    //         // else
    //         // {
    //         //     printf("From parent Application failed %d \n", ecall_return);
    //         // }  

    // }
    
    return ecall_return;
}
