#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
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
        cout << "\nPassword    : " << Client.pinCode;
        cout << "\nBalance     : " << Client.balance;
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

public:

    static void ShowWithdrawScreen()
    {
        _drawScreenHeader("\t   Withdraw Screen");

        string AccountNumber = _ReadAccountNumber();


        while (!clsBankClient::isClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client1 = clsBankClient::find(AccountNumber);
        _PrintClient(Client1);


        double Amount = 0;
        cout << "\nPlease enter Withdraw amount? ";
        Amount = clsInputValidate::readDoubleNumber();

        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client1.withdraw(Amount))
            {
                cout << "\nAmount Withdrew Successfully.\n";
                cout << "\nNew Balance Is: " << Client1.balance;
            }
            else
            {
                cout << "\nCannot withdraw, Insuffecient Balance!\n";
                cout << "\nAmout to withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client1.balance;

            }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }

    }

};

