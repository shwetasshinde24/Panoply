/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <sgx_rpc_util.h>
#include <sgx_ocall_util.h>
#include <map>
#include <sgx_thread.h>
#include <sgx_trts.h>

#include <MyEnclave_t.h>

static sgx_thread_mutex_t rpc_handler_map_mutex = SGX_THREAD_MUTEX_INITIALIZER;
static std::map<unsigned long int , __dispatch_fn_t> id_to_handler_info_map;
extern sgx_enclave_id_t enclave_self_id;
extern bool initiated_self_id;

INIT_LOCK(ocall_svc_getargs);
INIT_LOCK(ocall_svc_sendreply);
INIT_LOCK(ocall_svc_freeargs);

static inline unsigned long int get_an_random_id()
{
    unsigned long int rand_number = 0;
    sgx_read_rand((unsigned char*)(&rand_number), sizeof(rand_number));

    if (!initiated_self_id || enclave_self_id>=100 )	{
    	abort();
    }

    // Reserved 100 for the eid
    return rand_number - (rand_number%100) + enclave_self_id;
}

unsigned long int  put_handler(__dispatch_fn_t new_handler)
{
    unsigned long int  new_id = get_an_random_id();
    sgx_thread_mutex_lock(&rpc_handler_map_mutex);
    while(id_to_handler_info_map.count((new_id))>0)   
    {
        new_id = get_an_random_id();
    }
    id_to_handler_info_map.insert(std::pair<unsigned long int , __dispatch_fn_t>(new_id, new_handler));
    sgx_thread_mutex_unlock(&rpc_handler_map_mutex);
    return new_id;
}

bool get_handler(unsigned long int  job_id, __dispatch_fn_t *pt_job)
{
    //Retreive the job information for the corresponding job id
    // printf("Some one call get_handler %d \n", job_id);
    std::map<unsigned long int , __dispatch_fn_t>::iterator it = id_to_handler_info_map.find(job_id);
    if(it != id_to_handler_info_map.end())
    {
        __dispatch_fn_t *tmp = &it->second;
        *pt_job = *tmp;
        return true;
    }
    else
    {
        return false;
    }    
}

int sgx_wrapper_pmap_set(unsigned long prognum, unsigned long versnum,
        unsigned int protocol, unsigned short port)
{
	int ret;
	sgx_status_t status = ocall_pmap_set(&ret, prognum, versnum, protocol, port);
	CHECK_STATUS(status);	
	return ret;
}

int sgx_wrapper_pmap_unset(unsigned long prognum, unsigned long versnum)
{
	int ret;
	sgx_status_t status = ocall_pmap_unset(&ret, prognum, versnum);
	CHECK_STATUS(status);	
	return ret;
}

unsigned short sgx_wrapper_pmap_getport(struct sockaddr_in *addr,
            unsigned long prognum, unsigned long versnum,
            unsigned int protocol)
{
	unsigned short  ret;
	sgx_status_t status = ocall_pmap_getport(&ret, addr, prognum, versnum, protocol);
	CHECK_STATUS(status);	
	return ret;
}

SVCXPRT *sgx_wrapper_svcudp_create (int sock)
{
	SVCXPRT *ret;
	sgx_status_t status = ocall_svcudp_create(&ret, sock);
	CHECK_STATUS(status);	
	return ret;
}

void sgx_wrapper_svc_run()
{
	sgx_status_t status = ocall_svc_run();
	CHECK_STATUS(status);	
}

SVCXPRT *sgx_wrapper_svctcp_create(int __sock, u_int __sendsize, u_int __recvsize)
{
	SVCXPRT *ret;
	sgx_status_t status = ocall_svctcp_create(&ret, __sock, __sendsize, __recvsize);
	CHECK_STATUS(status);	
	return ret;
}

bool_t sgx_wrapper_svc_register(SVCXPRT *__xprt, rpcprog_t __prog,
	    rpcvers_t __vers, __dispatch_fn_t __dispatch,
	    rpcprot_t __protocol)
{
	bool_t ret;
	sgx_status_t status;
	if (sgx_is_within_enclave(__dispatch, 1))	{
		// debug("Handler is: %p \n", __handler);
		unsigned long int handler_id = put_handler(__dispatch);
		status = ocall_svc_register_generic(&ret, __xprt, __prog, __vers, handler_id, __protocol); 
		// ocall_signal_generic(&retval, __sig, handler_id);
	} else {
		// debug("ocall_signal Handler is: %p \n", __handler);
		// status = ocall_signal(&retval, __sig, __handler);
		status = ocall_svc_register(&ret, __xprt, __prog, __vers, __dispatch, __protocol);
	}
	CHECK_STATUS(status);
	 	
	return ret;
}


