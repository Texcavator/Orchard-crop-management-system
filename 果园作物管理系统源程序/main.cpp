/* 果园作物管理系统 */

#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

const int N = 110;

/* 以下为三个基本结构体 */

// 1.地块
typedef struct Land *land;
struct Land
{
    int id; // 地块编号
    string type; // 土壤种类
    string shape; // 地块形状
    double area; // 地块面积
    string location; // 地块位置
    Land* Next; // 下一个地块
};

// 2.作物
typedef struct Crop *crop;
struct Crop
{
    int id; // 作物种类编号
    string name; // 作物名称
    string plantingMonth; // 种植月份
    string harvestMonth; // 收获月份
    string characteristics; // 作物特性
    Crop* Next; // 下一个作物
};

// 3.用户
typedef struct User *user;
struct User
{
    int id; // 用户账号
    string name; // 用户姓名
    string password; // 用户密码
    int role; // 用户职务：1：管理员 2：操作员 3：财务员
    User* Next; // 下一个用户
};

/* 以下是四个基本操作集结构体 */

// 1.种植
typedef struct Planting *planting;
struct Planting
{
    int id; // 种植记录编号
    int landId; // 种植地块编号
    int cropId; // 种植作物种类编号
    int quantity; // 种植数量
    string date; // 种植时间
    string implementer; // 种植人
    string inspector; // 检查人
    Planting* Next; // 下一个种植操作
};

// 2.经营
typedef struct Operation *operation;
struct Operation
{
    int id; // 经营记录编号
    int operationType; // 经营种类：1：施肥 2：浇水 3：除草
    string date; // 经营时间
    string implementer; // 经营人
    string inspector; // 检查人 
    Operation* Next; // 下一个经营操作
};

// 3.采摘
typedef struct Harvest *harvest;
struct Harvest
{
    int id; // 采摘记录编号
    int landId; // 采摘地块
    int cropId; // 采摘作物种类
    int quantity; // 采摘数量
    string date; // 采摘时间
    string implementer; // 采摘人
    string inspector; // 检查人
    Harvest* Next; // 下一个采摘操作
};

// 4.财务
typedef struct Finance *finance;
struct Finance
{
    string date; // 时间
    double income; // 收入
    double expense; // 支出
    Finance* Next; // 下一个财务操作
};

/* 以下为自定义函数声明 */

// 登录系统
void Login(User* user_message, Operation* operation_message, Planting* planting_message, Harvest* harvest_message, Land* land_message, Crop* crop_message, Finance* finance_message);
// 结束界面
void ExitSystem();
// 输入错误界面
void InputError(User* user_message, Operation* operation_message, Planting* planting_message, Harvest* harvest_message, Finance* finance_message, Land* land_message, Crop* crop_message);
//管理员操作集
void Administrator_Operation(User* user_message, Land* land_message, Crop* crop_message, Finance* finance_message);
// 增加用户
void Add(User* user_message, Finance* finance_message, Land* land_message, Crop* crop_message);
// 删除用户
void User_Delete(User* user_message, Land* land_message, Finance* finance_message, Crop* crop_message);
// 修改用户
void Modify(User* user_message, Land* land_message, Crop* crop_message, Finance* finance_message);
// 查询用户
void Require(User* user_message, Land* land_message, Crop* crop_message, Finance* finance_message);
// 根据Id判断用户是否已存在
bool IsExist(int Id, User* user_message);
// 返回第K个用户
User* FindKth(int K, User* PtrL);
// 返回Id的位置
int Find(int Id, User* user_message);
// 操作员操作集
void Operator_Operation(Planting* planting_message, Operation* operation_message, Harvest* harvest_message);
// 种植
void Plant(Planting* planting_message, Operation* operation_message, Harvest* harvest_message);
// 经营
void Operate(Planting* planting_message, Operation* operation_message, Harvest* harvest_message);
// 采摘
void Picking(Planting* planting_message, Operation* operation_message, Harvest* harvest_message);
// 财务员操作集
void Treasurer_Operation(Finance* finance_message);
// 记录收入
void Income(Finance* finance_message);
// 记录支出
void Expense(Finance* finance_message);
// 返回查询结果
void Require_input(User* p);
// 根据Name判断用户是否已存在
bool IsExist_name(string Name, User* user_message);
// 延时
void delay(int seconds);
// 查询地块信息
void Require_land(Land* land_message, User* user_message, Crop* crop_message, Finance* finance_message);
// 查询作物信息
void Require_crop(Land* land_message, User* user_message, Crop* crop_message, Finance* finance_message);
// 查询财务信息
void Require_finance(Land* land_message, User* user_message, Crop* crop_message, Finance* finance_message);
// 输出财务信息
void Finance_input(Finance* p, int option);

int asset; // 总资产
int user_num; // 总人数
int crop_num; // 总作物数
int land_num; // 总地块数
int finance_num; // 总财务记录数

