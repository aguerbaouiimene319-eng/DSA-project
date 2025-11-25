#include"DoublyLinkedListLoanMeth.h"
#include<iostream>
using namespace std;


Node* createNode(loan data) {
	Node* n = new (nothrow) Node{ data,nullptr,nullptr };
	if (!n)
		cerr << "\nMemory allocation failed for new loan\n";
	return n;
}
void destroyNode(Node* loan) {
	delete loan;
}

LoanList createList() {
	LoanList*L = new LoanList{ nullptr,nullptr,0 };
	return *L;
}
void destroyList(LoanList* L) {
	if (!L)return;
	Node* currnt=L->head;
	while(currnt) {
		Node*temp = currnt;
		currnt = currnt->next;
		delete temp;
	}
	L->head = nullptr;
	L->tail = nullptr;
	L->size = 0;
}

bool isEmpty(const LoanList& L) {
	return L.size == 0;
}
bool isFull(const LoanList& L) {
	Node* n = new (nothrow)Node;
	if (!n) return true;
	delete n;
	return false;
}
int ListSize(const LoanList& L) {
	return L.size;
}

int insertAT(LoanList* L, loan l, int pos) {
	if (!L) return 0;
	if (pos<1 || pos> L->size + 1) {
		cerr << "\nCan not insert in these positions\n";
		return 0;
	}
	Node* n = new (nothrow) Node{};
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
	else if (pos = L->size + 1) {
		L->tail->next = n;
		n->prev = L->tail;
		L->tail = n;
	}
	else {
		Node* pre = nullptr;
		Node* curr = L->head;
		for (int i = 1; i < pos; i++) {
			pre = curr;
			curr = curr->next;
		}
		n->prev = pre;
		pre->next = n;
		n->next = curr;
		curr->prev = n;
	}
	L->size++;
	return 1;
}
int deleteAT(LoanList* L, int pos) {
	if (!L || L->size == 0) return 0;
	if (pos<1 || pos>L->size) return 0;
	Node* currnt = L->head;
	if (L->size == 1) {
		L->head = nullptr;
		L->tail = nullptr;
	}
	else if (pos == 1) {
		L->head = L->head->next;
		L->head->prev = nullptr;
	}
	else if (pos == L->size) {
		L->tail = L->tail->prev;
		L->tail->next = nullptr;
	}
	else {
		Node* pre=nullptr;
		for (int i; i < pos; i++) {
			pre = currnt;
			currnt = currnt->next;			
		}
		
		pre->next = currnt->next;
		currnt->next->prev = pre;
		delete currnt;
		L->size--;
	}
	return 1;

}
loan getElement(const LoanList& L, int pos) {
	if (!&L || isEmpty(L)) return ;
	if (pos<1 || pos>L.size) return ;
	Node* curr = L.head;
	for (int i = 1; i < pos; i++) {
		curr = curr->next;
	}
	return curr->data;
}

LoanList copyList(const LoanList& L) {
	if(!&L){
		cout << "there is no list" << endl;
		return;
	}
	LoanList* L1 = new LoanList{ nullptr,nullptr,0 };
	Node* n = L.head;
	if (!n)return;
	for (int i = 1; i < L.size; i++) {
		insertAT(L1, n->data, i);
		n = n->next;
	}
	L1->size = L.size;
	return *L1;
}
void displayList(LoanList L) {
	if (!&L) return;
	if (isEmpty(L)) {
		cout << "list is empty" << endl;
		return;
	}
	Node* curr = L.head;
	while (curr) {
		cout << curr->data << endl;
		curr = curr->next;
	}
	cout << "NULL\n";
}
void compareLists(const LoanList& L1, const LoanList& L2) {


}
