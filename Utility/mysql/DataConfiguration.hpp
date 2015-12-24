//
//  DataConfiguration.hpp
//  C++ConnectionMySQL
//
//  Created by 王思俊 on 15/12/20.
//  Copyright © 2015年 王思俊. All rights reserved.
//

#ifndef DataConfiguration_hpp
#define DataConfiguration_hpp

#include <stdio.h>
#include <string>

using namespace std;

class DataConfiguration
{
public:
    string host;
    string username;
    string password;
    string databases;
    string character_set;
    unsigned int port;
};
#endif /* DataConfiguration_hpp */
