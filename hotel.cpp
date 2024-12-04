//HOTEL MANAGEMENT
#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<bits/stdc++.h>
#include<string>
#include<unistd.h>
using namespace std;

fstream file;
fstream mfile; //file for meal class
int room_numbers[] ={101,102,103,104,201,202,203,204,301,302,303,304,401,402,403,404,501,502,503,601};

void line()
{
    cout<<"\t ****************************************************************************************************************************************"<<endl;
}
void dot_line()
{
    cout <<"\t ----------------------------------------------------------------------------------------------------------------------------------------" <<endl;
}
void tab()
{
    cout<<"\n\t\t\t\t\t\t  ";
}

void Hotel()
{
    line();
    cout<<"\n\t\t\t\t\t\t\t\t HOTEL AURORA \n"<<endl;
    line();
}

// Enumerator
enum IN
{
    IN_BACK = 8, //backspace
    IN_RET = 13  //return
};

string Password_input()
{
    string passwd = "";   // Stores the password
    char ch_ipt;

    while (true) // Until condition is true
    {
        ch_ipt = getch();

        if (ch_ipt == IN::IN_RET) //if user gives enter
        {
            cout << endl;
            return passwd;
        }
        else if (ch_ipt == IN::IN_BACK && passwd.length() != 0)
        {
            passwd.pop_back();      //if something entered
            cout << "\b \b";        //and giving backspace
            continue;
        }

        else if (ch_ipt == IN::IN_BACK && passwd.length() == 0)
        {
            continue;     //nothing entered and giving backspace
        }

        passwd.push_back(ch_ipt);
        cout << "*";
    }
}


string create_login(string name)
{
    tab(); cout<<"Enter the details"<<endl;
    tab(); cout<<"Enter username: ";
    tab(); cin>>name;
    tab(); cout<<"Enter password: ";
    tab();
    return name;
}

int check_pwd_file(string name,string pwd)
{
    //searching
    fstream file;
    file.open(name,ios::in);
    string mytxt;
    getline(file,mytxt);
    if(mytxt==pwd)
    {
        cout<<"\n";
        tab(); cout<<"***LOGGED IN SUCCESSFULLY!***"<<endl;
        sleep(2);
        return 2;
    }
    else
    {
        tab(); cout<<"Error! WRONG PASSWORD!"<<endl;
        return 1;
        sleep(2);
    }
    file.close();
}


int isLeapYr(int y)
{
    if((y%100==0)&&(y%4==0) || y%400==0)
        return 1;
    else
        return 0;
}

void checkout(int d, int m, int y, int days)
{
    if(d+days<=30 && m!=2)
        cout<<(d+days) <<"/" <<m <<"/" <<y <<endl;
    if((m==1 || m==3|| m==5|| m==7|| m==8|| m==10)&&((d+days)==31))
        cout<<(d+days) <<"/" <<m <<"/" <<y <<endl;

    if((m==1 || m==3|| m==5|| m==7|| m==8|| m==10)&&((d+days)>31))
    {
        d = (d+days)%31;
        m = m+1;
        cout<<d <<"/" <<m <<"/" <<y <<endl;
    }
    if((m==4 || m==6|| m==9|| m==11)&&((d+days)>30))
    {
        d = (d+days)%30;
        m = m+1;
        cout<<d <<"/" <<m <<"/" <<y <<endl;
    }
    if(m==12 && ((d+days)>31))
    {
        d = (d+days)%31;
        m = 1;
        y = y+1;
        cout<<d <<"/" <<m <<"/" <<y <<endl;
    }
    if(m==2 && d+days>=29)
    {
        if(isLeapYr(y)==1)
        {
            d = (d+days)%29;
            m = m+1;
            cout<<d <<"/" <<m <<"/" <<y <<endl;
        }
        else
        {
            d = (d+days)%28;
            m = m+1;
            cout<<d <<"/" <<m <<"/" <<y <<endl;
        }
    }
    if(m==2 && d+days<28)
    {
            cout<<(d+days)<<"/" <<m <<"/" <<y <<endl;
    }
}


/**************************************************************************************/

class room
{
  protected:
    int rno;
    char free[7];

  public:
    void room_types()
    {
        tab(); cout<<"\t   AVAILABLE TYPES OF ROOM "<<endl;
        tab(); cout<<"** Exclusive of (12%)GST and Room service charge **"<<endl;
        line();
        tab(); cout<<"TYPE" <<"\t\t\t\t" <<"PRICE (per day stay)\n" <<endl;
        tab(); cout<<"1. AC Single Room " <<"\t\t\t" <<"1500" <<endl;
        tab(); cout<<"2. Non-AC single Room " <<"\t\t" <<"1000" <<endl;
        tab(); cout<<"3. AC Double Room " <<"\t\t\t" <<"2500" <<endl;
        tab(); cout<<"4. Non-AC Double Room " <<"\t\t" <<"2000" <<endl ;
        tab(); cout<<"5. Deluxe Room " <<"\t\t\t" <<"3500" <<endl;
        tab(); cout<<"6. Suite Room " <<"\t\t\t" <<"4500 \n" <<endl;
        line();
    }

