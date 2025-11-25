#include <iostream>
#include <string>
using namespace std;
#include"customer.h"

const int MAX_CUSTOMERS = 10;

// Function to initialize sample customers
int initializeCustomers(Customer customers[]) {
    customers[0] = { "ACC001", "John Smith", "pass123", 5000.50 };
    customers[1] = { "ACC002", "Sarah Johnson", "secure456", 12500.75 };
    customers[2] = { "ACC003", "Mike Wilson", "mypass789", 3200.00 };

    return 3; // Return the number of customers
}

// Function to authenticate customer   method1
Customer* authenticateCustomer(Customer customers[], int numCustomers, string accNum, string pass) {
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].accountNumber == accNum && customers[i].password == pass) {
            return &customers[i];
        }
    }
    return nullptr;
}
//method 2
int authenticateCustomer(Customer customers[], int numCustomers, string accNum, string pass) {
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].accountNumber == accNum && customers[i].password == pass) {
            return i; // Return the index where customer was found
        }
    }
    return -1; // Return -1 if customer not found
}


// Function to display customer menu
void displayMenu() {
    cout << "\n===== Banking Menu =====" << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. View Account Details" << endl;
    cout << "3. Logout" << endl;
    cout << "========================" << endl;
    cout << "Enter your choice: ";
}

// Function to display account details
void displayAccountDetails(Customer* customer) {
    cout << "\n----- Account Details -----" << endl;
    cout << "Account Number: " << customer->accountNumber << endl;
    cout << "Name: " << customer->name << endl;
    cout << "Balance: $" << customer->balance << endl;
    cout << "---------------------------" << endl;
}

int main() {
    Customer customers[MAX_CUSTOMERS];
    int numCustomers = initializeCustomers(customers);
    Customer* loggedInCustomer = nullptr;
    int maxAttempts = 3;
    int attempts = 0;

    cout << "=====================================" << endl;
    cout << "  Welcome to SecureBank Login System" << endl;
    cout << "=====================================" << endl;

    // Login process
    while (attempts < maxAttempts && loggedInCustomer == nullptr) {
        string accountNum, password;

        cout << "\nAttempt " << (attempts + 1) << " of " << maxAttempts << endl;
        cout << "Enter Account Number: ";
        cin >> accountNum;
        cout << "Enter Password: ";
        cin >> password;

        loggedInCustomer = authenticateCustomer(customers, numCustomers, accountNum, password);

        if (loggedInCustomer == nullptr) {
            attempts++;
            if (attempts < maxAttempts) {
                cout << "\n[ERROR] Invalid credentials! Please try again." << endl;
            }
        }
    }

    // Check if login was successful
    if (loggedInCustomer == nullptr) {
        cout << "\n[LOCKED] Maximum login attempts exceeded!" << endl;
        cout << "Your account has been temporarily locked." << endl;
        return 1;
    }

    // Successful login
    cout << "\n[SUCCESS] Login successful!" << endl;
    cout << "Welcome, " << loggedInCustomer->name << "!" << endl;

    // Main banking menu loop
    bool isLoggedIn = true;
    while (isLoggedIn) {
        displayMenu();

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nYour current balance is: $" << loggedInCustomer->balance << endl;
            break;
        case 2:
            displayAccountDetails(loggedInCustomer);
            break;
        case 3:
            cout << "\nLogging out... Thank you for banking with us!" << endl;
            isLoggedIn = false;
            break;
        default:
            cout << "\n[ERROR] Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}

/*
Sample Login Credentials for Testing:
Account: ACC001, Password: pass123
Account: ACC002, Password: secure456
Account: ACC003, Password: mypass789
*/