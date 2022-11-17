#include <ctime>
#include <iostream>
using namespace std;

class Date
{
    private:
        int day;
        int mon;
        int year;
    public:
        Date();
        Date(const int&, const int&, const int&);
        Date(Date&);
        ~Date();
        int getDay();
        int getMon();
        int getYear();
        void setDay(int&);
        void setMon(int&);
        void setYear(int&);
        friend bool isLeapYear(Date&);
        friend int dayCount(Date&);
        friend bool checkDay(Date&);
        friend istream& operator>>(istream&, Date&);
        friend ostream& operator<<(ostream&,const Date&);
        friend bool operator<=(Date&, Date&);
        friend bool operator>=(Date&, Date&);
        const Date operator++(int);
        friend int countLeapYears(Date&);
        friend int operator-(Date&, Date&);
        void setCurrentTime();
};