int main()
{
    Land* land_message = new Land;
    Crop* crop_message = new Crop;
    User* user_message = new User;
    Planting* planting_message = new Planting;
    Operation* operation_message = new Operation;
    Harvest* harvest_message = new Harvest;
    Finance* finance_message = new Finance;

    land_message->Next = nullptr;
    crop_message->Next = nullptr;
    user_message->Next = nullptr;
    planting_message->Next = nullptr;
    operation_message->Next = nullptr;
    harvest_message->Next = nullptr;
    finance_message->Next = nullptr;


/* 为保证程序正常运行，先往原系统中添加如下信息 */
    
    // 地块信息
        // 地块编号：1  土壤种类：砂质土  地块形状：正方形  地块面积：4公顷  地块位置：30°15'00"N，120°10'00"E
        // 地块编号：2  土壤种类：黏质土  地块形状：长方形  地块面积：6公顷  地块位置：30°15'00"N，120°10'00"E
        // 地块编号：3  土壤种类：壤土  地块形状：长方形  地块面积：8公顷  地块位置：30°15'00"N，120°10'00"E
    land_num = 3;

    ifstream fin_land;
    fin_land.open("land_message.txt", ios::in);

    while (!fin_land.eof())
    {
        Land* Landptr = new Land;
        fin_land >> Landptr->id >> Landptr->type >> Landptr->shape >> Landptr->area >> Landptr->location;
        Landptr->Next = land_message->Next;
        land_message->Next = Landptr;
    }

    fin_land.close();

    // 作物信息
        // 作物种类编号：1  作物名称：小麦  种植月份：3月  收货月份：9月  作物特性：禾本科小麦属植物
        // 作物种类编号：2  作物名称：水稻  种植月份：5月  收货月份：10月  作物特性：稻属谷类一年生禾本作物
        // 作物种类编号：3  作物名称：花生  种植月份：4月  收货月份：10月  作物特性：豆科落花生属植物
    ifstream fin_crop;
    fin_crop.open("crop_message.txt", ios::in);

    fin_crop >> crop_num;
    while (!fin_crop.eof())
    {
        Crop* Cropptr = new Crop;
        fin_crop >> Cropptr->id >> Cropptr->name >> Cropptr->plantingMonth >> Cropptr->harvestMonth >> Cropptr->characteristics;
        Cropptr->Next = crop_message->Next;
        crop_message->Next = Cropptr;
    }

    fin_crop.close();

    // 用户信息
        // 用户账号：10001  用户姓名：John  用户密码：1234567  用户职务：管理员
        // 用户账号：10002  用户姓名：Bob  用户密码：1234567  用户职务：操作员
        // 用户账号：10003  用户姓名：Lily  用户密码：1234567  用户职务：财务员
    ifstream fin_user;
    fin_user.open("user_message.txt", ios::in);

    fin_user >> user_num;
    while (!fin_user.eof())
    {
        User* Userptr = new User;
        fin_user >> Userptr->id >> Userptr->name >> Userptr->password >> Userptr->role;
        Userptr->Next = user_message->Next;
        user_message->Next = Userptr;
    }

    fin_user.close();

    // 财务信息
    ifstream fin_finance;
    fin_finance.open("finance_message.txt", ios::in);

    fin_finance >> asset;
    while (!fin_finance.eof())
    {
        Finance* Financeptr = new Finance;
        fin_finance >> Financeptr->date >> Financeptr->income >> Financeptr->expense;
        Financeptr->Next = finance_message->Next;
        finance_message->Next = Financeptr;
    }

    Login(user_message, operation_message, planting_message, harvest_message, land_message, crop_message, finance_message);
    system("pause");
    return 0;
}

/* 以下为基本操作集函数 */

/* 基本操作 */

/* 1.登录系统 */
void Login(User* user_message, Operation* operation_message, Planting* planting_message, Harvest* harvest_message, Land* land_message, Crop* crop_message, Finance* finance_message)
{
    // 起始界面
    cout << "\33[5m+\33[0m";
    for (int i = 0; i < 78; i ++ )
        cout << "\33[5m-\33[0m";
    cout << "\33[5m+\33[0m" << endl;
    cout << "\33[5m|\33[0m";
    for (int i = 0; i < 26; i ++ )
        cout << " ";
    cout << "欢迎使用果园作物管理系统！";
    for (int i = 0; i < 26; i ++ )
        cout << " ";
    cout << "\33[5m|\33[0m" << endl;
    cout << "\33[5m+\33[0m";
    for (int i = 0; i < 78; i ++ )
        cout << "\33[5m-\33[0m";
    cout << "\33[5m+\33[0m" << endl;

    delay(1);

    // 登录操作
    cout << "请先登录——" << endl;
    cout << "请输入您的用户账号：";
    int Id;
    cin >> Id;
    cout << "请输入您的用户密码：";
    string Password;
    cin >> Password;
    
    User* p = user_message;
    for (int i = 0; i <= user_num; i ++ )
    {
        if (p->id == Id) break;
        p = p->Next;
    }
    if (p->id != Id) // 找不到账号
    {
        for (int i = 0; i < 80; i ++ )
            cout << '-';
        cout << endl;
        for (int i = 0; i < 25; i ++ )
            cout << " ";
        cout << "对不起，您的账号输入错误!";
        cout << endl;
        for (int i = 0; i < 80; i ++ )
            cout << '-';
        cout << endl;
        InputError(user_message, operation_message, planting_message, harvest_message, finance_message, land_message, crop_message);
    }
    else // 找到账号
    {
        if (p->password == Password) // 密码正确
        {
            system("cls");
            cout << "+";
            for (int i = 0; i < 78; i ++ ) cout << "-";
            cout << "+";
            cout << endl;
            cout << "|   " << p->name << ",您好！";
            for (int i = 0; i < 64; i ++ )
                cout << ' ';
            cout << "|" << endl << "|";
            for (int i = 0; i < 10; i ++ )
                cout << ' ';
            cout << "账号：" << p->id;
            for (int i = 0; i < 15; i ++ )
                cout << ' ';
            cout << "|";
            for (int i = 0; i < 15; i ++ ) cout << " ";
            cout << "职务：";
            if (p->role == 1)
            {
                cout << "管理员";
                for (int i = 0; i < 14; i ++ )
                    cout << " ";
                cout << "|" << endl;
                cout << "+";
                for (int i = 0; i < 78; i ++ )
                    cout << '-';
                cout << "+";
                cout << endl;
                Administrator_Operation(user_message, land_message, crop_message, finance_message); // 进入管理员操作集
            }
            else if (p->role == 2)
            {
                cout << "操作员";
                for (int i = 0; i < 14; i ++ )
                    cout << " ";
                cout << "|" << endl;
                cout << "+";
                for (int i = 0; i < 78; i ++ )
                    cout << '-';
                cout << "+";
                cout << endl;
                Operator_Operation(planting_message, operation_message, harvest_message); // 进入操作员操作集
            }
            else if (p->role == 3)
            {
                cout << "财务员";
                for (int i = 0; i < 14; i ++ )
                    cout << " ";
                cout << "|" << endl;
                cout << "+";
                for (int i = 0; i < 78; i ++ )
                    cout << '-';
                cout << "+";
                cout << endl;
                Treasurer_Operation(finance_message); // 进入财务员操作集
            }
        }
        else // 密码错误
        {
            for (int i = 0; i < 80; i ++ )
                cout << '-';
            cout << endl;
            for (int i = 0; i < 20; i ++ )
                cout << " ";
            cout << "对不起，您的账号或密码输入错误!" << endl;
            for (int i = 0; i < 80; i ++ )
                cout << '-';
            cout << endl;
            InputError(user_message, operation_message, planting_message, harvest_message, finance_message, land_message, crop_message);
        }
    }
}

