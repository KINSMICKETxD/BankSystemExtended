#pragma once

#include<iostream>
#include<string>

using namespace std;


class clsPerson
{
private:

	string _firstName;
	string _lastName;
	string _email;
	string _phoneNumber;
public:

	clsPerson() {

	}

	clsPerson(string firstName, string lastName, string email, string phoneNumber) {
		_firstName = firstName;
		_lastName = lastName;
		_email = email;
		_phoneNumber = phoneNumber;
	}

	void setFirstName(string firstName) {
		_firstName = firstName;
	}
	string getFirstName() {
		return _firstName;
	}
	__declspec(property(get = getFirstName, put = setFirstName)) string firstName;

	void setLastName(string lastName) {
		_lastName = lastName;
	}
	string getLastName() {
		return _lastName;
	}

	__declspec(property(get = getLastName, put = setLastName)) string lastName;

	string getFullName() {
		return (_firstName + " " + _lastName);
	}
	__declspec(property(get = getFullName)) string fullName;

	void setEmail(string email) {
		_email = email;
	}

	string getEmail() {
		return _email;
	}
	__declspec(property(get = getEmail, put = setEmail)) string email;

	void setPhoneNumber(string phoneNumber) {
		_phoneNumber = phoneNumber;
	}
	string getPhoneNumber() {
		return _phoneNumber;
	}
	__declspec(property(get = getPhoneNumber, put = setPhoneNumber)) string phoneNumber;
};

