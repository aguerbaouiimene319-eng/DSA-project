
#include"LoanRequestMeth.h"
#include"LoanListMeth.h"
#include"customer.h"
#include"employee.h"
#include"TransactionStackMeth.h"
#include"CompletedLoanListMeth.H"
#include<iostream>
#include<string>

#include"statistics.cpp"
using namespace std;

constexpr int Max_customers = 10000;
constexpr int Max_employees = 2000;
employee employeeArray[Max_employees];
customer customerArray[Max_customers];
customer archivedAccounts[Max_customers];
CompList* completedloans = createCompList();

queue* loanRequests = createQueue();

void employeeInterface() {
	char choice;
	do {
		std::cout << "\n============ EMPLOYEE MENU ============\n";
		std::cout << "1.  Add Employee\n";
		std::cout << "2.  Delete Employee\n";
		std::cout << "3.  Modify Employee\n";
		std::cout << "4.  Display Employees (Alphabetical)\n";
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
		case '1': 
			addEmployee();
			break;
		case '2': 
			deleteEmployee();
			break;
		case '3': 
			modifyEmployee(); 
			break;
		case '4': 
			displayEmployeesByAlphabeliticalOrder();
			break;
		case '5': 
			displayEmployeesByBranch(); 
			break;
		case '6': 
			displayRecruitmentInfo();
			break;
		case '7':
			addCustomerAccount(); 
			break;
		case '8':
			displayCustomerAccounts(); 
			break;
		case '9':
			changeAccountStatus(); 
			break;
		case '10':
			archiveClosedAccounts();//delete closed status for accounts ans store them in an array
			break;
		case '11':
			displayCustomerLoans();
			break;
		case '12':
			changeLoanStatus();
			break;
		case '13':
			deleteCompletedLoans();
			break;
		case '14':
			processLoanRequests(); 
			break;
		case '15':
			finalizeDay();
			break;
		case '16':
			displayStatistics(); 
			break;
		case '0':
			std::cout << "\nLogging out...\n"; break;
		default: std::cout << "\nInvalid choice!\n";
		}
	} while (choice !='0' || choice>'16');
}
// function to return the exact size of the array, the fulled ones
int sizeofarrayEmployee(employee employeeArray[]) {
	int size = 0;
	while (size < Max_employees && employeeArray[size].ID != "" && employeeArray[size].name != "") {
		size++;
	}
	return size;
}
// returns the filled cases in the array of customers
int sizeofarrayCustomer(customer customerArray[]) {
	int size = 0;
	while (size < Max_customers && customerArray[size].AccNum != 0 && customerArray[size].name != "") {
		size++;
	}
	return size;
}

// 1) add employee
//________________it is done
void addEmployee() {
	cout << "add employee" << endl;
	int size = sizeofarrayEmployee(employeeArray);
	employee emp;
	cout << "Employee ID: ";
	cin >> emp.ID;
	// Check uniqueness
	for (int i = 0; i < size; i++) {
		if (employeeArray[i].ID == emp.ID) {
			cout << "Employee ID already exists!\n";
			return;
		}
	}
	cout << "Name: ";
	cin.ignore();
	getline(cin, emp.name);

	cout << "Last Name: ";
	getline(cin, emp.LastName);

	cout << "Address: ";
	getline(cin, emp.address);

	cout << "Salary (TND): ";
	cin >> emp.salary;

	cout << "Hire Date (DD MM YYYY): ";
	cin >> emp.HireDate.day >> emp.HireDate.month >> emp.HireDate.year;

	cout << "Branch Code (1 for head office): ";
	cin >> emp.BankBranch;


	employeeArray[size] = emp;
	size++;
	cout << "Employee" << emp.ID << "added successfully\n";
}

