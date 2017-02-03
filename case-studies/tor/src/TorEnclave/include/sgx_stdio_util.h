#ifndef SGX_STDIO_UTIL_H
#define SGX_STDIO_UTIL_H

#include "struct/sgx_stdio_struct.h"
#include "proxy/sgx_stdio_t.h"
#include <stdio.h>
#include <string.h>

#define WRAPBUFSIZ 15000

static inline int sgx_wrapper_printf(const char *fmt, ...)
{
    return 1;
    char buf[WRAPBUFSIZ] = {'\0'};
    int result;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, WRAPBUFSIZ, fmt, ap);
    va_end(ap);
    ocall_print_string(&result, buf);
    // printf("Return to wrapper \n ");
    return result;
}

static inline int sgx_wrapper_fprintf(int FILESTREAM, const char* fmt, ...)	
{
    char buf[WRAPBUFSIZ] = {'\0'};
    int result = 0;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, WRAPBUFSIZ, fmt, ap);
    va_end(ap);
    ocall_fprint_string(&result, FILESTREAM, buf);
    return result;
}

// Fix me: Proposed wrapper of asprintf
static inline int sgx_wrapper_asprintf(char **s, const char* format, ...)
{
	char buf[WRAPBUFSIZ] = {'\0'};
	int res = 0;
    va_list ap;
    va_start(ap, format);
    res += vsnprintf(buf, WRAPBUFSIZ, format, ap);
    va_end(ap);	
	*s = (char*)malloc(strlen(buf)+1);
	strncpy(*s,buf,strlen(buf)+1);
	return res;
} 

// Fix me: Every sprintf shoud change to snprintf due to context
// static inline int sgx_wrapper_sprintf(char* string, const char* fmt, ...)	
// {
//     // char buf[BUFSIZ] = {'\0'};
//     int size = sizeof(string);
//     // sgx_wrapper_printf("Call sprintf with string size: %d", size);
//     int result;
//     va_list ap;
//     va_start(ap, fmt);
//     int ret = 0;
//     ret = vsnprintf(string, size, fmt, ap);
//     result += ret;
//     va_end(ap);
//     // ocall_fprint_string(&result, buf);
//     return result;
// }


// static inline int sgx_wrapper_printf(const char* format, ...)	
// {
// 	int result = 0;
// 	va_list ap;
// 	va_start(ap, format);
// 	int ret;
// 	result += ret;
//     ocall_vprintf(&ret, format, &ap);
//     va_end(ap);
//     return result;
// }

// static inline int sgx_wrapper_fprintf(int FILESTREAM, const char* format, ...)	
// {
// 	sgx_wrapper_printf("sgx_wrapper_fprintf \n");
// 	int result = 0;
// 	va_list ap;
// 	va_start(ap, format);
// 	int ret;
//     ocall_vfprintf(&ret, FILESTREAM, format, &ap);
//     result += ret;
//     va_end(ap);
//     sgx_wrapper_printf("sgx_wrapper_fprintf \n");
//     return result;
// }

// static inline int sgx_wrapper_sprintf(char* string, const char* format, ...)	
// {
// 	sgx_wrapper_printf("sgx_wrapper_sprintf \n");
// 	int result = 0;
// 	va_list ap;
// 	va_start(ap, format);
// 	int ret;
//     ocall_vsprintf(&ret, string, format, &ap);
//     result += ret;
//     va_end(ap);
//     sgx_wrapper_printf("sgx_wrapper_sprintf \n");
//     return result;
// }

static inline SGX_WRAPPER_FILE sgx_wrapper_fdopen(int fd, const char* mode)	
{
	SGX_WRAPPER_FILE f = 0;
	ocall_fdopen(&f, fd, mode);
	return f;
}

static inline int sgx_wrapper_fileno(SGX_WRAPPER_FILE stream)
{
    int retval;
    ocall_fileno(&retval, stream);    
    return retval;
}

