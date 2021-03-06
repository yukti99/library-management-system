// Header Files
#include <iostream>
#include <cstdio>
#include <fstream>                  // file handling
#include <conio.h>                  //contains delay(),getch(),gotoxy(),etc.
#include <string>
#include <stdlib.h>
#include <string>                   //contains strcmp(),strcpy(),strlen(),etc
#include <windows.h>
#include <time.h>
#include  <ctype.h>                  //contains toupper(), tolower(),etc
#include <dos.h>                    //contains _dos_getdate
#include <stdio.h>                  //contains printf,scanf etc
#include <cstdlib>                  //rand()
#include <sstream>                  // to inter-convert string and numbers
#include <limits>                   /* To prevent sudden abortion or error in program
                                          if user enters invalid input */
 
using namespace std ;

void Customer_Menu();
void IssueBooks();
void MainMenu();


//Global variables
char password[8] = "enchant"; 



/*################ help from stackoverflow ################# */
COORD coord = {0, 0}; // sets coordinates to 0,0
//COORD max_buffer_size = GetLargestConsoleWindowSize(hOut);
COORD max_res,cursor_size;
void gotoxy (int x, int y)
{
        // X and Y coordinates
		coord.X = x; 
		coord.Y = y; 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void end()
{
	system("cls");
	system("color F5");
	gotoxy(10,4);
	cout<<"*******************THANK YOU FOR VISITING*******************";
	gotoxy(10,6);
	cout<<"HEAD OF DREAMS LIBRARY : MS. YUKTI KHURANA";
	gotoxy(10,8);
	cout<<"CONTACT : 9871636565";
	gotoxy(10,10);
	cout<<"EMAIL   :yuktikhurana99@gmail.com";
	gotoxy(10,12);
	cout<<"************************HAPPY READING!**********************";
	gotoxy(10,14);
	delay(3000);
}


struct Lib_date
{
	int dd,mm,yy ;
};
struct Lib_date d1;
struct Lib_date d2;

const char* MONTHS[] =
  {
  "January", "February", "March", "April", "May", "June",
  "July", "August", "September", "October", "November", "December"
  };
// To store number of days in all months from January to Dec.
const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};
 
