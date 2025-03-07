#pragma once
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsFindClientScreen.h"

class clsFindClientScreen :protected clsScreen
{

private :
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

public:

    static void ShowFindClientScreen()
    {
		if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;
        }

        _DrawScreenHeader("\tFind Client Screen");

        string AccountNumber;
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        (!Client1.IsEmpty()) ? cout << "\nClient Found " << endl : cout << "\nClient Was not Found " << endl;
        

        _PrintClient(Client1);
    }

};
