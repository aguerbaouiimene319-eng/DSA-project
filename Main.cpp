#include <iostream>
#include <string>
#include "Customer.h"
#include"FileHandler.h"

// Forward declarations from interfaces
customer* login(customer customers[], int n);
void customerMenu(customer* c);
void employeeInterface();

using namespace std;

// Demo seed (optional)
void seedDemo(customer arr[], int& n) {
    customer c{};
    c.AccNum = 1001;
    c.passwrd = "1234";
    c.name = "Imen";
    c.AccType = "current";
    c.IBAN = 5910;
    c.Branch = 1;
    c.OpDate = { 5,1,2025 };
    c.status = "active";
    c.balance = 1200.0f;

    LoanList* ll = createList();
    c.loans = *ll; delete ll;
    stack* st = createStack();
    c.transList = *st; delete st;

    arr[0] = c;
    n = 1;
}

int main() {
    cout << "=========Welcome to the Banking Management System========\n";
    cout << "=========1. Customer interface==============\n";
    cout << "=========2. Employee interface==============\n";
    cout << "=========3. Exit==========\n";

    // Demo customers (replace with file load if desired)
    customer customers[100]{};
    int nCustomers = 0;
    seedDemo(customers, nCustomers);

    while (true) {
        cout << "\nChoice: ";
        int choice; cin >> choice;
        if (choice == 1) {
            customer* c = login(customers, nCustomers);
            if (c) customerMenu(c);
        }
        else if (choice == 2) {
            employeeInterface();
        }
        else if (choice == 3) {
            cout << "Goodbye.\n";
            break;
        }
        else {
            cout << "Invalid.\n";
        }
    }
    return 0;
}


#include <iostream>
#include "FileHandler.h"
#include "Customer.h"
#include "Employee.h"
#include "LoanListMeth.h"
#include "TransactionStackMeth.h"
#include "LoanRequestMeth.h"
#include "CompletedLoanListMeth.h"

using namespace std;

// Global arrays and structures
constexpr int Max_customers = 10000;
constexpr int Max_employees = 2000;

employee employeeArray[Max_employees];
customer customerArray[Max_customers];
customer archivedAccounts[Max_customers];

CompList* completedloans = createCompList();
queue* loanRequests = createQueue();
stack* dailyTransaction = createStack();

int employeeCount = 0;
int customerCount = 0;

// Helper functions (already defined elsewhere)
int sizeofarrayCustomer(customer customerArray[]);
int sizeofarrayEmployee(employee employeeArray[]);
customer* login(customer customers[], int n);
void customerMenu(customer* c);
void employeeInterface();

int main() {
    // Load data
    employeeCount = loadEmployees(employeeArray, Max_employees);
    customerCount = loadCustomers(customerArray, Max_customers);

    for (int i = 0; i < customerCount; i++) {
        loadLoans(&customerArray[i].loans, customerArray[i].AccNum);
        loadTransactions(&customerArray[i].transList, customerArray[i].AccNum);
    }

    loadArchivedAccounts(archivedAccounts, Max_customers);
    loadCompletedLoans(completedloans);
    loadLoanRequests(loanRequests);

    // Main menu loop
    char choice;
    do {
        cout << "\n====== BANKING MANAGEMENT SYSTEM ======\n";
        cout << "1. Customer Interface\n";
        cout << "2. Employee Interface\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case '1': {
            customer* c = login(customerArray, sizeofarrayCustomer(customerArray));
            if (c) customerMenu(c);
            break;
        }
        case '2':
            employeeInterface();
            break;
        case '0':
            cout << "\nExiting system. Goodbye!\n";
            break;
        default:
            cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != '0');

    // Optional: Save system state (e.g., last used IDs)
    // saveSystemState(lastLoanID, lastTransactionID);

    // Cleanup
    destroyCompList(completedloans);
    destroyQueue(loanRequests);
    destroyStack(dailyTransaction);

    return 0;
}