#include "manager.h"

Manager::Manager(string name, string pwd)
{
    // 初始化管理员信息
    this->m_Name = name;
    this->m_Pwd = pwd;
    // 初始化老师和学生信息
    this->initVector();
    // 初始化机房信息
    this->initComputerRoom();
}
Manager::~Manager()
{
}

// 初始化学生和老师
void Manager::initVector()
{
    // 确保容器清空
    this->vStu.clear();
    this->vTea.clear();
    // 分别读取学生和老师文件信息，并将数据存入容器中
    ifstream ifs;
    ifs.open(STUDENT_FILE, ios::in);
    Student stu;
    while (ifs >> stu.m_Id && ifs >> stu.m_Name && ifs >> stu.m_Pwd)
    {
        this->vStu.push_back(stu);
    }
    ifs.close();

    ifs.open(TEACHER_FILE, ios::in);
    Teacher tea;
    while (ifs >> tea.m_empId && ifs >> tea.m_Name && ifs >> tea.m_Pwd)
    {
        this->vTea.push_back(tea);
    }
    ifs.close();
}
// 初始化机房信息
void Manager::initComputerRoom()
{
    ComputerRoom cr;
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    while (ifs >> cr.m_ComId && ifs >> cr.m_MaxNum)
    {
        this->vCom.push_back(cr);
    }
    ifs.close();
}

// 打印函数
void printStudent(const Student &stu)
{
    cout << "学号：" << stu.m_Id << "\t姓名：" << stu.m_Name << "\t密码：" << stu.m_Pwd << endl;
}
void printTeacher(const Teacher &tea)
{
    cout << "职工编号：" << tea.m_empId << "\t姓名：" << tea.m_Name << "\t密码：" << tea.m_Pwd << endl;
}

// 菜单界面(父类纯虚函数重写)
void Manager::operMenu()
{
    cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
    cout << "\t\t ---------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.添加账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.查看账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.查看机房            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          4.清空预约            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.注销登录            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "请输入您的操作： ";
}

// 查询是否已有重复学号或职工编号，用于添加账号
bool Manager::isSame(int select, int new_id)
{
    if (select == 1)
    {
        for (vector<Student>::iterator it = this->vStu.begin(); it != this->vStu.end(); it++)
        {
            if (new_id == it->m_Id)
            {
                return true;
            }
        }
    }
    else
    {
        for (vector<Teacher>::iterator it = this->vTea.begin(); it != this->vTea.end(); it++)
        {
            if (new_id == it->m_empId)
            {
                return true;
            }
        }
    }
    return false;
}
// 添加账户
void Manager::addPerson()
{
    int select = -1; //老师还是学生
    string filename; //读取文件名
    string tip;
    int id = -1;
    string name;
    string pwd;
    cout << "请输入添加账户类型: 1.学生 2.老师" << endl;
    cin >> select;
    while (select != 1 && select != 2)
    {
        cout << "输入有误，请重新输入: 1.学生 2.老师" << endl;
        cin >> select;
    }
    ofstream ofs;
    if (select == 1)
    {
        filename = STUDENT_FILE;
        tip = "输入你的学号:";
    }
    if (select == 2)
    {
        filename = TEACHER_FILE;
        tip = "输入你的职工号:";
    }
    cout << "请" << tip << endl;
    cin >> id;
    // 去重操作
    while (this->isSame(select, id))
    {
        cout << "已存在，请重新" << tip << endl;
        cin >> id;
    }
    cout << "请输入用户名:" << endl;
    cin >> name;
    cout << "请输入密码:" << endl;
    cin >> pwd;
    ofs.open(filename, ios::out | ios::app);
    ofs << id << " " << name << " " << pwd << endl;
    ofs.close();
    cout << "已完成添加!" << endl;
    system("pause");
    system("cls");
    this->initVector(); //调用初始化容器接口，更新容器。避免因为刚添加的账号没有更新到容器中，再次添加时可以重复添加
}

// 查看账户
void Manager::showPerson()
{
    cout << "请选择查看内容" << endl;
    cout << "1、查看所有学生" << endl;
    cout << "2、查看所有教师" << endl;
    int select = 0;
    cin >> select;
    if (select == 1)
    {
        if (this->vStu.size() == 0)
        {
            cout << "学生文件不存在或为空" << endl;
        }
        else
        {
            for_each(this->vStu.begin(), this->vStu.end(), printStudent);
        }
    }
    else
    {
        if (this->vTea.size() == 0)
        {
            cout << "老师文件不存在或为空" << endl;
        }
        else
        {
            for_each(this->vTea.begin(), this->vTea.end(), printTeacher);
        }
    }
    system("pause");
    system("cls");
}

// 查看机房信息
void Manager::showComputerRoom()
{
    cout << "当前机房数量: " << this->vCom.size() << endl;
    for (vector<ComputerRoom>::iterator it = this->vCom.begin(); it != vCom.end(); it++)
    {
        cout << "机房编号: " << it->m_ComId << "\t机房最大容量: " << it->m_MaxNum << endl;
    }
    system("pause");
    system("cls");
    return;
}

// 清空预约记录
void Manager::clearFile()
{
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::out | ios::trunc);
    ofs.close();
    cout << "已完成清除" << endl;
    system("pause");
    system("cls");
}