/* ��԰�������ϵͳ */

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

/* ����Ϊ���������ṹ�� */

// 1.�ؿ�
typedef struct Land *land;
struct Land
{
    int id; // �ؿ���
    string type; // ��������
    string shape; // �ؿ���״
    double area; // �ؿ����
    string location; // �ؿ�λ��
    Land* Next; // ��һ���ؿ�
};

// 2.����
typedef struct Crop *crop;
struct Crop
{
    int id; // ����������
    string name; // ��������
    string plantingMonth; // ��ֲ�·�
    string harvestMonth; // �ջ��·�
    string characteristics; // ��������
    Crop* Next; // ��һ������
};

// 3.�û�
typedef struct User *user;
struct User
{
    int id; // �û��˺�
    string name; // �û�����
    string password; // �û�����
    int role; // �û�ְ��1������Ա 2������Ա 3������Ա
    User* Next; // ��һ���û�
};

/* �������ĸ������������ṹ�� */

// 1.��ֲ
typedef struct Planting *planting;
struct Planting
{
    int id; // ��ֲ��¼���
    int landId; // ��ֲ�ؿ���
    int cropId; // ��ֲ����������
    int quantity; // ��ֲ����
    string date; // ��ֲʱ��
    string implementer; // ��ֲ��
    string inspector; // �����
    Planting* Next; // ��һ����ֲ����
};

// 2.��Ӫ
typedef struct Operation *operation;
struct Operation
{
    int id; // ��Ӫ��¼���
    int operationType; // ��Ӫ���ࣺ1��ʩ�� 2����ˮ 3������
    string date; // ��Ӫʱ��
    string implementer; // ��Ӫ��
    string inspector; // ����� 
    Operation* Next; // ��һ����Ӫ����
};

// 3.��ժ
typedef struct Harvest *harvest;
struct Harvest
{
    int id; // ��ժ��¼���
    int landId; // ��ժ�ؿ�
    int cropId; // ��ժ��������
    int quantity; // ��ժ����
    string date; // ��ժʱ��
    string implementer; // ��ժ��
    string inspector; // �����
    Harvest* Next; // ��һ����ժ����
};

// 4.����
typedef struct Finance *finance;
struct Finance
{
    string date; // ʱ��
    double income; // ����
    double expense; // ֧��
    Finance* Next; // ��һ���������
};

/* ����Ϊ�Զ��庯������ */

// ��¼ϵͳ
void Login(User* user_message, Operation* operation_message, Planting* planting_message, Harvest* harvest_message, Land* land_message, Crop* crop_message, Finance* finance_message);
// ��������
void ExitSystem();
// ����������
void InputError(User* user_message, Operation* operation_message, Planting* planting_message, Harvest* harvest_message, Finance* finance_message, Land* land_message, Crop* crop_message);
//����Ա������
void Administrator_Operation(User* user_message, Land* land_message, Crop* crop_message, Finance* finance_message);
// �����û�
void Add(User* user_message, Finance* finance_message, Land* land_message, Crop* crop_message);
// ɾ���û�
void User_Delete(User* user_message, Land* land_message, Finance* finance_message, Crop* crop_message);
// �޸��û�
void Modify(User* user_message, Land* land_message, Crop* crop_message, Finance* finance_message);
// ��ѯ�û�
void Require(User* user_message, Land* land_message, Crop* crop_message, Finance* finance_message);
// ����Id�ж��û��Ƿ��Ѵ���
bool IsExist(int Id, User* user_message);
// ���ص�K���û�
User* FindKth(int K, User* PtrL);
// ����Id��λ��
int Find(int Id, User* user_message);
// ����Ա������
void Operator_Operation(Planting* planting_message, Operation* operation_message, Harvest* harvest_message);
// ��ֲ
void Plant(Planting* planting_message, Operation* operation_message, Harvest* harvest_message);
// ��Ӫ
void Operate(Planting* planting_message, Operation* operation_message, Harvest* harvest_message);
// ��ժ
void Picking(Planting* planting_message, Operation* operation_message, Harvest* harvest_message);
// ����Ա������
void Treasurer_Operation(Finance* finance_message);
// ��¼����
void Income(Finance* finance_message);
// ��¼֧��
void Expense(Finance* finance_message);
// ���ز�ѯ���
void Require_input(User* p);
// ����Name�ж��û��Ƿ��Ѵ���
bool IsExist_name(string Name, User* user_message);
// ��ʱ
void delay(int seconds);
// ��ѯ�ؿ���Ϣ
void Require_land(Land* land_message, User* user_message, Crop* crop_message, Finance* finance_message);
// ��ѯ������Ϣ
void Require_crop(Land* land_message, User* user_message, Crop* crop_message, Finance* finance_message);
// ��ѯ������Ϣ
void Require_finance(Land* land_message, User* user_message, Crop* crop_message, Finance* finance_message);
// ���������Ϣ
void Finance_input(Finance* p, int option);

