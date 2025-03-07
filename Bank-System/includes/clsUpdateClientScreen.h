#pragma once
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen :protected clsScreen

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

    static void ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

public:

    static void ShowUpdateClientScreen()
    {
		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;
        }

        _DrawScreenHeader("\tUpdate Client Screen");

        string AccountNumber = "";
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
    
        _PrintClient(Client1);
        cout << "\nAre you sure you want to update this client y/n? ";

        char Answer = 'n';  cin >> Answer;
	
        if (Answer == 'y' || Answer == 'Y')
        {
			system("clear");
            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";

            ReadClientInfo(Client1);

            clsBankClient::enSaveResults SaveResult;

            SaveResult = Client1.Save();

            switch (SaveResult)
            {
            case  clsBankClient::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Updated Successfully ✅\n";
              
                _PrintClient(Client1);
                break;
            }
            case clsBankClient::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty ❌";
                break;

            }
            }
        }

    }
};
