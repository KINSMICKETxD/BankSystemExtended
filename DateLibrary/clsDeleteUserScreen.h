#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen :protected clsScreen
{

private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.firstName;
        cout << "\nLastName    : " << User.lastName;
        cout << "\nFull Name   : " << User.fullName;
        cout << "\nEmail       : " << User.email;
        cout << "\nPhone       : " << User.phoneNumber;
        cout << "\nUser Name   : " << User.userName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

public:
    static void ShowDeleteUserScreen()
    {

        _drawScreenHeader("\tDelete User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::readString();
        while (!clsUser::isUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::readString();
        }

        clsUser User1 = clsUser::find(UserName);
        _PrintUser(User1);

        cout << "\nAre you sure you want to delete this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            if (User1.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User1);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }

};

