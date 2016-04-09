#pragma once

#include "IpPacket.h"
#include <netinet/ip.h>

namespace udpninja
{

class RawSocketSender
{
public:
	RawSocketSender();
	~RawSocketSender();

	int open();
	int send(IpPacket * packet);

private:
	uint16_t generateChecksum(void *buf, size_t hdr_len);
	
	int socketHandle;
	sockaddr_in * dest;
};

}

