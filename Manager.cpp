#include "Manager.h"
#include <iomanip>
#include <fstream>
Manager::Manager()
    : _c(nullptr), _r(nullptr), _b(nullptr), _pb(nullptr), _ccount(0), _rcount(0), _bcount(0), _pbcount(0)
{
    this->readCustomerFile();
    this->readReceiptFile();
    this->readPaidFile();
    this->roomInit();
}
Manager::~Manager()
{
    this->rewriteRoomFile();
    delete[] this->_c;
    delete[] this->_r;
    delete[] this->_b;
}
void Manager::roomInit()
{
    ifstream f("Database/Room.txt", ios_base::in);
    if (!f)
    {
        cerr << "Error: file not opened." << endl;
    }
    f >> this->_rcount;
    this->_r = new Room[_rcount];
    int i = 0;
    while (f.get() != EOF)
    {
        int id, type, stt;
        f >> id;
        f >> type;
        f >> stt;
        this->_r[i].setId(id);
        this->_r[i].setType(type);
        this->_r[i].setStatus(stt);
        i++;
    }
    f.close();
    // set price
    for (int i = 0; i < this->_rcount; i++)
    {
        if (this->_r[i].getType() == 1)
            this->_r[i].setPrice(600000);
        if (this->_r[i].getType() == 2)
            this->_r[i].setPrice(800000);
    }
}
int Manager::check_exist_Customer(string &id)
{
    int i = 0;
    for(i=0; i<_ccount; i++)
    {
        if(id == _c[i].getId())
        {
            break;
        }
    }
    return i;
}
void Manager::searchReceipt()
{
    cout << "x========================================x" << endl;
    cout << "|        TRA CUU THONG TIN HOA DON       |" << endl;
    cout << "x========================================x" << endl;
    cout << "|        1. Tra cuu theo Ma hoa don      |" << endl;
    cout << "|        2. Tra cuu theo CMND            |" << endl;
    cout << "x========================================x" << endl;
    int choice;
    do
    {
        cout << "Moi nhap chuc nang: ";
        cin >> choice;
        if (choice < 1 || choice > 2)
            cout << "Loi cu phap!" << endl;
    } while (choice < 1 || choice > 2);
    switch(choice)
    {
    case 1:
    {
        int i;
        cout << "Nhap Ma hoa don: ";
        cin >> i;
        cout << "----------------------" << endl;
        if(i < 0 || i >= this->_pbcount)
            cout << "Hoa don khong ton tai!" << endl;
        else
        {
            this->showReceipt(this->_pb[i], i);
        }
        break;
    }
    case 2:
    {
        string id;
        int stt = 0;
        cout << "Moi nhap CMND: ";
        cin >> id;
        cout << "----------------------" << endl;
        for (int i = 0; i < this->_pbcount; i++)
        {
            if (id == _c[_pb[i].getCustomerId()].getId())
            {
                this->showReceipt(this->_pb[i], i);
                stt = 1;
            }
        }
        if (stt == 0)
            cout << "Hoa don khong ton tai!" << endl;
        break;
    }
    }
}
// thong ke
long Manager::Sum(Date& a, Date& b)
{
    long total = 0;
    for(int i = 0; i < this->_pbcount; i++)
    {
        Date temp = _pb[i].getCheckoutDate();
        if(temp >= a && temp <= b)
            total += _pb[i].getTotalAmount();
    }
    return total;
}
void Manager::statistic()
{
    cout << "x========================================x" << endl;
    cout << "|           THONG KE DOANH THU           |" << endl;
    cout << "x========================================x" << endl;
    cout << "|         1. Thong ke theo nam           |" << endl;
    cout << "|         2. Thong ke theo thang         |" << endl;
    cout << "|         3. Thong ke theo ngay          |" << endl;
    cout << "x========================================x" << endl;
    int c;
    do
    {
        cout << "Moi nhap chuc nang: ";
        cin >> c;
        if (c < 0 || c > 3)
            cout << "Sai cu phap!" << endl;
    } while (c < 0 || c > 3);
    switch(c)
    {
    case 1:
    {
        cout << "Nhap nam can thong ke: ";
        int y;
        cin >> y;
        Date a(1, 1, y), b(31, 12, y);
        cout << "Doanh thu nam " << y << " la: " << Sum(a, b) << " VND" << endl;
        break;
    }
    case 2:
    {
        int m, y;
        do
        {
            cout << "Nhap thang can thong ke (mm/yyyy): ";
            cin >> m;
            cin.ignore(1, '/');
            cin >> y;
            if(m < 1 || m > 12)
                cout << "Sai cu phap!" << endl;
        } while(m < 1 || m > 12);
        Date a(1, m, y), b(1, m, y);
        int temp = dayCount(b);
        b.setDay(temp);
        cout << "Doanh thu thang " << m << "/" << y << " la: " << Sum(a, b) << " VND" << endl;
        break;
    }
    case 3:
    {
        Date a;
        bool stt;
        do
        {
            stt = 1;
            cout << "Nhap ngay can thong ke: ";
            cin >> a;
            if(!checkDay(a))
            {
                cout << "Ngay khong ton tai!" << endl;
                stt = 0;
            }
        } while (!stt);
        cout << "Doanh thu ngay " << a << " la: " << Sum(a, a) << " VND" << endl;
        break;
    }
    }
}