int asset; // ���ʲ�
int user_num; // ������
int crop_num; // ��������
int land_num; // �ܵؿ���
int finance_num; // �ܲ����¼��

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


/* Ϊ��֤�����������У�����ԭϵͳ�����������Ϣ */
    
    // �ؿ���Ϣ
        // �ؿ��ţ�1  �������ࣺɰ����  �ؿ���״��������  �ؿ������4����  �ؿ�λ�ã�30��15'00"N��120��10'00"E
        // �ؿ��ţ�2  �������ࣺ�����  �ؿ���״��������  �ؿ������6����  �ؿ�λ�ã�30��15'00"N��120��10'00"E
        // �ؿ��ţ�3  �������ࣺ����  �ؿ���״��������  �ؿ������8����  �ؿ�λ�ã�30��15'00"N��120��10'00"E
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

    // ������Ϣ
        // ���������ţ�1  �������ƣ�С��  ��ֲ�·ݣ�3��  �ջ��·ݣ�9��  �������ԣ��̱���С����ֲ��
        // ���������ţ�2  �������ƣ�ˮ��  ��ֲ�·ݣ�5��  �ջ��·ݣ�10��  �������ԣ���������һ�����̱�����
        // ���������ţ�3  �������ƣ�����  ��ֲ�·ݣ�4��  �ջ��·ݣ�10��  �������ԣ������仨����ֲ��
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

    // �û���Ϣ
        // �û��˺ţ�10001  �û�������John  �û����룺1234567  �û�ְ�񣺹���Ա
        // �û��˺ţ�10002  �û�������Bob  �û����룺1234567  �û�ְ�񣺲���Ա
        // �û��˺ţ�10003  �û�������Lily  �û����룺1234567  �û�ְ�񣺲���Ա
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

    // ������Ϣ
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

/* ����Ϊ�������������� */

/* �������� */

/* 1.��¼ϵͳ */
void Login(User* user_message, Operation* operation_message, Planting* planting_message, Harvest* harvest_message, Land* land_message, Crop* crop_message, Finance* finance_message)
{
    // ��ʼ����
    cout << "\33[5m+\33[0m";
    for (int i = 0; i < 78; i ++ )
        cout << "\33[5m-\33[0m";
    cout << "\33[5m+\33[0m" << endl;
    cout << "\33[5m|\33[0m";
    for (int i = 0; i < 26; i ++ )
        cout << " ";
    cout << "��ӭʹ�ù�԰�������ϵͳ��";
    for (int i = 0; i < 26; i ++ )
        cout << " ";
    cout << "\33[5m|\33[0m" << endl;
    cout << "\33[5m+\33[0m";
    for (int i = 0; i < 78; i ++ )
        cout << "\33[5m-\33[0m";
    cout << "\33[5m+\33[0m" << endl;

    delay(1);

    // ��¼����
    cout << "���ȵ�¼����" << endl;
    cout << "�����������û��˺ţ�";
    int Id;
    cin >> Id;
    cout << "�����������û����룺";
    string Password;
    cin >> Password;
    
    User* p = user_message;
    for (int i = 0; i <= user_num; i ++ )
    {
        if (p->id == Id) break;
        p = p->Next;
    }
    if (p->id != Id) // �Ҳ����˺�
    {
        for (int i = 0; i < 80; i ++ )
            cout << '-';
        cout << endl;
        for (int i = 0; i < 25; i ++ )
            cout << " ";
        cout << "�Բ��������˺��������!";
        cout << endl;
        for (int i = 0; i < 80; i ++ )
            cout << '-';
        cout << endl;
        InputError(user_message, operation_message, planting_message, harvest_message, finance_message, land_message, crop_message);
    }
    else // �ҵ��˺�
    {
        if (p->password == Password) // ������ȷ
        {
            system("cls");
            cout << "+";
            for (int i = 0; i < 78; i ++ ) cout << "-";
            cout << "+";
            cout << endl;
            cout << "|   " << p->name << ",���ã�";
            for (int i = 0; i < 64; i ++ )
                cout << ' ';
            cout << "|" << endl << "|";
            for (int i = 0; i < 10; i ++ )
                cout << ' ';
            cout << "�˺ţ�" << p->id;
            for (int i = 0; i < 15; i ++ )
                cout << ' ';
            cout << "|";
            for (int i = 0; i < 15; i ++ ) cout << " ";
            cout << "ְ��";
            if (p->role == 1)
            {
                cout << "����Ա";
                for (int i = 0; i < 14; i ++ )
                    cout << " ";
                cout << "|" << endl;
                cout << "+";
                for (int i = 0; i < 78; i ++ )
                    cout << '-';
                cout << "+";
                cout << endl;
                Administrator_Operation(user_message, land_message, crop_message, finance_message); // �������Ա������
            }
            else if (p->role == 2)
            {
                cout << "����Ա";
                for (int i = 0; i < 14; i ++ )
                    cout << " ";
                cout << "|" << endl;
                cout << "+";
                for (int i = 0; i < 78; i ++ )
                    cout << '-';
                cout << "+";
                cout << endl;
                Operator_Operation(planting_message, operation_message, harvest_message); // �������Ա������
            }
            else if (p->role == 3)
            {
                cout << "����Ա";
                for (int i = 0; i < 14; i ++ )
                    cout << " ";
                cout << "|" << endl;
                cout << "+";
                for (int i = 0; i < 78; i ++ )
                    cout << '-';
                cout << "+";
                cout << endl;
                Treasurer_Operation(finance_message); // �������Ա������
            }
        }
        else // �������
        {
            for (int i = 0; i < 80; i ++ )
                cout << '-';
            cout << endl;
            for (int i = 0; i < 20; i ++ )
                cout << " ";
            cout << "�Բ��������˺Ż������������!" << endl;
            for (int i = 0; i < 80; i ++ )
                cout << '-';
            cout << endl;
            InputError(user_message, operation_message, planting_message, harvest_message, finance_message, land_message, crop_message);
        }
    }
}