/* 2.结束界面 */
void ExitSystem()
{
    for (int i = 0; i < 80; i ++ )
        cout << "\33[5m-\33[0m";
    cout << endl;
    for (int i = 0; i < 30; i ++ )
        cout << ' ';
    cout << "正在退出中，请稍后……" << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "\33[5m-\33[0m";
    delay(3);
    system("cls");

    cout << "\33[5m+\33[0m";
    for (int i = 0; i < 78; i ++ )
        cout << "\33[5m-\33[0m";
    cout << "\33[5m+\33[0m" << endl;
    cout << "\33[5m|\33[0m";
    for (int i = 0; i < 23; i ++ )
        cout << " ";
    cout << "感谢使用果园作物管理系统，再见！";
    for (int i = 0; i < 23; i ++ )
        cout << " ";
    cout << "\33[5m|\33[0m" << endl;
    cout << "\33[5m+\33[0m";
    for (int i = 0; i < 78; i ++ )
        cout << "\33[5m-\33[0m";
    cout << "\33[5m+\33[0m" << endl;

    return;
}

/* 3.输入错误 */
void InputError(User* user_message, Operation* operation_message, Planting* planting_message, Harvest* harvest_message, Finance* finance_message, Land* land_message, Crop* crop_message)
{
    cout << "请问您想要——" << endl;
    for (int i = 0; i < 20; i ++ )
        cout << " ";
    cout << "A.重新登录";
    for (int i = 0; i < 20; i ++ )
        cout << " ";
    cout << "B.退出系统";
    cout << endl;
    char option;
    cin >> option;
    if (option == 'A')
    {
        system("cls");
        Login(user_message, operation_message, planting_message, harvest_message, land_message, crop_message, finance_message);
    }
    else if (option == 'B')
        ExitSystem();
}

/* 4. 延时 */
void delay(int seconds) //  参数必须为整型，表示延时多少秒
{
    clock_t start = clock();
    clock_t lay = (clock_t)seconds * CLOCKS_PER_SEC;
    while ((clock()-start) < lay);
}

/* 管理员操作集 */
void Administrator_Operation(User* user_message, Land* land_message, Crop* crop_message, Finance* finance_message)
{
    cout << endl << "请选择您想要进行的操作——" << endl;

    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "增加用户 - 1";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "删除用户 - 2";
    cout << endl;
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "修改用户 - 3";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "查询用户 - 4";
    cout << endl;
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "查询地块 - 5";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "查询作物 - 6";
    cout << endl;
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "查询财务 - 7";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "退出系统 - 8";
    cout << endl;

    cout << endl << "请输入您想要进行的操作后的数字：";
    int operate;
    cin >> operate;
    if (operate == 1)
        Add(user_message, finance_message, land_message, crop_message);
    else if (operate == 2)
        User_Delete(user_message, land_message, finance_message, crop_message);
    else if (operate == 3)
        Modify(user_message, land_message, crop_message, finance_message);
    else if (operate == 4)
        Require(user_message, land_message, crop_message, finance_message);
    else if (operate == 5)
        Require_land(land_message, user_message, crop_message, finance_message);
    else if (operate == 6)
        Require_crop(land_message, user_message, crop_message, finance_message);
    else if (operate == 7)
        Require_finance(land_message, user_message, crop_message, finance_message);
    else if (operate == 8)
        ExitSystem();
}

/* 1.增加用户 */
void Add(User* user_message, Finance* finance_message, Land* land_message, Crop* crop_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " 增加用户 ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << "请输入新用户账号：";
    int Id;
    cin >> Id;
    if (IsExist(Id, user_message))
    {
        cout << "该账号已被使用，请重新输入。";
        delay(1);
        Add(user_message, finance_message, land_message, crop_message);
    }
    else
    {
        cout << endl << "请输入新用户姓名：";
        string name;
        cin >> name;
        cout << endl << "请输入新用户密码：";
        string password;
        cin >> password;
        cout << endl << "请输入新用户职务：1：管理员 2：操作员 3：财务员";
        int role;
        cin >> role;

        // 增加新用户
        User* newperson = new User;
        newperson->id = Id;
        newperson->name = name;
        newperson->password = password;
        newperson->role = role;
        newperson->Next = user_message->Next;
        user_message->Next = newperson;
        user_num ++ ;

        fstream f_user;
	    f_user.open("user_message.txt", ios::out | ios::app);
	    f_user << newperson->id << endl;
        f_user << newperson->name << endl;
        f_user << newperson->password << endl;
        f_user << newperson->role << endl << endl;
	    f_user.close();

        fstream ofile("user_message.txt", ios::in | ios::out);
        ofile << user_num;
        ofile.close();

        cout << endl;
        for (int i = 0; i < 35; i ++ )
            cout << "-";
        cout << "添加成功！";
        for (int i = 0; i < 35; i ++ )
            cout << "-";
        cout << endl;
        Administrator_Operation(user_message, land_message, crop_message, finance_message);
    }
}

