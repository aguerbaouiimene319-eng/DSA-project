#ifndef LOANLIST_H
#define LOANLIST_H

#include "Loan.h"
#include <iostream>

struct Nodelist {
    loan data;
    Nodelist* next;
    Nodelist* prev;
    Nodelist() : next(nullptr), prev(nullptr) {}
};

struct LoanList {
    Nodelist* head;
    Nodelist* tail;
    LoanList() : head(nullptr), tail(nullptr) {}
};

#endif