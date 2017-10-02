#include "ids.h"
#include <pcap.h>

using namespace std;

int main(int argc, char *argv[]){
	if (argc < 2){
		cout << "Missing argument\nUsage: interface" << endl;
		exit(2);
	}
	else if (argc > 2){
		cout << "Wrong Usage\nUsage: interface" << endl;
		exit(2);
	}
	char *dev = argv[1], errbuf[PCAP_ERRBUF_SIZE];
	cout << "Chosen interface: " << dev << endl;

	//Creating session handler...
	pcap_t *handle;
	handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
	if (handle == NULL){
		cout << "Can't open interface: " << dev << " for sniffing." << endl;
		cout << "Error: " << errbuf << endl;
		exit(2);
	}

	//Looping pcap
	pcap_loop(handle, -1, Ids::process_packet, NULL);

	return 0;
}