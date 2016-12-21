#include <netinet/in.h>

#include "TopensslEnclave_u.h"

extern void increase_ocall_count();
uint32_t ocall_ntohl(uint32_t netlong)
{
	increase_ocall_count();
	return ntohl(netlong);
}

uint16_t ocall_ntohs(uint16_t netshort)
{
	increase_ocall_count();
	return ntohs(netshort);
}

uint32_t ocall_htonl(uint32_t hostlong)
{
	increase_ocall_count();
	return htonl(hostlong);
}

uint16_t ocall_htons(uint16_t hostshort)
{
	increase_ocall_count();
	return htons(hostshort);
}