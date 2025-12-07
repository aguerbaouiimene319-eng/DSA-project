#include "CompletedLoanListMeth.h"
#include <new>
#include <iostream>
using namespace std;

NodeCompLoan* createLoanNode(const loan& value) {
    NodeCompLoan* n = new (nothrow) NodeCompLoan(value);
    if (!n) return nullptr;
    return n;
}

void destroyLoanNode(NodeCompLoan* n) {
    delete n;
}

CompList* createCompList() {
    CompList* L = new (nothrow) CompList();
    return L;
}

void destroyCompList(CompList* s) {
    if (!s) return;
    NodeCompLoan* curr = s->head;
    while (curr) {
        NodeCompLoan* temp = curr->next;
        destroyLoanNode(curr);
        curr = temp;
    }
    delete s;
}

void addCompLoan(CompList* L, const loan& l) {
    if (!L) return;
    NodeCompLoan* newNode = createLoanNode(l);
    if (!newNode) return;
    newNode->next = L->head;
    L->head = newNode;
}

void displayCompList(const CompList& L) {
    NodeCompLoan* curr = L.head;
    if (!curr) {
        cout << "No completed loans in archive\n";
        return;
    }
    cout << "Archived completed loans:\n";
    while (curr) {
        cout << "ID:" << curr->data.ID
            << ", Type: " << curr->data.type
            << ", Amount: " << curr->data.amount << " TND"
            << ", End: " << curr->data.EndDate.stringDate() << "\n";
        curr = curr->next;
    }
    cout << "___________________________________\n";
}