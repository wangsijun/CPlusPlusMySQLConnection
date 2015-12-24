//
//  MySQLQueryResult.hpp
//  C++ConnectionMySQL
//
//  Created by 王思俊 on 15/12/20.
//  Copyright © 2015年 王思俊. All rights reserved.
//

#ifndef MySQLQueryResult_hpp
#define MySQLQueryResult_hpp

#include <stdio.h>
#include <mysql.h>
#include <string>
#include <vector>
using namespace std;

class MySQLQueryResult
{
private:
    int m_numRow;
    int m_numCol;
    vector<vector<string>> m_dataList;
public:
    const char* m_errorMessage;
    bool m_error;
    MySQLQueryResult();
    MySQLQueryResult(vector<vector<string>> resultList);
    int GetRowCount();
    int GetColCount();
    void SetRowCount(int rowCount);
    void SetColCount(int colCount);
    string GetDataAt(int row,int col);
    void FreeDataList();
    ~MySQLQueryResult();
};


#endif /* MySQLQueryResult_hpp */
