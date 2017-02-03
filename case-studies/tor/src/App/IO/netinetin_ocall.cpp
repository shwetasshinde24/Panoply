#include <netinet/in.h>

#include "TorEnclave_u.h"


uint32_t ocall_ntohl(uint32_t netlong)
{
	return ntohl(netlong);
}

uint16_t ocall_ntohs(uint16_t netshort)
{
	return ntohs(netshort);
}

uint32_t ocall_htonl(uint32_t hostlong)
{
	return htonl(hostlong);
}

uint16_t ocall_htons(uint16_t hostshort)
{
	return htons(hostshort);
}