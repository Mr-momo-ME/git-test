#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Identity.h"
#include "orderFile.h"
#include "globalFile.h"
using namespace std;
// 老师类:身份抽象类
class Teacher : public Identity
{
public:
    int m_empId; //职工编号

    Teacher();
    // 有参构造
    Teacher(int empId, string name, string pwd);
    // 析构
    ~Teacher();
    // 菜单界面(父类纯虚函数重写)
    virtual void operMenu();
    // 查看全部预约
    void showAllOrder();
    // 审核预约
    void validOrder();
};