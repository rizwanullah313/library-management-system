/****************************************************
               LIBRARY MAMNEMENT SYSTEM 
*****************************************************/                    
#include <iostream>
#include <conio.h> //getch
#include <ctime>
#include <fstream>
#include <string>
#include <ctime>
#include<windows.h>
using namespace std;

string BookName,StdName,sid,BookAuthor,Membername,MemberID,MemberNIC,Memberqualification;
int countBook=0,countissuebook=0,BookBookNo,BookQuantity,countMembers;

    //structure of book
struct Book        
    {
    string name;
    string author;
    int bookNo;
    int quantit;
    Book*next= NULL;
    }*head=NULL;

    //Structure Of Members
struct Members
    {
    string name;
    string NIC;
    string ID;
    string Qualification;
    Members*next= NULL;	
    }*head2=NULL;

    //structure of issuing  book
struct issuebook{
    string stdname;
    string stdid;
    string bookname;
    string issuedate;
    string duedate;
    int no_of_book_issued_to_student;
    issuebook *next;  
    }*head1=NULL; 

    // current time() And time           
char* current_time()  
    {
    time_t now = time(0);
    time_t r=time(0);
    char* dt = ctime(&now);
    char* rt=ctime(&r);
    tm *gmtm = gmtime(&now);
    return dt;
    }

    //insert a book
bool insertbook(string Name,string Author,int BookNo, int Quantity,char* time)
    {
    bool flag=false;
    ofstream myfile("books.txt",ofstream::out | ofstream::app);
    Book *newBook= new Book;
    Book *temp;
    countBook++;
    newBook->name    = Name;
    newBook->author  = Author;
	newBook->bookNo  = BookNo;
	newBook->quantit = Quantity; 
    newBook->next=NULL;
    if(head==NULL)
    {
    head=newBook;
    flag=true;
    }
    else
    {
    temp=head;
    while(temp->next!=NULL)
    {
    temp=temp->next;
    }
    temp->next=newBook;
    flag=true;
    }
    myfile<<newBook->name<<" "<<newBook->author<<" "<<newBook->bookNo<<" "<<newBook->quantit<<" Date and time "<<time<<endl;
    myfile.close();
    return flag;
    }
    //ADD Members
bool insertmembers(string name,string NIC,string ID,string qualification,char* time)
    {
    bool flag=false;
    fstream myfile22("members.txt",ofstream::out | ofstream::app);
  
    Members *newMembers= new Members;
    Members *temp;
    countMembers++;
    newMembers->name    = name;
    newMembers->NIC     = NIC;
	newMembers->ID      = ID;
	newMembers->Qualification = qualification; 
    newMembers->next=NULL;
    if(head2==NULL)
    {
    head2=newMembers;
    flag=true;
    }
    else
    {
    temp=head2;
    while(temp->next!=NULL)
    {
    temp=temp->next;
    }
    temp->next=newMembers;
    flag=true;
    }
    myfile22<<newMembers->name<<" "<<newMembers->NIC<<" "<<newMembers->ID<<" "<<newMembers->Qualification<<" Date and time "<<time<<endl;
    myfile22.close();
    return flag;	
    }

    // search book
bool Search(string bname)
    {
    bool flag=false;
    ifstream myfile2("books.txt");  
    while(!myfile2.eof())
    {
    myfile2>>StdName;
    if(StdName==bname)
    {
    flag=true;
    break;
    }
    }
    myfile2.close();
    return flag;
    }

    // search student
bool Searchstd(string name){   
    bool flag=false;
    string Snme;
    ifstream myfile("students.txt");
    while(!myfile.eof()){
    myfile>>Snme;
    if(Snme==name)
    {
    flag=true;
    break;
    }
    }
    myfile.close();
    return flag;
    }

    //search issue book
issuebook *SearchissueBook(string input)
    {
    bool flag=false;
    issuebook *temp=head1;
    for(int i=1;i<=countissuebook;i++)
    {
    if(temp->stdid==input)
    { 
    flag=true;
    break;
    }
    temp=temp->next;
    }
    if(flag==true)
    {
    return temp;
    }
    else
    return NULL;
    }

    //Issue Book To student
