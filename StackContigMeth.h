#ifndef STACKCONTIGMETH_H
#define STACKCONTIGMETH_H

#include"StackContig.h"
#include<iostream>"
using namespace std;

stack* createStack();
void destroyStack(stack* s);

bool isEmpty(const stack& s);
bool isFull(const stack& s);
int stackSize(const stack& s);
void displaystack(const stack& s);

int push(stack s, int e);
int pop(stack s);
int top(const stack& s);

stack* copyStack(const stack& s);
bool compareStack(const stack& s1, const stack& s2);

#endif