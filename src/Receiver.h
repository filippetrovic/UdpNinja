#pragma once
#include "RawSocket.h"

namespace udpninja
{

class Receiver {
public:
	Receiver(unsigned int port);
	~Receiver();
	
	void doJob();
private:
	unsigned int port;
	RawSocket * inSocket;
};

}

