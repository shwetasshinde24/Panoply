#ifndef SGX_STDIO_U_H__
#define SGX_STDIO_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "stdarg.h"
#include "sgx/sys/types.h"
#include "struct/sgx_stdio_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

SGX_WRAPPER_FILE SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fopen, (const char* filename, const char* mode));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fclose, (SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fputs, (const char* str, SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_feof, (SGX_WRAPPER_FILE FILESTREAM));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_rewind, (SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fflush, (SGX_WRAPPER_FILE FILESTREAM));
size_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fread, (void* ptr, size_t size, size_t nmemb, SGX_WRAPPER_FILE FILESTREAM));
size_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fwrite, (const void* ptr, size_t size, size_t count, SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_vfprintf, (SGX_WRAPPER_FILE FILESTREAM, const char* format, void* val));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_vprintf, (const char* format, void* val));
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fgets, (char* str, int num, SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getc_unlocked, (SGX_WRAPPER_FILE FILESTREAM));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_flockfile, (SGX_WRAPPER_FILE filehandle));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_funlockfile, (SGX_WRAPPER_FILE filehandle));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_vsprintf, (char* string, const char* format, void* val));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_vasprintf, (char** string, const char* format, void* val));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_ftello, (SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fseeko, (SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence));
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_ftell, (SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fseek, (SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_ferror, (SGX_WRAPPER_FILE FILESTREAM));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_perror, (const char* s));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getc, (SGX_WRAPPER_FILE FILESTREAM));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_vfscanf, (SGX_WRAPPER_FILE s, const char* format, void* val));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_vscanf, (const char* format, void* val));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_vsscanf, (const char* s, const char* format, void* val));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_putchar, (int c));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_putc, (int c, SGX_WRAPPER_FILE stream));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fputc, (int c, SGX_WRAPPER_FILE stream));
SGX_WRAPPER_FILE SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fdopen, (int fd, const char* modes));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fileno, (SGX_WRAPPER_FILE stream));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_rename, (const char* _old, const char* _new));

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_string, (const char* s));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fprint_string, (SGX_WRAPPER_FILE FILESTREAM, const char* s));

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
