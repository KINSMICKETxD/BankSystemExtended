#pragma once

#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include "StringLibrary.h";
using namespace std;


class clsDate
{
	enum eCompResult { Before = -1, Equal = 0, After = 1 };

	struct stDate
	{
		int day;
		int month;
		int year;

	};
	struct stPeriod
	{
		stDate startDate;
		stDate endDate;
	};
private:
	stDate myDate;
	stPeriod period;
	string stringDate;
public:

	clsDate() {
		time_t t = time(0);
		tm* now = localtime(&t);
		this->myDate.day = now->tm_mday;
		this->myDate.month = now->tm_mon + 1;
		this->myDate.year = now->tm_year + 1900;
		this->stringDate = dateToString();
	}
	clsDate(string dateString) {
		vector<string> myDate = clsString::splitString(dateString, "/");
		this->myDate.day = std::stoi(myDate[0]);
		this->myDate.month = std::stoi(myDate[1]);
		this->myDate.year = std::stoi(myDate[2]);
		this->stringDate = dateToString();
	}
	clsDate(int day, int month, int year) {
		this->myDate.day = day;
		this->myDate.month = month;
		this->myDate.year = year;
		this->stringDate = dateToString();
	}
	clsDate(int NbrDays, int year) {
		myDate = getDateFromNumberOfDays(NbrDays, year);
		this->stringDate = dateToString();
	}

	static short getDaysInMonth(short month, bool isLeap) {
		int arr31Days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (month == 2) ? (isLeap ? 29 : 28) : arr31Days[month - 1];
	}
	short getDaysInMonth() {
		return getDaysInMonth(this->myDate.month, checkIfLeapYear());
	}

	static short getDaysInYear(bool isLeadYear) {
		if (isLeadYear) {
			return 366;
		}
		else {
			return 365;
		}
	}
	short getDaysInYear() {
		return getDaysInYear(checkIfLeapYear(myDate.year));
	}

	static int getHoursInYear(int year) {
		return getDaysInYear(year) * 24;
	}
	int getHoursInYear() {
		return getDaysInYear(myDate.year);
	}

	static int getMinutesInYear(int year) {
		return getHoursInYear(year) * 60;
	}
	int getMinutesInYear() {
		return getMinutesInYear(myDate.year);
	}

	static long int getSecondsInYear(short year) {
		return getMinutesInYear(year) * 60;
	}
	long int getSecondsInYear() {
		return getSecondsInYear(myDate.year);
	}

	static short getHoursInMonth(short month, bool isLeap) {
		return getDaysInMonth(month, isLeap) * 24;
	}
	short getHoursInMonth() {
		return getHoursInMonth(myDate.month, checkIfLeapYear(myDate.year));
	}

	static int getMinutesInMonth(short month, bool isLeap) {
		return getHoursInMonth(month, isLeap) * 60;
	}
	int getMinutesInMonth() {
		return getMinutesInMonth(myDate.month, checkIfLeapYear(myDate.year));
	}

	static int getSecondsInMonth(short month, bool isLeap) {
		return getMinutesInMonth(month, isLeap) * 60;
	}
	int getSecondsInMonth() {
		return getSecondsInMonth(myDate.month, checkIfLeapYear(myDate.year));
	}

	static short NumberOfDaysFromTheBeginningOfTheyear(short year, short month, short day) {
		int daysOfLastMonths = 0;
		for (int i = 1; i < month; i++) {
			daysOfLastMonths += getDaysInMonth(i, checkIfLeapYear(year));
		}
		daysOfLastMonths += day;
		return daysOfLastMonths;
	}
	short NumberOfDaysFromTheBeginningOfTheyear() {
		return NumberOfDaysFromTheBeginningOfTheyear(myDate.year, myDate.month, myDate.day);
	}



	static bool checkIfLeapYear(int year) {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}
	bool checkIfLeapYear() {
		return checkIfLeapYear(this->myDate.year);
	}



	static stDate getDateFromNumberOfDays(short daysNumber, short year) {
		stDate date;
		short remainingDays = daysNumber;
		short monthDays = 0;
		date.year = year;
		date.month = 1;
		while (true) {
			monthDays = getDaysInMonth(date.month, checkIfLeapYear(year));
			if (remainingDays > monthDays) {
				remainingDays -= monthDays;
				date.month++;
			}
			else {
				date.day = remainingDays;
				break;
			}
		}
		return date;
	}
	stDate getDateFromNumberOfDays(short daysNumber) {
		return getDateFromNumberOfDays(daysNumber, this->myDate.year);
	}

