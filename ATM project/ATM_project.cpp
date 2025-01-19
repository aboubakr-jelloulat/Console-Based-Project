#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

typedef struct	sClient
{
	string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
	bool	ChangeAmount = false;
}	tClient;

typedef enum	eAtmMain
{
	QuickWithdraw 	= 1,
	NormalWithdraw 	= 2,
	Deposit  		= 3,
	CheckBalance	= 4,
	logout			= 5
}	tAtm;

typedef	enum	eAmount
{
	one		= 1,
	two 	= 2,
	three 	= 3,
	four	= 4,
	five	= 5,
	six		= 6,
	seven	= 7,
	eight	= 8,
	nine	= 9
}	tAmount;

sClient	CurrentClient;
const string	f_Client = "clients.txt";

void	ShowAtmMainMenue();
void	QuickWithdrawScreen();
void	login();
void	NormalWithdrawScreen();

vector<string> ft_split(string s1, string seperator)
{
	vector <string> vString;
	int pos = 0;
	string	line;

	while ((pos = s1.find(seperator)) != string::npos)
	{
		line = s1.substr(0, pos);
		if (line != "")
		{
			vString.push_back(line);
		}
		s1.erase(0, pos + seperator.length());
	}
	if (s1 != "")
	{
		vString.push_back(s1);
	}
	return (vString);
}

tClient	ConvertLineToRecord(string Line, string seperator = "#//#")
{
	vector <string> vClient;
	tClient			Client;
	vClient	= ft_split(Line, seperator);

	Client.AccountNumber = vClient[0];
	Client.PinCode = vClient[1];
	Client.Name = vClient[2];
	Client.Phone = vClient[3];
	Client.AccountBalance = stod(vClient[4]);
	return (Client);
}

vector <tClient> LoadClientDataFromFile(string pathname)
{
	fstream				file;
	vector <tClient>	vClient;

	file.open(pathname, ios::in);
	if (file.is_open())
	{
		string Line;
		tClient	Client;
		while (getline(file, Line))
		{
			Client	= ConvertLineToRecord(Line);
			vClient.push_back(Client);
		}
		file.close();
	}
	return (vClient);
}

bool	FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, tClient	&CuurClient)
{
	vector <tClient> Client;

	Client	= LoadClientDataFromFile(f_Client);
	for (tClient &C : Client)
	{
		if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
		{
			CuurClient = C;
			return true;
		}
	}
	return false;
}

short	ReadAtmMainMenueChoice()
{
	short choice;

	do
	{
		cout << "choose what do you want to do [1 to 5] : ";
		cin >> choice;
	} while (choice < 1 || choice > 5);
	return (choice);
}


// ********* 	QuickWithdraw		*****************

short	ReadQuickWithdrawChoice()
{
	short choice;

	do
	{
		cout << "choose what to withdraw from [1] to [8] : ";
		cin >> choice;
	} while (choice < 1 || choice > 9);
	return (choice);
}
string	ConvertRecordToLine(tClient	CurrentClient, string delim = "#//#")
{
	string	line = "";

	line += CurrentClient.AccountNumber + delim;
	line += CurrentClient.PinCode + delim;
	line += CurrentClient.Name + delim;
	line += CurrentClient.Phone + delim;
	line += to_string(CurrentClient.AccountBalance);

	return (line);
}

void	SaveClientDataToFile(string pathname, vector <tClient> vClient) // pass  tClient	&CurrentClient
{
	fstream	file;
	string	line;

	file.open(pathname, ios::out);
	if (file.is_open())
	{
		for (tClient &C : vClient)
		{
			line = ConvertRecordToLine(C);
			file << line << endl;
		}
	}
	file.close(); 
}

bool	IsGraterThenBalance(int	Amount)
{
	return (Amount > CurrentClient.AccountBalance) ? true : false;
}

void	ChangeDepositAndAmount(int Amount)
{
	char	accept;
	vector <tClient>	vClient = LoadClientDataFromFile(f_Client);

    cout << "❗️Are you sure you want perform this transaction? y/n ⁉️?  ";
	cin >> accept;

	if (accept == 'y' || accept == 'Y')
	{
		for (tClient &C : vClient)
		{
			if (C.AccountNumber == CurrentClient.AccountNumber)
			{
				C.AccountBalance += Amount;
				CurrentClient.AccountBalance = C.AccountBalance;
				SaveClientDataToFile(f_Client, vClient);
				cout << endl << "✅Done Successfully. New Balance is :  " << CurrentClient.AccountBalance << endl;
				break;
			}
		}
	}
}

short	getQuickWithDrawAmount(short option)
{
	switch (option)
	{
	case 1 :
		return (20);
	
	case 2 :
		return (50);
	
	case 3 :
		return (100);
	
	case 4 :
		return (200);
	
	case 5 :
		return (400);
	
	case 6 :
		return (600);
	
	case 7 :
		return (800);
	
	case 8 :
		return (1000);

	default :
		return (0);

	}

}

void	QuickWithdrawAmountOption(short QuickWithdrawOption)
{
	short Amount;

	if (QuickWithdrawOption == 9)
		return ; // return to Main Menue
	
	Amount = getQuickWithDrawAmount(QuickWithdrawOption);

	if (IsGraterThenBalance(Amount))
	{
		cout << endl << "⚠️ The Amount exceeds Your Balance. Make Another Choice. ⚠️" << endl;
		cout << "\nPress any key to continue...";
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	cin.get();
		QuickWithdrawScreen();
		return ;
	}
	ChangeDepositAndAmount(Amount * (-1));
	// CurrentClient.AccountBalance -= Amount;
}

