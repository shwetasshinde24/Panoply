/* Compatibility definitions for System V `poll' interface.
   Copyright (C) 1994-2014 Free Software Foundation, Inc.
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

#ifndef	_SYS_POLL_H
#define	_SYS_POLL_H	1

#include <sgx/features.h>

/* Get the platform dependent bits of `poll'.  */
#include <sgx/bits/poll.h>
#ifdef __USE_GNU
/* Get the __sigset_t definition.  */
# include <sgx/bits/sigset.h>
/* Get the timespec definition.  */
# define __need_timespec
# include <struct/sgx_time_struct.h>
#endif


/* Type used for the number of file descriptors.  */
typedef unsigned long int nfds_t;

/* Data structure describing a polling request.  */
struct pollfd
  {
    int fd;			/* File descriptor to poll.  */
    short int events;		/* Types of events poller cares about.  */
    short int revents;		/* Types of events that actually occurred.  */
  };



// /* Define some inlines helping to catch common problems.  */
// #if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
// # include <sgx/bits/poll2.h>
// #endif

#endif	/* sys/poll.h */
