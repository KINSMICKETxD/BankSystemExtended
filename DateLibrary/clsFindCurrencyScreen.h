#pragma once
#include <string>
#include <iostream>
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "StringLibrary.h"
class clsFindCurrencyScreen : protected clsScreen
{

private:
	static void _printCurrencyCard(clsCurrency currency) {
        cout << "\Currency Card:";
        cout << "\n___________________";
        cout << "\nCountry     : " << currency.getCountry();
        cout << "\nCode        : " << currency.getCurrencyCode();
        cout << "\nName        : " << currency.getCurrencyName();
        cout << "\nRate(1$)    : " << currency.getCurrencyRate();
        cout << "\n___________________\n";
	}



public:

    static void showFindCurrencyScreen(){

        string Title = "\t  Find Currency Screen";
        _drawScreenHeader(Title);
        string currencyCode;
        cout << "Find By: [1] Code or [2] Country ? ";
        short findChoice = clsInputValidate::readIntNumberBetween(1, 2);
        if (findChoice == 1) {
            cout << "Please enter currency Code ";
            currencyCode = clsInputValidate::readString();
            
            if (!(clsCurrency::findByCode(currencyCode)).isEmpty()) {
                cout << "\n\nCurrency Found :-)\n";
                _printCurrencyCard(clsCurrency::findByCode(currencyCode));

            }
            else {
                cout << "\n\nCurrency Not Found :-(\n";
            }
        }
        else {
            cout << "Please Enter Country Name: ";
            currencyCode = clsInputValidate::readString();
            if (!(clsCurrency::findByCountry(currencyCode)).isEmpty()) {
                cout << "\n\nCurrency Found :-)\n";
                _printCurrencyCard(clsCurrency::findByCountry(currencyCode));
            }
            else
            {
                cout << "\n\nCurrency Not Found :-(\n";
            }
        }
    }
};