    void get_info(int i)
    {
        rno = room_numbers[i];
        strcpy(free,"vacant");
    }
    int check()
    {
        if(strcmp(free,"vacant")==0)
            return 1;
        else
            return 0;
    }
    void update()
    {
        strcpy(free,"booked");
    }
    void display()
    {
        tab(); cout<<"\t" <<rno <<"\t"<<free;
    }

    void write()
    {
        room rm;
        file.open("Room_book.txt", ios::app);
        for(int i=0;i<20;i++)
        {
            rm.get_info(i);
            file.write((char*)&rm, sizeof(rm));
        }
        file.close();
    }
    void change()
    {
        strcpy(free,"vacant");
    }
    void hide_read()
    {
        room rm;
        file.open("Room_book.txt", ios::in);
        file.seekp(0,ios::beg);
        for(int i=0;i<20;i++)
        {
            file.read((char*)&rm, sizeof(rm));
        }
        file.close();
    }
    void vacate(int num)
    {
        room rm;
        rm.hide_read();
        rm.hide_read();
        file.open("Room_book.txt",ios::out | ios::in);
        file.seekp(0);
        bool found = false;
        while(!file.eof())
        {
            file.read((char*)&rm, sizeof(rm));
            if(rm.rno==num)
            {
                rm.change();
                int pos = sizeof(rm);
                file.seekp(-pos,ios::cur);
                file.write((char*)&rm, sizeof(rm));
                found = true;
                break;
            }
        }
        if(!found)
        {
                        cout << "Record not found" << endl;
        }
        file.close();
    }

    int book(int x)
    {
        room rm;
        file.open("Room_book.txt",ios::out | ios::in);
        file.seekp(0);
        switch(x)
        {
            case 1: file.seekg(0*sizeof(rm),ios::beg);
                    for(int i=0;i<4;i++)
                    {
                        file.read((char*)&rm, sizeof(rm));
                        if(rm.check()==1)
                        {
                            rm.update();
                            int pos = sizeof(rm);
                            file.seekp(-pos,ios::cur);
                            file.write((char*)&rm, sizeof(rm));
                            return room_numbers[0+i];
                        }
                    }
                    tab(); cout<<"No Ac single rooms available!!"<<endl;
                    return 1;
                    break;

            case 2: file.seekg(4*sizeof(rm),ios::beg);
                    for(int i=0;i<4;i++)
                    {
                        file.read((char*)&rm, sizeof(rm));
                        if(rm.check()==1)
                        {
                            rm.update();
                            int pos = sizeof(rm);
                            file.seekp(-pos,ios::cur);
                            file.write((char*)&rm, sizeof(rm));
                            return room_numbers[4+i];
                        }
                    }
                    tab(); cout<<"No Non-Ac single rooms available!!"<<endl;
                    return 1;
                    break;

            case 3: file.seekg(8*sizeof(rm),ios::beg);
                    for(int i=0;i<4;i++)
                    {
                        file.read((char*)&rm, sizeof(rm));
                        if(rm.check()==1)
                        {
                            rm.update();
                            int pos = sizeof(rm);
                            file.seekp(-pos,ios::cur);
                            file.write((char*)&rm, sizeof(rm));
                            return room_numbers[8+i];
                        }
                    }
                    tab();cout<<"No Ac double rooms available!!"<<endl;
                    return 1;
                    break;

            case 4: file.seekg(12*sizeof(rm),ios::beg);
                    for(int i=0;i<4;i++)
                    {
                        file.read((char*)&rm, sizeof(rm));
                        if(rm.check()==1)
                        {
                            rm.update();
                            int pos = sizeof(rm);
                            file.seekp(-pos,ios::cur);
                            file.write((char*)&rm, sizeof(rm));
                            return room_numbers[12+i];
                        }
                    }
                    tab(); cout<<"No Non-Ac double rooms available!!"<<endl;
                    return 1;
                    break;

            case 5: file.seekg(16*sizeof(rm),ios::beg);
                    for(int i=0;i<3;i++)
                    {
                        file.read((char*)&rm, sizeof(rm));
                        if(rm.check()==1)
                        {
                            rm.update();
                            int pos = sizeof(rm);
                            file.seekp(-pos,ios::cur);
                            file.write((char*)&rm, sizeof(rm));
                            return room_numbers[16+i];
                        }
                    }
                    tab(); cout<<"No Deluxe rooms available!!"<<endl;
                    return 1;
                    break;

            case 6: file.seekg(19*sizeof(rm),ios::beg);
                    file.read((char*)&rm, sizeof(rm));
                    if(rm.check()==1)
                    {
                        rm.update();
                        int pos = sizeof(rm);
                        file.seekp(-pos,ios::cur);
                        file.write((char*)&rm, sizeof(rm));
                        return room_numbers[19];
                    }
                    tab(); cout<<"Suit room is not available!!"<<endl;
                    return 1;
                    break;

        }
        file.close();

    }
    void show()
    {
        room rm;
        file.open("Room_book.txt", ios::in);
        file.seekp(0,ios::beg);
        for(int i=0;i<20;i++)
        {
            file.read((char*)&rm, sizeof(rm));
            rm.display();
        }
        file.close();
    }
};


