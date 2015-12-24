//
//  MySQLConnector.hpp
//  C++ConnectionMySQL
//
//  Created by 王思俊 on 15/12/20.
//  Copyright © 2015年 王思俊. All rights reserved.
//

#ifndef MySQLConnector_hpp
#define MySQLConnector_hpp

#include <stdio.h>
#include <mysql.h>
#include <string>
#include "DataConfiguration.hpp"
#include "MySQLQueryResult.hpp"

using namespace std;
#define MYSQL_CONNECTION_SUCCESS 1
#define MYSQL_CONNECTION_ERROR 0
#define MYSQL_CHANGE_SUCCESS 1
#define MYSQL_CHANGE_ERROR -1
#define MYSQL_USEDB_SUCCESS 1
#define MYSQL_USEDB_FAILED -1

class MySqlOperation
{
private:
    bool ConnectionSuccess();
    const char* character_set;
public:
    
    MYSQL *connection, mysql;
    MySqlOperation(DataConfiguration config);
    int SelectDatabase(string db);
    int Command(string sql);
    MySQLQueryResult Query(string sql);
    ~MySqlOperation();
};

#endif /* MySQLConnector_hpp */
