#ifndef _NEVERBLEED_H_
#define _NEVERBLEED_H_

// #include <stdlib.h>
#include <sgx_stdlib_util.h>
#include <assert.h>
// #include <pthread.h>
#include <sgx_pthread_util.h>
// #include <sys/socket.h>
#include <sgx_syssocket_util.h>
// #include <sys/un.h>
#include <sgx/sys/un.h>
#include <openssl/engine.h>


// #include <sys/types.h>
#include <sgx/sys/types.h>
// #include <unistd.h>
#include <sgx_unistd_util.h>


#define AF_UNIX         1       /* Unix domain sockets          */
#define PF_UNIX         AF_UNIX
#define SOMAXCONN       128


#if defined(__cplusplus)
extern "C" {
#endif


//#include <limits.h>		/* PATH_MAX */
#define PATH_MAX        4096	/* # chars in a path name including nul */

// void printf(const char *fmt, ...);

#define NEVERBLEED_ERRBUF_SIZE (256)
#define NEVERBLEED_AUTH_TOKEN_SIZE 32

typedef struct st_neverbleed_t {
    ENGINE *engine;
    pid_t daemon_pid;
    struct sockaddr_un sun_;
    pthread_key_t thread_key;
    unsigned char auth_token[NEVERBLEED_AUTH_TOKEN_SIZE];
} neverbleed_t;

/**
 * initializes the privilege separation engine (returns 0 if successful)
 */
int neverbleed_init(neverbleed_t *nb, char *errbuf);
/**
 * loads a private key file (returns 0 if successful, -1 if failed)
 */
int neverbleed_load_private_key_file(neverbleed_t *nb, SSL_CTX *ctx, const char *fn, char *errbuf);
/**
 * setuidgid (also changes the file permissions so that `user` can connect to the daemon, if change_socket_ownership is non-zero)
 */
int neverbleed_setuidgid(neverbleed_t *nb, const char *user, int change_socket_ownership);


#if defined(__cplusplus)
}
#endif

#endif /* !_NEVERBLEED_H_ */


