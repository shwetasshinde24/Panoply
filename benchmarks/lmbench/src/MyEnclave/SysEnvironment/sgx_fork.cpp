/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sgx_fork_util.h>
#include <sgx_ocall_util.h>

#include <MyEnclave_t.h>

static const size_t WORD_SIZE = sizeof(size_t);
static void* unsealed_sync_buffer;
size_t fork_magic;
size_t* base_stack_pointer = NULL;
size_t* last_fp = NULL;
size_t* parent_ret_p = NULL;
bool is_origin = false;
static int ret_pid = -1;
static int parent_fd[2];
static int child_fd[2];

size_t enc_start_addr;
size_t sec_data_addr;
size_t sec_data_size;
size_t bss_sec_addr;
size_t bss_sec_size;

void close_fds(int fd[2])
{
    close(fd[0]);
    close(fd[1]);
    fd[0] = -1;
    fd[1] = -1;
}

void reset_fork_metadata()
{
    ret_pid = -1;
    is_origin = false;
    fork_magic = 0;
    close_fds(child_fd);
    close_fds(parent_fd);
}

int get_stack_size()
{
	size_t *frame_addr = (size_t*)__builtin_frame_address(0);
    size_t* stack_highest_addr = (size_t*)base_stack_pointer;

    int stack_size = (stack_highest_addr-frame_addr);
    return stack_size;
}

void* unseal_data(void *seal_buff, int size, uint32_t *unseal_buff_size)
{
	size_t unseal_size = ((float)1.3*size);
    uint8_t *unseal_buff = (uint8_t *)malloc(unseal_size);
    *unseal_buff_size = unseal_size;

    uint8_t *inside_seal_buff = (uint8_t *)malloc(size);

    if (unseal_buff==NULL || inside_seal_buff==NULL )
    {
        // sgx_wrapper_printf_debug("Malloc error \n");
        abort();        
    }

    memcpy(inside_seal_buff, seal_buff, size);
    // ocall_free(seal_buff);
    int error_code = sgx_unseal_data((const sgx_sealed_data_t *)inside_seal_buff, NULL, NULL, unseal_buff, unseal_buff_size);
    if (error_code!=SGX_SUCCESS)
    {
        // sgx_wrapper_printf_debug("Cannot unseal data, error is: %x \n", error_code);
        abort();
        return NULL;
    } 

    return unseal_buff;
}

int ecall_set_pipe_fd(int _parentfd[2], int _childfd[2])
{
	memcpy(parent_fd, _parentfd, sizeof(parent_fd));
	memcpy(child_fd, _childfd, sizeof(child_fd));
	return 1;
}

int ecall_set_parsed_section_info(const char* name, int type, size_t val)
{
	// // // sgx_wrapper_printf_debug("ecall_set_parsed_section_info \n");
    if (strcmp(name, ".start")==0)   {
        enc_start_addr = val;
        return 0;
    }


    if (strcmp(name, ".data")==0)   {
        switch(type)    {
            case 0: // return section address
		        sec_data_addr = val;
		        return 0;
            case 1:
		        sec_data_size = val;
		        return 0;
            default: 
                return -1;
        }
    }

    if (strcmp(name, ".bss")==0)   {
        switch(type)    {
            case 0: // return section address
		        bss_sec_addr = val;
		        return 0;
            case 1:
		        bss_sec_size = val;
		        return 0;
            default: 
                return -1;                
        }
    }

    return -1;  
}

bool satisfy_fork_condition()
{
	return enc_start_addr!=0 && sec_data_addr!=0 && bss_sec_addr!=0 && base_stack_pointer!=0;
}

