#include "LoanListMeth.h"
#include <iostream>
using namespace std;

Nodelist* createloan(const loan& data) {
    Nodelist* n = new (nothrow) Nodelist();
    if (!n) {
        cerr << "\nMemory allocation failed for new loan\n";
        return nullptr;
    }
    n->data = data;
    n->next = nullptr;
    n->prev = nullptr;
    return n;
}

void destroyLoanNode(Nodelist* n) {
    delete n;
}

LoanList* createList() {
    LoanList* L = new LoanList();
    return L;
}

void destroyList(LoanList* L) {
    if (!L) return;
    Nodelist* current = L->head;
    while (current) {
        Nodelist* temp = current->next;
        delete current;
        current = temp;
    }
    L->head = nullptr;
    L->tail = nullptr;
}

bool isEmpty(const LoanList& L) {
    return L.head == nullptr;
}

bool isFull(const LoanList& L) {
    Nodelist* n = new (nothrow) Nodelist();
    if (!n) return true;
    delete n;
    return false;
}

int ListSize(const LoanList& L) {
    if (isEmpty(L)) return 0;
    int size = 0;
    Nodelist* n = L.head;
    while (n) {
        size++;
        n = n->next;
    }
    return size;
}

int addLoan(LoanList* L, const loan& l, int pos) {
    if (!L) return 0;
    int size = ListSize(*L);
    if (pos < 1 || pos > size + 1) {
        cerr << "\nCannot insert at position " << pos << "\n";
        return 0;
    }
    Nodelist* n = createloan(l);
    if (!n) return 0;

    if (isEmpty(*L)) {
        L->head = L->tail = n;
    }
    else if (pos == 1) {
        n->next = L->head;
        L->head->prev = n;
        L->head = n;
    }
    else if (pos == size + 1) {
        n->prev = L->tail;
        L->tail->next = n;
        L->tail = n;
    }
    else {
        Nodelist* curr = L->head;
        for (int i = 1; i < pos; ++i) curr = curr->next;
        Nodelist* pre = curr->prev;
        n->prev = pre;
        n->next = curr;
        pre->next = n;
        curr->prev = n;
    }
    return 1;
}

int deleteLoan(LoanList* L, int pos) {
    if (!L) return 0;
    int size = ListSize(*L);
    if (size == 0 || pos < 1 || pos > size) return 0;

    Nodelist* curr = L->head;
    for (int i = 1; i < pos; ++i) curr = curr->next;

    if (curr == L->head && curr == L->tail) {
        L->head = L->tail = nullptr;
    }
    else if (curr == L->head) {
        L->head = curr->next;
        L->head->prev = nullptr;
    }
    else if (curr == L->tail) {
        L->tail = curr->prev;
        L->tail->next = nullptr;
    }
    else {
        Nodelist* pre = curr->prev;
        Nodelist* nxt = curr->next;
        pre->next = nxt;
        nxt->prev = pre;
    }
    destroyLoanNode(curr);
    return 1;
}

loan getElement(const LoanList& L, int pos) {
    loan l{};
    int size = ListSize(L);
    if (isEmpty(L) || pos < 1 || pos > size) return l;
    Nodelist* curr = L.head;
    for (int i = 1; i < pos; ++i) curr = curr->next;
    return curr->data;
}

LoanList copyList(const LoanList& L) {
    LoanList result;
    Nodelist* curr = L.head;
    int pos = 1;
    while (curr) {
        addLoan(&result, curr->data, pos);
        curr = curr->next;
        pos++;
    }
    return result;
}

void displayLoan(const LoanList& L) {
    if (isEmpty(L)) {
        cout << "No loans.\n";
        return;
    }
    Nodelist* curr = L.head;
    while (curr) {
        cout << "ID: " << curr->data.ID << " | Type: " << curr->data.type
            << " | Remaining: " << curr->data.ReBalance
            << " | Status: " << curr->data.LoanStatus << "\n";
        curr = curr->next;
    }
}

loan* findloan(LoanList* l, int loanId) {
    if (!l) return nullptr;
    Nodelist* curr = l->head;
    while (curr) {
        if (curr->data.ID == loanId) return &curr->data;
        curr = curr->next;
    }
    return nullptr;
}