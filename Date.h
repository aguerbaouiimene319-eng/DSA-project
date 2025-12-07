#ifndef DATE_H
#define DATE_H
#include<string>
#include<iostream>
using namespace std;

struct date {

	int day;
	int month;
	int year;

	string stringDate() const {
		string Day = to_string(day);
		string Month = to_string(month);
		string Year = to_string(year);
		return Day + "/" + Month + "/" + Year;
	}
};
#endif
