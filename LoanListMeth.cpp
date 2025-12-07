#include"LoanListMeth.h"
#include<iostream>
using namespace std;


Nodelist* createloan(loan data) {
	Nodelist* n = new (nothrow) Nodelist{ data };
	if (!n)
		cerr << "\nMemory allocation failed for new loan\n";
	return n;
}
void destroyLoan(loan* loan) {
	delete loan;
}

LoanList* createList() {
	LoanList* L = new LoanList{};
	return L;
}
void destroyList(LoanList* L) {
	if (!L)return;
	Nodelist* currnt = L->head;
	while (currnt) {
		Nodelist* temp = currnt;
		currnt = currnt->next;
		delete temp;
	}
	L->head = nullptr;
	L->tail = nullptr;
}

bool isEmpty(const LoanList& L) {
	return L.head == nullptr;
}
bool isFull(const LoanList& L) {
	Nodelist* n = new (nothrow)Nodelist;
	if (!n) return true;
	delete n;
	return false;
}
int ListSize(const LoanList& L) {
	if (isEmpty)return 0;
	int size;
	Nodelist* n = L.head;
	while (n != nullptr) {
		size++;
		n = n->next;
	}
	return size;
}

int addLoan(LoanList* L, loan l, int pos) {
	int size = ListSize(*L);
	if (!L) return 0;
	if (pos<1 || pos> size + 1) {
		cerr << "\nCan not insert in these positions\n";
		return 0;
	}
	Nodelist* n = new (nothrow) Nodelist{};
	if (!n) {
		cerr << "\nMemory allocation failed for new loan\n";
		return 0;
	}
	if (isEmpty(*L)) {
		L->head = n;
		L->tail = n;
	}
	else if (pos == 1) {
		L->head->prev = n;
		n->next = L->head;
		L->head = n;
	}
	else if (pos = size) {
		L->tail->next = n;
		n->prev = L->tail;
		L->tail = n;
	}
	else {
		Nodelist* pre = nullptr;
		Nodelist* curr = L->head;
		for (int i = 1; i < pos; i++) {
			pre = curr;
			curr = curr->next;
		}
		n->prev = pre;
		pre->next = n;
		n->next = curr;
		curr->prev = n;
	}

	size++;
	return 1;
}
int deleteLoan(LoanList* L, int pos) {
	if (!L || ListSize(*L) == 0) return 0;
	if (pos<1 || pos>ListSize(*L)) return 0;
	Nodelist* currnt = L->head;
	if (ListSize(*L) == 1) {
		L->head = nullptr;
		L->tail = nullptr;
	}
	else if (pos == 1) {
		L->head = L->head->next;
		L->head->prev = nullptr;
	}
	else if (pos == ListSize(*L)) {
		L->tail = L->tail->prev;
		L->tail->next = nullptr;
	}
	else {
		Nodelist* pre = nullptr;
		for (int i; i < pos; i++) {
			pre = currnt;
			currnt = currnt->next;
		}

		pre->next = currnt->next;
		currnt->next->prev = pre;
		delete currnt;
		int size = ListSize(*L);
		size--;
	}
	return 1;

}
loan getElement(const LoanList& L, int pos) {
	loan l = {};
	int size = ListSize(L);
	if (!&L || isEmpty(L)) return l;
	if (pos<1 || pos>size) return l;
	Nodelist* curr = L.head;
	for (int i = 1; i < pos; i++) {
		curr = curr->next;
	}
	return curr->data;
}

LoanList copyList(const LoanList& L) {
	if (!&L) {
		cout << "there is no list" << endl;
		return;
	}
	int size = ListSize(L);
	LoanList* L1 = new LoanList{};
	Nodelist* n = L.head;
	if (!n)return;
	for (int i = 1; i < size; i++) {
		addLoan(L1, n->data, i);
		n = n->next;
	}
	return *L1;
}
void displayLoan(const LoanList& L) {
	if (isEmpty(L)) {
		cout << "list is empty" << endl;
		return;
	}
	Nodelist* curr = L.head;
	while (curr) {
		cout << curr->data.ID << endl;
		cout << curr->data.type << endl;
		cout << curr->data.ReBalance << endl;
		cout << curr->data.LoanStatus << endl;
		curr = curr->next;
	}
	cout << "NULL\n";
}
bool compareLists(const LoanList& L1, const LoanList& L2) {
	int size1 = ListSize(L1);
	int size2 = ListSize(L2);
	if (size1 != size2)return false;
	Nodelist* curr1 = L1.head;
	Nodelist* curr2 = L2.head;
	while (curr1 != nullptr) {
		if (curr1 != curr2) {
			return false;
		}
		curr1 = curr1->next;
		curr2 = curr2->next;
	}
	return true;
}