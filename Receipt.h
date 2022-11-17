#include "Customer.h"
#include "Room.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Receipt
{
    private:
        //stt == 0: chua thanh toan, == 1: da thanh toan
        bool _stt;
        int _customerId;
        int _roomId;
        Date _checkinDate;
        Date _checkoutDate;
        int _duration;
        long _totalAmount;
    public:
        Receipt();
        Receipt(int, int, Date, int);
        ~Receipt();
        bool getStatus();
        int getCustomerId();
        int getRoomId();
        Date& getCheckinDate();
        Date& getCheckoutDate();
        int getDuration();
        long getTotalAmount();
        void setStatus(bool&);
        void setCustomerId(int&);
        void setRoomId(int&);
        void setCheckinDate(Date&);
        void setCheckoutDate(Date&);
        void setDuration(int&);
        void setTotalAmount(long&);
        friend ostream& operator<<(ostream&, Receipt&);
};