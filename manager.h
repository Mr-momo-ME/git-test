#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Identity.h"
#include "student.h"
#include "teacher.h"
#include "ComputerRoom.h" 
#include "globalFile.h"

using namespace std;
// 管理员类:身份抽象类
class Manager : public Identity
{
public:
    vector<Student> vStu;
    vector<Teacher> vTea;
    vector<ComputerRoom> vCom; //机房容量

    // 有参构造
    Manager(string name, string pwd);
    // 析构
    ~Manager();

    // 菜单界面(父类纯虚函数重写)
    virtual void operMenu();

    // 添加账户
    void addPerson();
    bool isSame(int select, int id); //用于查询添加账户的id是否有重复
    void initVector();               //初始化存放学生和老师的容器

    // 查看账户
    void showPerson();

    // 查看机房信息
    void showComputerRoom();
    void initComputerRoom(); //初始化机房信息

    // 清空预约记录
    void clearFile();
};