void sync_the_heap()
{
    // sgx_wrapper_printf_debug("sync_the_heap \n");
    if (is_origin) {
        return;
    }

    size_t* sec_buff = (size_t*)unsealed_sync_buffer;
    size_t sync_enc_start_addr = sec_buff[0];
    size_t sync_dsec_size = sec_buff[1];
    size_t sync_bsec_size = sec_buff[2];
    size_t sync_stack_size = sec_buff[3];
    size_t sync_heap_size = sec_buff[4];
    size_t sync_mlstate_size = sec_buff[5];
    size_t sync_mlparam_size = sec_buff[6];

    if (sync_mlstate_size*WORD_SIZE!=mstate_size || sync_mlparam_size*WORD_SIZE!=mparam_size)
    {
        // sgx_wrapper_printf_debug("Malloc state struct is not matched \n");
        // sgx_wrapper_printf_debug("Ml state size diff: %u - %u \n", sync_mlstate_size*WORD_SIZE, mstate_size);
        // sgx_wrapper_printf_debug("Ml para, size diff: %u - %u \n", sync_mlparam_size*WORD_SIZE, mparam_size);
        abort();        
    }

    size_t* hsec_buff = sec_buff+7+sync_dsec_size+sync_bsec_size+sync_stack_size;
    size_t* mlstate_buff = sec_buff+7+sync_dsec_size+sync_bsec_size+sync_stack_size+sync_heap_size;
    size_t* mlparam_buff = sec_buff+7+sync_dsec_size+sync_bsec_size+sync_stack_size+sync_heap_size+sync_mlstate_size;

    // Copy parent's heap to stack and free allocated mem
    size_t hsec_in_stk[sync_heap_size];
    size_t mlstate_in_stk[sync_mlstate_size];
    size_t mlparam_in_stk[sync_mlparam_size];

    memcpy(hsec_in_stk, hsec_buff, sync_heap_size*WORD_SIZE);
    memcpy(mlstate_in_stk, mlstate_buff, sync_mlstate_size*WORD_SIZE);
    memcpy(mlparam_in_stk, mlparam_buff, sync_mlparam_size*WORD_SIZE);
    free(unsealed_sync_buffer);

    // Overwrite heap metadata
    memcpy(malloc_mparams_ptr, mlparam_in_stk, mparam_size);
    memcpy(malloc_gm_ptr, mlstate_in_stk, mstate_size);
    *(hu_ptr) = sync_heap_size*WORD_SIZE;

    // Copy parent's heap to heap
    memcpy((void *)GET_MS_LEAST_ADDR(malloc_gm_ptr), hsec_in_stk, sync_heap_size*WORD_SIZE);
}