static inline int sgx_wrapper_fclose(SGX_WRAPPER_FILE file)	
{
	int ret = 0;
	ocall_fclose(&ret, file);
	return ret;
}
static inline int sgx_wrapper_fputs(const char* str, SGX_WRAPPER_FILE file)	
{
	int ret = 0;
	ocall_fputs(&ret, str, file);
	return ret;
}
static inline char* sgx_wrapper_fgets(char* str, int num, SGX_WRAPPER_FILE FILESTREAM)
{
	char* ret;
	ocall_fgets(&ret, str, num, FILESTREAM);
	return ret;
}
static inline int sgx_wrapper_feof(SGX_WRAPPER_FILE file)	
{
	int ret = 0;
	ocall_feof(&ret, file);
	return ret;
}
static inline size_t sgx_wrapper_fread(void* ptr, size_t size, size_t nmemb, SGX_WRAPPER_FILE FILESTREAM)
{
	size_t ret; 
	ocall_fread(&ret, ptr, size, nmemb, FILESTREAM);
	return ret;
}
static inline size_t sgx_wrapper_fwrite(const void* ptr, size_t size, size_t count, SGX_WRAPPER_FILE FILESTREAM)
{
	size_t ret;
	ocall_fwrite(&ret, ptr, size, count, FILESTREAM);
	return ret;
}
static inline int sgx_wrapper_fseeko(SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence)
{
	int ret;
	ocall_fseeko(&ret, FILESTREAM, offset, whence);
	return ret;
}
static inline off_t sgx_wrapper_ftello(SGX_WRAPPER_FILE FILESTREAM)
{
	off_t ret;
	ocall_ftello(&ret, FILESTREAM);
	return ret;
}
static inline int sgx_wrapper_fseek(SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence)
{
	int ret;
	ocall_fseek(&ret, FILESTREAM, offset, whence);
	return ret;
}
static inline off_t sgx_wrapper_ftell(SGX_WRAPPER_FILE FILESTREAM)
{
	off_t ret;
	ocall_ftell(&ret, FILESTREAM);
	return ret;
}
static inline int sgx_wrapper_ferror(SGX_WRAPPER_FILE FILESTREAM)
{
	int ret;
	ocall_ferror(&ret, FILESTREAM);
	return ret;
}
static inline void sgx_wrapper_perror(const char* s)
{
	ocall_perror(s);
}
static inline int sgx_wrapper_fflush(SGX_WRAPPER_FILE FILESTREAM)
{
	int ret;
	ocall_fflush(&ret, FILESTREAM);
	return ret;
}
static inline int sgx_wrapper_vfprintf(SGX_WRAPPER_FILE FILESTREAM, const char* format, void* val)
{
	int ret;
	ocall_vfprintf(&ret, FILESTREAM, format, val);
	return ret;
}
static inline int sgx_wrapper_vprintf(const char* format, void* val)
{
	int ret;
	ocall_vprintf(&ret, format, val);
	return ret;
}
static inline int sgx_wrapper_vsprintf(char* string, const char* format, void* val)
{
	int ret;
	ocall_vsprintf(&ret, string, format, val);
	return ret;
}
static inline int sgx_wrapper_vasprintf(char** string, const char* format, void* val)
{
	int ret;
	ocall_vasprintf(&ret, string, format, val);
	return ret;
}
static inline int sgx_wrapper_getc(SGX_WRAPPER_FILE FILESTREAM)
{
	int ret;
	ocall_getc(&ret, FILESTREAM);
	return ret;
}

static inline int sgx_wrapper_getchar()
{
	return sgx_wrapper_getc(SGX_STDIN);
}


static inline int sgx_wrapper_vfscanf(SGX_WRAPPER_FILE FILESTREAM, const char *format, void* ap)
{
	int retval;
    ocall_vfscanf(&retval, FILESTREAM, format, ap);
	return retval;
}

static inline int sgx_wrapper_vscanf(const char *format, void* ap)
{
	int retval;
    ocall_vscanf(&retval, format, ap);
	return retval;
}

static inline int sgx_wrapper_vsscanf(const char* s, const char *format, void* ap)
{
	int retval;
    ocall_vsscanf(&retval, s, format, ap);
	return retval;
}

static inline int sgx_wrapper_putchar(int c)
{
	int retval;
    ocall_putchar(&retval, c);
	return retval;
}

static inline int sgx_wrapper_putc(int c, SGX_WRAPPER_FILE FILESTREAM)
{
	int retval; 
    ocall_putc(&retval, c, FILESTREAM);
	return retval;
}

static inline int sgx_wrapper_fputc(int c, SGX_WRAPPER_FILE FILESTREAM)
{
	int retval; 
    ocall_fputc(&retval, c, FILESTREAM);
	return retval;
}


// #define fprintf(A, B, ...) ocall_fprintf(A, B, ##__VA_ARGS__)
// static inline int sgx_wrapper_scanf(const char* format, ...)	
// {
// 	sgx_wrapper_printf("sgx_wrapper_scanf \n");
// 	int result = 0;
// 	va_list ap;
// 	va_start(ap, format);
// 	int ret;
// 	result += ret;
//     ocall_vscanf(&ret, format, &ap);
//     va_end(ap);
//     sgx_wrapper_printf("done sgx_wrapper_scanf \n");
//     return result;
// }

