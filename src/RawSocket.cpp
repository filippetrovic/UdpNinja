#include "RawSocket.h"
#include <sys/socket.h>
#include <netinet/ip.h>
#include <cstring>
#include <unistd.h>
#include <netinet/udp.h>
#include <netinet/ip.h>

using namespace udpninja;

IpPacket::IpPacket() {
	data = new unsigned char [65536];
}

IpPacket::~IpPacket() {
	delete data;
}

RawSocket::RawSocket(unsigned int port){
	this->port = port;
	packet = new IpPacket();
}

RawSocket::~RawSocket(){
	delete packet;
	close(socketHandle);
}

int RawSocket::open() {
	socketHandle = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	
	if (socketHandle < 0) {
		return -1;
	}

	int one = 1;
	if (setsockopt(socketHandle, IPPROTO_IP, IP_HDRINCL, &one, sizeof (one)) < 0) {
		return -1;
	}
	
//	TODO: should we bind socket to device?
//	if (setsockopt(socketHandle , SOL_SOCKET , SO_BINDTODEVICE , "eth1" , strlen("eth1") + 1 ) < 0) {
//		return -1;
//	}

	return 0;
}

IpPacket * udpninja::RawSocket::read() {
	while (1) {	//	wait for packet on defined port.
		packet->len = recv(socketHandle , packet->data , 65536 , 0);
			
		if (packet->len < 0) {
			return packet;	//	error handling.
		}

		udphdr * udpHeader = (udphdr *) (packet->data + sizeof(iphdr));	//	udp header is just after ip header.
		if (port == ntohs(udpHeader->dest)) {
			return packet;
		}
	}
}