// This function counts number of leap years before the given date
int countLeapYears(Lib_date d)
{
    int years = d.yy;
    // Check if the current year needs to be considered
    // for the count of leap years or not
    if (d.mm <= 2)
        years--; 
    // An year is a leap year if it is a multiple of 4,
    // multiple of 400 and not a multiple of 100.
    return years / 4 - years / 100 + years / 400;
} 
// This function returns number of days between two given
// dates
int Days_Diff(Lib_date d1,Lib_date d2)
{
    // COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1'
 
    // initialize count using years and day
    long n1 = d1.yy*365 + d1.dd;
 
    // Add days for months in given date
    for (int i=0; i<d1.mm - 1; i++)
        n1 += monthDays[i];
 
    // Since every leap year is of 366 days,
    // Add a day for every leap year
    n1 += countLeapYears(d1);
 
    // SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2'
 
    long int n2 = d2.yy*365 + d2.dd;
    for (int i=0; i<d2.mm - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(d2);
 
    // return difference between two counts
    return (n2 - n1);
}
int day()
{
	time_t T;
	struct tm* timeinfo ;    // pointer to struct tm
	time(&T);
	timeinfo = localtime(&T);
	return timeinfo->tm_mday;
}	
int month()
{
	time_t T;
	struct tm* timeinfo ;    
	time(&T);
	timeinfo = localtime(&T);
	return timeinfo->tm_mon;
}
int year()
{
	time_t T;
	struct tm* timeinfo ;    
	time(&T);
	timeinfo = localtime(&T);
	return timeinfo->tm_year+1900 ;
}


char genre[5][20] = {"Fantasy","Adventure","Crime-Fiction","Science","Social-Science"};


struct Reader
{
	char name[50];
	int R_id;
	int age;
	char gender;
	char email[50];
	char password[50];
	long long contact;
	int book_id ;
	struct Lib_date issued  ;
	struct Lib_date duedate ;
};
struct library
{
    int id;
    int issued ;
    char name[50];
    char author[50];
    int quantity;
    float price;
    char *gen;
    int count ;
    
};
struct Reader a;
struct library b;

//  for date & time
void Date_Time(void) 
{
	time_t t = time(NULL);
	cout<<"Date and time : "<<ctime(&t);
}
// To return to main menu
void back()
{       
	cout<<" Press ENTER to return to main menu ";
    a:
    if(getch() == 13)               //allow only use of enter
    	Customer_Menu();
    else
    	goto a;
}
void Lib_Menu();

//check whether the book exists in library or not
int CheckId(int i)  
{
	fstream f;
	f.open("lib.txt",ios::in|ios::binary);
	f.seekg(0,ios::beg);
	while ( !f.eof() )
	{
		f.read( (char*)&b , sizeof(library) );		
		if (b.id == i)
			return 0;             //returns 0 if book exits
	} 
	f.close();
	return 1;                     //return 1 if it does not exist
	
}

void ViewBooks()
{
	system("cls");
	system("color f2");
	int id;
	fstream f;
	f.open("lib.txt",ios::in|ios::binary);
	f.seekg(0,ios::beg);
	if (f.bad())
		cout<<"Some problem is occuring in file opening..\n";
	cout<<"Enter Id to search = ";
	cin>>id;
	cout<<"Searching...."<<endl;
	//delay(1000);
	if (CheckId(id)==1)      // book does not exist
	{
		cout<<"No book with given ID exists in the library\n";
		goto m;
	}	
	system("cls");
	while (!f.eof())
	{
		f.read( (char*)&b , sizeof(library) );
		if (b.id == id)
		{
			cout<<"########################################\n";
			cout<<"BOOK ID  : "<<b.id<<endl;
			cout<<"CATEGORY : "<<b.gen<<endl;			
			cout<<"NAME     : "<<b.name<<endl;
			cout<<"AUTHOR   : "<<b.author<<endl;
			cout<<"PRICE    : "<<b.price<<endl;
			cout<<"QUANTITY : "<<b.quantity<<endl;
			cout<<"NO ISSUED: "<<b.issued<<endl;
			cout<<"########################################\n";
			goto m;			
		}			
	}
	m : f.close();
    cout<<"Do you want to see any more records?(Y/N)";
	if (getch()=='y')
		ViewBooks();
    cout<<"\nPress ENTER to return to main menu\n";	
	if (getch() == 13)
		Lib_Menu();	
	
}
void BooksList()
{
	
	system("cls");
	system("color F5");
	gotoxy(1,1);
    //cout<<"\t\t\t\t\t\t\tBOOK LIST";
    cout<<"*******************************************************BOOK LIST****************************************************";
    gotoxy(2,2);
    cout<<"ID\tCATEGORY\t\tBOOK NAME\t\tAUTHOR NAME\t\tQTY\tPRICE\tNO ISSUED " ;  // 3 tabs gap
    int j=4,i=0;
    fstream f;
	f.open("lib.txt",ios::in|ios::binary);
	f.seekg(0,ios::beg);
	if (f.bad())
		cout<<"Some problem is occuring in file opening..\n";
    while (1)
	{
		f.read( (char*)&b , sizeof(library) );
		/* after encountering eof it flags it and finally end it in next iteration
		to avoid duplication of last book record this statement is used rather than while(f.eof()) */
		if (f.eof())       
			break;
    	gotoxy(3,j);
		cout<<b.id;			
		gotoxy(9,j);
		cout<<b.gen;		
		gotoxy(30,j);
		cout<<b.name;	
		gotoxy(60,j);
		cout<<b.author;				
		gotoxy(80,j); 
		cout<<b.quantity;		
		gotoxy(90,j);
		cout<<b.price;				
		gotoxy(100,j);
		cout<<b.issued;				
		j++;
		i++;	
	}
	gotoxy(3,25);
    cout<<"Total Books = "<<i;
    f.close();
    gotoxy(35,25);
	if (getch()==13)
		Customer_Menu();
}

// Function that adds books
void AddBooks()
{
	system("cls");	
	system("color F2");
	int c=0;
	cout<<"Which Category do you want to add the book to ?\n";
	for(int i=0;i<5;i++)	
		cout<<i+1<<"."<<genre[i]<<endl;	
	cin>>c;	
	b.gen = genre[c-1];
	system("cls");
	system("color F2");
	cout<<"Category : "<<b.gen<<endl; 
	cout<<"Please Enter the information of the book to add...\n";
	int ID;	
	cout<<"Book Id : ";
	cin>>ID;	
	if (CheckId(ID) == 0)   // book exists already
	{
		cout<<"\aThe book Id already exists...\n";
		cout<<"Press ENTER to continue...";
		if (getch() == 13)
			Lib_Menu();
		
	}
	b.id = ID ;
	cout<<"Name : ";
	cin>>b.name;              //cin.getline(b.name,50);	
	cout<<"Author : ";        //cin.getline(b.author,50);		
	cin>>b.author;		
	cout<<"No of Copies : ";
	cin>>b.quantity ;	
	cout<<"Price(Rs.) : ";
	cin>>b.price;	
	b.issued = 0;
	cout<<"\nAdding book...";
	delay(1000);
	// Writing to file
	fstream f ;
	f.open("lib.txt",ios::out|ios::app|ios::binary);
	if (!f.fail())
	{
		f.write( (char*)&b , sizeof(library) );
	}
	else
	{
		cout<<"Failed..\n";
		Lib_Menu();
		
	}
		
	cout<<"\aBook added successfully!\n";
	f.close();	
	cout<<"Do you want to add more(Y/N)";
	if (getch()=='y')
		AddBooks();
	else
		Lib_Menu();
}

// Function that modifies book records
void EditBooks()
{
	system("cls");
	int i;
	char ans;
	cout<<"Enter Book ID to edit : ";
	cin>>i;
	if (CheckId(i)==1)       // book record does not exist
	{
		cout<<"The book record does not exist!\n";
			if (getch())
				Lib_Menu();
		
	}
	fstream f;
	f.open("lib.txt",ios::in|ios::binary);
	f.seekg(0,ios::beg);
	while(f.read( (char*)&b , sizeof(b) ))
	{
		if (i == b.id)
		{
			cout<<"The Book record exists : \n";
			cout<<"########################################\n";
			cout<<"BOOK ID  : "<<b.id<<endl;
			cout<<"CATEGORY : "<<b.gen<<endl;			
			cout<<"NAME     : "<<b.name<<endl;
			cout<<"AUTHOR   : "<<b.author<<endl;
			cout<<"PRICE    : "<<b.price<<endl;
			cout<<"QUANTITY : "<<b.quantity<<endl;
			cout<<"########################################\n";	
			goto l;			
		}
	}
	l : f.close();
	cout<<"Do you want to Modify it ?(Y/N)";
	cin>>ans;
	if (ans == 'y')
	{
		fstream f ;
		f.open("lib.txt",ios::in |ios::out|ios::binary);
		f.seekg(0,ios::beg);
		while (f.read( (char*)&b, sizeof(b)))
		{
			if (b.id == i)
			{
				int c=0;
				cout<<"Select New Category ?\n";
				for(int i=0;i<5;i++)	
					cout<<i+1<<"."<<genre[i]<<endl;	
				cin>>c;	
				b.gen = genre[c-1];
				cout<<"Update Info\n";
				int ID;	
				cout<<"Book Id : ";
				cin>>ID;	
				b.id = ID ;
				cout<<"Name : ";
				cin>>b.name;              
				cout<<"Author : ";       		
				cin>>b.author;		
				cout<<"No of Copies : ";
				cin>>b.quantity ;	
				cout<<"Price(Rs.) : ";
				cin>>b.price;	
				cout<<"\nUpdating Record...";
				delay(2000);
				system("cls");
				gotoxy(5,5);
				cout<<"Record Modified successfully!";
				f.seekp(-sizeof(b) ,ios::cur);		
				f.write( (char*)&b , sizeof(library) );	
				break;	
					
			}
		}
		f.close();	
		
	}
	gotoxy(5,6);
	cout<<"Press ENTER to continue...\n";
	if (getch()==13)
		Lib_Menu();
	
}


// Function that deletes books
void DeleteBooks()
{
	system("cls");
	int i;
	char ans;
	cout<<"Enter Book ID to delete : ";
	cin>>i;
	if (CheckId(i)==1)       // book record does not exist
	{
		cout<<"The book record does not exist!\n";
			if (getch())
				Lib_Menu();
		
	}
	fstream f;
	f.open("lib.txt",ios::in|ios::binary);
	f.seekg(0,ios::beg);
	while(!f.eof())
	{
		f.read( (char*)&b , sizeof(b) ) ;
		if (i == b.id)
		{
			cout<<"The Book record exists : \n";
			cout<<"########################################\n";
			cout<<"BOOK ID  : "<<b.id<<endl;
			cout<<"CATEGORY : "<<b.gen<<endl;			
			cout<<"NAME     : "<<b.name<<endl;
			cout<<"AUTHOR   : "<<b.author<<endl;
			cout<<"PRICE    : "<<b.price<<endl;
			cout<<"QUANTITY : "<<b.quantity<<endl;
			cout<<"########################################\n";	
			goto c;			
		}
	}
	c : f.close();
	cout<<"Do you want to delete it ?(Y/N)";
	cin>>ans;
	if (ans == 'y')
	{
		cout<<"Deleting...\n";
		fstream f1;
		fstream f2;
		f2.open("lib.txt",ios::in|ios::binary);
		f2.seekg(0,ios::beg);
		f1.open("t.txt",ios::out|ios::binary|ios::app);
		f1.seekg(0,ios::beg);
		//f.seekg(0,ios::beg);   // go to beginning to file -lib.txt
		while ( !f2.eof() )
		{
			f2.read( (char*)&b , sizeof(library));
			if (b.id != i)                  // Writing all records except the one to be deleted
			{
				//f1.seekg(0,ios::cur);
				f1.write( (char*)&b , sizeof(library) );
			}
		}
		f1.close();
		f2.close();
		remove("lib.txt");
		rename("t.txt","lib.txt"); //copy all item from temporary file to f except that what we want to delete
		cout<<"Book deleted successfully!\n";
		goto v;
		if (CheckId(i)==1)   // book does not exist
		{
			cout<<"Book successfully deleted..\n";
			goto v;
		}
		else
		{
			cout<<"Deletion failed due to some technical error!\n";
			goto v;
		}
				
	}
	else
	{
		v: cout<<"\nPress ENTER to return to main menu..\n";
		if (getch() == 13)
			Lib_Menu();
	}
}


// To validate the entered email
int Check_Email(string s)
{
	int a=0,b=0,c=0,d=0,e=0,f=0,pos1,pos2;
	int l = s.length() ;
	if (s[0]>=65 && s[0]<=122) 
		a = 1;
	if ( (s[l-1]>=65 && s[l-1]<=122) || (s[l-1]>=0 && s[l-1]<=9)   )
		d = 1 ;	
	for(int i=0;i<l;i++)
	{
		if (s[i] == '@')
		{
			pos1 = i;
			b++;
			if (s[i+1]=='.')
				b=0;			
		}			
		if (s[i] == '.')
		{
			pos2 = i;
			c++;
		}		
			
		if ( (s[i]>=65 && s[i]<=122) || (s[i]>=48 && s[i]<=57) || s[i]=='_'|| s[i]=='@'|| s[i]=='.' )
			e++;
					
	}
	if (c<1)
		return 0;
    if(pos1<pos2)
    	f=1;
	for(int j=0;j<pos1;j++)
	{
		if (s[j]=='.')
			return 0;
	}
	if (a==1&&b==1&&d==1&&e==l&&f)
		return 1;
	else
		return 0;	
}
// Function to convert numeric value into string
string no_to_str(int n)
{
	ostringstream s1;
    s1<<n;
    string s = s1.str();
    return s;		
}
int Check_Password(string s)
{
	int l,d,a,c,b ;
	int len = s.length();
	l=d=a=c=0;
    b=1;
    for(int i=0 ; i<len ;i++)
    {
		l++;
		if (s[i]>=48 && s[i]<=57)
			d = 1;
		if (s[i]>=65 && s[i]<=90)
			a = 1 ;
		if (s[i] == '_'|| s[i] == '@' || s[i] == '$')
			c = 1 ;
		if ((s[i]>=0 && s[i]<=35) ||(s[i]>=37 && s[i]<=47)|| (s[i]>=91 && s[i]<=94) || s[i]>=123 || (s[i]>=58 && s[i]<=63) || s[i]==96)
		    b = 0 ;   	    
    }
    if (l>=8 && d==1 && a==1 && c==1 && b==1)
   		return 1;
   	else
   		return 0;
	
}
int login(void);

// Function to issue books
void IssueBooks()
{
	if (!login())
		Customer_Menu() ;
	else
	{
		system("cls");
		system("color F5");
		int ib,ir,y=0,z=0;
		char n[50];
		fstream fr,fl;
		fr.open("Readers.txt",ios::in|ios::out|ios::binary);
		fl.open("lib.txt",ios::in|ios::out|ios::binary);
		fr.seekg(0,ios::beg);
		fl.seekg(0,ios::beg);
		if (fr.fail() || fl.fail())
			cout<<"Failed due to technical error!\n";
			
		cout<<"********************ISSUE SECTION********************\n";
		cout<<"Enter Book Name : ";			
		cin>>n;
		while( fl.read((char*)&b,sizeof(b)) )
		{
			
			if (strcmp(n,b.name)==0 && b.quantity > 0)
			{
				y=1;
				cout<<"Book is available!\n";
				v:cout<<"Enter your membership ID : ";
				cin>>ir;
				while(fr.read((char*)&a,sizeof(a)) )
				{

					if (ir == a.R_id)                // a- reader,b-book
					{
						if (a.book_id)
						{
							cout<<"Sorry!You have already issued a book with Id - "<<a.book_id;
							cout<<"\nYou must return it first...\n ";
							fr.close();
							fl.close();
							if (getch()==13)
								Customer_Menu();							
						}
						z=1;
						b.quantity-- ;
						a.book_id = b.id;
						b.issued++ ;
						a.issued.dd = day();
						a.issued.mm = month();
						a.issued.yy = year();
						a.duedate.dd = a.issued.dd + 15;   // return time is 15 days
						a.duedate.mm=a.issued.mm;
	 					a.duedate.yy=a.issued.yy;	
						if(a.duedate.dd>30)
					    {
							a.duedate.mm+=a.duedate.dd/30;
							a.duedate.dd-=30;
		
					    }
					    if(a.duedate.mm>12)
					    {
							a.duedate.yy+=a.duedate.mm/12;
							a.duedate.mm-=12;
						}
						fl.seekp(-sizeof(b) ,ios::cur);		
						fl.write( (char*)&b , sizeof(library) );
						fr.seekp(-sizeof(a) ,ios::cur);		
						fr.write( (char*)&a , sizeof(Reader) );	
						cout<<"Book Id : "<<b.id<<" is successfully issued to ";
						cout<<a.name<<" with ID : "<<a.R_id<<endl;
						cout<<"The book must be returned in 15 days.\n";
						cout<<"Date of Issue  : ";
						cout<<a.issued.dd<<" "<<MONTHS[a.issued.mm]<<" "<<a.issued.yy<<endl;						
						cout<<"Date of Return : ";
						cout<<a.duedate.dd<<" "<<MONTHS[a.duedate.mm]<<" "<<a.duedate.yy<<endl;
						fl.close();
						fr.close();
						if (getch()==13)
							Customer_Menu();						
				   }
					
			    }			    
				if (z==0)
				{
					fl.close();
					fr.close();
					cout<<"\aInvalid Readers ID....\n";
					cout<<"Try Again? (Y/N) ";
					if (getch()=='y')
						goto v;
					else
						Customer_Menu();							
				}
			}
		}		
		if (y==0)
		{
			fl.close();
			fr.close();
			cout<<"\aSorry!This book is unavailable...\n";
			cout<<"Want to issue another book? (Y/N) ";
			if (getch()=='y')
				IssueBooks();
			else
				Customer_Menu();							
		}			
		
					
	}	
}
// Function to return books
void ReturnBooks()
{
	if (!login())
		Customer_Menu() ;
	else
	{
		system("cls");
		system("color F4");
		int ib,ir,y=0,z=0;
		int fine = 0,late_days = 0,perday = 10;
		char n[50];
		fstream fr,fl;
		fr.open("Readers.txt",ios::in|ios::out|ios::binary);
		fl.open("lib.txt",ios::in|ios::out|ios::binary);
		fr.seekg(0,ios::beg);
		fl.seekg(0,ios::beg);
		if (fr.fail() || fl.fail())
			cout<<"Failed due to technical error!\n";
			
		cout<<"********************RETURN SECTION********************\n";
		cout<<"Enter Book Name : ";			
		cin>>n;
		while( fl.read((char*)&b,sizeof(b)) )
		{
			
			if (strcmp(n,b.name)==0 && b.issued > 0 )
			{
				y=1;
				v:cout<<"Enter your membership ID : ";
				cin>>ir;
				while(fr.read((char*)&a,sizeof(a)) )
				{

					if (ir == a.R_id && a.book_id == b.id)                // a- reader,b-book
					{
						z=1;
						cout<<"The book with ID : "<<b.id<<"\nwas issued on :";
						cout<<a.issued.dd<<" "<<MONTHS[a.issued.mm]<<" "<<a.issued.yy<<endl;
						cout<<"\nLast date of Return : ";
						cout<<a.duedate.dd<<" "<<MONTHS[a.duedate.mm]<<" "<<a.duedate.yy<<endl;		
						b.quantity++ ;
						a.book_id = 0; 
						b.issued-- ;
						d1.dd = a.duedate.dd;
						d1.mm = a.duedate.mm +1;
						d1.yy = a.duedate.yy;
						d2.dd = day();
						d2.mm = month() +1 ;
						d2.yy = year();
						late_days = Days_Diff(d1,d2);
						fine = late_days*perday;   // fine perday late is Rs.10
						if (fine>0)
							cout<<"\nYour FINE = Rs."<<fine<<endl;						
						fl.seekp(-sizeof(b) ,ios::cur);		
						fl.write( (char*)&b , sizeof(library) );
						fr.seekp(-sizeof(a) ,ios::cur);		
						fr.write( (char*)&a , sizeof(Reader) );	
						cout<<"Book Id : "<<b.id<<" is successfully returned to ";
						cout<<"The library on ";
						cout<<d2.dd<<" "<<MONTHS[d2.mm-1]<<" "<<d2.yy;
						cout<<"\nby "<<a.name<<"endl";						
						fl.close();
						fr.close();
						if (getch()==13)
							Customer_Menu();						
				   }
					
			    }			    
				if (z==0)
				{
					fl.close();
					fr.close();
					cout<<"\aInvalid Readers ID....\n";
					cout<<"Try Again? (Y/N) ";
					if (getch()=='y')
						goto v;
					else
						Customer_Menu();							
				}
			}
		}		
		if (y==0)
		{
			fl.close();
			fr.close();
			cout<<"\aSorry!This book is either not issued yet or does not exist in the library...\n";
			cout<<"Want to try again ? (Y/N) ";
			if (getch()=='y')
				ReturnBooks();
			else
				Customer_Menu();							
		}			
		
					
	}	
}


void PasswordRules()
{
	cout<<"\nPlease create a Password for your account\n";
	cout<<"***************************************************\n";	
	cout<<"Primary conditions for Password validation :\n\n";	
	cout<<" # Minimum 8 characters.\n";	
	cout<<" # The alphabets must be between [a-z].\n";	
	cout<<" # At least one alphabet should be of Upper Case [A-Z].\n";	
	cout<<" # At least 1 number or digit between [0-9].\n";	
	cout<<" # At least 1 character from [ _ or @ or $ ].\n\n";	
	cout<<"***************************************************\n\n";
}
void ResetPassword()
{
	system("cls");
	int i,y=0 ;
	char e[50] ;
	cout<<"***************RESET PASSWORD**************\n";
	cout<<"Enter id :";
	cin>>i;
	cout<<"Email :";
	cin>>e;
	fstream f;
	f.open("Readers.txt",ios::in|ios::out|ios::binary);
	f.seekg(0,ios::beg);
	if (f.bad())
		cout<<"\nFailed! Due to some technincal error\n";
	while(f.read( (char*)&a, sizeof(a) ))
	{
		if (a.R_id == i && strcmp(e,a.email) == 0 )
		{
			y=1;
			x : PasswordRules();
			cout<<"\nEnter New Password : ";
			cin>>a.password;
			a.age = 54;
			if (Check_Password(a.password))
			{
				f.seekp( -sizeof(a) ,ios::cur);		
				f.write( (char*)&a , sizeof(Reader) );	
				f.close();
				break;	
			}
			else
			{
				cout<<"\aWrong Password Format!\n";
				cout<<"Enter again!\n";
				goto x;				
			}		
				
		}
	}
	if (y==0)
	{
		cout<<"\aWrong ID or Email!!\n";
		cout<<"What do you want to do ?"<<endl;
		cout<<"1. Try again"<<endl;
		cout<<"2. Back to menu"<<endl;
		cout<<"\nPlease enter your choice :"<<endl;
	    switch(getch())
	    {
	    	case '1':
				ResetPassword();
				break;
			case '2':
				Customer_Menu();
				break;
			default :
				{
					cout<<"\aWrong option!"<<endl;
					Customer_Menu();						
				}					
	     }	
			
	}	
	else
	{
		cout<<"Password Changed Successfully!"<<endl;
		if (getch()==13)
			Customer_Menu();		
	}	
}
int login()
{
	system("cls");
	system("color F9");
	cout<<"------------------------You must be a member for this task!------------------------\n\n";
	cout<<"Enter your login information :\n";
	int i;
	char p[50];	
	cout<<"LOGIN ID : ";
    // To make sure user enters a valid number for login Id
	while(!(cin >> i))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid input.Try again: ";
    }							
	cout<<"PASSWORD : ";
	while(!(cin >> p))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid input.Try again: ";
    }
    fstream f;
    f.open("Readers.txt",ios::in|ios::binary);
    f.seekg(0,ios::beg);
    while(f.read((char*)&a,sizeof(a)))
    {
    	if  ( a.R_id == i && strcmp(a.password,p)==0)
    	{
			f.close();
			system("color F2");
			cout<<"LOGIN SUCCESSFUL!\n";
			cout<<"WELCOME "<<a.name<<" !"<<endl;
			delay(2000);
			return 1;
		}			    		
	}
	f.close();
	system("color Fc");
	cout<<"Invalid User Id or Password!\n";
	cout<<"What do you want to do ?"<<endl;
	cout<<"1. Try again"<<endl;
	cout<<"2. Reset Password"<<endl;
	cout<<"3. Back to menu "<<endl;
	cout<<"\nPlease enter your choice :"<<endl;
    switch(getch())
    {
    	case '1':
			login();
			break;
		case '2':
			ResetPassword();
			break;
		case '3':
			Customer_Menu();
			break;
		default :
			{
				cout<<"\aWrong option!"<<endl;
				Customer_Menu();						
			}					
     }	
		
}
int CheckRId(int i)
{
	fstream f;
	f.open("Readers.txt",ios::in|ios::binary);
	while(f.read( (char*)&a,sizeof(a)) )
	{
		if (i==a.R_id)
			return 1;
	}
	return 0;
}
void DisplayReaders()
{
	system("cls");
	system("color f2");
	int id;
	cout<<"Enter Id to search = ";
	cin>>id;
	cout<<"Searching...."<<endl;
	fstream f;
	f.open("Readers.txt",ios::in|ios::binary);
	f.seekg(0,ios::beg);
	if (f.bad())
		cout<<"Some problem is occuring in file opening..\n";
	
	//delay(1000);
	if (CheckRId(id)==0)      // Not a reader
	{
		cout<<"\aNo Member with given ID exists!\n";
		goto m;
	}		
	system("cls");
	while (f.read( (char*)&a , sizeof(a) ))
	{		
		if (a.R_id == id)
		{
			cout<<"########################################\n";
			cout<<"READER ID     : "<<a.R_id<<endl;
			cout<<"NAME          : "<<a.name<<endl;			
			cout<<"GENDER        : "<<a.gender<<endl;
			cout<<"AGE           : "<<a.age<<endl;
			cout<<"EMAIL         : "<<a.email<<endl;
			cout<<"CONTACT       : "<<a.contact<<endl;
			//cout<<"BOOK ID       : "<<a.book_id<<endl;
			//cout<<"JOINING DATE  : "<<a.joining<<endl;
			cout<<"########################################\n";
			goto m;			
		}			
	}
	m : f.close();
    cout<<"Do you want to see any more Reader records?(Y/N)";
	if (getch()=='y')
		DisplayReaders();
    cout<<"\nPress ENTER to return to main menu\n";	
	if (getch() == 13)
		Lib_Menu();	
	
}
void IssuedRecords()
{
	system("cls");
	system("color F4");
	gotoxy(1,1);
    cout<<"****************************************ISSUED RECORDS*************************************";
    gotoxy(2,2);
    cout<<"ID\t\tNAME\t\tBOOK ID\t\tISSUE DATE\t\tRETURN DATE" ;
    int j=4,i=0;
    fstream f;
	f.open("Readers.txt",ios::in|ios::binary);
	f.seekg(0,ios::beg);
	if (f.bad())
		cout<<"Some problem is occuring in file opening..\n";
    while (f.read( (char*)&a , sizeof(a) ))
	{
    	if (a.book_id == 0)
    	{
    		continue;
		}
		gotoxy(2,j);
		cout<<a.R_id;			
		gotoxy(14,j);
		cout<<a.name;		
		gotoxy(35,j);
		cout<<a.book_id;	
		gotoxy(47,j);
		cout<<a.issued.dd<<" "<<MONTHS[a.issued.mm]<<" "<<a.issued.yy;				
		gotoxy(73,j); 
		cout<<a.duedate.dd<<" "<<MONTHS[a.duedate.mm]<<" "<<a.duedate.yy;											
		j++;
		i++;	
	}
    f.close();
    gotoxy(35,25);
	if (getch()==13)
		Lib_Menu();
	
}
void AllReaders()
{
	
	system("cls");
	system("color F6");
	gotoxy(1,1);
    cout<<"****************************************************READERS RECORDS*************************************************";
    gotoxy(2,2);
    cout<<"ID\t\tNAME\t\tGENDER\t\tEMAIL\t\t\tCONTACT\t\tAGE\tISSUED BOOK ID " ;  // 3 tabs gap
    int j=4,i=0;
    fstream f;
	f.open("Readers.txt",ios::in|ios::binary);
	f.seekg(0,ios::beg);
	if (f.bad())
		cout<<"Some problem is occuring in file opening..\n";
    while (f.read( (char*)&a , sizeof(a) ))
	{
		/* after encountering eof it flags it and finally end it in next iteration
		to avoid duplication of last book record this statement is used rather than while(f.eof()) */
    	gotoxy(2,j);
		cout<<a.R_id;			
		gotoxy(10,j);
		cout<<a.name;		
		gotoxy(35,j);
		cout<<a.gender;	
		gotoxy(40,j);
		cout<<a.email;				
		gotoxy(70,j); 
		cout<<a.contact;		
		gotoxy(87,j);
		cout<<a.age;				
		gotoxy(103,j);
		cout<<a.book_id;				
		j++;
		i++;	
	}
	gotoxy(3,25);
    cout<<"Total Readers = "<<i;
    f.close();
    gotoxy(35,25);
	if (getch()==13)
		Lib_Menu();
}