/* 2.删除用户 */
void User_Delete(User* user_message, Land* land_message, Finance* finance_message, Crop* crop_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " 删除用户 ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "请输入要删除用户的账号：";
    int Id;
    cin >> Id;
    if (!IsExist(Id, user_message))
    {
        cout << endl << "该账号不存在，请重新输入。";
        delay(2);
        User_Delete(user_message, land_message, finance_message, crop_message);
    }
    else
    {
        user p = user_message;
        while (p != nullptr && p->id != Id)
            p = p->Next;
        cout << endl;
        cout << "账号：" << Id;
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "|";
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "姓名：" << p->name;
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "|";
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "职务：";
        if (p->role == 1)
            cout << "管理员" << endl;
        else if (p->role == 2)
            cout << "操作员" << endl;
        else if (p->role == 3)
            cout << "财务员" << endl;
        cout << "请确认相关信息，确认删除？" << endl;
        for (int i = 0; i < 20; i ++ )
            cout << " ";
        cout << "A. Yes";
        for (int i = 0; i < 20; i ++ )
            cout << " ";
        cout << "B. No";
        cout << endl;

        char option;
        cin >> option;
        if (option == 'A')
        {
            int location = Find(Id, user_message);
            user p, s;
            if (location == 1) // 删除的是第一个用户
            {
                s = user_message; // s是要删除的用户
                if (user_message != nullptr) 
                {
                    user_message = user_message->Next;
                    free(s);
                    Administrator_Operation(user_message, land_message, crop_message, finance_message);
                    return;
                }
                else
                {
                    for (int i = 0; i < 35; i ++ )
                        cout << "-";
                    cout << "该用户不存在，删除失败！" ; // 空表
                    for (int i = 0; i < 35; i ++ )
                        cout << "-";
                    Administrator_Operation(user_message, land_message, crop_message, finance_message);
                    return;
                }
            }
            p = FindKth(location - 1, user_message); // 找到要删除的用户的前一个用户
            if (p == nullptr) // 用户不存在
            {
                for (int i = 0; i < 35; i ++ )
                    cout << "-";
                cout << "该用户不存在，删除失败！" ; // 空表
                for (int i = 0; i < 35; i ++ )
                    cout << "-";
                Administrator_Operation(user_message, land_message, crop_message, finance_message);
                return;
            }
            else if(p->Next == nullptr) // 用户不存在
            {
                for (int i = 0; i < 35; i ++ )
                    cout << "-";
                cout << "该用户不存在，删除失败！" ; // 空表
                for (int i = 0; i < 35; i ++ )
                    cout << "-";
                Administrator_Operation(user_message, land_message, crop_message, finance_message);
                return;
            }
            else
            {
                s = p->Next; // s是要删除的用户
                p->Next = s->Next;
                free(s);
            }

            cout << endl;
            for (int i = 0; i < 35; i ++ )
                cout << "-";
            cout << "删除成功！";
            user_num -- ;
            for (int i = 0; i < 35; i ++ )
                cout << "-";

            fstream f_user;
	        f_user.open("temp.txt", ios::out);
            f_user << user_num << endl << endl;
            User* q = new User;
            q = user_message->Next->Next;
            while (q != nullptr)
            {
                f_user << q->id << endl;
                f_user << q->name << endl;
                f_user << q->password << endl;
                f_user << q->role << endl << endl;
                q = q->Next;
            }
            fstream outf;
            outf.open("user_message.txt", ios::out);
            fstream inf;
            inf.open("temp.txt", ios::in);
            string str;
            while (getline(inf, str))
            {
                outf << str << endl;
            }
            outf << endl;
            f_user.close();
            outf.close();
            inf.close();

            Administrator_Operation(user_message, land_message, crop_message, finance_message);
            return;
        }
        else if (option == 'B')
        {
            for (int i = 0; i < 80; i ++ )
                cout << "-";
            cout << endl;
            for (int i = 0; i < 28; i ++ )
                cout << ' ';
            cout << "请重新输入删除用户信息。";
            cout << endl;
            for (int i = 0; i < 80; i ++ )
                cout << "-";
            User_Delete(user_message, land_message, finance_message, crop_message);
        }
    }
}

/* 3.修改用户 */
void Modify(User* user_message, Land* land_message, Crop* crop_message, Finance* finance_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " 修改用户 ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << endl << endl;

    delay(1);

    cout << "请输入要修改用户的账号：";
    int Id;
    cin >> Id;
    if (!IsExist(Id, user_message))
    {
        cout << "该账号不存在，请重新输入。";
        delay(2);
        Modify(user_message, land_message, crop_message, finance_message);
    }
    else
    {
        user p = user_message;
        while (p != nullptr && p->id != Id)
            p = p->Next;
        
        cout << "您要修改——" << endl;
        for (int i = 0; i < 10; i ++ )
            cout << " ";
        cout << "用户账号 - 1";
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "|";
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "用户姓名 - 2" << endl;
        for (int i = 0; i < 10; i ++ )
            cout << " ";
        cout << "用户职务 - 3";
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "|";
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "用户密码 - 4" << endl;
        cout << "请输入要修改内容后面的数字（输入-1表示修改结束）：";
        int option;
        while (scanf("%d", &option) != -1)
        {
            if (option == 1)
            {
                cout << "请输入修改后的账号：";
                int newId;
                cin >> newId;
                if (IsExist(newId, user_message))
                {
                    cout << "该账号已存在，请重新输入。";
                    Modify(user_message, land_message, crop_message, finance_message);
                }
                else
                {
                    p->id = newId;
                    cout << endl;
                    for (int i = 0; i < 29; i ++ )
                        cout << "-";
                    cout << "修改成功！请继续进行修改。";

                    fstream f_user;
	                f_user.open("temp.txt", ios::out);
                    f_user << user_num << endl << endl;
                    User* p = new User;
                    p = user_message->Next->Next;
                    while (p != nullptr)
                    {
                        f_user << p->id << endl;
                        f_user << p->name << endl;
                        f_user << p->password << endl;
                        f_user << p->role << endl << endl;
                        p = p->Next;
                    }
                    fstream outf;
                    outf.open("user_message.txt", ios::out);
                    fstream inf;
                    inf.open("temp.txt", ios::in);
                    string s;
                    while (getline(inf, s)) //将temp.txt的内容写到test.txt
                    {
                        outf << s << endl;
                    }
                    outf << endl;
                    f_user.close();
                    outf.close();
                    inf.close();

                    for (int i = 0; i < 29; i ++ )
                        cout << "-";
                    cout << endl;
                    cout << "您要修改——" << endl;
                    for (int i = 0; i < 10; i ++ )
                        cout << " ";
                    cout << "用户账号 - 1";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "|";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "用户姓名 - 2" << endl;
                    for (int i = 0; i < 10; i ++ )
                        cout << " ";
                    cout << "用户职务 - 3";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "|";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "用户密码 - 4" << endl;
                    cout << "请输入要修改内容后面的数字（输入-1表示修改结束）：";
                }
            }
            else if (option == 2)
            {
                cout << "请输入修改后的姓名：";
                string newName;
                cin >> newName;
                p->name = newName;
                cout << endl;
                for (int i = 0; i < 29; i ++ )
                    cout << "-";
                cout << "修改成功！请继续进行修改。";

                fstream f_user;
	            f_user.open("temp.txt", ios::out);
                f_user << user_num << endl << endl;
                User* p = new User;
                p = user_message->Next->Next;
                while (p != nullptr)
                {
                    f_user << p->id << endl;
                    f_user << p->name << endl;
                    f_user << p->password << endl;
                    f_user << p->role << endl << endl;
                    p = p->Next;
                }
                fstream outf;
                outf.open("user_message.txt", ios::out);
                fstream inf;
                inf.open("temp.txt", ios::in);
                string s;
                while (getline(inf, s)) //将temp.txt的内容写到test.txt
                {
                    outf << s << endl;
                }
                outf << endl;
                f_user.close();
                outf.close();
                inf.close();

                for (int i = 0; i < 29; i ++ )
                    cout << "-";
                cout << endl;
                cout << "您要修改——" << endl;
                for (int i = 0; i < 10; i ++ )
                    cout << " ";
                cout << "用户账号 - 1";
                for (int i = 0; i < 5; i ++ )
                    cout << " ";
                cout << "|";
                for (int i = 0; i < 5; i ++ )
                    cout << " ";
                cout << "用户姓名 - 2" << endl;
                for (int i = 0; i < 10; i ++ )
                    cout << " ";
                cout << "用户职务 - 3";
                for (int i = 0; i < 5; i ++ )
                    cout << " ";
                cout << "|";
                for (int i = 0; i < 5; i ++ )
                    cout << " ";
                cout << "用户密码 - 4" << endl;
                cout << "请输入要修改内容后面的数字（输入-1表示修改结束）：";
            }
            else if (option == 3)
            {
                cout << "请输入修改后的职务：1：管理员 2：操作员 3：财务员";
                int newRole;
                cin >> newRole;
                p->role = newRole;
                cout << endl;
                for (int i = 0; i < 29; i ++ )
                    cout << "-";
                cout << "修改成功！请继续进行修改。";

                fstream f_user;
	            f_user.open("temp.txt", ios::out);
                f_user << user_num << endl << endl;
                User* p = new User;
                p = user_message->Next->Next;
                while (p != nullptr)
                {
                    f_user << p->id << endl;
                    f_user << p->name << endl;
                    f_user << p->password << endl;
                    f_user << p->role << endl << endl;
                    p = p->Next;
                }
                fstream outf;
                outf.open("user_message.txt", ios::out);
                fstream inf;
                inf.open("temp.txt", ios::in);
                string s;
                while (getline(inf, s)) //将temp.txt的内容写到test.txt
                {
                    outf << s << endl;
                }
                outf << endl;
                f_user.close();
                outf.close();
                inf.close();

                for (int i = 0; i < 29; i ++ )
                    cout << "-";
                cout << endl;
                for (int i = 0; i < 10; i ++ )
                        cout << " ";
                    cout << "用户账号 - 1";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "|";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "用户姓名 - 2" << endl;
                    for (int i = 0; i < 10; i ++ )
                        cout << " ";
                    cout << "用户职务 - 3";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "|";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "用户密码 - 4" << endl;
                    cout << "请输入要修改内容后面的数字（输入-1表示修改结束）：";
            }
            else if (option == 4)
            {
                cout << "请输入修改后的密码：";
                string newPassword;
                cin >> newPassword;
                p->password = newPassword;
                cout << endl;
                for (int i = 0; i < 29; i ++ )
                    cout << "-";
                cout << "修改成功！请继续进行修改。";

                fstream f_user;
	            f_user.open("temp.txt", ios::out);
                f_user << user_num << endl << endl;
                User* p = new User;
                p = user_message->Next->Next;
                while (p != nullptr)
                {
                    f_user << p->id << endl;
                    f_user << p->name << endl;
                    f_user << p->password << endl;
                    f_user << p->role << endl << endl;
                    p = p->Next;
                }
                fstream outf;
                outf.open("user_message.txt", ios::out);
                fstream inf;
                inf.open("temp.txt", ios::in);
                string s;
                while (getline(inf, s))
                {
                    outf << s << endl;
                }
                outf << endl;
                f_user.close();
                outf.close();
                inf.close();

                for (int i = 0; i < 29; i ++ )
                    cout << "-";
                cout << endl;
                for (int i = 0; i < 10; i ++ )
                        cout << " ";
                    cout << "用户账号 - 1";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "|";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "用户姓名 - 2" << endl;
                    for (int i = 0; i < 10; i ++ )
                        cout << " ";
                    cout << "用户职务 - 3";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "|";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "用户密码 - 4" << endl;
                    cout << "请输入要修改内容后面的数字（输入-1表示修改结束）：";
            }
            else if (option == -1)
            {
                cout << endl;
                Administrator_Operation(user_message, land_message, crop_message, finance_message);
            }
        }
    }
}

