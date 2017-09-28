#include "ids.h"

using namespace std;

Ids Ids;

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer, struct Ids::Protocols *proto){
	int size = header->len;
    //Getting IP Header
    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    ++proto->total;
    switch (iph->protocol) //Sorting the packets by protocol
    {
        case 1:  //ICMP Protocol
            ++proto->icmp;
            //print_icmp_packet( buffer , size);
            break;
         
        case 2:  //IGMP Protocol
            ++proto->igmp;
            break;
         
        case 6:  //TCP Protocol
            ++proto->tcp;
            //print_tcp_packet(buffer , size);
            break;
         
        case 17: //UDP Protocol
            ++proto->udp;
            //print_udp_packet(buffer , size);
            break;
         
        default: //Some Other Protocol like ARP etc.
            ++proto->others;
            break;
    }
    cout << "TCP: " << proto->tcp << " UDP: " << proto->udp << " ICMP: " << proto->icmp << " IGMP: " << proto->igmp << " Others: " << proto->others << " Total: " << proto->total << "\r";
}