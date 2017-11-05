#ifndef IDS_H
#define IDS_H

#include <pcap.h>
#include <iostream>
#include <stdio.h>
#include <string>
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
		unsigned int tcp, udp, others, total, icmp, igmp = 0;
		Ids();
		~Ids();
		static void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer);
		void sql_connection();
		void add_db(int tcp, int udp, int others, int total, int icmp, int igmp);
		std::string getRes();
};
class Data{
	public:
		Data();
		void getData();
		~Data();
};

#endif
