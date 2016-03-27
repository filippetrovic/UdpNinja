#pragma once

#include "Job.h"

namespace udpninja
{

class HelpJob: public Job{
public:
	HelpJob();
	~HelpJob();
	
	void doJob();
	void sayHello();
};

}

