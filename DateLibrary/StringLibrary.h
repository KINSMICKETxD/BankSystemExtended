#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class clsString
{

private:
	string _value;

public:
	clsString() {
		_value = "";
	}
	clsString(string myString) {
		this->_value = myString;
	}

	void setValue(string newString) {
		this->_value = newString;
	}

	string getValue() {
		return this->_value;
	}

	__declspec(property(get = getValue, put = setValue)) string Value;

	static short countWords(string s1) {
		string delim = " ";
		short Counter = 0;
		short pos = 0;
		string sWord;

		while ((pos = s1.find(delim)) != std::string::npos) {
			sWord = s1.substr(0, pos);
			if (sWord != "") {
				Counter++;
			}
			s1.erase(0, pos + delim.length());
		}
		if (s1 != "") {
			Counter++;
		}

		return Counter;

	}
	short countWords() {
		return countWords(_value);
	}
	short countCapicalLetters() {
		int counter = 0;
		for (short i = 0; i < _value.length(); i++) {
			if (isupper(_value[i])) {
				counter++;
			}
		}
		return counter;
	}
	short countLetters() {
		int counter = 0;
		for (short i = 0; i < _value.length(); i++) {
			if (isalpha(_value[i])) {
				counter++;
			}
		}
		return counter;
	}
	short countSmallLetters() {
		int counter = 0;
		for (int i = 0; i < _value.length(); i++) {
			if (islower(_value[i])) {
				counter++;
			}
		}
		return counter;
	}
	short countSpecificLetter(char letter) {
		int counter = 0;
		for (int i = 0; i < _value.length(); i++) {
			if (_value[i] == letter) {
				counter++;
			}
		}
		return counter;
	}

	short countVowels() {
		short counter = 0;
		for (int i = 0; i < _value.length(); i++) {
			if (tolower(_value[i]) == 'a' || tolower(_value[i]) == 'e' || tolower(_value[i]) == 'i' ||
				tolower(_value[i]) == 'u' || tolower(_value[i]) == 'o') {
				counter++;
			}
		}
		return counter;
	}
	void invertAllLetterCase() {
		for (int i = 0; i < _value.length(); i++) {
			if (isupper(_value[i])) {
				_value[i] = tolower(_value[i]);
			}
			else {
				_value[i] = toupper(_value[i]);
			}
		}
	}
	void invertLetterCase(char letter) {
		for (int i = 0; i < _value.length(); i++) {
			if (letter == _value[i]) {
				if (isupper(_value[i])) {
					_value[i] = tolower(_value[i]);
				}
				else {
					_value[i] = toupper(_value[i]);
				}
			}
		}
	}
	bool isVowel(char letter) {
		if (tolower(letter) == 'a' || tolower(letter) == 'e' || tolower(letter) == 'i' ||
			tolower(letter) == 'o' || tolower(letter) == 'u') {
			return true;
		}
		else {
			return false;
		}
	}

	string joinString(vector<string> myStrings) {
		string finalString = "";
		for (int i = 0; i < myStrings.size() - 1; i++) {
			finalString = finalString + myStrings[i] + " ";
		}
		finalString = finalString + myStrings[myStrings.size() - 1];
		return finalString;
	}
	int Length() {
		return _value.length();
	}
	void lowerAllString() {
		for (char c : _value) {
			c = tolower(c);
		}
	}
	static vector<string> splitString(string s1, string delim) {
		vector<string> vResult;
		short pos = 0;
		string word;
		while ((pos = s1.find(delim)) != std::string::npos) {
			word = s1.substr(0, pos);
			vResult.push_back(word);
			s1.erase(0, pos + delim.length());
		}
		if (s1 != "") {
			vResult.push_back(s1);
		}
		return vResult;
	}

	void lowerFirstLetterOfEachWord() {
		vector<string> myWords = splitString(_value, " ");
		for (string& s : myWords) {
			s[0] = tolower(s[0]);
		}
		_value = joinString(myWords);
	}
	void removePunctuation() {
		for (int i = 0; i < _value.length(); i++) {
			while (ispunct(_value[i])) {
				_value.erase(i, 1);
			}
		}
	}
	void remplaceAWord(string newWord, string oldWord) {
		vector<string> myWords = splitString(_value, " ");
		for (string& s : myWords) {
			if (s == oldWord) {
				s = newWord;
			}
		}
		_value = joinString(myWords);
	}
	void ReverseWordsInString() {
		string stringResult = "";
		vector<string> myWords = splitString(_value, " ");
		for (int i = myWords.size() - 1; i > 0; i--) {
			stringResult = stringResult + myWords[i] + " ";
		}
		stringResult = stringResult + myWords[0];
		_value = stringResult;
	}
	void TrimLeft() {
		short i = 0;
		while (_value[i] == ' ') {
			i++;
		}
		_value.erase(0, i);
	}
	void TrimRight() {
		short i = _value.length() - 1;
		while (_value[i] == ' ') {
			i--;
		}
		_value.erase(i + 1);
	}
	void Trim() {
		TrimLeft();
		TrimRight();
	}

	void UpperFirstLetterOfEachWord() {
		vector<string> myString = splitString(_value, " ");
		for (string& s : myString) {
			s[0] = toupper(s[0]);
		}
		_value = joinString(myString);
	}
	void upperAllString() {
		for (int i = 0; i < _value.length(); i++) {
			_value[i] = toupper(_value[i]);
		}
	}
	static string upperAllString(string myString) {
		for (int i = 0; i < myString.length(); i++) {
			myString[i] = toupper(myString[i]);
		}
		return myString;
	}
};


