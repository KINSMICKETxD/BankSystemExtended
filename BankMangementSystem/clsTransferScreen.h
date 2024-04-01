#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;
class clsTransferScreen : protected clsScreen
{
private:


	static void _printClientCard(clsBankClient Client) {
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.fullName;
		cout << "\nAcc.Number  : " << Client.getAccountNumber();
		cout << "\nBalance	   : " << Client.balance;
		cout << "\n___________________\n";
	}

	static void _printTransferLogRecord(clsTransferLog record) {
		cout << setw(8) << left << "" << "| " << setw(25) << left << record.getDateTime();
		cout << "| " << setw(10) << left << record.getSourceAcc();
		cout << "| " << setw(10) << left << record.getDestinationAcc();
		cout << "| " << setw(10) << left << record.getAmount();
		cout << "| " << setw(10) << left << record.getSourceBalance();
		cout << "| " << setw(10) << left << record.getDestinationBalance();
		cout << "| " << setw(10) << left << record.getUser();
	}

public:

	static void showTransferScreen() {
		string Title = "\t  Transfer Screen";
		clsScreen::_drawScreenHeader(Title);
		cout << "\nPlease Enter Account Number to Transfer From: ";
		string accountNumber1 = clsInputValidate::readString();
		while (!clsBankClient::isClientExist(accountNumber1)) {
			cout << "\nWrong account Number ! please enter a valid one : ";
			accountNumber1 = clsInputValidate::readString();
		}
		clsBankClient clientFrom = clsBankClient::find(accountNumber1);
		_printClientCard(clientFrom);

		cout << "\nPlease Enter Account Number to Transfer To: ";
		string accountNumber2 = clsInputValidate::readString();
		while (!clsBankClient::isClientExist(accountNumber2)) {
			cout << "\nWrong account Number ! please enter a vlid one : ";
			accountNumber2 = clsInputValidate::readString();
		}
		clsBankClient clientTo = clsBankClient::find(accountNumber2);
		_printClientCard(clientTo);

		cout << "\nEnter transfer Ammount? ";
		int transferAmount = clsInputValidate::readIntNumber();
		while (transferAmount > clientFrom.balance) {
			cout << "\nAmmount Exceeds the available Balance, Enter another Amount? ";
			transferAmount = clsInputValidate::readIntNumber();
		}
		char answer = 'n';
		cout << "Are you sure you want to performe this operation ? y/n ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y') {
			clientFrom.withdraw(transferAmount);
			clientTo.deposit(transferAmount);
			clientFrom.saveTransferLogs(clientTo, transferAmount);
			cout << "\nTransfer Done !";
		}
	}

	static void showTransferLogList() {
		string title = "\tTransfer Log List Screen";
		vector<clsTransferLog> vLogs = clsBankClient::getTransferLogList();
		string subTitle = "\t( " + to_string(vLogs.size()) + " ) Record(s).";
		_drawScreenHeader(title, subTitle);


		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(10) << "s.Acc";
		cout << "| " << left << setw(10) << "d.Acc";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(10) << "User";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		for (clsTransferLog& t : vLogs) {
			_printTransferLogRecord(t);
			cout << endl;
		}
	}
};

