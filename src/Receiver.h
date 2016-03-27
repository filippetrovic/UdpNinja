#pragma once
#include "RawSocket.h"
#include "FileSplitter.h"
#include "Job.h"

namespace udpninja
{

class Receiver: public Job {
public:
	Receiver(unsigned int port, char * dir);
	~Receiver();
	
	void doJob();
	void sayHello();
private:
	RawSocket * inSocket;
	FileSplitter * outputFile;
};

}

