#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string>
#include<iomanip>
#include<windows.h>
#include<stdlib.h>
#define clrscr() system("cls");
using namespace std;
                    //Header Files Used
class book
{
   char bno[6];
   char bname[50];
	char aname[50];
  public:
   void newbook()
	{
		cout<<"\nCREATING NEW BOOK RECORD\n";
		cout<<"\nEnter The Book No.: ";
		cin>>bno;
		cout<<"\n\nEnter Name of The Book: ";
		gets(bname);
		cout<<"\n\nEnter Author's Name: ";
		gets(aname);
		cout<<"\n\n\nNew Book Record Created";
	}                //Member Function For Creating New Book

	void displaybook()
	{
		cout<<"\nBook No.: "<<bno;
		cout<<"\nBook's Name: ";
		puts(bname);
		cout<<"Author's Name: ";
		puts(aname);
	}                //Member Function For Displaying Book

	void editbook()
	{
		cout<<"\nBook No.: "<<bno;
		cout<<"\nEdit Book's Name: ";
		gets(bname);
		cout<<"\nEdit Book's Author's Name: ";
		gets(aname);
	}                //Member Function For Editing Details of Book

	char* retbno()
	{
		return bno;
	}                //Member Function For Returning Book No. Value

	void list()
	{cout<<bno<<setw(30)<<bname<<setw(25)<<aname<<"\n";}
                    //Member Function For Listing All Books

};
                    //Class For Book Ends Here
class student
{
   char admno[6];
	char name[50];
   char stbno[6];
   int token;
public:
	void newstudent()
	{
		clrscr();
	 	cout<<"\nCREATING NEW STUDENT RECORD\n";
		cout<<"\nEnter Admission no.: ";
		cin>>admno;
		cout<<"\n\nEnter Name of The Student: ";
		gets(name);
		token=0;
		stbno[0]='/0';
		cout<<"\n\nNew Student Record Created";
	}                //Member Function For Creating New Student

	void displaystudent()
	{
		cout<<"\nAdmission No.: "<<admno;
		cout<<"\nStudent Name: ";
		puts(name);
		cout<<"\nNo. of Books issued: "<<token;
		if(token==1)
			cout<<"\nBook No.: "<<stbno;
	}                //Member Function For Displaying Student

	void editstudent()
	{
		cout<<"\nAdmission No.: "<<admno;
		cout<<"\nEdit Student's Name: ";
		gets(name);
	}                //Member Function For Editing Student

   void getstbno(char n[])
   {
      strcpy(stbno,n);
   }                //Member Function To Assign Book No. To Students

	char* retadmno()
	{
		return admno;
	}                //Member Function To Return Students' Admission No.

	char* retstbno()
	{
		return stbno;
	}                //Member Function To Return Students' Book No.

	int rettoken()
	{
		return token;
	}                //Member Function To Return Token


	void addtoken()
	{token=1;}       //Member Function To Add Token When Book Issued

	void resettoken()
	{token=0;}       //Member Function To Reset Token When Book Deposited

             void list()
	{cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<"\n";}
                    //Member Function To List All The Books

};                  //Class For Student Ends Here

fstream fp,fp1,fp2;
book bk;
student st;         //Global Declaration for Class And Stream Objects

void writebook()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	{
		clrscr();
		bk.newbook();
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\nAdd more records?(y/n)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}                   //Function To Make New Book Record In A File

void writestudent()
{
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		st.newstudent();
		fp.write((char*)&st,sizeof(student));
		cout<<"\n\nAdd more records?(y/n)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}
                    //Function To Make New Student Record In A File
void specificbook(char n[])
{
	cout<<"\nBOOK DETAILS\n";
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
         flag=1;
			bk.displaybook();
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nBook Record Does Not Exist";
	getch();
}
                    //Function To Search For Specific Book Record In A File

void specificstudent(char n[])
{
	cout<<"\nSTUDENT DETAILS\n";
	int flag=0;
	fp.open("student.dat",ios::in);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
         flag=1;
			st.displaystudent();

		}
	}

	fp.close();
	if(flag==0)
    		cout<<"\n\nStudent Record Does Not Exist";
 	getch();
}
                    //Function To Search For Specific Student Record In A File
