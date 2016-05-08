#pragma once

#include "Job.h"

namespace udpninja
{

class JobBuilder
{
public:
	JobBuilder(int argc, char **argv);
	~JobBuilder();
	Job* getJob();
private:
	Job* createReceiver();
	Job* createReplayJob();
	
	int argc;
	char ** argv;
	Job * job;
};

}

