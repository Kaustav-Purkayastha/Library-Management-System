/*
Project :- Library-Management-System
Made By :- Kaustav Purkayastha
*/
#include<iostream>
#include<conio.h>
#include<fstream>
#include<iomanip>
#include<stdlib.h>

using namespace std;
int Display1();                                                            
//Displaying menu and using arrow keys (function)
class Book
{       int Book_id;
  		char Book_Name[30];
  		char Author_Name[30];
  		float Book_price;
  		int Number_of_Books_Aviailable;
		int membercode[10]={0,0,0,0,0,0,0,0,0,0};
        int ans = 0;
		int temp;                                                     //temp variable
    public :
        Book()                                                              // constructor
        {
            Book_id=0;
            Book_price=0;
        }
        void Newbook()                                                      // for adding a new book to the system
        {   system("cls");
            ans=0;
            int tempBid;
            ReBid :
            cout.width(30); cout<< left <<"\n\tEnter Book id : ";
            cin>>Book_id;
            tempBid=Book_id;
            if(Bookidavailable(Book_id)==1)
            {
                cout<<"\n\tBook id TAKEN\n\tUse another id"<<endl;
                goto ReBid;
            }
            else
            {
            Book_id=tempBid;
            cout.width(30); cout<< left <<"\n\tEnter Book name : ";
            cin.ignore();
            cin.getline(Book_Name,30);
            cout.width(30); cout<< left <<"\n\tEnter Author Name : ";
            cin.ignore(0,'\n');
            cin.getline(Author_Name,30);
            cout.width(30); cout<< left <<"\n\tEnter Book price : ";
            cin>>Book_price;
            cout.width(30); cout<< left <<"\n\tEnter Books Available : ";
            cin>>Number_of_Books_Aviailable;
            storebook();
            }                                                     // for storing the variables in the file
        }
        void bookdata()                                                      // to show all the data about the book
        {
            cout.width(30); cout<< left <<"\n\tBook id : "<<Book_id;
            cout.width(30); cout<< left <<"\n\tBook name : "<<Book_Name;
            cout.width(30); cout<< left <<"\n\tAuthor Name : "<<Author_Name;
            cout.width(30); cout<< left <<"\n\tBook price : "<<Book_price;
            cout.width(30); cout<< left <<"\n\tBooks Available : "<<Number_of_Books_Aviailable<<endl;
        }
        void Booklist()                                                       // To show all the books stored in the file
        {
            system("CLS");
            ifstream fin;
            fin.open("Allbook.dat",ios::in|ios::binary);
            if(!fin){
              cout.width(25); cout<< left <<"\n\tNo Book are stored";
              cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
              getch();
            }
            else
            {
                fin.read((char*)this,sizeof(*this));                         //Reading data from the file
                while(!fin.eof())
                {
                    bookdata();                                              // displaying data
                    fin.read((char*)this,sizeof(*this));
                }
                fin.close();
                cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                getch();
            }
        }
        void storebook()                                                     // for storing the Book data into the file
        {
            if(Book_id==0&&Book_price==0){                                   // if the Book data is not enter
               cout.width(25); cout<< left <<"\n\tBook has no data";
               cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
               getch();
            }
            else{
            ofstream fout;
            fout.open("Allbook.dat",ios::app|ios::binary|ios::out);
            fout.write((char*)this,sizeof(*this));                            // writing all the Book data to the file
            fout.close();
            cout.width(25); cout<< left <<"\n\tBook Added Successfully";
            cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
            getch();
            }
        }
        void Edit_Book(int t)                                                   // Editing the book data
        {
            fstream f;
            int flag=0;
            f.open("Allbook.dat",ios::in|ios::out|ios::ate|ios::binary);
            f.seekg(0);
            f.read((char*)this,sizeof(*this));
            while(!f.eof())
            {
                if(t==Book_id)
                {   bookdata();
                    cout.width(30); cout<< left <<"\n\tEnter Book name : ";
                    cin.ignore();
                    cin.getline(Book_Name,30);
                    cout.width(30); cout<< left <<"\n\tEnter Author Name : ";
                    cin.ignore(0,'\n');
                    cin.getline(Author_Name,30);
                    cout.width(30); cout<< left <<"\n\tEnter Book price : ";
                    cin>>Book_price;
                    cout.width(30); cout<< left <<"\n\tEnter Books Available : ";
                    cin>>Number_of_Books_Aviailable;
                    f.seekp(f.tellp()-sizeof(*this));                                    // going to the front of the object to update
                    f.write((char*)this,sizeof(*this));
                    flag=1;
                    cout.width(30); cout<< left <<"\n\tEdit Successful.";
                    break;
                }
                else {flag = 0;}
            f.read((char*)this,sizeof(*this));
            }
            f.close();
            if(flag==0)
                 {
                 cout.width(30); cout<< left<<"\n\tNo such book is stored";
                 cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                 getch();
                 }

        }
        int Bookidavailable(int tbi)                                                      // to check if the book id is available
        {
             int flag=0;
             ifstream fin;
             fin.open("Allbook.dat",ios::in|ios::binary);
             if(!fin){}
            else
               {
                fin.read((char*)this,sizeof(*this));
                while(!fin.eof())
                {
                    if(tbi==Book_id)
                    {
                        flag=1;
                        break;
                    }
                    fin.read((char*)this,sizeof(*this));
                }
                fin.close();
            }
            if(flag==1)
                return 1;                        // if book id is present
            else
                return 0;                        // book id is not present
        }
        int getMembercode(int temp1,int B_id)    // for getting the code who issued this book
        {
            system("CLS");
            fstream f;
            int flag=0;
            f.open("Allbook.dat",ios::in|ios::out|ios::ate|ios::binary);
            f.seekg(0);
            f.read((char*)this,sizeof(*this));
            while(!f.eof())
            {
                if(B_id==Book_id)
                 {if(Number_of_Books_Aviailable>0)
                   {if(membercode[0]==0)
                    {   Number_of_Books_Aviailable--;
                        membercode[0]=temp1;
                        flag=1;
                    }
                    else if(membercode[1]==0)
                    {
                        Number_of_Books_Aviailable--;
                        membercode[1]=temp1;
                        flag=1;
                    }
                    else if(membercode[2]==0)
                    {
                        Number_of_Books_Aviailable--;
                        membercode[2]=temp1;
                        flag=1;
                    }
                    else if(membercode[3]==0)
                    {
                        Number_of_Books_Aviailable--;
                        membercode[3]=temp1;
                        flag=1;
                    }
                    else if(membercode[4]==0)
                    {
                        Number_of_Books_Aviailable--;
                        membercode[4]=temp1;
                        flag=1;
                    }
                    else if(membercode[5]==0)
                    {
                        Number_of_Books_Aviailable--;
                        membercode[5]=temp1;
                        flag=1;
                    }
                    else if(membercode[6]==0)
                    {
                        Number_of_Books_Aviailable--;
                        membercode[6]=temp1;
                        flag=1;
                    }
                    else if(membercode[7]==0)
                    {
                        Number_of_Books_Aviailable--;
                        membercode[7]=temp1;
                        flag=1;
                    }
                    else if(membercode[8]==0)
                    {
                        Number_of_Books_Aviailable--;
                        membercode[8]=temp1;
                        flag=1;
                    }
                    else if(membercode[9]==0)
                    {
                        Number_of_Books_Aviailable--;
                        membercode[9]=temp1;
                        flag=1;
                    }
                    else
                    {
                         cout.width(30); cout<< left <<"\n\tThis Book is not available";
                         cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                         getch();
                         flag=0;
                         break;
                    }
                    f.seekp(f.tellp()-sizeof(*this));
                    f.write((char*)this,sizeof(*this));
                    flag=1;
                    }
                else
                    {
                    cout.width(30); cout<< left <<"\n\tNo Book Are available to be issued";
                    cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                    getch();
                    break;
                    }
                }
                f.read((char*)this,sizeof(*this));
            }
            f.close();
            if(flag==0)
                {
                    cout.width(30); cout<< left <<"\n\tNo such book is stored";
                    cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                    return 0;
                    getch();
                }
                else if(flag==1)
                {
                    return 1;
                }

        }
        void returnedbook(int tempMCode,int tempBid)                // change to default by returning the book
        {
             system("CLS");
            fstream f;
            int flag=0,i;
            f.open("Allbook.dat",ios::in|ios::out|ios::ate|ios::binary);
            f.seekg(0);
            f.read((char*)this,sizeof(*this));
            while(!f.eof())
            {
                if(tempBid==Book_id)
                {
                    for(i=0;i<10;i++)
                    {
                        if(membercode[i]==tempMCode)
                        {
                            membercode[i]=0;
                            Number_of_Books_Aviailable++;
                            break;
                        }
                    }
                    f.seekp(f.tellp()-sizeof(*this));
                    f.write((char*)this,sizeof(*this));
                    flag=1;
                    break;
                }
                f.read((char*)this,sizeof(*this));
            }
            f.close();
            if(flag==0)
            {
                cout.width(30); cout<< left <<"\n\tNo such book is stored";
                cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                getch();
            }

        }
        void EnqureBook()                                        // Enquire of book
        {
            system("cls");
            int Tbid;
            cout.width(25); cout<< left <<"\n\tEnter book id you want to enquire : ";
            cin>>Tbid;
            if(Bookidavailable(Tbid)==1)
            {
            ifstream fin;
            fin.open("Allbook.dat",ios::in|ios::binary);
            if(!fin){
              cout.width(25); cout<< left <<"\n\tNo Book are stored";
              cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
              getch();
            }
            else
            {
                fin.read((char*)this,sizeof(*this));
                while(!fin.eof())
                {
                    if(Book_id==Tbid)
                    {
                      bookdata();
                      Memberissuedlist(Tbid);
                      break;
                    }
                    fin.read((char*)this,sizeof(*this));
                }
                fin.close();
                cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                getch();
            }
            }
            else
            { cout.width(25); cout<< left <<"\n\tWrong book id"; }
        }
        void Memberissuedlist(int Tbid)                         // List of all the member code who issued the book
        {
            ifstream fin;
            fin.open("Allbook.dat",ios::in|ios::binary);
            if(!fin){
              cout.width(25); cout<< left <<"\n\tNo Book are stored";
              cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
              getch();
            }
            else
            {
                fin.read((char*)this,sizeof(*this));
                while(!fin.eof())
                {
                    if(Book_id==Tbid)
                    {
                       for(int i=0;i<10;i++)
                       {    if(membercode[i]!=0)
                              {
                                 cout<<"\n\tBook issued by the Member id : "<<membercode[i];
                              }
                       }
                       break;
                    }
                    fin.read((char*)this,sizeof(*this));
                }
                fin.close();
        }
        }
}B;
class Member : public Book
{
      int Member_Code;
	  char Member_Name[21];
	  char Member_Phone[11];
	  char Member_Address[31];
	  int Book_Code[5]={0,0,0,0,0};
	  int DD[5],MM[5],YY[5];
	  int ans;
  public :
        Member()
        {
          Member_Code=0;
        }
        void Newmember()
        {
        system("CLS");
        int tempMc;
        ReMC :
        cout.width(25); cout<< left <<"\n\tEnter Member code    :";
        cin>>Member_Code;
        tempMc=Member_Code;
            if(Membercodeavailable(Member_Code)==1)
            {
                cout<<"\n\tMember code TAKEN\n\tUse another code"<<endl;
                goto ReMC;
            }
            else
            {   Member_Code = tempMc;
                cout.width(25); cout<< left <<"\n\tEnter Member Name    :";
                cin.ignore();
                cin.getline(Member_Name,21);
                cout.width(25); cout<< left <<"\n\tEnter Member Phone   :";
                cin.ignore(0,'\n');
                cin.getline(Member_Phone,11);
                cout.width(25); cout<< left <<"\n\tEnter Member Address :";
                cin.ignore(0,'\n');
                cin.getline(Member_Address,31);
                storeMember();
            }
      }
        void memberdata()
        {   int flag=0;
            cout.width(25); cout<< left <<"\n\tMember code    : "<<Member_Code;
            cout.width(25); cout<< left <<"\n\tMember Name    : "<<Member_Name;
            cout.width(25); cout<< left <<"\n\tMember Phone   : "<<Member_Phone;
            cout.width(25); cout<< left <<"\n\tMember Address : "<<Member_Address;
            cout<<endl<<endl;
        }
        void Memberlist()
        {    system("CLS");
            ifstream fin;
            fin.open("Allmember.dat",ios::in|ios::binary);
            fin.seekg(0);
            if(!fin)
            {
              cout.width(25); cout<< left <<"\n\tNo Member are stored";
              cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
              getch();
            }
            else
            {
                fin.read((char*)this,sizeof(*this));
                while(!fin.eof())
                {
                    memberdata();
                    fin.read((char*)this,sizeof(*this));
                }
                fin.close();
                cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                getch();
            }
        }
        void storeMember()
        {     system("CLS");
            if(Member_Code==0){
               cout.width(25); cout<< left <<"\n\tBook has no data";
               cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
               getch();
            }
            else{
            ofstream fout;
            fout.open("Allmember.dat",ios::app|ios::binary);
            fout.write((char*)this,sizeof(*this));
            fout.close();
            cout.width(25); cout<< left <<"\n\tMember Added Successfully.";
            cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
            getch();
            }
        }
        void Edit_Member(int temp)
        {
            fstream f;
            int flag=0;
            f.open("Allmember.dat",ios::in|ios::out|ios::ate|ios::binary);
            f.seekg(0);
            f.read((char*)this,sizeof(*this));
            while(!f.eof())
            {
                if(temp==Member_Code)
                {   memberdata();
                    cout.width(25); cout<< left <<"\n\tEnter Member Name    :";
                    cin.ignore();
                    cin.getline(Member_Name,21);
                    cout.width(25); cout<< left <<"\n\tEnter Member Phone   :";
                    cin>>Member_Phone;
                    cout.width(25); cout<< left <<"\n\tEnter Member Address :";
                    cin.ignore();
                    cin.getline(Member_Address,21);
                    f.seekp(f.tellp()-sizeof(*this));
                    f.write((char*)this,sizeof(*this));
                    flag=1;
                    cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                    getch();
                    break;
                    }
                f.read((char*)this,sizeof(*this));
            }
            f.close();
            if(flag==0)
                {cout.width(25); cout<< left <<"\n\tNo such Member is stored";
                cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                getch();
                }
        }
        void issue(int temp,int Bookid)
            {
            int flag=0,ans1=0;
            fstream f;
                f.open("Allmember.dat",ios::in|ios::out|ios::ate|ios::binary);
                f.seekg(0);
                f.read((char*)this,sizeof(*this));
                while(!f.eof())
                {
                    if(Member_Code==temp)
                    {
                        if(Book_Code[0]==0)
                           {
                               ans1=B.getMembercode(Member_Code,Bookid);
                               if(ans1==1)
                               {
                                flag=1;
                                Book_Code[0]=Bookid;
                                cout<<"\n\tEnter date (DD/MM/YY):";
                                D:
                                cout<<"\n\tDD : ";
                                cin>>DD[0];
                                if(DD[0]<0||DD[0]>31)
                                {
                                    cout<<"\n\tThe date is incorrect\n\tEnter again!!";
                                    goto D;
                                }
                                M:
                                cout<<"\n\tMM : ";
                                cin>>MM[0];
                                if(MM[0]<0||MM[0]>12)
                                {
                                    cout<<"\n\tThe month is invalid\n\tEnter again!!";
                                    goto M;
                                }
                                if(MM[0]==2)
                                {
                                    if(DD[0]>29)
                                    {
                                        cout<<"\n\tFebruary can't have more than 29 days\n\tEnter Again!!";
                                        goto D;
                                    }
                                }
                                cout<<"\n\tYY : ";
                                cin>>YY[0];
                               }
                               else
                                flag=0;
                           }
                        else if(Book_Code[1]==0)
                           {
                               ans1=B.getMembercode(Member_Code,Bookid);
                               if(ans1==1)
                               {
                                   flag=1;
                                   Book_Code[1]=Bookid;
                                   cout<<"\n\tEnter date (DD/MM/YY):";
                                D1:
                                cout<<"\n\tDD : ";
                                cin>>DD[1];
                                if(DD[1]<0||DD[1]>31)
                                {
                                    cout<<"\n\tThe date is incorrect\n\tEnter again!!";
                                    goto D1;
                                }
                                M1:
                                cout<<"\n\tMM : ";
                                cin>>MM[1];
                                if(MM[1]<0||MM[1]>12)
                                {
                                    cout<<"\n\tThe month is invalid\n\tEnter again!!";
                                    goto M1;
                                }
                                if(MM[1]==2)
                                {
                                    if(DD[1]>29)
                                    {
                                        cout<<"\n\tFebruary can't have more than 29 days\n\tEnter Again!!";
                                        goto D1;
                                    }
                                }
                                cout<<"\n\tYY : ";
                                cin>>YY[1];
                               }
                               else
                                flag=0;
                           }
                           else if(Book_Code[2]==0)
                           {
                               B.getMembercode(Member_Code,Bookid);
                                if(ans1==1)
                                {
                                    flag=1;
                                    Book_Code[2]=Bookid;
                                    cout<<"\n\tEnter date (DD/MM/YY):";
                                D2:
                                cout<<"\n\tDD : ";
                                cin>>DD[2];
                                if(DD[2]<0||DD[2]>31)
                                {
                                    cout<<"\n\tThe date is incorrect\n\tEnter again!!";
                                    goto D2;
                                }
                                M2:
                                cout<<"\n\tMM : ";
                                cin>>MM[2];
                                if(MM[2]<0||MM[2]>12)
                                {
                                    cout<<"\n\tThe month is invalid\n\tEnter again!!";
                                    goto M2;
                                }
                                if(MM[2]==2)
                                {
                                    if(DD[2]>29)
                                    {
                                        cout<<"\n\tFebruary can't have more than 29 days\n\tEnter Again!!";
                                        goto D2;
                                    }
                                }
                                cout<<"\n\tYY : ";
                                cin>>YY[2];
                                }
                               else
                                flag=0;
                           }
                           else if(Book_Code[3]==0)
                           {
                               B.getMembercode(Member_Code,Bookid);
                               if(ans1==1)
                               {
                                    flag=1;
                                    Book_Code[3]=Bookid;
                                    cout<<"\n\tEnter date (DD/MM/YY):";
                                D3:
                                cout<<"\n\tDD : ";
                                cin>>DD[3];
                                if(DD[3]<0||DD[3]>31)
                                {
                                    cout<<"\n\tThe date is incorrect\n\tEnter again!!";
                                    goto D3;
                                }
                                M3:
                                cout<<"\n\tMM : ";
                                cin>>MM[3];
                                if(MM[3]<0||MM[3]>12)
                                {
                                    cout<<"\n\tThe month is invalid\n\tEnter again!!";
                                    goto M3;
                                }
                                if(MM[3]==2)
                                {
                                    if(DD[3]>29)
                                    {
                                        cout<<"\n\tFebruary can't have more than 29 days\n\tEnter Again!!";
                                        goto D3;
                                    }
                                }
                                cout<<"\n\tYY : ";
                                cin>>YY[3];
                               }
                               else
                                flag=0;
                           }
                           else if(Book_Code[4]==0)
                           {
                               B.getMembercode(Member_Code,Bookid);
                                if(ans1==1)
                                 {
                                     flag=1;
                                     Book_Code[4]=Bookid;
                                     cout<<"\n\tEnter date (DD/MM/YY):";
                                D4:
                                cout<<"\n\tDD : ";
                                cin>>DD[4];
                                if(DD[4]<0||DD[4]>31)
                                {
                                    cout<<"\n\tThe date is incorrect\n\tEnter again!!";
                                    goto D4;
                                }
                                M4:
                                cout<<"\n\tMM : ";
                                cin>>MM[4];
                                if(MM[4]<0||MM[4]>12)
                                {
                                    cout<<"\n\tThe month is invalid\n\tEnter again!!";
                                    goto M4;
                                }
                                if(MM[4]==2)
                                {
                                    if(DD[4]>29)
                                    {
                                        cout<<"\n\tFebruary can't have more than 29 days\n\tEnter Again!!";
                                        goto D4;
                                    }
                                }
                                cout<<"\n\tYY : ";
                                cin>>YY[4];
                                 }
                               else
                                flag=0;
                           }
                        else{
                            cout.width(25); cout<< left <<"\n\tYou already have issued 5 books";
                            cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                            getch();
                            flag=0;
                            break;
                            }
                        f.seekp(f.tellp()-sizeof(*this));
                        f.write((char*)this,sizeof(*this));
                        break;
                    }
                    f.read((char*)this,sizeof(*this));
                }
                f.close();
                if(flag==1)
                    {
                    cout.width(25); cout<< left <<"\n\tBook issued";
                    cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                    getch();
                    }
                else
                {
                    cout.width(25); cout<< left <<"\n\tBook not issued";
                    cout.width(25); cout<< left <<"\n\n\n\tPress Any Key to go to main Menu.";
                    getch();
                }
            }
        int Membercodeavailable(int temp)
        {
            int flag=0;
            ifstream fin;
            fin.open("Allmember.dat",ios::in|ios::binary);
             if(!fin)
            {
            }
            else
            {
                fin.read((char*)this,sizeof(*this));
                while(!fin.eof())
                {
                    if(temp==Member_Code)
                    {
                        flag=1;
                        break;
                    }
                    fin.read((char*)this,sizeof(*this));
                }
                fin.close();
            }
            if(flag==1)
                return 1;
            else
                return 0;
            }
        void returnbook(int temp,int bookid)
        {
            system("CLS");
            fstream f;
            int flag=0,ans1;
            f.open("Allmember.dat",ios::in|ios::out|ios::ate|ios::binary);
            f.seekg(0);
            f.read((char*)this,sizeof(*this));
            while(!f.eof())
            {
                if(Member_Code==temp)
                {
                    if(Book_Code[0]==0&&Book_Code[1]==0&&Book_Code[2]==0&&Book_Code[3]==0&&Book_Code[4]==0)
                    {
                        cout.width(25); cout<< left <<"\n\tThis member isn't issued a book"<<endl;
                        break;
                    }
                    else if(Book_Code[0]==bookid)
                    {
                        ans1=B.Bookidavailable(bookid);
                        if(ans1==1)
                        {
                            B.returnedbook(Member_Code,bookid);
                            Book_Code[0]=0;
                            flag=1;
                        }
                        else
                        {
                            flag=0;
                        }
                    }
                    else if(Book_Code[1]==bookid)
                    {
                        ans1=B.Bookidavailable(bookid);
                        if(ans1==1)
                        {
                            B.returnedbook(Member_Code,bookid);
                            Book_Code[1]=0;
                            flag=1;
                        }
                        else
                        {
                            flag=0;
                        }
                    }
                    else if(Book_Code[2]==bookid)
                    {
                        ans1=B.Bookidavailable(bookid);
                        if(ans1==1)
                        {
                            B.returnedbook(Member_Code,bookid);
                            Book_Code[2]=0;
                            flag=1;
                        }
                        else
                        {
                            flag=0;
                        }
                    }
                    else if(Book_Code[3]==bookid)
                    {
                        ans1=B.Bookidavailable(bookid);
                        if(ans1==1)
                        {
                            B.returnedbook(Member_Code,bookid);
                            Book_Code[3]=0;
                            flag=1;
                        }
                        else
                        {
                            flag=0;
                        }
                    }
                    else if(Book_Code[4]==bookid)
                    {
                        ans1=B.Bookidavailable(bookid);
                        if(ans1==1)
                        {
                            B.returnedbook(Member_Code,bookid);
                            Book_Code[4]=0;
                            flag=1;
                        }
                        else
                        {
                            flag=0;
                        }
                    }
                        f.seekp(f.tellp()-sizeof(*this));
                        f.write((char*)this,sizeof(*this));
                        break;
                    }
                f.read((char*)this,sizeof(*this));
            }
            f.close();
            if(flag==0)
                {
                    cout.width(25); cout<< left <<"\n\tNo Book is returned";
                    cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                    getch();
                }
            else if(flag==1)
            {
                cout.width(25); cout<< left <<"\n\tBook is returned";
                cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                getch();
            }
            else {}

        }
        void Bookissuedlist(int tempMcode)
        {
            ifstream fin;
            int i;
            fin.open("Allmember.dat",ios::in|ios::binary);
            if(!fin)
            {
              cout.width(25); cout<< left <<"\n\tNo Member are stored";
              cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
              getch();
            }
            else
            {
                fin.read((char*)this,sizeof(*this));
                while(!fin.eof())
                {
                    if(tempMcode==Member_Code)
                    {
                        for(i=0;i<5;i++)
                        {   if(Book_Code[i]!=0)
                            {
                            cout.width(25); cout<< left <<"\n\tBook issued "<<Book_Code[i]<<" At "<<DD[i]<<"-"<<MM[i]<<"-"<<YY[i];
                            }
                            else
                                continue;
                        }
                        break;
                    }
                    fin.read((char*)this,sizeof(*this));
                }
            }
                fin.close();
        }
        void EnqureMember()
        {
            system("cls");
            int TMc;
            cout.width(25); cout<< left <<"\n\tEnter Member code you want to enquire : ";
            cin>>TMc;
            if(Membercodeavailable(TMc)==1)
            {
            ifstream fin;
            fin.open("Allmember.dat",ios::in|ios::binary);
            if(!fin){
              cout.width(25); cout<< left <<"\n\tNo Member are stored";
              cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
              getch();
            }
            else
            {
                fin.read((char*)this,sizeof(*this));
                while(!fin.eof())
                {
                    if(Member_Code==TMc)
                    {
                      memberdata();
                      Bookissuedlist(TMc);
                      break;
                    }
                    fin.read((char*)this,sizeof(*this));
                }
                fin.close();
                cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                getch();
            }
            }
            else
            {cout.width(25); cout<< left <<"\n\tWrong Member Code !! ";}
        }
}M;

