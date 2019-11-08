#include "tree.h"

void initTN(TN * node, char c, int frequency){
	node->val = c;
	node->frequency = frequency;
	node->left = node->right = NULL;
}