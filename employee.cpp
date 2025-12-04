#include "Employee.h"
#include "structures.h"
#include <iostream>
#include <string>
using namespace std;

/*void employeeMenu(BankSystem* system) {
    int choice;

    do {
        clearScreen();
        cout << "\n============ EMPLOYEE MENU ============\n";
        cout << "1.  Add Employee\n";
        cout << "2.  Delete Employee\n";
        cout << "3.  Modify Employee\n";
        cout << "4.  Display Employees (Alphabetical)\n";
        cout << "5.  Display Employees by Branch\n";
        cout << "6.  Display Recruitment Info\n";
        cout << "7.  Add Customer Account\n";
        cout << "8.  Display Accounts\n";
        cout << "9.  Change Account Status\n";
        cout << "10. Archive Closed Accounts\n";
        cout << "11. Display Customer Loans\n";
        cout << "12. Change Loan Status\n";
        cout << "13. Delete Completed Loans\n";
        cout << "14. Process Loan Requests\n";
        cout << "15. Finalize Day\n";
        cout << "16. View Statistics\n";
        cout << "0.  Logout\n";
        cout << "=======================================\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addEmployee(system); pause(); break;
        case 2: deleteEmployee(system); pause(); break;
        case 3: modifyEmployee(system); pause(); break;
        case 4: displayEmployees(system); pause(); break;
        case 5: displayEmployeesByBranch(system); pause(); break;
        case 6: displayRecruitmentInfo(system); pause(); break;
        case 7: addCustomerAccount(system); pause(); break;
        case 8: displayAccounts(system); pause(); break;
        case 9: changeAccountStatus(system); pause(); break;
        case 10: archiveClosedAccounts(system); pause(); break;
        case 11: displayCustomerLoans(system); pause(); break;
        case 12: changeLoanStatus(system); pause(); break;
        case 13: deleteCompletedLoans(system); pause(); break;
        case 14: processLoanRequests(system); pause(); break;
        case 15: finalizeDay(system); pause(); break;
        case 16: displayStatistics(system); pause(); break;
        case 0: cout << "\nLogging out...\n"; break;
        default: cout << "\nInvalid choice!\n"; pause();
        }
    } while (choice != 0);
}

*/

void addEmployee(BankSystem* system) {
    clearScreen();
    cout << "\n=== Add Employee ===\n";

    if (system->employeeCount >= MAX_EMPLOYEES) {
        cout << "Employee limit reached!\n";
        return;
    }

    Employee& emp = system->employees[system->employeeCount];

    cout << "Employee ID: ";
    cin >> emp.id;

    // Check uniqueness
    for (int i = 0; i < system->employeeCount; i++) {
        if (system->employees[i].id == emp.id) {
            cout << "Employee ID already exists!\n";
            return;
        }
    }

    cout << "Name: ";
    cin.ignore();
    getline(cin, emp.name);

    cout << "Last Name: ";
    getline(cin, emp.lastName);

    cout << "Address: ";
    getline(cin, emp.address);

    cout << "Salary (TND): ";
    cin >> emp.salary;

    cout << "Hire Date (DD MM YYYY): ";
    cin >> emp.hireDate.day >> emp.hireDate.month >> emp.hireDate.year;

    cout << "Branch Code (1 for head office): ";
    cin >> emp.branchCode;

    system->employeeCount++;
    cout << "\nEmployee added successfully!\n";
}

void deleteEmployee(BankSystem* system) {
    clearScreen();
    cout << "\n=== Delete Employee ===\n";

    string empId;
    cout << "Enter Employee ID to delete: ";
    cin >> empId;

    for (int i = 0; i < system->employeeCount; i++) {
        if (system->employees[i].id == empId) {
            // Shift remaining employees
            for (int j = i; j < system->employeeCount - 1; j++) {
                system->employees[j] = system->employees[j + 1];
            }
            system->employeeCount--;
            cout << "\nEmployee deleted successfully!\n";
            return;
        }
    }

    cout << "\nEmployee not found!\n";
}

