#ifndef IDS_H
#define IDS_H

#include <pcap.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h> // for exit()
#include <string.h> //for memset
#include <sys/socket.h>
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
    void connect();
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
    void process_packet();
    void ext_Tcp();
    void ext_Udp();
    void writeData();
    unsigned int tcp, udp, icmp, others, total, igmp;
};

class Socket{
  public:
    Socket();
    ~Socket();
    void getData();
    void sendData();
  private:
    Ids ids;
};

#endif
