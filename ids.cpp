/*
 *	DoS Detection tool with libpcap
 *	Version 1.0
 *	MUST-SICT-Network&Security Department
 *	J.IN12D067 G.Bayarkhuu

 *****************************************
 
 * 
 	This tool is for network security developers.
 	Main purpose of the tool is detecting Denial of Service attack.
 	This tool detects DoS TCP SynFlood attacks by examining packets passed by the machines interface or directed to the machine.
 	Also tool has ability to extract packets like wireshark do.
 *
 *	For security and education purpose only. Source from :
 		* tcpdump.org
 		* stackoverflow.com
 		* binarytides.com
*/
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

using namespace std;

void process_packet(u_char *, const struct pcap_pkthdr *, const u_char *);

int tcp,udp,icmp,igmp,others,total = 0;

int main(int argc, char *argv[]){
	//checking required arguments are passed
	if(argc < 2){
		cout << "Missing argument\nUsage : interface" << endl;
		exit(0);
	}

	//checking log file. If already created it will write append to existing file. If not it will create a file.


	//getting device name
	char *dev = argv[1], errbuf[PCAP_ERRBUF_SIZE];
	cout << "Chosen interface : " << dev << endl;

	//Creating session handler
	pcap_t *handle;
	handle = pcap_open_live(dev, BUFSIZ, 1, 1, errbuf);
	if (handle == NULL){
		cout << "Can't open interface " << dev << " for sniffing" << endl << "Error : " << errbuf << endl;
		return(2);
	}
	//Looping pcap
	pcap_loop(handle, -1, process_packet, NULL);
	return 0;
}

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer){
	int size = header->len;
    //Getting IP Header
    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    ++total;
    switch (iph->protocol) //Sorting the packets by protocol
    {
        case 1:  //ICMP Protocol
            ++icmp;
            //print_icmp_packet( buffer , size);
            break;
         
        case 2:  //IGMP Protocol
            ++igmp;
            break;
         
        case 6:  //TCP Protocol
            ++tcp;
            //print_tcp_packet(buffer , size);
            break;
         
        case 17: //UDP Protocol
            ++udp;
            //print_udp_packet(buffer , size);
            break;
         
        default: //Some Other Protocol like ARP etc.
            ++others;
            break;
    }
    cout << "TCP: " << tcp << " UDP: " << udp << " ICMP: " << icmp << " IGMP: " << igmp << " Others: " << others << " Total: " << total << "\r";
}