void start_fork()
{
    // sgx_wrapper_printf_debug("The enclave start addr I archieve is: ==0x%llx \n", enc_start_addr);
    // sgx_wrapper_printf_debug("The .data start addr I archieve is: ==0x%llx \n", sec_data_addr);
    // sgx_wrapper_printf_debug("The .data size addr I archieve is: ==0x%x \n", sec_data_size);
    // sgx_wrapper_printf_debug("The .bss start addr I archieve is: ==0x%llx \n", bss_sec_addr);
    // sgx_wrapper_printf_debug("The .bss size addr I archieve is: ==0x%x \n", bss_sec_size);      
    size_t* data_sec_start_addr = (size_t*)(enc_start_addr+sec_data_addr);
    size_t* data_sec_end_addr = (size_t*)(enc_start_addr+sec_data_addr+sec_data_size);
    size_t* bss_sec_start_addr = (size_t*)(enc_start_addr+bss_sec_addr);
    size_t* bss_sec_end_addr = (size_t*)(enc_start_addr+bss_sec_addr+bss_sec_size);
    void *ret_addr = __builtin_return_address(0);
    parent_ret_p = (size_t*)ret_addr;
    size_t *frame_addr = (size_t*)__builtin_frame_address(0); 
    last_fp = frame_addr;   
    size_t* stack_highest_addr = (size_t*)base_stack_pointer;

    int dsec_size = (data_sec_end_addr-data_sec_start_addr);
    int bsec_size = (bss_sec_end_addr-bss_sec_start_addr);
    int stack_size = (stack_highest_addr-frame_addr);
    int heap_size = (*hu_ptr)/WORD_SIZE;
    int mlstate_size = mstate_size/WORD_SIZE;
    int mlparam_size = mparam_size/WORD_SIZE;
    int total_size = dsec_size+bsec_size+stack_size+heap_size + mlstate_size + mlparam_size + 7;

    // // sgx_wrapper_printf_debug("\n start_fork Stack size is: %d - Total size: %d \n", stack_size, total_size);

    size_t data_sec[dsec_size];
    size_t sec_buff[total_size];
    size_t magic;

    if (sgx_read_rand((unsigned char*)&fork_magic, sizeof(size_t))!=SGX_SUCCESS)
    {
        // sgx_wrapper_printf_debug("Cannot random nonce \n");
        abort();
    }

    sec_buff[0] = enc_start_addr;
    sec_buff[1] = dsec_size;
    sec_buff[2] = bsec_size;
    sec_buff[3] = stack_size;
    sec_buff[4] = heap_size;
    sec_buff[5] = mlstate_size;
    sec_buff[6] = mlparam_size;
    size_t* dsec_buff = sec_buff+7;
    size_t* bsec_buff = sec_buff+7+dsec_size;
    size_t* ssec_buff = sec_buff+7+dsec_size+bsec_size;
    size_t* hsec_buff = sec_buff+7+dsec_size+bsec_size+stack_size;
    size_t* mlstate_buff = sec_buff+7+dsec_size+bsec_size+stack_size+heap_size;
    size_t* mlparam_buff = sec_buff+7+dsec_size+bsec_size+stack_size+heap_size+mlstate_size;

    memcpy(dsec_buff, data_sec_start_addr, dsec_size*WORD_SIZE);
    memcpy(bsec_buff, bss_sec_start_addr, bsec_size*WORD_SIZE);
    memcpy(ssec_buff, frame_addr, stack_size*WORD_SIZE);
    
    // In extreme case, heap can be very big and need to split to churns 
    memcpy(hsec_buff, (void *)GET_MS_LEAST_ADDR(malloc_gm_ptr), heap_size*WORD_SIZE);
    memcpy(mlstate_buff, malloc_gm_ptr, mlstate_size*WORD_SIZE);
    memcpy(mlparam_buff, malloc_mparams_ptr, mlparam_size*WORD_SIZE);

    memcpy(frame_addr, ssec_buff, stack_size*WORD_SIZE);

    // sgx_wrapper_printf_debug("The size of: heap: %llu, stack: %llu, total: %llu \n", heap_size, stack_size, total_size);

    // Sampling all the stacks and heap. Now can create the memory region for seal data
    size_t seal_len = sgx_calc_sealed_data_size(0, total_size*WORD_SIZE);

    // sgx_wrapper_printf_debug("The seallen need: %lu \n", seal_len);

    uint8_t* seal_buf = (uint8_t*)malloc(seal_len);
    uint8_t* outside_buf = (uint8_t*)untrusted_malloc(seal_len);

    if (seal_buf==NULL || outside_buf==NULL) {
        printf("Malloc error \n");
        abort();
    }

    if (sgx_seal_data(0, NULL, total_size*WORD_SIZE, (const uint8_t*)sec_buff, seal_len, (sgx_sealed_data_t *)seal_buf))
    {
        // sgx_wrapper_printf_debug("seal data error \n");
        abort();
    }

    memcpy(outside_buf, seal_buf, seal_len);
    free(seal_buf);

    int msg_size;

    int bufsiz = 1000;
    uint8_t ret_msg[bufsiz]; 
    // void *ret_msg = malloc(bufsiz);

    int code = ocall_fork(&msg_size, outside_buf, seal_len, ret_msg, bufsiz);
    is_origin = true;

    uint32_t original_ack_size;

    size_t* ack_msg = (size_t*)unseal_data(ret_msg, msg_size, &original_ack_size);
    
    /* Only if ack_msg is matched with the same fork_magic, then proceed */
    if (ack_msg!=NULL && fork_magic == ack_msg[0] )	
    {
        size_t parent_ack_msg[2];
    	ret_pid = ack_msg[1];

        parent_ack_msg[0] = fork_magic+1;
        parent_ack_msg[1] = ret_pid;

        size_t parent_ack_seal_len = sgx_calc_sealed_data_size(0, sizeof(parent_ack_msg));
        uint8_t parent_ack_seal_buf[parent_ack_seal_len];

        if (sgx_seal_data(0, NULL, sizeof(parent_ack_msg), (const uint8_t*)parent_ack_msg, parent_ack_seal_len, (sgx_sealed_data_t *)parent_ack_seal_buf))
        {
            sgx_wrapper_printf_debug("seal parent_ack_seal_buf error \n");
            abort();
        }
        write(child_fd[1], parent_ack_seal_buf, parent_ack_seal_len);
    	free(ack_msg);
    } else {
        // // sgx_wrapper_printf_debug("ack_msg is not matched \n");
    	ret_pid = -1;
        // abort();
    }

}

