/* Suppose FIRST and SECOND are sorted singly linked lists with 
    distinct elements. Write an algorithm and program which combines
    the lists into a single sorted linked list by changing the pointers. */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

typedef struct Node Node;

void displayList(Node *p);
void createListByArr(Node **p, int arr[], int n);
void mergeLists(Node *first, Node *second, Node **third);

int main() {
    Node *first = NULL, *second = NULL, *third = NULL;

    int n1, n2;
    printf("Enter size of first linked list : ");
    scanf("%d", &n1);

    int arr1[n1];

    printf("Enter all elements (in sorted order): ");
    int i;
    for (i=0; i<n1; i++) {
        scanf("%d", &arr1[i]);
    }

    printf("Enter size of second linked list : ");
    scanf("%d", &n2);

    int arr2[n2];

    printf("Enter all elements (in sorted order): ");
    for (i=0; i<n2; i++) {
        scanf("%d", &arr2[i]);
    }

    createListByArr(&first, arr1, n1);
    createListByArr(&second, arr2, n2);

    printf("\nFirst linked list : ");
    displayList(first);
    printf("\nSecond linked list : ");
    displayList(second);
    mergeLists(first, second, &third);
    printf("\nMerged linked list : ");
    displayList(third);

    return 0;
}


void createListByArr(Node **p, int arr[], int n) {
    Node *t;
    t = (Node*) malloc(sizeof(Node));
    t->data = arr[0];
    t->next = NULL;
    
    *p = t;
    Node *trav = *p;
    
    int i;
    for (i=1; i<n; i++) {
        t = (Node*) malloc(sizeof(Node));
        t->data = arr[i];
        t->next = NULL;
        trav->next = t;
        trav = t;
    }
}

void displayList(Node *p) {
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void mergeLists(Node *first, Node *second, Node **third) {
    *third = (Node*) malloc(sizeof(Node));
    (*third)->data = -1;
    (*third)->next = NULL;

    Node *t = *third;
    while (first != NULL && second != NULL) {
        if (first->data < second->data) {
            t->next = first;
            first = first->next;
        }
        else {
            t->next = second;
            second = second->next;
        }
        t = t->next;
    }
    if (first == NULL)
        t->next = second;
    else 
        t->next = first;  

    *third = (*third)->next;
}