/* 2.�������� */
void ExitSystem()
{
    for (int i = 0; i < 80; i ++ )
        cout << "\33[5m-\33[0m";
    cout << endl;
    for (int i = 0; i < 30; i ++ )
        cout << ' ';
    cout << "�����˳��У����Ժ󡭡�" << endl;
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
    cout << "��лʹ�ù�԰�������ϵͳ���ټ���";
    for (int i = 0; i < 23; i ++ )
        cout << " ";
    cout << "\33[5m|\33[0m" << endl;
    cout << "\33[5m+\33[0m";
    for (int i = 0; i < 78; i ++ )
        cout << "\33[5m-\33[0m";
    cout << "\33[5m+\33[0m" << endl;

    return;
}

/* 3.������� */
void InputError(User* user_message, Operation* operation_message, Planting* planting_message, Harvest* harvest_message, Finance* finance_message, Land* land_message, Crop* crop_message)
{
    cout << "��������Ҫ����" << endl;
    for (int i = 0; i < 20; i ++ )
        cout << " ";
    cout << "A.���µ�¼";
    for (int i = 0; i < 20; i ++ )
        cout << " ";
    cout << "B.�˳�ϵͳ";
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

/* 4. ��ʱ */
void delay(int seconds) //  ��������Ϊ���ͣ���ʾ��ʱ������
{
    clock_t start = clock();
    clock_t lay = (clock_t)seconds * CLOCKS_PER_SEC;
    while ((clock()-start) < lay);
}

/* ����Ա������ */
void Administrator_Operation(User* user_message, Land* land_message, Crop* crop_message, Finance* finance_message)
{
    cout << endl << "��ѡ������Ҫ���еĲ�������" << endl;

    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "�����û� - 1";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "ɾ���û� - 2";
    cout << endl;
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "�޸��û� - 3";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "��ѯ�û� - 4";
    cout << endl;
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "��ѯ�ؿ� - 5";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "��ѯ���� - 6";
    cout << endl;
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "��ѯ���� - 7";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "�˳�ϵͳ - 8";
    cout << endl;

    cout << endl << "����������Ҫ���еĲ���������֣�";
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

/* 1.�����û� */
void Add(User* user_message, Finance* finance_message, Land* land_message, Crop* crop_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " �����û� ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << "���������û��˺ţ�";
    int Id;
    cin >> Id;
    if (IsExist(Id, user_message))
    {
        cout << "���˺��ѱ�ʹ�ã����������롣";
        delay(1);
        Add(user_message, finance_message, land_message, crop_message);
    }
    else
    {
        cout << endl << "���������û�������";
        string name;
        cin >> name;
        cout << endl << "���������û����룺";
        string password;
        cin >> password;
        cout << endl << "���������û�ְ��1������Ա 2������Ա 3������Ա";
        int role;
        cin >> role;

        // �������û�
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
        cout << "��ӳɹ���";
        for (int i = 0; i < 35; i ++ )
            cout << "-";
        cout << endl;
        Administrator_Operation(user_message, land_message, crop_message, finance_message);
    }
}

/* 2.ɾ���û� */
void User_Delete(User* user_message, Land* land_message, Finance* finance_message, Crop* crop_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " ɾ���û� ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "������Ҫɾ���û����˺ţ�";
    int Id;
    cin >> Id;
    if (!IsExist(Id, user_message))
    {
        cout << endl << "���˺Ų����ڣ����������롣";
        delay(2);
        User_Delete(user_message, land_message, finance_message, crop_message);
    }
    else
    {
        user p = user_message;
        while (p != nullptr && p->id != Id)
            p = p->Next;
        cout << endl;
        cout << "�˺ţ�" << Id;
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "|";
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "������" << p->name;
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "|";
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "ְ��";
        if (p->role == 1)
            cout << "����Ա" << endl;
        else if (p->role == 2)
            cout << "����Ա" << endl;
        else if (p->role == 3)
            cout << "����Ա" << endl;
        cout << "��ȷ�������Ϣ��ȷ��ɾ����" << endl;
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
            if (location == 1) // ɾ�����ǵ�һ���û�
            {
                s = user_message; // s��Ҫɾ�����û�
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
                    cout << "���û������ڣ�ɾ��ʧ�ܣ�" ; // �ձ�
                    for (int i = 0; i < 35; i ++ )
                        cout << "-";
                    Administrator_Operation(user_message, land_message, crop_message, finance_message);
                    return;
                }
            }
            p = FindKth(location - 1, user_message); // �ҵ�Ҫɾ�����û���ǰһ���û�
            if (p == nullptr) // �û�������
            {
                for (int i = 0; i < 35; i ++ )
                    cout << "-";
                cout << "���û������ڣ�ɾ��ʧ�ܣ�" ; // �ձ�
                for (int i = 0; i < 35; i ++ )
                    cout << "-";
                Administrator_Operation(user_message, land_message, crop_message, finance_message);
                return;
            }
            else if(p->Next == nullptr) // �û�������
            {
                for (int i = 0; i < 35; i ++ )
                    cout << "-";
                cout << "���û������ڣ�ɾ��ʧ�ܣ�" ; // �ձ�
                for (int i = 0; i < 35; i ++ )
                    cout << "-";
                Administrator_Operation(user_message, land_message, crop_message, finance_message);
                return;
            }
            else
            {
                s = p->Next; // s��Ҫɾ�����û�
                p->Next = s->Next;
                free(s);
            }

            cout << endl;
            for (int i = 0; i < 35; i ++ )
                cout << "-";
            cout << "ɾ���ɹ���";
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
            cout << "����������ɾ���û���Ϣ��";
            cout << endl;
            for (int i = 0; i < 80; i ++ )
                cout << "-";
            User_Delete(user_message, land_message, finance_message, crop_message);
        }
    }
}

