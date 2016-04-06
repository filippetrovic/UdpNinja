#pragma once

#include "RawSocketSender.h"
#include "Job.h"

namespace udpninja
{

class ReplaySender: public Job {
public:
	ReplaySender();
	~ReplaySender();
	
	void doJob();
	void sayHello();
	
private:
	int prepare();

	RawSocketSender * outSocket;
};

}

