#pragma once


#include<iostream>
#include<string>
#include"clsDate.h";
#include"clsPeriod.h"

using namespace std;
class clsInputValidate
{
public:

	static bool isNumberBetween(int number, int from, int to) {
		return (number >= from && number <= to);
	}
	static bool isNumberBetween(double number, double from, double to) {
		return (number >= from && number <= to);
	}
	static bool isDateBetween(clsDate date1, clsDate dateFrom, clsDate dateTo) {
		if (clsDate::isDateOneBeforeDateTwo(dateFrom, dateTo)) {
			return (clsDate::checkIfDateOneAfterDateTwo(date1, dateFrom) && clsDate::isDateOneBeforeDateTwo(date1, dateTo));
		}
		return (clsDate::checkIfDateOneAfterDateTwo(date1, dateTo) && clsDate::isDateOneBeforeDateTwo(date1, dateFrom));
		
	}

	static int readIntNumber(string message="Invalid number, Enter again:\n") {
		int result;
		while (!(cin >> result)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << message;
		}

		return result;
	}

	static int readIntNumberBetween(int From, int To, string message = "Number should be in Range\n") {
		int x = readIntNumber();
		while (x< From || x >To) {
			cout << message;
			x = readIntNumber();
		}
		return x;
	}

	static double readDoubleNumber(string message = "Invalid number,Enter again:\n") {
		double result;
		while (!(cin >> result)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << message;
		}
		return result;
	}

	static double readDoubleNumberBetween(double From, double To, string message = "Number should be in Range\n") {
		double result = readDoubleNumber();
		while (result<From || result > To) {
			cout << message;
			result = readDoubleNumber();
		}
		return result;
	}

	static bool isValidDate(clsDate date) {
		return date.isValid();
	}

	static string readString() {
		string s1;
		getline(cin >> ws, s1);
		return s1;
	}

	static string NumberToText(int number) {
		if (number == 0) {
			return "";
		}
		if (number >= 1 && number <= 19) {
			string arr[] = { "","One","Two","Three","Four","Five","Six","Seven",
				"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
				"Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
			return arr[number] + " ";
		}
		if (number >= 20 && number <= 99) {
			string arr[] = { "","","Twenty","Thirty","Forty","Fifty",
				"Sixty","Seventy","Eighty","Ninety" };
			return arr[number / 10] + " " + NumberToText(number % 10);
		}
		if (number >= 100 && number <= 199) {
			return "One Hundred " + NumberToText(number % 100);
		}
		if (number >= 200 && number <= 999) {
			return NumberToText(number / 100) + "Hundred " + NumberToText(number % 100);
		}
		if (number >= 1000 && number <= 1999) {
			return "One Thousand " + NumberToText(number % 1000);
		}
		if (number <= 2000 && number <= 99999) {
			return NumberToText(number / 1000) + "Thousand " + NumberToText(number % 1000);
		}
		if (number >= 1000000 && number <= 1999999) {
			return "One Million " + NumberToText(number % 1000000);
		}
		if (number >= 2000000 && number <= 9999999) {
			return NumberToText(number / 1000000) + " Millions " + NumberToText(number % 1000000);
		}
		if (number >= 1000000000 && number <= 1999999999) {
			return "One Billion " + NumberToText(number % 1000000000);
		}
		else {
			return NumberToText(number / 1000000000) + "billions " + NumberToText(number % 1000000000);
		}
	}


};

