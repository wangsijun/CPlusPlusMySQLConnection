//
//  MySQLQueryResult.cpp
//  C++ConnectionMySQL
//
//  Created by 王思俊 on 15/12/20.
//  Copyright © 2015年 王思俊. All rights reserved.
//

#include "MySQLQueryResult.hpp"

MySQLQueryResult::MySQLQueryResult(){
    
};

MySQLQueryResult::MySQLQueryResult(vector<vector<string>> resultList)
{
    for (vector<vector<string>>::iterator it = resultList.begin(); it != resultList.end(); it++)
    {
        vector<string> temp(it->size());
        copy(it->begin(), it->end(), temp.begin());
        m_dataList.push_back(temp);
    }
};

string MySQLQueryResult::GetDataAt(int row, int col)
{
    if (row > m_numRow || row < 0 || col > m_numCol || col < 0)
    {
        return "#Error#";
    }
    else
    {
        return m_dataList[row][col];
    }
};

int MySQLQueryResult::GetRowCount()
{
    return MySQLQueryResult::m_numRow;
};

int MySQLQueryResult::GetColCount()
{
    return MySQLQueryResult::m_numCol;
};

void MySQLQueryResult::SetRowCount(int rowCount)
{
    MySQLQueryResult::m_numRow = rowCount;
};

void MySQLQueryResult::SetColCount(int colCount)
{
    MySQLQueryResult::m_numCol = colCount;
};

void MySQLQueryResult::FreeDataList()
{
    for (int i = 0; i< m_numRow; i++)
    {
        m_dataList[i].clear();
    }
};

MySQLQueryResult::~MySQLQueryResult(){
    FreeDataList();
};