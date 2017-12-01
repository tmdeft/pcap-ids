#include "ids.h"

using namespace std;

unsigned int tcp, udp, icmp, igmp, others, total, intVal, http, https, dns, dhcp = 0;
unsigned int packet_max = 0;

Ids::Ids(){
}

std::string Ids::setProtocol(){
    int test = freqUp();
    string result = to_string(test) + ",";
    result += to_string(packet_max) + ",";
    result += to_string(http) + ",";
    result += to_string(https) + ",";
    result += to_string(dns) + ",";
    result += to_string(dhcp);
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
            ext_Tcp(buffer, size);
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

void Ids::ext_Tcp(const u_char * Buffer, int Size){
    unsigned short iphdrlen;

    struct iphdr *iph = (struct iphdr *)( Buffer  + sizeof(struct ethhdr) );
    iphdrlen = iph->ihl*4;

    struct tcphdr *tcph=(struct tcphdr*)(Buffer + iphdrlen + sizeof(struct ethhdr));

    int header_size =  sizeof(struct ethhdr) + iphdrlen + tcph->doff*4;
    tcpData tcpd;
    //print_ip_header(Buffer,Size);
    unsigned int dport = ntohs(tcph->dest);
    unsigned int sport = ntohs(tcph->source);

    if(tcph->syn == 1){
        switch(dport){
            case 80: ++http; break;
            case 443: ++https; break;
            case 53: ++dns; break;
            case 67: ++dhcp; break;
            default: break;
        }
    }
    // tcpd.sport = ntohs(tcph->source);
    // tcpd.dport = ntohs(tcph->dest);
    // tcpd.seq_num = ntohl(tcph->seq);
    // tcpd.ack_num = ntohl(tcph->ack_seq);
    // tcpd.hdr_length = (unsigned int)tcph->doff * 4;
    // tcpd.urgent_flag = (unsigned int)tcph->urg;
    // tcpd.ack_flag = (unsigned int)tcph->ack;

    // fprintf(logfile , "\n");
    // fprintf(logfile , "TCP Header\n");
    // fprintf(logfile , "   |-Source Port      : %u\n",ntohs(tcph->source));
    // fprintf(logfile , "   |-Destination Port : %u\n",ntohs(tcph->dest));
    // fprintf(logfile , "   |-Sequence Number    : %u\n",ntohl(tcph->seq));
    // fprintf(logfile , "   |-Acknowledge Number : %u\n",ntohl(tcph->ack_seq));
    // fprintf(logfile , "   |-Header Length      : %d DWORDS or %d BYTES\n" ,(unsigned int)tcph->doff,(unsigned int)tcph->doff*4);
    // //fprintf(logfile , "   |-CWR Flag : %d\n",(unsigned int)tcph->cwr);
    // //fprintf(logfile , "   |-ECN Flag : %d\n",(unsigned int)tcph->ece);
    // fprintf(logfile , "   |-Urgent Flag          : %d\n",(unsigned int)tcph->urg);
    // fprintf(logfile , "   |-Acknowledgement Flag : %d\n",(unsigned int)tcph->ack);
    // fprintf(logfile , "   |-Push Flag            : %d\n",(unsigned int)tcph->psh);
    // fprintf(logfile , "   |-Reset Flag           : %d\n",(unsigned int)tcph->rst);
    // fprintf(logfile , "   |-Synchronise Flag     : %d\n",(unsigned int)tcph->syn);
    // fprintf(logfile , "   |-Finish Flag          : %d\n",(unsigned int)tcph->fin);
    // fprintf(logfile , "   |-Window         : %d\n",ntohs(tcph->window));
    // fprintf(logfile , "   |-Checksum       : %d\n",ntohs(tcph->check));
    // fprintf(logfile , "   |-Urgent Pointer : %d\n",tcph->urg_ptr);
    // fprintf(logfile , "\n");
    // fprintf(logfile , "                        DATA Dump                         ");
    // fprintf(logfile , "\n");
    //
    // fprintf(logfile , "IP Header\n");
    // PrintData(Buffer,iphdrlen);
    //
    // fprintf(logfile , "TCP Header\n");
    // PrintData(Buffer+iphdrlen,tcph->doff*4);
    //
    // fprintf(logfile , "Data Payload\n");
    // PrintData(Buffer + header_size , Size - header_size );
    //
    // fprintf(logfile , "\n###########################################################");
}

Ids::~Ids(){
}
