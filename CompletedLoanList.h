#ifndef COMPLETEDLOANLIST_H
#define COMPLETEDLOANLIST_H

#include "Loan.h"
#include <iostream>
using namespace std;

struct NodeCompLoan {
    loan data;
    NodeCompLoan* next;
    NodeCompLoan(const loan& l) : data(l), next(nullptr) {}
};

struct CompList {
    NodeCompLoan* head;
    CompList() : head(nullptr) {}
};

#endif