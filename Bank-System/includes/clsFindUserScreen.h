#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
	{
		cout << "\n🆔 User Card:";
		cout << "\n───────────────────";
		cout << "\n📝 First Name   : " << User.FirstName;
		cout << "\n📝 Last Name    : " << User.LastName;
		cout << "\n📛 Full Name    : " << User.FullName();
		cout << "\n📧 Email        : " << User.Email;
		cout << "\n📞 Phone        : " << User.Phone;
		cout << "\n👤 User Name    : " << User.UserName;
		cout << "\n🔒 Password     : " << User.Password;
		cout << "\n🛠️ Permissions  : " << User.Permissions;
		cout << "\n───────────────────\n";
	}

public:

    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("\t  Find User Screen");

        string UserName;
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);

        if (!User1.IsEmpty())
        {
            cout << "\nUser Found : ✅\n";
        }
        else
        {
            cout << "\nUser Was not Found \n";
        }

        _PrintUser(User1);
    }

};
