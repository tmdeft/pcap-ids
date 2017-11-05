#include "ids.h"

using namespace std;

Socket::Socket(){
    //cout << "Entering socket program" << endl;
}

Socket::~Socket(){
    //cout << "Leaving socket program" << endl;
}

void error(const char *msg){
	perror(msg);
	exit(1);
}

std::string Socket::getData(){
    Ids ids;
    string res;
    res = ids.setProtocol();
    return res;
    //cout << "TCP:" << ids.tcp << " UDP:" << ids.udp << " ICMP:" << ids.icmp << " IGMP:" << ids.igmp << " Others:" << ids.others << " Total:" << ids.total << endl;
}

void Socket::startSock(){
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi("5555");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
        sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
        (struct sockaddr *) &cli_addr,
        &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    string data = getData();
    n = write(newsockfd,data.data(),data.size());
    if (n < 0) error("ERROR writing to socket");
}