void modifybook()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFYING BOOK REOCORD";
	cout<<"\n\n\tEnter The Book No.: ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
         found=1;
			bk.displaybook();
			cout<<"\nEnter New Details of The book\n";
			bk.editbook();
			int pos=-1*sizeof(bk);
		    	fp.seekp(pos,ios::cur);
		    	fp.write((char*)&bk,sizeof(book));
		    	cout<<"\n\n\tBook Record Modified";
	   }
	}

    	fp.close();
    	if(found==0)
    		cout<<"\n\nBook Record Not Found";
    	getch();
}                                                                    //Function To Modify Book Record In A File
void modifystudent()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFYING STUDENT RECORD";
	cout<<"\n\n\tEnter Admission No. Of The Student";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.displaystudent();
			cout<<"\nEnter The New Details of Student\n";
			st.editstudent();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n\n\tStudent Record Modified";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\nStudent Record Not Found ";
	getch();
}                                                                //Function To Modify Student Record In A File
void deletestudent()
{
	char n[6];
	int flag=0;
	clrscr();
    	cout<<"\n\n\n\tDELETING STUDENT RECORD";
    	cout<<"\n\nEnter Admission No. of Student To be Deleted: ";
    	cin>>n;
    	fp.open("student.dat",ios::in|ios::out);
    	fstream fp2;
    	fp2.open("Temp.dat",ios::out);
    	fp.seekg(0,ios::beg);
    	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
	     		fp2.write((char*)&st,sizeof(student));
      else
	   	   flag=1;
	}

	fp2.close();
    	fp.close();
    	remove("student.dat");
    	rename("Temp.dat","student.dat");
    	if(flag==1)
     		cout<<"\n\n\tRecord Successfully Deleted";
    	else
     		cout<<"\n\nStudent Record Not found";
    	getch();  }                                                 //Function To Delete Book Record From A File
void deletebook()
{
	char n[6],
   flag=0;
	clrscr();
	cout<<"\n\n\n\tDELETING BOOK RECORD";
	cout<<"\n\nEnter Book no. of Book To be Deleted: ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)!=0)
             fp2.write((char*)&bk,sizeof(book));
      else
             flag=1;

	}

	fp2.close();
    	fp.close();
    	remove("book.dat");
    	rename("Temp.dat","book.dat");
    	if(flag==1)
     		cout<<"\n\n\tRecord Successfully Deleted";
    	else
     		cout<<"\n\nBook Record Not found";
    	getch();  }                                                       //Function To Delete Student Record From A File
void allstudent()
{
	clrscr();
     	fp.open("student.dat",ios::in);
     	if(!fp)
     	{
       		cout<<"FILE COULD NOT BE OPENED OR WAS NOT FOUND";
       		getch();
       		return;
     	}

	cout<<"\n\n\t\tLIST OF STUDENTS\n\n";
	cout<<"**************************************************************\n";
	cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Books Issued"<<"\n";
	cout<<"**************************************************************\n";

	while(fp.read((char*)&st,sizeof(student)))
	{
		st.list();
	}

	fp.close();
	getch();
}
                    //Function To Display List Of Student Records In A File




void allbook()
{
	clrscr();
	fp.open("book.dat",ios::in);
	if(!fp)
	{
		cout<<"FILE COULD NOT BE OPENED OR WAS NOT FOUND";
       		getch();
       		return;
     	}

	cout<<"\n\n\t\tLIST OF BOOKS\n\n";
	cout<<"**************************************************************\n";
	cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
	cout<<"**************************************************************\n";

	while(fp.read((char*)&bk,sizeof(book)))
	{
		bk.list();
	}
     	fp.close();
     	getch();
}
                    //Function To Display List Of Book Records Record In A File





void issuebook()
{
	char sn[6],bn[6];
	int found=0,flag=0;
	clrscr();
	cout<<"\n\nISSUING BOOK";
	cout<<"\n\n\tEnter Student's Admission No.: ";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
    	fp1.open("book.dat",ios::in|ios::out);
    	while(fp.read((char*)&st,sizeof(student)) && found==0)
       	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{
		      		cout<<"\n\n\tEnter Book No.: ";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
				{
			   		if(strcmpi(bk.retbno(),bn)==0)
					{
						bk.displaybook();
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
                  int pos=-1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\t Book Issued Successfully\n\nNote: Please Write the Current Date on the Backside of the Book and Submit it \n within 15 Days or else Fine of Rs. 1 for each Day Exceeded";
					}
		    		}
		  		if(flag==0)
		    			cout<<"Book No. Does Not Exist";
			}
	    		else
		  		cout<<"The Last Book Has Not Been Returned";

		}
	}
      	if(found==0)
		cout<<"Student Record Does Not Exist";
	getch();
  	fp.close();
  	fp1.close();
}
                    //Function To Issue Book To A Student