	static short calculateDayOrder(short day, short month, short year) {
		short a = (14 - month) / 12;
		short y = year - a;
		short m = month + (12 * a) - 2;
		return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static string getShortMonthName(short monthIndex) {
		string arrMonths[12] = { "Jan","Feb","Mar","Apr","Mai","Jui","Jul","Aug","Sep","Oct","Nov","Dec" };
		return arrMonths[monthIndex - 1];
	}
	string getShortMonthName() {
		return getShortMonthName(this->myDate.month);
	}

	static void printMonthCalendar(short month, short year) {
		int numberOfDays;
		int current = calculateDayOrder(1, month, year);
		numberOfDays = getDaysInMonth(month, checkIfLeapYear(year));

		printf("\n _______________%s__________________\n\n", getShortMonthName(month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
		int i;
		for (i = 0; i < current; i++) {
			printf("     ");
		}
		for (int j = 1; j <= numberOfDays; j++) {
			printf("%5d", j);

			if (++i == 7) {
				i = 0;
				printf("\n");
			}
		}

		printf("\n ____________________________________");

	}
	void printMonthCalendar() {
		printMonthCalendar(myDate.month, myDate.year);
	}

private:
	static void printYearCalendarHeader(short year) {
		cout << "___________________________________" << endl;
		cout << "          Calendar - " << year << endl;
		cout << "___________________________________" << endl;
	}

public:

	static void printYearCalendar(short year) {
		printYearCalendarHeader(year);
		for (int i = 1; i <= 12; i++) {
			printMonthCalendar(i, year);
			cout << endl;
		}
	}
	void printYearCalendar() {
		printYearCalendar(myDate.year);
	}

	static bool isDateValid(clsDate date) {
		short days = getDaysInMonth(date.myDate.month, checkIfLeapYear(date.myDate.year));
		if (date.myDate.month >= 1 && date.myDate.month <= 12) {
			if (date.myDate.day >= 1 && date.myDate.day <= days) {
				return true;
			}
			return false;
		}
		return false;
	}
	bool isValid() {
		return isDateValid(*this);
	}

	static bool isDateOneBeforeDateTwo(clsDate date1,clsDate date2) {
		return (date1.myDate.year < date2.myDate.year) ? true : (date1.myDate.year == date2.myDate.year) ? ((date1.myDate.month < date2.myDate.month) ? true : ((date1.myDate.month == date2.myDate.month) ? date1.myDate.day < date2.myDate.day : false)) : false;
	}
	bool isDateBeforeDateTwo(clsDate date) {
		return clsDate::isDateOneBeforeDateTwo(*this,date);
	}

	static void swapDates(clsDate& date1, clsDate& date2) {
		clsDate tempDate;
		tempDate = date1;

		date1 = date2;

		date2 = tempDate;
	}
	void swapDates(clsDate& date2) {
		swapDates(*this,date2);
	}

	static bool checkIfLastMonthInYear(short month) {
		return month == 12;
	}
	bool checkIfLastMonthInYear() {
		return checkIfLastMonthInYear(myDate.month);
	}

	static void increaseDateByOneDay(clsDate& date) {
		short monthDays = getDaysInMonth(date.myDate.month, checkIfLeapYear(date.myDate.year));
		if (date.myDate.day == monthDays) {
			date.myDate.day = 1;
			if (checkIfLastMonthInYear(date.myDate.month)) {
				date.myDate.month = 1;
				date.myDate.year++;
			}
			else {
				date.myDate.month++;
			}
		}
		else {
			date.myDate.day++;
		}
	}
	stDate increaseDateByOneDay() {
		 increaseDateByOneDay(*this);
	}

	static short calculateDifferenceBetweenTwoDates(clsDate date1, clsDate date2, bool isLastDayIncluded = false) {
		short daysCount = 0;
		short swapFlag = 1;
		if (!isDateOneBeforeDateTwo(date1, date2)) {
			swapDates(date1, date2);
			swapFlag = -1;
		}
		while (isDateOneBeforeDateTwo(date1, date2)) {
			daysCount++;
			increaseDateByOneDay(date1);
		}
		return isLastDayIncluded ? ++daysCount * swapFlag : daysCount * swapFlag;
	}
	static int calculateMyAgeInDays(clsDate date) {
		clsDate localDate;
		return calculateDifferenceBetweenTwoDates(date, localDate);
	}

	static clsDate getCurrentDate() {
		stDate date;
		time_t t = time(0);
		tm* now = localtime(&t);
		date.year = now->tm_year + 1900;
		date.month = now->tm_mon + 1;
		date.day = now->tm_mday;
		clsDate dateObj = clsDate(date.day, date.month, date.year);
		return dateObj;
	}

	static void increaseDateByXDays(clsDate& date, int days) {
		for (int i = 1; i <= days; i++) {
			increaseDateByOneDay(date);
		}
	}
	stDate increaseDateByXDays(int days) {
		 increaseDateByXDays(*this, days);
	}

	static void increaseDateByOneWeek(clsDate& date) {
		 increaseDateByXDays(date, 7);
	}
	void increaseDateByOneWeek() {
		 increaseDateByOneWeek(*this);
	}

	static void increaseDateByXWeeks(clsDate date, int weeks) {
		for (int i = 1; i <= weeks; i++) {
			increaseDateByOneWeek(date);
		}
	}
	void increaseDateByXWeeks(int weeks) {
		 increaseDateByXWeeks(*this, weeks);
	}

	static void increaseDateByOneMonth(clsDate& date) {
		if (date.myDate.month == 12) {
			date.myDate.month = 1;
			date.myDate.year++;
		}
		else {
			date.myDate.month++;
		}
		short numberOfDaysInMonth = getDaysInMonth(date.myDate.month, checkIfLeapYear(date.myDate.year));
		if (date.myDate.day > numberOfDaysInMonth) {
			date.myDate.day = numberOfDaysInMonth;
		}
	}
	void increaseDateByOneMonth() {
		return increaseDateByOneMonth(*this);
	}

	static void increaseDateByXMonths(clsDate& date, int months) {
		for (int i = 1; i <= months; i++) {
			increaseDateByOneMonth(date);
		}
	}
	stDate increaDateByXMonths(int months) {
		 increaseDateByXMonths(*this, months);
	}

	static void increaseDateByOneYear(clsDate& date) {
		date.myDate.year++;
	}
	stDate increaseDateByOneYear() {
		increaseDateByOneYear(*this);
	}

	static void increaseDateByXYears(clsDate& date, int years) {
		for (int i = 1; i <= years; i++) {
			increaseDateByOneYear(date);
		}
	}
	void increseDateByXYears(int years) {
		 increaseDateByXYears(*this, years);
	}

	static void increaseDateByXYearsFaster(clsDate& date, int years) {
		date.myDate.year += years;
	}
	stDate increseDateByXYearsFaster(int years) {
		increaseDateByXYearsFaster(*this, years);
	}

	static void increaseDateByOneDecade(clsDate& date) {
		date.myDate.year += 10;
	}
	void increaseDateByOneDecade() {
		increaseDateByOneDecade(*this);
	}

	static void increaseDateByXDecades(clsDate& date, int decades) {
		for (int i = 1; i <= decades; i++) {
			increaseDateByOneDecade(date);
		}
	}
	void increaseDateByXDecades(int decades) {
		increaseDateByXDecades(*this, decades);
	}

	static void increaseDateByOneCentury(clsDate& date) {
		increaseDateByXDecades(date, 10);
	}
	void increaseDateByOneCentury() {
		increaseDateByOneCentury(*this);
	}

	static void increaseDateByXCentries(clsDate& date, int centeries) {
		for (int i = 1; i < centeries; i++) {
			increaseDateByOneCentury(date);
		}
	}
	void increaseDateByXCentries(int centeries) {
		increaseDateByXCentries(*this, centeries);
	}

	static void increaseDateByOneMillennium(clsDate& date) {
		date.myDate.year += 1000;
	}
	void increaseDateByOneMillennium() {
		increaseDateByOneMillennium(*this);
	}

	static short calculateDayOrder(clsDate date) {
		return calculateDayOrder(date.myDate.day, date.myDate.month, date.myDate.year);
	}
	short calculateDayOrder() {
		return calculateDayOrder(*this);
	}

	static bool isEndOfWeek(clsDate date) {
		return calculateDayOrder(date) == 6;
	}
	bool isEndOfWeek() {
		return isEndOfWeek(*this);
	}

	static bool isWeekEnd(clsDate date) {
		return calculateDayOrder(date) == 5 || calculateDayOrder(date) == 6;
	}
	bool isWeekEnd() {
		return isWeekEnd(*this);
	}

	static bool isBusinessDay(clsDate date) {
		return !isWeekEnd(date);
	}
	bool isBusinessDay() {
		return isBusinessDay(*this);
	}

	static short daysUntilTheEndOfWeek(clsDate date) {
		return 6 - calculateDayOrder(date);
	}
	short daysUntilTheEndOfWeek() {
		return daysUntilTheEndOfWeek(*this);
	}

	static short daysUntilTheEndOfMonth(clsDate date) {
		clsDate endOfMonth = clsDate();
		endOfMonth.myDate.day = getDaysInMonth(date.myDate.month, checkIfLeapYear(date.myDate.year));
		endOfMonth.myDate.month = date.myDate.month;
		endOfMonth.myDate.year = date.myDate.year;
		return calculateDifferenceBetweenTwoDates(date, endOfMonth, true);
	}
	short daysUntilTheEndOfMonth() {
		return daysUntilTheEndOfMonth(*this);
	}

	static short daysUntilTheEndOfYear(clsDate date) {
		clsDate endOfYear;
		endOfYear.myDate.day = 31;
		endOfYear.myDate.month = 12;
		endOfYear.myDate.year = date.myDate.year;
		return calculateDifferenceBetweenTwoDates(date, endOfYear, true);
	}
	short daysUntilTheEndOfYear() {
		return daysUntilTheEndOfYear(*this);
	}

	static short calculateActualVacationDays(clsDate dateFrom,clsDate dateTo) {
		short vacDays = 0;
		if (!isDateOneBeforeDateTwo(dateFrom, dateTo)) {
			return 0;
		}
		while (isDateOneBeforeDateTwo(dateFrom, dateTo)) {
			if (isBusinessDay(dateFrom)) {
				vacDays++;
			}
			increaseDateByOneDay(dateFrom);
		}
		return vacDays;
	}
	short calculateActualVaccationDays(clsDate dateTo) {
		return calculateActualVacationDays(*this, dateTo);
	}

	static clsDate calculateVacationReturnDate(clsDate dateFrom, short vacDays) {
		while (vacDays > 0) {
			if (isBusinessDay(dateFrom)) {
				vacDays--;
			}
			increaseDateByOneDay(dateFrom);
		}
		return dateFrom;
	}
	void calculateVacationReturnDate(short vacDays) {
		 calculateVacationReturnDate(*this, vacDays);
	}

	static bool checkIfDateOneEqualDateTwo(clsDate date1,clsDate date2) {
		return (date1.myDate.year == date2.myDate.year) ? ((date1.myDate.month == date2.myDate.month) ? (date1.myDate.day == date2.myDate.day) : false) : false;
	}
	bool checkIfDateOneEqualDateTwo(clsDate date2) {
		return checkIfDateOneAfterDateTwo(*this,date2);
	}

	static bool checkIfDateOneAfterDateTwo(clsDate dateFrom,clsDate dateTo) {
		return (!isDateOneBeforeDateTwo(dateFrom, dateTo) && !checkIfDateOneEqualDateTwo(dateFrom, dateTo));
	}
	bool checkIfDateOneAfterDateTwo(clsDate dateTo) {
		return checkIfDateOneAfterDateTwo(*this, dateTo);
	}

private:
	static short readPositiveNumber(string message) {
		short year;
		cout << message;
		cin >> year;
		return year;
	}

public:

	static clsDate readFullDate() {
		clsDate date;
		date.myDate.day = readPositiveNumber("Please enter day? ");
		date.myDate.month = readPositiveNumber("please enter A month? ");
		date.myDate.year = readPositiveNumber("Please enter A Year? ");
		return date;
	}

	static eCompResult compareDates(clsDate date1, clsDate date2) {
		if (isDateOneBeforeDateTwo(date1, date2)) {
			return eCompResult::Before;
		}
		else if (checkIfDateOneEqualDateTwo(date1, date2)) {
			return eCompResult::Equal;
		}
		else {
			return eCompResult::After;
		}
	}
	eCompResult compareDates(clsDate date2) {
		return compareDates(*this, date2);
	}

	static clsDate stringToDate(string dateString) {
		clsDate date = clsDate();
		vector<string> vDate;
		vDate = clsString::splitString(dateString, "/");
		date.myDate.day = stoi(vDate[0]);
		date.myDate.month = stoi(vDate[1]);
		date.myDate.year = stoi(vDate[2]);
		return date;
	}

	static string  readStringDate(string message) {
		string date;
		cout << message << endl;
		getline(cin >> ws, date);
		return date;
	}
	void readString(string message) {
		this->stringDate = readStringDate(message);
	}

	static string dateToString(clsDate date) {
		string dateString = to_string(date.myDate.day) + "/" + to_string(date.myDate.month) + "/" + to_string(date.myDate.year);
		return dateString;
	}
	string dateToString() {
		return dateToString(*this);
	}
	static string replaceWordInString(string originalString, string stringToReplace, string newString) {
		short pos = originalString.find(stringToReplace);
		while (pos != string::npos) {
			originalString = originalString.replace(pos, stringToReplace.length(), newString);
			pos = originalString.find(stringToReplace);
		}
		return originalString;
	}

	static string formatDate(clsDate date, string dateFormat = "dd/mm/yyy") {
		string FormattedDateString = "";
		FormattedDateString = replaceWordInString(dateFormat, "dd", to_string(date.myDate.day));
		FormattedDateString = replaceWordInString(FormattedDateString, "mm", to_string(date.myDate.month));
		FormattedDateString = replaceWordInString(FormattedDateString, "yyy", to_string(date.myDate.year));
		return FormattedDateString;
	}
	string formatDate(string dateFormat = "dd/mm/yyy") {
		return formatDate(*this, dateFormat);
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

	static string getDateTimeString() {
		time_t t = time(0);
		tm* now = localtime(&t);
		return (to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec));
	}


	void print() {
		cout << this->myDate.day << "/" << this->myDate.month << "/" << this->myDate.year << endl;
	}
};

