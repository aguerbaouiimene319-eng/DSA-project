#ifndef TRANSACTIONSTACKMETH_H
#define TRANSACTIONSTACKMETH_H

#include"TransactionStack.h"
#include<iostream>
using namespace std;

//stack using singly linked list 

Nodetrans* CreateNodetrans(transaction data);
void destroyNode(Nodetrans* n);
stack* createStack();
void destroyStack(stack* s);

bool isEmptyTransaction(const stack& s);
bool isFull(const stack& s);
void displaystack(const stack& s);
int stackSize(const stack& s);

int push(stack* s, transaction data);
void pop(stack* s);
transaction peek(const stack& s);

stack* copyStack(const stack& s);
bool compareStack(const stack& s1, const stack& s2);

#endif