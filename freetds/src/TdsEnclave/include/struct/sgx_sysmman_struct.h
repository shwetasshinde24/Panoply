#ifndef SGX_SYSMMAN_STRUCT_H
#define SGX_SYSMMAN_STRUCT_H

#ifndef	_SYS_MMAN_H
#define	_SYS_MMAN_H	1

#include <sgx/features.h>
#include <sgx/bits/types.h>
#define __need_size_t
#include <stddef.h>

#ifndef __off_t_defined
# ifndef __USE_FILE_OFFSET64
typedef __off_t off_t;
# else
typedef __off64_t off_t;
# endif
# define __off_t_defined
#endif

#ifndef __mode_t_defined
typedef __mode_t mode_t;
# define __mode_t_defined
#endif

#include <sgx/bits/mman.h>

/* Return value of `mmap' in case of an error.  */
#define MAP_FAILED	((void *) -1)

#endif	/* sys/mman.h */

#endif