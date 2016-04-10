#include "ReplaySender.h"
#include <iostream>
#include "IpPacket.h"
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>

#define READ_BINARY_MODE "rb"

using namespace udpninja;

ReplaySender::ReplaySender() {
}

ReplaySender::~ReplaySender() {
	delete outSocket;
	delete inFile;
}

void ReplaySender::sayHello() {
	std::cout << "UdpNinja started in replay mode. ";
	std::cout << "Sending packets from \"" << inputFile << "\" to ";
	std::cout << receiverIp << "/" << ntohs(receiverPort) << ".\n";
}

void ReplaySender::doJob() {
	
	if (prepare() == -1) {
		return;	// error
	}

	IpPacket * packet = new IpPacket();
	in_addr_t destinationIp = inet_addr(receiverIp);

	while (1) {
		
		if (inFile->read(&(packet->len), sizeof(packet->len)) == 0) {
			break;
		}

		inFile->read(packet->data, packet->len);
		
		// set destination address:
		iphdr * ipHeader = (iphdr *) packet->data;
		ipHeader->daddr = destinationIp;
		
		udphdr * udpHeader = (udphdr *)(packet->data + sizeof(iphdr));
		udpHeader->dest = receiverPort;
		udpHeader->check = 0;	// TODO: Calculate udp header checksum.
	
		//std::cout << "src: " << inet_ntoa(*(struct in_addr*) &ipHeader->saddr);
		//std::cout << " dst: " << inet_ntoa(*(struct in_addr*) &ipHeader->daddr);
		//std::cout << " size: " << ntohs(ipHeader->tot_len) << "\n" << std::flush;

		outSocket->send(packet);
	}
	
	inFile->close();
	delete packet;
}

int ReplaySender::prepare() {
	outSocket = new RawSocketSender();

	if (outSocket->open() < 0) {
		std::cout << "Socket Error: Cannot open socket. Be sure you have root privileges\n";
		return -1;
	}
	
	inFile = new File(inputFile, READ_BINARY_MODE);
		
	if (!inFile->isOpen()) {
		std::cout << "Failed to open file " << inputFile << "\n";
		return -1;
	}

	return 0;
}

void ReplaySender::setInputFilename(char* inputFile) {
	this->inputFile = inputFile;
}

void ReplaySender::setReceiver(char* receiver) {
	
	int slashPosition = 0;
	for (int i = 0 ; i < strlen(receiver) ; ++i) {
		if (receiver[i] == '/') {
			slashPosition = i;
			break;
		}
	}
	
	receiverIp = new char [slashPosition + 1];
	strncpy(receiverIp, receiver, slashPosition);
	receiverIp[slashPosition] = '\0';
	
	receiverPort = htons(atoi(receiver + slashPosition + 1));
}

char* ReplaySender::getInputFilename() {
	return inputFile;
}

char* ReplaySender::getReceiverIp() {
	return receiverIp;
}

int ReplaySender::getReceiverPort() {
	return receiverPort;
}