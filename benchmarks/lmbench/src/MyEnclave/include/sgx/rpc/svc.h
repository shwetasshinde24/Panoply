/*
 * svc.h, Server-side remote procedure call interface.
 *
 * Copyright (C) 2012-2014 Free Software Foundation, Inc.
 * This file is part of the GNU C Library.
 *
 * The GNU C Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * The GNU C Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the GNU C Library; if not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright (c) 2010, Oracle America, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name of the "Oracle America, Inc." nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *   COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 *   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _RPC_SVC_H
#define _RPC_SVC_H 1

#include <sgx/features.h>
#include <sgx/rpc/rpc_msg.h>

/*
 * This interface must manage two items concerning remote procedure calling:
 *
 * 1) An arbitrary number of transport connections upon which rpc requests
 * are received.  The two most notable transports are TCP and UDP;  they are
 * created and registered by routines in svc_tcp.c and svc_udp.c, respectively;
 * they in turn call xprt_register and xprt_unregister.
 *
 * 2) An arbitrary number of locally registered services.  Services are
 * described by the following four data: program number, version number,
 * "service dispatch" function, a transport handle, and a boolean that
 * indicates whether or not the exported program should be registered with a
 * local binder service;  if true the program's number and version and the
 * port number from the transport handle are registered with the binder.
 * These data are registered with the rpc svc system via svc_register.
 *
 * A service's dispatch function is called whenever an rpc request comes in
 * on a transport.  The request's program and version numbers must match
 * those of the registered service.  The dispatch function is passed two
 * parameters, struct svc_req * and SVCXPRT *, defined below.
 */

enum xprt_stat {
	XPRT_DIED,
	XPRT_MOREREQS,
	XPRT_IDLE
};

/*
 * Server side transport handle
 */
typedef struct SVCXPRT SVCXPRT;
struct SVCXPRT {
  int xp_sock;
  u_short xp_port;		/* associated port number */
  const struct xp_ops {
    bool_t	(*xp_recv) (SVCXPRT *__xprt, struct rpc_msg *__msg);
				/* receive incoming requests */
    enum xprt_stat (*xp_stat) (SVCXPRT *__xprt);
				/* get transport status */
    bool_t	(*xp_getargs) (SVCXPRT *__xprt, xdrproc_t __xdr_args,
			       caddr_t __args_ptr); /* get arguments */
    bool_t	(*xp_reply) (SVCXPRT *__xprt, struct rpc_msg *__msg);
				/* send reply */
    bool_t	(*xp_freeargs) (SVCXPRT *__xprt, xdrproc_t __xdr_args,
				caddr_t __args_ptr);
				/* free mem allocated for args */
    void	(*xp_destroy) (SVCXPRT *__xprt);
				/* destroy this struct */
  } *xp_ops;
  int		xp_addrlen;	 /* length of remote address */
  struct sockaddr_in xp_raddr;	 /* remote address */
  struct opaque_auth xp_verf;	 /* raw response verifier */
  caddr_t		xp_p1;		 /* private */
  caddr_t		xp_p2;		 /* private */
  char		xp_pad [256];	/* padding, internal use */
};

/*
 *  Approved way of getting address of caller
 */
#define svc_getcaller(x) (&(x)->xp_raddr)

/*
 * Operations defined on an SVCXPRT handle
 *
 * SVCXPRT		*xprt;
 * struct rpc_msg	*msg;
 * xdrproc_t		 xargs;
 * caddr_t		 argsp;
 */
// #define SVC_RECV(xprt, msg)				\
// 	(*(xprt)->xp_ops->xp_recv)((xprt), (msg))
// #define svc_recv(xprt, msg)				\
// 	(*(xprt)->xp_ops->xp_recv)((xprt), (msg))

// #define SVC_STAT(xprt)					\
// 	(*(xprt)->xp_ops->xp_stat)(xprt)
// #define svc_stat(xprt)					\
// 	(*(xprt)->xp_ops->xp_stat)(xprt)

// #define SVC_GETARGS(xprt, xargs, argsp)			\
// 	(*(xprt)->xp_ops->xp_getargs)((xprt), (xargs), (argsp))
// #define svc_getargs(xprt, xargs, argsp)			\
// 	(*(xprt)->xp_ops->xp_getargs)((xprt), (xargs), (argsp))

// #define SVC_REPLY(xprt, msg)				\
// 	(*(xprt)->xp_ops->xp_reply) ((xprt), (msg))
// #define svc_reply(xprt, msg)				\
// 	(*(xprt)->xp_ops->xp_reply) ((xprt), (msg))

// #define SVC_FREEARGS(xprt, xargs, argsp)		\
// 	(*(xprt)->xp_ops->xp_freeargs)((xprt), (xargs), (argsp))
// #define svc_freeargs(xprt, xargs, argsp)		\
// 	(*(xprt)->xp_ops->xp_freeargs)((xprt), (xargs), (argsp))

// #define SVC_DESTROY(xprt)				\
// 	(*(xprt)->xp_ops->xp_destroy)(xprt)
// #define svc_destroy(xprt)				\
// 	(*(xprt)->xp_ops->xp_destroy)(xprt)


/*
 * Service request
 */
struct svc_req {
  rpcprog_t rq_prog;            /* service program number */
  rpcvers_t rq_vers;            /* service protocol version */
  rpcproc_t rq_proc;            /* the desired procedure */
  struct opaque_auth rq_cred;   /* raw creds from the wire */
  caddr_t rq_clntcred;          /* read only cooked cred */
  SVCXPRT *rq_xprt;             /* associated transport */
};

#ifndef __DISPATCH_FN_T
#define __DISPATCH_FN_T
typedef void (*__dispatch_fn_t) (struct svc_req*, SVCXPRT*);
#endif

#define svc_fds svc_fdset.fds_bits[0]	/* compatibility */


/*
 * Socket to use on svcxxx_create call to get default socket
 */
#define	RPC_ANYSOCK	-1

/*
 * These are the existing service side transport implementations
 */


#endif /* rpc/svc.h */
