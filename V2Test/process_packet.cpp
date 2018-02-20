#include "ids.h"
#include <pcap.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>

using namespace std;

string ifname = "";
string machineAddr = "";
string attackerIp = "";
char attackerMac[200];
unsigned int attackerPort = 0;
unsigned int total, icmp, igmp, tcp, udp, intVal, others, currentCnt, attackCount = 0;
unsigned int dns, dhcp, ftp, http, https, ssh, packet_max = 0;
struct sockaddr_in dest,source;

MainProcess::MainProcess(){
}

MainProcess::~MainProcess(){
}

std::string MainProcess::getSocketData(){
    string result;
    unsigned int freqTest = freqUp();
    result = to_string(freqTest) + ",";
    result += to_string(packet_max) + ",";
    result += to_string(http) + ",";
    result += to_string(https) + ",";
    result += to_string(dns) + ",";
    result += machineAddr + ",";
    result += ifname + ",";
    result += to_string(attackCount) + ",";
    result += to_string(attackCount) + ",";
    if(attackerIp == "")
      result += "Failed to retrieve IP address";
    else
      result += attackerIp;
    return result;
    attackCount = 0;
}

void MainProcess::setCounter(){
    attackCount ++;
}

unsigned int MainProcess::freqUp(){
    currentCnt = intVal;
    intVal = 0;
    if(packet_max < currentCnt)
        packet_max = currentCnt;
    cout << "Total : " << total << "\nInterval : " << currentCnt << endl;
    return currentCnt;
}

std::string MainProcess::getIp(){
    if (attackerIp != "")
      return attackerIp;
    else return "Failed to retrieve IP Address";
}

unsigned int MainProcess::getPort(){
    return attackerPort;
}

std::string MainProcess::getMac(){
    if (string(attackerMac) != "")
      return string(attackerMac);
    else return "Failed to retrieve MAC Address";
}

void MainProcess::setup(char *ptr){
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

void MainProcess::process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer){
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
}

void MainProcess::ext_Tcp(const u_char * Buffer, int Size){
    struct ethhdr *eth = (struct ethhdr *)Buffer;
    unsigned short iphdrlen;
    struct iphdr *iph = (struct iphdr *)( Buffer  + sizeof(struct ethhdr) );
    iphdrlen = iph->ihl*4;
    struct tcphdr *tcph=(struct tcphdr*)(Buffer + iphdrlen + sizeof(struct ethhdr));
    int header_size =  sizeof(struct ethhdr) + iphdrlen + tcph->doff*4;
    unsigned int dport = ntohs(tcph->dest);
    unsigned int sport = ntohs(tcph->source);
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
    if(currentCnt > 300){
      switch(dport){
          case 80: attackerIp = inet_ntoa(source.sin_addr); attackerPort = 80; sprintf(attackerMac, "%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5]); break;
          case 443: attackerIp = inet_ntoa(source.sin_addr); attackerPort = 443; sprintf(attackerMac, "%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5]); break;
          case 53: attackerIp = inet_ntoa(source.sin_addr); attackerPort = 53; sprintf(attackerMac, "%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5]); break;
      }
    }
    if(tcph->syn == 1){
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
    else if (tcph->ack == 1){
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
}

void MainProcess::ext_Udp(const u_char *Buffer, int Size){
    unsigned short iphdrlen;

    struct iphdr *iph = (struct iphdr *)(Buffer +  sizeof(struct ethhdr));
    iphdrlen = iph->ihl*4;

    struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen  + sizeof(struct ethhdr));

    int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;

    unsigned int dport = ntohs(udph->dest);
    unsigned int sport = ntohs(udph->source);

    switch(dport){
        case 53: ++dns; break;
    }
}