//2) delete employee
//___________________it is done
void deleteEmployee() {
	string IDsearch;
	cout << "enter the ID of the employee you want to delete :" << endl;
	cin >> IDsearch;
	int size = sizeofarrayEmployee(employeeArray);
	int index = -1;
	for (int i = 0; i < size; i++) {
		if (employeeArray[i].ID == IDsearch) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "employee of id " << IDsearch << "is not founded. Can't remove" << endl;
		return;
	}
	// move to the right
	for (int i = index; i < size - 1; i++) {
		employeeArray[i] = employeeArray[i + 1];
	}
	size--;
	cout << "Employee of ID" << IDsearch << "removed successfully" << endl;
	return;
}

//3) modifiy employee
//------------------it is done
/*bool modifyEmployee() {
	int IDsearch;
	cout << "enter the ID of the employee you want to modify" << endl;
	cin >> IDsearch;
	employee* emp = find(e);
	if (emp == nullptr) {
		cout << "employee of ID" << e.ID << "not found. Cannot modify" << endl;
		return false;
	}
	emp->address = e.address;
	emp->BankBranch = e.BankBranch;
	emp->name = e.name;
	emp->ID = e.ID;
	emp->HireDate = e.HireDate;
	emp->LastName = e.LastName;
	emp->salary = e.salary;
	cout << "employee of id " << e.ID << "is modified successfully." << endl;
	return true;
}*/

void modifyEmployee() {
	//clearScreen();
	cout << "\n=== Modify Employee ===\n";
	int size = sizeofarrayEmployee(employeeArray);
	string empId;
	cout << "Enter Employee ID: ";
	cin >> empId;

	for (int i = 0; i < size; i++) {
		if (employeeArray[i].ID == empId) {
			employee emp = employeeArray[i];

			cout << "\nCurrent Details:\n";
			cout << "Name: " << emp.name << " " << emp.LastName << "\n";
			cout << "Salary: " << emp.salary << " TND\n";

			cout << "\nEnter new details:\n";
			cout << "Name: ";
			cin.ignore();
			getline(cin, emp.name);

			cout << "Last Name: ";
			getline(cin, emp.LastName);

			cout << "Address: ";
			getline(cin, emp.address);
			
			cout << "ID: ";
			cin >> emp.ID;
			
			for (int j = 0; j < size; j++) {
				if (j != i && employeeArray[j].ID == emp.ID) {
					cout << "This ID already exists! Modification canceled.\n";
					return;
				}
			}

			cout << "Salary: ";
			cin >> emp.salary;

			cout << "Branch Code: ";
			cin >> emp.BankBranch;

			cout << "New hire date: " << endl;
			cin >> emp.HireDate.day >> emp.HireDate.month >> emp.HireDate.year;

			employeeArray[i] = emp;
			cout << "\nEmployee updated successfully!\n";
			return;
		}
	}

	cout << "\nEmployee not found!\n";
}



//4) display employees
// a sort function is needed
//----------------------it is done 
void sortEmployeesByLastName(employee employees[]) {
	// Bubble sort by last name
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
	if (size == 0) {
		cout << "No employees found.\n";
		return;
	}

	// Create a copy for sorting
	employee* tempEmployees = new employee[size];
	for (int i = 0; i < size; i++) {
		tempEmployees[i] = employeeArray[i];
	}

	sortEmployeesByLastName(tempEmployees);

	for (int i = 0; i < size; i++) {
		cout << "\nEmployee " << (i + 1) << ":\n";
		cout << "ID: " << tempEmployees[i].ID << "\n";
		cout << "Name: " << tempEmployees[i].name << " "
			<< tempEmployees[i].LastName << "\n";
		cout << "Salary: " << tempEmployees[i].salary << " TND\n";
		cout << "Branch: " << tempEmployees[i].BankBranch << "\n";
		cout << "Hire Date: "<< tempEmployees[i].HireDate.day<< tempEmployees[i].HireDate.month<< tempEmployees[i].HireDate.year;
		cout << "\n";
	}

	delete[] tempEmployees;
}