void IssueBook(string sname,string sid,string bname)
    {
    ofstream myfile1("issuebooks.txt",ofstream::out | ofstream::app);
    bool flag=false;
    issuebook *temp;
    issuebook *Ibook=new issuebook;
    issuebook *temp2;
    // issuebook * Ibook= new issuebook;
    temp2= SearchissueBook(sname);
    if(Searchstd(sname) && Search(bname) && temp2==NULL)
    {
    cout<<"\t\t\t\t\tBook FOund\n"<<endl;
    Ibook->no_of_book_issued_to_student=1;
    cout<<"\n\t\t\t\t\tEnter BoOk NamE: ";
    cin>>Ibook->bookname;
    cout<<"\n\t\t\t\t\tEnter StuDent NamE: ";
    cin>>Ibook->stdname;
    cout<<"\n\t\t\t\t\tEnter StudEnt iD: ";
    cin>>Ibook->stdid;
    Ibook->issuedate=current_time();
    Ibook->next=NULL;
    countissuebook++;
    cout<<"\n\t\t\t\t\tEnter Due date: ";
    cin>>Ibook->duedate;
     if(head1==NULL)
   {
    head1=Ibook;
   }
   else
   {
    temp=head1;
    while(temp->next!=NULL)
    {
     temp=temp->next; 
     
    }temp->next=Ibook;
    
   }
   Ibook->no_of_book_issued_to_student=1;
    cout<<"\t\t\t\t\tSucessfully ISsued!\n";
    system("PAUSE");
    flag=true;
    }
    
 if(flag==true)
 {
  cout<<"\t\t\t\t\tSucessfully issued \n";
   myfile1<<"Student NAme: "<<Ibook->stdname<<" Book name: "<<Ibook->bookname<<" Issuedate: "<<current_time()<<endl;

 }
 else
 cout<<"\t\t\t\t\tyou have already issued a book \n";
   myfile1.close();

}

   // Display Issue Books
void display()
   {
   issuebook *temp1=NULL;
   if(head1==NULL)
   {
   cout<<"\t\t\t\t\tNO book issued \n";
   }
   else
   {temp1=head1;
   while(temp1->next!=NULL)
   {
   cout<<temp1->bookname<<endl;
   /*cout<<temp1->stdname<<endl;
   cout<<temp1->stdid<<endl;
   cout<<temp1->issuedate<<endl;
   cout<<temp1->no_of_book_issued_to_student<<endl;
   cout<<temp1->duedate<<endl;
   cout<<temp1->next;*/
   temp1=temp1->next;
   }
   cout<<temp1->bookname<<endl;
   system("PASUE");
   }}
   //return Book
void ReturnBook(string name)
   {
   int DaysBookKept;
   issuebook *temp=head1;
   issuebook* temp2=NULL;
   bool flag=false;
   for(int i=0;i<countissuebook;i++)
   {
   if(temp->stdname==name)
   {
   cout<<"\t\t\t\t\t************************************************** \n";
   cout<<"\t\t\t\t\t"<<temp->issuedate<<"\t\t\t\t\t was his issued dATE "<<endl;
   cout<<"\t\t\t\t\tDue DAte of your book is "<<temp->duedate<<endl;
   cout<<"\t\t\t\t\t************************************************** \n";
   cout<<"\t\t\t\t\tEnter No of days kept ";
   cin>>DaysBookKept;
   temp2=temp;
   if(DaysBookKept<=7 && DaysBookKept>=1)
   {
   countissuebook--;
   flag=true; 
   }
   else
   {
   cout<<"\t\t\t\t\tYou have to pay fine \n";
   cout<<"\t\t\t\t\t"<<(DaysBookKept-7)*100<<"  rupees"<<endl;
   temp->no_of_book_issued_to_student=0;
   flag=true;
   countissuebook--;
    system("PAUSE");
   return;
   }
   break;
   } 
   temp=temp->next; 
   }
   if(flag==true)
   {
   cout<<"\t\t\t\t\tReturn sucessfuly \n";
   }
   else
   {
   cout<<"\t\t\t\t\tInvalid student name \n";
   }
   if(head1==NULL)
   {
   cout<<"\t\t\t\t\tNo book issue \n";
   }
   else
   {
   temp2->next=temp->next;
   delete temp;
   cout<<"\t\t\t\t\tBook is also del from the list \n";
   }
   }
