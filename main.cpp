#include "structurs.h"
#include "customer.h"
#include "employee.h"
#include <iostream>
#include <fstream>
using namespace std;

// Function prototypes
void initializeSystem(BankSystem* system);
void loadDataFromFiles(BankSystem* system);
void saveDataToFiles(BankSystem* system);
void mainMenu(BankSystem* system);
void customerMenu(BankSystem* system, Account* account);
void employeeMenu(BankSystem* system);
void clearScreen();
void pause();

int main() {
    BankSystem system;
    initializeSystem(&system);
    loadDataFromFiles(&system);

    cout << "\n========================================\n";
    cout << "   BANKING MANAGEMENT SYSTEM\n";
    cout << "========================================\n";

    mainMenu(&system);

    saveDataToFiles(&system);

    // Cleanup
    for (int i = 0; i < system.accountCount; i++) {
        destroyLoanList(&system.accounts[i].loans);
        destroyTransactionStack(&system.accounts[i].dailyTransactions);
    }

    cout << "\nThank you for using the Banking System!\n";
    return 0;
}

void initializeSystem(BankSystem* system) {
    system->accountCount = 0;
    system->archivedCount = 0;
    system->employeeCount = 0;
    system->loanRequests = createLoanRequestQueue();
    system->completedLoans = nullptr;
    system->dayFinalized = false;
}

void loadDataFromFiles(BankSystem* system) {
    // ====================== LOAD EMPLOYEES ======================
    ifstream empFile("employees.txt");
    if (empFile.is_open()) {
        // Check if file is empty
        empFile.seekg(0, ios::end);
        if (empFile.tellg() == 0) {
            cout << "employees.txt is empty — starting with 0 employees.\n";
            system->employeeCount = 0;
            empFile.close();
        }
        else {
            empFile.seekg(0, ios::beg);

            empFile >> system->employeeCount;
            if (!empFile.good() || system->employeeCount < 0) {
                cout << "Error: employees.txt corrupted — resetting employees.\n";
                system->employeeCount = 0;
                empFile.close();
            }
            else {
                empFile.ignore();

                for (int i = 0; i < system->employeeCount; i++) {
                    getline(empFile, system->employees[i].id);
                    getline(empFile, system->employees[i].name);
                    getline(empFile, system->employees[i].lastName);
                    getline(empFile, system->employees[i].address);
                    empFile >> system->employees[i].salary;
                    empFile >> system->employees[i].hireDate.day
                        >> system->employees[i].hireDate.month
                        >> system->employees[i].hireDate.year;
                    empFile.ignore();
                    getline(empFile, system->employees[i].branchCode);
                }
                empFile.close();
                cout << "Loaded " << system->employeeCount << " employees.\n";
            }
        }
    }
    else {
        cout << "employees.txt not found — starting with 0 employees.\n";
        system->employeeCount = 0;
    }

    // ====================== LOAD ACCOUNTS ======================
    ifstream accFile("accounts.txt");
    if (!accFile.is_open()) {
        cout << "accounts.txt missing — starting with an empty database.\n";
        system->accountCount = 0;
        return;
    }

    // Checking if file is empty
    accFile.seekg(0, ios::end);
    if (accFile.tellg() == 0) {
        cout << "accounts.txt is empty — starting with 0 accounts.\n";
        system->accountCount = 0;
        accFile.close();
        return;
    }
    accFile.seekg(0, ios::beg);

    // Reading number of accounts
    accFile >> system->accountCount;
    if (!accFile.good() || system->accountCount < 0) {
        cout << "Error: accounts.txt is corrupted — resetting database.\n";
        system->accountCount = 0;
        accFile.close();
        return;
    }
    accFile.ignore();

    // Loading each account
    for (int i = 0; i < system->accountCount; i++) {
        getline(accFile, system->accounts[i].accountNumber);
        getline(accFile, system->accounts[i].accountType);
        getline(accFile, system->accounts[i].iban);
        getline(accFile, system->accounts[i].branchCode);
        getline(accFile, system->accounts[i].holderName);

        accFile >> system->accounts[i].openingDate.day
            >> system->accounts[i].openingDate.month
            >> system->accounts[i].openingDate.year;
        accFile.ignore();

        getline(accFile, system->accounts[i].status);

        accFile >> system->accounts[i].balance;
        accFile.ignore();

        getline(accFile, system->accounts[i].password);

        // Initialize loan list & transaction stack
        system->accounts[i].loans = createLoanList();
        system->accounts[i].dailyTransactions = createTransactionStack();

        // ====== LOAD LOANS FOR THIS ACCOUNT ======
        int loanCount;
        accFile >> loanCount;
        accFile.ignore();

        if (loanCount < 0) {
            cout << "Warning: corrupted loan count — skipping loans for account "
                << system->accounts[i].accountNumber << "\n";
            loanCount = 0;
        }

        for (int j = 0; j < loanCount; j++) {
            Loan loan;
            getline(accFile, loan.loanId);
            getline(accFile, loan.loanType);

            accFile >> loan.principalAmount >> loan.interestRate
                >> loan.amountPaid >> loan.remainingBalance;

            accFile >> loan.startDate.day >> loan.startDate.month >> loan.startDate.year;
            accFile >> loan.endDate.day >> loan.endDate.month >> loan.endDate.year;

            accFile.ignore();
            getline(accFile, loan.status);

            addLoan(&system->accounts[i].loans, loan);
        }
    }

    accFile.close();
    cout << "Loaded " << system->accountCount << " accounts successfully.\n";

    // ====================== LOAD ARCHIVED ACCOUNTS ======================
    ifstream archFile("archived_accounts.txt");
    if (archFile.is_open()) {
        archFile.seekg(0, ios::end);
        if (archFile.tellg() == 0) {
            cout << "No archived accounts found.\n";
            system->archivedCount = 0;
            archFile.close();
        }
        else {
            archFile.seekg(0, ios::beg);
            archFile >> system->archivedCount;
            if (!archFile.good() || system->archivedCount < 0) {
                system->archivedCount = 0;
            }
            else {
                archFile.ignore();
                for (int i = 0; i < system->archivedCount; i++) {
                    getline(archFile, system->archivedAccounts[i].accountNumber);
                    getline(archFile, system->archivedAccounts[i].accountType);
                    getline(archFile, system->archivedAccounts[i].iban);
                    getline(archFile, system->archivedAccounts[i].branchCode);
                    getline(archFile, system->archivedAccounts[i].holderName);
                    archFile >> system->archivedAccounts[i].openingDate.day
                        >> system->archivedAccounts[i].openingDate.month
                        >> system->archivedAccounts[i].openingDate.year;
                    archFile.ignore();
                    getline(archFile, system->archivedAccounts[i].status);
                    archFile >> system->archivedAccounts[i].balance;
                    archFile.ignore();
                    getline(archFile, system->archivedAccounts[i].password);
                }
                cout << "Loaded " << system->archivedCount << " archived accounts.\n";
            }
            archFile.close();
        }
    }
    else {
        cout << "No archived accounts file found.\n";
        system->archivedCount = 0;
    }
}

