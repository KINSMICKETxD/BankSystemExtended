#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewUserScreen : protected clsScreen
{
private:

    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.firstName = clsInputValidate::readString();

        cout << "\nEnter LastName: ";
        User.lastName = clsInputValidate::readString();

        cout << "\nEnter Email: ";
        User.email = clsInputValidate::readString();

        cout << "\nEnter Phone: ";
        User.phoneNumber = clsInputValidate::readString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::readString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }

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

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {


            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nShow login Register? y/n ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += clsUser::enPermissions::pLoginRegister;
        }

        return Permissions;

    }

public:

    static void ShowAddNewUserScreen()
    {

        _drawScreenHeader("\t  Add New User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::readString();
        while (clsUser::isUserExist(UserName))
        {
            cout << "\nUserName Is Already Used, Choose another one: ";
            UserName = clsInputValidate::readString();
        }

        clsUser NewUser = clsUser::getAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;

        SaveResult = NewUser.save();

        switch (SaveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(NewUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;

        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;

        }
        }
    }



};

