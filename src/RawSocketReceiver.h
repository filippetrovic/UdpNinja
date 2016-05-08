#pragma once

#include "IpPacket.h"

namespace udpninja
{

class RawSocketReceiver {
public:
	RawSocketReceiver(unsigned int port);
	~RawSocketReceiver();
	int open();
	IpPacket * read();
	unsigned int getPort();

private:
	int socketHandle;
	IpPacket * packet;
	unsigned int port;
};

}

