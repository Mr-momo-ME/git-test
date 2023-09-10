/*
案例-机房预约系统
1.1 身份简介
分别有三种身份使用该程序
学生代表：申请使用机房
教师：审核学生的预约申请
管理员：给学生、教师创建账号

1.2 机房简介
机房总共有3间
1号机房   --- 最大容量20人
2号机房   --- 最多容量50人
3号机房   --- 最多容量100人

1.3 申请简介
申请的订单每周由管理员负责清空。
学生可以预约未来一周内的机房使用，预约的日期为周一至周五，预约时需要选择预约时段（上午、下午）
教师来审核预约，依据实际情况审核预约通过或者不通过

1.4 系统具体需求
首先进入登录界面，可选登录身份有：
  * 学生代表
  * 老师
  * 管理员
  * 退出
每个身份都需要进行验证后，进入子菜单
  * 学生需要输入 ：学号、姓名、登录密码
  * 老师需要输入：职工号、姓名、登录密码
  * 管理员需要输入：管理员姓名、登录密码
学生具体功能
  * 申请预约    ---   预约机房
  * 查看自身的预约    ---  查看自己的预约状态
  * 查看所有预约   ---   查看全部预约信息以及预约状态
  * 取消预约    ---   取消自身的预约，预约成功或审核中的预约均可取消
  * 注销登录    ---   退出登录
教师具体功能
  * 查看所有预约   ---   查看全部预约信息以及预约状态
  * 审核预约    ---   对学生的预约进行审核
  * 注销登录    ---   退出登录
管理员具体功能
  * 添加账号    ---   添加学生或教师的账号，需要检测学生编号或教师职工号是否重复
  * 查看账号    ---   可以选择查看学生或教师的全部信息
  * 查看机房    ---   查看所有机房的信息
  * 清空预约    ---   清空所有预约记录
  * 注销登录    ---   退出登录
 */
#include "manager.h"
using namespace std;

// 全局函数
// 进入管理员菜单
void managerMenu(Identity *person) //这里传入参数只能是父类指针而不是子类，虽然person指向的是子类，但是本身是父类指针
{
  Manager *admin = (Manager *)person; //传入的是父类指针,要将其强转为子类指针,才能用子类的成员属性和函数
  int select = 0;
  while (1)
  {
    admin->operMenu();
    cin >> select;
    switch (select)
    {
    case 1:
      admin->addPerson();
      break;
    case 2:
      admin->showPerson();
      break;
    case 3:
      admin->showComputerRoom();
      break;
    case 4:
      admin->clearFile();
      break;
    case 0:
    {
      cout << "已退出登陆，即将返回主菜单" << endl;
      system("pause");
      system("cls");
      return;
    }
    break;
    default:
      cout << "输入有误，请重新输入" << endl;
      system("pause");
      system("cls");
      break;
    }
  }
}

// 进入学生菜单
void studentMenu(Identity *person)
{
  Student *student = (Student *)person; //传入的是父类指针,要将其强转为子类指针,才能用子类的成员属性和函数
  int select = 0;
  while (1)
  {
    student->operMenu();
    cin >> select;
    switch (select)
    {
    case 1:
      student->applyOrder();
      break;
    case 2:
      student->showMyOrder();
      break;
    case 3:
      student->showAllOrder();
      break;
    case 4:
      student->cancelOrder();
      break;
    case 0:
    {
      cout << "已退出登陆，即将返回主菜单" << endl;
      system("pause");
      system("cls");
      return;
    }
    break;
    default:
      cout << "输入有误，请重新输入" << endl;
      system("pause");
      system("cls");
      break;
    }
  }
}

// 进入教师菜单
void teacherMenu(Identity *person)
{
  Teacher *teacher = (Teacher *)person; //传入的是父类指针,要将其强转为子类指针,才能用子类的成员属性和函数
  int select = 0;
  while (1)
  {
    teacher->operMenu();
    cin >> select;
    switch (select)
    {
    case 1:
      teacher->showAllOrder();
      break;
    case 2:
      teacher->validOrder();
      break;
    case 0:
    {
      cout << "已退出登陆，即将返回主菜单" << endl;
      system("pause");
      system("cls");
      return;
    }
    break;
    default:
      cout << "输入有误，请重新输入" << endl;
      system("pause");
      system("cls");
      break;
    }
  }
}

