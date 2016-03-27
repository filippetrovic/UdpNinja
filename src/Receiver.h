#pragma once
#include "RawSocket.h"
#include "FileSplitter.h"

namespace udpninja
{

class Receiver {
public:
	Receiver(unsigned int port);
	~Receiver();
	
	void doJob();
private:
	RawSocket * inSocket;
	FileSplitter * outputFile;
};

}