/* 4.查询用户 */
void Require(User* user_message, Land* land_message, Crop* crop_message, Finance* finance_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " 查询用户 ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "您可以选择以下几种查询方式："<< endl;
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "A. 账号查询";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "B. 姓名查询";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "C. 职务查询" << endl;
    cout << "请输出您想选择的查询方式：";
    char option;
    cin >> option;

    if (option == 'A')
    {
        cout << "请输入您要查询的账号：";
        int Id;
        cin >> Id;
        cout << endl;
        if (!IsExist(Id, user_message))
        {
            for (int i = 0; i < 27; i ++ )
                cout << "-";
            cout << "该账号不存在，请重新查询。";
            for (int i = 0; i < 27; i ++ )
                cout << "-";
            cout << endl;

            delay(2);
            Require(user_message, land_message, crop_message, finance_message);
        }
        else
        {
            user p = user_message;
            while (p != nullptr && p->id != Id)
                p = p->Next;
            for (int i = 0; i < 35; i ++ )
                cout << "-";
            cout << "查询成功！";
            for (int i = 0; i < 35; i ++ )
                cout << "-";
            cout << endl;
            for (int i = 0; i < 80; i ++ )
                cout << "-";
            cout << endl;
            Require_input(p);
            for (int i = 0; i < 80; i ++ )
                cout << "-";
            cout << endl;
            Administrator_Operation(user_message, land_message, crop_message, finance_message);
        }
    }
    else if (option == 'B')
    {
        cout << "请输入您要查询的姓名：";
        string Name;
        cin >> Name;
        if (!IsExist_name(Name, user_message))
        {
            for (int i = 0; i < 27; i ++ )
                cout << "-";
            cout << "该姓名不存在，请重新查询。";
            for (int i = 0; i < 27; i ++ )
                cout << "-";
            cout << endl;

            delay(2);
            Require(user_message, land_message, crop_message, finance_message);
        }
        User* p = user_message;
        for (int i = 0; i < 35; i ++ )
            cout << "-";
        cout << "查询成功！";
        for (int i = 0; i < 35; i ++ )
            cout << "-";
        cout << endl;
        for (int i = 0; i < 80; i ++ )
            cout << "-";
        cout << endl;
        for (int i = 0; i <= user_num; i ++ )
        {
            if (p->name == Name)
                Require_input(p);
            p = p->Next;
            if (i == user_num) break;
        }
        for (int i = 0; i < 80; i ++ )
            cout << "-";
        cout << endl;
        Administrator_Operation(user_message, land_message, crop_message, finance_message);
    }
    else if (option == 'C')
    {
        cout << "请输入您要查询的职务：1：管理员 2：操作员 3：财务员" << endl;
        int Role;
        cin >> Role;
        User* p = new User;
        p = user_message->Next->Next;
        for (int i = 0; i < 35; i ++ )
            cout << "-";
        cout << "查询成功！";
        for (int i = 0; i < 35; i ++ )
            cout << "-";
        cout << endl;
        for (int i = 0; i < 80; i ++ )
            cout << "-";
        cout << endl;
        while (p)
        {
            if (p->role == Role)
                Require_input(p);
            p = p->Next;
        }
        for (int i = 0; i < 80; i ++ )
            cout << "-";
        cout << endl;
        Administrator_Operation(user_message, land_message, crop_message, finance_message);
    }
}

