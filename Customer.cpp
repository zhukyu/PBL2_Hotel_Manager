#include "Customer.h"
#include <iomanip>
Customer::Customer()
{
}
Customer::Customer(Customer &c)
{
    this->_address = c._address;
    this->_birthday = c._birthday;
    this->_id = c._id;
    this->_name = c._name;
    this->_phone = c._phone;
}
Customer::~Customer()
{
}
string Customer::getId()
{
    return this->_id;
}
string Customer::getName()
{
    return this->_name;
}
Date Customer::getBirthday()
{
    return this->_birthday;
}
string Customer::getAddress()
{
    return this->_address;
}
string Customer::getPhone()
{
    return this->_phone;
}
void Customer::setName(string name)
{
    this->_name = name;
}
void Customer::setPhone(string phone)
{
    this->_phone = phone;
}
void Customer::setAddress(string address)
{
    this->_address = address;
}
void Customer::setId(string id)
{
    this->_id = id;
}
void Customer::setBirthday(Date birthday)
{
    this->_birthday = birthday;
}
void xu_li(string &str) {
    for(int i=0;i<str.length();i++) 
    {
        if (str[i] >= 'A' && str[i]<='Z')
            str[i]+=32;
    }
    int i=0;
    while(i < str.length())
    {
        if(str[i]==' ')
            while(str[i+1]==' ')
            {
                int j=i+1;
                for(int j=i+1;j<=str.length();j++)
                {
                    str[j]=str[j+1];
                    
                }
                str.pop_back();
               // cout << str.length() <<  endl
            }
        i++; 
    }
    
    str[0]-=32;
    for(int i=1 ;i<str.length();i++)
    {
        if(str[i-1]==' ')
            str[i]-=32;
    }
}
bool checkPhone(string& s)
{
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}
istream &operator>>(istream &i, Customer &c)
{
    cout << "Ten: ";
    getline(i, c._name);
	xu_li(c._name);
	do
	{
        cout << "Ngay sinh: ";
		i >> c._birthday;
		if(!checkDay(c._birthday))
			cout << "Ngay sinh khong hop le!" << endl;
	}while(!checkDay(c._birthday));
    do
    {
        cout << "So dien thoai: ";
        i >> c._phone;
        if(!checkPhone(c._phone))
            cout << "So dien thoai khong hop le!" << endl;
    } while(!checkPhone(c._phone));
	cin.ignore(1000,'\n');
    cout << "Dia chi: ";
    getline(i, c._address);
    return i;
}
ostream &operator<<(ostream &o, Customer &c)
{
    o << "Ten: " << c._name << endl;
    o << "CMND: " << c._id << endl;
    o << "Ngay sinh: " << c._birthday << endl;
    o << "SDT: " << c._phone << endl;
    o << "Dia chi: " << c._address << endl;
    return o;
}
void Customer::show()
{
	cout << setw(22) << left << this->_name << setw(14) << left << this->_id 
    << this->_birthday << "    " << setw(14) << left << this->_phone << setw(22) << left << this->_address;
}