int main()
{
    system("color 3F");                                          // To change the color of the console
    int n,ans,ans1,ans2,temp,count1,Tbookid;
    do{
    system("CLS");                                               // Clear screen
    n=Display1();
	switch(n)
	{
	    case 1 : B.Newbook();
                    break;
	    case 2 : M.Newmember();
                    break;
	    case 3 : system("CLS");
                 cout.width(30); cout<< left <<"\n\tEnter Member code :";
                 cin>>temp;
                 ans=M.Membercodeavailable(temp);
                 if(ans==1)
                 {
                        cout.width(30); cout<< left <<"\n\tEnter book id for issue :";
                        cin>>Tbookid;
                        ans2=B.Bookidavailable(Tbookid);
                        if(ans2==1)
                        {
                            M.issue(temp,Tbookid);
                            break;
                        }
                        else
                        {
                            cout.width(30); cout<< left <<"\n\tWrong book id";
                            cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                            getch();
                            break;
                        }
                 }
                 else
                    {
                    cout.width(30); cout<< left <<"\n\tWrong Member code";
                    cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                    getch();
                    }
                    break;
	    case 4 : system("CLS");
                 cout.width(30); cout<< left <<"\n\tEnter Member code :";
                 cin>>temp;
                 ans=M.Membercodeavailable(temp);
                 if(ans==1)
                 {       M.Bookissuedlist(temp);
                        cout.width(30); cout<< left <<"\n\tEnter book id you want to return :";
                        cin>>ans1;
                        ans2=B.Bookidavailable(ans1);
                        if(ans2==1)
                        {
                            M.returnbook(temp,ans1);
                            break;
                        }
                        else
                        {
                            cout.width(30); cout<< left <<"\n\tWrong book id";
                            cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                            getch();
                            break;
                        }
                 }
                 else
                    {
                    cout.width(30); cout<< left <<"\n\tWrong Member code";
                    cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                    getch();
                    }
                 break;
	    case 5 : B.Booklist();
                    break;
	    case 6 : M.Memberlist();
                    break;
	    case 7 : system("CLS");
                 cout.width(25); cout<< left <<"\n\tEnter book id : ";
                 cin>>ans;
                 ans1=B.Bookidavailable(ans);
                 if(ans1==1)
                 B.Edit_Book(ans);
                 else {cout.width(30); cout<< left <<"\n\tYou Entered wrong book id ";}
                 cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                 getch();
	             break;
	    case 8 : system("CLS");
                 cout.width(25); cout<< left <<"\n\tEnter Member Code : ";
                 cin>>ans;
                 ans1 = M.Membercodeavailable(ans);
                 if(ans1 == 1)
                 { M.Edit_Member(ans); }
                 else {cout.width(30); cout<< left <<"\n\tYou Entered wrong member code ";}
                 cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                 getch();
                 break;
        case 9 : B.EnqureBook();
                 cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                 getch();
                 break;
        case 10 : M.EnqureMember();
                  cout.width(25); cout<< left <<"\n\n\tPress Any Key to go to main Menu.";
                  getch();
                  break;
	    case 11 : system("CLS");
                 cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
                 cout<<"\n\n\t\t\t\t\t\t  ****EXIT****"<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
                 break;
	    default : cout<<"\n\n\t\t\t\tInvalid Choice!"<<endl;
	}
    }while(n != 11);
    getch();
	return 0;
}
int Display1()              // To use arrow keys in the menu
{   int a=0,i=1;
    char c='>';
    cout<<"\n\n\t\t**********   WELCOME TO SIMPLE BOOKS LIBRARY SYSTEM  **********\n\n";
	cout<<"\n\t\t\t\t"<<c<<" Add new Books"<<endl;
	cout<<"\n\t\t\t\t Add new Members"<<endl;
	cout<<"\n\t\t\t\t Issue Book to a Member"<<endl;
	cout<<"\n\t\t\t\t Return Book from a Member"<<endl;
	cout<<"\n\t\t\t\t List all Books in the System"<<endl;
	cout<<"\n\t\t\t\t List all Members in the System"<<endl;
	cout<<"\n\t\t\t\t Edit Book"<<endl;
	cout<<"\n\t\t\t\t Edit Member"<<endl;
	cout<<"\n\t\t\t\t Enquire Book"<<endl;
	cout<<"\n\t\t\t\t Enquire Member"<<endl;
	cout<<"\n\t\t\t\t Quit from this System"<<endl;
	while(1)
    {
        a=getch();
        if(a==72)                                      // input code for UP Arrow key
        {
            i--;
        }
        else if(a==80)                                 // input code for DOWN Arrow key
        {
            i++;
        }
        else if(a==13)                                 // input code for Enter key
        {
            return i;
        }
        else
        {
         continue;
        }


        if(i<=0)                                       // To keep the value of i between 1 and 11
            i=1;
        else if(i>11)
            i=11;
        else;

        if(i==1)
        {
            system("cls");
            cout<<"\n\n\t\t**********   WELCOME TO SIMPLE BOOKS LIBRARY SYSTEM  **********\n\n";
            cout<<"\n\t\t\t\t"<<c<<" Add new Books"<<endl;
            cout<<"\n\t\t\t\t Add new Members"<<endl;
            cout<<"\n\t\t\t\t Issue Book to a Member"<<endl;
            cout<<"\n\t\t\t\t Return Book from a Member"<<endl;
            cout<<"\n\t\t\t\t List all Books in the System"<<endl;
            cout<<"\n\t\t\t\t List all Members in the System"<<endl;
            cout<<"\n\t\t\t\t Edit Book"<<endl;
            cout<<"\n\t\t\t\t Edit Member"<<endl;
            cout<<"\n\t\t\t\t Enquire Book"<<endl;
            cout<<"\n\t\t\t\t Enquire Member"<<endl;
            cout<<"\n\t\t\t\t Quit from this System"<<endl;
        }
        else if(i==2)
        {
            system("cls");
            cout<<"\n\n\t\t**********   WELCOME TO SIMPLE BOOKS LIBRARY SYSTEM  **********\n\n";
            cout<<"\n\t\t\t\t Add new Books"<<endl;
            cout<<"\n\t\t\t\t"<<c<<" Add new Members"<<endl;
            cout<<"\n\t\t\t\t Issue Book to a Member"<<endl;
            cout<<"\n\t\t\t\t Return Book from a Member"<<endl;
            cout<<"\n\t\t\t\t List all Books in the System"<<endl;
            cout<<"\n\t\t\t\t List all Members in the System"<<endl;
            cout<<"\n\t\t\t\t Edit Book"<<endl;
            cout<<"\n\t\t\t\t Edit Member"<<endl;
            cout<<"\n\t\t\t\t Enquire Book"<<endl;
            cout<<"\n\t\t\t\t Enquire Member"<<endl;
            cout<<"\n\t\t\t\t Quit from this System"<<endl;
        }
        else if(i==3)
        {
            system("cls");
            cout<<"\n\n\t\t**********   WELCOME TO SIMPLE BOOKS LIBRARY SYSTEM  **********\n\n";
            cout<<"\n\t\t\t\t Add new Books"<<endl;
            cout<<"\n\t\t\t\t Add new Members"<<endl;
            cout<<"\n\t\t\t\t"<<c<<" Issue Book to a Member"<<endl;
            cout<<"\n\t\t\t\t Return Book from a Member"<<endl;
            cout<<"\n\t\t\t\t List all Books in the System"<<endl;
            cout<<"\n\t\t\t\t List all Members in the System"<<endl;
            cout<<"\n\t\t\t\t Edit Book"<<endl;
            cout<<"\n\t\t\t\t Edit Member"<<endl;
            cout<<"\n\t\t\t\t Enquire Book"<<endl;
            cout<<"\n\t\t\t\t Enquire Member"<<endl;
            cout<<"\n\t\t\t\t Quit from this System"<<endl;
        }
        else if(i==4)
        {
            system("cls");
            cout<<"\n\n\t\t**********   WELCOME TO SIMPLE BOOKS LIBRARY SYSTEM  **********\n\n";
            cout<<"\n\t\t\t\t Add new Books"<<endl;
            cout<<"\n\t\t\t\t Add new Members"<<endl;
            cout<<"\n\t\t\t\t Issue Book to a Member"<<endl;
            cout<<"\n\t\t\t\t"<<c<<" Return Book from a Member"<<endl;
            cout<<"\n\t\t\t\t List all Books in the System"<<endl;
            cout<<"\n\t\t\t\t List all Members in the System"<<endl;
            cout<<"\n\t\t\t\t Edit Book"<<endl;
            cout<<"\n\t\t\t\t Edit Member"<<endl;
            cout<<"\n\t\t\t\t Enquire Book"<<endl;
            cout<<"\n\t\t\t\t Enquire Member"<<endl;
            cout<<"\n\t\t\t\t Quit from this System"<<endl;
        }
        else if(i==5)
        {
            system("cls");
            cout<<"\n\n\t\t**********   WELCOME TO SIMPLE BOOKS LIBRARY SYSTEM  **********\n\n";
            cout<<"\n\t\t\t\t Add new Books"<<endl;
            cout<<"\n\t\t\t\t Add new Members"<<endl;
            cout<<"\n\t\t\t\t Issue Book to a Member"<<endl;
            cout<<"\n\t\t\t\t Return Book from a Member"<<endl;
            cout<<"\n\t\t\t\t"<<c<<" List all Books in the System"<<endl;
            cout<<"\n\t\t\t\t List all Members in the System"<<endl;
            cout<<"\n\t\t\t\t Edit Book"<<endl;
            cout<<"\n\t\t\t\t Edit Member"<<endl;
            cout<<"\n\t\t\t\t Enquire Book"<<endl;
            cout<<"\n\t\t\t\t Enquire Member"<<endl;
            cout<<"\n\t\t\t\t Quit from this System"<<endl;
        }
        else if(i==6)
        {
            system("cls");
            cout<<"\n\n\t\t**********   WELCOME TO SIMPLE BOOKS LIBRARY SYSTEM  **********\n\n";
            cout<<"\n\t\t\t\t Add new Books"<<endl;
            cout<<"\n\t\t\t\t Add new Members"<<endl;
            cout<<"\n\t\t\t\t Issue Book to a Member"<<endl;
            cout<<"\n\t\t\t\t Return Book from a Member"<<endl;
            cout<<"\n\t\t\t\t List all Books in the System"<<endl;
            cout<<"\n\t\t\t\t"<<c<<" List all Members in the System"<<endl;
            cout<<"\n\t\t\t\t Edit Book"<<endl;
            cout<<"\n\t\t\t\t Edit Member"<<endl;
            cout<<"\n\t\t\t\t Enquire Book"<<endl;
            cout<<"\n\t\t\t\t Enquire Member"<<endl;
            cout<<"\n\t\t\t\t Quit from this System"<<endl;
        }
        else if(i==7)
        {
            system("cls");
            cout<<"\n\n\t\t**********   WELCOME TO SIMPLE BOOKS LIBRARY SYSTEM  **********\n\n";
            cout<<"\n\t\t\t\t Add new Books"<<endl;
            cout<<"\n\t\t\t\t Add new Members"<<endl;
            cout<<"\n\t\t\t\t Issue Book to a Member"<<endl;
            cout<<"\n\t\t\t\t Return Book from a Member"<<endl;
            cout<<"\n\t\t\t\t List all Books in the System"<<endl;
            cout<<"\n\t\t\t\t List all Members in the System"<<endl;
            cout<<"\n\t\t\t\t"<<c<<" Edit Book"<<endl;
            cout<<"\n\t\t\t\t Edit Member"<<endl;
            cout<<"\n\t\t\t\t Enquire Book"<<endl;
            cout<<"\n\t\t\t\t Enquire Member"<<endl;
            cout<<"\n\t\t\t\t Quit from this System"<<endl;
        }
        else if(i==8)
        {
            system("cls");
            cout<<"\n\n\t\t**********   WELCOME TO SIMPLE BOOKS LIBRARY SYSTEM  **********\n\n";
            cout<<"\n\t\t\t\t Add new Books"<<endl;
            cout<<"\n\t\t\t\t Add new Members"<<endl;
            cout<<"\n\t\t\t\t Issue Book to a Member"<<endl;
            cout<<"\n\t\t\t\t Return Book from a Member"<<endl;
            cout<<"\n\t\t\t\t List all Books in the System"<<endl;
            cout<<"\n\t\t\t\t List all Members in the System"<<endl;
            cout<<"\n\t\t\t\t Edit Book"<<endl;
            cout<<"\n\t\t\t\t"<<c<<" Edit Member"<<endl;
            cout<<"\n\t\t\t\t Enquire Book"<<endl;
            cout<<"\n\t\t\t\t Enquire Member"<<endl;
            cout<<"\n\t\t\t\t Quit from this System"<<endl;
        }
         else if(i==9)
        {
            system("cls");
            cout<<"\n\n\t\t**********   WELCOME TO SIMPLE BOOKS LIBRARY SYSTEM  **********\n\n";
            cout<<"\n\t\t\t\t Add new Books"<<endl;
            cout<<"\n\t\t\t\t Add new Members"<<endl;
            cout<<"\n\t\t\t\t Issue Book to a Member"<<endl;
            cout<<"\n\t\t\t\t Return Book from a Member"<<endl;
            cout<<"\n\t\t\t\t List all Books in the System"<<endl;
            cout<<"\n\t\t\t\t List all Members in the System"<<endl;
            cout<<"\n\t\t\t\t Edit Book"<<endl;
            cout<<"\n\t\t\t\t Edit Member"<<endl;
            cout<<"\n\t\t\t\t"<<c<<" Enquire Book"<<endl;
            cout<<"\n\t\t\t\t Enquire Member"<<endl;
            cout<<"\n\t\t\t\t Quit from this System"<<endl;
        }
        else if(i==10)
        {
            system("cls");
            cout<<"\n\n\t\t**********   WELCOME TO SIMPLE BOOKS LIBRARY SYSTEM  **********\n\n";
            cout<<"\n\t\t\t\t Add new Books"<<endl;
            cout<<"\n\t\t\t\t Add new Members"<<endl;
            cout<<"\n\t\t\t\t Issue Book to a Member"<<endl;
            cout<<"\n\t\t\t\t Return Book from a Member"<<endl;
            cout<<"\n\t\t\t\t List all Books in the System"<<endl;
            cout<<"\n\t\t\t\t List all Members in the System"<<endl;
            cout<<"\n\t\t\t\t Edit Book"<<endl;
            cout<<"\n\t\t\t\t Edit Member"<<endl;
            cout<<"\n\t\t\t\t Enquire Book"<<endl;
            cout<<"\n\t\t\t\t"<<c<<" Enquire Member"<<endl;
            cout<<"\n\t\t\t\t Quit from this System"<<endl;
        }
        else if(i==11)
        {
            system("cls");
            cout<<"\n\n\t\t**********   WELCOME TO SIMPLE BOOKS LIBRARY SYSTEM  **********\n\n";
            cout<<"\n\t\t\t\t Add new Books"<<endl;
            cout<<"\n\t\t\t\t Add new Members"<<endl;
            cout<<"\n\t\t\t\t Issue Book to a Member"<<endl;
            cout<<"\n\t\t\t\t Return Book from a Member"<<endl;
            cout<<"\n\t\t\t\t List all Books in the System"<<endl;
            cout<<"\n\t\t\t\t List all Members in the System"<<endl;
            cout<<"\n\t\t\t\t Edit Book"<<endl;
            cout<<"\n\t\t\t\t Edit Member"<<endl;
            cout<<"\n\t\t\t\t Enquire Book"<<endl;
            cout<<"\n\t\t\t\t Enquire Member"<<endl;
            cout<<"\n\t\t\t\t"<<c<<" Quit from this System"<<endl;
        }
        else{}
    }
}
