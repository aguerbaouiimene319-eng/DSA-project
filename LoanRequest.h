#ifndef LOANREQUEST_H
#define LOANREQUEST_H

#include <iostream>
#include <string>
#include "Date.h"
using namespace std;

struct LoanRequest {
    int requestAccNumber{};
    string loanType;
    double PrincipleAmount{};
    date StartDate{};
    date EndDate{};
    date RequestDate{};
};

struct LRNode {
    LoanRequest data;
    LRNode* next;
    LRNode(const LoanRequest& r) : data(r), next(nullptr) {}
};

struct queue {
    LRNode* front; // ptr to first element
    LRNode* tail;  // ptr to last element
    queue() : front(nullptr), tail(nullptr) {}
};

#endif