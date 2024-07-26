#include <bits/stdc++.h>

using namespace std;

#define CLEAR_SCREEN "cls"

//***************************STUDENT SECTION*****************************

class Student
{
    public :
        int cls,i;
        string Name,sub,Student_Id,Stream;
        void Entry();
        void Display();
        string return_id()
        {
            return Student_Id;
        }
        string return_name()
        {
            return Name;
        }
};

void Student::Entry()
{ 
    system(CLEAR_SCREEN);
    cout<<"Enter Student Id : ";
    cin >> Student_Id;
    cout<<"Enter Name : ";
    getline(cin, Name);
    cout<<"Enter Class : ";
    cin>>cls;
    cout<<"Enter Stream : ";
    cin >> Stream;
    cout<<"Enter Subjects you want to study :\n";
    cin >> sub;
}

void Student::Display()
{ 
    cout<<"Student Id : "<<Student_Id<<"\nName : "<<Name
    <<"\nClass : "<<cls<<"\nStream : "<<Stream
    <<"\nSubjects : "<<sub;
}

void Input()
{ 
    system(CLEAR_SCREEN);
    Student S;
    ofstream outf("sdetail.dat",ios::binary|ios::app);
    char ch='Y';
    if(!outf.is_open())
    { 
        cout<<"File does not exist.";
        cin.get();
        return;
    }
    while(ch=='Y')
    { 
        S.Entry();
        outf.write((char*)&S,sizeof(S));
        cout<<"\n\nDo you want to enter more records : ";
        cin>>ch;
        ch=toupper(ch);
    }
    outf.close();
}

void Output()
{ 
    system(CLEAR_SCREEN);
    Student S;
    ifstream inf("sdetail.dat",ios::binary);
    if(!inf.is_open())
    { 
        cout<<"\n\n\t\t\tError!! File not found";
        cin.get();
        return;
    }
    while(inf.read((char*)&S,sizeof(S)))
    { 
        S.Display();
        cout<<"\n\n";
        cin.get();
    }
    inf.close();
    cin.get();
}

void search_id()
{ 
    system(CLEAR_SCREEN);
    Student S;
    char found='f';
    string sid;
    cout<<"Enter Student ID you want to search : ";
    cin >> sid;
    ifstream inf("sdetail.dat",ios::binary);
    while(inf.read((char*)&S,sizeof(S)))
    {
        if(sid == S.return_id())
        {
            S.Display();
            found='t';
            break;
        }
    }
    inf.close();
    if(found=='f')
	cout << "\n\nStudent ID not found.!!!";
    cin.get();
}

void search_name()
{
    system(CLEAR_SCREEN);
    Student S;
    char found='f';
    string sname;
    cout<<"Enter Student Name you want to search : ";
    getline(cin, sname);
    ifstream inf("sdetail.dat",ios::binary);
    while(inf.read((char*)&S,sizeof(S)))
    { 
        if(sname == S.return_name())
        { 
            S.Display();
            found='t';
            break;
        }
    }
    inf.close();
    if(found=='f')
	    cout<<"\n\nStudent Name not found.!!!";
    cin.get();
}

void modify_id()
{
    system(CLEAR_SCREEN);
    Student S;
    char ch,mod='f';
    string sid;
    fstream file("sdetail.dat",ios::binary|ios::in|ios::out|ios::ate);
    if(!file.is_open())
    {
        cout<<"\n\n\t\t\tError!! File not found";
        cin.get();
        return;
    }
    cout<<"Enter the Student ID to modify : ";
    cin>>sid;
    file.seekp(0,ios::beg);
    while(file.read((char*)&S,sizeof(S)))
    { 
        if(sid == S.return_id())
        { 
            S.Display();
            cout<<"\n\nConfirm the record (Y/N) : ";
            cin>>ch;
            ch=toupper(ch);
            if(ch=='Y')
            { 
                system(CLEAR_SCREEN);
                S.Entry();
                auto x=-sizeof(S);
                file.seekp(x,ios::cur);
                file.write((char*)&S,sizeof(S));
                mod='t';
                break;
            }
        }
    }
    if(mod=='t')
	    cout<<"\n\n\nData Modified ";
    if(mod=='f')
	    cout<<"\n\n\nData not found.";
    file.close();
    cin.get();
}

