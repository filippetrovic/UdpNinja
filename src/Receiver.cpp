#include "Receiver.h"
#include <iostream>
#include <cstring>
extern "C"
{
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
}

udpninja::Receiver::Receiver() {
	std::cout << "Constructor\n";
}

udpninja::Receiver::~Receiver() {
}

void udpninja::Receiver::doJob() {
         
    unsigned char buffer[65536];
     
//    int sock_raw = socket(AF_PACKET , SOCK_RAW , htons(ETH_P_IP));
    int sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    
	int one = 1;
	const int *val = &one;
	setsockopt (sock_raw, IPPROTO_IP, IP_HDRINCL, val, sizeof (one));
	setsockopt(sock_raw , SOL_SOCKET , SO_BINDTODEVICE , "eth1" , strlen("eth1")+ 1 );
	
    if (sock_raw < 0)
    {
        std::cout << "Socket Error";
        return;
    }
    while(1)
    {
        //Receive a packet
        int data_size = recv(sock_raw , buffer , 65536 , 0);
        if (data_size < 0) {
            std::cout << "Recvfrom error , failed to get packets\n";
            return;
        } else {
			std::cout << "packet received\n" << std::flush;
		}
    }
}