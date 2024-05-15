//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>//used for file handling 
#include<iomanip>//The header <iomanip> consists of functions that are
  //used to manipulate the output of the C++ program.We can make the output 
 // of any program neater and presentable based on where we want to show it or who is going to use it.

using namespace std;
//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class Admin
{
    int rollno;
    char name[50];
    int phy,chem,bio,eng,urdu;
    float per;
    char Grade;
    int n;
  
public:
    void getdata()
    {
		cout<<endl<<"Enter Student Roll number:  ";
		cin>>rollno;
		cout<<endl<<"Enter the Name of the Student;  ";
		cin>>name;
		cout<<"Enter the marks of physics out of 100:   ";
		cin>>phy;
		cout<<endl<<"Enter the marks of chemistry out of 100:  ";
		cin>>chem;
		cout<<endl<<"Enter the marks of biology out of 100:  ";
		cin>>bio;
		cout<<endl<<"Enter the marks of english out of 100:   ";
		cin>>eng;
		cout<<endl<<"Enter the marks of urdu out of 100:   ";
		cin>>urdu;
		per=(phy+chem+bio+eng+urdu)/5.0;
		if(per>=60)
		{
			Grade='A';
		}
		else if(per>=50&&per<=60)
		{
			Grade='B';
		}
		else if(per>=33&&per<=50)
		{
			Grade='C';
		}
		else
		{
			Grade='F';
		}
		cout<<endl<<"Percentage of student:   "<<per;
		cout<<endl<<"Grade of student:  "<<Grade;
		cout<<endl<<"     Total Marks of Student are:  "<<phy+chem+bio+eng+urdu;
		system("cls");
			
    }

    void showdata()
    {
        cout<<"\t\t\t\tSTUDENT ROLL NUMBER :"<<rollno<<endl<<endl;
        cout<<"\t\t\t\tSTUDENT NAME :"<<name<<endl<<endl;
        cout<<"\t\t\t\tSTUDENT PHYSCIS MARKS :"<<phy<<endl<<endl;
        cout<<"\t\t\t\tSTUDENT CHEMISTRY MARK :"<<chem<<endl<<endl;
        cout<<"\t\t\t\tSTUDENT BIOLOGY MARK :"<<bio<<endl<<endl;
        cout<<"\t\t\t\tSTUDENT URDU MARKS MARK :"<<urdu<<endl<<endl;
        cout<<"\t\t\t\tSTUDENT ENGLISH MARK :"<<eng<<endl<<endl;
        cout<<"\t\t\t\tTOTAL MARKS :"<<phy+chem+bio+eng+urdu<<endl<<endl;
        cout<<"\t\t\t\tPERCENTAGE :"<<per<<endl<<endl;
        cout<<"\t\t\t\tGRADE :"<<Grade;
    }

    void showtabular()
    {
        cout<<rollno<<setw(12)<<name<<setw(10)<<phy<<setw(3)<<chem<<setw(3)<<bio<<setw(3)<<eng<<setw(3)<<urdu<<setw(6)<<per<<"   "<<Grade<<endl;
    }

    int  retrollno()
    {
        return rollno;
    }

};         //class ends here



//***************************************************************
//      global declaration for stream object, object
//****************************************************************

fstream fp;
Admin ad;

//***************************************************************
//      function to write in file
//****************************************************************

void writedata()
{
    fp.open("name.dat",ios::out|ios::app|ios::binary);
    ad.getdata();
    fp.write((char*)&ad,sizeof(Admin));
    fp.close();
    cout<<"\n\nstudent record Has Been Created ";
    getch();
}


//***************************************************************
//      function to read all records from file
//****************************************************************


void displayall()
{
    system("cls");
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("name.dat",ios::in|ios::binary);
    while(fp.read((char*)&ad,sizeof(Admin)))
    {
    	system("color 8");
        ad.showdata();
        cout<<"\n\n====================================\n";
        getch();
    }
    fp.close();
    getch();
}


//***************************************************************
//      function to read specific record from file
//****************************************************************


