#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
} *firstList = NULL;  

typedef struct Node Node;

void insertAtEnd(Node **p, int elem) {
    Node *firstNode = NULL;

    if (*p == NULL) {
        *p = (Node*) malloc(sizeof(Node));
        (*p)->data = elem;
        (*p)->next = NULL;
        firstNode = *p;
    } else {
        firstNode = *p;
        while ((*p)->next != NULL)
            *p = (*p)->next;

        Node *newNode = (Node*) malloc(sizeof(Node));
        newNode->data = elem;
        newNode->next = NULL;

        (*p)->next = newNode;
    }

    *p = firstNode;
}

void displayList(Node *p) {
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

Node* delRepElem(Node *p) {
    Node *t = p, *q, *temp;
    q = p;
    p = p->next;

    while (p != NULL) {
        if (p == q) {
            temp = p;
            q->next = p->next;
            free(temp);
        }
        q = p;
        p = p->next;
    }
    return t;
}

int main() {
    insertAtEnd(&firstList, 20);
    insertAtEnd(&firstList, 10);
    insertAtEnd(&firstList, 10);
    insertAtEnd(&firstList, 40);
    insertAtEnd(&firstList, 50);
    displayList(firstList);
    firstList = delRepElem(firstList);
    displayList(firstList);

    return 0;
}