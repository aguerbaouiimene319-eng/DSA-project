#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include"customer.h"
#include"transaction.h"
#include"loan.h"
struct Node {
	loan data;
	Node* next;
	Node* prev;
};

struct LoanList {
	Node* head;
	Node* tail;
	int size;
};
#endif
