#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h";
#include "StringLibrary.h"
#include <vector>
#include <fstream>
#include "clsDate.h"
#include "clsUtil.h";
using namespace std;
class clsUser : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::splitString(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], vUserData[5], stoi(vUserData[6]));

    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.firstName + Seperator;
        UserRecord += User.lastName + Seperator;
        UserRecord += User.email + Seperator;
        UserRecord += User.phoneNumber + Seperator;
        UserRecord += User.userName + Seperator;
        UserRecord += clsUtil::encryptText(User.Password,3) + Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;

    }

    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;

    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.markedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.userName == _UserName)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static string _convertRegisterUserToLine(clsUser user, string delim = "#//#") {
        string result;
        result = clsDate::getCurrentDate().dateToString() + " - " +
            clsDate::getDateTimeString() + delim +
            user.userName + delim +
            user.Password + delim +
            to_string(user.Permissions);

        return result;
    }

    static void _saveRegisterUserTofile(clsUser user) {
        fstream myFile;
        myFile.open("LoginRegister.txt", ios::app | ios::out);
        if (myFile.is_open()) {
            string line = _convertRegisterUserToLine(user);
            myFile << line << endl;
            myFile.close();
        }
    }

public:

    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64,pLoginRegister = 128
    };

    clsUser() {

    }

    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool isEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool markedForDeleted()
    {
        return _MarkedForDelete;
    }

    string getUserName()
    {
        return _UserName;
    }

    void setUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = getUserName, put = setUserName)) string userName;

    void setPassword(string Password)
    {
        _Password = Password;
    }

    string getPassword()
    {
        return _Password;
    }
    __declspec(property(get = getPassword, put = setPassword)) string Password;

    void setPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int getPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = getPermissions, put = setPermissions)) int Permissions;

    static clsUser find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.userName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

    static clsUser find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.userName == UserName && User.Password == clsUtil::encryptText(Password,0))
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (isEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsUser::isUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }

    }

    static bool isUserExist(string UserName)
    {

        clsUser User = clsUser::find(UserName);
        return (!User.isEmpty());
    }

    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.userName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }

    static clsUser getAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> getUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool checkAccessPermission(enPermissions permission) {
        if (this->Permissions == enPermissions::eAll) {
            return true;
        }
        else {
            if ((this->Permissions & permission) == permission) {
                return true;
            }
            else {
                return false;
            }

        }
    }

    void RegistedLoginUser() {
        _saveRegisterUserTofile(*this);
    }

};


