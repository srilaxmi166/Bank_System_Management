/********************************************************************************************
                                  BANK SYSTEM MANAGEMENT        
*********************************************************************************************/

//headerfiles

#include<fstream>
#include<ctype.h>
#include<iomanip>
#include<conio.h>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>

using namespace std;

// class Bank created 
class Bank
{
	private:

		int Account_number;
		char name[50];
		long deposit;
		char type[10];

	public:

		void create_account();			//function to create a new bank account
		void Display_Account_Details();	//function to show details of account
		void Deposit_Amount(int);		//function to deposit amount
		void Withdraw_Amount(int);		//function to withdraw amount
		void report();              	//function to show data in tabular format
		int retAccount_number();	    //function to return account number
		int retdeposit();				//function to return balance amount
};         

//class ends here

//function definations

void Bank::create_account()
{
	std::cout<<"\nEnter The account No. :";
	cin>>Account_number;
	std::cout<<"\n\nEnter The Name of The account Holder : ";
	fflush(stdin);
	cin.getline(name,30);
	std::cout<<"\nEnter Type of The account : ";
	cin.getline(type,30);
	std::cout<<"\nEnter The Initial deposit amount: ";
	cin>>deposit;
	std::cout<<"\n\n\nACCOUNT SUCCESSFULLY CREATED";
}

void Bank::Display_Account_Details()
{
	std::cout<<"\nAccount No. : "<<Account_number;
	std::cout<<"\nAccount Holder Name : "<<name;
	std::cout<<"\nType of Account : "<<type;
	std::cout<<"\nBalance amount : "<<deposit;
}


void Bank::Deposit_Amount(int x)
{
	deposit+=x;
}

void Bank::Withdraw_Amount(int x)
{
	deposit-=x;
}

void Bank::report()
{
	std::cout<<Account_number<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(10)<<deposit<<endl;
}

int Bank::retAccount_number()
{
	return Account_number;
}

int Bank::retdeposit()
{
	return deposit;
}


//Declarations of functions 

void write_account();				//function to write record in binary file
void display_sp(int);				//function to display account details given by user
void delete_account(int);			//function to delete record of file
void display_all();					//function to display all account details
void deposit_withdraw(int, int);    // function to desposit/withdraw amount for given account
void Introduction();				//Introduction screen function
void Account_Exists(int);			//function to check if account exist

//Main driver code

int main()
{
	char ch;
	int num;
	system("cls");
	Introduction();
	do
	{
		system("cls");
		std::cout<<"\n\n\n\tMAIN MENU";
		std::cout<<"\n\n\t01. NEW ACCOUNT";
		std::cout<<"\n\n\t02. DEPOSIT AMOUNT";
		std::cout<<"\n\n\t03. WITHDRAW AMOUNT";
		std::cout<<"\n\n\t04. BALANCE ENQUIRY";
		std::cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		std::cout<<"\n\n\t06. DELETE ACCOUNT";
		std::cout<<"\n\n\t07. CHECK IF ACCOUNT EXISTS ";
		std::cout<<"\n\n\t08. EXIT";
		std::cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			std::cout<<"\n\n\tEnter The account No. : "; 
			cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			std::cout<<"\n\n\tEnter The account No. : "; 
			cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			std::cout<<"\n\n\tEnter The account No. : "; 
			cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			std::cout<<"\n\n\tEnter The account No. : ";
			cin>>num;
			delete_account(num);
			break;
		 case '7':
			std::cout<<"\n\n\tEnter The account No. : "; 
			cin>>num;
			Account_Exists(num);
			break;
		 case '8':
			std::cout<<"\n\n\tThanks for using bank management system";
			break;
		 default :std::cout<<"Invalid - Enter any option from 1-8\n";
		}
		getch();
    }while(ch!='8');
	return 0;
}
//main function ends here


//function to write in file

void write_account()

{
	Bank ac;
	ofstream outFile;
	outFile.open("bankdetails.txt",ios::binary|ios::app);
	ac.create_account();
	outFile.write((char *) &ac, sizeof(Bank));
	outFile.close();
}


//function to read a record

void display_sp(int n)
{
	Bank ac;
	int flag=0;
	ifstream inFile;
    inFile.open("bankdetails.txt",ios::binary);
	if(!inFile)
	{
		std::cout<<"File cannot be opened !! Press any Key...";
		return;
	}
	std::cout<<"\nBALANCE DETAILS\n";
    while(inFile.read((char *) &ac, sizeof(Bank)))
	{
		if(ac.retAccount_number()==n)
		{
			ac.Display_Account_Details();
			flag=1;
		}
	}
    inFile.close();
	if(flag==0)
		std::cout<<"\n\nAccount does not exist";
}

//function to check if account exist account

 void Account_Exists(int n)
{
 	Bank ac;
	int flag=0;
	ifstream inFile;
    inFile.open("bankdetails.txt",ios::binary);
	if(!inFile)
	{
		std::cout<<"File cannot be opened !! Press any Key...";
		return;
	}
    while(inFile.read((char *) &ac, sizeof(Bank)))
	{
		if(ac.retAccount_number()==n)
		{
			flag=1;
		}
	}
   
	if(flag==0)
		std::cout<<"\n\nAccount does not exist";
	else
		std::cout<<"\n\nAccount exists ";

	inFile.close();
 }
 

 //function to delete a account

void delete_account(int n)
{
	Bank ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("bankdetails.txt",ios::binary);
	if(!inFile)
	{
		std::cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("temporary.txt",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &ac, sizeof(Bank)))
	{
		if(ac.retAccount_number()!=n)
		{
			outFile.write((char *) &ac, sizeof(Bank));
		}
	}
    inFile.close();
	outFile.close();
	remove("bankdetails.txt");
	rename("temporary.txt","bankdetails.txt");
	std::cout<<"\n\n\tRecord Deleted ..";
}

//function to display all accounts

void display_all()
{
	Bank ac;
	ifstream inFile;
	inFile.open("bankdetails.txt",ios::binary);
	if(!inFile)
	{
		std::cout<<"File could not be open !! Press any Key...";
		return;
	}
	std::cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	std::cout<<"====================================================\n";
	std::cout<<"A/c no.      NAME           Type        Balance\n";
	std::cout<<"====================================================\n";
	while(inFile.read((char *) &ac, sizeof(Bank)))
	{
		ac.report();
	}
	inFile.close();
}

// function to deposit and withdraw

void deposit_withdraw(int n, int option)
{
	int amt;
	int found=0;
	Bank ac;
	fstream File;
    File.open("bankdetails.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		std::cout<<"File could not be open !! Press any Key...";
		return;
	}
    while(File.read((char *) &ac, sizeof(Bank)) && found==0)
	{
		if(ac.retAccount_number()==n)
		{
			ac.Display_Account_Details();
			if(option==1)
			{
				std::cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				std::cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.Deposit_Amount(amt);
			}
		    if(option==2)
			{
				std::cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				std::cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				
		    }
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(Bank));
			std::cout<<"\n\n\t Record Updated";
			found=1;
	       }
	 }
    File.close();
	if(found==0)
		std::cout<<"\n\n Record Not Found ";
}


//Introduction function defination


void Introduction()
{
	std::cout<<"\n\n\n\t  BANK";
	std::cout<<" SYSTEM";
	std::cout<<" MANAGEMENT";
	getch();
}

//Project ends here