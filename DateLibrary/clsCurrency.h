#pragma once

#include <string>
#include <vector>
#include "StringLibrary.h"
#include <fstream>
using namespace std;
class clsCurrency
{

private:

	enum enMode { EmptyMode = 0,UpdateMode = 1};

	enMode _mode;
	string _country;
	string _currencyCode;
	string _currencyName;
	float _Rate;

	static clsCurrency _convertLinetoCurrencyObject(string line, string delim = "#//#") {
		vector<string> vCurrency;
		vCurrency = clsString::splitString(line, delim);
		return clsCurrency(enMode::UpdateMode, vCurrency[0], vCurrency[1], vCurrency[2],stof(vCurrency[3]));
	}

	static string _convertCurrencyObjectToLine(clsCurrency currency,string delim="#//#") {
		string result;
		result = currency.getCountry() + delim +
			currency.getCurrencyCode() + delim +
			currency.getCurrencyName() + delim +
			to_string(currency.getCurrencyRate());

		return result;

	}

	static vector<clsCurrency> _loadCurrencyDataFromFile() {
		fstream myFile;
		vector<clsCurrency> vCurrency;
		myFile.open("Currencies.txt", ios::in);
		if (myFile.is_open()) {
			string line;
			while (getline(myFile, line)) {
				vCurrency.push_back(_convertLinetoCurrencyObject(line));
			}
			myFile.close();
		}
		return vCurrency;
	}

	static void _saveCurrencyDataToFile(vector<clsCurrency> vCurrencies) {
		fstream myFile;
		myFile.open("Currencies.txt", ios::out);
		if (myFile.is_open()) {
			string line;
			for (clsCurrency& c : vCurrencies) {
				line = _convertCurrencyObjectToLine(c);
				myFile << line << endl;
			}
			myFile.close();
		}
	}

	void _update() {
		vector<clsCurrency> vCurrencys;
		vCurrencys = _loadCurrencyDataFromFile();
		for (clsCurrency& c : vCurrencys) {
			if (c.getCurrencyCode() == this->getCurrencyCode()) {
				c = *this;
				break;
			}
		}
		_saveCurrencyDataToFile(vCurrencys);
	}

	static clsCurrency _getEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}



public:
	clsCurrency(enMode mode,string country, string currencyCode, string currencyName, float rate) {
		this->_mode = mode;
		this->_country = country;
		this->_currencyCode = currencyCode;
		this->_currencyName = currencyName;
		this->_Rate = rate;
	}

	
	bool isEmpty() {
		return (enMode::EmptyMode == _mode);
	}

	static vector<clsCurrency> getAllUSDRates() {
		return _loadCurrencyDataFromFile();
	}

	
	string getCountry() {
		return this->_country;
	}

	string getCurrencyCode() {
		return this->_currencyCode;
	}

	string getCurrencyName() {
		return this->_currencyName;
	}

	float getCurrencyRate() {
		return this->_Rate;
	}
	void updateCurrencyRate(float rate) {
		this->_Rate = rate;
		_update();
	}

	static clsCurrency findByCode(string currencyCode) {
		currencyCode = clsString::upperAllString(currencyCode);
		vector<clsCurrency> vCurrency = _loadCurrencyDataFromFile();
		for (clsCurrency& c : vCurrency) {
			if (c.getCurrencyCode() == currencyCode) {
				return c;
			}
		}
		return _getEmptyCurrencyObject();
	}

	static clsCurrency findByCountry(string country) {
		country = clsString::upperAllString(country);
		vector<clsCurrency> vCurrency = _loadCurrencyDataFromFile();
		for (clsCurrency& c : vCurrency) {
			if (c.getCountry() == country) {
				return c;
			}
		}
		return _getEmptyCurrencyObject();
	}

	static bool isCurrencyExist(string currencyCode) {
		clsCurrency currency = clsCurrency::findByCode(currencyCode);
		return (!currency.isEmpty());
	}

	static vector<clsCurrency> getCurrenciesList() {
		return _loadCurrencyDataFromFile();
	}




};

