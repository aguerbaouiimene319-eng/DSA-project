#include "LoanRequestMeth.h"
#include "LoanListMeth.h"
#include "Customer.h"
#include "Employee.h"
#include"Loan.h"
#include "TransactionStackMeth.h"
#include "CompletedLoanListMeth.h"
#include <iostream>
#include <string>
#include "FileHandler.h"
using namespace std;

constexpr int Max_customers = 10000;
constexpr int Max_employees = 2000;

employee employeeArray[Max_employees]{};
customer customerArray[Max_customers]{};
customer archivedAccounts[Max_customers]{};

CompList* completedloans = createCompList();
queue* loanRequests = createQueue();

int sizeofarrayEmployee(employee employeeArray[]);
int sizeofarrayCustomer(customer customerArray[]);
int findAccountIndex(customer customerArray[], int accnum);
bool compareDates(date d1, date d2);

void addEmployee();
void deleteEmployee();
void modifyEmployee();
void sortEmployeesByLastName(employee employees[]);
void displayEmployeesByAlphabeliticalOrder();
void displayEmployeesByBranch();
void displayRecruitmentInfo();
date getDateFromEmployee();

void addCustomerAccount();
void displayCustomerAccounts();
void changeAccountStatus();
void archiveClosedAccounts();

void displayCustomerLoans();
void changeLoanStatus();
void deleteCompletedLoans();

void processLoanRequests();
bool loanIdExists(int id);
int generateUniqueLoanID();

void finalizeDay();
void displayStatistics();

void employeeInterface() {
    char choice;
    do {
        cout << "\n============ EMPLOYEE MENU ============\n";
        cout << "==========1. Add Employee============\n";
        cout << "==========2. Delete Employee=========\n";
        cout << "==========3. Modify Employee========\n";
        cout << "==========4. Display Employees (Alphabetical)========\n";
        cout << "==========5. Display Employees by Branch==========\n";
        cout << "==========6. Display Recruitment Info===========\n";
        cout << "==========7. Add Customer Account============\n";
        cout << "==========8. Display Accounts==============\n";
        cout << "==========9. Change Account Status==============\n";
        cout << "==========10. Archive Closed Accounts===========\n";
        cout << "==========11. Display Customer Loans========\n";
        cout << "==========12. Change Loan Status============\n";
        cout << "==========13. Delete Completed Loans========\n";
        cout << "==========14. Process Loan Requests=========\n";
        cout << "==========15. Finalize Day=========\n";
        cout << "==========16. View Statistics========\n";
        cout << "==========0. Logout========\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice) {
        case '1': addEmployee(); break;
        case '2': deleteEmployee(); break;
        case '3': modifyEmployee(); break;
        case '4': displayEmployeesByAlphabeliticalOrder(); break;
        case '5': displayEmployeesByBranch(); break;
        case '6': displayRecruitmentInfo(); break;
        case '7': addCustomerAccount(); break;
        case '8': displayCustomerAccounts(); break;
        case '9': changeAccountStatus(); break;
        case '10': archiveClosedAccounts(); break;
        case '11': displayCustomerLoans(); break;
        case '12': changeLoanStatus(); break;
        case '13': deleteCompletedLoans(); break;
        case '14': processLoanRequests(); break;
        case '15': finalizeDay(); break;
        case '16': displayStatistics(); break;
        case '0': cout << "\nLogging out...\n"; break;
        default: cout << "\nInvalid choice!\n";
        }
    } while (choice != '0');
}

// size helpers
int sizeofarrayEmployee(employee employeeArray[]) {
    int size = 0;
    while (size < Max_employees && employeeArray[size].ID != "" && employeeArray[size].name != "") size++;
    return size;
}

int sizeofarrayCustomer(customer customerArray[]) {
    int size = 0;
    while (size < Max_customers && customerArray[size].AccNum != 0 && customerArray[size].name != "") size++;
    return size;
}

