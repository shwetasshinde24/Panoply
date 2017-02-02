#ifndef SGX_FCNTL_STRUCT_H
#define SGX_FCNTL_STRUCT_H

#ifndef	_FCNTL_H
#define	_FCNTL_H	1

#include <sgx/features.h>

/* This must be early so <bits/fcntl.h> can define types winningly.  */

/* Get __mode_t, __dev_t and __off_t  .*/
#include <sgx/bits/types.h>

/* Get the definitions of O_*, F_*, FD_*: all the
   numbers and flag bits for `open', `fcntl', et al.  */

/* POSIX.1-2001 specifies that these types are defined by <fcntl.h>.
   Earlier POSIX standards permitted any type ending in `_t' to be defined
   by any POSIX header, so we don't conditionalize the definitions here.  */
#ifndef __mode_t_defined
typedef __mode_t mode_t;
# define __mode_t_defined
#endif

#ifndef __off_t_defined
# ifndef __USE_FILE_OFFSET64
typedef __off_t off_t;
# else
typedef __off64_t off_t;
# endif
# define __off_t_defined
#endif

#if defined __USE_LARGEFILE64 && !defined __off64_t_defined
typedef __off64_t off64_t;
# define __off64_t_defined
#endif

#ifndef __pid_t_defined
typedef __pid_t pid_t;
# define __pid_t_defined
#endif

// #include <bits/fcntl.h>

#ifdef __x86_64__
# define __O_LARGEFILE	0
#endif

#ifdef __x86_64__
/* Not necessary, we always have 64-bit offsets.  */
# define F_GETLK64	5	/* Get record locking info.  */
# define F_SETLK64	6	/* Set record locking info (non-blocking).  */
# define F_SETLKW64	7	/* Set record locking info (blocking).	*/
#endif

// #ifdef __USE_GNU
// # include <sgx/bits/uio.h>
// #endif

/* open/fcntl.  */
#define O_ACCMODE	   0003
#define O_RDONLY	     00
#define O_WRONLY	     01
#define O_RDWR		     02
#ifndef O_CREAT
# define O_CREAT	   0100	/* Not fcntl.  */
#endif
#ifndef O_EXCL
# define O_EXCL		   0200	/* Not fcntl.  */
#endif
#ifndef O_NOCTTY
# define O_NOCTTY	   0400	/* Not fcntl.  */
#endif
#ifndef O_TRUNC
# define O_TRUNC	  01000	/* Not fcntl.  */
#endif
#ifndef O_APPEND
# define O_APPEND	  02000
#endif
#ifndef O_NONBLOCK
# define O_NONBLOCK	  04000
#endif
#ifndef O_NDELAY
# define O_NDELAY	O_NONBLOCK
#endif
#ifndef O_SYNC
# define O_SYNC	       04010000
#endif
#define O_FSYNC		O_SYNC
#ifndef O_ASYNC
# define O_ASYNC	 020000
#endif
#ifndef __O_LARGEFILE
# define __O_LARGEFILE	0100000
#endif

#ifndef __O_DIRECTORY
# define __O_DIRECTORY  0200000
#endif
#ifndef __O_NOFOLLOW
# define __O_NOFOLLOW	0400000
#endif
#ifndef __O_CLOEXEC
# define __O_CLOEXEC   02000000
#endif
#ifndef __O_DIRECT
# define __O_DIRECT	 040000
#endif
#ifndef __O_NOATIME
# define __O_NOATIME   01000000
#endif
#ifndef __O_PATH
# define __O_PATH     010000000
#endif
#ifndef __O_DSYNC
# define __O_DSYNC	 010000
#endif
#ifndef __O_TMPFILE
# define __O_TMPFILE   020200000
#endif

#ifndef F_GETLK
# ifndef __USE_FILE_OFFSET64
#  define F_GETLK	5	/* Get record locking info.  */
#  define F_SETLK	6	/* Set record locking info (non-blocking).  */
#  define F_SETLKW	7	/* Set record locking info (blocking).	*/
# else
#  define F_GETLK	F_GETLK64  /* Get record locking info.	*/
#  define F_SETLK	F_SETLK64  /* Set record locking info (non-blocking).*/
#  define F_SETLKW	F_SETLKW64 /* Set record locking info (blocking).  */
# endif
#endif
#ifndef F_GETLK64
# define F_GETLK64	12	/* Get record locking info.  */
# define F_SETLK64	13	/* Set record locking info (non-blocking).  */
# define F_SETLKW64	14	/* Set record locking info (blocking).	*/
#endif

#ifdef __USE_LARGEFILE64
# define O_LARGEFILE __O_LARGEFILE
#endif

#ifdef __USE_XOPEN2K8
# define O_DIRECTORY	__O_DIRECTORY	/* Must be a directory.	 */
# define O_NOFOLLOW	__O_NOFOLLOW	/* Do not follow links.	 */
# define O_CLOEXEC	__O_CLOEXEC	/* Set close_on_exec.  */
#endif

