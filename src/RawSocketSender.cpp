#include "RawSocketSender.h"
#include "ChecksumCalculator.h"
#include <sys/socket.h>
#include <netinet/udp.h>
#include <unistd.h>

using namespace udpninja;

RawSocketSender::RawSocketSender() {
	dest = new sockaddr_in();
	dest->sin_family = AF_INET;
}

RawSocketSender::~RawSocketSender() {
	close(socketHandle);
	delete dest;
}

int RawSocketSender::open() {
	socketHandle = socket(PF_INET, SOCK_RAW, IPPROTO_RAW);
	
	if (socketHandle < 0) {
		return -1;
	}

//	int sendBufferSize = xxxx;
//	if (setsockopt(socketHandle, SOL_SOCKET, SO_SNDBUF, &sendBufferSize, sizeof sendBufferSize) < 0) {
//		return -1;
//	}

	int one = 1;
	if (setsockopt(socketHandle, IPPROTO_IP, IP_HDRINCL, &one, sizeof (one)) < 0) {
		return -1;
	}

	return 0;
}

int RawSocketSender::send(IpPacket * packet) {
	
	iphdr * ipHeader = (iphdr *) (packet->data);
	
	dest->sin_addr.s_addr = ipHeader->daddr;

	ipHeader->check = 0;
	ipHeader->check = ChecksumCalculator::calculateChecksum(ipHeader, ipHeader->ihl * 4);
	
	int status = sendto(socketHandle, packet->data, packet->len, 0, (struct sockaddr *)dest, sizeof(sockaddr_in));
//	if (status < 0) {
//		int sockerr;
//		socklen_t sockerr_size = sizeof sockerr;
//		if (getsockopt (socketHandle, SOL_SOCKET, SO_ERROR, (char *) &sockerr, &sockerr_size) == 0) {
//			std::cout << "socket error: " << sockerr << "\n";
//			std::cout << "socket: " << strerror(errno) << "\n"; // #include <cstring>, <errno.h>
//		}
//	}
	return status < 0;
}
