/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <rpc/pmap_clnt.h>
#include <rpc/rpc.h>
#include <rpc/svc.h>
#include <rpc/clnt.h>

#include <pthread.h>
#include <map>
#include <unistd.h>

#include "MyEnclave_u.h"

// Define wrapper generic routine 
#define WRAPPER_xdr_void 1
#define WRAPPER_xdr_short 2
#define WRAPPER_xdr_u_short 3
#define WRAPPER_xdr_int 4
#define WRAPPER_xdr_u_int 5
#define WRAPPER_xdr_long 6
#define WRAPPER_xdr_u_long 7
#define WRAPPER_xdr_hyper 8
#define WRAPPER_xdr_u_hyper 9
#define WRAPPER_xdr_longlong_t 10
#define WRAPPER_xdr_u_longlong_t 11
#define WRAPPER_xdr_int8_t 12
#define WRAPPER_xdr_uint8_t 13
#define WRAPPER_xdr_int16_t 14
#define WRAPPER_xdr_uint16_t 15
#define WRAPPER_xdr_int32_t 16
#define WRAPPER_xdr_uint32_t 17
#define WRAPPER_xdr_int64_t 18
#define WRAPPER_xdr_uint64_t 19
#define WRAPPER_xdr_quad_t 20
#define WRAPPER_xdr_u_quad_t 21
#define WRAPPER_xdr_bool 22
#define WRAPPER_xdr_enum 23
#define WRAPPER_xdr_array 24
#define WRAPPER_xdr_bytes 25
#define WRAPPER_xdr_opaque 26
#define WRAPPER_xdr_string 27
#define WRAPPER_xdr_union 28
#define WRAPPER_xdr_char 29
#define WRAPPER_xdr_u_char 30
#define WRAPPER_xdr_vector 31
#define WRAPPER_xdr_float 32
#define WRAPPER_xdr_double 33
#define WRAPPER_xdr_reference 34 
#define WRAPPER_xdr_pointer 35
#define WRAPPER_xdr_wrapstring 36 
#define WRAPPER_xdr_sizeof 37

#define XACT_PROG ((u_long)404040)
#define XACT_VERS ((u_long)1)
#define RPC_XACT ((u_long)1)
#define RPC_EXIT ((u_long)2)

static __dispatch_fn_t dispatcher_ids[10];
static int dispatcher_count = 0;
extern sgx_enclave_id_t global_eid;

/*
 * The remote procedure[s] that will be called
 */
/* ARGSUSED */
// char	*
// rpc_xact_1(char *msg, register SVCXPRT *transp)
// {
// 	static char r;

// 	MyEnclave_ecall_rpc_xact_1(global_eid, msg, transp, &r, 1);

// 	return &r;
// }

// static void
// xact_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
// {
// 	union {
// 		char rpc_xact_1_arg;
// 	} argument;
// 	//char argument;

// 	char *result;
// 	bool_t (*xdr_argument)(), (*xdr_result)();
// 	char *(*local)(char *msg, register SVCXPRT *transp);

// 	switch (rqstp->rq_proc) {
// 	case NULLPROC:
// 		(void) svc_sendreply(transp, (xdrproc_t)xdr_void, (char *)NULL);
// 		return;

// 	case RPC_XACT:
// 		xdr_argument = (bool_t (*)())xdr_char;
// 		xdr_result = (bool_t (*)())xdr_char;
// 		local = (char *(*)(char *msg, register SVCXPRT *transp)) rpc_xact_1;
// 		break;

// 	case RPC_EXIT:
// 		(void) svc_sendreply(transp, (xdrproc_t)xdr_void, (char *)NULL);
// 		(void) pmap_unset(XACT_PROG, XACT_VERS);
// 		exit(0);

// 	default:
// 		svcerr_noproc(transp);
// 		return;
// 	}
// 	bzero((char *)&argument, 1);
// 	if (!svc_getargs(transp, (xdrproc_t)xdr_argument, (char*)&argument)) {
// 		printf("Dummy \n ");
// 	 	svcerr_decode(transp);
// 	 	return;
// 	}
// 	result = (*local)((char *)&argument, (SVCXPRT *)rqstp);
// 	// printf("%d -- %d \n", argument[0], result[0]);

// 	if (result != NULL && !svc_sendreply(transp, (xdrproc_t)xdr_result, result)) {
// 		svcerr_systemerr(transp);
// 	}
// 	if (!svc_freeargs(transp, (xdrproc_t)xdr_argument, (char*)&argument)) {
// 		fprintf(stderr, "unable to free arguments\n");
// 		exit(1);
// 	}
// 	return;
// }