/***************************************************************************/

class customer
{
  public:
    long long mobile;
    char room_type[30];
    int no_people,days,advance,balance,total_r,room_no;
    int dd,mm,yyyy; //check-in date
  public:
    char name[30];
    void get_info(int room_ch,int rate,char room[]);
    void display();

    void show_all()
    {
        cout <<"\t" <<setw(20)<<name <<"\t"
            <<setw(10)<<mobile <<"\t" <<setw(3)<<room_no <<"\t"
            <<setw(10)<<dd<<"/"<<mm<<"/"<<yyyy <<"\t" <<setw(4)<<days <<"\t\t" <<setw(5)<<total_r <<"\t\t" <<setw(5)<<balance<<endl;
    }
};

void customer::get_info(int roomnum,int rate,char room[])
{
    tab();cout<<"Enter name: ";
    cin >> ws;
    cin.getline(name, 30);
    tab(); cout<<"Enter no.of people: ";
    cin>>no_people;
    tab(); cout<<"Enter mobile number: ";
    cin>>mobile;
    tab(); cout<<"Enter no. of days of stay: ";
    cin>>days;
    tab(); cout<<"Enter Check-in date(dd mm yyyy): ";
    cin>>dd>>mm>>yyyy;
    tab(); cout<<"Check-out date: "; checkout(dd,mm,yyyy,days);//<<dd+days <<"/" <<mm <<"/" <<yyyy<<endl;
    total_r = days*rate;
    tab(); cout<<"Your total room charge would be "<<total_r<<endl;
    char ch;
    string coupon;
    tab(); cout<<"Do you have the coupon for 20% discount (y/n)? ";
    cin>>ch;
    if(ch=='Y'||ch=='y')
    {
        tab(); cout<<"Enter the coupon code: ";  //coupon code - hotel2023
        cin.ignore();
        getline(cin,coupon);
        if(coupon=="hotel2023")
        {
            total_r = total_r-(total_r*0.2);
            tab(); cout<<"Congrats! you got 20% discount"<<endl;
            tab(); cout<<"Amount to be paid: "<<total_r <<endl;
        }
        else
        {
            tab(); cout<<"Sorry! Wrong coupon code!"<<endl;
        }
    }
    tab(); cout<<"Enter advance payment: ";
    cin>>advance;
    balance = (total_r)-advance;
    tab(); cout<<"Balance payment: "<<balance <<endl;
    strcpy(room_type,room);
    room_no = roomnum;
    tab(); cout<<"Your Room number: "<<room_no <<endl;
    tab(); cout<<"** BOOKED YOUR ROOM SUCCESSFULLY **"<<endl;
}

void customer:: display()
{
    system("cls");
    Hotel();
    cout<<endl;
    tab();cout<<"CUSTOMER INFO";
    tab();cout<<"_____________\n";
    tab();cout<<"Name: "<<name <<"\n";
    tab();cout<<"No.of people: "<<no_people <<"\n";
    tab();cout<<"Mobile. no: " <<mobile <<"\n";
    tab();cout<<"No. of days: "<<days <<"\n";
    tab();cout<<"Check-in date: "<<dd <<"/" <<mm <<"/" <<yyyy <<"\n";
    tab();cout<<"Check-out date: ";checkout(dd,mm,yyyy,days);
    cout<<endl;
    tab();cout<<"ROOM INFO";
    tab();cout<<"_________\n";
    tab();cout<<"Room number: "<<room_no <<"\n";
    tab();cout<<"Room type: "<<room_type <<"\n";
    tab();cout<<"Total Room charge: "<<total_r <<"\n";
    tab();cout<<"Advance paid: "<<advance <<"\n";
    tab();cout<<"Balance amount: "<<balance <<"\n";
}


/******************************************************************************************************/

class meals
{
    public:
    int total_m=0;

