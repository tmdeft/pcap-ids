#ifndef IDS_H
#define IDS_H

#include <pcap.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h> // for exit()
#include <string.h> //for memset
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h> // for inet_ntoa()
#include <net/ethernet.h>
#include <netinet/ip_icmp.h>   //Provides declarations for icmp header
#include <netinet/udp.h>   //Provides declarations for udp header
#include <netinet/tcp.h>   //Provides declarations for tcp header
#include <netinet/ip.h>    //Provides declarations for ip header

class Sql {
  public:
    Sql();
    ~Sql();
    bool connect();
    void insertData();
    void addData();
    void selectData();
  private:
    std::string dbUser = "ids";
    std::string dbPass = "QWEasd";
    std::string dbBase = "IDS";
    std::string dbHost = "localhost";
};

class Ids{
  public:
    Ids();
    ~Ids();
    void setup(char *);
    std::string setProtocol();
    void initData();
    static void process_packet(u_char *, const struct pcap_pkthdr *, const u_char *);
    void ext_Tcp();
    void ext_Udp();
    void writeData();
    unsigned int freqUp();
    //unsigned int tcp, udp, icmp, others, total, igmp;
};

class Socket{
  public:
    Socket();
    ~Socket();
    std::string getData();
    void sendData();
    void startSock();
  private:
    Ids ids;
};

#endif