void modify_name()
{
    system(CLEAR_SCREEN);
    Student S;
    char ch,mod='f';
    string sname;
    fstream file("sdetail.dat",ios::binary|ios::in|ios::out|ios::ate);
    if(!file.is_open())
    {
        cout<<"\n\n\t\t\tError!! File not found";
	    cin.get();
	    return;
    }
    cout<<"Enter the Student Name to modify : ";
    getline(cin, sname);
    file.seekp(0,ios::beg);
    while(file.read((char*)&S,sizeof(S)))
    {
        if(sname == S.return_name())
        {
            S.Display();
            cout<<"\n\nConfirm the record (Y/N) : ";
            cin>>ch;
            ch=toupper(ch);
            if(ch=='Y')
            {
                system(CLEAR_SCREEN);
                S.Entry();
                auto x=-sizeof(S);
                file.seekp(x,ios::cur);
                file.write((char*)&S,sizeof(S));
                mod='t';
                break;
            }
        }
    }
    if(mod=='t')
	    cout<<"\n\n\nData Modified ";
    if(mod=='f')
	    cout<<"\n\n\nData not found.";
    file.close();
    cin.get();
}

void Sdelete()
{
    system(CLEAR_SCREEN);
    char ch,found='f';
    string sname, sid;
    Student S;
    cout<<"Enter Name of Student : ";
    getline(cin, sname);
    cout<<"Enter ID of Student : ";
    cin>>sid;
    ofstream fout("temp.dat",ios::binary);
    ifstream fin("sdetail.dat",ios::binary);
    while(fin.read((char*)&S,sizeof(S)))
    {
        if(sid == S.return_id() && sname == S.return_name())
        {
            S.Display();
            found='t';
            cout<<"\n\nConfirm Record (Y/N) : ";
            cin>>ch;
            ch=toupper(ch);
            if(ch=='Y')
            {
                cout<<"\n\n\nRecord Deleted...";
                cin.get();
            }
            if(ch=='N')
                fout.write((char*)&S,sizeof(S));
        }
        else
            fout.write((char*)&S,sizeof(S));
    }
    if(found=='f')
    {
        cout<<"\n\n\nRecord not found...";
        cin.get();
    }
    fout.close();
    fin.close();
    remove("sdetail.dat");
    rename("temp.dat","sdetail.dat");
}

void Modify_Menu()
{
    char mm;
    do
    {
        system(CLEAR_SCREEN);
        cout<<"\n\n1. Modify by Name."
        <<"\n2. Modify by ID."
        <<"\n3. Return to previous Menu."
        <<"\n\nEnter your choice : ";
        cin>>mm;
        
        if(mm=='1')
            modify_name();
        else if(mm=='2')
            modify_id();
        else if(mm=='3')
        {
            cout<<"\n\nReturning to previous menu...";
            cin.get();
        }
        else
        {
            cout<<"\n\nWrong value entered...";
            cin.get();
        }
    } while(mm!='3');
}

void Search_Menu()
{
    char sm;
    do
    {
        system(CLEAR_SCREEN);
        cout<<"\n\n1. Search Student by Name."
        <<"\n2. Search Student by ID."
        <<"\n3. Return to previous menu."
        <<"\n\nEnter your choice : ";
        cin>>sm;
        
        if(sm=='1')
            search_name();
        else if(sm=='2')
            search_id();
        else if(sm=='3')
        {
            cout<<"\n\nReturning to previous menu...";
            cin.get();
        }
        else
        {
            cout<<"\n\nWrong value entered...";
            cin.get();
        }
    } while(sm!='3');
}

void Student_Menu()
{
    char sm;
    do
    {
        system(CLEAR_SCREEN);
        cout<<"\n\n1. Enter data of Student."
        <<"\n2. Display data of Student."
        <<"\n3. Search a Student."
        <<"\n4. Modify the details of a Student."
        <<"\n5. Delete record."
        <<"\n6. Exit."
        <<"\n\nEnter your choice : ";
        cin>>sm;

        if(sm=='1')
            Input();
        else if(sm=='2')
            Output();
        else if(sm=='3')
            Search_Menu();
        else if(sm=='4')
            Modify_Menu();
        else if(sm=='5')
            Sdelete();
        else if(sm=='6')
        {
            cout<<"\n\nReturning to main menu...";
            cin.get();
        }
        else
        {
            cout<<"\n\nWrong value entered.";
            cin.get();
        }
    } while(sm != '6');
}

//***************************TEACHER SECTION*****************************

class Teacher
{
    public :
        int i;
        string TName,subject,Teacher_Id;
        void TEntry();
        void TDisplay();
        string return_tid()
        {
            return Teacher_Id;
        }
        string return_tsubject()
        {
            return subject;
        }
};

