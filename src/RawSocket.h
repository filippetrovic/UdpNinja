#pragma once

#include "IpPacket.h"

namespace udpninja
{

class RawSocket {
public:
	RawSocket(unsigned int port);
	~RawSocket();
	int open();
	IpPacket * read();
	unsigned int getPort();

private:
	int socketHandle;
	IpPacket * packet;
	unsigned int port;
};

}

