#include "LoanListMeth.h"
#include "LoanRequestMeth.h"
#include "Customer.h"
#include "TransactionStackMeth.h"
#include "Transaction.h"
#include "Date.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "FileHandler.h"
using namespace std;

extern employee employeeArray[2000];
extern customer customerArray[10000];
extern customer archivedAccounts[10000];

extern int employeeCount;
extern int customerCount;

int sizeofarrayCustomer(customer customerArray[]);

// global per-session daily stack (as in your file)
stack* dailyTransaction = createStack();
queue* Request = createQueue();

void displayLoanList(customer* c);
void submitLoanRequest(customer* c);
void depositMoney(customer* c);
void withdrawMoney(customer* c);
void viewTodayTransactions(customer* c);
void UndoLastTransaction(customer* c);

date getDateFromCustomer();
bool transactionIdExists(stack* s, int id);
int generateUniqueTransactionID(stack* s);

void customerMenu(customer* c) {
    char choice;
    do {
        cout << "\n\n===== CUSTOMER MENU =====\n";
        cout << "1. View Loans\n";
        cout << "2. Request Loan\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. View Today Transactions\n";
        cout << "6. Undo Last Transaction\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice) {
        case '1': displayLoanList(c); break;
        case '2': submitLoanRequest(c); break;
        case '3': depositMoney(c); break;
        case '4': withdrawMoney(c); break;
        case '5': viewTodayTransactions(c); break;
        case '6': UndoLastTransaction(c); break;
        case '0': cout << "Logging out...\n"; break;
        default: cout << "Invalid option.\n";
        }
    } while (choice != '0');
}

// Login
customer* login(customer customers[], int n) {
    int acc; string pass; int attempt = 0;
    do {
        cout << "\n--- CUSTOMER LOGIN ---\n";
        cout << "Account Number: "; cin >> acc;
        cout << "Password: "; cin >> pass;
        for (int i = 0; i < n; i++) {
            if (customers[i].AccNum == acc && customers[i].passwrd == pass) {
                if (customers[i].status != "active") {
                    cout << "\nYour account is inactive.\n";
                    return nullptr;
                }
                cout << "\nLogin successful! Welcome, " << customers[i].name << "!\n";
                return &customers[i];
            }
        }
        cout << "\nIncorrect account number or password.\n";
        attempt++;
    } while (attempt < 3);
    cout << "\nAccess denied.\n";
    return nullptr;
}

// 2) View loans
void displayLoanList(customer* c) {
    if (!c) { cout << "No customer provided.\n"; return; }
    displayLoan(c->loans);
}

// 3) submit loan request
void submitLoanRequest(customer* c) {
    cout << "\n=== Submit Loan Request ===\n";
    LoanRequest newLoan{};
    newLoan.requestAccNumber = c->AccNum;

    cout << "Loan Type (car/home/student/business): ";
    cin >> newLoan.loanType;
    cout << "Principal Amount (TND): ";
    cin >> newLoan.PrincipleAmount;

    cout << "Enter request date (DD MM YYYY): ";
    cin >> newLoan.RequestDate.day >> newLoan.RequestDate.month >> newLoan.RequestDate.year;
    cout << "Loan end date (DD MM YYYY): ";
    cin >> newLoan.EndDate.day >> newLoan.EndDate.month >> newLoan.EndDate.year;
    cout << "Loan start date (DD MM YYYY): ";
    cin >> newLoan.StartDate.day >> newLoan.StartDate.month >> newLoan.StartDate.year;

    if (Enqueue(Request, newLoan)) cout << "Loan request submitted successfully.\n";
    // Save loan requests queue to file (optional if you want persistence)
    else cout << "Failed to submit: queue full.\n";
}

// 4a) deposit
void depositMoney(customer* c) {
    double amount;
    cout << "Enter deposit amount: "; cin >> amount;
    if (amount <= 0) { cout << "Invalid amount. Must be positive.\n"; return; }

    date d = getDateFromCustomer();
    c->balance += (float)amount;
    saveCustomers(customerArray, sizeofarrayCustomer(customerArray));
    saveTransactions(c->transList, c->AccNum);

    transaction t;
    t.ID = generateUniqueTransactionID(dailyTransaction);
    t.AccountNum = c->AccNum;
    t.TransType = "deposit";
    t.Amount = amount;
    t.TransDate = d;

    push(dailyTransaction, t);
    cout << "Deposit successful. New balance: " << c->balance << "\n";
}

// 4b) withdrawa
void withdrawMoney(customer* c) {
    int amount;
    cout << "Enter withdrawal amount (multiples of 10): "; cin >> amount;
    if (amount <= 0 || amount % 10 != 0) {
        cout << "Withdrawal failed: amount must be multiple of 10.\n"; return;
    }
    if (amount > (int)c->balance) {
        cout << "Withdrawal failed: insufficient balance.\n"; return;
    }

    date d = getDateFromCustomer();
    c->balance -= (float)amount;
    saveCustomers(customerArray, sizeofarrayCustomer(customerArray));
    saveTransactions(c->transList, c->AccNum);
    transaction t;
    t.ID = generateUniqueTransactionID(dailyTransaction);
    t.AccountNum = c->AccNum;
    t.TransType = "withdrawal";
    t.Amount = amount;
    t.TransDate = d;

    push(dailyTransaction, t);
    cout << "Withdrawal successful. New balance: " << c->balance << "\n";
}

// 5) view today's transactions
void viewTodayTransactions(customer* c) {
    if (isEmptyTransaction(*dailyTransaction)) {
        cout << "\nNo transactions today.\n";
        return;
    }
    stack* temper = copyStack(*dailyTransaction);
    cout << "\n----- Today's transactions -----\n";
    while (!isEmptyTransaction(*temper)) {
        transaction t = peek(*temper);
        pop(temper);
        cout << t.TransType << " | Amount: " << t.Amount
            << " | Date: " << t.TransDate.stringDate() << "\n";
    }
    destroyStack(temper);
}

// 6) undo last transaction
void UndoLastTransaction(customer* c) {
    if (isEmptyTransaction(*dailyTransaction)) {
        cout << "No transactions to undo\n"; return;
    }
    transaction t = peek(*dailyTransaction);
    if (t.TransType == "deposit") {
        c->balance -= (float)t.Amount;
        cout << "Undo deposit of " << t.Amount << " TND\n";
    }
    else if (t.TransType == "withdrawal") {
        c->balance += (float)t.Amount;
        cout << "Undo withdrawal of " << t.Amount << " TND\n";
    }
    pop(dailyTransaction);
    saveCustomers(customerArray, sizeofarrayCustomer(customerArray));
    saveTransactions(c->transList, c->AccNum);
    cout << "Last transaction undone. New balance: " << c->balance << "\n";
}

// date input
date getDateFromCustomer() {
    date d{};
    cout << "Enter day: "; cin >> d.day;
    cout << "Enter month: "; cin >> d.month;
    cout << "Enter year: "; cin >> d.year;
    return d;
}

// ID helpers
bool transactionIdExists(stack* s, int id) {
    if (!s) return false;
    Nodetrans* curr = s->top;
    while (curr) {
        if (curr->data.ID == id) return true;
        curr = curr->next;
    }
    return false;
}

int generateUniqueTransactionID(stack* s) {
    int id;
    do { id = rand(); } while (transactionIdExists(s, id));
    return id;
}