bool check_stack_integrity(void *buffer, int size)
{
    return true;
}

int compute_stack_gap(void* sta, int stack_size)
{
    size_t *frame_addr = (size_t*)__builtin_frame_address(0); 
    return last_fp - frame_addr;
}

void inner_overwrite_stack(void* sta, int stack_size)    
{
    // sgx_wrapper_printf_debug("start inner_overwrite_stack\n");
    size_t *frame_addr = (size_t*)__builtin_frame_address(0); 
    int offset = last_fp - frame_addr;

    if (offset!=0)  {
        // sgx_wrapper_printf_debug("two stacks don't have the same size \n");
        abort();
    }

    memcpy(last_fp, sta, stack_size*WORD_SIZE);
    void *ret_addr = __builtin_return_address(0);
    if (ret_addr!=parent_ret_p) {
        // sgx_wrapper_printf_debug("overwritten stack error\n");
        abort();
    }
    // sgx_wrapper_printf_debug("Pass overwritten stack\n");
}

void ecall_sync_stack(void *seal_buff, int seal_buff_size)
{
    // // sgx_wrapper_printf_debug("The base stack is: %p \n", base_stack_pointer);
    uint32_t buffer_size;

    void* buffer = unseal_data(seal_buff, seal_buff_size, &buffer_size);

    // Since we cannot sync the heap for now, save it for later
    unsealed_sync_buffer = buffer;

    size_t* sec_buff = (size_t*)buffer;
    size_t sync_enc_start_addr = sec_buff[0];
    size_t sync_dsec_size = sec_buff[1];
    size_t sync_bsec_size = sec_buff[2];
    size_t sync_stack_size = sec_buff[3];

    // // // sgx_wrapper_printf_debug("sync_stack_size: %d \n", sync_stack_size);

    // // // sgx_wrapper_printf_debug("ecall_sync_stack with buf size: %d  -- size is: %d \n", (sync_dsec_size+sync_bsec_size+sync_stack_size+4)*WORD_SIZE, buffer_size);

    // if ((sync_dsec_size+sync_bsec_size+sync_stack_size)*4)

    // sgx_wrapper_printf_debug("The enclave start addr I archieve is: ==0x%llx \n", enc_start_addr);
    // sgx_wrapper_printf_debug("The .data start addr I archieve is: ==0x%llx \n", sec_data_addr);
    // sgx_wrapper_printf_debug("The .data size addr I archieve is: ==0x%x \n", sec_data_size);
    // sgx_wrapper_printf_debug("The .bss start addr I archieve is: ==0x%llx \n", bss_sec_addr);
    // sgx_wrapper_printf_debug("The .bss size addr I archieve is: ==0x%x \n", bss_sec_size); 

    size_t offset = enc_start_addr - sync_enc_start_addr;

    if (!check_stack_integrity(buffer, buffer_size) || offset!=0)   {
        abort();
    }

    size_t* data_sec_start_addr = (size_t*)(enc_start_addr+sec_data_addr);
    size_t* data_sec_end_addr = (size_t*)(enc_start_addr+sec_data_addr+sec_data_size);

    size_t* bss_sec_start_addr = (size_t*)(enc_start_addr+bss_sec_addr);
    size_t* bss_sec_end_addr = (size_t*)(enc_start_addr+bss_sec_addr+bss_sec_size);

    int dsec_size = (data_sec_end_addr-data_sec_start_addr);
    int bsec_size = (bss_sec_end_addr-bss_sec_start_addr);
    
    if (sync_dsec_size!=dsec_size || sync_bsec_size!=bsec_size) 
    {
        // sgx_wrapper_printf_debug("Size is not matched \n");
        abort();
    }

    size_t* dsec_buff = sec_buff+7;
    size_t* bsec_buff = sec_buff+7+dsec_size;
    size_t* ssec_buff = sec_buff+7+dsec_size+bsec_size;

    
    memcpy(data_sec_start_addr, dsec_buff, dsec_size);

    // // sgx_wrapper_printf_debug("The bsec_size is: %d \n", bsec_size);
    // // sgx_wrapper_printf_debug("The offset is: %u \n", offset);
    // sgx_wrapper_printf_debug("Do the check \n");
    int p_count = 0;
    for (int i=0; i<bsec_size; i++) {
        if(bss_sec_start_addr[i]!=bsec_buff[i]) {
            size_t diff = bss_sec_start_addr[i]-bsec_buff[i];

            // If the bss addr is not zero, it is definitely system variable use by the sdk.
            // Then we have to skip
            if (bss_sec_start_addr[i]==0)   {
                bss_sec_start_addr[i] = bsec_buff[i];
            } else {
                // sgx_wrapper_printf_debug("%p  --  %p \n", bss_sec_start_addr+i, bsec_buff+i);
                // sgx_wrapper_printf_debug("%d : 0x%llx-0x%llx : %u \n", i, bsec_buff[i], bss_sec_start_addr[i], diff);
            }
        }
    }

    void *to_sync_stack = malloc(sync_stack_size*WORD_SIZE);
    memcpy(to_sync_stack, ssec_buff, sync_stack_size*WORD_SIZE);

    // We should fill the stack so that the parent and child stack with the same size
    int stack_gap = compute_stack_gap(to_sync_stack, sync_stack_size);

    if (stack_gap>0)    {
        // sgx_wrapper_printf_debug("Bug child stack is larger than parent stack before sync\n");
        abort();
    }

    char fill_in_stack[abs(stack_gap)*8];
    stack_gap = compute_stack_gap(to_sync_stack, sync_stack_size);

    if (stack_gap!=0)   {
        // sgx_wrapper_printf_debug("Bug, the gap should be 0. The real gap is: %d \n", stack_gap);
        abort();
    }

    inner_overwrite_stack(to_sync_stack, sync_stack_size);
}