// employee ops
void addEmployee() {
    cout << "Add employee\n";
    int size = sizeofarrayEmployee(employeeArray);
    if (size >= Max_employees) { cout << "Employee array full.\n"; return; }

    employee emp;
    cout << "Employee ID: "; cin >> emp.ID;

    for (int i = 0; i < size; i++) {
        if (employeeArray[i].ID == emp.ID) {
            cout << "Employee ID already exists!\n"; return;
        }
    }

    cout << "Name: "; cin.ignore(); getline(cin, emp.name);
    cout << "Last Name: "; getline(cin, emp.LastName);
    cout << "Address: "; getline(cin, emp.address);
    cout << "Salary (TND): "; cin >> emp.salary;
    cout << "Hire Date (DD MM YYYY): ";
    cin >> emp.HireDate.day >> emp.HireDate.month >> emp.HireDate.year;
    cout << "Branch Code (1 for head office): "; cin >> emp.BankBranch;
    employeeArray[size] = emp;
    cout << "Employee " << emp.ID << " added successfully\n";
    saveEmployees(employeeArray, sizeofarrayEmployee(employeeArray));

}

void deleteEmployee() {
    string IDsearch;
    cout << "Enter employee ID to delete: "; cin >> IDsearch;
    int size = sizeofarrayEmployee(employeeArray);
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (employeeArray[i].ID == IDsearch) { index = i; break; }
    }
    if (index == -1) { cout << "Employee not found.\n"; return; }
    for (int i = index; i < size - 1; i++) employeeArray[i] = employeeArray[i + 1];
    cout << "Employee " << IDsearch << " removed successfully\n";
    saveEmployees(employeeArray, sizeofarrayEmployee(employeeArray));
}

void modifyEmployee() {
    cout << "\n=== Modify Employee ===\n";
    int size = sizeofarrayEmployee(employeeArray);
    string empId;
    cout << "Enter Employee ID: "; cin >> empId;
    for (int i = 0; i < size; i++) {
        if (employeeArray[i].ID == empId) {
            employee emp = employeeArray[i];
            cout << "\nCurrent Details:\n";
            cout << "Name: " << emp.name << " " << emp.LastName << "\n";
            cout << "Salary: " << emp.salary << " TND\n";
            cout << "\nEnter new details:\n";
            cout << "Name: "; cin.ignore(); getline(cin, emp.name);
            cout << "Last Name: "; getline(cin, emp.LastName);
            cout << "Address: "; getline(cin, emp.address);
            cout << "ID: "; cin >> emp.ID;
            for (int j = 0; j < size; j++) {
                if (j != i && employeeArray[j].ID == emp.ID) {
                    cout << "This ID already exists! Modification canceled.\n"; return;
                }
            }
            cout << "Salary: "; cin >> emp.salary;
            cout << "Branch Code: "; cin >> emp.BankBranch;
            cout << "New hire date (DD MM YYYY): ";
            cin >> emp.HireDate.day >> emp.HireDate.month >> emp.HireDate.year;

            employeeArray[i] = emp;
            cout << "\nEmployee updated successfully!\n";
            return;
        }
    }
    cout << "\nEmployee not found!\n";
    saveEmployees(employeeArray, sizeofarrayEmployee(employeeArray));
}