static inline int sgx_wrapper_fscanf(SGX_WRAPPER_FILE FILESTREAM, const char* format, ...)	
{
	sgx_wrapper_printf("sgx_wrapper_fscanf \n");
	int result = 0;
	va_list ap;
	va_start(ap, format);
	int ret;
	result += ret;
    ocall_vfscanf(&ret, FILESTREAM, format, &ap);
    va_end(ap);
    sgx_wrapper_printf("done sgx_wrapper_fscanf \n");
    return result;
}


static inline SGX_WRAPPER_FILE sgx_wrapper_fopen(const char* filename, const char* mode)	
{
	SGX_WRAPPER_FILE f = 0;
	// sgx_wrapper_printf("Call ocall_fopen: %s \n", filename);
	int err = ocall_fopen(&f, filename, mode);
	// sgx_wrapper_printf("ocall_fopen error code: %x \n", err);
	return f;
}

// static inline int sgx_wrapper_sscanf(const char* s, const char* format, ...)	
// {
// 	sgx_wrapper_printf("sgx_wrapper_sscanf \n");
// 	int result = 0;
// 	va_list ap;
// 	va_start(ap, format);
// 	int ret;
//     int status = ocall_vsscanf(&ret, s, format, &ap);
//     result += ret;
//     // sgx_wrapper_printf("\n n The ocall return status code ocall_vsscanf is: %x \n", status);
//     va_end(ap);
//     // sgx_wrapper_printf("sgx_wrapper_sscanf return result is: %d\n", result);
//     sgx_wrapper_printf("sgx_wrapper_sscanf \n");
//     return result;
// }

// static inline int sgx_wrapper_asprintf(char** string, const char* format, ...)	
// {
// 	sgx_wrapper_printf("sgx_wrapper_asprintf \n");
// 	int result = 0;
// 	va_list ap;
// 	va_start(ap, format);
// 	int ret;
//     ocall_vasprintf(&ret, string, format, &ap);
//     result += ret;
//     va_end(ap);
//     sgx_wrapper_printf("sgx_wrapper_asprintf \n");
//     return result;
// }

#ifdef USE_INNER_SSCANF

#include <ctype.h>
#include <limits.h>
#include <assert.h>

#define HIDDEN_MAX_SCANF_WIDTH 9999
#define HIDDEN_TOR_ISDIGIT(A) isdigit(A)
#define HIDDEN_TOR_ISXDIGIT(A) isxdigit(A)
#define HIDDEN_TOR_ISSPACE(A) isspace(A)
#define hidden_tor_assert(A) assert(A)

static inline int
hidden_hex_decode_digit(char c)
{
  switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'A': case 'a': return 10;
    case 'B': case 'b': return 11;
    case 'C': case 'c': return 12;
    case 'D': case 'd': return 13;
    case 'E': case 'e': return 14;
    case 'F': case 'f': return 15;
    default:
      return -1;
  }
}

/** Helper: given an ASCII-encoded decimal digit, return its numeric value.
 * NOTE: requires that its input be in-bounds. */
static inline int
hidden_digit_to_num(char d)
{
  int num = ((int)d) - (int)'0';
  hidden_tor_assert(num <= 9 && num >= 0);
  return num;
}

/** Helper: Read an unsigned int from *<b>bufp</b> of up to <b>width</b>
 * characters.  (Handle arbitrary width if <b>width</b> is less than 0.)  On
 * success, store the result in <b>out</b>, advance bufp to the next
 * character, and return 0.  On failure, return -1. */
static inline int
hidden_scan_unsigned(const char **bufp, unsigned long *out, int width, int base)
{
  unsigned long result = 0;
  int scanned_so_far = 0;
  const int hex = base==16;
  hidden_tor_assert(base == 10 || base == 16);
  if (!bufp || !*bufp || !out)
    return -1;
  if (width<0)
    width=HIDDEN_MAX_SCANF_WIDTH;

  while (**bufp && (hex?HIDDEN_TOR_ISXDIGIT(**bufp):HIDDEN_TOR_ISDIGIT(**bufp))
         && scanned_so_far < width) {
    int digit = hex?hidden_hex_decode_digit(*(*bufp)++):hidden_digit_to_num(*(*bufp)++);
    unsigned long new_result = result * base + digit;
    if (new_result < result)
      return -1; /* over/underflow. */
    result = new_result;
    ++scanned_so_far;
  }

  if (!scanned_so_far) /* No actual digits scanned */
    return -1;

  *out = result;
  return 0;
}