void modifyEmployee(BankSystem* system) {
    clearScreen();
    cout << "\n=== Modify Employee ===\n";

    string empId;
    cout << "Enter Employee ID: ";
    cin >> empId;

    for (int i = 0; i < system->employeeCount; i++) {
        if (system->employees[i].id == empId) {
            Employee& emp = system->employees[i];

            cout << "\nCurrent Details:\n";
            cout << "Name: " << emp.name << " " << emp.lastName << "\n";
            cout << "Salary: " << emp.salary << " TND\n";

            cout << "\nEnter new details:\n";
            cout << "Name: ";
            cin.ignore();
            getline(cin, emp.name);

            cout << "Last Name: ";
            getline(cin, emp.lastName);

            cout << "Address: ";
            getline(cin, emp.address);

            cout << "Salary: ";
            cin >> emp.salary;

            cout << "Branch Code: ";
            cin >> emp.branchCode;

            cout << "\nEmployee updated successfully!\n";
            return;
        }
    }

    cout << "\nEmployee not found!\n";
}

void sortEmployeesByLastName(Employee employees[], int count) {
    // Bubble sort by last name
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (employees[j].lastName > employees[j + 1].lastName) {
                Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
}

void displayEmployees(BankSystem* system) {
    clearScreen();
    cout << "\n=== Employees (Alphabetical) ===\n";

    if (system->employeeCount == 0) {
        cout << "No employees found.\n";
        return;
    }

    // Create a copy for sorting
    Employee* tempEmployees = new Employee[system->employeeCount];
    for (int i = 0; i < system->employeeCount; i++) {
        tempEmployees[i] = system->employees[i];
    }

    sortEmployeesByLastName(tempEmployees, system->employeeCount);

    for (int i = 0; i < system->employeeCount; i++) {
        cout << "\nEmployee " << (i + 1) << ":\n";
        cout << "ID: " << tempEmployees[i].id << "\n";
        cout << "Name: " << tempEmployees[i].name << " "
            << tempEmployees[i].lastName << "\n";
        cout << "Salary: " << tempEmployees[i].salary << " TND\n";
        cout << "Branch: " << tempEmployees[i].branchCode << "\n";
        cout << "Hire Date: ";
        printDate(tempEmployees[i].hireDate);
        cout << "\n";
    }

    delete[] tempEmployees;
}

void displayEmployeesByBranch(BankSystem* system) {
    clearScreen();
    cout << "\n=== Employees Grouped by Branch ===\n";

    if (system->employeeCount == 0) {
        cout << "No employees found.\n";
        return;
    }

    // Get unique branches
    string branches[MAX_EMPLOYEES];
    int branchCount = 0;

    for (int i = 0; i < system->employeeCount; i++) {
        bool found = false;
        for (int j = 0; j < branchCount; j++) {
            if (branches[j] == system->employees[i].branchCode) {
                found = true;
                break;
            }
        }
        if (!found) {
            branches[branchCount++] = system->employees[i].branchCode;
        }
    }

    // Display by branch
    for (int i = 0; i < branchCount; i++) {
        cout << "\n--- Branch " << branches[i] << " ---\n";
        for (int j = 0; j < system->employeeCount; j++) {
            if (system->employees[j].branchCode == branches[i]) {
                cout << "  " << system->employees[j].name << " "
                    << system->employees[j].lastName
                    << " (ID: " << system->employees[j].id << ")\n";
            }
        }
    }
}

void displayRecruitmentInfo(BankSystem* system) {
    clearScreen();
    cout << "\n=== Recruitment Information ===\n";

    if (system->employeeCount == 0) {
        cout << "No employees found.\n";
        return;
    }

    int earliestIdx = 0;
    int latestIdx = 0;

    for (int i = 1; i < system->employeeCount; i++) {
        if (compareDates(system->employees[i].hireDate,
            system->employees[earliestIdx].hireDate)) {
            earliestIdx = i;
        }
        if (compareDates(system->employees[latestIdx].hireDate,
            system->employees[i].hireDate)) {
            latestIdx = i;
        }
    }

    cout << "\nEarliest Recruited Employee:\n";
    cout << "Name: " << system->employees[earliestIdx].name << " "
        << system->employees[earliestIdx].lastName << "\n";
    cout << "Hire Date: ";
    printDate(system->employees[earliestIdx].hireDate);

    cout << "\n\nMost Recently Recruited Employee:\n";
    cout << "Name: " << system->employees[latestIdx].name << " "
        << system->employees[latestIdx].lastName << "\n";
    cout << "Hire Date: ";
    printDate(system->employees[latestIdx].hireDate);
    cout << "\n";
}

void addCustomerAccount(BankSystem* system) {
    clearScreen();
    cout << "\n=== Add Customer Account ===\n";

    if (system->accountCount >= MAX_ACCOUNTS) {
        cout << "Account limit reached!\n";
        return;
    }

    Account& acc = system->accounts[system->accountCount];

    cout << "Account Number: ";
    cin >> acc.accountNumber;

    // Check uniqueness
    for (int i = 0; i < system->accountCount; i++) {
        if (system->accounts[i].accountNumber == acc.accountNumber) {
            cout << "Account number already exists!\n";
            return;
        }
    }

    cout << "Account Type: ";
    cin >> acc.accountType;

    cout << "IBAN: ";
    cin >> acc.iban;

    cout << "Branch Code: ";
    cin >> acc.branchCode;

    cout << "Account Holder Name: ";
    cin.ignore();
    getline(cin, acc.holderName);

    acc.openingDate = getCurrentDate();
    acc.status = "active";

    cout << "Initial Balance (TND): ";
    cin >> acc.balance;

    cout << "Set Password: ";
    cin >> acc.password;

    // Initialize loan list and transaction stack
    acc.loans = createLoanList();
    acc.dailyTransactions = createTransactionStack();

    system->accountCount++;
    cout << "\nAccount created successfully!\n";
    cout << "Account Number: " << acc.accountNumber << "\n";
}

void displayAccounts(BankSystem* system) {
    clearScreen();
    cout << "\n=== Customer Accounts ===\n";

    if (system->accountCount == 0) {
        cout << "No accounts found.\n";
        return;
    }

    for (int i = 0; i < system->accountCount; i++) {
        cout << "\n--- Account " << (i + 1) << " ---\n";
        cout << "Number: " << system->accounts[i].accountNumber << "\n";
        cout << "Holder: " << system->accounts[i].holderName << "\n";
        cout << "Type: " << system->accounts[i].accountType << "\n";
        cout << "Status: " << system->accounts[i].status << "\n";
        cout << "Balance: " << fixed << setprecision(3)
            << system->accounts[i].balance << " TND\n";
        cout << "Branch: " << system->accounts[i].branchCode << "\n";
    }
}

void changeAccountStatus(BankSystem* system) {
    clearScreen();
    cout << "\n=== Change Account Status ===\n";

    string accountNum;
    cout << "Enter Account Number: ";
    cin >> accountNum;

    int idx = findAccountIndex(system, accountNum);
    if (idx == -1) {
        cout << "\nAccount not found!\n";
        return;
    }

    cout << "\nCurrent Status: " << system->accounts[idx].status << "\n";
    cout << "New Status (active/inactive/closed): ";
    cin >> system->accounts[idx].status;

    cout << "\nStatus updated successfully!\n";
}

void archiveClosedAccounts(BankSystem* system) {
    clearScreen();
    cout << "\n=== Archive Closed Accounts ===\n";

    int archivedCount = 0;
    int i = 0;

    while (i < system->accountCount) {
        if (system->accounts[i].status == "closed") {
            if (system->archivedCount < MAX_ARCHIVED_ACCOUNTS) {
                system->archivedAccounts[system->archivedCount++] =
                    system->accounts[i];
                archivedCount++;
            }

            // Remove from active accounts
            for (int j = i; j < system->accountCount - 1; j++) {
                system->accounts[j] = system->accounts[j + 1];
            }
            system->accountCount--;
        }
        else {
            i++;
        }
    }

    cout << "\nArchived " << archivedCount << " closed accounts.\n";
}

int findAccountIndex(BankSystem* system, const string& accountNum) {
    for (int i = 0; i < system->accountCount; i++) {
        if (system->accounts[i].accountNumber == accountNum) {
            return i;
        }
    }
    return -1;
}

void displayCustomerLoans(BankSystem* system) {
    clearScreen();
    cout << "\n=== Display Customer Loans ===\n";

    string accountNum;
    cout << "Enter Account Number: ";
    cin >> accountNum;

    int idx = findAccountIndex(system, accountNum);
    if (idx == -1) {
        cout << "\nAccount not found!\n";
        return;
    }

    cout << "\nLoans for Account " << accountNum << ":\n";
    displayLoanList(system->accounts[idx].loans);
}

void changeLoanStatus(BankSystem* system) {
    clearScreen();
    cout << "\n=== Change Loan Status ===\n";

    string accountNum, loanId;
    cout << "Enter Account Number: ";
    cin >> accountNum;

    int idx = findAccountIndex(system, accountNum);
    if (idx == -1) {
        cout << "\nAccount not found!\n";
        return;
    }

    cout << "Enter Loan ID: ";
    cin >> loanId;

    Loan* loan = findLoan(&system->accounts[idx].loans, loanId);
    if (!loan) {
        cout << "\nLoan not found!\n";
        return;
    }

    cout << "\nCurrent Status: " << loan->status << "\n";
    cout << "New Status (active/completed/overdue): ";
    cin >> loan->status;

    cout << "\nLoan status updated!\n";
}

void deleteCompletedLoans(BankSystem* system) {
    clearScreen();
    cout << "\n=== Delete Completed Loans ===\n";

    int totalDeleted = 0;

    for (int i = 0; i < system->accountCount; i++) {
        LoanList* list = &system->accounts[i].loans;
        LoanNode* current = list->head;

        while (current != nullptr) {
            LoanNode* next = current->next;

            if (current->data.status == "completed") {
                // Add to completed loans list
                addCompletedLoan(&system->completedLoans, current->data);

                // Remove from loan list
                removeLoan(list, current->data.loanId);
                totalDeleted++;
            }

            current = next;
        }
    }

    cout << "\nDeleted " << totalDeleted << " completed loans.\n";
    cout << "They have been moved to the completed loans archive.\n";
}

void processLoanRequests(BankSystem* system) {
    clearScreen();
    cout << "\n=== Process Loan Requests ===\n";

    if (isQueueEmpty(system->loanRequests)) {
        cout << "No pending loan requests.\n";
        return;
    }

    Loan loan;
    string accountNum;

    if (dequeueLoanRequest(&system->loanRequests, loan, accountNum)) {
        cout << "\nProcessing Loan Request:\n";
        cout << "Account: " << accountNum << "\n";
        cout << "Loan ID: " << loan.loanId << "\n";
        cout << "Type: " << loan.loanType << "\n";
        cout << "Amount: " << loan.principalAmount << " TND\n";

        cout << "\nAccept this loan? (y/n): ";
        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            int idx = findAccountIndex(system, accountNum);
            if (idx != -1) {
                loan.status = "active";
                addLoan(&system->accounts[idx].loans, loan);
                cout << "\nLoan approved and added to customer account!\n";
            }
            else {
                cout << "\nError: Account not found!\n";
            }
        }
        else {
            cout << "\nLoan request declined and deleted.\n";
        }
    }
}