/* 5.查询地块信息 */
void Require_land(Land* land_message, User* user_message, Crop* crop_message, Finance* finance_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " 查询地块 ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "请输入您要查询的地块编号：";
    int Id;
    cin >> Id;
    cout << endl;
    Land* p = land_message->Next->Next;
    while (p)
    {
        if (p->id == Id)
        {
            for (int i = 0; i < 35; i ++ )
                cout << "-";
            cout << "查询成功！";
            for (int i = 0; i < 35; i ++ )
                cout << "-";
            cout << endl;
            for (int i = 0; i < 80; i ++ )
                cout << "-";
            cout << endl;

            for (int i = 0; i < 10; i ++ )
                cout << " ";
            cout << "地块编号：" << p->id;
            cout << '\t' << "|" << '\t';
            cout << "土壤种类：" << p->type;
            cout << '\t' << "|" << '\t';
            cout << "地块形状；" << p->shape;
            cout << endl;
            for (int i = 0; i < 10; i ++ )
                cout << " ";
            cout << "地块面积：" << p->area;
            cout << '\t' << "|" << '\t';
            cout << "地块位置：" << p->location;
            cout << endl;

            for (int i = 0; i < 80; i ++ )
                cout << "-";
            cout << endl;
            Administrator_Operation(user_message, land_message, crop_message, finance_message);
            return;
        }
        p = p->Next;
    }
    for (int i = 0; i < 27; i ++ )
        cout << "-";
    cout << "该地块不存在，请重新查询。";
    for (int i = 0; i < 27; i ++ )
        cout << "-";
    cout << endl;
    delay(2);
    Require_land(land_message, user_message, crop_message, finance_message);
    return;
}

/* 6.查询作物信息 */
void Require_crop(Land* land_message, User* user_message, Crop* crop_message, Finance* finance_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " 查询作物 ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "请输入您要查询的作物编号：";
    int Id;
    cin >> Id;
    cout << endl;
    Crop* p = crop_message->Next;
    for (int i = 0; i <= crop_num; i ++ )
    {
        if (p->id == Id)
        {
            for (int i = 0; i < 35; i ++ )
                cout << "-";
            cout << "查询成功！";
            for (int i = 0; i < 35; i ++ )
                cout << "-";
            cout << endl;
            for (int i = 0; i < 80; i ++ )
                cout << "-";
            cout << endl;

            for (int i = 0; i < 10; i ++ )
                cout << " ";
            cout << "作物编号：" << p->id;
            cout << '\t' << "|" << '\t';
            cout << "作物名称：" << p->name;
            cout << '\t' << "|" << '\t';
            cout << "种植月份；" << p->plantingMonth;
            cout << endl;
            for (int i = 0; i < 10; i ++ )
                cout << " ";
            cout << "收获月份：" << p->harvestMonth;
            cout << '\t' << "|" << '\t';
            cout << "作物特性：" << p->characteristics;
            cout << endl;

            for (int i = 0; i < 80; i ++ )
                cout << "-";
            cout << endl;
            Administrator_Operation(user_message, land_message, crop_message, finance_message);
            return;
        }
        p = p->Next;
    }
    for (int i = 0; i < 27; i ++ )
        cout << "-";
    cout << "该作物不存在，请重新查询。";
    for (int i = 0; i < 27; i ++ )
        cout << "-";
    cout << endl;
    delay(2);
    Require_crop(land_message, user_message, crop_message, finance_message);
    return;
}

/* 7.查询财务信息 */
void Require_finance(Land* land_message, User* user_message, Crop* crop_message, Finance* finance_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " 查询财务 ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "请问您要查询——" << endl;
    for (int i = 0; i < 10; i ++ )
        cout << ' ';
    cout << "收入信息 - 1";
    for (int i = 0; i < 10; i ++ )
        cout << ' ';
    cout << "支出信息 - 2";
    cout << endl;

    int option;
    cin >> option;
    Finance* p = finance_message->Next->Next;

    for (int i = 0; i < 35; i ++ )
        cout << "-";
    cout << "查询成功！";
    for (int i = 0; i < 35; i ++ )
        cout << "-";
    cout << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-";
    cout << endl;

    if (option == 1)
    {
        while (p)
        {
            if (p->expense == 0)
                Finance_input(p, option);
            p = p->Next;
        }
    }
    else if (option == 2)
    {
        while (p)
        {
            if (p->income == 0)
                Finance_input(p, option);
            p = p->Next;
        }
    }
    cout << endl;

    Administrator_Operation(user_message, land_message, crop_message, finance_message);
}

/* 8.输出财务信息 */
void Finance_input(Finance* p, int option)
{
    for (int i = 0; i < 20; i ++ )
        cout << " ";
    cout << "时间：" << p->date;
    for (int i = 0; i < 20; i ++ )
        cout << ' ';
    if (option == 1)
        cout << "收入：" << p->income << endl;
    else if (option == 2)
        cout << "支出：" << p->expense << endl;
}

/* 根据Id判断用户是否已经存在 */
bool IsExist(int Id, User* user_message)
{
    User* p = user_message->Next;
    while (p)
    {
        if (p->id == Id) return true;
        p = p->Next;
    }
    return false;
}

/* 根据Name判断用户是否已经存在 */
bool IsExist_name(string Name, User* user_message)
{
    User* p = user_message;
    for (int i = 0; i < user_num; i ++ )
    {
        if (p->name == Name) break;
        p = p->Next;
        if (i == user_num) return false;
    }
    if (Name == p->name)
        return true;
}

/* 返回第K个用户 */
User* FindKth(int K, User* PtrL)
{
    User* p = PtrL;
    int i = 1;
    while (p != nullptr && i < K)
    {
        p = p->Next;
        i ++;
    }
    if (i == K)
        return p;
    else
        return nullptr;
}

