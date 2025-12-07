#include "TransactionStackMeth.h"
#include <iostream>
using namespace std;

Nodetrans* CreateNodetrans(const transaction& data) {
    Nodetrans* n = new (nothrow) Nodetrans(data);
    if (!n) cout << "\nMemory allocation failed\n";
    return n;
}

void destroyTransNode(Nodetrans* n) {
    delete n;
}

stack* createStack() {
    stack* s = new (nothrow) stack();
    if (!s) cout << "\nMemory allocation failed\n";
    return s;
}

void destroyStack(stack* s) {
    if (!s) return;
    Nodetrans* curr = s->top;
    while (curr) {
        Nodetrans* next = curr->next;
        destroyTransNode(curr);
        curr = next;
    }
    delete s;
}

bool isEmptyTransaction(const stack& s) {
    return (s.top == nullptr);
}

bool isFull(const stack& s) {
    Nodetrans* n = new (nothrow) Nodetrans(transaction{});
    if (!n) return true;
    delete n;
    return false;
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
    if (isEmptyTransaction(s)) { cout << "No transactions in stack.\n"; return; }
    Nodetrans* n = s.top;
    while (n) {
        cout << "#" << n->data.ID << " | " << n->data.TransType
            << " | " << n->data.Amount << " TND | " << n->data.TransDate.stringDate() << "\n";
        n = n->next;
    }
}

int push(stack* s, const transaction& data) {
    if (!s) return 0;
    if (isFull(*s)) { cout << "Cannot push: out of memory\n"; return 0; }
    Nodetrans* n = CreateNodetrans(data);
    if (!n) return 0;
    n->next = s->top;
    s->top = n;
    return 1;
}

void pop(stack* s) {
    if (!s || isEmptyTransaction(*s)) return;
    Nodetrans* temp = s->top;
    s->top = temp->next;
    destroyTransNode(temp);
}

transaction peek(const stack& s) {
    if (isEmptyTransaction(s)) return transaction{};
    return s.top->data;
}

stack* copyStack(const stack& s) {
    // Copy preserving order: use temporary array of transactions
    int n = stackSize(s);
    transaction* arr = new transaction[n];
    Nodetrans* curr = s.top;
    int i = 0;
    while (curr) { arr[i++] = curr->data; curr = curr->next; }

    stack* copy = createStack();
    // push in reverse to keep same top-to-bottom order
    for (int j = n - 1; j >= 0; --j) push(copy, arr[j]);

    delete[] arr;
    return copy;
}

bool compareStack(const stack& s1, const stack& s2) {
    Nodetrans* c1 = s1.top;
    Nodetrans* c2 = s2.top;
    while (c1 && c2) {
        if (c1->data.ID != c2->data.ID) return false;
        c1 = c1->next; c2 = c2->next;
    }
    return c1 == nullptr && c2 == nullptr;
}