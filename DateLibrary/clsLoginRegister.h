#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "StringLibrary.h";
#include <fstream>

using namespace std;
class clsLoginRegister
{
private:
	string dateTime;
	string userName;
	string password;
	string permissions;

	static clsLoginRegister _convertLoginRegisterLineToObject(string line) {
		vector<string> vUser;
		vUser = clsString::splitString(line,"#//#");
		return clsLoginRegister(vUser[0], vUser[1], vUser[2], vUser[3]);
	}


public:

	clsLoginRegister(string dateTime, string userName, string password, string permissions) {
		this->dateTime = dateTime;
		this->userName = userName;
		this->password = password;
		this->permissions = permissions;
	}

	string getDateTime() {
		return this->dateTime;
	}

	string getUserName() {
		return this->userName;
	}

	string getPassword() {
		return this->password;
	}

	string getPermission() {
		return this->permissions;
	}



	static vector<clsLoginRegister> getLoginRegisterList() {
		vector<clsLoginRegister> vRegisters;
		fstream myFile;
		myFile.open("LoginRegister.txt", ios::in);
		if (myFile.is_open()) {
			string line;
			while (getline(myFile, line)) {
				vRegisters.push_back(_convertLoginRegisterLineToObject(line));
			}
			return vRegisters;
			myFile.close();
		}
	}
};