void process_ack_msg()
{
	if (!is_origin)	{
		size_t ack_msg[2];
		ack_msg[0] = fork_magic;
		ack_msg[1] = getpid();

	    size_t seal_len = sgx_calc_sealed_data_size(0, sizeof(ack_msg));
	    uint8_t seal_buf[seal_len];

	    if (sgx_seal_data(0, NULL, sizeof(ack_msg), (const uint8_t*)ack_msg, seal_len, (sgx_sealed_data_t *)seal_buf))
	    {
	        // sgx_wrapper_printf_debug("seal data error \n");
	        abort();
	    }
		write(parent_fd[1], seal_buf, seal_len);

        // Wait for the ack from parent to proceed
        {
            int bufsiz = 1000, ret_msg_sz = -1;
            uint8_t ret_msg[bufsiz]; 
            ocall_wait_for_parent_ack(&ret_msg_sz, ret_msg, bufsiz, child_fd[0]);

            if (ret_msg_sz<=0)   {
                sgx_wrapper_printf_debug("No ack msg ret \n");
                abort();
            }

            uint32_t original_parent_ack_size;
            size_t* parent_ack_msg = (size_t*)unseal_data(ret_msg, ret_msg_sz, &original_parent_ack_size);

            if (parent_ack_msg[0]!=fork_magic+1 && parent_ack_msg[1]!=ack_msg[1])   
            {
                sgx_wrapper_printf_debug("Parent ack msg mismatch \n");
                abort();
            }
        }
	}
}

