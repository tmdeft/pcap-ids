#include "ids.h"

using namespace std;

bool sqlState = false;

Ids::Ids(){
}

void Ids::process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer){
	Ids ids;

	cout << ids.icmp << ids.total << ids.igmp << ids.tcp << ids.udp ;

	if (sqlState == false){
		ids.sql_connection();
		sqlState = true;
	}

	int size = header->len;
    //Getting IP Header
    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    ids.total ++;
    switch (iph->protocol) //Sorting the packets by protocol
    {
        case 1:  //ICMP Protocol
        	ids.icmp ++;
            //print_icmp_packet( buffer , size);
            break;
         
        case 2:  //IGMP Protocol
            ids.igmp ++;
            break;
         
        case 6:  //TCP Protocol
            ids.tcp ++;
            //print_tcp_packet(buffer , size);
            break;
         
        case 17: //UDP Protocol
            ids.udp ++;
            //print_udp_packet(buffer , size);
            break;
         
        default: //Some Other Protocol like ARP etc.
            ids.others ++;
            break;
    }
    cout << "TCP: " << ids.tcp << " UDP: " << ids.udp << " ICMP: " << ids.icmp << " IGMP: " << ids.igmp << " Others: " << ids.others << " Total: " << ids.total << "\r";
    ids.add_db(ids.tcp, ids.udp, ids.others, ids.total, ids.icmp, ids.igmp);
}

Ids::~Ids(){
	//cout << "Total packets captured by this session : " << total <<endl;
}