#include "RawSocketSender.h"
#include <sys/socket.h>
#include <netinet/udp.h>
#include <netinet/ip.h>

using namespace udpninja;

RawSocketSender::RawSocketSender() {
	dest = new sockaddr_in();
	dest->sin_family = AF_INET;
}

RawSocketSender::~RawSocketSender() {
	delete dest;
}

int RawSocketSender::open() {
	socketHandle = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	
	if (socketHandle < 0) {
		return -1;
	}

	int one = 1;
	if (setsockopt(socketHandle, IPPROTO_IP, IP_HDRINCL, &one, sizeof (one)) < 0) {
		return -1;
	}

	return 0;
}

int RawSocketSender::send(IpPacket * packet) {
	
	dest->sin_port = ((udphdr *) (packet->data + sizeof(iphdr)))->dest;
	dest->sin_addr.s_addr = ((iphdr *) (packet->data))->daddr;

	return sendto(socketHandle, packet->data, packet->len, 0, (struct sockaddr *)&dest, sizeof(dest));
}
