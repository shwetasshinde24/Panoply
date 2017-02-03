#include	<sgx/sys/types.h>
#include	<sgx_syssocket_util.h>
#include	<sgx_netinetin_util.h>
#include	<sgx_netdb_util.h>
#include	<sgx_arpainet_util.h>

#ifdef __cplusplus
extern "C"	{
#endif 

int	tcp_server(int prog, int rdwr);
int	tcp_done(int prog);
int	tcp_accept(int sock, int rdwr);
int	tcp_connect(char *host, int prog, int rdwr);
void	sock_optimize(int sock, int rdwr);
int	sockport(int s);

#ifdef __cplusplus
}
#endif 