//_________not revised
//5) display employees by branch
void displayEmployeesByBranch() {

	std::cout << "\n=== Employees Grouped by Branch ===\n";
	int size = sizeofarrayEmployee(employeeArray);
	if (size == 0) {
		std::cout << "No employees found.\n";
		return;
	}

	// Get unique branches
	string branches[Max_employees];
	int branchCount = 0;

	for (int i = 0; i < size; i++) {
		bool found = false;
		for (int j = 0; j < branchCount; j++) {
			if (branches[j] == employeeArray[i].BankBranch) {
				found = true;
				break;
			}
		}
		if (!found) {
			branches[branchCount++] = employeeArray[i].BankBranch;
		}
	}

	// Display by branch
	for (int i = 0; i < branchCount; i++) {
		std::cout << "\n--- Branch " << branches[i] << " ---\n";
		for (int j = 0; j < size; j++) {
			if (employeeArray[j].BankBranch == branches[i]) {
				std::cout << "  " << employeeArray[j].name << " "
					<< employeeArray[j].LastName
					<< " (ID: " << employeeArray[j].ID << ")\n";
			}
		}
	}
}

// ______________________it is done
bool compareDates(date d1, date d2) {
	if (d1.year < d2.year)
		return true;
	if (d1.year > d2.year)
		return false;

	if (d1.month < d2.month)
		return true;
	if (d1.month > d2.month)
		return false;

	if (d1.day < d2.day)
		return true;

	return false;
}

//6) display recruitment info

//----------- it is done
void displayRecruitmentInfo() {
	cout << "\n=== Recruitment Information ===\n";
	int size = sizeofarrayEmployee(employeeArray);
	if (size == 0) {
		cout << "No employees found.\n";
		return;
	}

	int earliestIdx = 0;
	int latestIdx = 0;
	
	// void compare dates should be done 
	for (int i = 1; i < size; i++) {
		if (compareDates(employeeArray[i].HireDate,employeeArray[earliestIdx].HireDate)) {
			earliestIdx = i;
		}
		if (compareDates(employeeArray[latestIdx].HireDate,employeeArray[i].HireDate)) {
			latestIdx = i;
		}
	}

	cout << "\nEarliest Recruited Employee:\n";
	cout << "Name: " << employeeArray[earliestIdx].name << " "
		<< employeeArray[earliestIdx].LastName << "\n";
	cout << "Hire Date: "
		<< employeeArray[earliestIdx].HireDate.day
		<< employeeArray[earliestIdx].HireDate.month
		<< employeeArray[earliestIdx].HireDate.year << endl;

	cout << "\n\nMost Recently Recruited Employee:\n";
	cout << "Name: " << employeeArray[latestIdx].name << " "
		<< employeeArray[latestIdx].LastName << "\n";
	cout << "Hire Date: "
	     <<employeeArray[latestIdx].HireDate.day
		 << employeeArray[earliestIdx].HireDate.month
		 << employeeArray[earliestIdx].HireDate.year << endl;


	cout << "\n";
}

//_______________________done________________________
//7) add customer account 
void addCustomerAccount() {
	cout << "\n=== Add Customer Account ===\n";
	int size = sizeofarrayCustomer(customerArray);
	if (size >= Max_employees) {
		cout << "Account limit reached!\n";
		return;
	}
	customer acc{};
	customerArray[size]=acc;

	cout << "Account Number: ";
	cin >> acc.AccNum;

	// Check uniqueness
	for (int i = 0; i < size; i++) {
		if (customerArray[i].AccNum == acc.AccNum) {
			cout << "Account number already exists!\n";
			return;
		}
	}

	cout << "Account Type: ";
	cin >> acc.AccType;

	cout << "IBAN: ";
	cin >> acc.IBAN;

	cout << "Branch Code: ";
	cin >> acc.Branch;

	cout << "Account Holder Name: ";
	cin.ignore();
	getline(cin, acc.name);

	acc.OpDate = getDateFromEmployee();
	acc.status = "active";

	cout << "Initial Balance (TND): ";
	cin >> acc.balance;

	cout << "Set Password: ";
	cin >> acc.passwrd;

	// Initialize loan list and transaction stack
	acc.loans = *createList();
	acc.transList = *createStack();

	size++;
	cout << "\nAccount created successfully!\n";
	cout << "Account Number: " << acc.AccNum << "\n";
}

