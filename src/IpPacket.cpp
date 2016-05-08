#include "IpPacket.h"


using namespace udpninja;

IpPacket::IpPacket() {
	data = new unsigned char [65536];
}

IpPacket::~IpPacket() {
	delete data;
}