#include "pqueue.h"

void initPQ(PriorityQueue * pq, int (*func)(T,T)){
	pq->pos = -1;
	pq->size = 8;
	pq->queue = malloc(pq->size * sizeof(T));
	pq->compare = func;
}

int size(PriorityQueue * pq){
        return pq->pos + 1;
}

void resizePQ(PriorityQueue * pq){
	if(pq->pos + 1 < pq->size)
		return;
	
	pq->size *= 2;
	pq->queue = realloc(pq->queue, pq->size * sizeof(T));
}

void swapPQ(T* value1, T* value2){
	T temp = *value1; 
	*value1 = *value2;
	*value2 = temp;		
}

int parent(int child){
	return child / 2;
}

int leftChild(int parent){
	return 2 * parent + 1;
}

int rightChild(int parent){
	return 2 * parent + 2;
}

void push(PriorityQueue * pq, T value){
        resizePQ(pq);
        pq->queue[++pq->pos] = value;

        // percolate up
        int currPos = pq->pos;
        while(currPos != 0 && pq->compare(pq->queue[currPos], pq->queue[parent(currPos)])){
                swapPQ(&pq->queue[currPos], &pq->queue[parent(currPos)]);
                currPos = parent(currPos);
        }
}

T pop(PriorityQueue * pq){
        if(pq->pos == -1) return 0;

        // swap top of queue with last element
        swapPQ(&pq->queue[0], &pq->queue[pq->pos]);
        --pq->pos;

        // percolate element down from top
        int currPos = 0, down = 1, swapWith;
        while(currPos < pq->pos && (swapWith = leftChild(currPos)) <= pq->pos && down){ // each parent has at least left if it has children 
                down = 0;
                if(rightChild(currPos) <= pq->pos)
                        if (!pq->compare(pq->queue[leftChild(currPos)], pq->queue[rightChild(currPos)]))
                                swapWith = rightChild(currPos);
                
                if(pq->compare(pq->queue[swapWith], pq->queue[currPos])){
                        swapPQ(&pq->queue[swapWith], &pq->queue[currPos]);
                        currPos = swapWith;
                        down = 1;
                }
        }
        return pq->queue[pq->pos + 1];
}


void destructPQ(PriorityQueue * pq){
	free(pq->queue);
}
