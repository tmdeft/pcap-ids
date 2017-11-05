#include "ids.h"

using namespace std;

Ids::Ids(){
    this->tcp = 1;
    this->udp = 1;
    this->icmp = 1;
    this->igmp = 1;
    this->others = 1;
    this->total = 1;
    cout << "Entering IDS" << endl;
}

void Ids::setup(char *ptr){
    char *dev = ptr, errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL){
      cout << "Couldn't open device : " << dev << " for sniffing..." << endl;
      cout << "Error : " << errbuf << endl;
      exit(1);
    }
    cout << "Chosen interface : " << dev << endl;
}

void Ids::process_packet(){
    cout << "Processing packet" << endl;
    cout << "TCP : " << this->tcp << " UDP : " << this->udp << " ICMP : " << this->icmp << " IGMP : " << this->igmp << " Others : " << this->others << " Total : " << this->total << endl;
}

Ids::~Ids(){
    cout << "Exiting IDS" << endl;
}
