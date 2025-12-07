#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Customer.h"
#include "Employee.h"
#include "Loan.h"
#include "Transaction.h"
#include"CompletedLoanListMeth.h"
#include"LoanRequest.h"


// Employees
int loadEmployees(employee employees[], int maxSize);
void saveEmployees(employee employees[], int size);

// Customers
int loadCustomers(customer customers[], int maxSize);
void saveCustomers(customer customers[], int size);

// Loans (per customer)
int loadLoans(LoanList* loanList, int accNum);
void saveLoans(const LoanList& loanList, int accNum);

// Transactions (per customer)
int loadTransactions(stack* s, int accNum);
void saveTransactions(const stack& s, int accNum);
// Archived Accounts
int loadArchivedAccounts(customer archived[], int maxSize);
void saveArchivedAccounts(customer archived[], int size);

// Completed Loans
int loadCompletedLoans(CompList* list);
void saveCompletedLoans(const CompList& list);

// Loan Requests
int loadLoanRequests(queue* q);
void saveLoanRequests(const queue& q);

// System State (e.g., last used IDs)
void loadSystemState(int& lastLoanID, int& lastTransactionID);
void saveSystemState(int lastLoanID, int lastTransactionID);

#endif