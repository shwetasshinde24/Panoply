#ifndef SGX_STDIO_UTIL_H
#define SGX_STDIO_UTIL_H

#include "struct/sgx_stdio_struct.h"
#include "proxy/sgx_stdio_t.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C"	{
#endif 

extern int sgx_wrapper_printf(const char *fmt, ...);
extern int sgx_wrapper_printf_debug(const char *fmt, ...);
extern int sgx_wrapper_fprintf(int FILESTREAM, const char* fmt, ...);
extern int sgx_wrapper_asprintf(char **s, const char* format, ...);
extern SGX_WRAPPER_FILE sgx_wrapper_fdopen(int fd, const char* mode);
extern int sgx_wrapper_fileno(SGX_WRAPPER_FILE stream);
extern int sgx_wrapper_fclose(SGX_WRAPPER_FILE file);
extern int sgx_wrapper_fputs(const char* str, SGX_WRAPPER_FILE file);
extern char* sgx_wrapper_fgets(char* str, int num, SGX_WRAPPER_FILE FILESTREAM);
extern int sgx_wrapper_feof(SGX_WRAPPER_FILE file);
extern size_t sgx_wrapper_fread(void* ptr, size_t size, size_t nmemb, SGX_WRAPPER_FILE FILESTREAM);
extern size_t sgx_wrapper_fwrite(const void* ptr, size_t size, size_t count, SGX_WRAPPER_FILE FILESTREAM);
extern int sgx_wrapper_fseeko(SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence);
extern off_t sgx_wrapper_ftello(SGX_WRAPPER_FILE FILESTREAM);
extern int sgx_wrapper_fseek(SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence);
extern off_t sgx_wrapper_ftell(SGX_WRAPPER_FILE FILESTREAM);
extern int sgx_wrapper_ferror(SGX_WRAPPER_FILE FILESTREAM);
extern void sgx_wrapper_perror(const char* s);
extern int sgx_wrapper_fflush(SGX_WRAPPER_FILE FILESTREAM);
extern int sgx_wrapper_vfprintf(SGX_WRAPPER_FILE FILESTREAM, const char* format, void* val);
extern int sgx_wrapper_vprintf(const char* format, void* val);
extern int sgx_wrapper_vsprintf(char* string, const char* format, void* val);
extern int sgx_wrapper_vasprintf(char** string, const char* format, void* val);
extern int sgx_wrapper_getc(SGX_WRAPPER_FILE FILESTREAM);
extern int sgx_wrapper_getchar();
extern int sgx_wrapper_vfscanf(SGX_WRAPPER_FILE FILESTREAM, const char *format, void* ap);
extern int sgx_wrapper_vscanf(const char *format, void* ap);
extern int sgx_wrapper_vsscanf(const char* s, const char *format, void* ap);
extern int sgx_wrapper_putchar(int c);
extern int sgx_wrapper_putc(int c, SGX_WRAPPER_FILE FILESTREAM);
extern int sgx_wrapper_fputc(int c, SGX_WRAPPER_FILE FILESTREAM);
extern int sgx_wrapper_fscanf(SGX_WRAPPER_FILE FILESTREAM, const char* format, ...);
extern int sgx_wrapper_rename(const char* _old, const char* _new);
extern SGX_WRAPPER_FILE sgx_wrapper_fopen(const char* filename, const char* mode);	

#define USE_INNER_SSCANF
#ifdef USE_INNER_SSCANF

#include <ctype.h>
#include <limits.h>
#include <assert.h>

#define HIDDEN_MAX_SCANF_WIDTH 9999
#define HIDDEN_TOR_ISDIGIT(A) isdigit(A)
#define HIDDEN_TOR_ISXDIGIT(A) isxdigit(A)
#define HIDDEN_TOR_ISSPACE(A) isspace(A)
#define hidden_tor_assert(A) assert(A)

extern int
hidden_hex_decode_digit(char c);


/** Helper: given an ASCII-encoded decimal digit, return its numeric value.
 * NOTE: requires that its input be in-bounds. */
extern int
hidden_digit_to_num(char d);


/** Helper: Read an unsigned int from *<b>bufp</b> of up to <b>width</b>
 * characters.  (Handle arbitrary width if <b>width</b> is less than 0.)  On
 * success, store the result in <b>out</b>, advance bufp to the next
 * character, and return 0.  On failure, return -1. */
extern int
hidden_scan_unsigned(const char **bufp, unsigned long *out, int width, int base);


/** Helper: Read an signed int from *<b>bufp</b> of up to <b>width</b>
 * characters.  (Handle arbitrary width if <b>width</b> is less than 0.)  On
 * success, store the result in <b>out</b>, advance bufp to the next
 * character, and return 0.  On failure, return -1. */
