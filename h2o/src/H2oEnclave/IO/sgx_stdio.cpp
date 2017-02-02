#include <sgx_stdio_util.h>
#include <string.h>
#include <sgx_ocall_util.h>
#include <sgx_thread.h>

#define WRAPBUFSIZ 15000

INIT_LOCK(ocall_fdopen);
INIT_LOCK(ocall_fopen);
INIT_LOCK(ocall_fread);
INIT_LOCK(ocall_fwrite);
INIT_LOCK(ocall_fseek);
INIT_LOCK(ocall_ftell);
INIT_LOCK(ocall_fseeko);
INIT_LOCK(ocall_ftello);
INIT_LOCK(ocall_fflush);

int sgx_wrapper_printf(const char *fmt, ...)
{
    return 1;
    char buf[WRAPBUFSIZ] = {'\0'};
    int result;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, WRAPBUFSIZ, fmt, ap);
    va_end(ap);
    sgx_status_t status = ocall_print_string(&result, buf);
    CHECK_STATUS(status);
    return result;
}

int sgx_wrapper_printf_debug(const char *fmt, ...)
{
    char buf[WRAPBUFSIZ] = {'\0'};
    int result;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, WRAPBUFSIZ, fmt, ap);
    va_end(ap);
    sgx_status_t status = ocall_print_string(&result, buf);
    // CHECK_STATUS(status);
    return result;
}

int sgx_wrapper_fprintf(int FILESTREAM, const char* fmt, ...)
{
    char buf[WRAPBUFSIZ] = {'\0'};
    int result = 0;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, WRAPBUFSIZ, fmt, ap);
    va_end(ap);
    sgx_status_t status = ocall_fprint_string(&result, FILESTREAM, buf);
    CHECK_STATUS(status);
    return result;
}

int sgx_wrapper_asprintf(char **s, const char* format, ...)
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

SGX_WRAPPER_FILE sgx_wrapper_fdopen(int fd, const char* mode)	
{
	SGX_WRAPPER_FILE f = 0;
	sgx_status_t status = SAFE_INVOKE(ocall_fdopen, &f, fd, mode);
  CHECK_STATUS(status);
	return f;
}

int sgx_wrapper_fileno(SGX_WRAPPER_FILE stream)
{
    int retval;
    sgx_status_t status = ocall_fileno(&retval, stream);
    CHECK_STATUS(status);
    return retval;
}

