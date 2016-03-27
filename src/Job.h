#pragma once

namespace udpninja
{

class Job
{
public:
	Job();
	~Job();
	virtual void doJob() = 0;
	virtual void sayHello() = 0;
};

}

