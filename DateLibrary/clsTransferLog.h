#pragma once

#include <string>

using namespace std;
class clsTransferLog
{

private:

	string dateTime;
	string sourceAcc;
	string destinationAcc;
	float amount;
	float sourceBalance;
	float destinationBalance;
	string user;


public:

	clsTransferLog(string dateTime, string sourceAcc, string destinationAcc, float amount, float sourceBalance, float destinationBalance, string user) {
		this->dateTime = dateTime;
		this->sourceAcc = sourceAcc;
		this->destinationAcc = destinationAcc;
		this->amount = amount;
		this->sourceBalance = sourceBalance;
		this->destinationBalance = destinationBalance;
		this->user = user;
	}


	string getDateTime() {
		return this->dateTime;
	}

	string getSourceAcc() {
		return this->sourceAcc;
	}

	string getDestinationAcc() {
		return this->destinationAcc;
	}

	float getAmount() {
		return this->amount;
	}

	float getSourceBalance() {
		return this->sourceBalance;
	}

	float getDestinationBalance() {
		return this->destinationBalance;
	}

	string getUser() {
		return this->user;
	}

};

