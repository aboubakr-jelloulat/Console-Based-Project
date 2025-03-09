#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyRateScreen :protected clsScreen

{
private:

    static float _ReadRate()
    {
        cout << "\nEnter New Rate: ";
        float NewRate = 0;

        NewRate = clsInputValidate::ReadFloatNumber();
        return NewRate;
    }

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\n📈 Currency Card:\n";
        cout << "_____________________________\n";
        cout << "\n🌍 Country    : " << Currency.Country();
        cout << "\n🆔 Code       : " << Currency.CurrencyCode();
        cout << "\n🔖 Name       : " << Currency.CurrencyName();
        cout << "\n💲 Rate(1$) = : " << Currency.Rate();
        cout << "\n_____________________________\n";
    }

public:

    static void ShowUpdateCurrencyRateScreen()
    {

        _DrawScreenHeader("\tUpdate Currency Screen ♻️");

        string CurrencyCode = "";

        cout << "\nPlease Enter Currency Code : ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one : ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        _PrintCurrency(Currency);

        cout << "\nAre you sure you want to update the rate of this Currency y/n? ";

        char Answer = 'n';  cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";

            Currency.UpdateRate( _ReadRate());

            cout << "\nCurrency Rate Updated Successfully ✅\n";
            _PrintCurrency(Currency);
        }

    }
};