int sgx_wrapper_fork()
{
	if(!satisfy_fork_condition())	{
		// sgx_wrapper_printf_debug("Section addr or base stack pointer is not set \n");
        abort();
		return -1;
	}

	int stack_size = get_stack_size();
	int fill_in_size = stack_size > 200 ? 1 : 1000;
	char fill_in_stack[fill_in_size];

    start_fork();
    sync_the_heap();
    process_ack_msg();

    if (is_origin)  {
        int dup_ret_pid = ret_pid;
        // Reset the state of is_origin
        reset_fork_metadata();
        // printf("Fork return father");
        return dup_ret_pid;
    }
    else {
        reset_fork_metadata();
        // printf("Fork return child");
        return 0;
    }
}

extern int memsize_main(int ac, char **av);
extern int latfs_main(int ac, char **av);
extern int signal_test_main(int argc, char **argv);
extern int fork_test_main(int argc, char **argv);
extern int helloworld_main();
extern int latconnect_main(int ac, char **av);
extern int mhz_main(int ac, char **av);
extern int loop_o_main();
extern int tlb_main(int ac, char **av);
extern int msleep_main(int ac, char **av);
extern int par_ops_main(int ac, char **av);
extern int latsig_main(int ac, char **av);
extern int latpipe_main(int ac, char **av);
extern int select_test_main(void);
extern int latops_main(int ac, char **av);
extern int latfcntl_main(int ac, char **av);
extern int latdram_main(int ac, char **av);
extern int latsyscall_main(int ac, char **av);
extern int parmem_main(int ac, char **av);
extern int latmemrd_main(int ac, char **av);
extern int latrand_main(int ac, char **av);
extern int bwmem_main(int ac, char **av);
extern int bwpipe_main(int ac, char *av[]);
extern int bwfilerd_main(int ac, char **av);
extern int latunix_main(int ac, char **av);
extern int latfifo_main(int ac, char **av);
extern int latusleep_main(int ac, char **av);
extern int latudp_main(int ac, char **av);
extern int lattcp_main(int ac, char **av);
extern int latconnect_main(int ac, char **av);
extern int latunixconnect_main(int ac, char **av);
extern int latselect_main(int ac, char **av);
extern int lathttp_main(int ac, char **av);
extern int latpagefault_main(int ac, char **av);
extern int latpmake_main(int ac, char **av);
extern int bwtcp_main(int ac, char **av);
extern int bwudp_main(int ac, char **av);
extern int bwunix_main(int argc, char *argv[]);
extern int latctx_main(int ac, char **av);
extern int latproc_main(int ac, char **av);
extern int latcmd_main(int ac, char **av);
extern int latfs_main(int ac, char **av);
extern int latmmap_main(int ac, char **av);
extern int latsig_main(int ac, char **av);
extern int disk_main(int ac, char **av);
extern int cache_main(int ac, char **av);
extern int stream_main(int ac, char **av);
extern int line_main(int ac, char **av);
extern int bwmmaprd_main(int ac, char **av);
extern int enough_main();
extern int flushdisk_main(int ac, char **av);
extern int timing_main();
extern int latrpc_main(int ac, char **av);
extern int lat_mem_rd_old_main(int ac, char **av);
extern int lmhttp_main(int ac, char **av);
extern int lmdd_main(int ac, char **av);