    int meal_types()
    {
        int meal_type,st_ch;
        char ch1;
        float bill;

        begin://goto statement
        system("cls");
        Hotel();
        tab(); cout<<"\t  TYPES:"<<endl;
        tab(); cout<<"\t 1. STARTERS"<<endl;
        tab(); cout<<"\t 2. MEALS"<<endl;
        tab(); cout<<"\t 3. DESSERTS AND BEVERAGES"<<endl;
        tab(); cout<<"\t 4. EXIT"<<endl;
        tab(); cout<<"Please select your prefered type: ";
        cin>>meal_type;
        system("cls");
        Hotel();
        if(meal_type==1)
        {
            starters:
            tab();cout<<"ITEM"<<"\t\t\t\t"<<"PRICE"<<endl;
            tab();cout<<"1.Dragon Chicken"<<"\t\t"<<"350"<<endl;
            tab();cout<<"2.French Fries"<<"\t\t"<<"75"<<endl;
            tab();cout<<"3.Mini Pizza"<<"\t\t\t"<<"125"<<endl;
            tab();cout<<"4.Momos"<<"\t\t\t"<<"120"<<endl;
            tab();cout<<"5.Nachos"<<"\t\t\t"<<"60"<<endl;
            tab();cout<<"6.Nuggets"<<"\t\t\t"<<"150"<<endl;
            line();
        }
        if(meal_type==2)
        {
            lunch:
            tab();cout<<"ITEM"<<"\t\t\t\t"<<"PRICE"<<endl;
            tab();cout<<"1.Biriyani"<<"\t\t\t"<<"180"<<endl;
            tab();cout<<"2.Fried rice"<<"\t\t\t"<<"170"<<endl;
            tab();cout<<"3.Pasta"<<"\t\t\t"<<"200"<<endl;
            tab();cout<<"4.Rice with curry"<<"\t\t"<<"150"<<endl;
            tab();cout<<"5.Naan with butter chicken"<<"\t"<<"145"<<endl;
            tab();cout<<"6.Spagetti"<<"\t\t\t"<<"170"<<endl;
            line();
        }
        if(meal_type==3)
        {
            dessert:
            tab();cout<<"ITEM"<<"\t\t\t\t"<<"PRICE"<<endl;
            tab();cout<<"1.Icecream"<<"\t\t\t"<<"90"<<endl;
            tab();cout<<"2.Sizzling brownie"<<"\t\t"<<"170"<<endl;
            tab();cout<<"3.choco fudge"<<"\t\t\t"<<"190"<<endl;
            tab();cout<<"4.kheerkadam"<<"\t\t\t"<<"160"<<endl;
            tab();cout<<"5.Brownie with icecream"<<"\t"<<"185"<<endl;
            tab();cout<<"6.Gulab jamun"<<"\t\t\t"<<"120"<<endl;
            line();
        }
        return meal_type;
    }

    //meal info into file
    void meal_info(int q,int price,string name)
    {
        total_m+=price*q;
        mfile.open("meal.txt",ios::app);
        if(!mfile)
        {
            cout<<"file creation failed\n";
            return;
        }
        else
        {
            mfile <<"\t\t\t\t" <<setw(25)<<name   <<"\t" <<setw(3)<<price  <<"\t" <<setw(3)<<q          <<"\t\t" <<(price*q) <<endl;
            mfile.close();
        }
    }
};

/*************************************************************************************************************/

class bill:public customer,public room
{
 public:
    float billamt;
    float servicecharge;
    float gst;

    int display_bill(char name_bill[])
    {
        file.open("customer_info.dat", ios::in|ios::binary);
        if(!file)
            cout<<"file does not exist!"<<endl;
        else
        {
            customer c;
            int found=0;
            system("cls");
            while(file.read(reinterpret_cast<char *>(&c),sizeof(c)))
            {
                if(strcmp(c.name,name_bill) == 0)
                {
                    found=1;
                    gst = 0.12*c.total_r;
                    servicecharge = 0.02*c.total_r;
                    Hotel();
                    tab(); cout<<"\t   YOUR TOTAL BILL\n"<<endl;
                    cout<<"\t\t\t\t\t Name: " <<c.name <<"\t\t\t\t " <<"Room no: " <<c.room_no <<endl;
                    dot_line();
                    cout<<"\t\t\t\t" <<setw(30)<<"ROOM RENT\t\t" <<":" <<setw(10)<<c.total_r<<endl;
                    cout<<"\t\t\t\t" <<setw(30)<<"ADVANCE\t\t"   <<":" <<setw(10)<<c.advance<<endl;
                    cout<<"\t\t\t\t" <<setw(30)<<"BALANCE\t\t"  <<":" <<setw(10)<<c.balance<<endl;
                    cout<<"\t\t\t\t" <<setw(30)<<"ROOM SERVICE CHARGE (2%)\t\t"<<":"<<setw(10)<<servicecharge<<endl;
                    cout<<"\t\t\t\t" <<setw(30)<<"GST (12%)\t\t"   <<":" <<setw(10)<<gst <<endl;
                    cout<<endl;
                    dot_line();
                    tab(); cout<<"\t\t TO PAY :"<<setw(10)<<c.balance+gst+servicecharge<<endl;
                    return c.room_no;
                    break;
                }
            }
            if (found==0)
            {
                cout << "OOPS! Customer not found" << endl;
            }
            file.close();

        }
    }
};

/**********************************************************************************************/
class admin : public room
{
  string name,pwd;
  public:
     void file_create_login(string name1,string name2,string pwd1,string pwd2)
     {
        fstream file;
        //file writing
        file.open(name1,ios::out);
        if(!file)
        {
        cout<<"File creation failed";
        }
        else
        {
            file<<pwd1;   //Writing to file
            file.close();
        }
        file.open(name2,ios::out);
        if(!file)
        {
        cout<<"File creation failed";
        }
        else
        {
            file<<pwd2;   //Writing to file
            file.close();
        }
      }

