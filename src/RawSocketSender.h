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
	int socketHandle;
	sockaddr_in * dest;
};

}

