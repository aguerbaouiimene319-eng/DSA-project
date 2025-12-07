
#include "TransactionStackMeth.h"
#include<iostream>
#include<string>
using namespace std;

Nodetrans* CreateNodetrans(transaction data) {
	Nodetrans* n = new (nothrow) Nodetrans{data};
	if (!n) {
		cout << "\nMemory allocation failed\n";
	}
	return n;
}
void destroyNode(Nodetrans* n) {
	delete n;
}
stack* createStack() {
	stack* newstack = new (nothrow) stack{};
	if (!newstack) {
		cout << "\nMemmory allocation failed\n";
	}
	else {
		newstack->top = nullptr;
	}
	return newstack;
}
void destroyStack(stack* s) {
	if (!s) return;
	delete s;
}

bool isEmptyTransaction(const stack& s) {
	return (s.top == nullptr);
}
bool isFull(const stack& s) {
	stack* newStack = createStack();
	if (!newStack) return true;
	else {
		destroyStack(newStack);
	}
}
int stackSize(const stack& s) {
	int size = 0;
	Nodetrans* n = s.top;
	while (n) {
		size++;
		n = n->next;
	}
	return size;
}
void displaystack(const stack& s) {
	if (isEmptyTransaction(s))return;
	Nodetrans* n = s.top;
	while (n != nullptr) {
		cout <<"stack id is "<< n->data.AccountNum << " ";
		n=n->next;
	}
	cout << endl;
}

int push(stack* s, transaction data) {
	if (isFull(*s)) {
		cout << "can not add to the stack" << endl;
		return 0;
	}
	Nodetrans* n = CreateNodetrans(data);
	if (isEmptyTransaction(*s)) {
		s->top = n;
	}
	else {
		n->next = s->top;
		s->top = n;
	}
	return 1;
}
void pop(stack* s) {
	if (isEmptyTransaction(*s))return;
	else {
		Nodetrans* temp = s->top;
		transaction e = temp->data;
		s->top = temp->next;
		destroyNode(temp);
	}
}
transaction peek(const stack& s) {
	if (isEmptyTransaction(s))return transaction{};
	else {
		return s.top->data;
	}
}

stack* copyStack(const stack& s) {
	stack* s1 = createStack();
	if (isEmptyTransaction(s)) return s1;
	Nodetrans* curr = s.top;
	Nodetrans* newNode = s1->top;
	Nodetrans* lastNew = nullptr;
	while (curr) {
		newNode = CreateNodetrans(curr->data);
		if (curr = s.top) {
			s1->top = newNode;
			lastNew = newNode = nullptr;
		}
		else {
			lastNew->next = newNode;
			lastNew = newNode;
		}
		curr = curr->next;
	}
	return s1;
}

bool compareStack(const stack& s1, const stack& s2) {
	if (stackSize(s1) != stackSize(s2)) return false;
	Nodetrans* curr1 = s1.top;
	Nodetrans* curr2 = s2.top;
	while (curr1 != nullptr) {
		if (curr1->data.ID != curr2->data.ID) {
			return false;
		}
		curr1 = curr1->next;
		curr2 = curr2->next;
	}
	return true;
}