void Teacher::TEntry()
{
    system(CLEAR_SCREEN);
    cout<<"Enter Teacher Id : ";
    cin>>Teacher_Id;
    cout<<"Enter Name : ";
    getline(cin, TName);
    cout<<"Enter Subject you teach : ";
    cin >> subject;
}

void Teacher::TDisplay()
{
    cout<<"\nTeacher Id : "<<Teacher_Id
    <<"\nName : "<<TName
    <<"\nSubject : "<<subject;
}

void TInput()
{
    system(CLEAR_SCREEN);
    Teacher T;
    ofstream outf("tdetail.dat",ios::binary|ios::app);
    if(!outf.is_open())
    {
        cout<<"\n\n\t\t\tError!! File not found";
	    cin.get();
	    return;
    }
    char ch='Y';
    while(ch=='Y')
    {
        T.TEntry();
        outf.write((char*)&T,sizeof(T));
        cout<<"\n\nDo you want to enter more records : ";
        cin>>ch;
        ch=toupper(ch);
    }
    outf.close();
}

void TOutput()
{
    system(CLEAR_SCREEN);
    Teacher T;
    ifstream inf("tdetail.dat",ios::binary);
    if(!inf.is_open())
    {
        cout<<"\n\n\t\t\tError!! File not found";
        cin.get();
        return;
    }
    while(inf.read((char*)&T,sizeof(T)))
    {
        T.TDisplay();
        cout<<"\n\n";
        cin.get();
    }
    inf.close();
    cin.get();
}

void Tsearch_id()
{
    system(CLEAR_SCREEN);
    Teacher T;
    char found='f';
    string tid;
    cout<<"Enter Teacher ID you want to search : ";
    cin>>tid;
    ifstream inf("tdetail.dat",ios::binary);
    while(inf.read((char*)&T,sizeof(T)))
    {
        if(tid == T.return_tid())
        {
            T.TDisplay();
            found='t';
            break;
        }
    }
    inf.close();
    if(found=='f')
	cout<<"\n\nTeacher ID not found.!!!";
    cin.get();
}

void Tsearch_subject()
{
    system(CLEAR_SCREEN);
    Teacher T;
    char found='f';
    string tsub;
    cout<<"Enter Teacher ID you want to search : ";
    cin >> tsub;
    ifstream inf("tdetail.dat",ios::binary);
    while(inf.read((char*)&T,sizeof(T)))
    { 
        if(tsub == T.return_tsubject())
        {
            T.TDisplay();
            found='t';
            break;
        }
    }
    inf.close();
    if(found == 'f')
	    cout<<"\n\nSubject not found.!!!";
  cin.get();
}

void Tmodify_id()
{
    system(CLEAR_SCREEN);
    Teacher T;
    char ch;
    string tid;
    fstream file("tdetail.dat",ios::binary|ios::in|ios::out|ios::ate);
    if(!file.is_open())
    {
        cout<<"\n\n\t\t\tError!! File not found";
	    cin.get();
	    return;
    }
    cout<<"Enter the Teacher ID to modify : ";
    cin>>tid;
    file.seekp(0,ios::beg);
    while(file.read((char*)&T,sizeof(T)))
    {
        if(tid == T.return_tid())
        {
            T.TDisplay();
            cout<<"\n\nConfirm the record : ";
            cin>>ch;
            if(ch=='y' || ch=='Y')
            {
                system(CLEAR_SCREEN);
                T.TEntry();
                auto x=-sizeof(T);
                file.seekp(x,ios::cur);
                file.write((char*)&T,sizeof(T));
                break;
            }
        }
    }
    cout<<"\n\n\nData Modified ";
    file.close();
    cin.get();
}

void Tmodify_subject()
{
    system(CLEAR_SCREEN);
    Teacher T;
    char ch;
    string tsub;
    fstream file("tdetail.dat",ios::binary|ios::in|ios::out|ios::ate);
    if(!file.is_open())
    {
        cout<<"\n\n\t\t\tError!! File not found";
	    cin.get();
	    return;
    }
    cout<<"Enter the Teacher Subject to modify : ";
    cin >> tsub;
    file.seekp(0,ios::beg);
    while(file.read((char*)&T,sizeof(T)))
    {
        if(tsub == T.return_tsubject())
	    {
            T.TDisplay();
            cout<<"\n\nConfirm the record : ";
            cin>>ch;
            if(ch=='y' || ch=='Y')
            {
                system(CLEAR_SCREEN);
                T.TEntry();
                auto x=-sizeof(T);
                file.seekp(x,ios::cur);
                file.write((char*)&T,sizeof(T));
                break;
            }
	    }
    }
    cout<<"\n\n\nData Modified ";
    file.close();
    cin.get();
}

