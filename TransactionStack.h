#ifndef TRANSACTIONSTACK_H
#define TRANSACTIONSTACK_H

#include <iostream>
#include "Transaction.h"

struct Nodetrans {
    transaction data;
    Nodetrans* next;
    Nodetrans(const transaction& t) : data(t), next(nullptr) {}
};

struct stack {
    Nodetrans* top;
    stack() : top(nullptr) {}
};

#endif