typedef struct rpc_arg {
	unsigned long int handler_id;
	struct svc_req *rqstp;
	SVCXPRT *transp;
} rpc_arg_t;

void *call_dispatch_handler(void *arg)
{
	rpc_arg_t* my_arg = (rpc_arg_t*)arg;

	int enclave_id = my_arg->handler_id%100;
	usleep(5);
	// printf("Enclave id is: %d \n", enclave_id);
	int errorcode = MyEnclave_ecall_generic_rpc_dispatch_handler(enclave_id, my_arg->handler_id, my_arg->rqstp
		, my_arg->transp);
	if (errorcode!=0)	{
		printf("Ecall errocode return is: %x \n", errorcode);	
	} else {
		// printf("Done the handler with this handler id: %lu \n", *handler_id);
	}
	
	free(arg);
}

// #define DECLARE_GENERIC_STUB(index)                     \
//     static void generic_dispatch_stub_##index(struct svc_req *rqstp, register SVCXPRT *transp)                                              \
//     {    \
//         unsigned long int handler_id = (unsigned long int)dispatcher_ids[index];     \
//         int eid = handler_id%100;	\
//         rpc_arg_t* my_arg = (rpc_arg_t*)malloc(sizeof(rpc_arg_t));											\
//         my_arg->handler_id = handler_id; \
//         my_arg->rqstp = rqstp; \
//         my_arg->transp = transp; \
//         call_dispatch_handler(&my_arg); \
//     }
  //       pthread_t tid;			\
		// pthread_create(&tid, NULL, call_dispatch_handler, my_arg);		\
		// pthread_join(tid, NULL);  \

#define DECLARE_GENERIC_STUB(index)                     \
    static void generic_dispatch_stub_##index(struct svc_req *rqstp, register SVCXPRT *transp)                                              \
    {    \
        unsigned long int handler_id = (unsigned long int)dispatcher_ids[index];     \
        int eid = handler_id%100;	\
		int errorcode = MyEnclave_ecall_generic_rpc_dispatch_handler(eid, handler_id, rqstp  \
			, transp);  \
		if (errorcode!=0)	{  \
			printf("Ecall errocode return is: %x \n", errorcode);	\
		} else {  \
		} \
    }

DECLARE_GENERIC_STUB(0)
DECLARE_GENERIC_STUB(1)
DECLARE_GENERIC_STUB(2)
DECLARE_GENERIC_STUB(3)
DECLARE_GENERIC_STUB(4)
DECLARE_GENERIC_STUB(5)
DECLARE_GENERIC_STUB(6)
DECLARE_GENERIC_STUB(7)
DECLARE_GENERIC_STUB(8)
DECLARE_GENERIC_STUB(9)

#define generic_stub(index) generic_dispatch_stub_##index

static __dispatch_fn_t dispatcher_stubs[] = { generic_stub(0), generic_stub(1), generic_stub(2), generic_stub(3), generic_stub(4)   
, generic_stub(5), generic_stub(6), generic_stub(7), generic_stub(8), generic_stub(9) };