/* 返回Id的位置 */
int Find(int Id, User* user_message)
{
    user p = user_message;
    int location = 1;
    while (p != nullptr && p->id != Id)
    {
        p = p->Next;
        location ++ ;
    }
    if (p->id == Id)
        return location;
    else
        return 0;
}

/* 返回用户查询结果 */
void Require_input(User* p)
{
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "账号：" << p->id;
    cout << '\t' << "|" << '\t';
    cout << "姓名：" << p->name;
    cout << '\t' << "|" << '\t';
    cout << "职务；";
    if (p->role == 1)
        cout << "管理员";
    else if (p->role == 2)
        cout << "操作员";
    else if (p->role == 3)
        cout << "财务员";
    cout << endl;
}

/* 操作员操作集 */
void Operator_Operation(Planting* planting_message, Operation* operation_message, Harvest* harvest_message)
{
    cout << endl << "请选择您想要进行的操作——" << endl;

    for (int i = 0; i < 20; i ++ )
        cout << " ";
    cout << "种植 - 1";
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "经营 - 2";
    cout << endl;
    for (int i = 0; i < 20; i ++ )
        cout << " ";
    cout << "采摘 - 3";
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "退出系统 - 4" << endl;
    cout << endl;

    cout << endl << "请输入您想要进行的操作后面的数字：";
    int operate;
    cin >> operate;
    cout << endl;
    if (operate == 1)
        Plant(planting_message, operation_message, harvest_message);
    else if (operate == 2)
        Operate(planting_message, operation_message, harvest_message);
    else if (operate == 3)
        Picking(planting_message, operation_message, harvest_message);
    else if (operate == 4)
        ExitSystem();
}

