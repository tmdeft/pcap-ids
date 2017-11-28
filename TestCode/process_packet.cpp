#include "ids.h"
#include <time.h>

using namespace std;

unsigned int tcp, udp, icmp, igmp, others, total, intVal = 0;
unsigned int packet_max = 0;
clock_t start_time;

Ids::Ids(){
}

std::string Ids::setProtocol(){
    int test = freqUp();
    string result = to_string(test) + ",";
    result += to_string(packet_max);
    // string datas = "";
    // datas += "{'TCP':'";
    // datas += to_string(tcp);
    // datas += "','UDP':'";
    // datas += to_string(udp);
    // datas += "','ICMP':'";
    // datas += to_string(icmp);
    // datas += "','IGMP':'";
    // datas += to_string(igmp);
    // datas += "','Others':'";
    // datas += to_string(others);
    // datas += "','Total':'";
    // datas += to_string(total);
    // datas += "'}";
    // string result = to_string(tcp) + ",";
    // result += to_string(udp) + ",";
    // result += to_string(icmp) + ",";
    // result += to_string(igmp) + ",";
    // result += to_string(others) + ",";
    // result += to_string(total);
    // cout << "TEST : " << result << endl;
    return result;
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
    start_time = clock();
    pcap_loop(handle, -1, this->process_packet, NULL);
}

unsigned int Ids::freqUp(){
    unsigned int test;
    test = intVal;
    intVal = 0;
    if(packet_max < test)
      packet_max = test;
    cout << "Maximum interval : " << packet_max << endl;
    return test;
}

void Ids::process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer){
    int size = header->len;
    //Get the IP Header part of this packet , excluding the ethernet header
    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    ++total;
    ++intVal;
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
    //cout << "PCAP: TCP:" << tcp << " UDP:" << udp << " ICMP:" << icmp << " IGMP:" << igmp << " Others:" << others << " Total:" << total << "\r";
}

Ids::~Ids(){
}