static inline xdrproc_t replace_wrapper(xdrproc_t xpt)
{
	switch((size_t)xpt)	{
		case WRAPPER_xdr_void :
			// printf("Replace wrapper to xdr_void \n");
			return (xdrproc_t)xdr_void;
		case WRAPPER_xdr_short :
			return (xdrproc_t)xdr_short;
		case WRAPPER_xdr_u_short :
			return (xdrproc_t)xdr_u_short;
		case WRAPPER_xdr_int :
			return (xdrproc_t)xdr_int;
		case WRAPPER_xdr_u_int :
			return (xdrproc_t)xdr_u_int;
		case WRAPPER_xdr_long :
			return (xdrproc_t)xdr_long;
		case WRAPPER_xdr_u_long :
			return (xdrproc_t)xdr_u_long;
		case WRAPPER_xdr_hyper :
			return (xdrproc_t)xdr_hyper;
		case WRAPPER_xdr_u_hyper :
			return (xdrproc_t)xdr_u_hyper;
		case WRAPPER_xdr_longlong_t :
			return (xdrproc_t)xdr_longlong_t;
		case WRAPPER_xdr_u_longlong_t :
			return (xdrproc_t)xdr_u_longlong_t;
		case WRAPPER_xdr_int8_t :
			return (xdrproc_t)xdr_int8_t;
		case WRAPPER_xdr_uint8_t :
			return (xdrproc_t)xdr_uint8_t;
		case WRAPPER_xdr_int16_t :
			return (xdrproc_t)xdr_int16_t;
		case WRAPPER_xdr_uint16_t :
			return (xdrproc_t)xdr_uint16_t;
		case WRAPPER_xdr_int32_t :
			return (xdrproc_t)xdr_int32_t;
		case WRAPPER_xdr_uint32_t :
			return (xdrproc_t)xdr_uint32_t;
		case WRAPPER_xdr_int64_t :
			return (xdrproc_t)xdr_int64_t;
		case WRAPPER_xdr_uint64_t :
			return (xdrproc_t)xdr_uint64_t;
		case WRAPPER_xdr_quad_t :
			return (xdrproc_t)xdr_quad_t;
		case WRAPPER_xdr_u_quad_t :
			return (xdrproc_t)xdr_u_quad_t;
		case WRAPPER_xdr_bool :
			return (xdrproc_t)xdr_bool;
		case WRAPPER_xdr_enum :
			return (xdrproc_t)xdr_enum;
		case WRAPPER_xdr_array :
			return (xdrproc_t)xdr_array;
		case WRAPPER_xdr_bytes :
			return (xdrproc_t)xdr_bytes;
		case WRAPPER_xdr_opaque :
			return (xdrproc_t)xdr_opaque;
		case WRAPPER_xdr_string :
			return (xdrproc_t)xdr_string;
		case WRAPPER_xdr_union :
			return (xdrproc_t)xdr_union;
		case WRAPPER_xdr_char :
			// printf("Replace wrapper to xdr_char \n");
			return (xdrproc_t)xdr_char;
		case WRAPPER_xdr_u_char :
			return (xdrproc_t)xdr_u_char;
		case WRAPPER_xdr_vector :
			return (xdrproc_t)xdr_vector;
		case WRAPPER_xdr_float :
			return (xdrproc_t)xdr_float;
		case WRAPPER_xdr_double :
			return (xdrproc_t)xdr_double;
		case WRAPPER_xdr_reference :
			return (xdrproc_t)xdr_reference;
		case WRAPPER_xdr_pointer:
			return (xdrproc_t)xdr_pointer;
		case WRAPPER_xdr_wrapstring:
			return (xdrproc_t)xdr_wrapstring;
		case WRAPPER_xdr_sizeof:
			return (xdrproc_t)xdr_sizeof;
		default:
			// printf("not a wrapper: %p \n", xpt);
			// xpt is not a wrapper
			return xpt;
	}
}

int ocall_pmap_set(unsigned long prognum, unsigned long versnum,
        unsigned int protocol, unsigned short port)
{
	return pmap_set(prognum, versnum, protocol, port);
}

int ocall_pmap_unset(unsigned long prognum, unsigned long versnum)
{
	return pmap_unset(prognum, versnum);
}

unsigned short ocall_pmap_getport(struct sockaddr_in *addr,
            unsigned long prognum, unsigned long versnum,
            unsigned int protocol)
{
	return pmap_getport(addr, prognum, versnum, protocol);
}

SVCXPRT *ocall_svcudp_create (int sock)
{
	return svcudp_create(sock);
}

void ocall_svc_run()
{
	return svc_run();
}

SVCXPRT *ocall_svctcp_create(int __sock, u_int __sendsize, u_int __recvsize)
{
	return svctcp_create(__sock, __sendsize, __recvsize);
}


// bool get_handler(int signo, unsigned long int *handler_id)
// {
//     //Retreive the job information for the corresponding job id
//     // printf("Some one call get_handler %d \n", job_id);
//     std::map<int ,  unsigned long int>::iterator it = signal_to_handler_id_info_map.find(signo);
//     if(it != signal_to_handler_id_info_map.end())
//     {
//         unsigned long int *tmp = &it->second;
//         *handler_id = *tmp;
//         return true;
//     }
//     else
//     {
//         return false;
//     }    
// }


// void sgx_generic_sig_handler(int signo)
// {
// 	unsigned long int handler_id;

// 	if (signo==SIGTERM || signo==SIGILL)	{
// 		// abort();
// 		exit(0);
// 	}

