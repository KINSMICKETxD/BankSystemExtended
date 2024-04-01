#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
#include <iomanip>
#include "clsInputValidate.h";
#include "clsScreen.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:
    static void _readClientInfo(clsBankClient& client) {
    
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
    static void addNewClient() {

        if (!clsScreen::checkAccessRights(clsUser::pAddNewClient)) {
            return;
        }

        _drawScreenHeader("\tAddNewClient");
        string accountNumber = "";
        cout << "Please enter an account Number : ";
        accountNumber = clsInputValidate::readString();
        while (clsBankClient::isClientExist(accountNumber)) {
            cout << "\nAccount Number is ALready Used, choose another one: ";
            accountNumber = clsInputValidate::readString();
        }
        clsBankClient client = clsBankClient::getAddNewClientObject(accountNumber);
        _readClientInfo(client);
        clsBankClient::enSaveResults saveResult;

        saveResult = client.save();

        switch (saveResult)
        {
        case clsBankClient::svFailedEmptyObject:
            cout << "\nError account was not saved because it's empty";
            break;
        case clsBankClient::svSucceeded:
            cout << "\nAccount Added successfully :-)\n";
            _print(client);
            break;
        case clsBankClient::failedAccountNumberExist:
            cout << "\nError account was not saved because account number already used!\n";
            break;
        default:
            break;
        }
    }

};

