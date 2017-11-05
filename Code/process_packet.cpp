#include "ids.h"
#include <ctime>
#include <iostream>

using namespace std;

bool sqlState = false;
unsigned int tmpTcp, tmpUdp, tmpIcmp, tmpOthers, tmpIgmp, tmpTotal = 0;

Ids::Ids(){
}

void Ids::process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer){
	Ids ids;

	if (sqlState == false){
		ids.sql_connection();
		sqlState = true;
	}

	int size = header->len;
    //Getting IP Header
    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    tmpTotal ++;
    switch (iph->protocol) //Sorting the packets by protocol
    {
        case 1:  //ICMP Protocol
						tmpIcmp ++;
            //print_icmp_packet( buffer , size);
            break;

        case 2:  //IGMP Protocol
            tmpIgmp ++;
            break;

        case 6:  //TCP Protocol
            tmpTcp ++;
            //print_tcp_packet(buffer , size);
            break;

        case 17: //UDP Protocol
            tmpUdp ++;
            //print_udp_packet(buffer , size);
            break;

        default: //Some Other Protocol like ARP etc.
            tmpOthers ++;
            break;
    }
    cout << "TCP: " << tmpTcp << " UDP: " << tmpUdp << " ICMP: " << tmpIcmp << " IGMP: " << tmpIgmp << " Others: " << tmpOthers << " Total: " << tmpTotal << "\r";
    ids.add_db(tmpTcp, tmpUdp, tmpOthers, tmpTotal, tmpIcmp, tmpIgmp);
}

std::string Ids::getRes(){
		string data = "";
		data += "{'TCP':'";
		data += to_string(tmpTcp);
		data += "','UDP':'";
		data += to_string(tmpUdp);
		data += "','ICMP':'";
		data += to_string(tmpIcmp);
		data += "','IGMP':'";
		data += to_string(tmpIgmp);
		data += "','Others':'";
		data += to_string(tmpOthers);
		data += "','Total':'";
		data += to_string(tmpTotal);
		data += "'}";
		return data;
}

Ids::~Ids(){
	//cout << "Total packets captured by this session : " << total <<endl;
}
