#include "ReplaySender.h"
#include <iostream>
#include "IpPacket.h"

using namespace udpninja;

ReplaySender::ReplaySender() {
}

ReplaySender::~ReplaySender() {
}

void ReplaySender::sayHello() {
	std::cout << "UdpNinja started in replay mode.";
	std::cout << "\n";
}

void ReplaySender::doJob() {
	
	if (prepare() == -1) {
		return;	// error
	}

	IpPacket * packet = new IpPacket();
	packet->len = 29;
	packet->data = new unsigned char[29];

	outSocket->send(packet);
}

int ReplaySender::prepare() {
	outSocket = new RawSocketSender();

	if (outSocket->open() < 0) {
		std::cout << "Socket Error: Cannot open socket. Be sure you have root privileges\n";
		return -1;
	}
	
	return 0;
}