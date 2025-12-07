#ifndef COMPLETEDLOANLISTMETH_H
#define COMPLETEDLOANLISTMETH_H

#include "CompletedLoanList.h"
#include "Customer.h" // for types only if needed; safe to include
NodeCompLoan* createLoanNode(const loan& value);
void destroyLoanNode(NodeCompLoan* n);

CompList* createCompList();
void destroyCompList(CompList* L);

void addCompLoan(CompList* L, const loan& l);
void displayCompList(const CompList& L);

#endif 