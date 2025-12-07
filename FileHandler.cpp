
#include"FileHandler.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int loadEmployees(employee employees[], int maxSize) {
    ifstream file("employees.txt");
    if (!file) return 0;

    string line; int count = 0;
    while (getline(file, line) && count < maxSize) {
        stringstream ss(line);
        string token;
        employee e;

        getline(ss, e.ID, ';');
        getline(ss, e.name, ';');
        getline(ss, e.LastName, ';');
        getline(ss, e.address, ';');
        getline(ss, token, ';'); e.salary = stof(token);
        getline(ss, token, ';'); e.HireDate.day = stoi(token);
        getline(ss, token, ';'); e.HireDate.month = stoi(token);
        getline(ss, token, ';'); e.HireDate.year = stoi(token);
        getline(ss, e.BankBranch, ';');

        employees[count++] = e;
    }
    return count;
}

void saveEmployees(employee employees[], int size) {
    ofstream file("employees.txt");
    for (int i = 0; i < size; i++) {
        file << employees[i].ID << ";" << employees[i].name << ";" << employees[i].LastName << ";"
            << employees[i].address << ";" << employees[i].salary << ";"
            << employees[i].HireDate.day << ";" << employees[i].HireDate.month << ";" << employees[i].HireDate.year << ";"
            << employees[i].BankBranch << "\n";
    }
}

int loadCustomers(customer customers[], int maxSize) {
    ifstream file("customers.txt");
    if (!file) return 0;

    string line; int count = 0;
    while (getline(file, line) && count < maxSize) {
        stringstream ss(line);
        string token;
        customer c;

        getline(ss, token, ';'); c.AccNum = stoi(token);
        getline(ss, c.passwrd, ';');
        getline(ss, c.AccType, ';');
        getline(ss, token, ';'); c.IBAN = stoi(token);
        getline(ss, token, ';'); c.Branch = stoi(token);
        getline(ss, c.name, ';');
        getline(ss, token, ';'); c.OpDate.day = stoi(token);
        getline(ss, token, ';'); c.OpDate.month = stoi(token);
        getline(ss, token, ';'); c.OpDate.year = stoi(token);
        getline(ss, c.status, ';');
        getline(ss, token, ';'); c.balance = stof(token);

        customers[count++] = c;
    }
    return count;
}

void saveCustomers(customer customers[], int size) {
    ofstream file("customers.txt");
    for (int i = 0; i < size; i++) {
        file << customers[i].AccNum << ";" << customers[i].passwrd << ";" << customers[i].AccType << ";"
            << customers[i].IBAN << ";" << customers[i].Branch << ";" << customers[i].name << ";"
            << customers[i].OpDate.day << ";" << customers[i].OpDate.month << ";" << customers[i].OpDate.year << ";"
            << customers[i].status << ";" << customers[i].balance << "\n";
    }
}

int loadLoans(LoanList& loanList, int accNum) {
    ifstream file("loans_" + to_string(accNum) + ".txt");
    if (!file) return 0;

    string line; int count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        loan l;

        getline(ss, token, ';'); l.ID = stoi(token);
        getline(ss, l.type, ';');
        getline(ss, token, ';'); l.amount = stof(token);
        getline(ss, token, ';'); l.InterestRate = stof(token);
        getline(ss, token, ';'); l.AmPaid = stof(token);
        getline(ss, token, ';'); l.ReBalance = stof(token);
        getline(ss, token, ';'); l.StartDate.day = stoi(token);
        getline(ss, token, ';'); l.StartDate.month = stoi(token);
        getline(ss, token, ';'); l.StartDate.year = stoi(token);
        getline(ss, token, ';'); l.EndDate.day = stoi(token);
        getline(ss, token, ';'); l.EndDate.month = stoi(token);
        getline(ss, token, ';'); l.EndDate.year = stoi(token);
        getline(ss, l.LoanStatus, ';');

        addLoan(&loanList, l, ListSize(loanList) + 1);
        count++;
    }
    return count;
}

void saveLoans(const LoanList& loanList) {
    ofstream file("loans_" + to_string(loanList.head->data.ID) + ".txt");
    Nodelist* curr = loanList.head;
    while (curr) {
        file << curr->data.ID << ";" << curr->data.type << ";" << curr->data.amount << ";"
            << curr->data.InterestRate << ";" << curr->data.AmPaid << ";" << curr->data.ReBalance << ";"
            << curr->data.StartDate.day << ";" << curr->data.StartDate.month << ";" << curr->data.StartDate.year << ";"
            << curr->data.EndDate.day << ";" << curr->data.EndDate.month << ";" << curr->data.EndDate.year << ";"
            << curr->data.LoanStatus << "\n";
        curr = curr->next;
    }
}