void sortEmployeesByLastName(employee employees[]) {
    int count = sizeofarrayEmployee(employees);
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (employees[j].LastName > employees[j + 1].LastName) {
                employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
}

void displayEmployeesByAlphabeliticalOrder() {
    cout << "\n=== Employees (Alphabetical) ===\n";
    int size = sizeofarrayEmployee(employeeArray);
    if (size == 0) { cout << "No employees found.\n"; return; }
    employee* temp = new employee[size];
    for (int i = 0; i < size; i++) temp[i] = employeeArray[i];
    sortEmployeesByLastName(temp);
    for (int i = 0; i < size; i++) {
        cout << "\nEmployee " << (i + 1) << ":\n";
        cout << "ID: " << temp[i].ID << "\n";
        cout << "Name: " << temp[i].name << " " << temp[i].LastName << "\n";
        cout << "Salary: " << temp[i].salary << " TND\n";
        cout << "Branch: " << temp[i].BankBranch << "\n";
        cout << "Hire Date: " << temp[i].HireDate.stringDate() << "\n";
    }
    delete[] temp;
}

void displayEmployeesByBranch() {
    cout << "\n=== Employees Grouped by Branch ===\n";
    int size = sizeofarrayEmployee(employeeArray);
    if (size == 0) { cout << "No employees found.\n"; return; }
    string branches[Max_employees];
    int branchCount = 0;
    for (int i = 0; i < size; i++) {
        bool found = false;
        for (int j = 0; j < branchCount; j++) {
            if (branches[j] == employeeArray[i].BankBranch) { found = true; break; }
        }
        if (!found) branches[branchCount++] = employeeArray[i].BankBranch;
    }
    for (int i = 0; i < branchCount; i++) {
        cout << "\n--- Branch " << branches[i] << " ---\n";
        for (int j = 0; j < size; j++) {
            if (employeeArray[j].BankBranch == branches[i]) {
                cout << " " << employeeArray[j].name << " " << employeeArray[j].LastName
                    << " (ID: " << employeeArray[j].ID << ")\n";
            }
        }
    }
}

bool compareDates(date d1, date d2) {
    if (d1.year != d2.year) return d1.year < d2.year;
    if (d1.month != d2.month) return d1.month < d2.month;
    return d1.day < d2.day;
}

void displayRecruitmentInfo() {
    cout << "\n=== Recruitment Information ===\n";
    int size = sizeofarrayEmployee(employeeArray);
    if (size == 0) { cout << "No employees found.\n"; return; }
    int earliestIdx = 0, latestIdx = 0;
    for (int i = 1; i < size; i++) {
        if (compareDates(employeeArray[i].HireDate, employeeArray[earliestIdx].HireDate)) earliestIdx = i;
        if (compareDates(employeeArray[latestIdx].HireDate, employeeArray[i].HireDate)) latestIdx = i;
    }
    cout << "\nEarliest Recruited Employee:\n";
    cout << "Name: " << employeeArray[earliestIdx].name << " " << employeeArray[earliestIdx].LastName << "\n";
    cout << "Hire Date: " << employeeArray[earliestIdx].HireDate.stringDate() << "\n";

    cout << "\nMost Recently Recruited Employee:\n";
    cout << "Name: " << employeeArray[latestIdx].name << " " << employeeArray[latestIdx].LastName << "\n";
    cout << "Hire Date: " << employeeArray[latestIdx].HireDate.stringDate() << "\n";
}

// customers
date getDateFromEmployee() {
    date d{};
    cout << "Enter day: "; cin >> d.day;
    cout << "Enter month: "; cin >> d.month;
    cout << "Enter year: "; cin >> d.year;
    return d;
}

void addCustomerAccount() {
    cout << "\n=== Add Customer Account ===\n";
    int size = sizeofarrayCustomer(customerArray);
    if (size >= Max_customers) { cout << "Account limit reached!\n"; return; }

    customer acc{};
    cout << "Account Number: "; cin >> acc.AccNum;
    for (int i = 0; i < size; i++) {
        if (customerArray[i].AccNum == acc.AccNum) { cout << "Account number already exists!\n"; return; }
    }
    cout << "Account Type: "; cin >> acc.AccType;
    cout << "IBAN (int for this project): "; cin >> acc.IBAN;
    cout << "Branch Code: "; cin >> acc.Branch;
    cout << "Account Holder Name: "; cin.ignore(); getline(cin, acc.name);
    acc.OpDate = getDateFromEmployee();
    acc.status = "active";
    cout << "Initial Balance (TND): "; cin >> acc.balance;
    cout << "Set Password: "; cin >> acc.passwrd;

    // init loan list and stack
    LoanList* newList = createList();
    acc.loans = *newList;
    delete newList;

    stack* newStack = createStack();
    acc.transList = *newStack;
    delete newStack;

    customerArray[size] = acc;
    cout << "\nAccount created successfully!\n";
    cout << "Account Number: " << acc.AccNum << "\n";
    saveCustomers(customerArray, sizeofarrayCustomer(customerArray));
}

void displayCustomerAccounts() {
    cout << "\n=== Customer Accounts ===\n";
    int size = sizeofarrayCustomer(customerArray);
    if (size == 0) { cout << "No accounts found.\n"; return; }
    for (int i = 0; i < size; i++) {
        cout << "\n--- Account " << (i + 1) << " ---\n";
        cout << "Number: " << customerArray[i].AccNum << "\n";
        cout << "Holder: " << customerArray[i].name << "\n";
        cout << "Type: " << customerArray[i].AccType << "\n";
        cout << "Status: " << customerArray[i].status << "\n";
        cout << "Balance: " << customerArray[i].balance << " TND\n";
        cout << "Branch: " << customerArray[i].Branch << "\n";
    }
}

int findAccountIndex(customer customerArray[], int accnum) {
    int size = sizeofarrayCustomer(customerArray);
    for (int i = 0; i < size; i++) {
        if (customerArray[i].AccNum == accnum) return i;
    }
    return -1;
}

void changeAccountStatus() {
    cout << "\n=== Change Account Status ===\n";
    int accountNum;
    cout << "Enter Account Number: "; cin >> accountNum;
    int idx = findAccountIndex(customerArray, accountNum);
    if (idx == -1) { cout << "\nAccount not found!\n"; return; }
    cout << "\nCurrent Status: " << customerArray[idx].status << "\n";
    cout << "New Status (active/inactive/closed): ";
    cin >> customerArray[idx].status;
    cout << "\nStatus updated successfully!\n";
    saveCustomers(customerArray, sizeofarrayCustomer(customerArray));
}

void archiveClosedAccounts() {
    cout << "\n=== Archive Closed Accounts ===\n";
    int archivedCount = 0;
    int size = sizeofarrayCustomer(customerArray);
    int i = 0;
    while (i < size) {
        if (customerArray[i].status == "closed") {
            if (archivedCount < Max_customers) {
                archivedAccounts[archivedCount++] = customerArray[i];
            }
            for (int j = i; j < size - 1; j++) customerArray[j] = customerArray[j + 1];
            size--;
        }
        else {
            i++;
        }
    }
    saveArchivedAccounts(archivedAccounts, archivedCount);
    cout << "Closed accounts archived.\n";
}

// loans
void displayCustomerLoans() {
    cout << "\n=== Display Customer Loans ===\n";
    int accountNum;
    cout << "Enter Account Number: "; cin >> accountNum;
    int idx = findAccountIndex(customerArray, accountNum);
    if (idx == -1) { cout << "\nAccount not found!\n"; return; }
    cout << "\nLoans for Account " << accountNum << ":\n";
    displayLoan(customerArray[idx].loans);
}

void changeLoanStatus() {
    cout << "\n=== Change Loan Status ===\n";
    int accountNum; int loanId;
    cout << "Enter Account Number: "; cin >> accountNum;
    int idx = findAccountIndex(customerArray, accountNum);
    if (idx == -1) { cout << "\nAccount not found!\n"; return; }
    cout << "Enter Loan ID: "; cin >> loanId;
    loan* l = findloan(&customerArray[idx].loans, loanId);
    if (!l) { cout << "\nLoan not found!\n"; return; }
    cout << "\nCurrent Status: " << l->LoanStatus << "\n";
    cout << "New Status (active/completed/overdue): ";
    cin >> l->LoanStatus;
    cout << "\nLoan status updated!\n";
    saveLoans(customerArray[idx].loans, customerArray[idx].AccNum);
}

void deleteCompletedLoans() {
    cout << "\n=== Delete Completed Loans ===\n";
    int totalDeleted = 0;
    int size = sizeofarrayCustomer(customerArray);
    for (int i = 0; i < size; i++) {
        LoanList* list = &customerArray[i].loans;
        int pos = 1;
        Nodelist* current = list->head;
        while (current) {
            Nodelist* next = current->next;
            if (current->data.LoanStatus == "completed") {
                addCompLoan(completedloans, current->data);
                deleteLoan(list, pos);
                totalDeleted++;
            }
            else {
                pos++;
            }
            current = next;
        }
    }
    saveCompletedLoans(*completedloans);
    cout << "\nDeleted " << totalDeleted << " completed loans.\n";
    cout << "They have been moved to the completed loans archive.\n";
}

// loan requests FIFO
void processLoanRequests() {
    cout << "\n=== Process Loan Requests ===\n";
    if (isEmpty(*loanRequests)) { cout << "No pending loan requests.\n"; return; }

    LoanRequest nl = dequeue(loanRequests);
    int accountNum = nl.requestAccNumber;

    cout << "\nProcessing Loan Request:\n";
    cout << "Account: " << accountNum << "\n";
    cout << "Type: " << nl.loanType << "\n";
    cout << "Amount: " << nl.PrincipleAmount << " TND\n";
    cout << "\nAccept this loan? (y/n): ";
    char choice; cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int idx = findAccountIndex(customerArray, accountNum);
        if (idx != -1) {
            loan newLoanData{};
            // Build a loan from the request:
            newLoanData.type = nl.loanType;
            newLoanData.amount = (float)nl.PrincipleAmount;
            newLoanData.AmPaid = 0;
            newLoanData.ID = generateUniqueLoanID();
            newLoanData.EndDate = nl.EndDate;
            cout << "Enter the interest rate of this loan (e.g., 0.06): ";
            cin >> newLoanData.InterestRate;
            newLoanData.StartDate = nl.StartDate;
            newLoanData.ReBalance = newLoanData.amount + (newLoanData.amount * newLoanData.InterestRate);
            newLoanData.LoanStatus = "active";

            addLoan(&customerArray[idx].loans, newLoanData, 1);
            cout << "\nLoan approved and added to customer account!\n";
        }
        else {
            cout << "\nError: Account not found!\n";
        }
    }
    else {
        cout << "\nLoan request declined and deleted.\n";
    }
    saveLoanRequests(*loanRequests);
}

