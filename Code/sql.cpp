#include "ids.h"
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <mysql/mysql.h>

using namespace std;
using namespace sql::mysql;

sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;
sql::PreparedStatement *pstmt;
bool state=false;

Database::Database(){
    cout << "SQL" << endl;
}

Database::~Database(){
    cout << "~SQL" << endl;
}

bool Database::connect(){
    try{
      driver = ::get_driver_instance();
      con = driver->connect(this->dbHost, this->dbUser, this->dbPass);
      con->setSchema(this->dbBase);
      if (!con->isValid()){
        cout << "ERROR(WARNING)!:MySQL Connection failed" << endl;
        state = false;
      }
      else {
        cout << "MySQL Connection Success" << endl;
        state = true;
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

void Database::checkTable(){
    pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS dosLog(ID int not null auto_increment primary key, IP_Address varchar(320) not null, MAC_Address varchar(500) not null, Port int not null, Time TIMESTAMP default current_timestamp)");
    pstmt->execute();
    delete pstmt;
}

void Database::insert(){
    string ip = MainProcess::getIp();
    string mac = MainProcess::getMac();
    unsigned int port = MainProcess::getPort();
    pstmt = con->prepareStatement("INSERT INTO dosLog(IP_Address,MAC_Address,Port) VALUES(?,?,?)");
    pstmt->setString(1,ip);
    pstmt->setString(2,mac);
    pstmt->setInt(3,port);
    pstmt->execute();
    delete pstmt;
}
