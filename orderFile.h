// 为在student.cpp和teacher.app解析预约文件数据，创建了orderFile预约的类
// 功能：显示预约记录时，从文件中获取所有记录用来显示，创建该预约的类来管理和更新预约记录

#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "globalFile.h"
using namespace std;
class orderFile
{
public:
    int m_Size;                                //记录预约条数
    map<int, map<string, string>> m_orderData; //记录所有预约信息的容器，外面容器key为记录条数，valuie记录键值对信息

    orderFile();
    ~orderFile();
    // 更新预约记录
    void updateOrder();
    // 测试大容器内容
    void test();
};
