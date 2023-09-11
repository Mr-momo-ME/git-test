#include "student.h"
Student::Student()
{
}
Student::Student(int id, string name, string pwd)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;
    //初始化机房文件
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    ComputerRoom cr;
    while (ifs >> cr.m_ComId && ifs >> cr.m_MaxNum)
    {
        this->vCom.push_back(cr);
    }
    ifs.close();
}
Student::~Student()
{
}
// 菜单界面(父类纯虚函数重写)
void Student::operMenu()
{
    cout << "欢迎学生代表：" << this->m_Name << "登录！" << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          1.申请预约             |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          2.查看我的预约         |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          3.查看所有预约         |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          4.取消预约             |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          0.注销登录             |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t ----------------------------------\n";
    cout << "请输入您的操作： ";
}

// 申请预约
void Student::applyOrder()
{
    cout << "机房开放时间为周一至周五！" << endl;
    cout << "请输入申请预约的时间：" << endl;
    cout << "1、周一" << endl;
    cout << "2、周二" << endl;
    cout << "3、周三" << endl;
    cout << "4、周四" << endl;
    cout << "5、周五" << endl;
    int date = 0;     //预约日期
    int interval = 0; //预约时间段
    int room = 0;     //预约机房编号
    while (1)
    {
        cin >> date;
        if (date >= 1 && date <= 5)
        {
            break;
        }
        cout << "输入有误，请重新输入" << endl;
    }

    cout << "请输入申请预约的时间段：" << endl;
    cout << "1、上午" << endl;
    cout << "2、下午" << endl;
    while (1)
    {
        cin >> interval;
        if (interval == 1 || interval == 2)
        {
            break;
        }
        cout << "输入有误，请重新输入" << endl;
    }
    cout << "请选择机房：" << endl;
    for (vector<ComputerRoom>::iterator it = this->vCom.begin(); it != this->vCom.end(); it++)
    {
        cout << it->m_ComId << "号机房容量：" << it->m_MaxNum << endl;
    }
    while (1)
    {
        cin >> room;
        if (room >= 1 && room <= (int)this->vCom.size())
        {
            break;
        }
        cout << "输入有误，请重新输入" << endl;
    }
    cout << "预约申请成功!审核中" << endl;

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::out | ios::app);
    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->m_Id << " ";
    ofs << "stuName:" << this->m_Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << endl;
    ofs.close();
    //除此之外，还可以选择往of的容器里写，然后调用of的update()函数写入到文件中
    system("pause");
    system("cls");
}

// 查看我的预约
void Student::showMyOrder()
{
    orderFile of; // 创建预约类
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    int flag = 0;  //用于判断该学生有无预约记录
    int count = 0; //统计该学生有多少条预约记录
    for (int i = 0; i < of.m_Size; i++)
    {
        //一个是string，一个是int，需要转换才能比较
        // if (of.m_orderData[i]["stuId"] == to_string(this->m_Id))
        if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
        {
            flag = 1;
            count++;
            cout << count << "、";
            cout << "预约日期: 周" << of.m_orderData[i]["date"];
            cout << ", 时段: " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
            cout << ", 机房" << of.m_orderData[i]["roomId"];
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
    }
    if (flag == 0)
    {
        cout << "您没有预约记录" << endl;
    }
    system("pause");
    system("cls");
    return;
}
// 查看全部预约
void Student::showAllOrder()
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
        cout << i + 1 << "、";
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
// 取消预约
void Student::cancelOrder()
{
    orderFile of; // 创建预约类
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;
    cout << "----------------------------------------" << endl;
    int count = 0; //统计该学生有多少条预约记录
    vector<int> v; //用于记录每条预约记录是在OrderFile文件中的哪一行数据
    for (int i = 0; i < of.m_Size; i++)
    {
        //  先判断文件中是否有自身学号的预约
        if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
        {
            // 再筛选状态，仅审核中和审核通过的预约可以取消
            if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
            {
                v.push_back(i); // v[count] == i
                cout << count << "、";
                cout << "预约日期: 周" << of.m_orderData[i]["date"];
                cout << ", 时段: " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
                cout << ", 机房" << of.m_orderData[i]["roomId"];
                string status = ", 状态: "; // 0 1 2 -1
                if (of.m_orderData[i]["status"] == "1")
                {
                    status += "审核中";
                }
                if (of.m_orderData[i]["status"] == "2")
                {
                    status += "预约成功";
                }
                cout << status << endl;
                count++;
            }
        }
    }
    if (count == 0)
    {
        cout << "您没有可以取消的预约" << endl;
        system("pause");
        system("cls");
        return;
    }
    int select = -1;
    cout << "请输入您想取消预约的编号, -1代表返回菜单" << endl;
    while (1)
    {
        cin >> select;
        if (select == -1)
        {
            break;
        }
        if (select >= 0 && select <= (int)v.size() - 1)
        {
            of.m_orderData[v[select]]["status"] = "0";
            of.updateOrder(); //上面操作只改变了容器的值，而每次调用查看预约，容器的值是根据文件重新初始化的，所以还要更新到文件中。
            cout << "取消预约成功" << endl;
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