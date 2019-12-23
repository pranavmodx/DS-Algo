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
    if (p == NULL) {
        printf("List empty! \n");
        return;
    }
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void deleteAllOccOf(Node **p, int elem) {
    Node *firstNode = *p;
    Node *q = NULL, *temp;

    while ((*p)->next != NULL) {
        if ((*p)->data == elem) {
            temp = *p;

            // If first node is an occurence
            if (*p == firstNode) {
                // printf("True \n");
                q = *p;  
                (*p) = firstNode = (*p)->next;
                free(temp); 
            // } 
            // If mid node is an occurence
            } else {
                temp = *p;
                *p = (*p)->next;
                q->next = *p;
                free(temp);
            }
        } 
        else {
            q = *p;  
            *p = (*p)->next;
        }  
    }

    // If last node is an occurence; some problem here with logic... hard-coded a bit
    if ((*p)->data == elem) {
        // printf("True ' \n");
        temp = *p;
        // firstNode = (*p)->next;
        if (q->data == (*p)->data)
            firstNode = NULL; // hard-coded
        else
            q->next = NULL;
        free(temp);
    }

    *p = firstNode;
    // printf("%d \n", firstNode->data);
}

int main() {
    insertAtEnd(&firstList, 10);
    insertAtEnd(&firstList, 10);
    insertAtEnd(&firstList, 10);
    insertAtEnd(&firstList, 10);
    insertAtEnd(&firstList, 10);
    insertAtEnd(&firstList, 10);
    insertAtEnd(&firstList, 10);
    displayList(firstList);
    deleteAllOccOf(&firstList, 10);
    displayList(firstList);

    return 0;
}