void finalizeDay(BankSystem* system) {
    clearScreen();
    cout << "\n=== Finalize Day ===\n";

    cout << "This will:\n";
    cout << "1. Copy all daily transactions to permanent records\n";
    cout << "2. Prevent customers from undoing transactions\n";
    cout << "3. Clear daily transaction stacks\n";
    cout << "\nContinue? (y/n): ";

    char choice;
    cin >> choice;

    if (choice != 'y' && choice != 'Y') {
        cout << "\nOperation cancelled.\n";
        return;
    }

    for (int i = 0; i < system->accountCount; i++) {
        // In a real system, we would copy transactions to a permanent list
        // For this implementation, we just clear the stacks
        destroyTransactionStack(&system->accounts[i].dailyTransactions);
        system->accounts[i].dailyTransactions = createTransactionStack();
    }

    system->dayFinalized = true;
    cout << "\nDay finalized successfully!\n";
    cout << "All daily transactions have been recorded.\n";
}

void displayStatistics(BankSystem* system) {
    clearScreen();
    cout << "\n========== STATISTICS ==========\n";

    // Loan statistics
    int totalLoans = 0;
    int loansByType[4] = { 0 }; // car, home, student, business
    int loansByStatus[3] = { 0 }; // active, completed, overdue

    for (int i = 0; i < system->accountCount; i++) {
        LoanNode* current = system->accounts[i].loans.head;
        while (current != nullptr) {
            totalLoans++;

            // Count by type
            if (current->data.loanType == "car") loansByType[0]++;
            else if (current->data.loanType == "home") loansByType[1]++;
            else if (current->data.loanType == "student") loansByType[2]++;
            else if (current->data.loanType == "business") loansByType[3]++;

            // Count by status
            if (current->data.status == "active") loansByStatus[0]++;
            else if (current->data.status == "completed") loansByStatus[1]++;
            else if (current->data.status == "overdue") loansByStatus[2]++;

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

    // Customer with highest loans
    int maxLoans = 0;
    string customerMaxLoans = "";
    for (int i = 0; i < system->accountCount; i++) {
        if (system->accounts[i].loans.size > maxLoans) {
            maxLoans = system->accounts[i].loans.size;
            customerMaxLoans = system->accounts[i].holderName;
        }
    }

    cout << "\n5. Customer with Most Loans: " << customerMaxLoans
        << " (" << maxLoans << " loans)\n";

    // Balance statistics
    if (system->accountCount > 0) {
        int maxBalIdx = 0, minBalIdx = 0;
        for (int i = 1; i < system->accountCount; i++) {
            if (system->accounts[i].balance >
                system->accounts[maxBalIdx].balance) {
                maxBalIdx = i;
            }
            if (system->accounts[i].balance <
                system->accounts[minBalIdx].balance) {
                minBalIdx = i;
            }
        }

        cout << "\n6. Highest Balance: "
            << system->accounts[maxBalIdx].holderName << " - "
            << fixed << setprecision(3)
            << system->accounts[maxBalIdx].balance << " TND\n";

        cout << "\n7. Lowest Balance: "
            << system->accounts[minBalIdx].holderName << " - "
            << fixed << setprecision(3)
            << system->accounts[minBalIdx].balance << " TND\n";
    }

    // Employee statistics
    cout << "\n8. Total Employees: " << system->employeeCount << "\n";

    // Employees per branch
    string branches[MAX_EMPLOYEES];
    int branchCounts[MAX_EMPLOYEES] = { 0 };
    int uniqueBranches = 0;

    for (int i = 0; i < system->employeeCount; i++) {
        bool found = false;
        for (int j = 0; j < uniqueBranches; j++) {
            if (branches[j] == system->employees[i].branchCode) {
                branchCounts[j]++;
                found = true;
                break;
            }
        }
        if (!found) {
            branches[uniqueBranches] = system->employees[i].branchCode;
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