#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
using namespace std;

// Forward declarations
struct date;
struct Loan;
struct Transaction;
struct LoanNode;
struct TransactionNode;
struct Transactionstack;
struct TransactionlistNode;
struct LoanList;
struct LoanRequestQueue;
struct BankSystem;
struct account;
struct employee;


// Date structure
struct Date {
    int day;
    int month;
    int year;
};

// Loan structure
struct Loan {
    string loanId;
    string loanType; // car, home, student, business
    double principalAmount;
    double interestRate;
    double amountPaid;
    double remainingBalance;
    Date startDate;
    Date endDate;
    string status; // active, completed, overdue
};

// Loan Node for doubly linked list
struct LoanNode {
    Loan data;
    LoanNode* next;
    LoanNode* prev;
};

// Transaction structure
struct Transaction {
    string transactionId;
    string accountNumber;
    string type; // deposit, withdrawal
    double amount;
    Date date;
};

// Transaction Node for stack
struct TransactionNode {
    Transaction data;
    TransactionNode* next;
};

// Transaction Stack
struct TransactionStack {
    TransactionNode* top;
    int size;
};

// Transaction List Node (singly linked list)
struct TransactionListNode {
    Transaction data;
    TransactionListNode* next;
};

// Loan Doubly Linked List
struct LoanList {
    LoanNode* head;
    LoanNode* tail;
    int size;
};

// Customer Account structure
struct Account {
    string accountNumber;
    string accountType;
    string iban;
    string branchCode;
    string holderName;
    Date openingDate;
    string status; // active, inactive, closed
    double balance;
    LoanList loans;
    TransactionStack dailyTransactions;
    string password; // for login
};

// Employee structure
struct Employee {
    string id;
    string name;
    string lastName;
    string address;
    double salary;
    Date hireDate;
    string branchCode; // "1" for head office
};

// Loan Request Node for queue
struct LoanRequestNode {
    Loan data;
    string accountNumber;
    Date requestDate;
    LoanRequestNode* next;
};

// Loan Request Queue
struct LoanRequestQueue {
    LoanRequestNode* front;
    LoanRequestNode* rear;
    int size;
};

// Constants
const int MAX_ACCOUNTS = 1000;
const int MAX_EMPLOYEES = 500;
const int MAX_ARCHIVED_ACCOUNTS = 1000;

// Global data structures
struct BankSystem {
    Account accounts[MAX_ACCOUNTS];
    int accountCount;

    Account archivedAccounts[MAX_ARCHIVED_ACCOUNTS];
    int archivedCount;

    Employee employees[MAX_EMPLOYEES];
    int employeeCount;

    LoanRequestQueue loanRequests;

    TransactionListNode* completedLoans; // singly linked list

    bool dayFinalized;
};

#endif // STRUCTURES_H
