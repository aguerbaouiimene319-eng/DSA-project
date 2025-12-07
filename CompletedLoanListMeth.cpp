
#include"CompletedLoanListMeth.h"
#include<new>
#include<iostream>

NodeCompLoan* createLoanNode(loan value) {
	NodeCompLoan* n = new (nothrow) NodeCompLoan {value,nullptr};
	if (!n)return nullptr;
	return n;
}
void destroyLoanNode(NodeCompLoan*n) {
	delete n;
}
CompList* createCompList() {
	CompList* L = new (nothrow) CompList {nullptr};
	return L;
}
void destroyList(CompList* s) {
	NodeCompLoan* curr = s->head;
	while (curr) {
		NodeCompLoan* temp = curr->next;
		destroyLoanNode(curr);
		curr = temp;
	}
	delete s;
}

void addCompLoan(CompList* L, loan l) {
	NodeCompLoan* newNode = createLoanNode(l);
	newNode->data = l;
	newNode->next = L->head;
	L->head = newNode;
}

void displayCompList(const CompList& L){
	NodeCompLoan* curr = L.head;
	if (curr == nullptr) {
		cout << "no completed loans in archive" << endl;
		return;
	}
	cout << "archived completed loans " << endl;
	while (curr) {
		cout << "ID:" << curr->data.ID
			<< ", type: " << curr->data.type
			<< " amount: " << curr->data.amount << " TND "
			<< "end date: " << curr->data.EndDate.day << curr->data.EndDate.month << curr->data.EndDate.year << endl;
		curr = curr->next;
	}
	cout << "___________________________________" << endl;
}
// need the singly linked list to be sent all of it