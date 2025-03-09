#pragma once

#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurrenciesListScreen :protected clsScreen
{

private:
    static void PrintCurrencyRecordLine(clsCurrency Currency)
    {

        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
        cout << "| " << setw(6) << left << Currency.CurrencyCode();
        cout << "| " << setw(40) << left << Currency.CurrencyName();
        cout << "| " << setw(18) << left << Currency.Rate();

    }

public:


    static void ShowCurrenciesListScreen()
    {


        vector <clsCurrency> vCurrencys = clsCurrency::GetCurrenciesList();
        string Title = "\t  📈 Currencies List Screen 💹";
        string SubTitle = "\t    (" + to_string(vCurrencys.size()) + ") Currency.";

        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "" << "\n\t______________________________________________________________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "🌍 Country";
        cout << "| " << left << setw(6) << "🆔 Code";
        cout << "| " << left << setw(40) << "🔖 Name";
        cout << "| " << left << setw(8) << "💲 Rate (1$)";
        cout << setw(8) << left << "" << "\n\t______________________________________________________________________________________________________\n" << endl;

        if (vCurrencys.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System! ❌";
        else

            for (clsCurrency Currency : vCurrencys)
            {

                PrintCurrencyRecordLine(Currency);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t______________________________________________________________________________________________________\n" << endl;

    }

};
