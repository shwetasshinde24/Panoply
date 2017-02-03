/* Copyright (C) 1992-2014 Free Software Foundation, Inc.
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

#ifndef	_SYS_RESOURCE_H
#define	_SYS_RESOURCE_H	1

#include <sgx/features.h>

/* Get the system-dependent definitions of structures and bit values.  */
#include <sgx/bits/resource.h>

#ifndef __id_t_defined
typedef __id_t id_t;
# define __id_t_defined
#endif

/* The X/Open standard defines that all the functions below must use
   `int' as the type for the first argument.  When we are compiling with
   GNU extensions we change this slightly to provide better error
   checking.  */
#if defined __USE_GNU && !defined __cplusplus
typedef enum __rlimit_resource __rlimit_resource_t;
typedef enum __rusage_who __rusage_who_t;
typedef enum __priority_which __priority_which_t;
#else
typedef int __rlimit_resource_t;
typedef int __rusage_who_t;
typedef int __priority_which_t;
#endif

#endif	/* sys/resource.h  */
