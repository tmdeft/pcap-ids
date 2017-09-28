#ifndef IDS_H
#define IDS_H

#include <pcap.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h> // for exit()
#include <string.h> //for memset
#include <sys/socket.h>
#include <arpa/inet.h> // for inet_ntoa()
#include <net/ethernet.h>
#include <netinet/ip_icmp.h>   //Provides declarations for icmp header
#include <netinet/udp.h>   //Provides declarations for udp header
#include <netinet/tcp.h>   //Provides declarations for tcp header
#include <netinet/ip.h>    //Provides declarations for ip header

class Ids{

	public:
		Ids();
		struct Protocols{
			int tcp;
			int udp;
			int icmp;
			int igmp;
			int total;
			int others;
		};
		void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer, struct Protocols proto);
};

#endif