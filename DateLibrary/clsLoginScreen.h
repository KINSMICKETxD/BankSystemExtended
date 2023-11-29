#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "Global.h"
#include "clsMainScreen.h"
#include "clsDate.h";
#include "clsUtil.h"

class clsLoginScreen :protected clsScreen
{

private:

    static  bool _Login()
    {
        bool LoginFaild = false;
        short trials = 2;
        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                cout << "\nInvlaid Username/Password!";
                trials -= 1;
                cout << "\nYou have " << to_string(trials+1) << " Trials to login.\n";
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;
            CurrentUser = clsUser::find(Username, Password);

            LoginFaild = CurrentUser.isEmpty();

        } while (trials > 0 && LoginFaild);
        if (trials ==0 && LoginFaild) {
            cout << "You are locked after 3 failed trials\n\n";
            return false;
        }
        else {
            CurrentUser.RegistedLoginUser();
            clsMainScreen::ShowMainMenue();
            return true;
        }
        
    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _drawScreenHeader("\t  Login Screen");
        return _Login();
    }

};

