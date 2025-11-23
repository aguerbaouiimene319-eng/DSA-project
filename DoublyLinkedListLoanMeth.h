
#include"loan.h"

Node* createNode(loan L);
void destroyNode(Node* loan);

LoanList createList();
void destroyList(LoanList* L);
void isEmpty(const LoanList& L);
int isFull(const LoanList& L);
int ListSize(const LoanList& L);

int insertAT(LoanList& L, loan l, int pos);
int getElement(const LoanList& L, int pos);
int deleteAT(LoanList& L, loan l, int pos);

void displayList(LoanList L);
void compareLists(LoanList& L1, LoanList& L2);