/* 3.�޸��û� */
void Modify(User* user_message, Land* land_message, Crop* crop_message, Finance* finance_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " �޸��û� ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << endl << endl;

    delay(1);

    cout << "������Ҫ�޸��û����˺ţ�";
    int Id;
    cin >> Id;
    if (!IsExist(Id, user_message))
    {
        cout << "���˺Ų����ڣ����������롣";
        delay(2);
        Modify(user_message, land_message, crop_message, finance_message);
    }
    else
    {
        user p = user_message;
        while (p != nullptr && p->id != Id)
            p = p->Next;
        
        cout << "��Ҫ�޸ġ���" << endl;
        for (int i = 0; i < 10; i ++ )
            cout << " ";
        cout << "�û��˺� - 1";
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "|";
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "�û����� - 2" << endl;
        for (int i = 0; i < 10; i ++ )
            cout << " ";
        cout << "�û�ְ�� - 3";
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "|";
        for (int i = 0; i < 5; i ++ )
            cout << " ";
        cout << "�û����� - 4" << endl;
        cout << "������Ҫ�޸����ݺ�������֣�����-1��ʾ�޸Ľ�������";
        int option;
        while (scanf("%d", &option) != -1)
        {
            if (option == 1)
            {
                cout << "�������޸ĺ���˺ţ�";
                int newId;
                cin >> newId;
                if (IsExist(newId, user_message))
                {
                    cout << "���˺��Ѵ��ڣ����������롣";
                    Modify(user_message, land_message, crop_message, finance_message);
                }
                else
                {
                    p->id = newId;
                    cout << endl;
                    for (int i = 0; i < 29; i ++ )
                        cout << "-";
                    cout << "�޸ĳɹ�������������޸ġ�";

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
                    while (getline(inf, s)) //��temp.txt������д��test.txt
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
                    cout << "��Ҫ�޸ġ���" << endl;
                    for (int i = 0; i < 10; i ++ )
                        cout << " ";
                    cout << "�û��˺� - 1";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "|";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "�û����� - 2" << endl;
                    for (int i = 0; i < 10; i ++ )
                        cout << " ";
                    cout << "�û�ְ�� - 3";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "|";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "�û����� - 4" << endl;
                    cout << "������Ҫ�޸����ݺ�������֣�����-1��ʾ�޸Ľ�������";
                }
            }
            else if (option == 2)
            {
                cout << "�������޸ĺ��������";
                string newName;
                cin >> newName;
                p->name = newName;
                cout << endl;
                for (int i = 0; i < 29; i ++ )
                    cout << "-";
                cout << "�޸ĳɹ�������������޸ġ�";

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
                while (getline(inf, s)) //��temp.txt������д��test.txt
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
                cout << "��Ҫ�޸ġ���" << endl;
                for (int i = 0; i < 10; i ++ )
                    cout << " ";
                cout << "�û��˺� - 1";
                for (int i = 0; i < 5; i ++ )
                    cout << " ";
                cout << "|";
                for (int i = 0; i < 5; i ++ )
                    cout << " ";
                cout << "�û����� - 2" << endl;
                for (int i = 0; i < 10; i ++ )
                    cout << " ";
                cout << "�û�ְ�� - 3";
                for (int i = 0; i < 5; i ++ )
                    cout << " ";
                cout << "|";
                for (int i = 0; i < 5; i ++ )
                    cout << " ";
                cout << "�û����� - 4" << endl;
                cout << "������Ҫ�޸����ݺ�������֣�����-1��ʾ�޸Ľ�������";
            }
            else if (option == 3)
            {
                cout << "�������޸ĺ��ְ��1������Ա 2������Ա 3������Ա";
                int newRole;
                cin >> newRole;
                p->role = newRole;
                cout << endl;
                for (int i = 0; i < 29; i ++ )
                    cout << "-";
                cout << "�޸ĳɹ�������������޸ġ�";

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
                while (getline(inf, s)) //��temp.txt������д��test.txt
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
                    cout << "�û��˺� - 1";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "|";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "�û����� - 2" << endl;
                    for (int i = 0; i < 10; i ++ )
                        cout << " ";
                    cout << "�û�ְ�� - 3";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "|";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "�û����� - 4" << endl;
                    cout << "������Ҫ�޸����ݺ�������֣�����-1��ʾ�޸Ľ�������";
            }
            else if (option == 4)
            {
                cout << "�������޸ĺ�����룺";
                string newPassword;
                cin >> newPassword;
                p->password = newPassword;
                cout << endl;
                for (int i = 0; i < 29; i ++ )
                    cout << "-";
                cout << "�޸ĳɹ�������������޸ġ�";

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
                    cout << "�û��˺� - 1";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "|";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "�û����� - 2" << endl;
                    for (int i = 0; i < 10; i ++ )
                        cout << " ";
                    cout << "�û�ְ�� - 3";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "|";
                    for (int i = 0; i < 5; i ++ )
                        cout << " ";
                    cout << "�û����� - 4" << endl;
                    cout << "������Ҫ�޸����ݺ�������֣�����-1��ʾ�޸Ľ�������";
            }
            else if (option == -1)
            {
                cout << endl;
                Administrator_Operation(user_message, land_message, crop_message, finance_message);
            }
        }
    }
}

