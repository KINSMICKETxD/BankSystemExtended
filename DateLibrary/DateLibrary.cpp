#include <iostream>
#include "clsLoginScreen.h";
#include "clsListLoginRegistersScreen.h"
#include "clsLoginRegister.h"
#include "clsTransferLog.h"
#include "clsUtil.h"
#include "clsCurrency.h"
#include "clsCurrencyMainScreen.h"
#include "clsCurreniesListScreen.h"
using namespace std;
int main()

{
     /*bool result = true;
     while (result) {

        result =  clsLoginScreen::ShowLoginScreen();
     }
     return 0;
     */
    clsCurreniesListScreen::showCurrencyList();
}
