#include "src/pqueue.h"
#include <stdio.h>

int compare(T a, T b){
    return a > b;
}

int main(){
    PriorityQueue pq;
    initPQ(&pq, compare);

    int i = 0;
    while(i < 20)
        push(&pq, i++);

    printf("PQ size: %d\n", pq.size);    
    for(i = 0; i < 20; ++i)
        printf("%d ", pq.queue[i]);
    printf("\n");

    T item;
    while(pq.pos > -1){
        printf("Top element: %d\n", pq.queue[0]);
        
        item = pop(&pq);
        printf("%d\n\n", item);
    }

    destructPQ(&pq);
    return 0;
}