#pragma once

#include<iostream>
#include<string>
#include"clsPerson.h";
#include"StringLibrary.h";
#include<vector>
#include<fstream>
#include "clsTransferLog.h"
using namespace std;


class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0,UpdateMode = 1,AddNewMode = 2};

	enMode _mode;


	string	_accountNumber;
	string	_pinCode;
	float	_accountBalance;
	bool	_deleteFlag = false;

	static clsBankClient _convertLineToClientObject(string line, string delim = "#//#") {
		vector<string> vClientData;
		vClientData = clsString::splitString(line,delim);
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5],stof( vClientData[6]));
	}
	static string _convertClientObjectToLine(clsBankClient client) {
		 return  (client.getAccountNumber() + "#//#" + client.firstName + "#//#" + client.lastName + "#//#" +
		client.email + "#//#" + client.phoneNumber + "#//#" + client.pinCode + "#//#" + to_string(client.balance));
	}
	static clsBankClient _getEmptyClientObject() {
		clsBankClient emptyClient = clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
		return emptyClient;
	}
	static vector<clsBankClient> _loadClientsDataFromFile() {
		vector<clsBankClient> vClients;
		fstream myFile;
		myFile.open("Clients.txt", ios::in);

		if (myFile.is_open()) {
			string line;
			while (getline(myFile, line)) {
				clsBankClient client = _convertLineToClientObject(line);
				vClients.push_back(client);
			}
			myFile.close();
		}
		return vClients;
	}
	void _saveClientsDataToFile(vector<clsBankClient> vClients) {
		fstream myFile;
		myFile.open("Clients.txt", ios::out);
		string clientData;
		if (myFile.is_open()) {

			for (clsBankClient c : vClients) {
				if (c.getFlag() == false) {
					clientData = _convertClientObjectToLine(c);
					myFile << clientData << endl;
				}
			}
			myFile.close();
		}

	}
	void _update() {
		vector<clsBankClient> vClients;
		vClients = _loadClientsDataFromFile();
		for (clsBankClient& c : vClients) {
			if (c.getAccountNumber() == getAccountNumber()) {
				c = *this;
				break;
			}
		}
		_saveClientsDataToFile(vClients);
	}
	void _addDataLineToFile(string line) {
		fstream myFile;
		myFile.open("Clients.txt",ios::out | ios::app);
		if (myFile.is_open()) {
			myFile << line << endl;
			myFile.close();
		}
	}
	void _addNew() {
		_addDataLineToFile(_convertClientObjectToLine(*this));
	}

	static string _getTransferLogLine(clsBankClient clientFrom,clsBankClient clientTo, int transferAmount,string delim = "#//#") {
		string line;
		line = clsDate::getCurrentDate().dateToString() + " - " + clsDate::getDateTimeString() + delim +
			clientFrom.getAccountNumber() + delim +
			clientTo.getAccountNumber() + delim +
			to_string(transferAmount) + delim +
			to_string(clientFrom.balance) + delim +
			to_string(clientTo.balance) + delim +
			CurrentUser.userName;
		return line;
	}

	static clsTransferLog _convertTransferLogLineToStruct(string line) {
		vector<string> vTransferLog = clsString::splitString(line,"#//#");
		return clsTransferLog(vTransferLog[0], vTransferLog[1],vTransferLog[2],stof(vTransferLog[3]),stof(vTransferLog[4]),stof(vTransferLog[5]),
			vTransferLog[6]);
		
	}
