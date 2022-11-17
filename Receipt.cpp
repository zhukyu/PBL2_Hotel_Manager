#include "Receipt.h"

Receipt::Receipt()
{
}
Receipt::Receipt(int C_Id, int R_Id, Date checkin, int duration)
{
    this->_customerId = C_Id;
    this->_roomId = R_Id;
    this->_checkinDate = checkin;
    this->_duration = duration;
    Date temp(0,0,0);
    this->_checkoutDate = temp;
    this->_stt = 0; // not paid
    this->_totalAmount = 0;
}
Receipt::~Receipt()
{
}
bool Receipt::getStatus()
{
    return this->_stt;
}
int Receipt::getCustomerId()
{
    return this->_customerId;
}
int Receipt::getRoomId()
{
    return this->_roomId;
}
Date& Receipt::getCheckinDate()
{
    return this->_checkinDate;
}
Date& Receipt::getCheckoutDate()
{
    return this->_checkoutDate;
}
int Receipt::getDuration()
{
    return this->_duration;
}
long Receipt::getTotalAmount()
{
    return this->_totalAmount;
}
void Receipt::setStatus(bool &stt)
{
    this->_stt = stt;
}
void Receipt::setCustomerId(int& customerId)
{
    this->_customerId= customerId;
}
void Receipt::setRoomId(int& roomId)
{
    this->_roomId= roomId;
}
void Receipt::setCheckinDate(Date &t)
{
    this->_checkinDate = t;
}
void Receipt::setCheckoutDate(Date &t)
{
    this->_checkoutDate = t;
}
void Receipt::setDuration(int &t)
{
    this->_duration = t;
}
void Receipt::setTotalAmount(long &ta)
{
    this->_totalAmount = ta;
}
ostream &operator<<(ostream &o, Receipt &b)
{
    o << "Ngay thue phong: " << b._checkinDate << endl;
    o << "Ngay tra phong: " << b._checkoutDate << endl;
    o << "Tong cong: " << b._totalAmount << " VND";
    return o;
}