void Manager::addCustomer(Customer &c)
{
    if (this->_ccount == 0)
    {
        this->_c = new Customer[this->_ccount + 1];
        this->_c[this->_ccount] = c;
    }
    else
    {
        Customer *temp = new Customer[this->_ccount];
        for (int i = 0; i < this->_ccount; i++)
        {
            temp[i] = this->_c[i];
        }
        delete[] this->_c;
        this->_c = new Customer[this->_ccount + 1];
        for (int i = 0; i < this->_ccount; i++)
        {
            this->_c[i] = temp[i];
        }
        this->_c[this->_ccount] = c;
        delete[] temp;
    }
    this->_ccount++;
}
void Manager::showRoom()
{
    cout << "x================================================================x" << endl;
    cout << "|                         DANH SACH PHONG                        |" << endl;
    cout << "x================================================================x" << endl;
    cout << "| " << setw(7) << left << "Phong" << setw(12) << left << "Loai phong";
    cout << setw(12) << left << "Trang thai" << setw(7) << right << "Gia" << "  " << setw(22) << left << "Ten nguoi thue" << " |" << endl;
    cout << "x----------------------------------------------------------------x" << endl;
    for (int i = 0; i < this->_rcount; i++)
    {
        if (this->_r[i].getStatus() == 1)
        {
            cout << "| ";
            this->_r[i].show();
            cout << setw(26) << right << " |" << endl;
        }
        else
        {
            cout << "| ";
            this->_r[i].show();
            for(int j = 0; j < _bcount; j++)
            {
                if(this->_r[i].getId() == this->_b[j].getRoomId())
                {
                    cout << "  " << setw(22) << left << this->_c[this->_b[j].getCustomerId()].getName() <<" |" << endl;
                    break;
                }
            } 
        }
    }
    cout << "x================================================================x" << endl;
}
void Manager::showAvailableRoom()
{
    cout << "x========================================x" << endl;
    cout << "|             DANH SACH PHONG            |" << endl;
    cout << "x========================================x" << endl;
    cout << "| " << setw(7) << left << "Phong" << setw(12) << left << "Loai phong";
    cout << setw(12) << left << "Trang thai" << setw(7) << right << "Gia" << " |" << endl;
    cout << "x----------------------------------------x" << endl;
    for (int i = 0; i < this->_rcount; i++)
    {
        if (this->_r[i].getStatus() == 1)
        {
            cout << "| ";
            this->_r[i].show();
            cout << " |" << endl;
        }
    }
    cout << "x========================================x" << endl;
}
bool isNotPrinted(string exist[], string& i, int& prc)
{
    for(int j = 0; j < prc; j++)
    {
        if(exist[j] == i)
            return false;
    }
    return true;
}
void Manager::showCustomer()
{
    cout << "x=======================================================================================x" << endl;
    cout << "|                                  DANH SACH KHACH HANG                                 |" << endl;
    cout << "x=======================================================================================x" << endl;
    cout << "| " << setw(22) << left << "Ten khach hang" << setw(14) << left << "CMND" << setw(13) << left
         << "Ngay sinh" << setw(14) << left << "SDT" << setw(22) << left << "Dia chi" << " |" << endl;
    cout << "x---------------------------------------------------------------------------------------x" << endl;
    string exist[this->_bcount];
    int prc = 0;
    for (int i = 0; i < this->_bcount; i++)
    {
        Customer c = this->_c[this->_b[i].getCustomerId()];
        string id = c.getId(); //lay CMND
        if(isNotPrinted(exist, id, prc))
        {
            cout << "| ";
            c.show();
            cout << " |" << endl;
            exist[prc] = id;
            prc++;
        }
    }
    cout << "x=======================================================================================x" << endl;
}
void Manager::addReceipt(Receipt &b)
{
    if (this->_bcount == 0)
    {
        this->_b = new Receipt[this->_bcount + 1];
        this->_b[this->_bcount] = b;
    }
    else
    {
        Receipt *temp = new Receipt[this->_bcount];
        for (int i = 0; i < this->_bcount; i++)
        {
            temp[i] = this->_b[i];
        }
        delete[] this->_b;
        this->_b = new Receipt[this->_bcount + 1];
        for (int i = 0; i < this->_bcount; i++)
        {
            this->_b[i] = temp[i];
        }
        this->_b[this->_bcount] = b;
        delete[] temp;
    }
    this->_bcount++;
}
void Manager::deleteReceipt(int &index)
{
    Receipt *temp;
    this->_bcount--;
    temp = new Receipt[this->_bcount];
    for (int i = 0; i < index; i++)
    {
        temp[i] = this->_b[i];
    }
    for (int i = index; i < this->_bcount; i++)
    {
        temp[i] = this->_b[i + 1];
    }
    delete[] this->_b;
    this->_b = new Receipt[this->_bcount];
    for (int i = 0; i < this->_bcount; i++)
    {
        this->_b[i] = temp[i];
    }
    delete[] temp;
}
void Manager::addPaidReceipt(Receipt &b)
{

    if (this->_pbcount == 0)
    {
        this->_pb = new Receipt[this->_pbcount + 1];
        this->_pb[this->_pbcount] = b;
    }
    else
    {
        Receipt *temp = new Receipt[this->_pbcount];
        for (int i = 0; i < this->_pbcount; i++)
        {
            temp[i] = this->_pb[i];
        }
        delete[] this->_pb;
        this->_pb = new Receipt[this->_pbcount + 1];
        for (int i = 0; i < this->_pbcount; i++)
        {
            this->_pb[i] = temp[i];
        }
        this->_pb[this->_pbcount] = b;
        delete[] temp;
    }
    this->_pbcount++;
}
void Manager::checkIn()
{
    cout << "x========================================x" << endl;
    cout << "|               THUE PHONG               |" << endl;
    cout << "x========================================x" << endl;
    if(this->_bcount == this->_rcount)
    {
        cout << "Khong con phong trong!" << endl;
        return;
    }
    Customer c;
    cout << "       ---Nhap thong tin khach hang---" << endl;
    string id;
    cin.ignore(1000, '\n');
    cout << "CMND: ";
    getline(cin, id);
    int a=check_exist_Customer(id);
    if(a != this->_ccount)
    {
        cout << "------------------------" << endl;
        cout << this->_c[a];
        cout << "------------------------" << endl;
        cout << "Khach hang da ton tai! Su dung thong tin khach hang? (y/n): ";
        char stt;
        do
        {
            cin >> stt;
            if(stt != 'y' && stt != 'n')
            {
                cout << "Loi cu phap!" << endl;
                continue;
            }
            if(stt != 'y')
                return;
        } while(stt != 'y' && stt != 'n');
    }
    else if(a == this->_ccount)
    {
        c.setId(id);
        cin >> c;
    }
    int i, roomID, stt;
    system("cls");
    this->showAvailableRoom();
    cout << "Nhap phong: ";
    do
    {
        stt = 0;
        cin >> roomID;
        for (i = 0; i < this->_rcount; i++)
        {
            if (roomID == this->_r[i].getId() && this->_r[i].getStatus() == 1)
            {
                stt = 1;
                break;
            }
        }
        if (!stt)
            cout << "Phong khong ton tai hoac da duoc thue! Vui long nhap lai: ";
    } while (!stt);
    // thoi gian checkin
    Date checkInTime;
    checkInTime.setCurrentTime();
    // thoi gian thue
    int duration;
    cout << "Nhap so ngay thue: ";
    cin >> duration;
    Receipt temp(a, this->_r[i].getId(), checkInTime, duration);
    //in hoa don
    cout << "------------------------" << endl;
    if(a == this->_ccount)
        cout << c;
    else
        cout << this->_c[temp.getCustomerId()];
    cout << this->_r[i];
    cout << "Ngay thue phong: " << temp.getCheckinDate() << endl;
    cout << "So ngay thue: " << temp.getDuration() << endl;
    cout << "------------------------" << endl;
    //xac nhan thue phong
    char cf;
    do
    {
        cout << "Xac nhan thue phong (y/n): ";
        cin >> cf;
        if(cf != 'y' && cf != 'n')
        {
            cout << "Loi cu phap!" << endl;
            continue;
        }
        if(cf == 'y')
        {
            this->_r[i].setStatus(0);
            if(a == this->_ccount)
            {
                addCustomer(c);
                writeCustomerFile(c);
            }
            this->addReceipt(temp);
            writeReceiptFile(temp, 0);
            cout << "Thue phong thanh cong!" << endl;
        }
    } while(cf != 'y' && cf != 'n');
}
void Manager::confirm(int& i)
{
    Date checkOutTime;
    checkOutTime.setCurrentTime();
    Receipt temp = _b[i];
    //tim ma phong
    int j = 0;
    for (j = 0; j < this->_rcount; j++)
    {
        if(this->_r[j].getId() == temp.getRoomId())
            break;
    }
    temp.setCheckoutDate(checkOutTime);
    Date checkInTime = _b[i].getCheckinDate();
    //tinh tien
    int duration = checkOutTime - checkInTime;
    long total = long(duration) * _r[j].getPrice();
    temp.setTotalAmount(total);
    //in hoa don
    cout << "------------------------" << endl;
    cout << "Ma khach hang: " << temp.getCustomerId() << endl;
    cout << this->_c[temp.getCustomerId()];
    cout << this->_r[j];
    cout << temp << endl;
    cout << "------------------------" << endl;
    //xac nhan thanh toan
    char stt;
    do
    {
        cout << "Xac nhan thanh toan (y/n): ";
        cin >> stt;
        if(stt != 'y' && stt != 'n')
        {
            cout << "Loi cu phap!" << endl;
            continue;
        }
        if(stt == 'y')
        {
            // tim phong
            int j = 0;
            for (j = 0; j < this->_rcount; j++)
            {
                if (this->_b[i].getRoomId() == _r[j].getId())
                {
                    this->_r[j].setStatus(1);
                    break;
                }
            }
            addPaidReceipt(temp);
            writeReceiptFile(temp, 1);
            deleteReceipt(i);
            rewriteReceiptFile();
            cout << "Thanh toan thanh cong!" << endl;
        }
    } while(stt != 'y' && stt != 'n');
}
void Manager::checkOut()
{
    cout << "x========================================x" << endl;
    cout << "|                TRA PHONG               |" << endl;
    cout << "x========================================x" << endl;
    cout << "|       LUA CHON CHUC NANG TIM KIEM      |" << endl;
    cout << "|     1. Tim theo chung minh nhan dan    |" << endl;
    cout << "|     2. Tim theo phong thue             |" << endl;
    cout << "x========================================x" << endl;
    int choice;
    do
    {
        cout << "Moi nhap chuc nang: ";
        cin >> choice;
        if (choice < 1 || choice > 3)
            cout << "Chuc nang khong ton tai!" << endl;
    } while (choice < 1 || choice > 3);
    switch (choice)
    {
    case 1:
    {
        int count = 0;
        //chua ten phong
        int r[this->_rcount];
        //chua ma hoa don
        int b[this->_rcount];
        string id;
        cout << "Moi nhap CMND: ";
        cin >> id;
        for (int i = 0; i < this->_bcount; i++)
        {
            if (id == _c[_b[i].getCustomerId()].getId())
            {
                r[count] = _b[i].getRoomId();
                b[count] = i;
                count++;
            }
        }
        if(count == 0)
            cout << "So CMND nay khong ton tai hoac chua thue phong!" << endl;
        else if(count == 1)
            confirm(b[count - 1]);
        else
        {
            cout << setw(5) << left << "STT" << setw(10) << left << "Ten phong" << endl;
            cout << "--------------" << endl;
            for(int i = 0; i < count; i++)
            {
                cout <<  setw(5) << left << i << setw(10) << left << r[i] << endl;
            }
            int choice;
            bool stt;
            do
            {
                stt = 1;
                cout << "Chon STT phong muon thanh toan: ";
                cin >> choice;
                if (choice < 0 || choice >= count)
                {
                    cout << "Sai cu phap!" << endl;
                    stt = 0;
                }
            } while (!stt);
            confirm(b[choice]);
        }
        break;
    }
    case 2:
    {
        int i = 0;
        bool stt = 0;
        int id;
        cout << "Moi nhap ten phong: ";
        cin >> id;
        for (i = 0; i < this->_bcount; i++)
        {
            if (id == _b[i].getRoomId())
            {
                stt = 1;
                break;
            }
        }
        if(stt == 0)
            cout << "Phong chua duoc thue hoac khong ton tai!" << endl;
        else
            confirm(i);
        break;
    }
    default:
        break;
    }
    
}
void Manager::showReceipt(Receipt& b, int& i)
{
    cout << "Ma hoa don: " << i << endl;
    cout << "Ma khach hang: " << b.getCustomerId() << endl;
    cout << this->_c[b.getCustomerId()];
    for (int j = 0; j < this->_rcount; j++)
    {
        if(this->_r[j].getId() == b.getRoomId())
            cout << this->_r[j];
    }
    cout << b;
    cout << endl << endl;
}
// thao tac file
void Manager::readCustomerFile()
{
    ifstream f("Database/Customer.txt", ios_base::in);
    if (!f)
    {
        cerr << "Error: file not opened." << endl;
    }
    string d="";
    while (!f.eof())
    {
        Customer c;
        // Read Customer
        string a1, a3, a4, a5;
        Date a2;
        getline(f, a1, '\t');
        if(a1==d) break;
        f >> a2;
        f.ignore(1,'\t');
        getline(f, a3, '\t');
        getline(f, a4, '\t');
        getline(f, a5, '\n');
        c.setName(a1);
        c.setBirthday(a2);
        c.setPhone(a3);
        c.setAddress(a4);
        c.setId(a5);
        addCustomer(c);
    }
    f.close();
}

