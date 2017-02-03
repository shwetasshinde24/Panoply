 /* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 *	ISO C99 Standard: 7.14 Signal handling <signal.h>
 */

#ifndef	_SIGNAL_H

#if !defined __need_sig_atomic_t && !defined __need_sigset_t
# define _SIGNAL_H
#endif

#include <sgx/features.h>

#include <sgx/bits/sigset.h>		/* __sigset_t, __sig_atomic_t.  */

/* An integral type that can be modified atomically, without the
   possibility of a signal arriving in the middle of the operation.  */
#if defined __need_sig_atomic_t || defined _SIGNAL_H
# ifndef __sig_atomic_t_defined
#  define __sig_atomic_t_defined
typedef __sig_atomic_t sig_atomic_t;
# endif
# undef __need_sig_atomic_t
#endif

#if defined __need_sigset_t || (defined _SIGNAL_H && defined __USE_POSIX)
# ifndef __sigset_t_defined
#  define __sigset_t_defined
typedef __sigset_t sigset_t;
# endif
# undef __need_sigset_t
#endif

#ifdef _SIGNAL_H

#include <sgx/bits/types.h>
#include <sgx/bits/signum.h>

#if defined __USE_XOPEN || defined __USE_XOPEN2K
# ifndef __pid_t_defined
typedef __pid_t pid_t;
#  define __pid_t_defined
#endif
#ifdef __USE_XOPEN
# endif
# ifndef __uid_t_defined
typedef __uid_t uid_t;
#  define __uid_t_defined
# endif
#endif	/* Unix98 */

#ifdef __USE_POSIX199309
/* We need `struct timespec' later on.  */
# define __need_timespec
# include <struct/sgx_time_struct.h>
#endif

#if defined __USE_POSIX199309 || defined __USE_XOPEN_EXTENDED
/* Get the `siginfo_t' type plus the needed symbols.  */
# include <sgx/bits/siginfo.h>
#endif


/* Type of a signal handler.  */
typedef void (*__sighandler_t) (int);








#ifdef __USE_BSD
/* None of the following functions should be used anymore.  They are here
   only for compatibility.  A single word (`int') is not guaranteed to be
   enough to hold a complete signal mask and therefore these functions
   simply do not work in many situations.  Use `sigprocmask' instead.  */

/* Compute mask for signal SIG.  */
# define sigmask(sig)	__sigmask(sig)


#endif /* Use BSD.  */


#ifdef __USE_MISC
# define NSIG	_NSIG
#endif

#ifdef __USE_GNU
typedef __sighandler_t sighandler_t;
#endif

/* 4.4 BSD uses the name `sig_t' for this.  */
#ifdef __USE_BSD
typedef __sighandler_t sig_t;
#endif

#ifdef __USE_POSIX

/* Get the system-specific definitions of `struct sigaction'
   and the `SA_*' and `SIG_*'. constants.  */
# include <sgx/bits/sigaction.h>

#endif /* Use POSIX.  */

#ifdef __USE_BSD


/* Structure passed to `sigvec'.  */
struct sigvec
  {
    __sighandler_t sv_handler;	/* Signal handler.  */
    int sv_mask;		/* Mask of signals to be blocked.  */

    int sv_flags;		/* Flags (see below).  */
# define sv_onstack	sv_flags /* 4.2 BSD compatibility.  */
  };

/* Bits in `sv_flags'.  */
# define SV_ONSTACK	(1 << 0)/* Take the signal on the signal stack.  */
# define SV_INTERRUPT	(1 << 1)/* Do not restart system calls.  */
# define SV_RESETHAND	(1 << 2)/* Reset handler to SIG_DFL on receipt.  */





/* Get machine-dependent `struct sigcontext' and signal subcodes.  */
# include <sgx/bits/sigcontext.h>



#endif /*  use BSD.  */


#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8
# define __need_size_t
# include <stddef.h>



# include <sgx/bits/sigstack.h>
# if defined __USE_XOPEN || defined __USE_XOPEN2K8
/* This will define `ucontext_t' and `mcontext_t'.  */
#  include <sgx/sys/ucontext.h>
# endif

#endif /* use BSD or X/Open Unix.  */

#ifdef __USE_XOPEN_EXTENDED
/* Simplified interface for signal management.  */


#endif

// #if defined __USE_POSIX199506 || defined __USE_UNIX98
//  Some of the functions for handling signals in threaded programs must
//    be defined here.  
// # include <bits/pthreadtypes.h>
// # include <bits/sigthread.h>
// #endif /* use Unix98 */

/* The following functions are used internally in the C library and in
   other code which need deep insights.  */


#endif /* signal.h  */


#endif /* not signal.h */