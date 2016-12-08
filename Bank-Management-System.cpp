#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//*********************************************//
//         Main class used                     //
//*********************************************//

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();
	void show_account();
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacno() const;
	int retdeposit() const;
	char rettype() const;
};

void account::create_account()
{
	cout << "\nEnter the account No. :";
	cin >> acno;
	cout << "\n\nEnter the name of the account holder :";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nEnter the type of acount (C/S) :";
	cin >> type;
	type=toupper(type);
	cout << "\nEnter the initial amount (>=500 for Savings | >=1000 for Checking) :";
	cin >> deposit;
	cout << "\n\n\nAccount Created ...";
}

void account::show_account() const
{
	cout << "Account No. : " << acno;
	cout << "\nAccount Holder Name : ";
	cout << name;
	cout << "\nType of Account : " << type;
	cout << "\nBalance : " << deposit;
}

void account::modify()
{
	cout << "\nAccount No. : " << acno;
	cout << "\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nModify Type of Account : ";
	cin >> type;
	type=toupper(type);
	cout << "\nModify Balance : ";
	cin >> deposit;
}

void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report() const
{
	cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << end1;
}

int account::retacno() const
{
	return acno;
}

int account::rettype() const
{
	return type;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}

//***********************************************//
//  Function Declaration                         //
//***********************************************//

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();

//***************************************************//
//  Main Function of the Program                     //
//***************************************************//

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t01. NEW ACCOUNT";
		cout << "\n\n\t02. DEPOSIT AMOUNT";
		cout << "\n\n\t03. WITHDRAW AMOUNT";
		cout << "\n\n\t04. BALANCE INQUIRY";
		cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout << "\n\n\t06. CLOSE AN ACCOUNT";
		cout << "\n\n\t07. MODIFY AN ACCOUNT";
		cout << "\n\n\t08. EXIT";
		cin >> ch;
		system("cls");
		switch(ch)
		{
			case '1':
				write_account();
				break;
			case '2':
				cout << "\n\n\tEnter The Account No. : "; cin >> num;
				deposit_withdraw(num, 1);
				break;
			case '3':
				cout << "\n\n\tEnter The Account No. : "; cin >> num;
				deposit_withdraw(num, 2);
				break;
			case '4':
				cout << "\n\n\tEnter The Account No. : "; cin >> num;
				display_sp(num);
				break;
			case '5':
				display_all();
				break;
			case '6':
				cout << "\n\n\tEnter The Account No. : "; cin >> num;
				delete_account(num);
				break;
			case '7':
				cout << "\n\n\tEnter The Account No. : "; cin >> num;
				modify_account(num);
				break;
			case '8':
				cout << "\n\n\tThanks for using bank management system";
				break;
			default : cout << "\a";
		}
		cin.ignore();
		cin.get();
	}whole (ch!='8');
	return 0;
}

//*************************************************//
// Function to write in file                       //
//*************************************************//

void write_accoutn()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//*******************************************************//
// Function to read specific file from record            //
//*******************************************************//

void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if(!inFile)
	{
		cout << "File could not be opened !! Press any key ...";
		return;
	}
	cout << "\nBALANCE DETAILS\n";

	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if(flag == false)
		cout << "\n\nAccount number does not exist";
}

//*******************************************************//
// Function to modify record of file                     //
//*******************************************************//

void modify_account(int n)
{
	bool found = false;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout << "File could not be open !! Press any key...";
		return;
	}
	while(!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno() == n)
		{
			ac.show_account();
			cout << "\n\nEnter The New Details of The Account" << end1;
			ac.modify();
			int pos = (-1) * static_cast<itn>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if(found == false)
		cout << "\n\n Record Not Found ";
}

//*****************************************************//
//  function to delete record of file                  //
//*****************************************************//

void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if(!inFile)
	{
		cout << "File could not be opened !! Press any key ...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno() !=  n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\tRecord Deleated ...";
}

//******************************************************************//
//  Function to display all accounts deposit list                   //
//******************************************************************//

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if(!inFile)
	{
		cout << "File could not be opened !! Press any key ...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "=================================================="
	cout << "A/c No.      NAME           TYPE  BALANCE\n";
}