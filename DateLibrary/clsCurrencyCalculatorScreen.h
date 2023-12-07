#pragma once

#include <string>
#include "clsInputValidate.h";
#include "clsCurrency.h"
#include "clsScreen.h"
using namespace std;
class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
	static void _printCurrencyCard(clsCurrency currency) {

        cout << "\nConvert From:";
        cout << "\n___________________";
        cout << "\nCountry     : " << currency.getCountry();
        cout << "\nCode        : " << currency.getCurrencyCode();
        cout << "\nName        : " << currency.getCurrencyName();
        cout << "\nRate(1$)    : " << currency.getCurrencyRate();
        cout << "\n___________________\n";
	}

public:

    static void showCurrencyCalculatorScreen() {
        string Title = "\t  Currency Calculator";
        _drawScreenHeader(Title);
        char answer = 'n';
        do{
            if (answer == 'y') {
                system("cls");
                _drawScreenHeader(Title);
            }
            cout << "Please Enter Currency1 Code: \n";
            string currencyFromCode = clsInputValidate::readString();
            clsCurrency currencyFrom = clsCurrency::findByCode(currencyFromCode);
            while (currencyFrom.isEmpty()) {
                cout << "\nInvalid Currency Code, please Try Again :";
                currencyFromCode = clsInputValidate::readString();
                currencyFrom = clsCurrency::findByCode(currencyFromCode);
            }
            cout << "Please Enter Currency2 Code: \n";
            string currencyToCode = clsInputValidate::readString();
            clsCurrency currencyTo = clsCurrency::findByCode(currencyToCode);
            while (currencyTo.isEmpty()) {
                cout << "\nInvalid Currency Code, please Try Again :";
                currencyToCode = clsInputValidate::readString();
                currencyTo = clsCurrency::findByCode(currencyToCode);
            }
            cout << "\nEnter Amount to Exchange: ";
            double AmountToExchange = clsInputValidate::readDoubleNumber();

            _printCurrencyCard(currencyFrom);
            cout << AmountToExchange << " " << currencyFrom.getCurrencyCode() << " = " << currencyFrom.ConvertToOtherCurrency(AmountToExchange, currencyTo) << " " << currencyTo.getCurrencyCode() << "\n";
            cout << "\nDo you want to perform another Calculation? y/n ? ";
            cin >> answer;
        } while (answer == 'Y' || answer  == 'y');
        
    }
};

