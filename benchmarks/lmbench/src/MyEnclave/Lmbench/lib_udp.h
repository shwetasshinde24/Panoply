#include	<sgx/sys/types.h>
#include	<sgx_syssocket_util.h>
#include	<sgx_netinetin_util.h>
#include	<sgx_netdb_util.h>
#include	<sgx_arpainet_util.h>

#ifdef __cplusplus
extern "C"	{
#endif 

int	udp_server(u_long prog, int rdwr);
void	udp_done(u_long prog);
int	udp_connect(char *host, u_long prog, int rdwr);
void	sock_optimize(int sock, int rdwr);
int	sockport(int);

#ifdef __cplusplus
}
#endif 
