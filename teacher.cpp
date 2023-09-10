#include "teacher.h"

Teacher::Teacher()
{
}
Teacher::Teacher(int empId, string name, string pwd)
{
    this->m_empId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}
Teacher::~Teacher()
{
}
// 菜单界面(父类纯虚函数重写)
void Teacher::operMenu()
{
    cout << "欢迎教师：" << this->m_Name << "登录！" << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          1.查看所有预约          |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          2.审核预约              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          0.注销登录              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t ----------------------------------\n";
    cout << "请选择您的操作： " << endl;
}
// 查看全部预约
void Teacher::showAllOrder()
{
}
// 审核预约
void Teacher::validOrder()
{
}
