#pragma once

#include <netinet/ip.h>

namespace udpninja
{

struct IPv4PseudoHeader {
	IPv4PseudoHeader() {
		zeroes = 0;
	}

	u_int32_t sourceIp;
    u_int32_t destIp;
    u_int8_t zeroes;
    u_int8_t protocol;
    u_int16_t udpLength;
};

class ChecksumCalculator {
public:
	ChecksumCalculator();
	~ChecksumCalculator();

	static uint16_t calculateChecksum(void * buf, size_t buf_len);
	static uint16_t calculateUdpChecksum(iphdr * ipHeader);

private:
	static uint32_t sum(void * buf, size_t buf_len, uint32_t sum);
	static uint16_t fold(uint32_t sum);
};

}

