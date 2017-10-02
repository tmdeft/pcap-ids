#include "ids.h"

int total, icmp, igmp, tcp, udp, others = 0;

using namespace std;

#define DBHOST "localhost"
#define DBUSER "ids_user"
#define DBPASS "QWEasd"
#define DBBASE "ids"

sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;

Ids::Ids(){
}

void sql_connection(){

}

void Ids::process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer){
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

Ids::~Ids(){
	cout << "Bye!" << endl;
	exit(2);
}