int sgx_wrapper_fclose(SGX_WRAPPER_FILE file)	
{
	int ret = 0;
	sgx_status_t status = ocall_fclose(&ret, file);
  CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_fputs(const char* str, SGX_WRAPPER_FILE file)	
{
	int ret = 0;
	sgx_status_t status = ocall_fputs(&ret, str, file);
  CHECK_STATUS(status);
	return ret;
}

char* sgx_wrapper_fgets(char* str, int num, SGX_WRAPPER_FILE FILESTREAM)
{
	char* ret;
	sgx_status_t status = ocall_fgets(&ret, str, num, FILESTREAM);
  CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_feof(SGX_WRAPPER_FILE file)
{
	int ret = 0;
	sgx_status_t status = ocall_feof(&ret, file);
  CHECK_STATUS(status);
	return ret;
}

size_t sgx_wrapper_fread(void* ptr, size_t size, size_t nmemb, SGX_WRAPPER_FILE FILESTREAM)
{
	size_t ret; 
	sgx_status_t status = SAFE_INVOKE(ocall_fread, &ret, ptr, size, nmemb, FILESTREAM);
  CHECK_STATUS(status);
	return ret;
}

size_t sgx_wrapper_fwrite(const void* ptr, size_t size, size_t count, SGX_WRAPPER_FILE FILESTREAM)
{
	size_t ret;
	sgx_status_t status = SAFE_INVOKE(ocall_fwrite, &ret, ptr, size, count, FILESTREAM);
  CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_fseeko(SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence)
{
	int ret;
	sgx_status_t status = SAFE_INVOKE(ocall_fseeko, &ret, FILESTREAM, offset, whence);
  CHECK_STATUS(status);
	return ret;
}

off_t sgx_wrapper_ftello(SGX_WRAPPER_FILE FILESTREAM)
{
	off_t ret;
	sgx_status_t status = SAFE_INVOKE(ocall_ftello, &ret, FILESTREAM);
  CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_fseek(SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence)
{
	int ret;
	sgx_status_t status = SAFE_INVOKE(ocall_fseek, &ret, FILESTREAM, offset, whence);
  CHECK_STATUS(status);
	return ret;
}

off_t sgx_wrapper_ftell(SGX_WRAPPER_FILE FILESTREAM)
{
	off_t ret;
	sgx_status_t status = SAFE_INVOKE(ocall_ftell, &ret, FILESTREAM);
  CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_ferror(SGX_WRAPPER_FILE FILESTREAM)
{
	int ret;
	sgx_status_t status = ocall_ferror(&ret, FILESTREAM);
  CHECK_STATUS(status);
	return ret;
}

void sgx_wrapper_perror(const char* s)
{
	sgx_status_t status = ocall_perror(s);
  CHECK_STATUS(status);
}

int sgx_wrapper_fflush(SGX_WRAPPER_FILE FILESTREAM)
{
	int ret;
	sgx_status_t status = SAFE_INVOKE(ocall_fflush, &ret, FILESTREAM);
  CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_vfprintf(SGX_WRAPPER_FILE FILESTREAM, const char* format, void* val)
{
	int ret;
	sgx_status_t status = ocall_vfprintf(&ret, FILESTREAM, format, val);
  CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_vprintf(const char* format, void* val)
{
	int ret;
	sgx_status_t status = ocall_vprintf(&ret, format, val);
  CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_vsprintf(char* string, const char* format, void* val)
{
	int ret;
	sgx_status_t status = ocall_vsprintf(&ret, string, format, val);
  CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_vasprintf(char** string, const char* format, void* val)
{
	int ret;
	sgx_status_t status = ocall_vasprintf(&ret, string, format, val);
  CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_getc(SGX_WRAPPER_FILE FILESTREAM)
{
	int ret;
	sgx_status_t status = ocall_getc(&ret, FILESTREAM);
  CHECK_STATUS(status);
	return ret;
}

int sgx_wrapper_getchar()
{
	return sgx_wrapper_getc(SGX_STDIN);
}


int sgx_wrapper_vfscanf(SGX_WRAPPER_FILE FILESTREAM, const char *format, void* ap)
{
	int retval;
  sgx_status_t status = ocall_vfscanf(&retval, FILESTREAM, format, ap);
  CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_vscanf(const char *format, void* ap)
{
	int retval;
  sgx_status_t status = ocall_vscanf(&retval, format, ap);
  CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_vsscanf(const char* s, const char *format, void* ap)
{
	int retval;
    sgx_status_t status = ocall_vsscanf(&retval, s, format, ap);
	return retval;
}

int sgx_wrapper_putchar(int c)
{
	int retval;
  sgx_status_t status = ocall_putchar(&retval, c);
  CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_putc(int c, SGX_WRAPPER_FILE FILESTREAM)
{
	int retval; 
  sgx_status_t status = ocall_putc(&retval, c, FILESTREAM);
  CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_fputc(int c, SGX_WRAPPER_FILE FILESTREAM)
{
	int retval; 
  sgx_status_t status = ocall_fputc(&retval, c, FILESTREAM);
  CHECK_STATUS(status);
	return retval;
}

int sgx_wrapper_fscanf(SGX_WRAPPER_FILE FILESTREAM, const char* format, ...)
{
	sgx_wrapper_printf("sgx_wrapper_fscanf \n");
	int result = 0;
	va_list ap;
	va_start(ap, format);
  	int ret;
  	result += ret;
    sgx_status_t status = ocall_vfscanf(&ret, FILESTREAM, format, &ap);
  va_end(ap);
  sgx_wrapper_printf("done sgx_wrapper_fscanf \n");
  CHECK_STATUS(status);
  return result;
}

int sgx_wrapper_rename(const char* _old, const char* _new)
{
  int ret;
  sgx_status_t status = ocall_rename(&ret, _old, _new);
  CHECK_STATUS(status);
  return ret;
}

SGX_WRAPPER_FILE sgx_wrapper_fopen(const char* filename, const char* mode)
{
	SGX_WRAPPER_FILE f = 0;
	// sgx_wrapper_printf("Call sgx_status_t status = ocall_fopen: %s \n", filename);
	sgx_status_t status = ocall_fopen(&f, filename, mode);
  CHECK_STATUS(status);
	// sgx_wrapper_printf("sgx_status_t status = ocall_fopen error code: %x \n", err);
	return f;
}


#ifdef USE_INNER_SSCANF

#include <ctype.h>
#include <limits.h>
#include <assert.h>

int
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
int
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
int
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
int
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
int
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
int
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
int
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
int
hidden_tor_sscanf(const char *buf, const char *pattern, ...)
{
  // sgx_wrapper_printf("Fix me: Call untested hidden_tor_sscanf: %s", buf);
  int r;
  va_list ap;
  va_start(ap, pattern);
  r = hidden_tor_vsscanf(buf, pattern, ap);
  va_end(ap);
  return r;
}

#endif