void displaySP(int n)
{
    int flag=0;
    fp.open("name.dat",ios::in|ios::binary);
    while(fp.read((char*)&ad,sizeof(Admin)))
    {
        if(ad.retrollno()==n)
        {
            system("cls");
            system("color 4");
            ad.showdata();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)
        cout<<"\n\nrecord not exist";
    getch();
}


//***************************************************************
//      function to modify record of file
//****************************************************************


void modifydata()
{
    int no,found=0;
    system("cls");
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The roll number of student";
    cin>>no;
    fp.open("name.dat",ios::in|ios::out|ios::binary);
    while(fp.read((char*)&ad,sizeof(Admin)) && found==0)
    {
        if(ad.retrollno()==no)
        {
            ad.showdata();
            cout<<"\nPlease Enter The New Details of student"<<endl;
            ad.getdata();
            int pos=(-1)*static_cast<int>(sizeof(ad));
           // int pos=(-1)*sizeof(ad);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&ad,sizeof(Admin));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }
    fp.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    getch();
}



//***************************************************************
//      function to display all students grade report
//****************************************************************

void classResult()
{
    system("cls");
    fp.open("name.dat",ios::in|ios::binary);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Entry Menu to create File";
        cout<<"\n\n\n Program is closing ....";
        getch();
        exit(0);
    }

    cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
    cout<<"====================================================\n";
    cout<<"Roll No. Name          P  C  M  E  CS  %age Grade\n";
    cout<<"====================================================\n";

    while(fp.read((char*)&ad,sizeof(Admin)))
    {
        ad.showtabular();
    }
    fp.close();
    getch();
}




//***************************************************************
//      function to display result menu
//****************************************************************

void result()
{
    int ans,rno;
    char ch;
    system("cls");
    cout<<"\n\n\nRESULT MENU";
    cout<<"\n\n\n1. Class Result\n\n2. Student Report Card\n\n3.Back to Main Menu";
    cout<<"\n\n\nEnter Choice (1/2)? ";
    cin>>ans;
    switch(ans)
    {
    case 1 :
        classResult();
        break;
    case 2 :
    {
        do
        {
            system("cls");
            char ans;
            cout<<"\n\nEnter Roll Number Of Student : ";
            cin>>rno;
            displaySP(rno);
            cout<<"\n\nDo you want to See More Result (y/n)?";
            cin>>ans;
        }
        while(ans=='y'||ans=='Y');

        break;
    }
    case 3:
        break;
    default:
        cout<<"\a";
    }
}




//***************************************************************
//      ENTRY / EDIT MENU FUNCTION
//****************************************************************
void mainPage()
{
    system("cls");
    system("color 5");
    int x;
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
    cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
    cin>>x;
    if(x==1)
    {
    	system("cls");
    	writedata();
	}
	else if(x==2)
	{
		displayall();
	}
	else if(x==3)
	{
		int num;
		system("cls");
		cout<<"      Please enter the roll Number that you want to search:  ";
		cin>>num;
		displaySP(num);
	}
	else if(x==4)
	{
		modifydata();
	}
}


//***************************************************************
//      INTRODUCTION FUNCTION
//***************************************************************

		bool intro()
		{ 
		    system("color a");
			cout<<endl<<endl<<endl<<endl<<endl;
			cout<<endl<<"                    WELCOME TO RESULT MANAGEMENT PROJECT       "<<endl<<endl<<endl;
			cout<<"                             PRESS ENTER TO CONTINUE      "<<endl<<endl<<endl;
			cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
			cout<<"         Made by :"<<endl; 
			cout<<"                 AREEBA WASEEM  "<<endl;
			cin.get();
			
		}

//***************************************************************
//         		AFTER LOGIN FUNCTION
//***************************************************************


bool SecondPage()
{
	int c;
	do
	{
    	cin.ignore();
    	system("cls");
        system("color 5");
        cout<<"\n\n\n\tMAIN MENU";
    	cout<<"\n\n\t01. RESULT MENU";
        cout<<"\n\n\t02. ENTRY/EDIT MENU";
        cout<<"\n\n\t03. EXIT";
        cout<<"\n\n\tPlease Select Your Option (1-3) ";
        cin>>c;
    	if(c==1)
    	{
        	system("cls");
        	result();
		}	
		else if(c==2)
		{
			mainPage();
		}
		else 
		{
			exit(0);
		}
	}
    while(c!='3');
}


//****************************************************************
//           ADMIN LOGIN FUNCTION(READ & COMPARE FROM FILE DATA)
//****************************************************************
	
bool admin()
{
	char c=' ';
	int i=0;//count login attempt
	int a=0;
    int option;
    int count=0;
    system("color 7");
    string name, accountname, password,username;
    cout<<"ARE YOU ADMIN OR USER?"<<endl;
    cout<<"[Press 1] if you are admin"<<endl<<"[Press 2] if you are student"<<endl;
    cout<<"Your Option: ";
    cin>>option;
    if (option == 1)
    {
		char username[20],pass[20];
		ofstream m("passwordfile.txt",ios::app);//creating a .txt file to write user's username and password in it
		cout<<"Enter Username"<<endl;
		cin>>username;
		m<<username<<"\t";
		cout<<"Enter Password"<<endl;
		if()
		int i;
		char a;
		for(i=0;;)
		{
			a=getch();//stores char typed in a
		    if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9'))
		    //check if a is numeric or alphabet
			{
				pass[i]=a;//stores a in pass
				++i;
				cout<<"*";	
	        }
	        if(a=='\b'&&i>=1)//if user typed backspace
	        //i should be greater than 1.
	        {
				cout<<"\b \b";//rub the character behind the cursor.
		        --i;
		    }		        					
			if(a=='\r')//if enter is pressed.
	        {
				password[i]='\0';//null means end of string.
				//here we can even check for minimum digits needed			
		    	break;	
		    }
		}
		m<<pass<<endl;
		cout<<"LOGIN SUCCESSFULL";
		SecondPage();
		m.close();
	}
		
        	/*else 
        	{						
				cout<<"\nSO MANY WRONG ATTEMPTS!!!";
				exit(0);
				return false;
            }*/
	
	//	}
    	else if(option==2)
    	{
    		int s;
    		cout<<"Enter your Roll Number:    ";
    		cin>>s;
    		displaySP(s);
		}
        else 
        {   
            cout << endl << "please enter correct option" << endl;
    	}
	
}

//***************************************************************
//      THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
	intro();
	system("cls");
	admin();
   
}

//***************************************************************
//                      END OF PROJECT
//***************************************************************