void Tdelete()
{
    system(CLEAR_SCREEN);
    char found='f',ch;
    string tsub, tid;
    Teacher T;
    cout<<"Enter Subject of the Teacher : ";
    cin >> tsub;
    cout<<"Enter ID of Teacher : ";
    cin>>tid;
    ofstream fout("temp.dat",ios::binary);
    ifstream fin("tdetail.dat",ios::binary);
    while(fin.read((char*)&T,sizeof(T)))
    { 
        if(tid == T.return_tid() && tsub == T.return_tsubject())
        { 
            T.TDisplay();
            found='t';
            cout<<"\n\nConfirm Record (Y/N) : ";
            cin>>ch;
            ch=toupper(ch);
            if(ch=='Y')
            {
                cout<<"\n\n\nRecord Deleted...";
                cin.get();
            }
            if(ch=='N')
            fout.write((char*)&T,sizeof(T));
        }
        else
            fout.write((char*)&T,sizeof(T));
    }
    if(found=='f')
    cout<<"\n\n\nRecord not found...";
    fout.close();
    fin.close();
    remove("tdetail.dat");
    rename("temp.dat","tdetail.dat");
}

void TModify_Menu()
{
    char mm;
    do
    {
        system(CLEAR_SCREEN);
        cout<<"\n\n1. Modify by Subject."
        <<"\n2. Modify by ID."
        <<"\n3. Return to previous Menu."
        <<"\n\nEnter your choice : ";
        cin>>mm;
        if(mm=='1')
            Tmodify_subject();
        else if(mm=='2')
            Tmodify_id();
        else if(mm=='3')
        {
            cout<<"\n\nReturning to previous menu...";
            cin.get();
        }
        else
        {
            cout<<"\n\nWrong value entered...";
            cin.get();
        }
    } while(mm!='3');
}

void TSearch_Menu()
{
    char sm;
    do
    {
        system(CLEAR_SCREEN);
        cout<<"\n\n1. Search Teacher by Subject."
        <<"\n2. Search Teacher by ID."
        <<"\n3. Return to previous menu."
        <<"\n\nEnter your choice : ";
        cin>>sm;
        if(sm=='1')
            Tsearch_subject();
        else if(sm=='2')
            Tsearch_id();
        else if(sm=='3')
        {
            cout<<"\n\nExiting to previous menu...";
            cin.get();
        }
        else
        {
            cout<<"\n\nWrong value entered...";
            cin.get();
        }
    } while(sm!='3');
}

void Teacher_Menu()
{
    char tm;
    do
    {
        system(CLEAR_SCREEN);
        cout<<"\n\n1. Enter data of Teacher."
        <<"\n2. Display data of Teacher."
        <<"\n3. Search a Teacher."
        <<"\n4. Modify the details of a Teacher."
        <<"\n5. Delete Record."
        <<"\n6. Exit."
        <<"\n\nEnter your choice : ";
        cin>>tm;
        if(tm=='1')
            TInput();
        else if(tm=='2')
            TOutput();
        else if(tm=='3')
            TSearch_Menu();
        else if(tm=='4')
            TModify_Menu();
        else if(tm=='5')
            Tdelete();
        else if(tm=='6')
        {
            cout<<"\n\nReturning to main menu...";
            cin.get();
        }
        else
        {
            cout<<"\n\nWrong value entered.";
            cin.get();
        }
    } while(tm!='6');
}

//*******************************ABOUT US*************************************

