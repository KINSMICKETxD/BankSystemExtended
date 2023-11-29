#pragma once
#include <iostream>
#include "clsUser.h";
#include "Global.h";
#include "clsDate.h";
using namespace std;
class clsScreen
{
protected:
	static void _drawScreenHeader(string Title, string SubTitle = "") {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        cout << "\t\t\t\t\tUser: " + CurrentUser.fullName << endl;
        clsDate date = clsDate();
        cout << "\t\t\t\t\tDate: " + date.dateToString() << "\n\n";
    }

    static bool checkAccessRights(clsUser::enPermissions permissions) {
        if (!CurrentUser.checkAccessPermission(permissions)) {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else {
            return true;
        }
    }
};