bool loanIdExists(int id) {
    int size = sizeofarrayCustomer(customerArray);
    for (int i = 0; i < size; i++) {
        Nodelist* curr = customerArray[i].loans.head;
        while (curr) {
            if (curr->data.ID == id) return true;
            curr = curr->next;
        }
    }
    return false;
}

int generateUniqueLoanID() {
    int id;
    do { id = rand(); } while (loanIdExists(id));
    return id;
}

// finalize day
void finalizeDay() {
    cout << "\n=== Finalize Day ===\n";
    cout << "This will:\n";
    cout << "1. Copy all daily transactions to permanent records (not implemented here)\n";
    cout << "2. Prevent customers from undoing transactions\n";
    cout << "3. Clear daily transaction stacks\n";
    cout << "\nContinue? (y/n): ";
    char choice; cin >> choice;
    if (choice != 'y' && choice != 'Y') { cout << "\nOperation cancelled.\n"; return; }

    int size = sizeofarrayCustomer(customerArray);
    for (int i = 0; i < size; i++) {
        // In a full system, we'd copy to a permanent log per account before clearing
        destroyStack(&customerArray[i].transList);
        stack* newStack = createStack();
        customerArray[i].transList = *newStack;
        delete newStack;
    }
    cout << "\nDay finalized successfully!\n";
    cout << "All daily transactions have been recorded.\n";
}

