#ifndef LOANREQUESTMETH_H
#define LOANREQUESTMETH_H

#include "LoanRequest.h"
#include <iostream>
using namespace std;

LRNode* createLRNode(const LoanRequest& loan);
void destroyLRNode(LRNode* n);

queue* createQueue();
void destroyQueue(queue* q);

bool isEmpty(const queue& q);
bool isFull(const queue& q); // memory probe

int queueSize(const queue& q);
void displayQueue(const queue& q);

int Enqueue(queue* q, const LoanRequest& loan);
LoanRequest dequeue(queue* q);
LoanRequest frontElement(const queue& q);

queue* copyQueue(const queue& q);
bool compareQueues(const queue& q1, const queue& q2);

#endif