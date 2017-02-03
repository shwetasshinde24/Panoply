/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sgx_pthread_util.h>
#include <sgx_signal_util.h>
#include <sgx_ocall_util.h>
#include <map>
#include <sgx_trts.h>

#include <MyEnclave_t.h>

sgx_thread_mutex_t handler_map_mutex = SGX_THREAD_MUTEX_INITIALIZER;
std::map<unsigned long int , __sighandler_t> id_to_handler_info_map;
extern sgx_enclave_id_t enclave_self_id;
extern bool initiated_self_id;

static inline unsigned long int get_an_random_id(int __sig)
{
    unsigned long int rand_number = 0;
    sgx_read_rand((unsigned char*)(&rand_number), sizeof(rand_number));

    if (!initiated_self_id || enclave_self_id>=100 )	{
    	abort();
    }

    // Reserved 100 for the eid
    return rand_number - (rand_number%10000) + enclave_self_id + 100*__sig;
}

unsigned long int  put_handler(__sighandler_t new_handler, int __sig)
{
    unsigned long int  new_id = get_an_random_id(__sig);
    sgx_thread_mutex_lock(&handler_map_mutex);
    while(id_to_handler_info_map.count((new_id))>0)   
    {
        new_id = get_an_random_id(__sig);
    }
    id_to_handler_info_map.insert(std::pair<unsigned long int , __sighandler_t>(new_id, new_handler));
    sgx_thread_mutex_unlock(&handler_map_mutex);
    return new_id;
}

bool get_handler(unsigned long int  job_id, __sighandler_t *pt_job)
{
    //Retreive the job information for the corresponding job id
    // printf("Some one call get_handler %d \n", job_id);
    std::map<unsigned long int , __sighandler_t>::iterator it = id_to_handler_info_map.find(job_id);
    if(it != id_to_handler_info_map.end())
    {
        __sighandler_t *tmp = &it->second;
        *pt_job = *tmp;
        return true;
    }
    else
    {
        return false;
    }    
}

int sgx_wrapper_sigemptyset(sigset_t *set)
{
	int retval;
	sgx_status_t status = ocall_sigemptyset(&retval, set);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_sigfillset(sigset_t *set)
{
	int retval;
	sgx_status_t status = ocall_sigfillset(&retval, set);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_sigaddset(sigset_t *set, int signo)
{
	int retval;
	sgx_status_t status = ocall_sigaddset(&retval, set, signo);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_sigdelset(sigset_t *set, int signo)
{
	int retval;
	sgx_status_t status = ocall_sigdelset(&retval, set, signo);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_sigismember(const sigset_t *set, int signo)
{
	int retval;
	sgx_status_t status = ocall_sigismember(&retval, set, signo);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_sigsuspend(const sigset_t *set)
{
	int retval;
	sgx_status_t status = ocall_sigsuspend(&retval, set);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_sigaction(int sig, struct sigaction *act, struct sigaction *oact)
{
	int retval;
	sgx_status_t status;
	__sighandler_t __handler = act->sa_handler;
	if (__handler!=SIG_DFL && __handler!=SIG_IGN && __handler!=SIG_ERR )	{
		// debug("Handler is: %p \n", __handler);
		unsigned long int handler_id = put_handler(__handler, sig);
		act->sa_handler = (__sighandler_t)handler_id;
		status = ocall_sigaction_generic(&retval, sig, act, oact);
	} else {
		// debug("ocall_signal Handler is: %p \n", __handler);
		status = ocall_sigaction(&retval, sig, act, oact);
	}
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_sigpending(sigset_t *set)
{
	int retval;
	sgx_status_t status = ocall_sigpending(&retval, set);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_sigwait(const sigset_t *set, int *sig)
{
	int retval;
	sgx_status_t status = ocall_sigwait(&retval, set, sig);
	CHECK_STATUS(status);
	return retval;
}

__sighandler_t sgx_wrapper_signal(int __sig, __sighandler_t __handler)
{
	__sighandler_t retval;
	sgx_status_t status;
	if (__handler!=SIG_DFL && __handler!=SIG_IGN && __handler!=SIG_ERR )	{
		// debug("Handler is: %p \n", __handler);
		unsigned long int handler_id = put_handler(__handler, __sig);
		status = ocall_signal_generic(&retval, __sig, handler_id);
	} else {
		// debug("ocall_signal Handler is: %p \n", __handler);
		status = ocall_signal(&retval, __sig, __handler);
	}
	CHECK_STATUS(status);
	return retval;
}

void ecall_generic_signal_handler(unsigned long int handler_id)
{
	// debug("Call ecall_generic_signal_handler");
	__sighandler_t generic_handler;
	if (get_handler(handler_id, &generic_handler))	{
		int signo = (handler_id%10000)/100;
		// sgx_wrapper_printf("Handler address: %p - with signo: %d \n", generic_handler, signo);
		generic_handler(signo);
	}
}

int sgx_wrapper_raise(int signal)
{
	int retval;
	sgx_status_t status = ocall_raise(&retval, signal);
	CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_kill(pid_t pid, int sig)
{
	int retval;
	sgx_status_t status = ocall_kill(&retval, pid, sig);
	CHECK_STATUS(status);
	return retval;
}