// 	if (get_handler(signo, &handler_id))	{
// 		 Invoke ecall using different thread because SGX doesn't allow nested ecall-ocall-ecall 
// 		pthread_t tid;
// 		pthread_create(&tid, NULL, call_dispatch_handler, &handler_id);
// 		/* wait for the thread to finish and then return  */
// 		(void) pthread_join(tid, NULL);
// 	}
// }

// static void
// xact_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
// {

// }


bool_t ocall_svc_register(SVCXPRT *__xprt, rpcprog_t __prog,
	    rpcvers_t __vers, __dispatch_fn_t __dispatch,
	    rpcprot_t __protocol)
{
	return svc_register(__xprt, __prog, __vers, __dispatch, __protocol);
}

bool_t ocall_svc_register_generic(SVCXPRT *__xprt, rpcprog_t __prog,
	    rpcvers_t __vers, __dispatch_fn_t __dispatch,
	    rpcprot_t __protocol)
{
	int index = dispatcher_count;
	// dispatcher_ids[index] = xact_prog_1;
	dispatcher_ids[index] = __dispatch;
	printf("Call ocall_svc_register_generic %d - %lu \n", __protocol, __dispatch);
	// bool_t ret = svc_register(__xprt, __prog, __vers, xact_prog_1, __protocol);
	bool_t ret = svc_register(__xprt, __prog, __vers, dispatcher_stubs[index], __protocol);
	printf("Return result: %d \n", ret);
	return ret;
}

CLIENT *ocall_clnt_create (const char *__host, const u_long __prog,
	    const u_long __vers, const char *__prot)
{
	clnt_create(__host, __prog, __vers, __prot);
}

void ocall_clnt_perror (CLIENT *__clnt, const char *__msg)
{
	clnt_perror(__clnt, __msg);
}

void ocall_clnt_pcreateerror (const char *__msg)
{
	clnt_pcreateerror(__msg);
}


int ocall_callrpc (const char *__host, const u_long __prognum,
    const u_long __versnum, const u_long __procnum,
    xdrproc_t __inproc, const char *__in,
    xdrproc_t __outproc, char *__out)
{
	__inproc = replace_wrapper(__inproc);
	__outproc = replace_wrapper(__outproc);

	return callrpc(__host, __prognum, __versnum, __procnum, __inproc, __in, __outproc, __out);
}

bool_t ocall_svc_sendreply (SVCXPRT *__xprt, xdrproc_t __xdr_results,
	       caddr_t __xdr_location)
{
	__xdr_results = replace_wrapper(__xdr_results);
	bool_t ret = svc_sendreply(__xprt, __xdr_results, __xdr_location);
	// printf("ocall_svc_sendreply: %p, %p, --- %d ", __xprt, __xdr_location, ret);
	return ret;
}

void ocall_svcerr_noproc(SVCXPRT *__xprt)
{
	svcerr_noproc(__xprt);
}

void ocall_svcerr_decode(SVCXPRT *__xprt)
{
	svcerr_decode(__xprt);
}

void ocall_svcerr_systemerr (SVCXPRT *__xprt)
{
	svcerr_systemerr(__xprt);
}

bool ocall_clnt_call(CLIENT *rh, unsigned long proc, xdrproc_t xargs, caddr_t argsp, 
			xdrproc_t xres, caddr_t resp, struct timeval timeout)
{
	xargs = replace_wrapper(xargs);
	xres = replace_wrapper(xres);
	return clnt_call(rh, proc, xargs, argsp, xres, resp, timeout);
}

void ocall_fast_clnt_call(unsigned long proc)
{
	printf("Call ocall_fast_clnt_call \n");
	return;
}

bool_t ocall_clnt_control(CLIENT *cl, u_int rq, char* in, int in_size)
{
	return clnt_control(cl, rq, in);
}

bool_t ocall_svc_getargs(SVCXPRT *xprt, xdrproc_t xargs, char* argsp)
{
	union {
		char rpc_xact_1_arg;
	} argument;
	xargs = replace_wrapper(xargs);
	bool_t ret = svc_getargs(xprt, (xdrproc_t)xdr_char, (char *)&argument);
	// printf("ocall_svc_getargs: %p, %p, %p - %d \n", xprt, xargs, argsp, ret);
	return ret;
}

bool_t ocall_svc_freeargs(SVCXPRT *xprt, xdrproc_t xargs, char* argsp)
{
	xargs = replace_wrapper(xargs);
	return svc_freeargs(xprt, xargs, argsp);
}