CLIENT *sgx_wrapper_clnt_create (const char *__host, const u_long __prog,
	    const u_long __vers, const char *__prot)
{
	CLIENT *ret;
	sgx_status_t status = ocall_clnt_create(&ret, __host, __prog, __vers, __prot);
	CHECK_STATUS(status);	
	return ret;
}

void sgx_wrapper_clnt_perror (CLIENT *__clnt, const char *__msg)
{
	sgx_status_t status = ocall_clnt_perror(__clnt, __msg);
}

void sgx_wrapper_clnt_pcreateerror (const char *__msg)
{
	sgx_status_t status = ocall_clnt_pcreateerror(__msg);
}


int sgx_wrapper_callrpc (const char *__host, const u_long __prognum,
    const u_long __versnum, const u_long __procnum,
    xdrproc_t __inproc, const char *__in,
    xdrproc_t __outproc, char *__out)
{
	int ret;
	sgx_status_t status = ocall_callrpc(&ret, __host, __prognum, __versnum, __procnum, __inproc, __in, __outproc, __out);
	CHECK_STATUS(status);	
	return ret;
}

bool_t sgx_wrapper_svc_sendreply (SVCXPRT *__xprt, xdrproc_t __xdr_results,
	       caddr_t __xdr_location)
{
	CHECK_OUTSIDE_ENCLAVE(__xdr_location);
	bool_t ret;
	sgx_status_t status = SAFE_INVOKE(ocall_svc_sendreply, &ret, __xprt, __xdr_results, __xdr_location);
	CHECK_STATUS(status);	
	return ret;
}

void sgx_wrapper_svcerr_noproc(SVCXPRT *__xprt)
{
	sgx_status_t status = ocall_svcerr_noproc(__xprt);
	CHECK_STATUS(status);
}

void sgx_wrapper_svcerr_decode(SVCXPRT *__xprt)
{
	sgx_status_t status = ocall_svcerr_decode(__xprt);
	CHECK_STATUS(status);
}

void sgx_wrapper_svcerr_systemerr (SVCXPRT *__xprt)
{
	sgx_status_t status = ocall_svcerr_systemerr(__xprt);
	CHECK_STATUS(status);
}

bool sgx_wrapper_clnt_call(CLIENT *rh, unsigned long proc, xdrproc_t xargs, caddr_t argsp, 
			xdrproc_t xres, caddr_t resp, struct timeval timeout)
{
	bool ret;

	// xargs = xdr_bytes;
	// xres = xdr_bytes;
	CHECK_OUTSIDE_ENCLAVE(argsp);
	sgx_status_t status = ocall_clnt_call(&ret, rh, proc, xargs, argsp, xres, resp, timeout);
	// sgx_status_t status = ocall_fast_clnt_call(proc);
	CHECK_STATUS(status);	
	return RPC_SUCCESS;
}

bool_t sgx_wrapper_clnt_control(CLIENT *cl, u_int rq, char* in, int in_size)
{
	bool_t ret;
	sgx_status_t status = ocall_clnt_control(&ret, cl, rq, in, in_size);
	CHECK_STATUS(status);	
	return ret;
}

void ecall_generic_rpc_dispatch_handler(unsigned long int handler_id, struct svc_req *rqstp, register SVCXPRT *transp)
{
	// sgx_wrapper_printf("generic_rpc_dispatch_handler: %lu \n", handler_id);
	__dispatch_fn_t generic_dispatch;
	if (get_handler(handler_id, &generic_dispatch))	{
		// sgx_wrapper_printf("Handler address: %p - with signo: %d \n", generic_handler, signo);
		generic_dispatch(rqstp, transp);
	}
}

bool_t sgx_wrapper_svc_getargs(SVCXPRT *xprt, xdrproc_t xargs, char* argsp)
{
	bool_t ret;
	CHECK_OUTSIDE_ENCLAVE(argsp);
	sgx_status_t status = SAFE_INVOKE(ocall_svc_getargs, &ret, xprt, xargs, argsp);
	// (*(xprt)->xp_ops->xp_getargs)((xprt), (xargs), (argsp));
	CHECK_STATUS(status);	
	return ret;
}

bool_t sgx_wrapper_svc_freeargs(SVCXPRT *xprt, xdrproc_t xargs, char* argsp)
{
	bool_t ret;
	CHECK_OUTSIDE_ENCLAVE(argsp);
	sgx_status_t status = SAFE_INVOKE(ocall_svc_freeargs, &ret, xprt, xargs, argsp);
	CHECK_STATUS(status);	
	return ret;
}