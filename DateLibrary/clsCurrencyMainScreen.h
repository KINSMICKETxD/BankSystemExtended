#pragma once

#include <string>
#include <iomanip>
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsCurreniesListScreen.h"
using namespace std;
class clsCurrencyMainScreen : protected clsScreen  
{
private:

	enum enCurrencyMenueOption{eListCurrencies = 1,eFindCurrency=2,eUpdateRate=3,
	eCurrencyCalculator = 4,eMainMenue=5};

	static enCurrencyMenueOption readCurrencyMainScreenOption() {
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short answer = clsInputValidate::readIntNumberBetween(1, 5);
		return (enCurrencyMenueOption)answer;
	}

	static void _goBacktoCurrencyMainMenueScreen() {
		cout << "\n\nPress any key to go back to Manage Users Menue...";
		system("pause>0");
	}

	static void _showListCurrenciesScreen() {
		//cout << "listCurrencies Code will be here...";
		clsCurreniesListScreen::showCurrencyList();
	}

	static void _showFindCurrencyScreen() {
		cout << "showFindCurrencyScreen code will be here...";
	}

	static void _showUpdateRateScreen() {
		cout << "showUpdateRateScreen code will be here...";
	}

	static void _showCurrencyCalculator() {
		cout << "showCurrencyCalculator code will be here...";
	}

	static void _performeCurrencyMainMenueScreenOption(enCurrencyMenueOption option) {
		switch (option)
		{
		case clsCurrencyMainScreen::eListCurrencies:
		{
			system("cls");
			_showListCurrenciesScreen();
			_goBacktoCurrencyMainMenueScreen();
		}
			break;
		case clsCurrencyMainScreen::eFindCurrency:
			system("cls");
			_showFindCurrencyScreen();
			_goBacktoCurrencyMainMenueScreen();
			break;
		case clsCurrencyMainScreen::eUpdateRate:
			system("cls");
			_showUpdateRateScreen();
			_goBacktoCurrencyMainMenueScreen();
			break;
		case clsCurrencyMainScreen::eCurrencyCalculator:
			system("cls");
			_showCurrencyCalculator();
			_goBacktoCurrencyMainMenueScreen();
			break;
		case clsCurrencyMainScreen::eMainMenue:
			break;
		default:
			break;
		}
	}



public:

	static void showCurrencyMainMenueScreen() {
		string Title = "\tCurrency Exchange Main Screen";

		system("cls");
		_drawScreenHeader(Title);

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Currency Exchange Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_performeCurrencyMainMenueScreenOption(readCurrencyMainScreenOption());

	}
};

