#include "Job.h"
#include "JobBuilder.h"

using namespace udpninja;


int main(int argc, char **argv) {

	JobBuilder * builder = new JobBuilder(argc, argv);
	
	Job * job = builder->getJob();

	delete builder;
	
	job->sayHello();
	job->doJob();
	
	delete job;
	
}