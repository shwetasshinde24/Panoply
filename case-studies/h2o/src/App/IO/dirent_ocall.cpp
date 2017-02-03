#include <dirent.h>

#include "H2oEnclave_u.h"



// Fix me: Dirent struct is opaque and is hidden, cannot pick its definition and put inside enclave

void *ocall_opendir (const char *name)
{
	return (void *)opendir(name);
}

void *ocall_fdopendir (int fd)
{
	return (void *)fdopendir(fd);
}

int ocall_closedir (void *dirp_cast)
{
	DIR *dirp = (DIR *)dirp_cast;
	return closedir(dirp);
}

struct dirent *ocall_readdir (void *dirp_cast)
{
	DIR *dirp = (DIR *)dirp_cast;
	return readdir(dirp);
}

int ocall_readdir_r (void *dirp_cast, struct dirent *entry, struct dirent **result)
{
	DIR *dirp = (DIR *)dirp_cast;
	return readdir_r(dirp, entry, result);
}

void ocall_rewinddir (void *dirp_cast)
{
	DIR *dirp = (DIR *)dirp_cast;
	rewinddir(dirp);
}

void ocall_seekdir (void *dirp_cast, long int pos)
{
	DIR *dirp = (DIR *)dirp_cast;
	seekdir(dirp, pos);
}

long int ocall_telldir ( void *dirp_cast)
{
	DIR *dirp = (DIR *)dirp_cast;
	return telldir(dirp);
}

int ocall_dirfd ( void *dirp_cast)
{
	DIR *dirp = (DIR *)dirp_cast;
	return dirfd(dirp);
}

int ocall_alphasort ( const struct dirent **e1,  const struct dirent **e2)
{
	return alphasort(e1, e2);
}

ssize_t ocall_getdirentries (int fd, char *buf, size_t nbytes, off_t *basep)
{
	return getdirentries(fd, buf, nbytes, basep);
}

int ocall_versionsort (const struct dirent **e1,  const struct dirent **e2)
{
	return versionsort(e1, e2);
}