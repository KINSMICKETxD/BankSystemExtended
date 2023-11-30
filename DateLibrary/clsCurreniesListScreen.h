#pragma once
#include <string>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;
class clsCurreniesListScreen : protected clsScreen
{
private:

    static void _PrintCurrencyRecord(clsCurrency currency)
    {

        cout << setw(8) << left << "" << "| " << setw(30) << left << currency.getCountry();
        cout << "| " << setw(10) << left << currency.getCurrencyCode();
        cout << "| " << setw(40) << left << currency.getCurrencyName();
        cout << "| " << setw(20) << left << currency.getCurrencyRate();
    }

public:

    static void showCurrencyList() {
        string title = "\tCurrencies List Screen";
        vector<clsCurrency> vCurrencies = clsCurrency::getAllUSDRates();
        string subTitle = "\t (" + to_string(vCurrencies.size()) + ") Currency";

        _drawScreenHeader(title, subTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(10) << "Code";
        cout << "| " << left << setw(40) << "Name";
        cout << "| " << left << setw(20) << "Rate/(1$)";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vCurrencies.size() == 0) {
            cout << "\t\t\t\tNo Currency Available In the System!";
        }
        else {
            for (clsCurrency& c : vCurrencies) {
                _PrintCurrencyRecord(c);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
        
    }
};

