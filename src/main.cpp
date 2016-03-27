#include <cstdlib>
#include <iostream>
#include "Receiver.h"
using namespace udpninja;

int main(int argc, char **argv) {
	
	unsigned int port = atoi(argv[1]);

	Receiver * r = new Receiver(port);
	r->doJob();
	delete r;

}