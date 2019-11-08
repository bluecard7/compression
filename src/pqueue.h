#include "lib.h"

#ifndef PRIORITYQUEUE 
#define PRIORITYQUEUE

// change this based on what type used
#include "tree.h"
typedef TN * T;
//typedef int T;

typedef struct{
        int size, pos;
        T * queue;
        int (*compare)(T,T);
} PriorityQueue;

void initPQ(PriorityQueue*, int (*)(T,T));
int size(PriorityQueue *);
void resizePQ(PriorityQueue*);
void swapPQ(T*, T*);
int parent(int);
int leftChild(int);
int rightChild(int);
void push(PriorityQueue*, T);
T pop(PriorityQueue*);
void destructPQ(PriorityQueue*);

#endif