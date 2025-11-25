
#include"loan.h"

Node* createNode(loan L);
void destroyNode(Node* loan);

LoanList createList();
void destroyList(LoanList* L);

bool isEmpty(const LoanList& L);
bool isFull(const LoanList& L);
int ListSize(const LoanList& L);

int insertAT(LoanList* L, loan l, int pos);
int deleteAT(LoanList* L, int pos);
loan getElement(const LoanList& L, int pos);
LoanList copyList(const LoanList& L);
void displayList(LoanList L);
void compareLists(LoanList& L1, LoanList& L2);

