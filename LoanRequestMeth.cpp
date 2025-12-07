#include "LoanRequestMeth.h"
#include <iostream>
using namespace std;

LRNode* createLRNode(const LoanRequest& loan) {
    LRNode* n = new (nothrow) LRNode(loan);
    if (!n) {
        cout << "Memory allocation failed\n";
        return nullptr;
    }
    return n;
}

void destroyLRNode(LRNode* n) {
    delete n;
}

queue* createQueue() {
    queue* q = new (nothrow) queue();
    if (!q) {
        cout << "Memory allocation failed\n";
        return nullptr;
    }
    // front and tail already nullptr via constructor
    return q;
}

void destroyQueue(queue* q) {
    if (!q) return;
    LRNode* n = q->front;
    while (n) {
        LRNode* next = n->next;
        destroyLRNode(n);
        n = next;
    }
    delete q;
}

bool isEmpty(const queue& q) {
    return q.front == nullptr;
}

bool isFull(const queue& q) {
    LRNode* test = new (nothrow) LRNode(LoanRequest{});
    if (!test) return true;
    delete test;
    return false;
}

int queueSize(const queue& q) {
    int size = 0;
    LRNode* temp = q.front;
    while (temp) { size++; temp = temp->next; }
    return size;
}

void displayQueue(const queue& q) {
    LRNode* curr = q.front;
    while (curr) {
        cout << "Req for Acc#" << curr->data.requestAccNumber
            << " | Type: " << curr->data.loanType
            << " | Amount: " << curr->data.PrincipleAmount
            << " | ReqDate: " << curr->data.RequestDate.stringDate() << "\n";
        curr = curr->next;
    }
}

int Enqueue(queue* q, const LoanRequest& loan) {
    if (!q) return 0;
    if (isFull(*q)) return 0;
    LRNode* curr = createLRNode(loan);
    if (!curr) return 0;

    if (isEmpty(*q)) {
        q->front = q->tail = curr;
    }
    else {
        q->tail->next = curr;
        q->tail = curr;
    }
    return 1;
}

LoanRequest dequeue(queue* q) {
    LoanRequest empty{};
    if (!q || isEmpty(*q)) return empty;

    LRNode* curr = q->front;
    LoanRequest data = curr->data;
    q->front = q->front->next;
    if (q->front == nullptr) q->tail = nullptr;
    destroyLRNode(curr);

    return data;
}

LoanRequest frontElement(const queue& q) {
    if (isEmpty(q)) return LoanRequest{};
    return q.front->data;
}

queue* copyQueue(const queue& q) {
    queue* newQ = createQueue();
    LRNode* curr = q.front;
    while (curr) {
        Enqueue(newQ, curr->data);
        curr = curr->next;
    }
    return newQ;
}

bool compareQueues(const queue& q1, const queue& q2) {
    LRNode* c1 = q1.front;
    LRNode* c2 = q2.front;
    while (c1 && c2) {
        if (c1->data.requestAccNumber != c2->data.requestAccNumber) return false;
        c1 = c1->next; c2 = c2->next;
    }
    return c1 == nullptr && c2 == nullptr;
}