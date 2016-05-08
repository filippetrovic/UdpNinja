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
	std::cout << "Usage: udpninja <mode> [ <options>... ]\n";

	// record mode
	std::cout << SMALL_TAB << "mode:\n";
	std::cout << SMALL_TAB << SMALL_TAB;
	std::cout << "-record \t Record UDP packets to file.\n";
	std::cout << SMALL_TAB << "options:\n";
	std::cout << SMALL_TAB << SMALL_TAB;
	std::cout <<  "-p <port> \t Set UDP port on which to listen for\n";
	std::cout << SMALL_TAB << SMALL_TAB << "\t\t " << "incoming packets. (default 2055)\n";
	std::cout << SMALL_TAB << SMALL_TAB;
	std::cout << "-o <dir> \t Set directory in which to store files. (default /tmp)\n";

	// replay mode
	std::cout << "\n";
	std::cout << SMALL_TAB << "mode:\n";
	std::cout << SMALL_TAB << SMALL_TAB;
	std::cout << "-replay \t Send UDP packets from file to network.\n";
	std::cout << SMALL_TAB << "options:\n";
	std::cout << SMALL_TAB << SMALL_TAB;
	std::cout <<  "-i <file> \t Input file\n";
	std::cout << SMALL_TAB << SMALL_TAB;
	std::cout <<  "-r <ip/port> \t Receiver in format ip_address/port\n";
	std::cout << SMALL_TAB << SMALL_TAB;
	std::cout <<  "-c \t\t Set UDP header checksum to 0.\n";
	std::cout << SMALL_TAB << SMALL_TAB << "\t\t " << "Use this if you care about performance.\n";

	std::cout << "\n";
}
