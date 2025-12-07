#include <iostream>
#include <string>

using namespace std;
Loan loans[] = {
    {1, 101, "Mortgage", "Active", "2024-01-15"},
    {2, 102, "Auto", "Active", "2024-03-10"},
    {3, 101, "Personal", "Closed", "2023-05-20"},
    {4, 103, "Student", "Active", "2025-02-01"},
    {5, 103, "Auto", "Active", "2025-04-12"}
};
const int LOAN_COUNT = sizeof(loans) / sizeof(Loan);

Account accounts[] = {
    {101, 15000.50},
    {102, 350.75},
    {103, 9800.00}
};
const int ACCOUNT_COUNT = sizeof(accounts) / sizeof(Account);

Employee employees[] = {
    {501, 1}, {502, 1}, {503, 2}, {504, 2}, {505, 3}
};
const int EMPLOYEE_COUNT = sizeof(employees) / sizeof(Employee);

bool equal(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return false;
        i++;
    }
    return s1[i] == '\0' && s2[i] == '\0';
}

void print_metrics() {
    cout << "Banking System Metrics:\n";

    cout << "- Total loans: " << LOAN_COUNT << "\n";

    cout << "- Loans by type:\n";
    int mortgage_count = 0;
    int auto_count = 0;
    int personal_count = 0;
    int student_count = 0;

    for (int i = 0; i < LOAN_COUNT; ++i) {
        if (equal(loans[i].type, "Mortgage")) mortgage_count++;
        else if (equal(loans[i].type, "Auto")) auto_count++;
        else if (equal(loans[i].type, "Personal")) personal_count++;
        else if (equal(loans[i].type, "Student")) student_count++;
    }
    if (mortgage_count > 0) cout << "  Mortgage: " << mortgage_count << "\n";
    if (auto_count > 0) cout << "  Auto: " << auto_count << "\n";
    if (personal_count > 0) cout << "  Personal: " << personal_count << "\n";
    if (student_count > 0) cout << "  Student: " << student_count << "\n";

    
    cout << "- Loans by status:\n";
    int active_count = 0;
    int closed_count = 0;
    for (int i = 0; i < LOAN_COUNT; ++i) {
        if (equal(loans[i].status, "Active")) active_count++;
        else if (equal(loans[i].status, "Closed")) closed_count++;
    }
    if (active_count > 0) cout << "  Active: " << active_count << "\n";
    if (closed_count > 0) cout << "  Closed: " << closed_count << "\n";

    const char* start = "2025-01-01";
    const char* end = "2025-12-31";
    int active_in_range = 0;
    for (int i = 0; i < LOAN_COUNT; ++i)
        if (are_strings_equal(loans[i].status, "Active") &&
            strcmp(loans[i].start_date, start) >= 0 &&
            strcmp(loans[i].start_date, end) <= 0) {
            active_in_range++;
        }
    }
    cout << "- Active loans between " << start << " and " << end << ": " << active_in_range << "\n";

    int count_101 = 0;
    int count_102 = 0;
    int count_103 = 0;
    for (int i = 0; i < LOAN_COUNT; ++i) {
        if (loans[i].customer_id == 101) count_101++;
        else if (loans[i].customer_id == 102) count_102++;
        else if (loans[i].customer_id == 103) count_103++;
    }

    int highest_loan_count = count_101;
    int customer_with_most_loans = 101;

    if (count_102 > highest_loan_count) {
        highest_loan_count = count_102;
        customer_with_most_loans = 102;
    }
    if (count_103 > highest_loan_count) {
        highest_loan_count = count_103;
        customer_with_most_loans = 103;
    }
    cout << "- Customer " << customer_with_most_loans << " has the highest loan count (" << highest_loan_count << ")\n";
    
   
    int max = 0;
    int min = 0;

    for (int i = 1; i < ACCOUNT_COUNT; ++i) {
        if (accounts[i].balance > accounts[max].balance) {
            max = i;
        }
        if (accounts[i].balance < accounts[min].balance) {
            min = i;
        }
    }
    cout << "- Customer " << accounts[max_acc_index].customer_id << " has the highest balance (" << accounts[max_acc_index].balance << ")\n";
    cout << "- Customer " << accounts[min_acc_index].customer_id << " has the lowest balance (" << accounts[min_acc_index].balance << ")\n"
    cout << "- Total employees: " << EMPLOYEE_COUNT << "\n";
    cout << "- Employees per branch:\n";
   
    int branch1_count = 0;
    int branch2_count = 0;
    int branch3_count = 0;

    for (int i = 0; i < EMPLOYEE_COUNT; i++) {
        if (employees[i].branch_id == 1) branch1_count++;
        else if (employees[i].branch_id == 2) branch2_count++;
        else if (employees[i].branch_id == 3) branch3_count++;
    }
    if (branch1_count > 0) cout << "  Branch 1: " << branch1_count << "\n";
    if (branch2_count > 0) cout << "  Branch 2: " <<  branch2_count << "\n";
    if (branch3_count > 0) cout << "  Branch 3: " << branch3_count << "\n";
}








int main()
{
    print_metrics();
    return 0;
}
