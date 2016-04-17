#include "ChecksumCalculator.h"
#include <netinet/udp.h>

#include <iostream>

using namespace udpninja;

ChecksumCalculator::ChecksumCalculator() {
}

ChecksumCalculator::~ChecksumCalculator() {
}

uint32_t ChecksumCalculator::sum(void * buf, size_t buf_len, uint32_t start) {
	uint16_t * pointer = (uint16_t *) buf;
	while (buf_len > 1) {
		start += *pointer++;
		if (start & 0x80000000) {
			start = (start & 0xFFFF) + (start >> 16);
		}
		buf_len -= 2;
	}

	if (buf_len > 0) {
		start += *((uint8_t *) pointer);
	}
	return start;
}

uint16_t ChecksumCalculator::fold(uint32_t sum) {
	while (sum >> 16) {
		sum = (sum & 0xFFFF) + (sum >> 16);
	}
	
	return ~sum;
}

uint16_t ChecksumCalculator::calculateChecksum(void * buf, size_t buf_len) {
	return fold(sum(buf, buf_len, 0));
}

uint16_t ChecksumCalculator::calculateUdpChecksum(iphdr * ipHeader) {
	IPv4PseudoHeader * pseudoHeader = new IPv4PseudoHeader();
	
	udphdr * udpHeader = (udphdr *)((char *)ipHeader + sizeof(iphdr));
	udpHeader->check = 0;
	
	pseudoHeader->sourceIp = ipHeader->saddr;
	pseudoHeader->destIp = ipHeader->daddr;
	pseudoHeader->protocol = ipHeader->protocol;
	pseudoHeader->udpLength = udpHeader->len;

	uint16_t tempChecksum = sum(pseudoHeader, sizeof(IPv4PseudoHeader), 0);
	delete pseudoHeader;
	return fold(sum(udpHeader, ntohs(udpHeader->len), tempChecksum)) - 1; // -1?
}
