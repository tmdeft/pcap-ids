#include "ids.h"

using namespace std;

unsigned int tcp, udp, icmp, igmp, others, total = 0;

Ids::Ids(){
      // this->tcp = 0;
      // this->udp = 0;
      // this->icmp = 0;
      // this->igmp = 0;
      // this->others = 0;
      // this->total = 0;
      // cout << "Initialized Datas" << endl;
}

std::string Ids::setProtocol(){
    string datas = "";
    datas += "{'TCP':'";
    datas += to_string(tcp);
    datas += "','UDP':'";
    datas += to_string(udp);
    datas += "','ICMP':'";
    datas += to_string(icmp);
    datas += "','IGMP':'";
    datas += to_string(igmp);
    datas += "','Others':'";
    datas += to_string(others);
    datas += "','Total':'";
    datas += to_string(total);
    datas += "'}";
    cout << "TEST : " << datas << endl;
    return datas;
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
    cout << "PCAP:Chosen interface : " << dev << endl;
    pcap_loop(handle, -1, this->process_packet, NULL);
}

void Ids::process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer){
    int size = header->len;
    //Get the IP Header part of this packet , excluding the ethernet header
    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    ++total;
    switch (iph->protocol) //Check the Protocol and do accordingly...
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
    cout << "PCAP: TCP:" << tcp << " UDP:" << udp << " ICMP:" << icmp << " IGMP:" << igmp << " Others:" << others << " Total:" << total << "\r";
}

Ids::~Ids(){
}