public:

	clsBankClient() {

	}

	clsBankClient(enMode mode,string accountNumber, string firstName, string lastName, string email, string phone,
		 string pinCode, float balance)
		:clsPerson(firstName, lastName,email, phone)
	{
		_mode = mode;
		_accountNumber = accountNumber;
		_pinCode = pinCode;
		_accountBalance = balance;
	}


	bool isEmpty() {
		return (_mode == enMode::EmptyMode);
	}

	string getAccountNumber() {
		return _accountNumber;
	}

	void setPinCode(string pinCode) {
		_pinCode = pinCode;
	}
	string getPinCode() {
		return _pinCode;
	}
	__declspec(property(get = getPinCode, put = setPinCode)) string pinCode;

	void setBalance(float balance) {
		_accountBalance = balance;
	}
	float getBalance() {
		return _accountBalance;
	}
	__declspec(property(get = getBalance, put = setBalance)) float balance;

	bool getFlag() {
		return _deleteFlag;
	}

	/*void print() {
		cout << "\nClient Card:";
		cout << "\n____________________";
		cout << "\nFirstName	: " << firstName;
		cout << "\nLastName		: " << lastName;
		cout << "\nFullName		: " << fullName;
		cout << "\nEmail		: " << email;
		cout << "\nPhone		: " << phoneNumber;
		cout << "\nAccNumber	: " << _accountNumber;
		cout << "\nPassword		: " << _pinCode;
		cout << "\nBalance		: " << _accountBalance;
		cout << "\n____________________";
	}*/

	void deposit(double ammount) {
		this->balance += ammount;
		save();
	}

	bool withdraw(double ammount) {
		if (ammount > this->balance) {
			return false;
		}
		else {
			this->balance -= ammount;
			save();
			return true;
		}
	}

	static clsBankClient find(string accountNumber) {

		vector<clsBankClient> vClients;
		
		fstream myFile;

		myFile.open("Clients.txt", ios::in);
		if (myFile.is_open()) {
			string line;
			while (getline(myFile, line)) {
				 
				clsBankClient client = _convertLineToClientObject(line);
				if (client.getAccountNumber() == accountNumber) {
					myFile.close();
					return client;
				}
				vClients.push_back(client);
			}
			myFile.close();
		}

		return _getEmptyClientObject();

	}

	static clsBankClient find(string accountNumber, string pinCode) {

		vector<clsBankClient> vClients;

		fstream myFile;
		myFile.open("Clients.txt", ios::in);
		if (myFile.is_open()) {
			string line;
			while (getline(myFile, line)) {

				clsBankClient client = _convertLineToClientObject(line);
				if (client.getAccountNumber() == accountNumber && client.pinCode == pinCode) {
					myFile.close();
					return client;
				}
				vClients.push_back(client);
			}
			myFile.close();
		}
		return _getEmptyClientObject();
	}

	static bool isClientExist(string accountNumber) {
		clsBankClient client = find(accountNumber);
		return (!client.isEmpty());
	}


	enum enSaveResults {svFailedEmptyObject = 0,svSucceeded = 1,failedAccountNumberExist=2};

	enSaveResults save() {
		switch (_mode)
		{
		case clsBankClient::EmptyMode:

			return enSaveResults::svFailedEmptyObject;
			break;
		case clsBankClient::UpdateMode:

			_update();
			return enSaveResults::svSucceeded;
			break;
		case clsBankClient::AddNewMode:

			if (clsBankClient::isClientExist(_accountNumber)) {
				return enSaveResults::failedAccountNumberExist;
			}
			else {

				_addNew();
				_mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
	}

	static clsBankClient  getAddNewClientObject(string accountNumber) {

		return clsBankClient(enMode::AddNewMode,accountNumber, "", "", "", "", "", 0);
	}

	bool deleteClient() {

		vector<clsBankClient> vClients;
		vClients = _loadClientsDataFromFile();
		for (clsBankClient& c : vClients) {
			if (c.getAccountNumber() == _accountNumber) {
				c._deleteFlag = true;
				break;
			}
		}
		_saveClientsDataToFile(vClients);

		*this = _getEmptyClientObject();
		return true;
		


		return true;
	}

	static vector<clsBankClient> getClientsList() {
		return _loadClientsDataFromFile();
	}

	static int getTotalBalances() {
		double totalBalances = 0;
		vector<clsBankClient> vClients = _loadClientsDataFromFile();
		for (clsBankClient& c : vClients) {
			totalBalances += c.balance;
		}
		return totalBalances;
	}

	void saveTransferLogs(clsBankClient clientTo,int transferAmount) {
		fstream myFile;
		myFile.open("TransferLog.txt", ios::out | ios::app);
		if (myFile.is_open()) {
			string line = _getTransferLogLine(*this, clientTo, transferAmount);
			myFile << line << endl;
		}
	}

	static vector<clsTransferLog> getTransferLogList() {
		vector<clsTransferLog> vLogs;
		fstream myFile;
		myFile.open("TransferLog.txt", ios::in);
		if (myFile.is_open()) {
			string line;
			while (getline(myFile, line)) {
				vLogs.push_back(_convertTransferLogLineToStruct(line));
			}
			myFile.close();
		}
		return vLogs;
	}


};

