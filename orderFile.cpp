#include "orderFile.h"

void dataParse(map<string, string> &m, const string &data)
{
    string key;   //每个键值对的索引
    string value; //每个键值对的值
    int pos = 0;
    pos = data.find(':', 0);
    if (pos != -1)
    {
        key = data.substr(0, pos);
        value = data.substr(pos + 1, data.size() - pos - 1); //第二个参数是截取长度，等于子字符串末尾后一位位置-首位位置
        m.insert(make_pair(key, value));
    }
}

orderFile::orderFile()
{
    this->m_Size = 0; //记录预约条数
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);
    string date;     //日期
    string interval; //时间段
    string stuId;    //学生编号
    string stuName;  //学生姓名
    string roomId;   //机房编号
    string status;   //预约状态

      while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
    {
        map<string, string> tempMap;  //存放每行预约数据中的所有键值对信息
        dataParse(tempMap, date);     //截取日期
        dataParse(tempMap, interval); //截取时间段
        dataParse(tempMap, stuId);    //截取学生编号
        dataParse(tempMap, stuName);  //截取学生姓名
        dataParse(tempMap, roomId);   //截取机房编号
        dataParse(tempMap, status);   //截取预约状态
        // 测试小容器
        // for (map<string, string>::iterator it = tempMap.begin(); it != tempMap.end(); it++)
        // {
        //     cout << it->first << ":" << it->second << " ";
        // }
        // cout << endl;
        this->m_orderData.insert(make_pair(this->m_Size, tempMap));
        this->m_Size++;
    }
    ifs.close();
    //测试大容器
    // for (map<int, map<string, string>>::iterator it = this->m_orderData.begin(); it != this->m_orderData.end(); it++)
    // {
    //     cout << "条数为= " << it->first << ", value= " << endl;
    //     for (map<string, string>::iterator sit = it->second.begin(); sit != it->second.end(); sit++)
    //     {
    //         cout << sit->first << ":" << sit->second << " ";
    //     }
    //     cout << endl;
    // }
}
orderFile::~orderFile()
{
}

void orderFile::updateOrder()
{
    if (this->m_Size == 0)
    {
        return;
    }
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::out | ios::trunc);
    for (int i = 0; i < this->m_Size; i++)
    {
        ofs << "date:" << this->m_orderData[i]["date"] << " ";
        ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
        ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
        ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
        ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
        ofs << "status:" << this->m_orderData[i]["status"] << endl;
    }
    ofs.close();
}

void orderFile::test()
{
    for (map<int, map<string, string>>::iterator it = this->m_orderData.begin(); it != this->m_orderData.end(); it++)
    {
        cout << "条数为= " << it->first << ", value= " << endl;
        for (map<string, string>::iterator sit = it->second.begin(); sit != it->second.end(); sit++)
        {
            cout << sit->first << ":" << sit->second << " ";
        }
        cout << endl;
    }
}