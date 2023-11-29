#include <iostream>
#include "clsLoginScreen.h";
#include "clsListLoginRegistersScreen.h"
#include "clsLoginRegister.h"
#include "clsTransferLog.h"
#include "clsUtil.h"
using namespace std;
int main()

{
   bool result = true;
    while (result) {

       result =  clsLoginScreen::ShowLoginScreen();
    }
    return 0;
    //cout << clsUtil::encryptText("azizgh",3);
}