extern int
hidden_scan_signed(const char **bufp, long *out, int width);


/** Helper: Read a decimal-formatted double from *<b>bufp</b> of up to
 * <b>width</b> characters.  (Handle arbitrary width if <b>width</b> is less
 * than 0.)  On success, store the result in <b>out</b>, advance bufp to the
 * next character, and return 0.  On failure, return -1. */
extern int
hidden_scan_double(const char **bufp, double *out, int width);


/** Helper: copy up to <b>width</b> non-space characters from <b>bufp</b> to
 * <b>out</b>.  Make sure <b>out</b> is nul-terminated. Advance <b>bufp</b>
 * to the next non-space character or the EOS. */
extern int
hidden_scan_string(const char **bufp, char *out, int width);

/** Locale-independent, minimal, no-surprises scanf variant, accepting only a
 * restricted pattern format.  For more info on what it supports, see
 * tor_sscanf() documentation.  */
extern int
hidden_tor_vsscanf(const char *buf, const char *pattern, va_list ap);


/** Minimal sscanf replacement: parse <b>buf</b> according to <b>pattern</b>
 * and store the results in the corresponding argument fields.  Differs from
 * sscanf in that:
 * <ul><li>It only handles %u, %lu, %x, %lx, %[NUM]s, %d, %ld, %lf, and %c.
 *     <li>It only handles decimal inputs for %lf. (12.3, not 1.23e1)
 *     <li>It does not handle arbitrarily long widths.
 *     <li>Numbers do not consume any space characters.
 *     <li>It is locale-independent.
 *     <li>%u and %x do not consume any space.
 *     <li>It returns -1 on malformed patterns.</ul>
 *
 * (As with other locale-independent functions, we need this to parse data that
 * is in ASCII without worrying that the C library's locale-handling will make
 * miscellaneous characters look like numbers, spaces, and so on.)
 */
extern int
hidden_tor_sscanf(const char *buf, const char *pattern, ...);


#define sscanf(A, B, ...) hidden_tor_sscanf(A, B, ##__VA_ARGS__)
#define vsscanf(A, B, C) hidden_tor_vsscanf(A, B, C)

#endif

#ifdef __cplusplus
}
#endif

#define stdin SGX_STDIN
#define stdout SGX_STDOUT 
#define stderr SGX_STDERR

#define printf(A, ...) sgx_wrapper_printf(A, ##__VA_ARGS__)
#define debug(A, ...) sgx_wrapper_printf_debug(A, ##__VA_ARGS__)
#define fprintf(A, B, ...) sgx_wrapper_fprintf(A, B, ##__VA_ARGS__)
#define asprintf(A, B, ...) sgx_wrapper_asprintf(A, B, ##__VA_ARGS__)
#define funlockfile(A) sgx_wrapper_funlockfile(A)
#define flockfile(A) sgx_wrapper_flockfile(A)
#define rewind(A) sgx_wrapper_rewind(A)
#define sgx_wrapper_rewind(A) ocall_rewind(A)
#define fopen(A, B) sgx_wrapper_fopen(A, B)
#define fdopen(A, B) sgx_wrapper_fdopen(A, B)
#define fileno(A) sgx_wrapper_fileno(A)
#define fclose(A) sgx_wrapper_fclose(A)
#define fputs(A, B) sgx_wrapper_fputs(A, B)
#define fgets(A, B, C) sgx_wrapper_fgets(A, B, C)	
#define feof(A) sgx_wrapper_feof(A)
#define fread(A, B, C, D) sgx_wrapper_fread(A, B, C, D)
#define fwrite(A, B, C, D) sgx_wrapper_fwrite(A, B, C, D)
#define fseeko(A, B, C) sgx_wrapper_fseeko(A, B, C)
#define ftello(A) sgx_wrapper_ftello(A)
#define fseek(A, B, C) sgx_wrapper_fseek(A, B, C)
#define ftell(A) sgx_wrapper_ftell(A)
#define ferror(A) sgx_wrapper_ferror(A)
#define perror(A) sgx_wrapper_perror(A)
#define fflush(A) sgx_wrapper_fflush(A)
#define getc(A) sgx_wrapper_getc(A)
#define getchar() sgx_wrapper_getchar()
#define putchar(A) sgx_wrapper_putchar(A)
#define putc(A, B) sgx_wrapper_putc(A, B)
#define fputc(A, B) sgx_wrapper_fputc(A, B)
#define rename(A, B) sgx_wrapper_rename(A, B)

#endif