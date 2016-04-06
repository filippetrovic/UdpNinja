#pragma once
#include "RawSocket.h"
#include "IpPacket.h"
#include "FileSplitter.h"
#include "Job.h"

#define DEFAULT_OUTPUT_DIR "/tmp"
#define DEFAULT_PORT 514
namespace udpninja
{

class Receiver: public Job {
public:
	Receiver();
	~Receiver();
	
	void doJob();
	void sayHello();
	
	
	void setDir(char* dir);
	char* getDir();

	void setPort(unsigned int port);
	unsigned int getPort();
private:

	int prepare();

	unsigned int port;
	char * dir;

	RawSocket * inSocket;
	FileSplitter * outputFile;
};

}

