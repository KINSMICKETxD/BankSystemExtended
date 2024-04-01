#pragma once

#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
class clsUpdateCurrencyScreen : protected clsScreen
{

private:

    static void _printCurrencyCard(clsCurrency currency) {
        cout << "\nCurrency Card:";
        cout << "\n___________________";
        cout << "\nCountry     : " << currency.getCountry();
        cout << "\nCode        : " << currency.getCurrencyCode();
        cout << "\nName        : " << currency.getCurrencyName();
        cout << "\nRate(1$)    : " << currency.getCurrencyRate();
        cout << "\n___________________\n";
    }
    static void _updateCurrencyRate(clsCurrency& currency) {
        char answer = 'n';
        cout << "Are you sure you want to update the rate of this Currency y/n?";
        cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            cout << "\nUpdate Currency Rate: ";
            cout << "\n\n_____________________"; 
            cout << "\n\nEnter New Rate:";
            float newRate = clsInputValidate::readDoubleNumber();
            currency.updateCurrencyRate(newRate);
            cout << "\nCurrency Rate Updated Successfully :-)";
            _printCurrencyCard(currency);
        }
    }

public:

    static void showUpdateCurrencyScreen() {
        string Title = "\t  Update Currency Screen";

        _drawScreenHeader(Title);

        cout << "please enter Currency Code: ";
        string currencyCode = clsInputValidate::readString();

        if (!(clsCurrency::findByCode(currencyCode)).isEmpty()) {
            clsCurrency currency = clsCurrency::findByCode(currencyCode);
            _printCurrencyCard(currency);
            _updateCurrencyRate(currency);
        }
        else {
            cout << "\nCurrency Code is Invalid\n";
        }
    }
};

