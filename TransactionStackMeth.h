#ifndef TRANSACTIONSTACKMETH_H
#define TRANSACTIONSTACKMETH_H

#include "Transaction.h"
#include "TransactionStack.h"
#include <iostream>
using namespace std;

// stack using singly linked list
Nodetrans* CreateNodetrans(const transaction& data);
void destroyTransNode(Nodetrans* n);

stack* createStack();
void destroyStack(stack* s);

bool isEmptyTransaction(const stack& s);
bool isFull(const stack& s); // memory probe

void displaystack(const stack& s);
int stackSize(const stack& s);

int push(stack* s, const transaction& data);
void pop(stack* s);
transaction peek(const stack& s);

stack* copyStack(const stack& s);
bool compareStack(const stack& s1, const stack& s2);

#endif