#ifdef __USE_GNU
# define O_DIRECT	__O_DIRECT	/* Direct disk access.	*/
# define O_NOATIME	__O_NOATIME	/* Do not set atime.  */
# define O_PATH		__O_PATH	/* Resolve pathname but do not open file.  */
# define O_TMPFILE	__O_TMPFILE	/* Atomically create nameless file.  */
#endif

/* For now, Linux has no separate synchronicitiy options for read
   operations.  We define O_RSYNC therefore as the same as O_SYNC
   since this is a superset.  */
#if defined __USE_POSIX199309 || defined __USE_UNIX98
# define O_DSYNC	__O_DSYNC	/* Synchronize data.  */
# if defined __O_RSYNC
#  define O_RSYNC	__O_RSYNC	/* Synchronize read operations.	 */
# else
#  define O_RSYNC	O_SYNC		/* Synchronize read operations.	 */
# endif
#endif

/* Values for the second argument to `fcntl'.  */
#define F_DUPFD		0	/* Duplicate file descriptor.  */
#define F_GETFD		1	/* Get file descriptor flags.  */
#define F_SETFD		2	/* Set file descriptor flags.  */
#define F_GETFL		3	/* Get file status flags.  */
#define F_SETFL		4	/* Set file status flags.  */

#ifndef __F_SETOWN
# define __F_SETOWN	8
# define __F_GETOWN	9
#endif

#if defined __USE_BSD || defined __USE_UNIX98 || defined __USE_XOPEN2K8
# define F_SETOWN	__F_SETOWN /* Get owner (process receiving SIGIO).  */
# define F_GETOWN	__F_GETOWN /* Set owner (process receiving SIGIO).  */
#endif

#ifndef __F_SETSIG
# define __F_SETSIG	10	/* Set number of signal to be sent.  */
# define __F_GETSIG	11	/* Get number of signal to be sent.  */
#endif
#ifndef __F_SETOWN_EX
# define __F_SETOWN_EX	15	/* Get owner (thread receiving SIGIO).  */
# define __F_GETOWN_EX	16	/* Set owner (thread receiving SIGIO).  */
#endif

#ifdef __USE_GNU
# define F_SETSIG	__F_SETSIG	/* Set number of signal to be sent.  */
# define F_GETSIG	__F_GETSIG	/* Get number of signal to be sent.  */
# define F_SETOWN_EX	__F_SETOWN_EX	/* Get owner (thread receiving SIGIO).  */
# define F_GETOWN_EX	__F_GETOWN_EX	/* Set owner (thread receiving SIGIO).  */
#endif

#ifdef __USE_GNU
# define F_SETLEASE	1024	/* Set a lease.	 */
# define F_GETLEASE	1025	/* Enquire what lease is active.  */
# define F_NOTIFY	1026	/* Request notifications on a directory.  */
# define F_SETPIPE_SZ	1031	/* Set pipe page size array.  */
# define F_GETPIPE_SZ	1032	/* Set pipe page size array.  */
#endif
#ifdef __USE_XOPEN2K8
# define F_DUPFD_CLOEXEC 1030	/* Duplicate file descriptor with
				   close-on-exit set.  */
#endif

/* For F_[GET|SET]FD.  */
#define FD_CLOEXEC	1	/* Actually anything with low bit set goes */

#ifndef F_RDLCK
/* For posix fcntl() and `l_type' field of a `struct flock' for lockf().  */
# define F_RDLCK		0	/* Read lock.  */
# define F_WRLCK		1	/* Write lock.	*/
# define F_UNLCK		2	/* Remove lock.	 */
#endif


/* For old implementation of BSD flock.  */
#ifndef F_EXLCK
# define F_EXLCK		4	/* or 3 */
# define F_SHLCK		8	/* or 4 */
#endif

#ifdef __USE_BSD
/* Operations for BSD flock, also used by the kernel implementation.  */
# define LOCK_SH	1	/* Shared lock.  */
# define LOCK_EX	2	/* Exclusive lock.  */
# define LOCK_NB	4	/* Or'd with one of the above to prevent
				   blocking.  */
# define LOCK_UN	8	/* Remove lock.  */
#endif

#ifdef __USE_GNU
# define LOCK_MAND	32	/* This is a mandatory flock:	*/
# define LOCK_READ	64	/* ... which allows concurrent read operations.	 */
# define LOCK_WRITE	128	/* ... which allows concurrent write operations.  */
# define LOCK_RW	192	/* ... Which allows concurrent read & write operations.	 */
#endif

