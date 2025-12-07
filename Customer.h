#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Date.h"
#include "LoanListMeth.h"
#include "Transaction.h"
#include "TransactionStackMeth.h"
#include <string>
using namespace std;

struct customer {
    string passwrd;
    int AccNum{};
    string AccType;
    int IBAN{};      // if IBAN should be numeric; consider string for real
    int Branch{};
    string name;
    date OpDate{};
    string status;   // active, inactive, closed
    float balance{};

    LoanList loans;  // doubly linked list of loans
    stack transList; // daily transactions stack
};

#endif