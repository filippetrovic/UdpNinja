#include "RawSocketReceiver.h"
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <errno.h>

using namespace udpninja;

RawSocketReceiver::RawSocketReceiver(unsigned int port){
	this->port = port;
	packet = new IpPacket();
}

RawSocketReceiver::~RawSocketReceiver(){
	delete packet;
	close(socketHandle);
}

int RawSocketReceiver::open() {
	socketHandle = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	
	if (socketHandle < 0) {
		return -1;
	}

	int one = 1;
	if (setsockopt(socketHandle, IPPROTO_IP, IP_HDRINCL, &one, sizeof (one)) < 0) {
		return -1;
	}
	
	timeval tv;
	tv.tv_sec = 20;	// socket timeout in seconds
	tv.tv_usec = 0;

	if (setsockopt(socketHandle, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(timeval)) < 0) {
		return -1;
	}

//	TODO: should we bind socket to device?
//	if (setsockopt(socketHandle , SOL_SOCKET , SO_BINDTODEVICE , "eth1" , strlen("eth1") + 1 ) < 0) {
//		return -1;
//	}

	return 0;
}

IpPacket * RawSocketReceiver::read() {
	while (1) {	//	wait for packet on defined port.
		errno = 0;
		packet->len = recv(socketHandle , packet->data , 65536 , 0);
		
		if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {	//	timeout
			packet->len = 0;
			return packet;
		}

		if (packet->len < 0) {	//	error handling
			return packet;
		}

		udphdr * udpHeader = (udphdr *) (packet->data + sizeof(iphdr));	//	udp header is just after ip header.
		if (port == ntohs(udpHeader->dest)) {
			return packet;
		}
	}
}

unsigned int RawSocketReceiver::getPort() {
	return port;
}
