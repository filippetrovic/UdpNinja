#include "Receiver.h"
#include "RawSocket.h"
#include "FileSplitter.h"
#include <iostream>

#include <netinet/ip.h>
#include <arpa/inet.h>

using namespace udpninja;

Receiver::Receiver(unsigned int port) {	
	inSocket = new RawSocket(port);
}

Receiver::~Receiver() {
	delete inSocket;
}

void Receiver::doJob() {

	if (inSocket->open() < 0) {
		std::cout << "Socket Error: Cannot open socket. Be sure you have root privileges\n";
		return;
	}

	FileSplitter * outputFile = new FileSplitter();
	
	if (!outputFile->isOpen()) {
		std::cout << "File Error: Failed to open file. Be sure you have root privileges\n";
		return;
	}

	while(1) {
		//Receive a packet
		IpPacket * packet = inSocket->read();
		if (packet->len < 0) {
			std::cout << "Socket Error: Failed to read from socket.\n";
			return;
		} else {
			iphdr * ipHeader = (iphdr *) packet->data;
			
			outputFile->write(&(packet->len), sizeof(packet->len));
			outputFile->write(packet->data, packet->len);
			outputFile->checkForNewFile();
//			TODO: add verbose parameter and log to console.
//			std::cout << inet_ntoa(*(struct in_addr*) &ipHeader->saddr);
//			std::cout << " " << ntohs(ipHeader->tot_len) << "\n" << std::flush;
		}
	}
}