/** Helper: Read an signed int from *<b>bufp</b> of up to <b>width</b>
 * characters.  (Handle arbitrary width if <b>width</b> is less than 0.)  On
 * success, store the result in <b>out</b>, advance bufp to the next
 * character, and return 0.  On failure, return -1. */
static inline int
hidden_scan_signed(const char **bufp, long *out, int width)
{
  int neg = 0;
  unsigned long result = 0;

  if (!bufp || !*bufp || !out)
    return -1;
  if (width<0)
    width=HIDDEN_MAX_SCANF_WIDTH;

  if (**bufp == '-') {
    neg = 1;
    ++*bufp;
    --width;
  }

  if (hidden_scan_unsigned(bufp, &result, width, 10) < 0)
    return -1;

  if (neg) {
    if (result > ((unsigned long)LONG_MAX) + 1)
      return -1; /* Underflow */
    *out = -(long)result;
  } else {
    if (result > LONG_MAX)
      return -1; /* Overflow */
    *out = (long)result;
  }

  return 0;
}

/** Helper: Read a decimal-formatted double from *<b>bufp</b> of up to
 * <b>width</b> characters.  (Handle arbitrary width if <b>width</b> is less
 * than 0.)  On success, store the result in <b>out</b>, advance bufp to the
 * next character, and return 0.  On failure, return -1. */
static inline int
hidden_scan_double(const char **bufp, double *out, int width)
{
  int neg = 0;
  double result = 0;
  int scanned_so_far = 0;

  if (!bufp || !*bufp || !out)
    return -1;
  if (width<0)
    width=HIDDEN_MAX_SCANF_WIDTH;

  if (**bufp == '-') {
    neg = 1;
    ++*bufp;
  }

  while (**bufp && HIDDEN_TOR_ISDIGIT(**bufp) && scanned_so_far < width) {
    const int digit = hidden_digit_to_num(*(*bufp)++);
    result = result * 10 + digit;
    ++scanned_so_far;
  }
  if (**bufp == '.') {
    double fracval = 0, denominator = 1;
    ++*bufp;
    ++scanned_so_far;
    while (**bufp && HIDDEN_TOR_ISDIGIT(**bufp) && scanned_so_far < width) {
      const int digit = hidden_digit_to_num(*(*bufp)++);
      fracval = fracval * 10 + digit;
      denominator *= 10;
      ++scanned_so_far;
    }
    result += fracval / denominator;
  }

  if (!scanned_so_far) /* No actual digits scanned */
    return -1;

  *out = neg ? -result : result;
  return 0;
}

/** Helper: copy up to <b>width</b> non-space characters from <b>bufp</b> to
 * <b>out</b>.  Make sure <b>out</b> is nul-terminated. Advance <b>bufp</b>
 * to the next non-space character or the EOS. */
static inline int
hidden_scan_string(const char **bufp, char *out, int width)
{
  int scanned_so_far = 0;
  if (!bufp || !out || width < 0)
    return -1;
  while (**bufp && ! HIDDEN_TOR_ISSPACE(**bufp) && scanned_so_far < width) {
    *out++ = *(*bufp)++;
    ++scanned_so_far;
  }
  *out = '\0';
  return 0;
}

/** Locale-independent, minimal, no-surprises scanf variant, accepting only a
 * restricted pattern format.  For more info on what it supports, see
 * tor_sscanf() documentation.  */
