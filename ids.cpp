/*
 *	DoS Detection tool with libpcap
 *	Version 1.0
 *	MUST-SICT-Network&Security Department
 *	J.IN12D067 G.Bayarkhuu

 *****************************************
 
 * 
 	This tool is for network security developers.
 	Main purpose of the tool is detecting Denial of Service attack.
 	This tool detects DoS attacks by examining packets passed by the machines interface or directed to the machine.
 	Also tool has ability to extract packets like wireshark do.
 *
 *	For security and education purpose only. Source from :
 		* tcpdump.org
 		* stackoverflow.com
 		* binarytides.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pcap.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void process_packet(u_char *, const struct pcap_pkthdr *, const u_char *);

using namespace std;

int main(int argc, char *argv[]){
	//checking required arguments are passed
	if(argc < 2){
		cout << "Missing argument\nUsage : interface" << endl;
		exit(0);
	}

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
	cout << "Incoming" << endl;
}