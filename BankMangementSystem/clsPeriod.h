#pragma once

#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include "clsDate.h";

using namespace std;


class clsPeriod
{
	struct stDate
	{
		short day;
		short month;
		short year;

	};
private:
	clsDate startDate;
	clsDate endDate;


public:

	clsPeriod() {
		startDate = clsDate::getCurrentDate();
		endDate = clsDate::getCurrentDate();
	}
	clsPeriod(clsDate startDate, clsDate endDate) {
		this->startDate = startDate;
		this->endDate = endDate;
	}
	clsPeriod(string startDate, string endDate) {
		this->startDate = clsDate::stringToDate(startDate);
		this->endDate = clsDate::stringToDate(startDate);
	}


	static bool isPeriodsOverlap(clsPeriod period1, clsPeriod period2) {
		if (clsDate::isDateOneBeforeDateTwo(period1.endDate, period2.startDate) ||
			clsDate::checkIfDateOneAfterDateTwo(period1.startDate, period2.endDate)) {
			return false;
		}
		else {
			return true;
		}
	}
	bool isPeriodOverlapWith(clsPeriod period2) {
		return isPeriodsOverlap(*this, period2);
	}

	void Print()
	{
		cout << "Period Start: ";
		startDate.print();


		cout << "Period End: ";
		endDate.print();


	}

};

