#ifndef LOANLISTMETH_H
#define LOANLISTMETH_H

#include<string>
#include"LoanList.h"

using namespace std;

Nodelist* createloan(loan L);
void destroyLoan(loan* loan);

LoanList* createList();
void destroyList(LoanList* L);

bool isEmpty(const LoanList& L);
bool isFull(const LoanList& L);
int ListSize(const LoanList& L);

int addLoan(LoanList* L, loan l, int pos);
int deleteLoan(LoanList* L, int pos);
loan getElement(const LoanList& L, int pos);
LoanList copyList(const LoanList& L);
void displayLoan(const LoanList& L);
void compareLists(LoanList& L1, LoanList& L2);

#endif