/* 1.种植 */
void Plant(Planting* planting_message, Operation* operation_message, Harvest* harvest_message)
{
    Planting* p = new Planting;

    system("cls");
    for (int i = 0; i < 36; i ++ )
        printf("\33[5m*\33[0m");
    cout << " 种植 ";
    for (int i = 0; i < 36; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "请输入种植记录编号：";
    cin >> p->id;
    cout << endl << "请输入种植地块编号：";
    cin >> p->landId;
    cout << endl << "请输入种植作物种类编号：";
    cin >> p->cropId;
    cout << endl << "请输入种植数量：";
    cin >> p->quantity;
    cout << endl << "请输入种植时间：";
    cin >> p->date;
    cout << endl << "请输入种植人：";
    cin >> p->implementer;
    cout << endl << "请输入检查人：";
    cin >> p->inspector;

    p->Next = planting_message->Next;
    planting_message->Next = p;

    fstream f_planting;
	f_planting.open("temp.txt", ios::out);
    Planting* q = new Planting;
    q = planting_message->Next;
    while (q != nullptr)
    {
        f_planting << q->id << endl;
        f_planting << q->landId << endl;
        f_planting << q->cropId << endl;
        f_planting << q->quantity << endl;
        f_planting << q->date << endl;
        f_planting << q->implementer << endl;
        f_planting << q->inspector << endl << endl;
        q = q->Next;
    }
    fstream outf;
    outf.open("planting_message.txt", ios::out);
    fstream inf;
    inf.open("temp.txt", ios::in);
    string s;
    while (getline(inf, s))
    {
        outf << s << endl;
    }
    outf << endl;
    f_planting.close();
    outf.close();
    inf.close();

    cout << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-"; // 第一行
    for (int i = 0; i < 35; i ++ )
        cout << " "; // 第二行
    cout << endl << "种植成功！";
    for (int i = 0; i < 35; i ++ )
        cout << " ";
    cout << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "种植记录编号：" << p->id;
    cout << '\t' << "|" << '\t';
    cout << "种植地块编号：" << p->landId;
    cout << '\t' << "|" << '\t';
    cout << "种植作物种类编号：" << p->cropId << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "种植数量：" << p->quantity;
    cout << '\t' << "|" << '\t';
    cout << "种植时间：" << p->date;
    cout << '\t' << "|" << '\t';
    cout << "种植人：" << p->implementer << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "检查人：" << p->inspector << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-"; // 第四行
    cout << endl;

    Operator_Operation(planting_message, operation_message, harvest_message);
}

/* 2.经营 */
void Operate(Planting* planting_message, Operation* operation_message, Harvest* harvest_message)
{
    Operation* p = new Operation;
    
    system("cls");
    for (int i = 0; i < 36; i ++ )
        printf("\33[5m*\33[0m");
    cout << " 经营 ";
    for (int i = 0; i < 36; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "请输入经营记录编号：";
    cin >> p->id;
    cout << endl << "请输入经营种类：1：施肥 2：浇水 3：除草";
    cin >> p->operationType;
    cout << endl << "请输入经营时间：";
    cin >> p->date;
    cout << endl << "请输入经营人：";
    cin >> p->implementer;
    cout << endl << "请输入检查人：";
    cin >> p->inspector;

    p->Next = operation_message->Next;
    operation_message->Next = p;

    fstream f_operation;
	f_operation.open("temp.txt", ios::out);
    Operation* q = new Operation;
    q = operation_message->Next;
    while (q != nullptr)
    {
        f_operation << q->id << endl;
        f_operation << q->operationType << endl;
        f_operation << q->date << endl;
        f_operation << q->implementer << endl;
        f_operation << q->inspector << endl << endl;
        q = q->Next;
    }
    fstream outf;
    outf.open("operation_message.txt", ios::out);
    fstream inf;
    inf.open("temp.txt", ios::in);
    string s;
    while (getline(inf, s))
    {
        outf << s << endl;
    }
    outf << endl;
    f_operation.close();
    outf.close();
    inf.close();

    cout << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-"; // 第一行
    cout << endl;
    for (int i = 0; i < 35; i ++ )
        cout << " "; // 第二行
    cout << "经营成功！" << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-"; // 第一行
    cout << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "经营记录编号：" << p->id;
    cout << '\t' << "|" << '\t';
    cout << "经营种类：";
    if (p->operationType == 1)
        cout << "施肥";
    else if (p->operationType == 2)
        cout << "浇水";
    else if (p->operationType == 3)
        cout << "除草";
    cout << '\t' << "|" << '\t';
    cout << "经营时间：" << p->date << endl;
    for (int i = 0; i < 5; i ++ )
        cout << ' ';
    cout << "经营人：" << p->implementer;
    cout << '\t' << "        |" << '\t';
    cout << "检查人：" << p->inspector << '\t' << endl;
    for (int i = 0; i < 80; i ++ ) cout << "-"; // 第四行
    cout << endl;

    Operator_Operation(planting_message, operation_message, harvest_message);
}

/* 3.采摘 */
void Picking(Planting* planting_message, Operation* operation_message, Harvest* harvest_message)
{
    Harvest* p = new Harvest;

    system("cls");
    for (int i = 0; i < 36; i ++ )
        printf("\33[5m*\33[0m");
    cout << " 采摘 ";
    for (int i = 0; i < 36; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "请输入采摘记录编号：";
    cin >> p->id;
    cout << endl << "请输入采摘地块：";
    cin >> p->landId;
    cout << endl << "请输入采摘作物种类：";
    cin >> p->cropId;
    cout << endl << "请输入采摘数量：";
    cin >> p->quantity;
    cout << endl << "请输入采摘时间：";
    cin >> p->date;
    cout << endl << "请输入采摘人：";
    cin >> p->implementer;
    cout << endl << "请输入检查人：";
    cin >> p->inspector;

    p->Next = harvest_message->Next;
    harvest_message->Next = p;

    fstream f_picking;
	f_picking.open("temp.txt", ios::out);
    Harvest* q = new Harvest;
    q = harvest_message->Next;
    while (q != nullptr)
    {
        f_picking << q->id << endl;
        f_picking << q->landId << endl;
        f_picking << q->cropId << endl;
        f_picking << q->quantity << endl;
        f_picking << q->date << endl;
        f_picking << q->implementer << endl;
        f_picking << q->inspector << endl << endl;
        q = q->Next;
    }
    fstream outf;
    outf.open("harvest_message.txt", ios::out);
    fstream inf;
    inf.open("temp.txt", ios::in);
    string s;
    while (getline(inf, s))
    {
        outf << s << endl;
    }
    outf << endl;
    f_picking.close();
    outf.close();
    inf.close();

    cout << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-"; // 第一行
    cout << endl;
    for (int i = 0; i < 35; i ++ )
        cout << " "; // 第二行
    cout << "采摘成功！" << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-"; // 第一行
    cout << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "采摘记录编号：" << p->id;
    cout << '\t' << "|" << '\t';
    cout << "采摘地块：" << p->landId;
    cout << '\t' << "|" << '\t';
    cout << "采摘作物种类编号：" << p->cropId << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "采摘数量：" << p->quantity;
    cout << '\t' << "|" << '\t';
    cout << "采摘时间：" << p->date;
    cout << '\t' << "|" << '\t';
    cout << "采摘人：" << p->implementer << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "检查人：" << p->inspector << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-"; // 第四行
    cout << endl;

    Operator_Operation(planting_message, operation_message, harvest_message);
}

/* 财务员操作集 */
void Treasurer_Operation(Finance* finance_message)
{
    cout << endl << "请选择您想要进行的操作——" << endl;

    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "记录收入 - 1";
    cout << '\t' << "|" << '\t';
    cout << "记录支出 - 2";
    cout << '\t' << "|" << '\t';
    cout << "退出系统 - 3" << endl;
    cout << endl << "请输入您想要进行的操作后面的数字：";

    int operate;
    cin >> operate;
    cout << endl;
    if (operate == 1)
        Income(finance_message);
    else if (operate == 2)
        Expense(finance_message);
    else if (operate == 3)
        ExitSystem();
}

/* 1.记录收入 */
void Income(Finance* finance_message)
{
    Finance* p = new Finance;

    cout << "请输入收入时间：";
    cin >> p->date;
    cout << "请输入收入额：";
    cin >> p->income;
    p->expense = 0;
    asset += p->income;

    p->Next = finance_message->Next;
    finance_message->Next = p;

    fstream ofile("finance_message.txt", ios::in | ios::out);
    ofile << asset;
    ofile.close();

    fstream f_finance;
	f_finance.open("finance_message.txt", ios::out | ios::app);
	f_finance << p->date << endl;
    f_finance << p->income << endl;
    f_finance << p->expense << endl << endl;
	f_finance.close();

    for (int i = 0; i < 80; i ++ )
        cout << "\33[5m-\33[0m";
    cout << endl;
    for (int i = 0; i < 30; i ++ )
        cout << ' ';
    cout << "正在为您记录，请稍后……" << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "\33[5m-\33[0m";
    delay(3);
    system("cls");

    for (int i = 0; i < 80; i ++ )
        cout << "-"; // 第一行
    cout << endl;
    for (int i = 0; i < 35; i ++ )
        cout << " "; // 第二行
    cout << "记录成功！" << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-";
    cout << endl;
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "本次收入：" << p->income;
    cout << '\t' << "               |" << '\t';
    cout << "          总资产：" << asset << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-";
    cout << endl << endl;

    Treasurer_Operation(finance_message);
}

/* 2.记录支出 */
void Expense(Finance* finance_message)
{
    Finance* p = new Finance;

    cout << "请输入支出时间：";
    cin >> p->date;
    cout << "请输入支出额：";
    cin >> p->expense;
    p->income = 0;
    asset -= p->expense;

    p->Next = finance_message->Next;
    finance_message->Next = p;

    fstream ofile("finance_message.txt", ios::in | ios::out);
    ofile << asset;
    ofile.close();

    fstream f_finance;
	f_finance.open("finance_message.txt", ios::out | ios::app);
	f_finance << p->date << endl;
    f_finance << p->income << endl;
    f_finance << p->expense << endl << endl;
	f_finance.close();

    for (int i = 0; i < 80; i ++ )
        cout << "\33[5m-\33[0m";
    cout << endl;
    for (int i = 0; i < 30; i ++ )
        cout << ' ';
    cout << "正在为您记录，请稍后……" << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "\33[5m-\33[0m";
    delay(3);
    system("cls");

    for (int i = 0; i < 80; i ++ )
        cout << "-"; // 第一行
    cout << endl;
    for (int i = 0; i < 35; i ++ )
        cout << " "; // 第二行
    cout << "记录成功！" << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-";
    cout << endl;
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "本次支出：" << p->expense;
    cout << '\t' << "               |" << '\t';
    cout << "          总资产：" << asset << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-";
    cout << endl << endl;

    Treasurer_Operation(finance_message);
}