static inline int
hidden_tor_vsscanf(const char *buf, const char *pattern, va_list ap)
{
  int n_matched = 0;

  while (*pattern) {
    if (*pattern != '%') {
      if (*buf == *pattern) {
        ++buf;
        ++pattern;
        continue;
      } else {
        return n_matched;
      }
    } else {
      int width = -1;
      int longmod = 0;
      ++pattern;
      if (HIDDEN_TOR_ISDIGIT(*pattern)) {
        width = hidden_digit_to_num(*pattern++);
        while (HIDDEN_TOR_ISDIGIT(*pattern)) {
          width *= 10;
          width += hidden_digit_to_num(*pattern++);
          if (width > HIDDEN_MAX_SCANF_WIDTH)
            return -1;
        }
        if (!width) /* No zero-width things. */
          return -1;
      }
      if (*pattern == 'l') {
        longmod = 1;
        ++pattern;
      }
      if (*pattern == 'u' || *pattern == 'x') {
        unsigned long u;
        const int base = (*pattern == 'u') ? 10 : 16;
        if (!*buf)
          return n_matched;
        if (hidden_scan_unsigned(&buf, &u, width, base)<0)
          return n_matched;
        if (longmod) {
          unsigned long *out = va_arg(ap, unsigned long *);
          *out = u;
        } else {
          unsigned *out = va_arg(ap, unsigned *);
          if (u > UINT_MAX)
            return n_matched;
          *out = (unsigned) u;
        }
        ++pattern;
        ++n_matched;
      } else if (*pattern == 'f') {
        double *d = va_arg(ap, double *);
        if (!longmod)
          return -1; /* float not supported */
        if (!*buf)
          return n_matched;
        if (hidden_scan_double(&buf, d, width)<0)
          return n_matched;
        ++pattern;
        ++n_matched;
      } else if (*pattern == 'd') {
        long lng=0;
        if (hidden_scan_signed(&buf, &lng, width)<0)
          return n_matched;
        if (longmod) {
          long *out = va_arg(ap, long *);
          *out = lng;
        } else {
          int *out = va_arg(ap, int *);
          if (lng < INT_MIN || lng > INT_MAX)
            return n_matched;
          *out = (int)lng;
        }
        ++pattern;
        ++n_matched;
      } else if (*pattern == 's') {
        char *s = va_arg(ap, char *);
        if (longmod)
          return -1;
        if (width < 0)
          return -1;
        if (hidden_scan_string(&buf, s, width)<0)
          return n_matched;
        ++pattern;
        ++n_matched;
      } else if (*pattern == 'c') {
        char *ch = va_arg(ap, char *);
        if (longmod)
          return -1;
        if (width != -1)
          return -1;
        if (!*buf)
          return n_matched;
        *ch = *buf++;
        ++pattern;
        ++n_matched;
      } else if (*pattern == '%') {
        if (*buf != '%')
          return n_matched;
        if (longmod)
          return -1;
        ++buf;
        ++pattern;
      } else {
        return -1; /* Unrecognized pattern component. */
      }
    }
  }

  return n_matched;
}

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
static inline int
hidden_tor_sscanf(const char *buf, const char *pattern, ...)
{
  sgx_wrapper_printf("Fix me: Call untested hidden_tor_sscanf: %s", buf);
  int r;
  va_list ap;
  va_start(ap, pattern);
  r = hidden_tor_vsscanf(buf, pattern, ap);
  va_end(ap);
  sgx_wrapper_printf("return: %d", r);
  return r;
}

#define sscanf(A, B, ...) hidden_tor_sscanf(A, B, ##__VA_ARGS__)

#endif

#define stdin SGX_STDIN
#define stdout SGX_STDOUT 
#define stderr SGX_STDERR

#define printf(A, ...) sgx_wrapper_printf(A, ##__VA_ARGS__)
#define fprintf(A, B, ...) sgx_wrapper_fprintf(A, B, ##__VA_ARGS__)
// Fix me: sprintf and asprintf need to change to snprintf version, mem sz need to be 
// added to the context
// #define sprintf(A, B, ...) snprintf(A,(sizeof(A)), B, ##__VA_ARGS__)
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
// #define vfprintf(A, B, C) sgx_wrapper_vfprintf(A, B, C)
// #define vprintf(A, B) sgx_wrapper_vprintf(A, B)
// #define vsprintf(A, B, C) sgx_wrapper_vsprintf(A, B, C)
// #define vasprintf(A, B, C) sgx_wrapper_vasprintf(A, B, C)
#define getc(A) sgx_wrapper_getc(A)
#define getchar() sgx_wrapper_getchar()
// #define vscanf(A, B) sgx_wrapper_vscanf(A, B)
// #define vfscanf(A, B, C) sgx_wrapper_vfscanf(A, B, C)
// #define vsscanf(A, B, C) sgx_wrapper_vsscanf(A, B, C)
#define putchar(A) sgx_wrapper_putchar(A)
#define putc(A, B) sgx_wrapper_putc(A, B)
#define fputc(A, B) sgx_wrapper_fputc(A, B)
// #define scanf(A, ...) sgx_wrapper_scanf(A, ##__VA_ARGS__)
// #define fscanf(A, B, ...) sgx_wrapper_fscanf(A, B, ##__VA_ARGS__)
// #define sscanf(A, B, ...) sgx_wrapper_sscanf(A, B, ##__VA_ARGS__)

#endif