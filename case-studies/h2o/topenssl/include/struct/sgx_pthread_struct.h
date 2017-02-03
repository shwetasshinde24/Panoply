#ifndef SGX_PTHREAD_STRUCT_H
#define SGX_PTHREAD_STRUCT_H

#include <stdbool.h>

#ifndef SGX_WRAPPER_PTHREAD_ATTRIBUTE
#define SGX_WRAPPER_PTHREAD_ATTRIBUTE int 
#define PTHREAD_ATTRIBUTE_NULL -1
#endif

#ifndef __pthread_job_t
#define __pthread_job_t
typedef struct {
    void *(*start_routine) (void *);
    void *arg;
} pthread_job_t;
#endif

extern long unsigned int put_job(pthread_job_t new_job);
extern bool get_job(long unsigned int job_id, pthread_job_t *pt_job);

#ifndef _BITS_PTHREADTYPES_H
#define _BITS_PTHREADTYPES_H	1

// include bits/wordsize.h
// #include /bits/pthreadtypes.h

#ifdef __x86_64__
# if __WORDSIZE == 64
#  define __SIZEOF_PTHREAD_ATTR_T 56
#  define __SIZEOF_PTHREAD_MUTEX_T 40
#  define __SIZEOF_PTHREAD_MUTEXATTR_T 4
#  define __SIZEOF_PTHREAD_COND_T 48
#  define __SIZEOF_PTHREAD_CONDATTR_T 4
#  define __SIZEOF_PTHREAD_RWLOCK_T 56
#  define __SIZEOF_PTHREAD_RWLOCKATTR_T 8
#  define __SIZEOF_PTHREAD_BARRIER_T 32
#  define __SIZEOF_PTHREAD_BARRIERATTR_T 4
# else
#  define __SIZEOF_PTHREAD_ATTR_T 32
#  define __SIZEOF_PTHREAD_MUTEX_T 32
#  define __SIZEOF_PTHREAD_MUTEXATTR_T 4
#  define __SIZEOF_PTHREAD_COND_T 48
#  define __SIZEOF_PTHREAD_CONDATTR_T 4
#  define __SIZEOF_PTHREAD_RWLOCK_T 44
#  define __SIZEOF_PTHREAD_RWLOCKATTR_T 8
#  define __SIZEOF_PTHREAD_BARRIER_T 20
#  define __SIZEOF_PTHREAD_BARRIERATTR_T 4
# endif
#else
# define __SIZEOF_PTHREAD_ATTR_T 36
# define __SIZEOF_PTHREAD_MUTEX_T 24
# define __SIZEOF_PTHREAD_MUTEXATTR_T 4
# define __SIZEOF_PTHREAD_COND_T 48
# define __SIZEOF_PTHREAD_CONDATTR_T 4
# define __SIZEOF_PTHREAD_RWLOCK_T 32
# define __SIZEOF_PTHREAD_RWLOCKATTR_T 8
# define __SIZEOF_PTHREAD_BARRIER_T 20
# define __SIZEOF_PTHREAD_BARRIERATTR_T 4
#endif

/* Thread identifiers.  The structure of the attribute type is not
   exposed on purpose.  */
typedef unsigned long int pthread_t;
typedef unsigned int pthread_key_t;

union pthread_attr_t
{
  char __size[__SIZEOF_PTHREAD_ATTR_T];
  long int __align;
};
#ifndef __have_pthread_attr_t
typedef union pthread_attr_t pthread_attr_t;
# define __have_pthread_attr_t	1
#endif

#endif

#endif