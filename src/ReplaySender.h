#pragma once

#include "RawSocketSender.h"
#include "Job.h"
#include "File.h"

namespace udpninja
{

class ReplaySender: public Job {
public:
	ReplaySender();
	~ReplaySender();
	
	void doJob();
	void sayHello();
	
	void setInputFilename(char* filename);
	void setReceiver(char* receiver);
	char* getInputFilename();
	char* getReceiverIp();
	int getReceiverPort();
	void setDontCalculateUdpCheckum(bool flag);
	
private:
	int prepare();
	
	char * receiverIp;
	int receiverPort;	// In htons format
	char * inputFile;
	bool dontCalculateUdpChecksum;
	File * inFile;
	RawSocketSender * outSocket;
};

}

