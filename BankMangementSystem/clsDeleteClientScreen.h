#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
#include <iomanip>
#include "clsInputValidate.h";

using namespace std;


class clsDeleteClientScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.firstName;
        cout << "\nLastName    : " << Client.lastName;
        cout << "\nFull Name   : " << Client.fullName;
        cout << "\nEmail       : " << Client.email;
        cout << "\nPhone       : " << Client.phoneNumber;
        cout << "\nAcc. Number : " << Client.getAccountNumber();
        cout << "\nPinCode     : " << Client.pinCode;
        cout << "\nBalance     : " << Client.balance;
        cout << "\n___________________\n";

    }


public:
    static void deleteClient() {

        if (!clsScreen::checkAccessRights(clsUser::pDeleteClient)) {
            return;
        }

        _drawScreenHeader("\tDeleteClientScreen");
        string accountNumber;
        cout << "Please enter the Account Number\n";
        accountNumber = clsInputValidate::readString();
        while (!clsBankClient::isClientExist(accountNumber)) {
            cout << "\nAccount number is not found please choose another one: \n";
            accountNumber = clsInputValidate::readString();
        }
        clsBankClient client = clsBankClient::find(accountNumber);
        _PrintClient(client);
        cout << "\n\nAre you sure you want to delete this client? y/n : ";
        char answer = 'n';
        cin >> answer;

        if (answer == 'y' || answer == 'Y') {

            if (client.deleteClient()) {
                cout << "\nClient deleted successfully :-)\n";
                _PrintClient(client);
            }
            else {
                cout << "\nError client was not deleted\n";
            }
        }
    }

};

