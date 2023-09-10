#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Identity.h"
#include "ComputerRoom.h"
#include "orderFile.h"
#include "globalFile.h"
using namespace std;
// 学生类:身份抽象类
class Student : public Identity
{
public:
    int m_Id;                  //学生学号
    vector<ComputerRoom> vCom; //机房容量

    Student();
    // 有参构造
    Student(int id, string name, string pwd);
    // 析构
    ~Student();
    // 菜单界面(父类纯虚函数重写)
    virtual void operMenu();
    // 申请预约
    void applyOrder();
    // 查看我的预约
    void showMyOrder();
    // 查看全部预约
    void showAllOrder();
    // 取消预约
    void cancelOrder();
};