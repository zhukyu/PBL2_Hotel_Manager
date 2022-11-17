#include "Receipt.h"
#include <iostream>
#include <string>
using namespace std;

class Manager
{
    private:
        Customer *_c;
        Room *_r;
        Receipt *_b; //not paid bill
        Receipt *_pb; //paid bill
        int _ccount; //customer count
        int _rcount; //room count
        int _bcount; //bill count
        int _pbcount; //paid bill count
    public:
        Manager();
        ~Manager();
        void addCustomer(Customer&);
        void showRoom();
        void showAvailableRoom();
        void showCustomer();
        bool checkAddress(string&,Customer&);
        int check_exist_Customer(string&);
        void searchReceipt();
        //thong ke
        long Sum(Date&, Date&);
        void statistic();
        //thao tac voi receipt
        void addReceipt(Receipt&);
        void deleteReceipt(int&);
        void addPaidReceipt(Receipt&);
        void checkIn();
        void confirm(int&);
        void checkOut();
        void showReceipt(Receipt&, int&);
        //thao tac voi file
        void roomInit();
        void rewriteRoomFile();
        void writeCustomerFile(Customer&);
        void readCustomerFile();
        void writeReceiptFile(Receipt&, int);
        void readReceiptFile();
        void readPaidFile();
        void rewriteReceiptFile();
};