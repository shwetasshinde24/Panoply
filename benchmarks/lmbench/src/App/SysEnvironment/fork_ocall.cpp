/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <sched.h>
#include <sys/epoll.h>
#include <pthread.h>

# include <unistd.h>
#include "MyEnclave_u.h"
#include "sgx_urts.h"

typedef struct {
    size_t size;
    void* buffer;
    int parent_fd[2];
    int child_fd[2];
} buf_t;

extern size_t get_parsed_section_info(const char *name, int type);
extern int initialize_enclave(void);
extern sgx_enclave_id_t global_eid;

#define READ_END 0
#define WRITE_END 1
#define CHILD_STACK 8000000
#define MAXEVENTS 5
#define TIMEOUT 10000

void erase_previous_enclave()
{
    // int err = sgx_destroy_enclave(global_eid);
    // printf("Erase return: %x \n", err);
}

int init_and_sync_stack(void* args){

    int ret;

    erase_previous_enclave();

    if(initialize_enclave() < 0){
        printf("Initialize another enclave fail \n");
        abort();
        return -1; 
    }

    uint64_t enc_start_addr = get_parsed_section_info(".start", 0);
    uint64_t sec_data_addr = get_parsed_section_info(".data", 0);
    uint64_t sec_data_size = get_parsed_section_info(".data", 1);
    uint64_t bss_data_addr = get_parsed_section_info(".bss", 0);
    uint64_t bss_data_size = get_parsed_section_info(".bss", 1);

    // printf("The enclave start addr I archieve is: ==0x%llx \n", enc_start_addr);
    // printf("The .data start addr I archieve is: ==0x%llx \n", sec_data_addr);
    // printf("The .data size addr I archieve is: ==0x%x \n", sec_data_size);
    // printf("The .bss start addr I archeve is: ==0x%llx \n", bss_data_addr);
    // printf("The .bss size addr I archieve is: ==0x%x \n", bss_data_size); 

    MyEnclave_ecall_set_parsed_section_info(global_eid, &ret, ".start", 0, enc_start_addr);
    MyEnclave_ecall_set_parsed_section_info(global_eid, &ret, ".data", 0, sec_data_addr);
    MyEnclave_ecall_set_parsed_section_info(global_eid, &ret, ".data", 1, sec_data_size);
    MyEnclave_ecall_set_parsed_section_info(global_eid, &ret, ".bss", 0, bss_data_addr);
    MyEnclave_ecall_set_parsed_section_info(global_eid, &ret, ".bss", 1, bss_data_size);

    buf_t* buf_ptr = (buf_t*)args;  

    MyEnclave_ecall_set_pipe_fd(global_eid, &ret, buf_ptr->parent_fd, buf_ptr->child_fd);

    ret = MyEnclave_ecall_set_enclave_id(global_eid, global_eid);

    if (ret != SGX_SUCCESS) {
        // print_error_message(ret);
        abort();
    }  

    // printf("The seal data len is: %d \n", buf_ptr->size);

    MyEnclave_ecall_fork_enter_main(global_eid, buf_ptr->buffer, buf_ptr->size, 0, NULL, -1);

    // printf(".data size: %d, .bss size: %d \n", dsec_size, bsec_size );

}

/* use epoll to wait for msg to comes to the pipe */
int wait_for_incoming_msg(int fd, int maxev, int tout)
{
    struct epoll_event event;
    struct epoll_event *events;
    int efd, n , s;

    efd = epoll_create1(0);
    events = (epoll_event*)calloc(maxev, sizeof(event));

    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLRDHUP | EPOLLPRI;
    s = epoll_ctl (efd, EPOLL_CTL_ADD, fd, &event);
    n = epoll_wait (efd, events, maxev, tout);
    free(events);
    return n;
}

void* set_pipe_to_enclave(void* args)
{
    int ret;
    buf_t* buf_ptr = (buf_t*)args;
    return (void*)MyEnclave_ecall_set_pipe_fd(global_eid, &ret, buf_ptr->parent_fd, buf_ptr->child_fd);
}

/* This is the ocall fork implementation using clone */
// int ocall_fork(void* buffer, int size, void* childmsg_buff, int bufsiz)
// {
//     void *stack = malloc(CHILD_STACK);
//     buf_t buf_struct;
//     buf_struct.size = size;
//     buf_struct.buffer = buffer;

//     if (pipe(buf_struct.parent_fd)==-1)
//     {
//     	printf("pipe failed \n");
//     	return -1;
//     }

//     if (pipe(buf_struct.child_fd)==-1)
//     {
//     	printf("pipe failed \n");
//     	return -1;
//     }

//     clone(&init_and_sync_stack, (char *)stack + CHILD_STACK, CLONE_IO , &buf_struct);

//     int n = wait_for_incoming_msg(buf_struct.parent_fd[0], MAXEVENTS, TIMEOUT);

//     // If epoll wait terminate normally, set pipe to the enclave and check if there is correct data in the pipe and read
//     if (n>=0) {
//         int msg_size = -1, ret = -1;
    
//         /* Call create new thread to set pipe_fd since it is a nested ecall  */
//         pthread_t tid;
//         pthread_create(&tid, NULL, set_pipe_to_enclave, &buf_struct);
//         /* wait for the thread to finish and then return  */
//         (void) pthread_join(tid, NULL);
//         msg_size = read(buf_struct.parent_fd[0], childmsg_buff, bufsiz);
//         return msg_size;
//     } else {
//         return -1;
//     }
// }


int ocall_fork(void* buffer, int size, void* childmsg_buff, int bufsiz)
{
    void *stack = malloc(CHILD_STACK);
    buf_t buf_struct;
    buf_struct.size = size;
    buf_struct.buffer = buffer;

    if (pipe(buf_struct.parent_fd)==-1)
    {
        printf("pipe failed \n");
        return -1;
    }

    if (pipe(buf_struct.child_fd)==-1)
    {
        printf("pipe failed \n");
        return -1;
    }

    // clone(&init_and_sync_stack, (char *)stack + CHILD_STACK, CLONE_IO , &buf_struct);
    // sleep(5);

    int pid = fork();

    if (pid==0) {
        init_and_sync_stack(&buf_struct);
    } else {
        
        int n = wait_for_incoming_msg(buf_struct.parent_fd[0], MAXEVENTS, TIMEOUT);

        // If epoll wait terminate normally, check if there is correct data in the pipe and read
        if (n>=0) {
            int msg_size = -1, ret = -1;
        
            /* Call create new thread to set pipe_fd since it is a nested ecall  */
            pthread_t tid;
            pthread_create(&tid, NULL, set_pipe_to_enclave, &buf_struct);
            /* wait for the thread to finish and then return  */
            (void) pthread_join(tid, NULL);
            msg_size = read(buf_struct.parent_fd[0], childmsg_buff, bufsiz);
            return msg_size;
        } else {
            return -1;
        }

    }

}


void ocall_fork_exit()
{
    sgx_destroy_enclave(global_eid);
    
    printf("Info: SampleEnclave successfully returned.\n");

    printf("Enter a character before exit ...\n");
    exit(0);
}

int ocall_wait_for_parent_ack(void *seal_parent_msg, int msgsiz, int read_fd)
{
    int n = wait_for_incoming_msg(read_fd, MAXEVENTS, TIMEOUT);

    if (n>=0) {
        int msg_size = -1;
        msg_size = read(read_fd, seal_parent_msg, msgsiz);
        return msg_size;
    } else {
        return -1;
    }

    return -1;
}