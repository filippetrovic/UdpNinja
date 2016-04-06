#pragma once

namespace udpninja
{

struct IpPacket {
public:
	IpPacket();
	~IpPacket();

	unsigned int len;
	unsigned char * data;
};
}

