/*Identify and store all unique elements with their frequency within file to be compressed

For each element, create a TN with frequency as the value. 
(May have to encode frequency and element as a hexadecimal or something like that because only one value)
Push each node into min pq (create appropriate comparator function)
Pop two nodes each time, create a new node whose value is the combined frequency of the two nodes.
	Make those two nodes the new node's children and insert the new node into the pq.


*/
#include "lib.h"
#include "tree.h"
#include "pqueue.h"
#include "bitbuf.h"

//-------------------------------------- Helpers --------------------------------------
int comparator(TN* node1, TN* node2){
	return node1->frequency < node2->frequency;
}

int myStrlen(const char * s, char stop){
	int count = 0;
	while(*s && *(s++) != stop) ++count;
	return count;
}

void changeExtension(char * buf, const char filename, int size){
	int pos = 0;
	while(pos < size)
		buf[pos] = filename[pos++];
	buf[pos++] = 'h';
	buf[pos++] = 'u';
	buf[pos++] = 'f';
	buf[pos] = 0;
}

TN * constructHuffmanTree(PriorityQueue * pq){
	TN * node1, * node2, * internal;
	
	while(size(&pq) > 1){
		node1 = pop(&pq);
		node2 = pop(&pq);

		internal = (TN *) Malloc(sizeof(TN));
		initTN(&internal, (char) -1, node1->frequency + node2->frequency);
		internal->left = node1;
		internal->right = node2;
		push(&pq, internal);
		// printf("%c:%d  ", node->val, node->frequency);
	}

	// pq should be empty after this
	return pop(&pq);
}

void getEncoding(char * encodings, TN * root, int leaves){
	// inorder dfs, pushing 0 or 1 depending on direction 
	// only need one bitbuffer
	BitBuffer bb;
	initBitBuffer(&bb);
	
	TN * s[leaves];
	int pos = 0, right = 0;

	while(root || pos){
		while(root){
			s[pos++] = root;
			root = root->left;
			if(right){
				writeBit(&bb, 1);
				right = 0;
			}
			else
				writeBit(&bb, 0);
		}

		root = s[--pos];
		// how do I know its a leaf?
		if(!root->right && !root->left){
			// write encoding
			encoding[root->val] = showBuffer(&bb);
		}
		popBit(&bb);
		root = root->right;
		right = 1;

	}

}

void reinterpretFile(const char * filename, FILE * toCompress, char * encodings){
	// concat filename and my compression file extension .huf
	int size = myStrlen(filename, '.');
	char buf [size + 4];
	changeExtension(buf, filename, size);
	FILE * compressedFile = fopen(buf, "w");

	// write to compressed file char by char as described 
	// by encoding. Just realized I need a decompression

	fclose(compressedFile);
}

void freeTree(TN * root, int leaves){
	// dfs to free all nodes in tree
	TN * s[leaves], * toFree; 
	int pos = 0;

	while(root || pos){
		while(root){
			s[pos++] = root;
			root = root->left;
		}

		toFree = s[--pos];
		root = toFree->right;
		free(toFree);
	}

}


//--------------------------------- Huffman Algorithm ---------------------------------
void huffman(const char * filename){
	// populate TN * [128] (because ASCII)
	int charFrequency [128], i;
	for(i = 0; i < 128; ++i){
		charFrequency[i] = 0;
	}
	
	// read file and update character frequency accordingly
	FILE * toCompress = Fopen(filename, "r");
	char c;
	while((c = fgetc(toCompress)) != EOF){
		++charFrequency[c];
	}
	
	// push into pq if frequency of a character is not 0
	PriorityQueue pq;
	TN * node;
	initPQ(&pq, comparator); 
	for(i = 0; i < 128; ++i){
		if(charFrequency[i]){
			node = (TN*) Malloc(sizeof(TN));
			initTN(node, (char) i, charFrequency[i]);
			push(&pq, node);	
		}
	}

	// ----------------------------------------------------------- Below not tested
	// save original amount of soon-to-be leaves of huffman tree
	int leaves = size(&pq);

	// construct Huffman Tree
	node = constructHuffmanTree(&pq);

	// get variable encoding of each leaf
	// in an array of 128 for O(1) lookup during reinterpretation
	// not initialized to 0 because only used chars should be queried
	char encodings [128];
	getEncoding(&encodings, node, leaves);

	// reinterpret file contents in new file
	fseek(toCompress, 0, SEEK_SET);
	reinterpretFile(filename, toCompress, encodings);

	fclose(toCompress);
	destructPQ(&pq);
	freeTree(node, leaves);
}

void main(int argc, char * argv[]){
	huffman(argv[1]);	
}
