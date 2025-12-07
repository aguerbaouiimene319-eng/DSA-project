#include"LoanListMeth.h"
#include"LoanRequestMeth.h"
#include"customer.h"
#include"TransactionStackMeth.h"
#include"transaction.h"
#include"Date.h"
#include<iostream>
#include<string>
using namespace std;

void displayLoanList(customer* c);
void submitLoanRequest(customer* c);
void depositMoney(customer* c);
void withdrawMoney(customer* c);
void viewTodayTransactions(customer* c);
void UndoLastTransaction(customer* c);
date getDateFromCustomer();
bool transactionIdExists(stack* s, int id);
int generateUniqueTransactionID(stack* s);


stack* dailyTransaction = createStack();
queue* Request = createQueue();

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
        case '1':
            displayLoanList(c);
            break;
        case '2':
            submitLoanRequest(c);
            break;
        case '3':
            depositMoney(c);
            break;
        case '4':
            withdrawMoney(c);
            break;
        case'5':
            viewTodayTransactions(c);
            break;
        case '6':
            UndoLastTransaction(c);
            break;
        case '0':
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid option.\n";
        }

    } while (choice <= '6' && choice != '0');
}

//1)login function : 
customer* login(customer customers[], int n) {// n is the size of the array of customers
    int acc;
    string pass;
    int attempt = 0;
    do {

        cout << "\n--- CUSTOMER LOGIN ---\n";
        cout << "Account Number: ";
        cin >> acc;
        cout << "Password: ";
        cin >> pass;

        for (int i = 0; i < n; i++) {
            if (customers[i].AccNum == acc &&
                customers[i].passwrd == pass) {

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

//2) view the list of loans

void displayLoanList(customer* c) {
    if (c == nullptr) {
        cout << "no customer providedd." << endl; 
        return;
    }
    displayLoan(c->loans);
}

//3)submit new loan request
void submitLoanRequest(customer* c) {
    cout << "\n=== Submit Loan Request ===\n";

    LoanRequest newLoan = {};
    cout << "enter the ID of the loan" << endl;
    newLoan.requestAccNumber = c->AccNum;

    //newLoan.ID= generateLoanId();
    cout << "Loan Type (car/home/student/business): ";
    cin >> newLoan.loanType;

    cout << "Principal Amount (TND): ";
    cin >> newLoan.PrincipleAmount;

    cout << "enter the request date (DD//MM/YYYY) " << endl;
    cin >> newLoan.RequestDate.day >> newLoan.RequestDate.month >> newLoan.RequestDate.year;

    cout << "Loan end date (DD//MM/YYYY) : " << endl;
    cin >> newLoan.EndDate.day >> newLoan.EndDate.month >> newLoan.EndDate.year;

    cout << "loan start date (DD//MM/YYYY) " << endl;
    cin >> newLoan.StartDate.day >> newLoan.StartDate.month >> newLoan.StartDate.year;

    Enqueue(Request, newLoan);
    cout << "loan request submitted successfully ." << endl;
}

// 4)a/ deposit 
void depositMoney(customer* c) {
    float amount;
    cout << " enter deposit amount: " << endl;
    cin >> amount;
    if (amount <= 0) {
        cout << "invalid amount. it must be positive " << endl;
        return;
    }
    date d = getDateFromCustomer();
    c->balance += amount;
    transaction t;
    bool exist = false;
    t.ID = generateUniqueTransactionID(dailyTransaction);  
    t.AccountNum = c->AccNum;
    t.TransType = "deposit";
    t.Amount = amount;
    t.TransDate = d;

    push(dailyTransaction, t);
    cout << "deposit successful. new balance: " << c->balance << endl;
}

// 4)b/ withdrawal

void withdrawMoney(customer* c) {

    float amount;
    cout << "enter withdrawal amount: " << endl;
    cin >> amount;
    int intAmount = (int)amount;
    if (intAmount % 10 != 0 || amount<=0) {
        cout << "withdrawal failed, amount should be in multiples of 10,20,50" << endl;
        return;
    }
    if (amount > c->balance) {
        cout << "withdrawal failed, insufficient balance. " << endl;
        return;

    }
    date d = getDateFromCustomer();

    c->balance -= amount;

    transaction t;
    t.ID = generateUniqueTransactionID(dailyTransaction);
    t.AccountNum = c->AccNum;
    t.TransType = "withdrawal";
    t.Amount = amount;
    t.TransDate = d;
    push(dailyTransaction, t);
    cout << "withdrawal successful. new balance: " << c->balance << endl;

}

//5) view today transactions

void viewTodayTransactions(customer* c) {
    if (isEmptyTransaction(*dailyTransaction)) {
        cout << "\nNo transactions today.";
        return;
    }

    stack* temper = copyStack(*dailyTransaction);   // copy stack header (OK)
    cout << "\n-----Today's transactions-----\n";

    while (!isEmptyTransaction(*temper)) {
        transaction t =temper->top->data ;
        pop(temper);   // pop from temper only

        cout << t.TransType
            << " | Amount: " << t.Amount
            << " | Date: " << t.TransDate.day << t.TransDate.month << t.TransDate.year << endl;
    }
}


//6) undo last transaction
void UndoLastTransaction(customer*c) {
    if (isEmptyTransaction(*dailyTransaction)) {
        cout << "no transactions to undo" << endl;
        return;
    }
    transaction t = peek(*dailyTransaction);
    if (t.TransType == "deposit") {
        c->balance -= t.Amount;
        cout << "undo deposit!" << t.Amount << "TND" << endl;
    }
    else if (t.TransType == "withdrawal") {
        c->balance += t.Amount;
        cout << "undo withdrawal!" << t.Amount << "TND" << endl;
    }
    pop(dailyTransaction);
    cout << "last transaction undone. New balance:" << c->balance << endl;
}

// generate date

date getDateFromCustomer() {
    date d = {};
    cout << "enter day: ";
    cin >> d.day;
    cout << "enter month: ";
    cin >> d.month;
    cout << "enter year: ";;
    cin >> d.year;
    return d;
}
#include <cstdlib>

// Checks if an ID already exists in the stack
bool transactionIdExists(stack* s, int id) {
    Nodetrans* curr = s->top;
    while (curr) {
        if (curr->data.ID == id) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Generates a unique transaction ID
int generateUniqueTransactionID(stack* s) {
    int id;
    do {
        id = rand();
    } while (transactionIdExists(s, id));

    return id;
}
