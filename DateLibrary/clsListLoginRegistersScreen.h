#pragma once

#include "clsLoginRegister.h"
#include <vector>
#include <iomanip>
#include "clsScreen.h"

using namespace std;
class clsListLoginRegistersScreen : protected clsScreen
{
private:

	static void _printLoginRegisterRecordLine(clsLoginRegister loginRegs) {
        cout << setw(8) << left << "" << "| " << setw(30) << left << loginRegs.getDateTime();
        cout << "| " << setw(20) << left << loginRegs.getUserName();
        cout << "| " << setw(20) << left << loginRegs.getPassword();
        cout << "| " << setw(20) << left << loginRegs.getPermission();

	}

public:
    static void showLoginRegisterList() {


        if (!clsScreen::checkAccessRights(clsUser::enPermissions::pLoginRegister)) {
            return;
        }

        vector<clsLoginRegister> vloginRegs = clsLoginRegister::getLoginRegisterList();;


        string Title = "\tListLoginRegister Screen";
        string subTitle = "\t( "+to_string(vloginRegs.size())+" ) LoggedIn User(s).";
        _drawScreenHeader(Title, subTitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(20) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
        for (clsLoginRegister& l : vloginRegs) {
            _printLoginRegisterRecordLine(l);
            cout << "\n";
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }
};