int main()
   {
	
    int ch;
	system("cls");
	system("color 3f");
	cout<<"\n\t\t\t/////////////////////////////////////////////////////////\n";
	cout<<"\n\t\t\t/\t\tLIBRARY MANAGEMENT SYSTEM\t\t/\n";                                    //MAIN MENU
	cout<<"\n\t\t\t/////////////////////////////////////////////////////////\n";	
	cout<<"\n\t\t\t|\t\t\tMain Menu\t\t\t|\n\n";
	cout<<"\t\t\t---------------------------------------------------------\n";
	Sleep(100);
	cout<<"\t\t\t\t\t1.  Add new Books\n";
	Sleep(100);
	cout<<"\t\t\t\t\t2.  Add new Members\n";
	Sleep(100);
	cout<<"\t\t\t\t\t3.  Search A Book\n";
	Sleep(100);
	cout<<"\t\t\t\t\t4.  Issue A Book\n";
	Sleep(100);
	cout<<"\t\t\t\t\t5.  Return A Book\n";
	Sleep(100);
	cout<<"\t\t\t\t\t6.  View Members Account\n";
	Sleep(100);
	cout<<"\t\t\t\t\t7.  View Stock\n";
	Sleep(100);
	cout<<"\t\t\t\t\t8.  List Of Books Issued\n";
	Sleep(100);
	cout<<"\t\t\t\t\t9.  Exit\n\n";
	Sleep(100);
	cout<<"\t\t\t\t\tEnter Your choice: ";
	cin>>ch;
	system("cls");
	if(ch==1){
	system("cls");
	cout<<"\t\t\t\tEnter Book Name:  ";
    cin>>BookName;
    cout<<"\t\t\t\tEnter Book Author: ";
    cin>>BookAuthor;
    cout<<"\t\t\t\tEnter Book ID: ";
    cin>>BookBookNo;
    cout<<"\t\t\t\tEnter Book Quantity: ";
    cin>>BookQuantity;
    if(insertbook(BookName,BookAuthor,BookBookNo,BookQuantity,current_time()) )
    {
    cout<<"\t\t\t\tSuccessFully Added"<<endl;
    }
    else
    {
    cout<<"\t\t\t\tNot added"<<endl;
    }
    system("PAUSE");
    system("cls");
    return main();
    }
    else if(ch==2)
	{
	system("cls");
	cout<<"\t\t\t\tEnter Member Name:  ";
    cin>>Membername;
    cout<<"\t\t\t\tEnter CNIC: ";
    cin>>MemberNIC;
    cout<<"\t\t\t\tEnter ID: ";
    cin>>MemberID;
    cout<<"\t\t\t\tEnter qualification: ";
    cin>>BookQuantity;
    if(insertmembers(Membername,MemberNIC,MemberID,Memberqualification,current_time() ))
    {
    cout<<"\t\t\t\tSuccessFully Added"<<endl;
    }
    else
    {
    cout<<"\t\t\t\tNot added"<<endl;
    }
    system("PAUSE");
    system("cls");
    return main();
    } 
    else if(ch==3)
    {
   	cout<<"\t\t\t\t\tEnTeR BooK NaMe: ";
    cin>>BookName;
    Search(BookName);
    if(Search(BookName))
    cout<<"\t\t\t\t\tBoOk found!\n";
    else
    cout<<"\t\t\t\t\tNot found!,InvaLiD BooK NaMe\n";
    system("pause");
    return main();
    }
    else if(ch==4)
    {
    cout<<"\t\t\t\t\tEnTeR BooK NaMe:";
    cin>>BookName;
    IssueBook(StdName,sid,BookName);
    return main();
	}
	else if(ch==5)
	{
	cout<<"\t\t\t\t\tEnter StUdEnT NaME :";
    cin>>StdName;
    ReturnBook(StdName);
    return main();
	}
	else if(ch==8)
	{
	display();
	return main();
	}
    }
