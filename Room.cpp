#include "Room.h"
#include <iomanip>
Room::Room() : _id(0), _type(0), _price(0), _status(0)
{

}
Room::Room(Room& r)
{
    this->_id = r._id;
    this->_price = r._price;
    this->_status = r._status;
    this->_type = r._type;
}
Room::~Room()
{

}
int Room::getId()
{
    return this->_id;
}
int Room::getType()
{
    return this->_type;
}
long Room::getPrice()
{
    return this->_price;
}
bool Room::getStatus()
{
    return this->_status;
}
void Room::setId(int id)
{
    this->_id = id;
}
void Room::setType(int type)
{
    this->_type = type;
    switch (type)
    {
    case 1:
    {
        this->setPrice(600000);
        break;
    }
    case 2:
        this->setPrice(800000);
    default:
        break;
    }
}
void Room::setPrice(long price)
{
    this->_price = price;
}
void Room::setStatus(bool stt)
{
    this->_status = stt;
}
ostream& operator<<(ostream& o, Room& r)
{
    o << "Phong: " << r.getId() << "\tLoai phong: ";
    switch (r.getType())
    {
    case 1:
    {
        o << "Standard" << endl;
        break;
    }
    case 2:
    {
        o << "Superior" << endl;
    }
    }
    return o;
}
void Room::show()
{
    
    cout << setw(7) << left << this->_id;
    //in ra loai phong
    switch(this->_type)
    {
        case 1:
        {
            cout << setw(12) << left << "Standard";
            break;
        }
        case 2:
        {
            cout << setw(12) << left << "Superior";
        }
    }
    //in ra trang thai phong
    switch(this->_status)
    {
        case 0:
        {
            cout << setw(12) << left << "Da thue";
            break;
        }
        case 1:
        {
            cout << setw(12) << left << "Trong";
            break;
        }
    }
    cout << setw(7) << right << this->_price;
}