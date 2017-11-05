#include "ids.h"

using namespace std;

Sql::Sql(){
    cout << "Sql starting" << endl;
}

void Sql::connect(){
    cout << "Connection success" << this->dbUser << endl;
}

void Sql::insertData(){
    cout << "Data inserted" << this->dbUser << endl;
}

void Sql::addData(){
    cout << "Data added" << this->dbUser << endl;
}

void Sql::selectData(){
    cout << "Select * from data" << this->dbUser << endl;
}

Sql::~Sql(){
    cout << "Exiting" << endl;
}
