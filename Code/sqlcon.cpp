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

sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;
sql::PreparedStatement *pstmt;

int sessionId = 0;

void Ids::sql_connection(){
	try{
		driver = ::get_driver_instance();
		con = driver->connect(DBHOST, DBUSER, DBPASS);
		con->setSchema("IDS");
		stmt = con->createStatement();
		stmt->execute("INSERT INTO summaryTable(TCP,UDP,Others,Total,ICMP,IGMP) VALUES(0,0,0,0,0,0)");
		sessionId ++;
		delete stmt;
		if (!con->isValid()){
			cout << "MySQL Connection failed" << endl;
			exit(1);
		}
		else {
			cout << "MySQL Connection Success" << endl;
		}
	}
	catch(sql::SQLException &e){
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}
void Ids::add_db(int tcp, int udp, int others, int total, int icmp, int igmp){
	pstmt = con->prepareStatement("UPDATE summaryTable SET TCP = ?, UDP = ?, Others = ?, Total = ?, ICMP = ?, IGMP = ? WHERE ID=?");
	pstmt->setInt(1,tcp);
	pstmt->setInt(2,udp);
	pstmt->setInt(3,others);
	pstmt->setInt(4,total);
	pstmt->setInt(5,icmp);
	pstmt->setInt(6,igmp);
	pstmt->setInt(7,sessionId);
	pstmt->execute();
	delete pstmt;
}