void LibMembership()
{
    
	srand(time(NULL));      // initialize random seed 
	system("cls");    
	cout<<"***************Thank you for joining our family!***************\n\n";	
	cout<<"Please fill in your information....\n";	
	cout<<"We will not share any of your personal information\n";
	delay(1000);	
	cout<<"NAME : ";
	cin.getline(a.name,50);                  // to take space separated input 
	cout<<"Age : ";
	while(!(cin >> a.age))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input.Try again : ";
    }
	cout<<"GENDER (M/F/T) : ";
	while (1)
	{
		cin>>a.gender;	
    	if (a.gender == 'M'||a.gender == 'F'||a.gender == 'T')    	
    		break;  		
	}	
	while(1)
	{
		cout<<"EMAIL : ";
		cin>>a.email;
		if (Check_Email(a.email))
			break;
		else		
			cout<<"Invalid Email! ";		
	}	
	cout<<"Phone No : ";
	while(!(cin >> a.contact))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input.Try again : ";
    }	
	PasswordRules();
	while(1)
	{
		cout<<"\nCreate a Password : ";
	    cin>>a.password;
		if ( Check_Password(a.password) )
		{		
			a.R_id = (rand() %1000) + 1000 ;			
			cout<<"Creating Password....\n";
			delay(2500);                              // delay of 2.5 sec		
			cout<<"\aPassword Created successfully!!!\n";
			cout<<"Your login Id = "<<a.R_id<<endl;
			break;
		}
		else
		{
			cout<<"\aInvalid Password Format!\n";		
			cout<<"Please Enter again!\n";
		}
		
	}
	system("color F2");
	fstream f;
	f.open("Readers.txt",ios::out|ios::app|ios::binary);
	
	// writing to file
	if(!f.fail())	
	{
		f.seekg(0,ios::end);
		f.write( (char*)&a ,sizeof(Reader) );
	}
	else
	{
		cout<<"\nOperation failed!\n";
		Customer_Menu();
	}	
	cout<<"\nCongratulations!\nYou are now a member of Dreams Library!!\n";
	f.close();	
	if ( getch()==13 )
		Customer_Menu() ;		
}

