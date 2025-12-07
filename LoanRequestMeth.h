#ifndef LOANREQUESTMETH_H
#define LOANREQUESTMETH_H

#include "LoanRequest.h"
#include <string>
#include <iostream>
using namespace std;

Node* createNode(LoanRequest loan);
void destroyNode(Node* n);
queue* createQueue();
void destroyQueue(queue* q);

bool isEmpty(const queue& q);
bool isFull(const queue& q);
int queueSize(const queue& q);
void displayQueue(const queue& q);

int Enqueue(queue* q, LoanRequest loan);
LoanRequest dequeue(queue* q);
LoanRequest frontElement(const queue& q);
queue* copyQueue(const queue& q);
bool compareQueues(const queue& q1, const queue& q2);

#endif