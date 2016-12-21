#ifndef SGX_STDIO_T_H__
#define SGX_STDIO_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "stdarg.h"
#include "sgx/sys/types.h"
#include "struct/sgx_stdio_struct.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif



sgx_status_t SGX_CDECL ocall_fopen(SGX_WRAPPER_FILE* retval, const char* filename, const char* mode);
sgx_status_t SGX_CDECL ocall_fclose(int* retval, SGX_WRAPPER_FILE FILESTREAM);
sgx_status_t SGX_CDECL ocall_fputs(int* retval, const char* str, SGX_WRAPPER_FILE FILESTREAM);
sgx_status_t SGX_CDECL ocall_feof(int* retval, SGX_WRAPPER_FILE FILESTREAM);
sgx_status_t SGX_CDECL ocall_rewind(SGX_WRAPPER_FILE FILESTREAM);
sgx_status_t SGX_CDECL ocall_fflush(int* retval, SGX_WRAPPER_FILE FILESTREAM);
sgx_status_t SGX_CDECL ocall_fread(size_t* retval, void* ptr, size_t size, size_t nmemb, SGX_WRAPPER_FILE FILESTREAM);
sgx_status_t SGX_CDECL ocall_fwrite(size_t* retval, const void* ptr, size_t size, size_t count, SGX_WRAPPER_FILE FILESTREAM);
sgx_status_t SGX_CDECL ocall_vfprintf(int* retval, SGX_WRAPPER_FILE FILESTREAM, const char* format, void* val);
sgx_status_t SGX_CDECL ocall_vprintf(int* retval, const char* format, void* val);
sgx_status_t SGX_CDECL ocall_fgets(char** retval, char* str, int num, SGX_WRAPPER_FILE FILESTREAM);
sgx_status_t SGX_CDECL ocall_getc_unlocked(int* retval, SGX_WRAPPER_FILE FILESTREAM);
sgx_status_t SGX_CDECL ocall_flockfile(SGX_WRAPPER_FILE filehandle);
sgx_status_t SGX_CDECL ocall_funlockfile(SGX_WRAPPER_FILE filehandle);
sgx_status_t SGX_CDECL ocall_vsprintf(int* retval, char* string, const char* format, void* val);
sgx_status_t SGX_CDECL ocall_vasprintf(int* retval, char** string, const char* format, void* val);
sgx_status_t SGX_CDECL ocall_ftello(off_t* retval, SGX_WRAPPER_FILE FILESTREAM);
sgx_status_t SGX_CDECL ocall_fseeko(int* retval, SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence);
sgx_status_t SGX_CDECL ocall_ftell(off_t* retval, SGX_WRAPPER_FILE FILESTREAM);
sgx_status_t SGX_CDECL ocall_fseek(int* retval, SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence);
sgx_status_t SGX_CDECL ocall_ferror(int* retval, SGX_WRAPPER_FILE FILESTREAM);
sgx_status_t SGX_CDECL ocall_perror(const char* s);
sgx_status_t SGX_CDECL ocall_getc(int* retval, SGX_WRAPPER_FILE FILESTREAM);
sgx_status_t SGX_CDECL ocall_vfscanf(int* retval, SGX_WRAPPER_FILE s, const char* format, void* val);
sgx_status_t SGX_CDECL ocall_vscanf(int* retval, const char* format, void* val);
sgx_status_t SGX_CDECL ocall_vsscanf(int* retval, const char* s, const char* format, void* val);
sgx_status_t SGX_CDECL ocall_putchar(int* retval, int c);
sgx_status_t SGX_CDECL ocall_putc(int* retval, int c, SGX_WRAPPER_FILE stream);
sgx_status_t SGX_CDECL ocall_fputc(int* retval, int c, SGX_WRAPPER_FILE stream);
sgx_status_t SGX_CDECL ocall_fdopen(SGX_WRAPPER_FILE* retval, int fd, const char* modes);
sgx_status_t SGX_CDECL ocall_fileno(int* retval, SGX_WRAPPER_FILE stream);
sgx_status_t SGX_CDECL ocall_rename(int* retval, const char* _old, const char* _new);

sgx_status_t SGX_CDECL ocall_print_string(int* retval, const char* s);
sgx_status_t SGX_CDECL ocall_fprint_string(int* retval, SGX_WRAPPER_FILE FILESTREAM, const char* s);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
