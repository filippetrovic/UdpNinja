#include "JobBuilder.h"
#include "Receiver.h"
#include "HelpJob.h"
#include <cstdlib>
#include <cstring>

using namespace udpninja;

JobBuilder::JobBuilder(int argc, char **argv) {
	this->argc = argc;
	this->argv = argv;
}

JobBuilder::~JobBuilder() {
}

Job* JobBuilder::getJob() {
	const char * mode = argv[1];

	if (strcmp(mode, "-record") == 0) {
		return createReceiver();
	}
	
	return new HelpJob();
}

Job* JobBuilder::createReceiver() {
	unsigned int port;
	char * dir = (char *) "/tmp";
	
	for (int i = 2 ; i < argc ; ++i) {
		if (strcmp(argv[i], "-p") == 0) {
			port = atoi(argv[++i]);
		} else if (strcmp(argv[i], "-o") == 0) {
			dir = argv[++i];
		} else {
			return new HelpJob();
		}
	}
	
	return new Receiver(port, dir);
}