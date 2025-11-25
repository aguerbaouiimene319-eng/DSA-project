
#include<iostream>
#include "StackContigMeth.h"

stack* createStack() {
	stack* newstack = new stack{};
	if (!newstack) {
		cerr << "\nMemmory allocation failed\n";
		return nullptr;
	}
	newstack->top = -1;
	return newstack;
}
void destroyStack(stack* s) {
	if (!s) return;
	delete s;
}

bool isEmpty(const stack& s) {
	return s.top == -1;
}
bool isFull(const stack& s) {
	return s.top == 99;
}
int stackSize(const stack& s) {
	if (isEmpty(s)) return 0;
	if (isFull(s)) return s.top;
	return s.top + 1;
}
void displaystack(const stack& s) {
	if (isEmpty(s))return;
	for (int i = s.top; i >= 0; i--) {
		cout << s.arr[i] << " ";
	}
	cout << endl;
}

int push(stack s, int e) {
	if (isFull(s)) {
		cout << "can not add to the stack" << endl;
		return 0;
	}
	s.top++;
	s.arr[s.top] = e;
	return 1;
}
int pop(stack s) {
	if (isEmpty(s))return 0;
	int x = s.arr[s.top];
	s.top--;
	return x;
}
int top(const stack& s) {
	if (isEmpty(s))return 0;
	return s.arr[s.top];
}

stack* copyStack(const stack& s) {
	if (isEmpty(s)) return nullptr;
	stack* s1 = createStack();
	s1->top = s.top;
	for (int i = 0; i <= s.top; i++) {
		s1->arr[i] = s.arr[i];
	}
	return s1;
}
bool compareStack(const stack& s1, const stack& s2) {
	if (stackSize(s1) != stackSize(s2)) return false;
	int i = 0;
	while ((s1.arr[i] == s2.arr[i]) && i < stackSize(s1) + 1) {
		i++;
	}
	return i == stackSize(s1) + 1;
}