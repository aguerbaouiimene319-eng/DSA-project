#include<iostream>
#include"LoanRequestMeth.h"
using namespace std;
Node* createNode(LoanRequest loan) {
	Node* n = new (nothrow) Node{loan};
	if (!n) {
		cout << "memory allocation failed" << endl;
		return nullptr;
	}
	return n;
}
void destroyNode(Node* n) {
	delete n;
}
queue* createQueue() {
	queue* q = new queue{};
	if (!q) {
		cout << "memory allocation failed " << endl;
		return nullptr;
	}
	return q;
}
void destroyQueue(queue* q) {
	Node* n = q->front;
	while (n) {
		q->front = n->next;
		destroyNode(n);
		n = q->front;
	}
	delete q;
}

bool isEmpty(const queue& q) {
	return q.front == nullptr;
}
bool isFull(const queue& q) {
	Node* curr = createNode({});
	if (!curr) return true;
	return false;
}
int queueSize(const queue& q) {
	int size = 0;
	Node* temp = q.front;
	while (temp) {
		size++;
		temp = temp->next;
	}
}
void displayQueue(const queue& q) {
	Node* curr = q.front;
	while (curr) {
		cout << "loan request ID is" << curr->data.requestAccNumber << endl;
	}
}

int Enqueue(queue* q, LoanRequest loan) {
	if (isFull(*q)) return 0;
	Node* curr = createNode(loan);
	q->tail->next = curr;
	q->tail = curr;
	return 1;
}
LoanRequest dequeue(queue* q) {
	LoanRequest* n = nullptr;
	if (isEmpty(*q)) return *n;
	Node* curr = q->front;
	q->front = q->front->next;
	destroyNode(curr);
	return curr->data;
}
LoanRequest frontElement(const queue& q) {
	if (isEmpty(q))return {};
	return(q.front->data);
}
queue* copyQueue(const queue& q) {
	queue* newQ = createQueue();
	Node* curr = q.front;
	while (curr) {
		Enqueue(newQ, curr->data);
		curr = curr->next;
	}
}
bool compareQueues(const queue& q1, const queue& q2) {

}