#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDepositScreen : protected clsScreen
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
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

public:

    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t   Deposit Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        double Amount = 0;
        cout << "\nPlease enter deposit amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n'; cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            Client1.Deposit(Amount);
            cout << "\nAmount Deposited Successfully ✅\n";
            cout << "\nNew Balance Is: " << Client1.AccountBalance;
        }
        else
        {
            cout << "\nOperation was cancelled 🆘\n";
        }

    }

};