#ifdef __USE_GNU
/* Types of directory notifications that may be requested with F_NOTIFY.  */
# define DN_ACCESS	0x00000001	/* File accessed.  */
# define DN_MODIFY	0x00000002	/* File modified.  */
# define DN_CREATE	0x00000004	/* File created.  */
# define DN_DELETE	0x00000008	/* File removed.  */
# define DN_RENAME	0x00000010	/* File renamed.  */
# define DN_ATTRIB	0x00000020	/* File changed attributes.  */
# define DN_MULTISHOT	0x80000000	/* Don't remove notifier.  */
#endif


/* Define some more compatibility macros to be backward compatible with
   BSD systems which did not managed to hide these kernel macros.  */
#ifdef	__USE_BSD
# define FAPPEND	O_APPEND
# define FFSYNC		O_FSYNC
# define FASYNC		O_ASYNC
# define FNONBLOCK	O_NONBLOCK
# define FNDELAY	O_NDELAY
#endif /* Use BSD.  */

#ifndef __POSIX_FADV_DONTNEED
#  define __POSIX_FADV_DONTNEED	4
#  define __POSIX_FADV_NOREUSE	5
#endif
/* Advise to `posix_fadvise'.  */
#ifdef __USE_XOPEN2K
# define POSIX_FADV_NORMAL	0 /* No further special treatment.  */
# define POSIX_FADV_RANDOM	1 /* Expect random page references.  */
# define POSIX_FADV_SEQUENTIAL	2 /* Expect sequential page references.	 */
# define POSIX_FADV_WILLNEED	3 /* Will need these pages.  */
# define POSIX_FADV_DONTNEED	__POSIX_FADV_DONTNEED /* Don't need these pages.  */
# define POSIX_FADV_NOREUSE	__POSIX_FADV_NOREUSE /* Data will be accessed once.  */
#endif


#ifdef __USE_GNU
/* Flags for SYNC_FILE_RANGE.  */
# define SYNC_FILE_RANGE_WAIT_BEFORE	1 /* Wait upon writeout of all pages
					     in the range before performing the
					     write.  */
# define SYNC_FILE_RANGE_WRITE		2 /* Initiate writeout of all those
					     dirty pages in the range which are
					     not presently under writeback.  */
# define SYNC_FILE_RANGE_WAIT_AFTER	4 /* Wait upon writeout of all pages in
					     the range after performing the
					     write.  */

/* Flags for SPLICE and VMSPLICE.  */
# define SPLICE_F_MOVE		1	/* Move pages instead of copying.  */
# define SPLICE_F_NONBLOCK	2	/* Don't block on the pipe splicing
					   (but we may still block on the fd
					   we splice from/to).  */
# define SPLICE_F_MORE		4	/* Expect more data.  */
# define SPLICE_F_GIFT		8	/* Pages passed in are a gift.  */


/* Flags for fallocate.  */
# define FALLOC_FL_KEEP_SIZE		1 /* Don't extend size of file
					     even if offset + len is
					     greater than file size.  */
# define FALLOC_FL_PUNCH_HOLE		2 /* Create a hole in the file.  */


/* Maximum handle size (for now).  */
# define MAX_HANDLE_SZ	128
#endif

/* Values for `*at' functions.  */
#ifdef __USE_ATFILE
# define AT_FDCWD		-100	/* Special value used to indicate
					   the *at functions should use the
					   current working directory. */
# define AT_SYMLINK_NOFOLLOW	0x100	/* Do not follow symbolic links.  */
# define AT_REMOVEDIR		0x200	/* Remove directory instead of
					   unlinking file.  */
# define AT_SYMLINK_FOLLOW	0x400	/* Follow symbolic links.  */
# ifdef __USE_GNU
#  define AT_NO_AUTOMOUNT	0x800	/* Suppress terminal automount
					   traversal.  */
#  define AT_EMPTY_PATH		0x1000	/* Allow empty relative pathname.  */
# endif
# define AT_EACCESS		0x200	/* Test access permitted for
					   effective IDs, not real IDs.  */
#endif

struct flock
  {
    short int l_type;	/* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK.	*/
    short int l_whence;	/* Where `l_start' is relative to (like `lseek').  */
#ifndef __USE_FILE_OFFSET64
    __off_t l_start;	/* Offset where the lock begins.  */
    __off_t l_len;	/* Size of the locked area; zero means until EOF.  */
#else
    __off64_t l_start;	/* Offset where the lock begins.  */
    __off64_t l_len;	/* Size of the locked area; zero means until EOF.  */
#endif
    __pid_t l_pid;	/* Process holding the lock.  */
  };

#ifdef __USE_LARGEFILE64
struct flock64
  {
    short int l_type;	/* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK.	*/
    short int l_whence;	/* Where `l_start' is relative to (like `lseek').  */
    __off64_t l_start;	/* Offset where the lock begins.  */
    __off64_t l_len;	/* Size of the locked area; zero means until EOF.  */
    __pid_t l_pid;	/* Process holding the lock.  */
  };
#endif

///////////////////////////////////////


#endif

#endif