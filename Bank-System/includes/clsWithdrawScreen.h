#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n📇 Client Card \n"
			 << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
			 << "🆔 First Name   : " << Client.FirstName << "\n"
			 << "🆔 Last Name    : " << Client.LastName << "\n"
			 << "👤 Full Name    : " << Client.FullName() << "\n"
			 << "📧 Email        : " << Client.Email << "\n"
			 << "📞 Phone        : " << Client.Phone << "\n"
			 << "🏦 Acc. Number  : " << Client.AccountNumber() << "\n"
			 << "🔑 Password     : " << Client.PinCode << "\n"
			 << "💰 Balance      : $" << fixed << setprecision(2) << Client.AccountBalance << "\n"
			 << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
	}

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";
		cout << "\nPlease enter Account Number? ";
		cin >> AccountNumber;
		return AccountNumber;
	}

public:
	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t   Withdraw Screen");

		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		double Amount = 0;
		cout << "\nPlease enter Withdraw amount? ";
		Amount = clsInputValidate::ReadDblNumber();

		cout << "\nAre you sure you want to perform this transaction? ";
		char Answer = 'n'; cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (Client1.Withdraw(Amount))
			{
				cout << "\nAmount Withdrew Successfully ✅\n";
				cout << "\nNew Balance Is: " << Client1.AccountBalance;
			}
			else
			{
				cout << "\nCannot withdraw, Insuffecient Balance🆘\n";
				cout << "\nAmout to withdraw is: " << Amount;
				cout << "\nYour Balance is: " << Client1.AccountBalance;
			}
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}
};
