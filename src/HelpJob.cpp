#include "HelpJob.h"
#include <iostream>

using namespace udpninja;

#define VERSION "0.1"
#define SMALL_TAB "  "

HelpJob::HelpJob() {
}

HelpJob::~HelpJob() {
}

void HelpJob::doJob() {
	//	nothing here.
}

void HelpJob::sayHello() {
	std::cout << "UdpNinja version " << VERSION << "\n";
	std::cout << "Usage: udpninja mode [options]\n";
	std::cout << SMALL_TAB << "mode:\n";
	std::cout << SMALL_TAB << SMALL_TAB;
	std::cout << "-record \t Record UDP packets to file.\n";
	std::cout << SMALL_TAB << "options:\n";
	std::cout << SMALL_TAB << SMALL_TAB;
	std::cout <<  "-p <port> \t Set UDP port on which to listen for incoming packets.\n";
	std::cout << SMALL_TAB << SMALL_TAB;
	std::cout << "-o <dir> \t Set dir in which to store files. (default /tmp)\n";
}