#include "ids.h"

using namespace std;
using namespace sql::mysql;

#define DBHOST "localhost"
#define DBUSER "ids"
#define DBPASS "QWEasd"
#define DBBASE "IDS"

int total, icmp, igmp, tcp, udp, others = 0;
bool dbCon = false;

sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;

Ids::Ids(){
}

void Ids::sql_connection(void){
	cout << "Connecting to MySQL database..." << endl;
	try {
		driver = get_mysql_driver_instance();
		con = driver->connect(DBHOST, DBUSER, DBPASS);
		con->setSchema(DBBASE);
		if (!con->isValid()) {
			cout << "Connection failed" << endl;
			exit(1);
		}
		else {
			cout << "MySQL Connection success" << endl;
			dbCon = true;
		}
	} catch (sql::SQLException &e){
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << "(MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << ")" << endl;
	}
}

void Ids::process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer){
	Ids ids;
	if (dbCon != true){
		ids.sql_connection();
	}

	int size = header->len;
    //Getting IP Header
    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    ++total;
    switch (iph->protocol) //Sorting the packets by protocol
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
    cout << "TCP: " << tcp << " UDP: " << udp << " ICMP: " << icmp << " IGMP: " << igmp << " Others: " << others << " Total: " << total << "\r";
}

Ids::~Ids(){
}