/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#ifndef SGX_RPC_UTIL_H
#define SGX_RPC_UTIL_H

#include <sgx/rpc/svc.h>

/* Type of a signal handler.  */
// typedef void (*__rpchandler_t) (struct svc_req *, register SVCXPRT *);

// Define wrapper generic routine 
#define xdr_void 1
#define xdr_short 2
#define xdr_u_short 3
#define xdr_int 4
#define xdr_u_int 5
#define xdr_long 6
#define xdr_u_long 7
#define xdr_hyper 8
#define xdr_u_hyper 9
#define xdr_longlong_t 10
#define xdr_u_longlong_t 11
#define xdr_int8_t 12
#define xdr_uint8_t 13
#define xdr_int16_t 14
#define xdr_uint16_t 15
#define xdr_int32_t 16
#define xdr_uint32_t 17
#define xdr_int64_t 18
#define xdr_uint64_t 19
#define xdr_quad_t 20
#define xdr_u_quad_t 21
#define xdr_bool 22
#define xdr_enum 23
#define xdr_array 24
#define xdr_bytes 25
#define xdr_opaque 26
#define xdr_string 27
#define xdr_union 28
#define xdr_char 29
#define xdr_u_char 30
#define xdr_vector 31
#define xdr_float 32
#define xdr_double 33
#define xdr_reference 34 
#define xdr_pointer 35
#define xdr_wrapstring 36 
#define xdr_sizeof 37

#ifdef __cplusplus
extern "C"	{
#endif

extern int sgx_wrapper_pmap_set(unsigned long prognum, unsigned long versnum,
        unsigned int protocol, unsigned short port);
extern int sgx_wrapper_pmap_unset(unsigned long prognum, unsigned long versnum);
extern unsigned short sgx_wrapper_pmap_getport(struct sockaddr_in *addr,
            unsigned long prognum, unsigned long versnum,
            unsigned int protocol);
extern SVCXPRT *sgx_wrapper_svcudp_create (int sock);
extern void sgx_wrapper_svc_run();
extern SVCXPRT *sgx_wrapper_svctcp_create(int __sock, u_int __sendsize, u_int __recvsize);
extern bool_t sgx_wrapper_svc_register(SVCXPRT *__xprt, rpcprog_t __prog,
	    rpcvers_t __vers, __dispatch_fn_t __dispatch,
	    rpcprot_t __protocol);

extern CLIENT *sgx_wrapper_clnt_create (const char *__host, const u_long __prog,
	    const u_long __vers, const char *__prot);
extern void sgx_wrapper_clnt_perror (CLIENT *__clnt, const char *__msg);
extern void sgx_wrapper_clnt_pcreateerror (const char *__msg);
extern int sgx_wrapper_callrpc (const char *__host, const u_long __prognum,
    const u_long __versnum, const u_long __procnum,
    const xdrproc_t __inproc, const char *__in,
    const xdrproc_t __outproc, char *__out);

extern bool_t sgx_wrapper_svc_sendreply (SVCXPRT *__xprt, xdrproc_t __xdr_results,
	       caddr_t __xdr_location);
extern void sgx_wrapper_svcerr_noproc(SVCXPRT *__xprt);
extern void sgx_wrapper_svcerr_decode(SVCXPRT *__xprt);
extern void sgx_wrapper_svcerr_systemerr (SVCXPRT *__xprt);
extern bool sgx_wrapper_clnt_call(CLIENT *rh, unsigned long proc, xdrproc_t xargs, caddr_t argsp, 
			xdrproc_t xres, caddr_t resp, struct timeval timeout);

// Adding info buffersize
extern bool_t sgx_wrapper_clnt_control(CLIENT *cl, u_int rq, char* in, int in_size);
extern bool_t sgx_wrapper_svc_getargs(SVCXPRT *xprt, xdrproc_t xargs, char* argsp);
extern bool_t sgx_wrapper_svc_freeargs(SVCXPRT *xprt, xdrproc_t xargs, char* argsp);

#ifdef __cplusplus
}
#endif 

#define pmap_set(A, B, C, D) sgx_wrapper_pmap_set(A, B, C, D)
#define pmap_unset(A, B) sgx_wrapper_pmap_unset(A, B)
#define pmap_getport(A, B, C, D) sgx_wrapper_pmap_getport(A, B, C, D)
#define svcudp_create(A) sgx_wrapper_svcudp_create(A)
#define svc_run() sgx_wrapper_svc_run()
#define svctcp_create(A, B, C) sgx_wrapper_svctcp_create(A, B, C)
#define svc_register(A, B, C, D, E) sgx_wrapper_svc_register(A, B, C, D, E)
#define clnt_create(A, B, C, D) sgx_wrapper_clnt_create(A, B, C, D)
#define clnt_perror(A, B) sgx_wrapper_clnt_perror(A, B)
#define clnt_pcreateerror(A) sgx_wrapper_clnt_pcreateerror(A)
#define callrpc(A, B, C, D, E, F, G, H) sgx_wrapper_callrpc(A, B, C, D, E, F, G, H)
#define svc_sendreply(A, B, C) sgx_wrapper_svc_sendreply(A, B, C)
#define svcerr_noproc(A) sgx_wrapper_svcerr_noproc(A)
#define svcerr_decode(A) sgx_wrapper_svcerr_decode(A)
#define svcerr_systemerr(A) sgx_wrapper_svcerr_systemerr(A)
#define clnt_call(A, B, C, D, E, F, G) sgx_wrapper_clnt_call(A, B, C, D, E, F, G)
#define clnt_control(A, B, C, D) sgx_wrapper_clnt_control(A, B, C, D)
#define svc_getargs(A, B, C) sgx_wrapper_svc_getargs(A, B, C)
#define svc_freeargs(A, B, C) sgx_wrapper_svc_freeargs(A, B, C)

#endif 
