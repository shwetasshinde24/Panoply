/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <stdio.h>
#include <stdarg.h>

#include "struct/sgx_stdio_struct.h"
#include <MyEnclave_u.h>

#define MAX_FILE_BUFFER 65000

FILE* fd_tables[MAX_FILE_BUFFER];

static int count = SGX_STDERR+1;

int ocall_print_string(const char* s)   {
    return printf("%s", s);
}

SGX_WRAPPER_FILE ocall_fopen(const char* filename, const char* mode)  {
    // printf("ocall_fopen : %s, %s", filename, mode);
    SGX_WRAPPER_FILE fd = count++;
    FILE* f = NULL;
    f = fopen(filename, mode);
    fd_tables[fd] = f;

    if (fd_tables[fd]==NULL)    {
        return 0;
    }

    return fd;
}

SGX_WRAPPER_FILE ocall_popen(const char* command, const char* type)   {
    SGX_WRAPPER_FILE fd = count++;
    FILE* f = NULL;
    f = popen(command, type);
    fd_tables[fd] = f;

    if (fd_tables[fd]==NULL)    {
        return 0;
    }

    return fd;  
}

SGX_WRAPPER_FILE ocall_fdopen(int fd, const char *modes)
{
    SGX_WRAPPER_FILE myfd = count++;
    FILE* f = NULL;
    f = fdopen(fd, modes);
    fd_tables[myfd] = f;

    if (fd_tables[myfd]==NULL)    {
        return 0;
    }

    return myfd;    
}

FILE* getFile(int fd)   
{
    if (fd == SGX_STDIN)
        return stdin;

    if (fd == SGX_STDOUT)
        return stdout;

    if (fd == SGX_STDERR)
        return stderr;

    if (fd<=0)
        return NULL;

    return fd_tables[fd];
}

int ocall_fprint_string(SGX_WRAPPER_FILE FILESTREAM, const char* s)   {
    FILE* file = NULL;
    file = getFile(FILESTREAM);    
    return fprintf(file, "%s", s);
}

int ocall_fileno(SGX_WRAPPER_FILE FILESTREAM)
{
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    return fileno(file);    
}

int ocall_fclose(SGX_WRAPPER_FILE FILESTREAM) {
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    fd_tables[FILESTREAM] = NULL;
    return fclose(file);
}

int ocall_pclose(SGX_WRAPPER_FILE FILESTREAM) {
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    fd_tables[FILESTREAM] = NULL;
    return pclose(file);
}

int ocall_fputs(const char* str, SGX_WRAPPER_FILE FILESTREAM) 
{
    fprintf (stderr, "ocall_fputs: %d", FILESTREAM);
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    return fputs(str, file);
}

int ocall_feof(SGX_WRAPPER_FILE FILESTREAM)   
{
    // // fprintf (stderr, "ocall_feof: %d", FILESTREAM);
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    return feof(file);
}

void ocall_rewind(SGX_WRAPPER_FILE FILESTREAM)    
{
    // // fprintf (stderr, "ocall_rewind: %d", FILESTREAM);
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    return rewind(file);
}

int ocall_fflush(SGX_WRAPPER_FILE FILESTREAM) 
{
    // printf("ocall_fflush: %d", FILESTREAM);
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    return fflush(file);
}

size_t ocall_fread(void *ptr, size_t size, size_t nmemb, SGX_WRAPPER_FILE FILESTREAM) 
{
    FILE* file = NULL;
    file = getFile(FILESTREAM); 
    size_t ret = -1;
    ret = fread(ptr, size, nmemb, file);
    return ret;
}

size_t ocall_fwrite(const void * ptr, size_t size, size_t count, SGX_WRAPPER_FILE FILESTREAM)
{
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    return fwrite(ptr, size, count, file);  
}

int ocall_fprintf(SGX_WRAPPER_FILE FILESTREAM, const char* format, ...)    {
    // // fprintf (stderr, "Some one call the wrapper // // fprintf ");
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    va_list ap;
    va_start(ap, format);
    fprintf (file, format, ap);
    va_end(ap);
    return 1;
}