      int search_login()
      {
            tab();
            int t=0;
            attempt_user:
            tab();
            cout<<"Enter username: ";
            cin>>name;
            tab();
            cout<<"Enter password: ";
            pwd = Password_input();
            tab();
            return(check_pwd_file(name,pwd));
      }


};

/************************************************************************************/

int main()
{

    room r;
    customer c;
    admin ad;
    meals m;

    ifstream file1("Room_book.txt");
    if(!file1.is_open())
    {
        r.write();
    }
    fstream filef; //feedback into file
/**************************/
    char user;
    start:
    line();
    cout<<"\n\t\t\t\t\t\t\tWELCOME TO HOTEL AURORA\n"<<endl;
    line();
    tab(); cout<<"\tAdmin (a)" <<endl;
    tab(); cout<<"\tCustomer (c)" <<endl;
    tab(); cout<<"\tEnter the Choice: ";
    cin>>user;

/***********************************************************************/
    if(user=='a')
    {
        system("cls");
        string name1,name2,pwd2,pwd1,pass,name,pwd;
        char admin;
        Hotel();
        tab(); cout<<"\t\t **LOGIN DETAILS** \n"<<endl;
        tab(); cout<<"Have you logged in before(y/n)? ";
        cin>>admin;
        if(admin=='n'||admin=='N')
        {
            char ch;
            tab(); cout<<"Do you want to create a new account? (y/n)"<<endl;
            tab(); cin>>ch;
            if(ch=='Y' || ch=='y')
            {
                tab(); name1 = create_login(name1);
                tab(); pwd1 = Password_input();
                tab(); name2 = create_login(name2);
                tab(); pwd2 = Password_input();
                tab(); ad.file_create_login(name1,name2,pwd1,pwd2);
                tab(); cout<<"***CREATED LOGIN SUCCESSFULLY!***"<<endl;
                sleep(2);
                system("cls");
                goto start;
            }
        }
        if(admin=='y'||admin=='Y')
        {
            int check = ad.search_login();
            if(check==1)
            {
                sleep(2);
                system("cls");
                goto start;
            }
        }
       /*****************************/
        int ch;
        admin_page:
        system("cls");
        Hotel();
        tab(); cout<<"1. Book room for the guest" <<endl;
        tab(); cout<<"2. Generate bill for a customer" <<endl;
        tab(); cout<<"3. Show details of all customer" <<endl;
        tab(); cout<<"4. Check the availability of rooms" <<endl;
        tab(); cout<<"5. Search for a customer details" <<endl;
        tab(); cout<<"6. See the Feedbacks" <<endl;
        tab(); cout<<"7. Exit" <<endl;
        tab(); cout<<"Enter your choice: ";
        cin>>ch;
        system("cls");

        if(ch==7)   //exit
        {
            system("cls");
            goto start;
        }

        if(ch==2)
        {
            bill bl;
            char name_bill[30];
            int rv;//room to vacate
            Hotel();
            tab(); cout<<"Enter your name: ";
            cin >> ws;
            cin.getline(name_bill, 30);
            cout<<"\n\n";
            tab(); cout<<"** GENERATING BILL FOR " <<name_bill <<" **" <<endl;
            sleep(1);
            rv = bl.display_bill(name_bill);
            printf("\n\n\n");
            r.vacate(rv);

            //delete that customer info
            fstream filec; //file object for reading customer detaila
            fstream filev;  //file object for writing customer details after vacating
            filec.open("customer_info.dat", ios::in | ios::binary);
            filec.seekp(0);
            filev.open("customer_info_new.dat", ios::app | ios::binary);
            if(!filec)
                cout<<"File not found!";
            else
            {
                filec.read(reinterpret_cast<char *>(&c),sizeof(c));
                while(!filec.eof())
                {
                    if(strcmp(name_bill,c.name)!=0)
                    {
                        filev.write(reinterpret_cast<const char *>(&c), sizeof(c));
                    }
                    filec.read(reinterpret_cast<char *>(&c),sizeof(c));
                }
            }
            filev.close();
            filec.close();
            remove("customer_info.dat");
            rename("customer_info_new.dat","customer_info.dat");

            cout<<"\t\t\t\t\t ^_^ THANKYOU FOR CHOOSING US!  HAVE A GREAT DAY AHEAD! ^_^ "<<endl;
            getch();
            system("cls");
            goto admin_page;
        }

        if(ch==1)  //book room
        {
            int roomnum=0;
            Hotel();
            tab(); cout<<"\t   BOOKING ROOM FOR A GUEST"<<endl;
            int room_ch;
            do
            {
                r.room_types();
                r.hide_read();
                tab(); cout<<"Enter your choice: ";
                cin>>room_ch;
                roomnum = r.book(room_ch);
                if(roomnum==1)
                {
                    tab(); cout<<"** Sorry! Please choose other type of room! **"<<endl;
                    sleep(3);
                    system("cls");
                }
            }while(roomnum==1);
            tab(); cout<<"BOOKING YOUR ROOM..."<<endl;
            sleep(1);

            system("cls");
            Hotel();
            switch(room_ch)
            {
                case 1: c.get_info(roomnum,1500,"AC single room");
                        break;
                case 2: c.get_info(roomnum,1000,"Non-AC single room");
                        break;
                case 3: c.get_info(roomnum,2500,"AC double room");
                        break;
                case 4: c.get_info(roomnum,2000,"Non-AC double room");
                        break;
                case 5: c.get_info(roomnum,3500,"Deluxe room");
                        break;
                case 6: c.get_info(roomnum,4500,"Suit room");
                        break;
            }

            fstream filec;  //file object for writing customer datails
            filec.open("customer_info.dat",ios::app | ios::binary);
            if(!filec)
                cout<<"File creation failed";
            else
            {
                filec.write(reinterpret_cast<const char *>(&c), sizeof(c));
            }
            filec.close();
            tab(); cout<<"** Registered Successfully!! **"<<endl;
            sleep(5);
            system("cls");
            goto admin_page;
        }

        if(ch==4)
        {
            Hotel();
            r.hide_read();
            tab(); cout<<"   Availbility of rooms"<<endl;
            dot_line();
            tab(); cout <<"Room number" <<"\t" <<"status" <<endl;
            r.show();
            cout<<"\n";
            dot_line();
            tab(); cout<<"101 - 104   -->   AC single rooms";
            tab(); cout<<"201 - 204   -->   Non-AC single rooms";
            tab(); cout<<"301 - 304   -->   AC double rooms";
            tab(); cout<<"401 - 404   -->   Non-AC double rooms";
            tab(); cout<<"501 - 503   -->   Deluxe rooms";
            tab(); cout<<"601         -->   Suit room";
            getch();
            goto admin_page;
        }

        if(ch==5)
        {
            char name_search[30]; //search for a customer details by admin
            file.open("customer_info.dat", ios::in|ios::binary);
            if(!file)
                cout<<"file does not exist!"<<endl;

            Hotel();
            tab(); cout<<"Enter the name to search: ";
            cin >> ws;
            cin.getline(name_search, 30);
            while(!file.eof())
            {
                file.read(reinterpret_cast<char *>(&c),sizeof(c));
                if(strcmp(c.name,name_search) == 0)
                {
                    c.display();
                    break;
                }
            }
            file.close();
            getch();
            system("cls");
            goto admin_page;
        }

        if(ch==6)
        {
            Hotel();
            tab(); cout<<"** FEEDBACKS **"<<endl;
            filef.open("Feedback.txt",ios::in);
            string feed;
            while(getline(filef,feed))
            {
                cout <<"\n\t\t\t " <<"-> "<<feed <<endl;
            }
            filef.clear(); // clear any error flags
            filef.seekg(0); // reset file pointer to beginning of file
            filef.close();
            getch();
            goto admin_page;
        }

        if(ch==3)
        {
            ifstream files;//to show details of all customers file
            customer all;//object to read and show all details -admin class
            Hotel();
            tab(); cout<<"\t\t CUSTOMER DETAILS"<<endl;
            dot_line();
            cout <<"\t" <<setw(20)<<"NAME" <<"\t" <<setw(10)<<"MOBILE_no." <<"\t" <<setw(3)<<"ROOM_no."<<"\t" <<setw(10)<<"CHECK-IN" <<"\t" <<setw(3)<<"DAYS STAY" <<"\t" <<setw(5)<<"ROOM CHARGE" <<"\t" <<setw(5)<<"BALANCE"<<endl<<endl;
            files.open("customer_info.dat", ios::in|ios::binary);
            files.seekg(0);
            while (files.read(reinterpret_cast<char*>(&all), sizeof(all)))
            {
                all.show_all();
            }
            files.close();
        }
        getch();
        goto admin_page;
    }

/**************************************************************************/
    else if(user=='c')
    {
        system("cls");
        int cus; //exiting or new customer
        customer_page:
        Hotel();
        tab(); cout<<"Are you a new guest or already residing guest? "<<endl;
        tab(); cout<<"\t 1. New"<<endl;
        tab(); cout<<"\t 2. Already residing"<<endl;
        tab(); cout<<"\t 3. Exit"<<endl;
        tab(); cout<<"Enter your choice: ";
        cin>>cus;
        system("cls");

        if(cus==3)
            goto start;
        if(cus==1)
        {
            int ch; //book room or exit
            int roomnum=0;
            Hotel();
            tab(); cout<<"1. Book room" <<endl;
            tab(); cout<<"2. Exit" <<endl;
            tab(); cout<<"Enter your choice: ";
            cin>>ch;
            system("cls");
            if(ch==1)
            {
                int room_ch;
                do
                {
                    Hotel();
                    r.room_types();
                    r.hide_read();
                    tab(); cout<<"Enter your choice: ";
                    cin>>room_ch;
                    roomnum = r.book(room_ch);
                    if(roomnum==1)
                    {
                        tab(); cout<<"** Sorry! Please choose other type of room! **"<<endl;
                        //r.show();
                        sleep(3);
                        system("cls");
                    }
                }while(roomnum==1);
                tab(); cout<<"BOOKING YOUR ROOM..."<<endl;
                sleep(1);

                system("cls");
                Hotel();
                switch(room_ch)
                {
                    case 1: c.get_info(roomnum,1500,"AC single room");
                            break;
                    case 2: c.get_info(roomnum,1000,"Non-AC single room");
                            break;
                    case 3: c.get_info(roomnum,2500,"AC double room");
                            break;
                    case 4: c.get_info(roomnum,2000,"Non-AC double room");
                            break;
                    case 5: c.get_info(roomnum,3500,"Deluxe room");
                            break;
                    case 6: c.get_info(roomnum,4500,"Suit room");
                            break;
                }

                fstream filec;  //file object for writing customer datails
                filec.open("customer_info.dat",ios::app | ios::binary);
                if(!filec)
                    cout<<"File creation failed";
                else
                {
                    filec.write(reinterpret_cast<const char *>(&c), sizeof(c));
                }
                filec.close();
                tab(); cout<<"** Registered Successfully!! **"<<endl;
                sleep(5);
                system("cls");
                goto start;
            }
            if(ch==2)
                goto start;
        }

        if(cus==2)
        {
           char cus_name_search[30];
            int choice;//order meal or exit
            Hotel();
            tab(); cout<<"\t ** WELCOME **\n"<<endl;
            tab(); cout<<"Enter your name: ";
            cin >> ws;
            cin.getline(cus_name_search, 30);
            file.open("customer_info.dat", ios::in|ios::binary);
            int found=0;//to check if the customer exists
            while(!file.eof())
            {
                file.read(reinterpret_cast<char *>(&c),sizeof(c));
                if(strcmp(c.name,cus_name_search) == 0)
                {
                    found=1;
                    tab(); cout<<"** Welcome  ^_^  " <<c.name <<" **" <<endl;
                    sleep(2);
                    break;
                }
            }
            file.close();
            if(found==1)
            {
                begin:
                system("cls");
                Hotel();
                tab();cout<<"1. Order meal" <<endl;
                tab();cout<<"2. See details"<<endl;
                tab();cout<<"3. Vacate room and generate bill"<<endl;
                tab();cout<<"4. Feedback entry"<<endl;
                tab();cout<<"5. exit "<<endl;
                tab();cout<<"Enter your choice: ";
                cin>>choice;
                if(choice==1)
                {
                    char more;
                    int c;
                    int meal_ch,meal_qty;
                    system("cls");
                    fbegin:
                    Hotel();
                    c = m.meal_types();
                    tab(); cout<<"Enter your choice:  ";
                    cin>>meal_ch;
                    tab(); cout<<"Enter the quantity you want?  ";
                    cin>>meal_qty;

                    if(c==1)
                    {
                        switch(meal_ch)
                        {
                            case 1: m.meal_info(meal_qty,350,"Dragon chicken");
                            break;
                            case 2:m.meal_info(meal_qty,75,"French Fries");
                            break;
                            case 3:m.meal_info(meal_qty,125,"Mini Pizza");
                            break;
                            case 4:m.meal_info(meal_qty,120,"Momos");
                            break;
                            case 5:m.meal_info(meal_qty,60,"Nachos");
                            break;
                            case 6:m.meal_info(meal_qty,150,"Nuggets");
                            break;
                        }
                    }
                    if(c==2)
                    {
                        switch(meal_ch)
                        {

                            case 1: m.meal_info(meal_qty,180,"Chicken Biriyani");
                            break;
                            case 2:m.meal_info(meal_qty,170,"Fried rice");
                            break;
                            case 3:m.meal_info(meal_qty,200,"Pasta");
                            break;
                            case 4:m.meal_info(meal_qty,150,"Rice with curry");
                            break;
                            case 5:m.meal_info(meal_qty,145,"Naan with butter chicken");
                            break;
                            case 6:m.meal_info(meal_qty,170,"Spagetti");
                            break;
                        }
                    }
                    if(c==3)
                    {
                        switch(meal_ch)
                        {
                            case 1: m.meal_info(meal_qty,90,"Icecream");
                            break;
                            case 2:m.meal_info(meal_qty,170,"Sizzling brownie");
                            break;
                            case 3:m.meal_info(meal_qty,190,"choco fudge");
                            break;
                            case 4:m.meal_info(meal_qty,160,"Kheerkadam");
                            break;
                            case 5:m.meal_info(meal_qty,185,"Brownie with icecream");
                            break;
                            case 6:m.meal_info(meal_qty,120,"Gulab jamun");
                            break;
                        }
                    }
                    if(c==4)
                        goto begin;

                    tab(); cout<<"Do you want to order something else (y/n)?  ";
                    cin>>more;
                    if((more=='y')||(more=='Y'))
                    {
                        goto fbegin;
                        system("cls");
                    }
                    if((more=='n')||(more=='N'))
                    {
                        system("cls");
                        mfile.open("meal.txt",ios::app);
                        mfile<<"\t ----------------------------------------------------------------------------------------------------------------------------------------";
                        mfile<<"\n\t\t\t\t\t\t\t\t\t\t TOTAL: "<<m.total_m<<"\n\n";
                        mfile.close();

                        Hotel();
                        cout<<"\n\t\t\t\t\t\t\t\tYOUR FOOD ORDER BILL\n"<<endl;
                        cout<<"\t ----------------------------------------------------------------------------------------------------------------------------------------" <<endl;
                        cout<<"\t\t\t\t" <<setw(25)<<"NAME" <<"\t" <<setw(3)<<"RATE" <<"\t" <<setw(3)<<"QUANTITY" <<"\t" <<"COST" <<endl<<endl;;

                        mfile.open("meal.txt",ios::in);
                        string bill;
                        while(getline(mfile,bill))
                        {
                            cout<<bill<<endl;
                        }
                        mfile.close();
                        dot_line();
                        tab(); cout<<" Your food will be provided to your room soon!!"<<endl;
                        tab(); cout<<"** Please pay your bill at the time of delivery **\n" <<endl;
                        tab(); cout<<"** THANK YOU **  ^_^  ** HAVE A NICE DAY **\n"<<endl;
                        line();
                        mfile.open("meal.txt",ios::in|ios::trunc|ios::out);
                        mfile.seekp(0);
                        mfile.close();
                        getch();
                        goto begin;

                    }

                }
                else if(choice==2)
                {
                    file.open("customer_info.dat", ios::in|ios::binary);
                    while(!file.eof())
                    {
                        file.read(reinterpret_cast<char *>(&c),sizeof(c));
                        if(strcmp(c.name,cus_name_search) == 0)
                        {
                            c.display();
                            break;
                        }
                    }
                    file.close();
                    getch();
                    system("cls");
                    goto begin;
                }
                else if(choice==3)
                {
                    room r;
                    system("cls");
                    bill b;
                    char name_bill[30];
                    int rv;//room to vacate
                    retry:
                    Hotel();
                    tab(); cout<<"Enter your name: ";
                    cin >> ws;
                    cin.getline(name_bill, 30);
                    if(strcmp(cus_name_search,name_bill)==0)
                    {
                        rv = b.display_bill(name_bill);
                        printf("\n\n\n");
                        r.vacate(rv);

                        //delete that customer info
                        fstream filec; //file object for reading customer detaila
                        fstream filev;  //file object for writing customer details after vacating
                        filec.open("customer_info.dat", ios::in | ios::binary);
                        filec.seekp(0);
                        filev.open("customer_info_new.dat", ios::app | ios::binary);
                        if(!filec)
                            cout<<"File not found!";
                        else
                        {
                            filec.read(reinterpret_cast<char *>(&c),sizeof(c));
                            while(!filec.eof())
                            {
                                if(strcmp(name_bill,c.name)!=0)
                                {
                                    filev.write(reinterpret_cast<const char *>(&c), sizeof(c));
                                }
                                filec.read(reinterpret_cast<char *>(&c),sizeof(c));
                            }
                        }
                        filev.close();
                        filec.close();
                        remove("customer_info.dat");
                        rename("customer_info_new.dat","customer_info.dat");

                        cout<<"\t\t\t\t ^_^ THANKYOU FOR CHOOSING US!  HAVE A GREAT DAY AHEAD! ^_^ "<<endl;
                        getch();
                        system("cls");
                        goto start;
                    }
                    else
                    {
                        cout<<"\n\n\n";
                        tab(); cout<<"** PLEASE ENTER YOUR NAME CORRECTLY **";
                        sleep(1);
                        system("cls");
                        goto retry;
                    }
                }
                else if(choice==4)
                {
                    string feedback;
                    system("cls");
                    Hotel();
                    cout<<"\n\t\t Enter your feedback message: ";
                    getline(cin>>ws,feedback);
                    filef.open("Feedback.txt",ios::app);
                    filef <<feedback <<"\n";
                    filef.close();
                    cout<<"\n\n\t\t THANKYOU FOR YOUR FEEDBACK! HAVE A NICE DAY!"<<endl;
                    sleep(2);
                    goto begin;
                }
                else if(choice==5)
                {

                    tab(); cout<<"Have a nice day!"<<endl;
                    sleep(1);
                    system("cls");
                    goto start;
                }
                else
                {
                    cout<<"\n\tEnter a valid option!\n";
                    sleep(2);
                    system("cls");
                    goto begin;
                }
            }
            if(found==0)
            {
                cout<<"\n";
                tab(); cout<<"YOU HAVEN'T REGISTERED!"<<endl;
                sleep(2);
                system("cls");
                goto start;
            }

        }
    }
    else
    {
        cout<<"\n\n\n\n";
        tab(); cout<<"** Enter a VALID choice!! **"<<endl;
        sleep(2);
        system("cls");
        goto start;
    }
}