int loadTransactions(stack& s, int accNum) {
    ifstream file("transactions_" + to_string(accNum) + ".txt");
    if (!file) return 0;

    string line; int count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        transaction t;

        getline(ss, token, ';'); t.ID = stoi(token);
        getline(ss, token, ';'); t.AccountNum = stoi(token);
        getline(ss, t.TransType, ';');
        getline(ss, token, ';'); t.Amount = stof(token);
        getline(ss, token, ';'); t.TransDate.day = stoi(token);
        getline(ss, token, ';'); t.TransDate.month = stoi(token);
        getline(ss, token, ';'); t.TransDate.year = stoi(token);

        push(&s, t);
        count++;
    }
    return count;
}

void saveTransactions(const stack& s, int accNum) {
    ofstream file("transactions_" + to_string(accNum) + ".txt");
    Nodetrans* curr = s.top;
    while (curr) {
        file << curr->data.ID << ";" << curr->data.AccountNum << ";" << curr->data.TransType << ";"
            << curr->data.Amount << ";" << curr->data.TransDate.day << ";" << curr->data.TransDate.month << ";" << curr->data.TransDate.year << "\n";
        curr = curr->next;
    }
}

int loadArchivedAccounts(customer archived[], int maxSize) {
    ifstream file("archived_accounts.txt");
    if (!file) return 0;

    string line; int count = 0;
    while (getline(file, line) && count < maxSize) {
        stringstream ss(line);
        string token;
        customer c;

        getline(ss, token, ';'); c.AccNum = stoi(token);
        getline(ss, c.passwrd, ';');
        getline(ss, c.AccType, ';');
        getline(ss, token, ';'); c.IBAN = stoi(token);
        getline(ss, token, ';'); c.Branch = stoi(token);
        getline(ss, c.name, ';');
        getline(ss, token, ';'); c.OpDate.day = stoi(token);
        getline(ss, token, ';'); c.OpDate.month = stoi(token);
        getline(ss, token, ';'); c.OpDate.year = stoi(token);
        getline(ss, c.status, ';');
        getline(ss, token, ';'); c.balance = stof(token);

        archived[count++] = c;
    }
    return count;
}

void saveArchivedAccounts(customer archived[], int size) {
    ofstream file("archived_accounts.txt");
    for (int i = 0; i < size; i++) {
        file << archived[i].AccNum << ";" << archived[i].passwrd << ";" << archived[i].AccType << ";"
            << archived[i].IBAN << ";" << archived[i].Branch << ";" << archived[i].name << ";"
            << archived[i].OpDate.day << ";" << archived[i].OpDate.month << ";" << archived[i].OpDate.year << ";"
            << archived[i].status << ";" << archived[i].balance << "\n";
    }
}

int loadCompletedLoans(CompList& list) {
    ifstream file("completed_loans.txt");
    if (!file) return 0;

    string line; int count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        loan l;

        getline(ss, token, ';'); l.ID = stoi(token);
        getline(ss, l.type, ';');
        getline(ss, token, ';'); l.amount = stof(token);
        getline(ss, token, ';'); l.InterestRate = stof(token);
        getline(ss, token, ';'); l.AmPaid = stof(token);
        getline(ss, token, ';'); l.ReBalance = stof(token);
        getline(ss, token, ';'); l.StartDate.day = stoi(token);
        getline(ss, token, ';'); l.StartDate.month = stoi(token);
        getline(ss, token, ';'); l.StartDate.year = stoi(token);
        getline(ss, token, ';'); l.EndDate.day = stoi(token);
        getline(ss, token, ';'); l.EndDate.month = stoi(token);
        getline(ss, token, ';'); l.EndDate.year = stoi(token);
        getline(ss, l.LoanStatus, ';');

        addCompLoan(&list, l);
        count++;
    }
    return count;
}
void saveCompletedLoans(const CompList& list) {
    ofstream file("completed_loans.txt");
    NodeCompLoan* curr = list.head;
    while (curr) {
        file << curr->data.ID << ";" << curr->data.type << ";" << curr->data.amount << ";"
            << curr->data.InterestRate << ";" << curr->data.AmPaid << ";" << curr->data.ReBalance << ";"
            << curr->data.StartDate.day << ";" << curr->data.StartDate.month << ";" << curr->data.StartDate.year << ";"
            << curr->data.EndDate.day << ";" << curr->data.EndDate.month << ";" << curr->data.EndDate.year << ";"
            << curr->data.LoanStatus << "\n";
        curr = curr->next;
    }
}