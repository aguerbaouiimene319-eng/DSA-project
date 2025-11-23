#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<string>
using namespace std;

struct customer {
	int AccNum;
	string AccType;
	int IBAN;
	int Branch;
	string name;
	string OpDate;
	string statute;
	float balance;
};
#endif
