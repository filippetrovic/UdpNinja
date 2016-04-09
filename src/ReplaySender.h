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

private:
	int prepare();
	
	char * receiverIp;
	int receiverPort;
	char * inputFile;
	File * inFile;
	RawSocketSender * outSocket;
};

}