void About()
{
    system(CLEAR_SCREEN);
        cout<<"\n*************************RAWAT BROS CHARITABLE INSTITUTE************************"
        <<"\n\nRawat Bros Charitable Institute (RBCI) is a not for profit charity Institute "
        <<"\nas a part of Rawat Bros Pvt. Ltd. Charity Program. Millions of children who "
        <<"\ndream big but are pulled aback by their circumstancesare invited and given "
        <<"\nassistance to achive their goal. RBCI, started in 2012 as a small institute in "
        <<"\nNew Delhi with a small staff is now prospering with 15 centres across India."
        <<"\nMany well known techers in their field give free classes in some of our"
        <<"\nInstitutes. We believe that education is must for all and no one should be"
        <<"\ndeprived of it. We belive in giving equal oppurtunity to everyone to"
        <<"\nfulfill their dream."
        <<"\n\n    This Delhi branch was the first branch in the chain and is the most"
        <<"\nof all branches. For more information contact us."
        <<"\n\n\n\n\n\n\n\t\t\t\t\t\tEmail : rbci.delhi@gmail.com"
        <<"\n\t\t\t\t\t\tContact : 011-99999999";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

//******************************DONATION**************************************

class Donate
{
        string Dname;
        int Donation_Amount,DID;
    public:
        int ret_id()
        {
            return DID;
        }
        string ret_name()
        {
            return Dname;
        }
        void DEntry();
        void DDisplay();
};

void Donate::DEntry()
{
    system(CLEAR_SCREEN);
    cout<<"\n\nEnter Donor ID : ";
    cin>>DID;
    cout<<"Enter your Name : ";
    getline(cin, Dname);
    cout<<"Enter amount you want to donate : ";
    cin>>Donation_Amount;
}

void Donate::DDisplay()
{
    cout<<"\nDonar ID : "<<DID<<"\nName : "<<Dname<<"\nAmount Donated : "<<Donation_Amount;
}

void DInput()
{
    system(CLEAR_SCREEN);
    Donate D;
    ofstream outf("ddetail.dat",ios::binary|ios::app);
    if(!outf.is_open())
    {
        cout<<"\n\n\t\t\tError!! File not found";
        cin.get();
        return;
    }
    D.DEntry();
    outf.write((char*)&D,sizeof(D));
    cout<<"\n\n\nThank you so much for your support.";
    outf.close();
    cin.get();
}

void DOutput()
{
    system(CLEAR_SCREEN);
    Donate D;
    ifstream inf("ddetail.dat",ios::binary);
    if(!inf.is_open())
    {
        cout<<"\n\n\t\t\tError!! File not found";
        cin.get();
        return;
    }
    while(inf.read((char*)&D,sizeof(D)))
    {
        D.DDisplay();
        cout<<"\n\n";
        cin.get();
    }
    inf.close();
    cin.get();
}

void Dsearch()
{
    system(CLEAR_SCREEN);
    Donate D;
    char found='f';
    int id;
        cout<<"Enter ID of Donor you want to search : ";
        cin>>id;
        ifstream inf("ddetail.dat",ios::binary);
        while(inf.read((char*)&D,sizeof(D)))
        {
            if(D.ret_id() == id)
            {
                D.DDisplay();
                found='t';
                break;
            }
        }
        inf.close();
        if(found=='f')
        cout<<"\n\nDonor ID not found.!!!";
    cin.get();
}

void Donation_Menu()
{
    char dm;
    do
    {
        system(CLEAR_SCREEN);
        cout<<"\n\n1. Donate."
        <<"\n2. Donation Details."
        <<"\n3. Search donor"
        <<"\n4. Exit."
        <<"\n\nEnter your choice : ";
        cin>>dm;
            
        if(dm=='1')
            DInput();
        else if(dm=='2')
            DOutput();
        else if(dm=='3')
            Dsearch();
        else if(dm=='4')
        {
            cout<<"\n\nReturning to main menu...";
            cin.get();
        }
        else
        {
            cout<<"\n\nWrong value entered.";
            cin.get();
        }
    } while(dm!='4');
}

//******************************MAIN**************************************

int main()
{
    string pass;
    char ch;
    cout << "Enter Password : ";
    cin >> pass;
    if(pass == "1234")
    { 
        cout<<"\n\n\nAccess Granted...";
	    cin.get();
        do
        {
            system(CLEAR_SCREEN);
            cout<<"\n\t\tWelcome to Rawat Bros Charitable Institute"
            <<"\n1. About the Institute."
            <<"\n2. Student."
            <<"\n3. Teacher."
            <<"\n4. Support Us."
            <<"\n5. Exit."
            <<"\n\nEnter choice : ";
            cin >> ch;
            if(ch=='1')
                About();
            else if(ch=='2')
                Student_Menu();
            else if(ch=='3')
                Teacher_Menu();
            else if(ch=='4')
                Donation_Menu();
            else if(ch=='5')
            {
                cout<<"\n\n\n\tExiting !!!...";
                cin.get();
            }
            else
            {
                cout<<"\n\n\nEnter valid choice !!!...";
                cin.get();
            }
        } while(ch != '5');
    }
    else
    {
        cout<<"\n\n\nAccess Aborted...";
        cin.get();
    }
    cin.get();
    return 0;
}