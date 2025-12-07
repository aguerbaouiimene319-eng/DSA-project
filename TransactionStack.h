#ifndef TRANSACTIONSTACK_H
#define TRANSACTIONSTACK_H

#include<iostream>
#include "transaction.h"

struct Nodetrans {
	transaction data;
	Nodetrans* next;
};
struct stack {
	Nodetrans* top;
};
#endif