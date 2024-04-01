#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
#include <iomanip>
#include "clsInputValidate.h";

using namespace std;
class clsUpdateClientScreen : protected clsScreen
{
private:

    static void readClientInfo(clsBankClient& client) {

        cout << "Enter firstName : ";
        client.firstName = clsInputValidate::readString();
        cout << "Enter lastName : ";
        client.lastName = clsInputValidate::readString();
        cout << "Enter Email : ";
        client.email = clsInputValidate::readString();
        cout << "Enter phone : ";
        client.phoneNumber = clsInputValidate::readString();
        cout << "Enter pinCode : ";
        client.pinCode = clsInputValidate::readString();
        cout << "Enter account balance : ";
        client.balance = clsInputValidate::readDoubleNumber();
    }

    static void _print(clsBankClient client) {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.firstName;
        cout << "\nLastName    : " << client.lastName;
        cout << "\nFull Name   : " << client.fullName;
        cout << "\nEmail       : " << client.email;
        cout << "\nPhone       : " << client.phoneNumber;
        cout << "\nAcc. Number : " << client.getAccountNumber();
        cout << "\nPinCode     : " << client.pinCode;
        cout << "\nBalance     : " << client.balance;
        cout << "\n___________________\n";
    }



public:
	static void updateClient() {

        if (!clsScreen::checkAccessRights(clsUser::pUpdateClients)) {
            return;
        }

        _drawScreenHeader("\tUpdate Client");
        string accountNumber = "";

        cout << "Please enter Client account number : \n";
        accountNumber = clsInputValidate::readString();

        while (!clsBankClient::isClientExist(accountNumber)) {
            cout << "\nAccount number is not found, choose another one : ";
            accountNumber = clsInputValidate::readString();
        }
        clsBankClient client = clsBankClient::find(accountNumber);
        _print(client);

        cout << "\n\nUpdate Client info: ";
        cout << "\n_____________________\n";
        readClientInfo(client);

        clsBankClient::enSaveResults saveResult;
        saveResult = client.save();
        switch (saveResult)
        {
        case clsBankClient::svFailedEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        case clsBankClient::svSucceeded:
            cout << "\nAccount Updated Successfully :-)\n";
            _print(client);
            break;
        default:
            break;
        }
    }

};