/* 4.��ѯ�û� */
void Require(User* user_message, Land* land_message, Crop* crop_message, Finance* finance_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " ��ѯ�û� ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "������ѡ�����¼��ֲ�ѯ��ʽ��"<< endl;
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "A. �˺Ų�ѯ";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "B. ������ѯ";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "C. ְ���ѯ" << endl;
    cout << "���������ѡ��Ĳ�ѯ��ʽ��";
    char option;
    cin >> option;

    if (option == 'A')
    {
        cout << "��������Ҫ��ѯ���˺ţ�";
        int Id;
        cin >> Id;
        cout << endl;
        if (!IsExist(Id, user_message))
        {
            for (int i = 0; i < 27; i ++ )
                cout << "-";
            cout << "���˺Ų����ڣ������²�ѯ��";
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
            cout << "��ѯ�ɹ���";
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
        cout << "��������Ҫ��ѯ��������";
        string Name;
        cin >> Name;
        if (!IsExist_name(Name, user_message))
        {
            for (int i = 0; i < 27; i ++ )
                cout << "-";
            cout << "�����������ڣ������²�ѯ��";
            for (int i = 0; i < 27; i ++ )
                cout << "-";
            cout << endl;

            delay(2);
            Require(user_message, land_message, crop_message, finance_message);
        }
        User* p = user_message;
        for (int i = 0; i < 35; i ++ )
            cout << "-";
        cout << "��ѯ�ɹ���";
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
        cout << "��������Ҫ��ѯ��ְ��1������Ա 2������Ա 3������Ա" << endl;
        int Role;
        cin >> Role;
        User* p = new User;
        p = user_message->Next->Next;
        for (int i = 0; i < 35; i ++ )
            cout << "-";
        cout << "��ѯ�ɹ���";
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

/* 5.��ѯ�ؿ���Ϣ */
void Require_land(Land* land_message, User* user_message, Crop* crop_message, Finance* finance_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " ��ѯ�ؿ� ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "��������Ҫ��ѯ�ĵؿ��ţ�";
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
            cout << "��ѯ�ɹ���";
            for (int i = 0; i < 35; i ++ )
                cout << "-";
            cout << endl;
            for (int i = 0; i < 80; i ++ )
                cout << "-";
            cout << endl;

            for (int i = 0; i < 10; i ++ )
                cout << " ";
            cout << "�ؿ��ţ�" << p->id;
            cout << '\t' << "|" << '\t';
            cout << "�������ࣺ" << p->type;
            cout << '\t' << "|" << '\t';
            cout << "�ؿ���״��" << p->shape;
            cout << endl;
            for (int i = 0; i < 10; i ++ )
                cout << " ";
            cout << "�ؿ������" << p->area;
            cout << '\t' << "|" << '\t';
            cout << "�ؿ�λ�ã�" << p->location;
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
    cout << "�õؿ鲻���ڣ������²�ѯ��";
    for (int i = 0; i < 27; i ++ )
        cout << "-";
    cout << endl;
    delay(2);
    Require_land(land_message, user_message, crop_message, finance_message);
    return;
}

/* 6.��ѯ������Ϣ */
void Require_crop(Land* land_message, User* user_message, Crop* crop_message, Finance* finance_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " ��ѯ���� ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "��������Ҫ��ѯ�������ţ�";
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
            cout << "��ѯ�ɹ���";
            for (int i = 0; i < 35; i ++ )
                cout << "-";
            cout << endl;
            for (int i = 0; i < 80; i ++ )
                cout << "-";
            cout << endl;

            for (int i = 0; i < 10; i ++ )
                cout << " ";
            cout << "�����ţ�" << p->id;
            cout << '\t' << "|" << '\t';
            cout << "�������ƣ�" << p->name;
            cout << '\t' << "|" << '\t';
            cout << "��ֲ�·ݣ�" << p->plantingMonth;
            cout << endl;
            for (int i = 0; i < 10; i ++ )
                cout << " ";
            cout << "�ջ��·ݣ�" << p->harvestMonth;
            cout << '\t' << "|" << '\t';
            cout << "�������ԣ�" << p->characteristics;
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
    cout << "�����ﲻ���ڣ������²�ѯ��";
    for (int i = 0; i < 27; i ++ )
        cout << "-";
    cout << endl;
    delay(2);
    Require_crop(land_message, user_message, crop_message, finance_message);
    return;
}

/* 7.��ѯ������Ϣ */
void Require_finance(Land* land_message, User* user_message, Crop* crop_message, Finance* finance_message)
{
    system("cls");
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    cout << " ��ѯ���� ";
    for (int i = 0; i < 35; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "������Ҫ��ѯ����" << endl;
    for (int i = 0; i < 10; i ++ )
        cout << ' ';
    cout << "������Ϣ - 1";
    for (int i = 0; i < 10; i ++ )
        cout << ' ';
    cout << "֧����Ϣ - 2";
    cout << endl;

    int option;
    cin >> option;
    Finance* p = finance_message->Next->Next;

    for (int i = 0; i < 35; i ++ )
        cout << "-";
    cout << "��ѯ�ɹ���";
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

/* 8.���������Ϣ */
void Finance_input(Finance* p, int option)
{
    for (int i = 0; i < 20; i ++ )
        cout << " ";
    cout << "ʱ�䣺" << p->date;
    for (int i = 0; i < 20; i ++ )
        cout << ' ';
    if (option == 1)
        cout << "���룺" << p->income << endl;
    else if (option == 2)
        cout << "֧����" << p->expense << endl;
}

/* ����Id�ж��û��Ƿ��Ѿ����� */
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

/* ����Name�ж��û��Ƿ��Ѿ����� */
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

/* ���ص�K���û� */
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

/* ����Id��λ�� */
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

/* �����û���ѯ��� */
void Require_input(User* p)
{
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "�˺ţ�" << p->id;
    cout << '\t' << "|" << '\t';
    cout << "������" << p->name;
    cout << '\t' << "|" << '\t';
    cout << "ְ��";
    if (p->role == 1)
        cout << "����Ա";
    else if (p->role == 2)
        cout << "����Ա";
    else if (p->role == 3)
        cout << "����Ա";
    cout << endl;
}

/* ����Ա������ */
void Operator_Operation(Planting* planting_message, Operation* operation_message, Harvest* harvest_message)
{
    cout << endl << "��ѡ������Ҫ���еĲ�������" << endl;

    for (int i = 0; i < 20; i ++ )
        cout << " ";
    cout << "��ֲ - 1";
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "��Ӫ - 2";
    cout << endl;
    for (int i = 0; i < 20; i ++ )
        cout << " ";
    cout << "��ժ - 3";
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "|";
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "�˳�ϵͳ - 4" << endl;
    cout << endl;

    cout << endl << "����������Ҫ���еĲ�����������֣�";
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

/* 1.��ֲ */
void Plant(Planting* planting_message, Operation* operation_message, Harvest* harvest_message)
{
    Planting* p = new Planting;

    system("cls");
    for (int i = 0; i < 36; i ++ )
        printf("\33[5m*\33[0m");
    cout << " ��ֲ ";
    for (int i = 0; i < 36; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "��������ֲ��¼��ţ�";
    cin >> p->id;
    cout << endl << "��������ֲ�ؿ��ţ�";
    cin >> p->landId;
    cout << endl << "��������ֲ���������ţ�";
    cin >> p->cropId;
    cout << endl << "��������ֲ������";
    cin >> p->quantity;
    cout << endl << "��������ֲʱ�䣺";
    cin >> p->date;
    cout << endl << "��������ֲ�ˣ�";
    cin >> p->implementer;
    cout << endl << "���������ˣ�";
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
        cout << "-"; // ��һ��
    for (int i = 0; i < 35; i ++ )
        cout << " "; // �ڶ���
    cout << endl << "��ֲ�ɹ���";
    for (int i = 0; i < 35; i ++ )
        cout << " ";
    cout << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "��ֲ��¼��ţ�" << p->id;
    cout << '\t' << "|" << '\t';
    cout << "��ֲ�ؿ��ţ�" << p->landId;
    cout << '\t' << "|" << '\t';
    cout << "��ֲ���������ţ�" << p->cropId << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "��ֲ������" << p->quantity;
    cout << '\t' << "|" << '\t';
    cout << "��ֲʱ�䣺" << p->date;
    cout << '\t' << "|" << '\t';
    cout << "��ֲ�ˣ�" << p->implementer << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "����ˣ�" << p->inspector << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-"; // ������
    cout << endl;

    Operator_Operation(planting_message, operation_message, harvest_message);
}

/* 2.��Ӫ */
void Operate(Planting* planting_message, Operation* operation_message, Harvest* harvest_message)
{
    Operation* p = new Operation;
    
    system("cls");
    for (int i = 0; i < 36; i ++ )
        printf("\33[5m*\33[0m");
    cout << " ��Ӫ ";
    for (int i = 0; i < 36; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "�����뾭Ӫ��¼��ţ�";
    cin >> p->id;
    cout << endl << "�����뾭Ӫ���ࣺ1��ʩ�� 2����ˮ 3������";
    cin >> p->operationType;
    cout << endl << "�����뾭Ӫʱ�䣺";
    cin >> p->date;
    cout << endl << "�����뾭Ӫ�ˣ�";
    cin >> p->implementer;
    cout << endl << "���������ˣ�";
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
        cout << "-"; // ��һ��
    cout << endl;
    for (int i = 0; i < 35; i ++ )
        cout << " "; // �ڶ���
    cout << "��Ӫ�ɹ���" << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-"; // ��һ��
    cout << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "��Ӫ��¼��ţ�" << p->id;
    cout << '\t' << "|" << '\t';
    cout << "��Ӫ���ࣺ";
    if (p->operationType == 1)
        cout << "ʩ��";
    else if (p->operationType == 2)
        cout << "��ˮ";
    else if (p->operationType == 3)
        cout << "����";
    cout << '\t' << "|" << '\t';
    cout << "��Ӫʱ�䣺" << p->date << endl;
    for (int i = 0; i < 5; i ++ )
        cout << ' ';
    cout << "��Ӫ�ˣ�" << p->implementer;
    cout << '\t' << "        |" << '\t';
    cout << "����ˣ�" << p->inspector << '\t' << endl;
    for (int i = 0; i < 80; i ++ ) cout << "-"; // ������
    cout << endl;

    Operator_Operation(planting_message, operation_message, harvest_message);
}

/* 3.��ժ */
void Picking(Planting* planting_message, Operation* operation_message, Harvest* harvest_message)
{
    Harvest* p = new Harvest;

    system("cls");
    for (int i = 0; i < 36; i ++ )
        printf("\33[5m*\33[0m");
    cout << " ��ժ ";
    for (int i = 0; i < 36; i ++ )
        printf("\33[5m*\33[0m");
    delay(1);
    cout << endl << endl;

    cout << "�������ժ��¼��ţ�";
    cin >> p->id;
    cout << endl << "�������ժ�ؿ飺";
    cin >> p->landId;
    cout << endl << "�������ժ�������ࣺ";
    cin >> p->cropId;
    cout << endl << "�������ժ������";
    cin >> p->quantity;
    cout << endl << "�������ժʱ�䣺";
    cin >> p->date;
    cout << endl << "�������ժ�ˣ�";
    cin >> p->implementer;
    cout << endl << "���������ˣ�";
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
        cout << "-"; // ��һ��
    cout << endl;
    for (int i = 0; i < 35; i ++ )
        cout << " "; // �ڶ���
    cout << "��ժ�ɹ���" << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-"; // ��һ��
    cout << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "��ժ��¼��ţ�" << p->id;
    cout << '\t' << "|" << '\t';
    cout << "��ժ�ؿ飺" << p->landId;
    cout << '\t' << "|" << '\t';
    cout << "��ժ���������ţ�" << p->cropId << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "��ժ������" << p->quantity;
    cout << '\t' << "|" << '\t';
    cout << "��ժʱ�䣺" << p->date;
    cout << '\t' << "|" << '\t';
    cout << "��ժ�ˣ�" << p->implementer << endl;
    for (int i = 0; i < 5; i ++ )
        cout << " ";
    cout << "����ˣ�" << p->inspector << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-"; // ������
    cout << endl;

    Operator_Operation(planting_message, operation_message, harvest_message);
}

/* ����Ա������ */
void Treasurer_Operation(Finance* finance_message)
{
    cout << endl << "��ѡ������Ҫ���еĲ�������" << endl;

    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "��¼���� - 1";
    cout << '\t' << "|" << '\t';
    cout << "��¼֧�� - 2";
    cout << '\t' << "|" << '\t';
    cout << "�˳�ϵͳ - 3" << endl;
    cout << endl << "����������Ҫ���еĲ�����������֣�";

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

/* 1.��¼���� */
void Income(Finance* finance_message)
{
    Finance* p = new Finance;

    cout << "����������ʱ�䣺";
    cin >> p->date;
    cout << "����������";
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
    cout << "����Ϊ����¼�����Ժ󡭡�" << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "\33[5m-\33[0m";
    delay(3);
    system("cls");

    for (int i = 0; i < 80; i ++ )
        cout << "-"; // ��һ��
    cout << endl;
    for (int i = 0; i < 35; i ++ )
        cout << " "; // �ڶ���
    cout << "��¼�ɹ���" << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-";
    cout << endl;
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "�������룺" << p->income;
    cout << '\t' << "               |" << '\t';
    cout << "          ���ʲ���" << asset << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-";
    cout << endl << endl;

    Treasurer_Operation(finance_message);
}

/* 2.��¼֧�� */
void Expense(Finance* finance_message)
{
    Finance* p = new Finance;

    cout << "������֧��ʱ�䣺";
    cin >> p->date;
    cout << "������֧���";
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
    cout << "����Ϊ����¼�����Ժ󡭡�" << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "\33[5m-\33[0m";
    delay(3);
    system("cls");

    for (int i = 0; i < 80; i ++ )
        cout << "-"; // ��һ��
    cout << endl;
    for (int i = 0; i < 35; i ++ )
        cout << " "; // �ڶ���
    cout << "��¼�ɹ���" << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-";
    cout << endl;
    for (int i = 0; i < 10; i ++ )
        cout << " ";
    cout << "����֧����" << p->expense;
    cout << '\t' << "               |" << '\t';
    cout << "          ���ʲ���" << asset << endl;
    for (int i = 0; i < 80; i ++ )
        cout << "-";
    cout << endl << endl;

    Treasurer_Operation(finance_message);
}