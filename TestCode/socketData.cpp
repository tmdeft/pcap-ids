#include "ids.h"

using namespace std;

Socket::Socket(){
    cout << "Entering socket program" << endl;
}

Socket::~Socket(){
    cout << "Leaving socket program" << endl;
}

void Socket::getData(){
    cout << "TCP:" << ids.tcp << " UDP:" << ids.udp << " ICMP:" << ids.icmp << " IGMP:" << ids.igmp << " Others:" << ids.others << " Total:" << ids.total << endl;
}
