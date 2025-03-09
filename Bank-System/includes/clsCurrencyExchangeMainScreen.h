#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"

using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{

private:
	enum enCurrenciesMainMenueOptions
	{
		eListCurrencies = 1,
		eFindCurrency = 2,
		eUpdateCurrencyRate = 3,
		eCurrencyCalculator = 4,
		eMainMenue = 5
	};

	static short ReadCurrenciesMainMenueOptions()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return Choice;
	}

	static void _GoBackToCurrenciesMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue... ↩️\n";
		cin.ignore();
		cin.get();
		ShowCurrenciesMenue();
	}

	static void _ShowCurrenciesListScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyRateScreen()
	{
		cout << "\nUpdate Currency Rate Screen Will Be Here.\n";
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		cout << "\nCurrency Calculator Screen Will Be Here.\n";
	}

	static void _PerformCurrenciesMainMenueOptions(enCurrenciesMainMenueOptions CurrenciesMainMenueOptions)
	{

		switch (CurrenciesMainMenueOptions)
		{
		case enCurrenciesMainMenueOptions::eListCurrencies:
		{
			system("clear");
			_ShowCurrenciesListScreen();
			_GoBackToCurrenciesMenue();
			break;
		}

		case enCurrenciesMainMenueOptions::eFindCurrency:
		{
			system("clear");
			_ShowFindCurrencyScreen();
			_GoBackToCurrenciesMenue();
			break;
		}

		case enCurrenciesMainMenueOptions::eUpdateCurrencyRate:
		{
			system("clear");
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrenciesMenue();
			break;
		}

		case enCurrenciesMainMenueOptions::eCurrencyCalculator:
		{
			system("clear");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrenciesMenue();
			break;
		}

		case enCurrenciesMainMenueOptions::eMainMenue:
		{

		}
		}
	}

public:
	static void ShowCurrenciesMenue()
	{

		system("clear");
		_DrawScreenHeader("    📈 Currancy Exhange Main Screen 💹");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Currency Exhange Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformCurrenciesMainMenueOptions((enCurrenciesMainMenueOptions)ReadCurrenciesMainMenueOptions());
	}
};
