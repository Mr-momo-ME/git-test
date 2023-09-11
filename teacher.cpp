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
    orderFile of; // 创建预约类
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        return;
    }
    for (int i = 0; i < of.m_Size; i++)
    {
        cout << "预约日期: 周" << of.m_orderData[i]["date"];
        cout << ", 时段: " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
        cout << ", 学号:" << of.m_orderData[i]["stuId"];
        cout << ", 姓名:" << of.m_orderData[i]["stuName"];
        cout << ", 机房: " << of.m_orderData[i]["roomId"];
        string status = ", 状态: "; // 0 1 2 -1
        if (of.m_orderData[i]["status"] == "1")
        {
            status += "审核中";
        }
        if (of.m_orderData[i]["status"] == "2")
        {
            status += "预约成功";
        }
        if (of.m_orderData[i]["status"] == "-1")
        {
            status += "预约失败";
        }
        if (of.m_orderData[i]["status"] == "0")
        {
            status += "取消预约";
        }
        cout << status << endl;
    }
    system("pause");
    system("cls");
    return;
}
// 审核预约
void Teacher::validOrder()
{
}