void depositbook()
{
    char sn[6];
    int found=0,flag=0,day,fine;
    clrscr();
    cout<<"\n\nDEPOSITING BOOK";
    cout<<"\n\n\tEnter Student’s Admission No.: ";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
	    if(strcmpi(st.retadmno(),sn)==0)
     {
		    found=1;
		    if(st.rettoken()==1)
       {
			while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			{
			   if(strcmpi(bk.retbno(),st.retstbno())==0)
			 {
				bk.displaybook();
				flag=1;
				cout<<"\n\nBook deposited in no. of days";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*1;
				   cout<<"\n\nFine to be Deposited: $"<<fine<<" CAD";
				}
					st.resettoken();
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&st,sizeof(student));
					cout<<"\n\n\t Book deposited successfully";
          }
          }
          if(flag==0)
          cout<<"\n No book was found.";
        }
		 else
			cout<<"No book was issued";
		}
    }
      if(found==0)
	cout<<"Student Record Does Not Exist";
	getch();
  fp.close();
}
                                    //Function For Book To Be Deposited By A Student








void intro()
{
	clrscr();
	cout<<"\n\n\t\t\tLIBRARY MANAGEMENT SYSTEM";
	cout<<"\n\n\t\t\tMODIFIED BY: MAHTAB MOHAMMED";
	cout<<"\n\n\t\t\tCARLETON UNIVERSITY";
	getch();
}
                                         //Introduction Function
void adminmenu()
{
	clrscr();
	int ch2;
	cout<<"\n\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS' RECORDS";
	cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT'S RECORD";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.CREATE BOOK RECORD";
	cout<<"\n\n\t7.DISPLAY ALL BOOKS' RECORDS ";
	cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK'S RECORD ";
	cout<<"\n\n\t9.MODIFY BOOK RECORD ";
	cout<<"\n\n\t10.DELETE BOOK RECORD ";
	cout<<"\n\n\t11.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
	cin>>ch2;
	switch(ch2)
	{
    		case 1:
                clrscr();
	    		    writestudent();
                break;
    		case 2:
                allstudent();
                break;
    		case 3:{
	       		 char n[6];
	       		 clrscr();
	       		 cout<<"\n\n\tPlease Enter Admission No.: ";
	       		 cin>>n;
	       		 specificstudent(n);
	       		 break;
                }
         case 4:
                modifystudent();
                break;
         case 5:
                deletestudent();
                break;
          case 6:
                clrscr();
                writebook();
                break;
           case 7:
                allbook();
                break;

       case 8:{
	       		 char n[6];
	       		 clrscr();
	       		 cout<<"\n\n\tPlease Enter Book No.: ";
	       		 cin>>n;
	       		 specificbook(n);
	       		 break;
                 }
         case 9:
                modifybook();
                break;
         case 10:
                 deletebook();
                 break;
          case 11:
                 return;
         default:
                 cout<<"\a";
   	}
   	adminmenu();
}                                                                             //Adminstartor Menu Function

int main()
{
	char ch;
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. BOOK ISSUE";
		cout<<"\n\n\t02. BOOK DEPOSIT";
	  	cout<<"\n\n\t03. ADMINISTRATOR MENU";
	  	cout<<"\n\n\t04. EXIT";
	  	cout<<"\n\n\tPlease Select Your Option (1-4) ";
	  	cin>>ch;
	  	switch(ch)
	  	{
			case '1':
                  clrscr();
                  issuebook();
			   	   break;
		  	case '2':
                  depositbook();
			    	   break;
		  	case '3':
                  adminmenu();
				      break;
		  	case '4':
                  exit(0);
		  	default :
                  cout<<"\a";
		}
   }while(ch!='4');
}
                                  //Void Main And Main Menu Function
