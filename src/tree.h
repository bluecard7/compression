#ifndef TREE
#define TREE

#include "lib.h"

//typedef char T;
typedef struct TN TN;
struct TN{
	char val;
	int frequency;
	TN * left;
	TN * right;
};

void initTN(TN*, char, int);
#endif