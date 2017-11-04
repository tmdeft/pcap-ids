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
 *	Functions :
 		* Initialize pcap function to sniff interface.
 		* Connect to MySQL for data store.
 		* Sorting packets by protocol.
 		* Catching TCP packets for Intrusion Detection.
 		* Checking TCP packets.
 		* Alert if intrusion detected.
 		* Write data to MySQL.
*/

#include "ids.h"
#include <pcap.h>
#include <pthread.h>

using namespace std;

void *Prep(void *arg){
		char *dev;
		dev = (char*)arg;
		cout << "Passed argument : " << dev << endl;
		char errbuf[PCAP_ERRBUF_SIZE];
		pcap_t *handle;
		handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
		if (handle == NULL){
			cout << "Can't open interface : " << dev << " for sniffing" << endl;
			cout << "Error : " << errbuf << endl;
			exit(1);
		}
		pcap_loop(handle, -1, Ids::process_packet, NULL);
}

int main(int argc, char *argv[]){
	if (argc < 2){
		cout << "Missing argument\nUsage: interface" << endl;
		exit(2);
	}
	else if (argc > 2){
		cout << "Wrong Usage\nUsage: interface" << endl;
		exit(2);
	}
	//Creating thread...
	pthread_t loopThread;
	int prep;
	const char *dev = argv[1];
	prep = pthread_create(&loopThread, NULL, Prep, (void*)dev);
	if (prep){
		cout << "Error unable to create thread : " << prep << endl;
		exit(1);
	}
	pthread_join(loopThread, NULL);
	
	return 0;
}
