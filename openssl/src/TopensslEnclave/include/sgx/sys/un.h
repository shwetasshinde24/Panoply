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

#ifndef	_SYS_UN_H
#define	_SYS_UN_H	1

#include <sys/cdefs.h>

/* Get the definition of the macro to define the common sockaddr members.  */
#include <sgx/bits/sockaddr.h>


/* Structure describing the address of an AF_LOCAL (aka AF_UNIX) socket.  */
struct sockaddr_un
  {
    __SOCKADDR_COMMON (sun_);
    char sun_path[108];		/* Path name.  */
  };

#endif	/* sys/un.h  */
