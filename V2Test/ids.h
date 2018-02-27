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

class MainProcess {
    private:
    public:
        struct sqlData{
            unsigned int port;
            std::string ipAddress;
        };
        MainProcess();
        ~MainProcess();
        void setup(char *ptr);
        std::string getIp();
        unsigned int getPort();
        std::string getMac();
        static void process_packet(u_char *, const struct pcap_pkthdr *, const u_char *);
        static void ext_Udp(const u_char *Buffer, int Size);
        static void ext_Tcp(const u_char * Buffer, int Size);
        unsigned int freqUp();
        void setCounter();
        std::string getSocketData();
        unsigned int * getPortArr();
};

class Database : public  MainProcess{
    private:
        std::string dbUser = "ids";
        std::string dbPass = "QWEasd";
        std::string dbBase = "ids";
        std::string dbHost = "localhost";
    public:
        Database();
        ~Database();
        bool connect();
        void insert();
        void checkTable();
};

class SocketData : public MainProcess{
    public:
        SocketData();
        ~SocketData();
        void setSocket();
        std::string getData();
        std::string getPortData();
};



#endif
