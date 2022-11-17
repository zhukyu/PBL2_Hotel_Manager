#include <iostream>
using namespace std;

class Room
{
    private:
        int _id;
        int _type;
        long _price;
        bool _status;
    public:
        Room();
        Room(Room&);
        ~Room();
        int getId();
        int getType();
        long getPrice();
        bool getStatus();
        void setId(int);
        void setType(int);
        void setPrice(long);
        void setStatus(bool);
        friend ostream& operator<<(ostream&, Room&);
        void show();
};