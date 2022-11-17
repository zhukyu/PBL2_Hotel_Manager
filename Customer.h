#include <iostream>
#include <string>
#include <ctime>
#include "Date.h"
using namespace std;

class Customer
{
    protected:
        string _name;
        Date _birthday;
        string _phone;
        string _address;
        string _id;
    public:
        Customer();
        Customer(Customer&);
        ~Customer();
        string getName();
        Date getBirthday();
        string getPhone();
        string getAddress();
        string getId();
        void setName(string);
        void setBirthday(Date);
        void setPhone(string);
        void setAddress(string);
        void setId(string);
        friend istream& operator>>(istream&, Customer&);
        friend ostream& operator<<(ostream&, Customer&);
        void show();
};