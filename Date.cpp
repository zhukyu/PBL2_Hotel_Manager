#include "Date.h"

Date::Date()
    : day(0), mon(0), year(0)
{

}
Date::Date(const int& d, const int& m, const int& y)
    : day(d), mon(m), year(y)
{

}
Date::Date(Date& d)
{
    this->day = d.day;
    this->mon = d.mon;
    this->year = d.year;
}
Date::~Date()
{

}
int Date::getDay()
{
    return this->day;
}
int Date::getMon()
{
    return this->mon;
}
int Date::getYear()
{
    return this->year;
}
void Date::setDay(int& d)
{
    this->day = d;
}
void Date::setMon(int& m)
{
    this->mon = m;
}
void Date::setYear(int& y)
{
    this->year = y;
}
bool isLeapYear(Date& d)
{
	return ((d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0);
}
int dayCount(Date& d)
{
	int nNumOfDays;

	switch (d.mon)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: 
		nNumOfDays = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11: 
		nNumOfDays = 30;
		break;
	case 2:
		if (isLeapYear(d))
		{
			nNumOfDays = 29;
		}
		else
		{
			nNumOfDays = 28;
		}
		break;
	}

	return nNumOfDays;
}
bool checkDay(Date& d)
{
	if (d.year < 0)
	{
		return false; 
	}
	
	if (d.mon < 1 || d.mon > 12)
	{
		return false; 
	}
	if (d.day < 1 || d.day> dayCount(d))
	{
		return false;
	}
	return true; 
}
istream& operator>>(istream& i, Date& d)
{
    i >> d.day;
    i.ignore(2, '/');
    i >> d.mon;
    i.ignore(2, '/');
    i >> d.year;
	return i;
}
ostream& operator<<(ostream& o,const Date& d)
{
    o << d.day << "/" << d.mon << "/" << d.year;
	return o;
}
bool operator>=(Date& a, Date& b)
{
    if(a.year > b.year)
        return true;
    if(a.year < b.year)
        return false;
    else
    {
        if(a.mon > b.mon)
            return true;
        if(a.mon < b.mon)
            return false;
        else
        {
           if(a.day > b.day)
                return true;
            if(a.day < b.day)
                return false; 
            else return true;
        }
    }   
}
bool operator<=(Date& a, Date& b)
{
    if(a.year < b.year)
        return true;
    if(a.year > b.year)
        return false;
    else
    {
        if(a.mon < b.mon)
            return true;
        if(a.mon > b.mon)
            return false;
        else
        {
           if(a.day < b.day)
                return true;
            if(a.day > b.day)
                return false; 
            else return true;
        }
    }
}
const Date Date::operator++(int)
{
	int maxDay = dayCount(*this);
    int temp = this->day + 1;
    this->day = temp;
    if(temp > maxDay)
    {
        this->day = temp % maxDay;
        temp = this->mon + (temp / maxDay);
        this->mon = temp;
        if(temp > 12)
        {
            this->mon = temp % 12;
            temp = temp / 12;
            this->year += temp;
        }
    }
    return *this;
}
int maxDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int countLeapYears(Date& d)
{
    int years = d.year;
    if (d.mon <= 2)
        years--;
    return years / 4 - years / 100 + years / 400;
}
int operator-(Date& a, Date& b)
{
    long int n1 = a.year * 365 + a.day;
    for (int i = 0; i < a.mon - 1; i++)
        n1 += maxDay[i];
    n1 += countLeapYears(a);

    long int n2 = b.year * 365 + b.day;
    for (int i = 0; i < b.mon - 1; i++)
        n2 += maxDay[i];
    n2 += countLeapYears(b);

    return n1 - n2;
}
void Date::setCurrentTime()
{
	time_t timenow = time(0);
    tm t = *localtime(&timenow);
    t.tm_mon += 1;
    t.tm_year += 1900;
	this->day = t.tm_mday;
	this->mon = t.tm_mon;
	this->year = t.tm_year;
}