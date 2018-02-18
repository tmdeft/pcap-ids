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

const char *dbUser, *dbHost, *dbBase, *dbPass;
bool state = false;

Sql::Sql(){
    cout << "Connecting to SQL database" << endl;
    dbUser = this->dbUser;
    dbHost = this->dbHost;
    dbPass = this->dbPass;
    dbBase = this->dbBase;
}

bool Sql::connect(){
  try{
    driver = ::get_driver_instance();
    con = driver->connect(dbHost, dbUser, dbPass);
    con->setSchema(dbBase);
    /*stmt = con->createStatement();
    stmt->execute("INSERT INTO summaryTable(TCP,UDP,Others,Total,ICMP,IGMP) VALUES(0,0,0,0,0,0)");
    */
    //sessionId ++;
    //delete stmt;
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
  Sql::checkTable();
  return state;
}

void Sql::checkTable(){
    pstmt = con->prepareStatement("CREATE TABLE IF NOT EXISTS dosLog(ID int not null auto_increment primary key, IP_Address varchar(320), MAC_Address varchar(500), Port int, Time TIMESTAMP default current_timestamp)");
    pstmt->execute();
    delete pstmt;
}

void Sql::insertData(std::string ip, std::string mac, unsigned int port){
    // string query = "INSERT INTO dosLog(IP_Address, MAC_Address, Port)VALUES('";
    // query += ip + "','";
    // query += mac + "',";
    // query += port + ")";
    pstmt = con->prepareStatement("INSERT INTO dosLog(IP_Address,MAC_Address,Port) VALUES(?,?,?)");
    pstmt->setString(1,ip);
    pstmt->setString(2,mac);
    pstmt->setInt(3,port);
    pstmt->execute();
    delete pstmt;
}

void Sql::addData(){
    //cout << "Data added" << this->dbUser << endl;
}

void Sql::selectData(){
    //cout << "Select * from data" << this->dbUser << endl;
}

Sql::~Sql(){
    //cout << "Exiting" << endl;
}