void saveDataToFiles(BankSystem* system) {
    // ====================== SAVE EMPLOYEES ======================
    ofstream empFile("employees.txt");
    if (empFile.is_open()) {
        empFile << system->employeeCount << "\n";

        for (int i = 0; i < system->employeeCount; i++) {
            empFile << system->employees[i].id << "\n";
            empFile << system->employees[i].name << "\n";
            empFile << system->employees[i].lastName << "\n";
            empFile << system->employees[i].address << "\n";
            empFile << system->employees[i].salary << "\n";
            empFile << system->employees[i].hireDate.day << " "
                << system->employees[i].hireDate.month << " "
                << system->employees[i].hireDate.year << "\n";
            empFile << system->employees[i].branchCode << "\n";
        }
        empFile.close();
        cout << "Saved " << system->employeeCount << " employees.\n";
    }
    else {
        cout << "Error: Could not save employees.txt\n";
    }

    // ====================== SAVE ACCOUNTS ======================
    ofstream accFile("accounts.txt");
    if (accFile.is_open()) {
        accFile << system->accountCount << "\n";

        for (int i = 0; i < system->accountCount; i++) {
            accFile << system->accounts[i].accountNumber << "\n";
            accFile << system->accounts[i].accountType << "\n";
            accFile << system->accounts[i].iban << "\n";
            accFile << system->accounts[i].branchCode << "\n";
            accFile << system->accounts[i].holderName << "\n";
            accFile << system->accounts[i].openingDate.day << " "
                << system->accounts[i].openingDate.month << " "
                << system->accounts[i].openingDate.year << "\n";
            accFile << system->accounts[i].status << "\n";
            accFile << system->accounts[i].balance << "\n";
            accFile << system->accounts[i].password << "\n";

            // Save loans
            accFile << system->accounts[i].loans.size << "\n";
            LoanNode* current = system->accounts[i].loans.head;
            while (current != nullptr) {
                accFile << current->data.loanId << "\n";
                accFile << current->data.loanType << "\n";
                accFile << current->data.principalAmount << " "
                    << current->data.interestRate << " "
                    << current->data.amountPaid << " "
                    << current->data.remainingBalance << "\n";
                accFile << current->data.startDate.day << " "
                    << current->data.startDate.month << " "
                    << current->data.startDate.year << "\n";
                accFile << current->data.endDate.day << " "
                    << current->data.endDate.month << " "
                    << current->data.endDate.year << "\n";
                accFile << current->data.status << "\n";

                current = current->next;
            }
        }
        accFile.close();
        cout << "Saved " << system->accountCount << " accounts.\n";
    }
    else {
        cout << "Error: Could not save accounts.txt\n";
    }

    // ====================== SAVE ARCHIVED ACCOUNTS ======================
    ofstream archFile("archived_accounts.txt");
    if (archFile.is_open()) {
        archFile << system->archivedCount << "\n";
        for (int i = 0; i < system->archivedCount; i++) {
            archFile << system->archivedAccounts[i].accountNumber << "\n";
            archFile << system->archivedAccounts[i].accountType << "\n";
            archFile << system->archivedAccounts[i].iban << "\n";
            archFile << system->archivedAccounts[i].branchCode << "\n";
            archFile << system->archivedAccounts[i].holderName << "\n";
            archFile << system->archivedAccounts[i].openingDate.day << " "
                << system->archivedAccounts[i].openingDate.month << " "
                << system->archivedAccounts[i].openingDate.year << "\n";
            archFile << system->archivedAccounts[i].status << "\n";
            archFile << system->archivedAccounts[i].balance << "\n";
            archFile << system->archivedAccounts[i].password << "\n";
        }
        archFile.close();
        cout << "Saved " << system->archivedCount << " archived accounts.\n";
    }
}

