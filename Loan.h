#ifndef LOAN_H
#define LOAN_H

#include <iostream>
#include <string>
#include "Date.h"
using namespace std;

struct loan {
    int ID{};
    string type;          // car, home, student, business
    float amount{};
    float InterestRate{}; // e.g., 0.08
    float AmPaid{};
    float ReBalance{};
    date StartDate{};
    date EndDate{};
    string LoanStatus;    // active, completed, overdue
};

#endif