// statistics
void displayStatistics() {
    cout << "\n=========== STATISTICS ===========\n";

    int totalLoans = 0;
    int carLoans = 0, homeLoans = 0, studentLoans = 0, businessLoans = 0;
    int activeLoans = 0, completedLoans = 0, overdueLoans = 0;

    int size = sizeofarrayCustomer(customerArray);
    int sizeEmp = sizeofarrayEmployee(employeeArray);

    // 1–3: Total loans, by type, by status
    for (int i = 0; i < size; i++) {
        Nodelist* curr = customerArray[i].loans.head;
        while (curr) {
            totalLoans++;

            if (curr->data.type == "car") carLoans++;
            else if (curr->data.type == "home") homeLoans++;
            else if (curr->data.type == "student") studentLoans++;
            else if (curr->data.type == "business") businessLoans++;

            if (curr->data.LoanStatus == "active") activeLoans++;
            else if (curr->data.LoanStatus == "completed") completedLoans++;
            else if (curr->data.LoanStatus == "overdue") overdueLoans++;

            curr = curr->next;
        }
    }

    cout << "\n1. Total number of loans: " << totalLoans << endl;
    cout << "\n2. Number of loans by type:\n";
    cout << "   Car: " << carLoans << "\n   Home: " << homeLoans << "\n   Student: " << studentLoans << "\n   Business: " << businessLoans << endl;

    cout << "\n3. Number of loans by status:\n";
    cout << "   Active: " << activeLoans << "\n   Completed: " << completedLoans << "\n   Overdue: " << overdueLoans << endl;

    // 4: Active loans in date range
    date start, end;
    cout << "\n4. Active loans within a date range:\n";
    cout << "   Enter start date (DD MM YYYY): ";
    cin >> start.day >> start.month >> start.year;
    cout << "   Enter end date (DD MM YYYY): ";
    cin >> end.day >> end.month >> end.year;

    int activeInRange = 0;
    for (int i = 0; i < size; i++) {
        Nodelist* curr = customerArray[i].loans.head;
        while (curr) {
            if (curr->data.LoanStatus == "active") {
                date d = curr->data.StartDate;
                if (compareDates(start, d) && compareDates(d, end)) {
                    activeInRange++;
                }
            }
            curr = curr->next;
        }
    }
    cout << "   Active loans in range: " << activeInRange << endl;

    // 5: Customer with highest number of loans
    int maxLoans = 0;
    string maxLoanCustomer = "";
    for (int i = 0; i < size; i++) {
        int count = ListSize(customerArray[i].loans);
        if (count > maxLoans) {
            maxLoans = count;
            maxLoanCustomer = customerArray[i].name;
        }
    }
    cout << "\n5. Customer with highest number of loans: " << maxLoanCustomer << " (" << maxLoans << " loans)" << endl;

    // 6 & 7: Highest and lowest balance
    if (size > 0) {
        int maxIdx = 0, minIdx = 0;
        for (int i = 1; i < size; i++) {
            if (customerArray[i].balance > customerArray[maxIdx].balance) maxIdx = i;
            if (customerArray[i].balance < customerArray[minIdx].balance) minIdx = i;
        }
        cout << "\n6. Customer with highest balance: " << customerArray[maxIdx].name << " (" << customerArray[maxIdx].balance << " TND)" << endl;
        cout << "7. Customer with lowest balance: " << customerArray[minIdx].name << " (" << customerArray[minIdx].balance << " TND)" << endl;
    }

    // 8: Total number of employees
    cout << "\n8. Total number of employees: " << sizeEmp << endl;

    // 9: Number of employees per branch
    string branches[Max_employees];
    int branchCounts[Max_employees] = { 0 };
    int branchTotal = 0;

    for (int i = 0; i < sizeEmp; i++) {
        string branch = employeeArray[i].BankBranch;
        bool found = false;
        for (int j = 0; j < branchTotal; j++) {
            if (branches[j] == branch) {
                branchCounts[j]++;
                found = true;
                break;
            }
        }
        if (!found) {
            branches[branchTotal] = branch;
            branchCounts[branchTotal] = 1;
            branchTotal++;
        }
    }

    cout << "\n9. Number of employees per branch:\n";
    for (int i = 0; i < branchTotal; i++) {
        cout << "   Branch " << branches[i] << ": " << branchCounts[i] << " employees" << endl;
    }

    cout << "\n==================================\n";
}