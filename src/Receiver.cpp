#include "Receiver.h"
#include <iostream>
#include <cstring>
#include <netinet/ip.h>
#include <arpa/inet.h>

using namespace udpninja;

Receiver::Receiver() {
	port = DEFAULT_PORT;
	dir = new char[strlen(DEFAULT_OUTPUT_DIR) + 1];
	strcpy(dir, DEFAULT_OUTPUT_DIR);
}

Receiver::~Receiver() {
	delete dir;
	delete inSocket;
	outputFile->close();
	delete outputFile;
}

void Receiver::doJob() {

	if (prepare() == -1) {
		return;	// error
	}

	while(1) {
		//Receive a packet
		IpPacket * packet = inSocket->read();
		outputFile->checkForNewFile();

		if (packet->len <= 0) {	// timeout or error
			if (packet->len < 0) { // error
				std::cout << "Socket Error: Failed to read from socket.\n";
				return;
			}
		} else {
			iphdr * ipHeader = (iphdr *) packet->data;
			
			outputFile->write(&(packet->len), sizeof(packet->len));
			outputFile->write(packet->data, packet->len);

//			TODO: add verbose parameter and log to console.
//			std::cout << inet_ntoa(*(struct in_addr*) &ipHeader->saddr);
//			std::cout << " " << ntohs(ipHeader->tot_len) << "\n" << std::flush;
		}
	}
}

int Receiver::prepare() {
	
	inSocket = new RawSocket(port);

	if (inSocket->open() < 0) {
		std::cout << "Socket Error: Cannot open socket. Be sure you have root privileges\n";
		return -1;
	}
	

	outputFile = new FileSplitter(dir);

	if (!outputFile->isOpen()) {
		std::cout << "File Error: Failed to open file. Be sure you have root privileges\n";
		return -1;
	}
	
	return 0;
}

void Receiver::sayHello() {
	std::cout << "UdpNinja started in record mode. "; 
	std::cout << "Listening on port " << port << ". "; 
	std::cout << "Output dir is \"" << dir << "\".\n";
}

void Receiver::setDir(char* dir) {
	delete this->dir;

	this->dir = new char[strlen(dir) + 1];
	strcpy(this->dir, dir);	
}

char* Receiver::getDir() {
	return dir;
}

void Receiver::setPort(unsigned int port) {
	this->port = port;
}

unsigned int Receiver::getPort() {
	return port;
}