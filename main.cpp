#include "Manager.h"
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
int menu()
{
    ifstream f = ifstream("menu.txt", ios_base::in);
    if (!f)
    {
        cerr << "Error: file not opened." << endl;
    }
    string c;
    while(!f.eof())
    {
        getline(f, c);
        cout << c;
        cout << endl;
    }
    int choice;
    cout << "Chon chuc nang: ";
    cin >> choice;
    f.close();
    return choice;
}
void introduce()
{
    ifstream f = ifstream("introduce.txt", ios_base::in);
    if (!f)
    {
        cerr << "Error: file not opened." << endl;
    }
    string c;
    while(!f.eof())
    {
        getline(f, c);
        cout << c;
        cout << endl;
    }
    f.close();
}
void login()
{
    string *username, *password;
    int n;
    ifstream f("staff.txt", ios_base::in);
    if (!f)
    {
        cerr << "Error: file not opened." << endl;
    }
    f >> n;
    username = new string[n];
    password = new string[n];
    int i = 0;
    while (f.get() != EOF)
    {
        f >> username[i];
        f >> password[i];
        i++;
    }
    f.close();
    string u = "", p = "";
    bool stt = 0;
    do
    {
        system("cls");
        introduce();
        cout << "             -------- Dang nhap --------" << endl;
        cout << "Tai khoan: ";
        cin >> u;
        cout << "Mat khau: ";
        //chuyen mat khau thanh *
        string p ="";
        char ch;
        ch = _getch();
        while(ch != 13){
            p.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        for(int j = 0; j < n; j++)
        {
            if(u == username[j] && p == password[j])
            {
                stt = 1;
                break;
            }
        }
        if(!stt)
        {
            cout << endl << "Sai tai khoan hoac mat khau!" << endl;
            system("pause");
        }
    } while (!stt);
}
int main()
{
    system("COLOR 6");
    login();
    Manager db;
    int choice;
    do
    {
        system("cls");
        choice = menu();
        system("cls");
        switch (choice)
        {
        case 1:
        {
            db.checkIn();
            db.rewriteRoomFile();
            break;
        }
        case 2:
        {
            db.checkOut();
            db.rewriteRoomFile();
            break;
        }
        case 3:
        {
            db.searchReceipt();
            break;
        }
        case 4:
        {
            db.showRoom();
            break;
        }
        case 5:
        {
            db.showCustomer();
            break;
        }
        case 6:
        {
            db.statistic();
            break;
        }
        case 7:
        {
            cout << "Cam on ban da su dung chuong trinh" << endl;
            break;
        }
        }
        system("pause");
        cout << "------------------------" << endl;
    } while (choice > 0 && choice < 7);
    return 0;
}