void Password()
{
    system("cls");
    char p[25]="PASSWORD PROTECTED";
    char c,code[10];
    int i=0,j;
    gotoxy(10,4);
    for(j=0;j<20;j++)
    {
    	delay(50);
    	printf("*");
    }
    for(j=0;j<20;j++)
	{
	   delay(50);
	   cout<<p[j] ;
	}
   for(j=0;j<20;j++)
   	{
   	   delay(50);
   	   printf("*");
   	}
    gotoxy(10,10);
    gotoxy(15,7);
    
    cout<<"Enter Password :";
    while(c != 13)                    // 13 -> Carriage return, 8-> Backspace 
    {
		// getch(): It will Accepts a Keystroke and never displays it.(So that it can be used in password).
		c = getch();	
		if (c !=13 && c != 8)
		{
			putch('*');
			code[i] = c;
			i++;
		}
    }
    code[i] = '\0';
    if(strcmp(code,password) == 0)
    {
		gotoxy(15,9);
		system("color F2");
		printf("Password match!");
		gotoxy(17,10);
		printf("Press any key to countinue.....");
		getch();
   }
   else
   {
		gotoxy(15,16);
		printf("\aWarning!! Incorrect Password...Please Enter again");    // \a -> bell sound
		getch();
		Password();
   }
	
}
void close()
{
	cout<<"\n\nThank you for choosing us!!\n\n"<<endl;
	exit(0);
}
void Customer_Menu()
{
	
	system("cls");
	system("color F9");
	int choice,ans ;
	system("cls");
	gotoxy(10,4);
	cout<<"What can we do for you?"<<endl;
	gotoxy(10,5);
	cout<<"======================MENU======================"<<endl; 
	gotoxy(10,6);
	cout<<"|1. Take library membership ";
	gotoxy(10,8);
	cout<<"|2. Issue books";
	gotoxy(10,10);
	cout<<"|3. Return Books";
	gotoxy(10,12);
	cout<<"|4. View Books";
	gotoxy(10,14);
	cout<<"|5. Display Readers";
	gotoxy(10,16);
	cout<<"|6. Main Menu";
	gotoxy(10,18);
	cout<<"|7. Close Application";
	gotoxy(10,20);
	cout<<"================================================"<<endl;
    cout<<"\nPlease enter your choice :"<<endl;
    switch(getch())
    {
    	case '1':
			LibMembership();
			break;
		case '2':
			IssueBooks();
			break;
		case '3':
			ReturnBooks();
		case '4':
			BooksList();
			break;
		case '5':
			DisplayReaders();
			break;
		case '6':
			MainMenu();
			break;
		case '7':
		{
			end();
			close();
	    }						
		default:
		{
			cout<<"\aOOPS! Wrong entry.Enter correct option again : "<<endl;
			delay(1000);	
			Customer_Menu();
		}			
			
    	
	}
	
}
void Lib_Menu()
{
	system("cls");
	system("color F1");
	gotoxy(10,2);
	cout<<"READING IS DREAMING WITH OPEN EYES.....\n";
	int choice ;	
	gotoxy(10,4);
	cout<<"Task to perform ?"<<endl;
	gotoxy(10,5);
	cout<<"======================MENU======================"<<endl; 
	gotoxy(10,6);
	cout<<"1. Add books";
	gotoxy(10,8);
	cout<<"2. Delete books";
	gotoxy(10,10);
	cout<<"3. View Book Records";
	gotoxy(10,12);
	cout<<"4. Edit Book Records";
	gotoxy(10,14);
	cout<<"5. Display Reader Records";
	gotoxy(10,16);
	cout<<"6. View Issued Books Records";
	gotoxy(10,18);
	cout<<"7. Main Menu";
	gotoxy(10,20);
	cout<<"8. Close Application";
	gotoxy(10,22);
	cout<<"================================================"<<endl; 
	cout<<"\nPlease enter your choice :"<<endl;
	switch (getch())
	{
		
		case '1':
			AddBooks();
			break;
		case '2':
			DeleteBooks();
			break;
		case '3':
			ViewBooks();
			break;
		case '4':
			EditBooks();
			break;
		case '5':
			AllReaders();
			break;
		case '6':
			IssuedRecords();
			break;
		case '7':
			MainMenu();
			break;
		case '8':
			{
				end();				
				close();
			}
		default:
			{
				cout<<"\aOOPS! Wrong entry.Enter correct option again : "<<endl;
				delay(1000);	
				Lib_Menu();
			}			
	}		
}
void MainMenu()
{
	int press;
	x : system("cls");
	system("color F3");
	gotoxy(20,4);
	cout<<"PRESS :";
	gotoxy(20,5);
	cout<<"1 - CUSTOMER  ";
	gotoxy(20,6);
	cout<<"2 - AUTHORIZED LIBRARIAN   ";
	gotoxy(20,7);
	cout<<"3 - CLOSE APPLICATION   ";
	switch(getch())
	{
		case '1':
			{
				Customer_Menu();    // Customer_Menu
				break;			
			}
		case '2':
			{
				system("color Fc");		
				Password() ;		//Password protection
				Lib_Menu();         // Librarian Menu				
			}
		case '3':
			{
				end();
				return ;
			}
			
		default:
			{
				system("color Fc");
				cout << "\n\aInvalid Input.Try again : ";
				delay(1000);
				MainMenu();					
			}			
	}
	
}

//Driver function
int main()
{
		
	// file handling to open intro file	
	system("cls");
	system ("color B1");
	fstream f ;
	char read_char;
	f.open("intro.txt");
	while( !f.eof() )
	{
		delay(25);
		read_char = f.get() ;
		cout<<read_char;				
	}	
	f.close() ;
	if (getch()==13)
		MainMenu();	 	
}
