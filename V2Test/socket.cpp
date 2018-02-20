#include "ids.h"

#define TPORT 5555

using namespace std;

MainProcess mp;

SocketData::SocketData(){
    cout << "S" << endl;
}

SocketData::~SocketData(){
    cout << "~S" << endl;
}


void error(const char *msg){
	perror(msg);
	exit(1);
}

std::string SocketData::getData(){
    string result;
    result = mp.getSocketData();
    return result;
}

void SocketData::setSocket(){
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[1024];
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
    while(1){
      newsockfd = accept(sockfd,
          (struct sockaddr *) &cli_addr,
          &clilen);
      if (newsockfd < 0)
          error("ERROR on accept");
      bzero(buffer,256);
      n = read(newsockfd,buffer,255);
      if (n < 0) error("ERROR reading from socket");
      string data = getData();
      n = write(newsockfd,data.data(),data.size());
      if (n < 0) error("ERROR writing to socket");
    }
}
