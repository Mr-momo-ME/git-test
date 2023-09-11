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
        system("pause");
        system("cls");
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
            status += "预约失败,审核未通过";
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
    orderFile of; // 创建预约类
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    vector<int> v; //用于记录每条预约记录是在OrderFile文件中的哪一行数据
    int count = 0; //统计有多少条待审核的预约记录
    cout << "待审核的预约记录如下" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < of.m_Size; i++)
    {
        if (of.m_orderData[i]["status"] == "1")
        {
            v.push_back(i);
            cout << count << "、";
            cout << "预约日期: 周" << of.m_orderData[i]["date"];
            cout << ", 时段: " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
            cout << ", 学号:" << of.m_orderData[i]["stuId"];
            cout << ", 姓名:" << of.m_orderData[i]["stuName"];
            cout << ", 机房: " << of.m_orderData[i]["roomId"];
            // string status = ", 状态: "; // 0 1 2 -1
            cout << ", 状态: 审核中" << endl;
            count++;
        }
    }
    if (count == 0)
    {
        cout << "没有需要审核的预约" << endl;
        system("pause");
        system("cls");
        return;
    }
    int select = -1;
    cout << "请输入您想审核的预约编号, -1代表返回菜单" << endl;
    while (1)
    {
        cin >> select; //选择预约编号
        if (select == -1)
        {
            break;
        }
        if (select >= 0 && select <= (int)v.size() - 1)
        {
            cout << "请输入审核结果: 1、通过   2、不通过" << endl;
            int choice = 0;
            while (1)
            {
                cin >> choice; //选择审核结果
                if (choice == 1 || choice == 2)
                {
                    of.m_orderData[v[select]]["status"] = choice == 1 ? "2" : "-1";
                    of.updateOrder(); //上面操作只改变了容器的值，而每次调用查看预约，容器的值是根据文件重新初始化的，所以还要更新到文件中。
                    cout << "已完成审核!" << endl;
                    break;
                }
                else
                {
                    cout << "输入有误，请重新输入" << endl;
                }
            }
            break;
        }
        else
        {
            cout << "输入有误，请重新输入:" << endl;
        }
    }
    system("pause");
    system("cls");
    return;
}
