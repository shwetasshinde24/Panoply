#ifndef SGX_STDIO_STRUCT_H
#define SGX_STDIO_STRUCT_H 1


# define SGX_STDIN 1
# define SGX_STDOUT 2
# define SGX_STDERR 3
# define FILE_IS_NULL(FILE) FILE<=0
typedef int SGX_WRAPPER_FILE;


/* End of file character.
   Some things throughout the library rely on this being -1.  */
#ifndef EOF
# define EOF (-1)
#endif


/* The possibilities for the third argument to `fseek'.
   These values should not be changed.  */
#define SEEK_SET	0	/* Seek from beginning of file.  */
#define SEEK_CUR	1	/* Seek from current position.  */
#define SEEK_END	2	/* Seek from end of file.  */
#ifdef __USE_GNU
# define SEEK_DATA	3	/* Seek to next data.  */
# define SEEK_HOLE	4	/* Seek to next hole.  */
#endif

#endif