void do_main(int argc, char **argv, int main_index)
{
    switch(main_index)  {
        case 0:
                bwfilerd_main(argc, argv);
            break;
        case 1:
            bwmem_main(argc, argv);
            break;
        case 2:
            bwmmaprd_main(argc, argv);
            break;
        case 3:
            bwpipe_main(argc, argv);
            break;
        case 4:
            bwtcp_main(argc, argv);
            break;
        case 5:
            // bwudp_main(argc, argv);
            break;
        case 6:
            bwunix_main(argc, argv);
            break;
        case 7:
            // cache_main(argc, argv);
            break;
        case 8:
            disk_main(argc, argv);
            break;
        case 9:
            enough_main();
            break;
        case 10:
            // flushdisk_main(argc, argv);
            break;
        case 11:
            helloworld_main( );
            break;
        case 12:
            // latcmd_main(argc, argv);
            break;
        case 13:
            latconnect_main(argc, argv);
            break;
        case 14:
            latctx_main(argc, argv);
            break;
        case 15:
            // latdram_main(argc, argv);
            break;
        case 16:
            latfcntl_main(argc, argv);
            break;
        case 17:
            latfifo_main(argc, argv);
            break;
        case 18:
            latfs_main(argc, argv);
            break;
        case 19:
            lathttp_main(argc, argv);
            break;
        case 20:
            lat_mem_rd_old_main(argc, argv);
            break;
        case 21:
            latmmap_main(argc, argv);
            break;
        case 22:
            // latops_main(argc, argv);
            break;
        case 23:
            latpagefault_main(argc, argv);
            break;
        case 24:
            latpipe_main(argc, argv);
            break;
        case 25:
            // latpmake_main(argc, argv);
            break;
        case 26:
            latproc_main(argc, argv);
            break;
        case 27:
            // latrand_main(argc, argv);
            break;    
        case 28:
            latrpc_main(argc, argv);
            break;
        case 29:
            latselect_main(argc, argv);
            break;
        case 30:
            // latsem(argc, argv);
            break;
        case 31:
            latsig_main(argc, argv);
            break;
        case 32:
            latsyscall_main(argc, argv);
            break;
        case 33:
            lattcp_main(argc, argv);
            break;
        case 34:
            latudp_main(argc, argv);
            break;
        case 35:
            latunix_main(argc, argv);
            break;
        case 36:
            latunixconnect_main(argc, argv);
            break;
        case 37:
            // // latusleep_main(argc, argv);
            break;
        case 38:
            // line_main(argc, argv);
            break;
        case 39:
            // loop_o_main();
            break;
        case 40:
            memsize_main(argc, argv);
            break;
        case 41:
            mhz_main(argc, argv);
            break;
        case 42:
            msleep_main(argc, argv);
            break;
        case 43:
            // parmem_main(argc, argv);
            break;
        case 44:
            // par_ops_main(argc, argv);
            break;
        case 45:
            // stream_main(argc, argv);
            break;
        case 46:
            // timing_main();
            break;
        case 47:
            // tlb_main(argc, argv);
            break;
        case 48:
            // disk_main(argc, argv);
            break;
        case 49:
            lmhttp_main(argc, argv);
            break;
        case 50: 
            lmdd_main(argc, argv);
            break;
    }
    // select_test_main();
    // fork();
}

void addextra_layer(void *seal_buff, int seal_buff_size)
{
    ecall_sync_stack(seal_buff, seal_buff_size);
}

extern int update_untrusted_buff_addr();

void ecall_fork_enter_main(void *seal_buff, int seal_buff_size, int argc, char **argv, int main_index)
{
    update_untrusted_buff_addr();
    register size_t sp asm ("sp");
    bool is_base_stack = base_stack_pointer==NULL;
    if (is_base_stack)  {
        base_stack_pointer = (size_t*)sp;
        base_stack_pointer += 50;
    }
    // printf("The base stack origional is: %p \n", base_stack_pointer);

    {
	    // This mem region will served as a margin 
	    // for copying the heap dont free it
	    void* tmp1 = malloc(10);
    }

	if (seal_buff_size==0)	{
		// Do the normal main call
		do_main(argc, argv, main_index);
	} else	{
		// Sync the stack as part of forking
		ecall_sync_stack(seal_buff, seal_buff_size);
	}

    if (is_base_stack)
        base_stack_pointer = NULL;

    // Optional: Only need when using recursive forks 
    // As fork still have bug from drivers when fork more than 2 Enclave !!!
    // ocall_fork_exit();
}