date getDateFromEmployee() {
	date d = {};
	cout << "enter day: ";
	cin >> d.day;
	cout << "enter month: ";
	cin >> d.month;
	cout << "enter year: ";;
	cin >> d.year;
	return d;
}

//void addCustomerAccount(){}
//_______________done
//8)display customers

void displayCustomerAccounts() {
	cout << "\n=== Customer Accounts ===\n";
	int size = sizeofarrayCustomer(customerArray);
	if (size == 0) {
		cout << "No accounts found.\n";
		return;
	}
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

//void displayCustomerAccounts(){}
//__________done
//9) change status of customers
void changeAccountStatus() {

	cout << "\n=== Change Account Status ===\n";

	int accountNum;
	cout << "Enter Account Number: ";
	cin >> accountNum;

	int idx = findAccountIndex(customerArray, accountNum);
	if (idx == -1) {
		cout << "\nAccount not found!\n";
		return;
	}

	cout << "\nCurrent Status: " << customerArray[idx].status << "\n";
	cout << "New Status (active/inactive/closed): ";
	cin >> customerArray[idx].status;

	cout << "\nStatus updated successfully!\n";
}

int findAccountIndex(customer customerArray[], int accnum) {
	int size = sizeofarrayCustomer(customerArray);
	for (int i = 0; i < size; i++) {
		if (customerArray[i].AccNum == accnum) {
			return i;
		}
	}
	return -1;
}

//----------------done
//10)delete closed status for accounts ans store them in an array
void archiveClosedAccounts() {
	cout << "\n=== Archive Closed Accounts ===\n";

	int archivedCount = 0;
	int i = 0;
	int size = sizeofarrayCustomer(customerArray);
	while (i < size) {
		if (customerArray[i].status == "closed") {
			if (archivedCount < Max_customers) {
				archivedAccounts[archivedCount++] =
					customerArray[i];
			}

			// Remove from active accounts
			for (int j = i; j < size - 1; j++) {
				customerArray[j] = customerArray[j + 1];
			}
			size--;
		}
		else {
			i++;
		}
	}
}

//-----------------done
//11) display Customer Loans
void displayCustomerLoans() {
	cout << "\n=== Display Customer Loans ===\n";

	int accountNum;
	cout << "Enter Account Number: ";
	cin >> accountNum;

	int idx = findAccountIndex(customerArray, accountNum);
	if (idx == -1) {
		cout << "\nAccount not found!\n";
		return;
	}

	cout << "\nLoans for Account " << accountNum << ":\n";
	displayLoan(customerArray[idx].loans);
}
//void displayCustomerLoans(){}

//12) change loan status


void changeLoanStatus() {
	cout << "\n=== Change Loan Status ===\n";

	int accountNum, 
	int loanId;
	cout << "Enter Account Number: ";
	cin >> accountNum;

	int idx = findAccountIndex(customerArray, accountNum);
	if (idx == -1) {
		cout << "\nAccount not found!\n";
		return;
	}

	cout << "Enter Loan ID: ";
	cin >> loanId;
	LoanList L = customerArray[idx].loans;
	loan* l = findloan(&L, loanId);
	if (!l) {
		cout << "\nLoan not found!\n";
		return;
	}

	cout << "\nCurrent Status: " << l->LoanStatus << "\n";
	cout << "New Status (active/completed/overdue): ";
	cin >> l->LoanStatus;

	cout << "\nLoan status updated!\n";
}

loan* findloan(LoanList*l, int loanId) {
	Nodelist* curr = l->head;
	while (curr ) {
		if (curr->data.ID == loanId) {
			return &curr->data;
		}
		curr = curr->next;
	}
	return nullptr;
}


//declare update loan status

//13) delete completed loans and store in a singly linked list

void deleteCompletedLoans() {
	cout << "\n=== Delete Completed Loans ===\n";

	int totalDeleted = 0;
	int size = sizeofarrayCustomer(customerArray);
	for (int i = 0; i < size; i++) {
		LoanList* list = &customerArray[i].loans;
		Nodelist* current = list->head;

		while (current != nullptr) {
			Nodelist* next = current->next;

			if (current->data.LoanStatus == "completed") {
				// Add to completed loans list
				addCompLoan(completedloans, current->data);

				// Remove from loan list
				deleteLoan(list, current->data.ID);
				totalDeleted++;
			}

			current = next;
		}
	}

	cout << "\nDeleted " << totalDeleted << " completed loans.\n";
	cout << "They have been moved to the completed loans archive.\n";
}

//14) manage loan requests (FIFO) queue (declined :permenantly deleted/accepted: added to customer loans and removed from list of loans request)
void processLoanRequests() {
	
	cout << "\n=== Process Loan Requests ===\n";

	if (isEmpty(*loanRequests)) {
		cout << "No pending loan requests.\n";
		return;
	}

	LoanRequest loan=dequeue(loanRequests);
	int accountNum=loan.requestAccNumber;

	cout << "\nProcessing Loan Request:\n";
	cout << "Account: " << accountNum << "\n";
	cout << "Loan ID: " << loan.requestAccNumber << "\n";
	cout << "Type: " << loan.loanType << "\n";
	cout << "Amount: " << loan.PrincipleAmount << " TND\n";

	cout << "\nAccept this loan? (yes/no): ";
	char choice;
	cin >> choice;

	if (choice == 'yes' || choice == 'YES') {
		Nodelist* nL = new(nothrow)Nodelist{};
		int idx = findAccountIndex(customerArray, accountNum);
		if (idx != -1) {
			nL->data.LoanStatus = "active";
			nL->data.amount = loan.PrincipleAmount;
			nL->data.AmPaid = 0;
			nL->data.ID = generateUniqueLoanID();
			nL->data.type = loan.loanType;
			nL->data.EndDate = loan.EndDate;

			cout << "enter the interest rate of this loan :" << endl;
			cin >> nL->data.InterestRate;

			nL->data.StartDate = loan.StartDate;
			nL->data.ReBalance = (nL->data.amount + (nL->data.amount * nL->data.InterestRate));
			
			addLoan(&customerArray[idx].loans, nL->data, 1);
			
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
// Check if a loan ID already exists in all customers
bool loanIdExists(int id) {
	int size = sizeofarrayCustomer(customerArray);

	for (int i = 0; i < size; i++) {
		Nodelist* curr = customerArray[i].loans.head;
		while (curr) {
			if (curr->data.ID == id) {
				return true;
			}
			curr = curr->next;
		}
	}
	return false;
}

// Generate a unique loan ID
int generateUniqueLoanID() {
	int id;
	do {
		id = rand();
	} while (loanIdExists(id));

	return id;
}

// function mentionned of add new loan will be used in the request process as a primitive function 

// used in process loan reaquest
// if laon is accepted,just add it in the loan list


//15) finalize the Day( transaction log ,day's transactions go to a singly linked list)
void finalizeDay() {
	bool dayFinalized = false;
	int size = sizeofarrayCustomer(customerArray);
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

	for (int i = 0; i < size; i++) {
		// In a real system, we would copy transactions to a permanent list
		// For this implementation, we just clear the stacks
		destroyStack(&customerArray[i].transList);
		customerArray[i].transList = *createStack();
	}

	dayFinalized = true;
	cout << "\nDay finalized successfully!\n";
	cout << "All daily transactions have been recorded.\n";
}
//16) display the statistics
void displayStatistics() {
	Statistics_main();
}