void Manager::writeCustomerFile(Customer &c)
{
    ofstream f("Database/Customer.txt", _S_app);
    if (_ccount != 1)
        f << endl;
    f << c.getName() << '\t' << c.getBirthday() << '\t' << c.getPhone() 
      << '\t' << c.getAddress() << '\t' << c.getId();
    f.close();
}
void Manager::writeReceiptFile(Receipt &r, int mode)
{
    ofstream f;
    int count;
    if(mode == 0)
    {
        f = ofstream("Database/Receipt.txt", _S_app);
        count = _bcount;
        if (count != 1)
            f << endl;
        f << r.getCustomerId() << '\t' << r.getRoomId() << '\t' ;
        f << r.getCheckinDate() << '\t';
        f << r.getCheckoutDate() << '\t';
        f << r.getDuration() << '\t' << r.getTotalAmount();
    }
    else
    {
        f = ofstream("Database/Paid_Receipt.txt", _S_app);
        count = _pbcount;
        if (count != 1)
            f << endl;
        f << "Ma hoa don: " << _pbcount - 1 << endl;
        f << "Ma khach hang: " << r.getCustomerId() << endl;
        Customer c = this->_c[r.getCustomerId()];
        f << c;
        //tim index room
        int j;
        for (j = 0; j < this->_rcount; j++)
        {
            if (this->_r[j].getId() == _r[j].getId())
            {
                this->_r[j].setStatus(1);
                break;
            }
        }
        Room w=this->_r[j];
        f << w;
        f << r << endl;
    }
    f.close();
}
void Manager::readReceiptFile()
{
    ifstream f;
    f = ifstream("Database/Receipt.txt", ios_base::in);
    if (!f)
    {
        cerr << "Error: file not opened." << endl;
    }
    while (!f.eof())
    {
        Receipt a;
        string e;
        int a1;
        f >> e;
        if(e == "") break;
        a1=stoi(e);
        // Read Customer
        a.setCustomerId(a1);
        f.ignore();
        int b1;
        f >> b1;
        // Read Room
        a.setRoomId(b1);
        Date c1, c2;
        // Check in date
        f.ignore();
        f >> c1;
        a.setCheckinDate(c1);
        // Check out date
        f.ignore();
        f >> c2;
        a.setCheckoutDate(c2);
        // Duration, Total Amount
        long c4;
        f.ignore();
        f >> c4;
        a.setTotalAmount(c4);
        f.ignore(2, '\n');
        addReceipt(a);
        }
    f.close();
}
void Manager::readPaidFile()
{
    ifstream f = ifstream("Database/Paid_Receipt.txt", ios_base::in);
    if (!f)
    {
        cerr << "Error: file not opened." << endl;
    }
    
    while(!f.eof())
    {
        string temp;
        getline(f, temp);
        if(temp == "")
            break;
        Receipt a;
        int a1;
        f.ignore(1000,':'); f.ignore();
        f >> a1;
        // Read Customer
        a.setCustomerId(a1);
        f.ignore(1000,'\n');
        f.ignore(1000,'\n');
        f.ignore(1000,'\n');
        f.ignore(1000,'\n');
        f.ignore(1000,'\n');
        f.ignore(1000,'\n');
        // Read Room
        int b1;
        f.ignore(1000,':'); f.ignore();
        f >> b1;
        a.setRoomId(b1);
        f.ignore(1000,'\n');
        // Check in date
        Date c1, c2;
        f.ignore(1000,':'); f.ignore();
        f >> c1;
        a.setCheckinDate(c1);
        // Check out date
        f.ignore(1000,':'); f.ignore();
        f >> c2;
        a.setCheckoutDate(c2);
        // Duration, Total Amount
        long c4;
        f.ignore(1000,':'); f.ignore();
        f >> c4;
        f.ignore(1000,'\n');
        f.ignore(1000,'\n');
        a.setTotalAmount(c4);
        addPaidReceipt(a);
    }
}
void Manager::rewriteReceiptFile()
{
    ofstream f("Database/Receipt.txt");
    for (int i = 0; i < this->_bcount; i++)
    {
        f << this->_b[i].getCustomerId() << '\t' << this->_b[i].getRoomId() << '\t';
        Date temp =this->_b[i].getCheckinDate(); 
        f << temp << '\t';
        temp = this->_b[i].getCheckoutDate();
        f << temp << '\t';
        f << this->_b[i].getDuration() << '\t' << this->_b[i].getTotalAmount();
        if (i != (this->_bcount - 1))
            f << endl;
    }
    f.close();
}
void Manager::rewriteRoomFile()
{
    ofstream f("Database/Room.txt");
    f << this->_rcount;
    for (int i = 0; i < this->_rcount; i++)
    {
        f << endl
          << this->_r[i].getId() << '\t';
        f << this->_r[i].getType() << '\t';
        f << this->_r[i].getStatus();
    }
    f.close();
}