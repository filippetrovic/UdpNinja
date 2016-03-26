#include <cstdlib>
#include <iostream>
#include "Receiver.h"
using namespace udpninja;

int main(int argc, char **argv) {
	
	Receiver * r = new Receiver();
	r->doJob();

}