int ocall_vfprintf(SGX_WRAPPER_FILE FILESTREAM, const char* format, void* ap)    {
    // fprintf (stderr, "Some one call the wrapper fprintf %p", ap);
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    va_list* wrapper = (va_list*)ap;
    return vfprintf (file, format, *wrapper);
}

int ocall_vsprintf(char* string, const char* format, void* ap)  {
     va_list* wrapper = (va_list*)ap;
    return vsprintf (string, format, *wrapper);
}

int ocall_vasprintf(char** string, const char* format, void* ap) {
    va_list* wrapper = (va_list*)ap;
    return vasprintf (string, format, *wrapper);
}

int ocall_vprintf(const char* format, void* ap)
{
    va_list* wrapper = (va_list*)ap;
    return vprintf(format, *wrapper);   
}

// static inline int ocall_vprintf(SGX_WRAPPER_FILE FILESTREAM, const char* format, ...)  {
//  FILE* file = getFile(FILESTREAM);
//  return vprintf(file, format);
// }


char* ocall_fgets(char * str, int num, SGX_WRAPPER_FILE FILESTREAM)   
{
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    char* ret = fgets(str, num, file);
    return ret;
}

int ocall_getc_unlocked(SGX_WRAPPER_FILE FILESTREAM)  
{
    // // fprintf (stderr, "ocall_getc_unlocked: %d", FILESTREAM);
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    return getc_unlocked(file);
}

void ocall_flockfile(SGX_WRAPPER_FILE filehandle) 
{
    // // fprintf (stderr, "ocall_flockfile: %d", filehandle);
    FILE* file = NULL;
    file = getFile(filehandle);
    return flockfile(file);
}

void ocall_funlockfile(SGX_WRAPPER_FILE filehandle)
{
    FILE* file = NULL;
    file = getFile(filehandle);
    return funlockfile(file);    
}

off_t ocall_ftello(SGX_WRAPPER_FILE FILESTREAM)
{
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    return ftello(file);
}

int ocall_fseeko(SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence)
{
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    return fseeko(file, offset, whence);
}

long ocall_ftell(SGX_WRAPPER_FILE FILESTREAM)
{
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    return ftell(file);
}

int ocall_fseek(SGX_WRAPPER_FILE FILESTREAM, off_t offset, int whence)
{
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    int ret = fseek(file, offset, whence);
    return ret;
}


int ocall_ferror(SGX_WRAPPER_FILE FILESTREAM)
{
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    return ferror(file);
}

void ocall_perror(const char* s)
{
    return perror(s);
}

int ocall_getc(SGX_WRAPPER_FILE FILESTREAM)
{
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    return getc(file);    
}

int ocall_vfscanf(SGX_WRAPPER_FILE FILESTREAM, const char *format, void* ap)
{
    FILE* file = NULL;
    file = getFile(FILESTREAM);
    va_list* wrapper = (va_list*)ap;
    return vfscanf(file, format, *wrapper);
}

int ocall_vscanf(const char *format, void* ap)
{
    va_list* wrapper = (va_list*)ap;
    return vscanf(format, *wrapper);
}

int ocall_vsscanf(const char* s, const char *format, void* ap)
{
    va_list* wrapper = (va_list*)ap;
    return vsscanf(s, format, *wrapper);
}

int ocall_putchar(int c)
{
    return putchar(c);
}

int ocall_putc(int c, SGX_WRAPPER_FILE FILESTREAM)
{
     printf("ocall_putc \n");
    FILE* file = NULL;
    file = getFile(FILESTREAM);    
    return putc(c, file);
}

int ocall_fputc(int c, SGX_WRAPPER_FILE FILESTREAM)
{
    printf("ocall_fputc \n");
    FILE* file = NULL;
    file = getFile(FILESTREAM);    
    return fputc(c, file);
}

int ocall_rename(const char* _old, const char* _new)
{
    int ret = -5;
    ret = rename(_old, _new);
    // printf ("Rename: %s to %s res: %d \n", _old, _new, ret);
    return ret;
}

char *ocall_tempnam(const char *dir, const char *pfx)
{
    return tempnam(dir, pfx);
}