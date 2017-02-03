/* FreeTDS - Library of routines accessing Sybase and Microsoft databases
 *
 * Copyright (C) 2005 Liam Widdowson
 * Copyright (C) 2010-2012 Frediano Ziglio
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef TDSTHREAD_ENCLAVE_H
#define TDSTHREAD_ENCLAVE_H 1

#undef TDS_HAVE_MUTEX

	#include <freetds/pushvis.h>
	#include <sgx_thread.h>
 	#include <sgx/sys/types.h>
	#define TDS_HAVE_MUTEX 1

 	// #ifndef pid_t
 	// #define pid_t sgx_thread_t
 	// #endif
	// typedef sgx_thread_t pid_t;

	typedef sgx_thread_mutex_t tds_raw_mutex;

	typedef tds_raw_mutex tds_mutex;

	#define TDS_RAW_MUTEX_INITIALIZER SGX_THREAD_MUTEX_INITIALIZER
	#define TDS_MUTEX_INITIALIZER TDS_RAW_MUTEX_INITIALIZER

	static inline void tds_raw_mutex_lock(tds_raw_mutex *mtx)
	{
		// sgx_thread_mutex_lock(mtx);
	}

	static inline int tds_raw_mutex_trylock(tds_raw_mutex *mtx)
	{
		// return sgx_thread_mutex_trylock(mtx);
	}

	static inline void tds_raw_mutex_unlock(tds_raw_mutex *mtx)
	{
		// sgx_thread_mutex_unlock(mtx);
	}

	static inline int tds_raw_mutex_init(tds_raw_mutex *mtx)
	{
		// return sgx_thread_mutex_init(mtx, NULL);
	}

	static inline void tds_raw_mutex_free(tds_raw_mutex *mtx)
	{
		// sgx_thread_mutex_destroy(mtx);
	}

	typedef sgx_thread_cond_t tds_condition;
	int tds_raw_cond_init(tds_condition *cond);
	

	static inline int tds_raw_cond_destroy(tds_condition *cond)
	{
		// return sgx_thread_cond_destroy(cond);
	}
	static inline int tds_raw_cond_signal(tds_condition *cond)
	{
		// return sgx_thread_cond_signal(cond);
	}
	static inline int tds_raw_cond_wait(tds_condition *cond, tds_raw_mutex *mtx)
	{
		// return sgx_thread_cond_wait(cond, mtx);
	}

	typedef struct {
	} tds_thread;
	typedef int tds_thread_id;

	#ifdef TDS_HAVE_MUTEX
	#  define tds_cond_init tds_raw_cond_init
	#  define tds_cond_destroy tds_raw_cond_destroy
	#  define tds_cond_signal tds_raw_cond_signal
	#  if !ENABLE_EXTRA_CHECKS
	#    define TDS_MUTEX_INITIALIZER TDS_RAW_MUTEX_INITIALIZER
	#    define tds_mutex tds_raw_mutex
	#    define tds_mutex_lock tds_raw_mutex_lock
	#    define tds_mutex_trylock tds_raw_mutex_trylock
	#    define tds_mutex_unlock tds_raw_mutex_unlock
	#    define tds_mutex_check_owned(mtx) do {} while(0)
	#    define tds_mutex_init tds_raw_mutex_init
	#    define tds_mutex_free tds_raw_mutex_free
	#    define tds_cond_wait tds_raw_cond_wait
	#    define tds_cond_timedwait tds_raw_cond_timedwait
	#  else
	#    include <assert.h>
	#  endif
	#endif

typedef void *(*tds_thread_proc)(void *arg);
#define TDS_THREAD_PROC_DECLARE(name, arg) \
	void *name(void *arg)

#define tds_thread_create(ret, proc, arg) \
	FreeTDS_Thread_not_compiled

#define tds_thread_create_detached(proc, arg) \
	FreeTDS_Thread_not_compiled

#define tds_thread_join(th, ret) \
	FreeTDS_Thread_not_compiled

static inline tds_thread_id tds_thread_get_current_id(void)
{
	return sgx_thread_self();
}

static inline int tds_thread_is_current(tds_thread_id th)
{
	return 1;
}

#include <freetds/popvis.h>

#endif

