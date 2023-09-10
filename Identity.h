#pragma once
#include <iostream>
#include <string>
using namespace std;
// 身份抽象类（基类，不需要具体的函数实现，所以也就不需要cpp文件）
class Identity
{
public:
    string m_Name; //用户名
    string m_Pwd;  //密码

    virtual void operMenu() = 0; //操作菜单，纯虚函数子类必须重写实现内容
};
