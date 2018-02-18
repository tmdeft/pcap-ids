#ifndef IDS_H
#define IDS_H

#include <pcap.h>
#include <iostream>
#include <stdio.h>
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
    void insertData(std::string, std::string, unsigned int);
    void addData();
    void selectData();
  private:
    std::string dbUser = "ids";
    std::string dbPass = "QWEasd";
    std::string dbBase = "ids";
    std::string dbHost = "localhost";
};

class Ids{
  public:
    Ids();
    ~Ids();
    std::string getIp();
    unsigned int getPort();
    std::string getMac();
    void setup(char *);
    std::string setProtocol();
    static void process_packet(u_char *, const struct pcap_pkthdr *, const u_char *);
    static void ext_Tcp(const u_char *, int);
    static void ext_Udp(const u_char *, int);
    void writeData();
    unsigned int freqUp();
    struct tcpData{
        unsigned int sport;
        unsigned int dport;
        unsigned int seq_num;
        unsigned int ack_num;
        unsigned int hdr_length;
        unsigned int urgent_flag;
        unsigned int ack_flag;
        unsigned int push_flag;
        unsigned int reset_flag;
        unsigned int syn_flag;
        unsigned int fin_flag;
        unsigned int window_size;
        unsigned int checksum;
        unsigned int urgent_pointer;
    };
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
