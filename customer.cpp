#include"LoanListMeth.h"
#include"LoanRequestMeth.h"
#include"customer.h"
#include"TransactionStackMeth.h"
#include"transaction.h"
#include<iostream>
#include<string>
#include"TransactionStack.h"
#include"Date.h"
using namespace std;
stack* dailyTransaction = createStack();
queue *Request= createQueue();

//1)login function : 
customer* login(customer customers[], int n) {
    string acc, pass;
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

void displayLoanList(customer*c) {
    if (c==nullptr) {
        cout << "no customer providedd." << endl; "  
            return;
    }
    displayLoan(c->loans);
}

//3)submit new loan request
void SubmitLoanRequest(LoanRequest q) {

}


// 4)a/ deposit 
void depositMoney(customer* c) {
    float amount;
    cout << " enter deposit amount: " << endl;
    cin >> amount;
    if (amount <= 0) {
        cout << "invalid amount. " << endl;
        return;
    }
	date d = getDateFromCustomer();
    c->balance += amount;
    transaction t;
    t.ID = rand();
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
    if(intAmount % 10!=0) {
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
    t.ID = rand();
    t.AccountNum = c->AccNum;
    t.TransType = "withdrawal";
    t.Amount = amount;
    t.TransDate = d;
    push(dailyTransaction, t);
	cout << "withdrawal successful. new balance: " << c->balance << endl;

}


//5) view today transactions

void viewTodayTransactions() {
    if (isEmptyTransaction(dailyTransaction)) {
        cout << "\n no transactions today.";
        return;
    }
    cout << "\n-----Today's transactions----\n";
    while (!isEmptyTransaction(temp)) {
        transaction t = temp.top();
        pop(dailyTransaction);
        cout << t.type << " Amount: " << t.amount << " date: " << t.date << endl;
    }
}//6) 

//6)undo last transaction
void UndoLastTransaction(transaction* s) {
    if (isEmptyTransaction(*s) {
        cout << "nothing to undo " << endl;
        return;
    }
    transaction peek(*s);
}

// generate date

date getDateFromCustomer() {
    date d;
	cout << "enter day: ";
    cin >> d.day;
    cout << "enter month: ";
    cin >> d.month;
    cout << "enter year: ";;
    cin >> d.year;
    return d;
}

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
            displayLoanList(c->loans);
            break;
        case '2':
            SubmitLoanRequest(c);
            break;
        case '3':
            depositMoney(c);
            break;
        case '4':
            withdrawMoney(c);
            break;
        case'5':
            viewTodayTransactions();
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

    } while (choice <=6 && choice>0);
}
