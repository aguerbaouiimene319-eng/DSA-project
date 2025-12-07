#ifndef COMPLETEDLOANLISTMETH_H
#define COMPLETEDLOANLISTMETH_H
#include"CompletedLoanList.h"
#include"customer.h"

NodeCompLoan* createLoanNode(loan value);
void destroyLoanNode(NodeCompLoan*n);
CompList* createCompList();
void destroyList(CompList*L);

void addCompLoan(CompList* L, loan l);
void displayCompList(const CompList& L);

#endif // !COMPLETEDLOANLISTMETH_H
