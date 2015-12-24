//
//  MySQLConnector.cpp
//  C++ConnectionMySQL
//
//  Created by 王思俊 on 15/12/20.
//  Copyright © 2015年 王思俊. All rights reserved.
//

#include <iostream>
#include "MySQLConnector.hpp"
#include "MySQLQueryResult.hpp"
MySQLQueryResult* mysqlResult;

MySqlOperation::MySqlOperation(DataConfiguration config){
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql,config.host.c_str(),config.username.c_str(),config.password.c_str(),config.databases.c_str(),config.port,NULL,0);
    character_set = config.character_set.c_str();
};
bool MySqlOperation::ConnectionSuccess(){
    if (connection != NULL)
    {
        return MYSQL_CONNECTION_SUCCESS;
    }
    else{
        return MYSQL_CONNECTION_ERROR;
    }
};

int MySqlOperation::SelectDatabase(string db){
    if(ConnectionSuccess()){
        if(0==mysql_select_db(&mysql, db.c_str()))
        {
            return MYSQL_USEDB_SUCCESS;
        }
        else{
            return MYSQL_USEDB_FAILED;
        }
    }
    else{
        return MYSQL_CONNECTION_ERROR;
    }
};

int MySqlOperation::Command(string sql){
    if(ConnectionSuccess())
    {
        if (0 == mysql_query(&mysql, sql.c_str())) {
            return MYSQL_CHANGE_SUCCESS;
        } else {
            return MYSQL_CHANGE_ERROR;
        }
    }
    else{
        return MYSQL_CONNECTION_ERROR;
    }
};

MySQLQueryResult MySqlOperation::Query(string sql){
    if (ConnectionSuccess())
    {
        mysql.reconnect = MYSQL_CONNECTION_SUCCESS;
        int rt = mysql_query(&mysql,character_set);
        if (rt)
        {
            char* message;
            int len = sprintf(message,"Error making query: %s !!!\n", mysql_error(&mysql));
            if(len>0){
                mysqlResult->m_errorMessage = message;
            }
            else{
                mysqlResult->m_errorMessage = "Error making query and sprintf error! address is MySQLConnector.cpp line 28.";
            }
        }
        else{
            const char* query = sql.c_str();
            rt = mysql_real_query(&mysql, query, strlen(query));
            if(rt){
                char* message;
                int len = sprintf(message,"Error making query: %s !!!\n", mysql_error(&mysql));
                if(len>0){
                    mysqlResult->m_errorMessage = message;
                }
                else{
                    mysqlResult->m_errorMessage = "Error making query and sprintf error! address is MySQLConnector.cpp line 38.";
                }
            }
            else{
                MYSQL_RES *res;
                MYSQL_ROW row;
                res = mysql_store_result(&mysql);
                vector<vector<string>> dataList;
                int rowCount = 0;
                while ((row = mysql_fetch_row(res)) != NULL)
                {
                    vector<string> list;
                    for (size_t i = 0; i < mysql_num_fields(res); i++)
                    {
                        list.push_back(row[i]);
                    }
                    dataList.push_back(list);
                    ++rowCount;
                }
                
                mysqlResult = new MySQLQueryResult(dataList);
                
                mysqlResult->SetColCount(mysql_num_fields(res));
                mysqlResult->SetRowCount(rowCount);
                mysql_free_result(res);
            }
        }
    }
    else{
        mysql.reconnect = MYSQL_CONNECTION_ERROR;
        mysqlResult->m_error = true;
        mysqlResult->m_errorMessage = "Connection failed!";
    }
    return *mysqlResult;
};

MySqlOperation::~MySqlOperation(){
    mysql_close(&mysql);
};