void mainMenu(BankSystem* system) {
    int choice;

    do {
        clearScreen();
        cout << "\n========================================\n";
        cout << "        BANKING SYSTEM - MAIN MENU\n";
        cout << "========================================\n";
        cout << "1. Customer Login\n";
        cout << "2. Employee Login\n";
        cout << "0. Exit\n";
        cout << "========================================\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Account* account = customerLogin(system);
            if (account != nullptr) {
                customerMenu(system, account);
            }
            else {
                cout << "\nLogin failed!\n";
                pause();
            }
            break;
        }
        case 2: {
            string empId;
            cout << "\nEmployee ID: ";
            cin >> empId;

            bool found = false;
            for (int i = 0; i < system->employeeCount; i++) {
                if (system->employees[i].id == empId) {
                    found = true;
                    cout << "\nWelcome " << system->employees[i].name
                        << " " << system->employees[i].lastName << "!\n";
                    pause();
                    employeeMenu(system);
                    break;
                }
            }

            if (!found) {
                cout << "\nEmployee not found!\n";
                pause();
            }
            break;
        }
        case 0:
            cout << "\nExiting...\n";
            break;
        default:
            cout << "\nInvalid choice!\n";
            pause();
        }
    } while (choice != 0);
}

void customerMenu(BankSystem* system, Account* account) {
    int choice;

    do {
        clearScreen();
        cout << "\n========== CUSTOMER MENU ==========\n";
        cout << "Account: " << account->accountNumber << "\n";
        cout << "Holder: " << account->holderName << "\n";
        cout << "Balance: " << fixed << setprecision(3)
            << account->balance << " TND\n";
        cout << "===================================\n";
        cout << "1. View Loans\n";
        cout << "2. Submit Loan Request\n";
        cout << "3. Perform Transaction\n";
        cout << "4. View Daily Transactions\n";
        cout << "5. Undo Last Transaction\n";
        cout << "0. Logout\n";
        cout << "===================================\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewLoans(account);
            pause();
            break;
        case 2:
            submitLoanRequest(system, account);
            pause();
            break;
        case 3:
            performTransaction(account);
            pause();
            break;
        case 4:
            viewDailyTransactions(account);
            pause();
            break;
        case 5:
            undoLastTransaction(account);
            pause();
            break;
        case 0:
            cout << "\nLogging out...\n";
            break;
        default:
            cout << "\nInvalid choice!\n";
            pause();
        }
    } while (choice != 0);
}

void employeeMenu(BankSystem* system) {
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

// Utility functions
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}






