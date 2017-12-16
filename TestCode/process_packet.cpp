#include "ids.h"
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>


using namespace std;

unsigned int tcp, udp, icmp, igmp, others, total, intVal, http, https, dns, dhcp, ftp, ssh = 0;
unsigned int packet_max = 0;
string machineAddr = "";
string ifname = "";
struct sockaddr_in dest;

Ids::Ids(){
}

std::string Ids::setProtocol(){
    //data sending function
    int test = freqUp();
    string result = to_string(test) + ",";
    result += to_string(packet_max) + ",";
    result += to_string(http) + ",";
    result += to_string(https) + ",";
    result += to_string(dns) + ",";
    result += to_string(dhcp) + ",";
    result += to_string(ssh) + ",";
    result += to_string(ftp) + ",";
    result += machineAddr + ",";
    result += ifname;
    return result;
}

void Ids::setup(char *ptr){
    //setting up device
    char *dev = ptr, errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL){
      cout << "Couldn't open device : " << dev << " for sniffing..." << endl;
      cout << "Error : " << errbuf << endl;
      exit(1);
    }
    cout << "PCAP:Chosen interface : " << dev << endl;
    ifname = dev;
    //getting IP address of an interface
    int fd;
    struct ifreq ifr;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, dev, IFNAMSIZ - 1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
    machineAddr = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
    cout << "IP Address : " << machineAddr << endl;
    //cout << "ADDRESS : " << inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
    pcap_loop(handle, -1, this->process_packet, NULL);
}

unsigned int Ids::freqUp(){
    unsigned int test;
    test = intVal;
    intVal = 0;
    if(packet_max < test)
      packet_max = test;
    if(test > 100)
      cout << "Warning" << endl;
    //cout << "Maximum interval : " << packet_max << endl;
    cout << "TCP : " << tcp << " UDP : " << udp << " ICMP : " << icmp << " IGMP : " << igmp << " SSH: " << ssh << " FTP: " << ftp << " HTTP : " << http << " HTTPS : " << https << " DNS : " << dns << " DHCP : " << dhcp << " Others : " << others << " Total : " << total << endl;
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
            ext_Udp(buffer, size);
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
    //tcpData tcpd;
    unsigned int dport = ntohs(tcph->dest);
    unsigned int sport = ntohs(tcph->source);
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
    string tmpAddr = inet_ntoa(dest.sin_addr);

    if(!tmpAddr.compare(machineAddr)){
      switch(dport){
          case 80: ++http; break;
          case 443: ++https; break;
          case 53: ++dns; break;
          case 67: ++dhcp; break;
          case 22: ++ssh; break;
          case 20: ++ftp; break;
          case 21: ++ftp; break;
          default: break;
      }
    }
    else {
      switch(sport){
          case 80: ++http; break;
          case 443: ++https; break;
          case 53: ++dns; break;
          case 67: ++dhcp; break;
          case 22: ++ssh; break;
          case 20: ++ftp; break;
          case 21: ++ftp; break;
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

void Ids::ext_Udp(const u_char *Buffer, int Size){
    unsigned short iphdrlen;

    struct iphdr *iph = (struct iphdr *)(Buffer +  sizeof(struct ethhdr));
    iphdrlen = iph->ihl*4;

    struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen  + sizeof(struct ethhdr));

    int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;

    unsigned int dport = ntohs(udph->dest);
    unsigned int sport = ntohs(udph->source);

    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
    string tmpAddr = inet_ntoa(dest.sin_addr);

    if(!tmpAddr.compare(machineAddr)){
        switch(dport){
            case 53: dns++; break;
            default: break;
        }
    }
    else
        switch(sport){
            case 53: dns++; break;
        }


    // fprintf(logfile , "\n\n***********************UDP Packet*************************\n");
    // fprintf(logfile , "\nUDP Header\n");
    // fprintf(logfile , "   |-Source Port      : %d\n" , ntohs(udph->source));
    // fprintf(logfile , "   |-Destination Port : %d\n" , ntohs(udph->dest));
    // fprintf(logfile , "   |-UDP Length       : %d\n" , ntohs(udph->len));
    // fprintf(logfile , "   |-UDP Checksum     : %d\n" , ntohs(udph->check));
    // fprintf(logfile , "\n");
    // fprintf(logfile , "IP Header\n");
    // fprintf(logfile , "UDP Header\n");
    // fprintf(logfile , "Data Payload\n");
}

Ids::~Ids(){
}
