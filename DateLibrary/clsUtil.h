#pragma once

#include<string>
#include<iostream>
#include"clsDate.h";

using namespace std;

class clsUtil
{
public:
	static enum enCharType { SmallLetter = 1, CapitalLetter = 2, SpecialLetter = 3, Digit = 4, MixChars = 5 };


	static void Srand() {
		srand((unsigned)time(NULL));
	}

	static int randomNumber(int from, int to) {
		int number = rand() % (to - from + 1) + from;
		return number;
	}

	static char getRandomCharacter(enCharType charType) {
		switch (charType)
		{
		case SmallLetter:
			return char(randomNumber(97, 122));
			break;
		case CapitalLetter:
			return char(randomNumber(65, 90));
			break;
		case SpecialLetter:
			return char(randomNumber(33, 47));
			break;
		case Digit:
			return randomNumber(48, 57);
			break;
		case MixChars:
			return getRandomCharacter((enCharType)randomNumber(1, 4));
			break;
		default:
			break;
		}
		return ' ';
	}

	static string generateRandomWord(enCharType charType, short length) {
		string word = "";
		for (int i = 1; i <= length; i++) {
			word += getRandomCharacter(charType);
		}
		return word;
	}


	static string generateKey() {
		string key = "";
		key += generateRandomWord(enCharType::CapitalLetter, 4) + '-';
		key += generateRandomWord(enCharType::CapitalLetter, 4) + '-';
		key += generateRandomWord(enCharType::CapitalLetter, 4) + '-';
		key += generateRandomWord(enCharType::CapitalLetter, 4);
		return key;
	}

	static void generateKeys(int keyNum) {
		for (int i = 1; i <= keyNum; i++) {
			cout << "key[" << i << "] : " << generateKey() << endl;
		}
	}

	static void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}

	static void swap(double& a, double& b) {
		double temp = a;
		a = b;
		b = temp;
	}

	static void swap(string& s1, string& s2) {
		string temp = s1;
		s1 = s2;
		s2 = temp;
	}

	static void swap(clsDate& date1,clsDate& date2) {
		clsDate tempDate;
		tempDate = date1;
		date1 = date2;
		date2 = tempDate;
	}

	static void shuffleArray(int arr[], int size) {
		int x = 0;
		int y = 0;
		for (int i = 0; i < size; i++) {
			x = randomNumber(0, size - 1);
			y = randomNumber(0, size - 1);
			swap(arr[x], arr[y]);
		}
	}

	static void shuffleArray(string arr[],int size) {
		int firstIndx = 0;
		int secondIndx = 0;

		for (int i = 0; i <size; i++) {
			firstIndx = randomNumber(0, size - 1);
			secondIndx = randomNumber(0, size - 1);
			swap(arr[firstIndx], arr[secondIndx]);
		}
	}

	static void fillArrayWithRandomNumbers(int arr[], int size, int from, int to) {
		for (int i = 0; i < size; i++) {
			arr[i] = randomNumber(from, to);
		}
	}

	static void fillArrayWithRandomWords(string arr[], int size, enCharType charType,int wordLength) {
		for (int i = 0; i < size; i++) {
			arr[i] = generateRandomWord(charType, wordLength);
		}
	}

	static string Tabs(int nbrTabs) {
		string result = "";
		for (int i = 0; i < nbrTabs; i++) {
			result += "	";
		}
		return result;
	}

	static string encryptText(string text, short encryptionKey) {
		for (int i = 0; i < text.length(); i++) {
			text[i] = char(int(text[i]) + encryptionKey);
		}
		return text;
	}

	static string decryptedText(string text, short decryptionKey) {
		for (int i = 0; i < text.length(); i++) {
			text[i] = char(int(text[i]) - decryptionKey);
		}
		return text;
	}



};



