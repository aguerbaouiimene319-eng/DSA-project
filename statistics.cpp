#include "Date.h"
#include "BankSystem.h"
#include "LoanListMeth.h"
#include "employeeInterface.cpp"
#include <iostream>
using namespace std;

// ===================== MAIN STATISTICS FUNCTION =====================

void statistics_1() {
    int sizecustomer = sizeofarrayCustomer(customerArray);
    int sizeemployee = sizeofarrayEmployee(employeeArray);

    int totalLoans = 0;
    int loansByType[4] = { 0 };
    int loansByStatus[3] = { 0 };

    for (int i = 0; i < sizecustomer; i++) {
        Nodelist* current = customerArray[i].loans.head;
        while (current != nullptr) {
            totalLoans++;

            if (current->data.type == "car") loansByType[0]++;
            else if (current->data.type == "home") loansByType[1]++;
            else if (current->data.type == "student") loansByType[2]++;
            else if (current->data.type == "business") loansByType[3]++;

            if (current->data.LoanStatus == "active") loansByStatus[0]++;
            else if (current->data.LoanStatus == "completed") loansByStatus[1]++;
            else if (current->data.LoanStatus == "overdue") loansByStatus[2]++;

            current = current->next;
        }
    }

    cout << "\n1. Total Loans: " << totalLoans << "\n";

    cout << "\n2. Loans by Type:\n";
    cout << "   Car: " << loansByType[0] << "\n";
    cout << "   Home: " << loansByType[1] << "\n";
    cout << "   Student: " << loansByType[2] << "\n";
    cout << "   Business: " << loansByType[3] << "\n";

    cout << "\n3. Loans by Status:\n";
    cout << "   Active: " << loansByStatus[0] << "\n";
    cout << "   Completed: " << loansByStatus[1] << "\n";
    cout << "   Overdue: " << loansByStatus[2] << "\n";

    // Customer with most loans
    int maxLoans = 0;
    string customerMaxLoans = "";
    for (int i = 0; i < sizecustomer; i++) {
        if (ListSize(customerArray[i].loans) > maxLoans) {
            maxLoans = ListSize(customerArray[i].loans);
            customerMaxLoans = customerArray[i].name;
        }
    }

    cout << "\n5. Customer with Most Loans: "
        << customerMaxLoans << " (" << maxLoans << " loans)\n";

    // Balance stats
    if (sizecustomer > 0) {
        int maxBalIdx = 0, minBalIdx = 0;
        for (int i = 1; i < sizecustomer; i++) {
            if (customerArray[i].balance > customerArray[maxBalIdx].balance)
                maxBalIdx = i;

            if (customerArray[i].balance < customerArray[minBalIdx].balance)
                minBalIdx = i;
        }

        cout << "\n6. Highest Balance: "
            << customerArray[maxBalIdx].name << " - "
            << customerArray[maxBalIdx].balance << " TND\n";

        cout << "\n7. Lowest Balance: "
            << customerArray[minBalIdx].name << " - "
            << customerArray[minBalIdx].balance << " TND\n";
    }

    // Employee stats
    int size = sizeofarrayEmployee(employeeArray);
    cout << "\n8. Total Employees: " << size << "\n";

    string branches[Max_employees];
    int branchCounts[Max_employees] = { 0 };
    int uniqueBranches = 0;

    for (int i = 0; i < size; i++) {
        bool found = false;
        for (int j = 0; j < uniqueBranches; j++) {
            if (branches[j] == employeeArray[i].BankBranch) {
                branchCounts[j]++;
                found = true;
                break;
            }
        }
        if (!found) {
            branches[uniqueBranches] = employeeArray[i].BankBranch;
            branchCounts[uniqueBranches] = 1;
            uniqueBranches++;
        }
    }

    cout << "\n9. Employees per Branch:\n";
    for (int i = 0; i < uniqueBranches; i++) {
        cout << "   Branch " << branches[i] << ": "
            << branchCounts[i] << " employees\n";
    }

    cout << "\n================================\n";
}


// ==================== HELPER FUNCTIONS =====================

int countLoans(Nodelist* head) {
    int count = 0;
    Nodelist* temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

int countPaidLoans(Nodelist* head) {
    int count = 0;
    Nodelist* temp = head;

    while (temp != NULL) {
        if (temp->data.AmPaid == temp->data.ReBalance) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

int isDateBetween(date d, date start, date end) {
    if (d.year < start.year || d.year > end.year)
        return 0;

    if (d.year == start.year) {
        if (d.month < start.month) return 0;
        if (d.month == start.month && d.day < start.day) return 0;
    }

    if (d.year == end.year) {
        if (d.month > end.month) return 0;
        if (d.month == end.month && d.day > end.day) return 0;
    }

    return 1;
}

int countActiveLoansBetweenDates(LoanList* l) {
    date start, end;
    int count = 0;

    cout << "\nEnter start date (day month year): ";
    cin >> start.day >> start.month >> start.year;

    cout << "Enter end date (day month year): ";
    cin >> end.day >> end.month >> end.year;

    Nodelist* temp = l->head;

    while (temp != NULL) {
        if (isDateBetween(temp->data.StartDate, start, end)) {
            count++;
        }
        temp = temp->next;
    }

    return count;
}


// ==================== FIXED STATISTICS MENU =====================

void Statistics_main() {
    cout << "---------------------Statistics----------------" << endl;
    statistics_1();

    char choice;
    do {
        cout << "\n--- Statistics Menu ---\n";
        cout << "1. Total loans granted\n";
        cout << "2. Successfully paid loans\n";
        cout << "3. Active loans between dates\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case '1': {
            int sizecustomer = sizeofarrayCustomer(customerArray);
            int total = 0;

            for (int i = 0; i < sizecustomer; i++) {
                total += countLoans(customerArray[i].loans.head);
            }

            cout << "Total Loans = " << total << endl;
            break;
        }

        case '2': {
            int sizecustomer = sizeofarrayCustomer(customerArray);
            int paid = 0;

            for (int i = 0; i < sizecustomer; i++) {
                paid += countPaidLoans(customerArray[i].loans.head);
            }

            cout << "Paid Loans = " << paid << endl;
            break;
        }

        case '3': {
            if (sizeofarrayCustomer(customerArray) > 0) {
                cout << "Active Loans Between Dates = "
                    << countActiveLoansBetweenDates(&customerArray[0].loans)
                    << endl;
            }
            else {
                cout << "No customers available.\n";
            }
            break;
        }
        }

    } while (choice != '0');
}
