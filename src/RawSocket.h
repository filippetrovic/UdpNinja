#pragma once

namespace udpninja
{

struct IpPacket {
	unsigned int len;
	unsigned char * data;

	IpPacket();
	~IpPacket();
};

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