void	QuickWithdrawScreen()
{
	system ("clear");
	cout << "=====================================" << endl;
	cout << "💸 Quick Withdraw 💸" << endl;
    cout << "=====================================" << endl;
    cout << "[1] 💵 20\t\t[2] 💵 50" << endl;
    cout << "[3] 💵 100\t\t[4] 💵 200" << endl;
    cout << "[5] 💵 400\t\t[6] 💵 600" << endl;
    cout << "[7] 💵 800\t\t[8] 💵 1000" << endl;
    cout << "[9] 🚪 Exit" << endl;
    cout << "=====================================" << endl;

	cout << "\tYour Balance is : " << CurrentClient.AccountBalance << endl;

	QuickWithdrawAmountOption(ReadQuickWithdrawChoice());
}

// *************** Normal Withdraw **************

int	ReadNomalWithdrawAmount()
{
	int Amount;

	cout << "Enter an amount multipe of 5 's ? ";
	cin >> Amount;
	
	while (Amount % 5 != 0)
	{
		cout << "Enter an amount multipe of 5 's ? ";
		cin >> Amount;
	}
	return (Amount);
}

void	ft_NormalWithdraw()
{
	int Amount = ReadNomalWithdrawAmount();
	if (IsGraterThenBalance(Amount))
	{
		cout << endl << "⚠️ The Amount exceeds Your Balance. Make Another Choice. ⚠️" << endl;
		cout << "\nPress any key to continue...";
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	cin.get();
		NormalWithdrawScreen();
	}
	ChangeDepositAndAmount(Amount * (-1));
}

void	NormalWithdrawScreen()
{
	system ("clear");
	cout << "========================================\n"
		<< "\tNormal Withdraw\n"
		<< "========================================\n" << endl;
	
	ft_NormalWithdraw();
}

// ************  Deposit **********

int	ReadDepositAmount()
{
	int	Amount;

	do
	{
		cout << "Enter a positive Deposit Amount ?  ";
		cin >> Amount;
	} while (Amount < 0);
	return (Amount);
}

void DepositScreen()
{

	cout << "========================================\n"
		<< "\tNormal Normal Withdraw\n"
		<< "========================================\n" << endl;

	ChangeDepositAndAmount(ReadDepositAmount());
}

// ************ CheckBalance **********

void	CheckBalanceScreen()
{
	cout << "========================================\n"
		<< "\tCheck Balance \n"
		<< "========================================\n" << endl;
	
	cout << "\n💹Your Balance is : " << CurrentClient.AccountBalance << endl;
}

// *********   the option ********
void	GoBacktoAtmMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
	ShowAtmMainMenue();
}
void	AtmMainMenueOption(tAtm choose)
{
	switch (choose)
	{
	case tAtm::QuickWithdraw :
	{
		system ("clear");
		QuickWithdrawScreen();
		GoBacktoAtmMenue();
		break;
	}
	case tAtm::NormalWithdraw :
	{
		system ("clear");
		NormalWithdrawScreen();
		GoBacktoAtmMenue();
		break;
	}
	case tAtm::Deposit :
	{
		system ("clear");
		DepositScreen();
		GoBacktoAtmMenue();
		break;
	}
	case tAtm::CheckBalance :
	{
		system ("clear");
		CheckBalanceScreen();
		GoBacktoAtmMenue();
		break;
	}
	case tAtm::logout :
	{
		system ("clear");
		login();
	}
	}
	
}

void	ShowAtmMainMenue()
{
	system ("clear");
	cout << "🏧 ATM Main Menu Screen 🏧" << endl;
    cout << "=========================" << endl;
    cout << "[1] 🚀 Quick Withdraw" << endl;
    cout << "[2] 🏦 Normal Withdraw" << endl;
    cout << "[3] 💰 Deposit" << endl;
    cout << "[4] 📊 Check Balance" << endl;
    cout << "[5] 🔒 Logout" << endl;
    cout << "=========================" << endl;
	AtmMainMenueOption((tAtm)ReadAtmMainMenueChoice());
}

// ********* login part *****************

bool	LoginClientInfo(string AccountNumber, string PinCode)
{
	return (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient)) ? true : false;
}

void	login()
{
	string	AccountNumbre, PinCode;
	bool	IsFailLogin = false;

	do
	{

		system ("clear");

		cout << "╔════════════════════════════════════════════════════════════════════════════╗" << endl;

    	cout << "║ 🔐  WELCOME TO THE BANK ATM - PLEASE LOGIN  🔐                             ║" << endl;

    	cout << "║────────────────────────────────────────────────────────────────────────────║" << endl;

		if (IsFailLogin)
			cout << "\n🆘Invalide Account Number / Pin Code ⚠️" << endl;

		cout << "\nEnter Account Number? ";
		cin >> AccountNumbre;

		cout << "Enter Pin? ";
		cin >> PinCode;

		IsFailLogin = !LoginClientInfo(AccountNumbre, PinCode);

	} while (IsFailLogin);
	ShowAtmMainMenue();
}

int main(void)
{
	login();
	
    return 0;
}
