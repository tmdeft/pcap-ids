#include "ids.h"
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <mysql/mysql.h>

#define DBHOST "localhost"
#define DBUSER "ids"
#define DBPASS "QWEasd"
#define DBBASE "IDS"

using namespace std;
using namespace sql::mysql;

bool connectionState = false;

sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;
sql::PreparedStatement *pstmt;

int sessionId = 0;

bool Ids::sql_connection(){
	try{
		driver = ::get_driver_instance();
		con = driver->connect(DBHOST, DBUSER, DBPASS);
		con->setSchema("IDS");
		if (!con->isValid()){
			cout << "MySQL Connection failed" << endl;
			exit(1);
		}
		else {
			cout << "MySQL Connection Success" << endl;
			connectionState = true;
		}
	}
	catch(sql::SQLException &e){
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	return connectionState;
}
void Ids::add_db(int tcp, int udp, int others, int total, int icmp, int igmp){
	sessionId ++;
	pstmt = con->prepareStatement("UPDATE summaryTable SET TCP = ?, UDP = ?, Others = ?, Total = ?, ICMP = ?, IGMP = ? WHERE ID=?");
	pstmt->setInt(1,tcp);
	pstmt->setInt(1,udp);
	pstmt->setInt(1,others);
	pstmt->setInt(1,total);
	pstmt->setInt(1,icmp);
	pstmt->setInt(1,igmp);
	pstmt->setInt(1,sessionId);
	pstmt->execute();
	delete pstmt;
}