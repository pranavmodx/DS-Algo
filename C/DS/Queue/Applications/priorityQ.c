// Write an algorithm and program to create a priority queue using linked list. 
// Store element and priority value. Assume square root of entered number as its
// priority value. Insert and delete the elements.

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int elem;
    int priority;
    struct Node *next;
} *front = NULL, *rear = NULL;

typedef struct Node Node;

void insertElem(int elem, int priority);
Node* getHighestPriorityElem(Node *p);
int deleteHighestPriorityElem(Node *p);
void displayQueue(Node *p);

int main() {
    insertElem(10, 2);
    insertElem(20, 1);
    insertElem(30, 3);
    insertElem(40, 7);
    insertElem(50, 8);
    insertElem(60, 0);
    displayQueue(front);
    deleteHighestPriorityElem(front);
    displayQueue(front);
    deleteHighestPriorityElem(front);
    displayQueue(front);
    deleteHighestPriorityElem(front);
    displayQueue(front);

    return 0;
}

void insertElem(int elem, int priority) {
    if (front == NULL) {
        front = malloc(sizeof(Node));
        front->elem = elem;
        front->priority = priority; 
        front->next= NULL;
        rear = front;
        return;
    }

    Node *t = malloc(sizeof(Node));
    t->elem = elem;
    t->priority = priority; 
    t->next= NULL;

    rear->next = t;
    rear = t;
}

Node* getHighestPriorityElem(Node *p) {
    Node *max = front;

    while (p != NULL) {
        if (p->priority > max->priority)
            max = p;
        p = p->next;
    }

    return max;
}


int deleteHighestPriorityElem(Node *p) {
    Node *highest = getHighestPriorityElem(front);
    int elem;
    Node *t;

    if (highest == front) {
        t = highest;
        front = front->next;
        elem = t->elem;

        free(t);

        return elem;
    }

    while (p->next != highest) 
        p = p->next;
    
    t = p->next;
    p->next = p->next->next;

    elem = t->elem;
    free(t);

    return elem;
}

void displayQueue(Node *p) {
    while (p != NULL) {
        printf("%d ", p->elem);
        p = p->next;
    }
    printf("\n");
}