// 登录功能
void LoginIn(string fileName, int type) //*操作文件名 *人员类型
{
  // 父类指针,用于指向子类对象
  Identity *person = nullptr;
  // 读文件
  ifstream ifs;
  ifs.open(fileName, ios::in);
  // 判断文件是否存在
  if (!ifs.is_open())
  {
    cout << "文件不存在" << endl;
    ifs.close();
    system("pause");
    system("cls");
    return;
  }
  // 判断文件是否为空
  char ch;
  ifs >> ch;
  if (ifs.eof())
  {
    cout << "文件为空" << endl;
    ifs.close();
    system("pause");
    system("cls");
    return;
  }
  // 文件不为空
  // 准备接收用户信息的变量
  int id = 0;
  string name;
  string pwd;
  // 输入登录信息
  switch (type)
  {
  case 1: //学生
  {
    cout << "请输入你的学号:" << endl;
    cin >> id;
    cout << "请输入用户名:" << endl;
    cin >> name;
    cout << "请输入密码:" << endl;
    cin >> pwd;
  }
  break;
  case 2: //教师
  {
    cout << "请输入您的职工号:" << endl;
    cin >> id;
    cout << "请输入用户名:" << endl;
    cin >> name;
    cout << "请输入密码:" << endl;
    cin >> pwd;
  }
  break;
  case 3: //管理员
  {
    cout << "请输入用户名:" << endl;
    cin >> name;
    cout << "请输入密码:" << endl;
    cin >> pwd;
  }
  break;
  default:
    break;
  }
  // 读取文件,身份验证
  ifs.putback(ch);
  switch (type)
  {
  case 1: //学生
  {
    int fileId;      //从文件中读取的id号
    string fileName; //从文件中读取的用户号
    string filePwd;  //从文件中读取的密码
    while (ifs >> fileId && ifs >> fileName && ifs >> filePwd)
    {
      if (id == fileId && name == fileName && pwd == filePwd)
      {
        cout << "学生验证登陆成功" << endl;
        system("pause");
        system("cls");
        person = new Student(id, name, pwd);
        // 进入学生子菜单
        studentMenu(person);
        return;
      }
    }
    ifs.close();
  }
  break;
  case 2: //教师
  {
    int fileId;
    string fileName;
    string filePwd;
    while (ifs >> fileId && ifs >> fileName && ifs >> filePwd)
    {
      if (id == fileId && name == fileName && pwd == filePwd)
      {
        cout << "教师验证登陆成功" << endl;
        system("pause");
        system("cls");
        person = new Teacher(id, name, pwd);
        // 进入教师子菜单
        teacherMenu(person);
        return;
      }
    }
    ifs.close();
  }
  break;
  case 3: //管理员
  {
    string fileName;
    string filePwd;
    while (ifs >> fileName && ifs >> filePwd)
    {
      if (name == fileName && pwd == filePwd)
      {
        cout << "管理员验证登陆成功" << endl;
        system("pause");
        system("cls");
        person = new Manager(name, pwd);
        // 进入管理员子菜单
        managerMenu(person);
        return;
      }
    }
    ifs.close();
  }
  break;
  default:
    break;
  }
  ifs.close();
  cout << "验证登录失败" << endl;
  system("pause");
  system("cls");
}

int main()
{
  int key = -1;
  while (1)
  {
    cout << "==================欢迎使用机房预约系统!==================" << endl;
    cout << endl;
    cout << "\t\t------------------------\n";
    cout << "\t\t|                      |\n";
    cout << "\t\t|      1.学生代表      |\n";
    cout << "\t\t|                      |\n";
    cout << "\t\t|      2.教    师      |\n";
    cout << "\t\t|                      |\n";
    cout << "\t\t|      3.管 理 员      |\n";
    cout << "\t\t|                      |\n";
    cout << "\t\t|      0.退    出      |\n";
    cout << "\t\t|                      |\n";
    cout << "\t\t------------------------\n";
    cout << "请输入您的身份: ";
    cin >> key;
    switch (key)
    {
    case 1: //学生身份
      LoginIn(STUDENT_FILE, 1);
      break;
    case 2: //老师身份
      LoginIn(TEACHER_FILE, 2);
      break;
    case 3: //管理员身份
      LoginIn(ADMIN_FILE, 3);
      break;
    case 0: //退出系统
    {
      cout << "已退出系统，欢迎下次使用!" << endl;
      exit(0);
    }
    break;
    default:
      cout << "输入有误，请重新输入" << endl;
      system("pause");
      system("cls");
      break;
    }
  }
}