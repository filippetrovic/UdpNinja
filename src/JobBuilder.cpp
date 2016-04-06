#include "JobBuilder.h"
#include "Receiver.h"
#include "ReplaySender.h"
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
	} else if (strcmp(mode, "-replay") == 0) {
		return createReplayJob();
	}
	
	return new HelpJob();
}

Job* JobBuilder::createReceiver() {
	Receiver * receiver = new Receiver();
	
	for (int i = 2 ; i < argc ; ++i) {
		if (strcmp(argv[i], "-p") == 0) {
			receiver->setPort(atoi(argv[++i]));
		} else if (strcmp(argv[i], "-o") == 0) {
			receiver->setDir(argv[++i]);
		} else {
			delete receiver;
			return new HelpJob();
		}
	}
	
	return receiver;
}

Job* JobBuilder::createReplayJob() {
	ReplaySender * replaySender = new ReplaySender();
	
	return replaySender;
}