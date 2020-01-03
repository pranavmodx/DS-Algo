#include <stdio.h>
#include <stdlib.h>


struct TNode {
    int data;
    struct TNode *leftChild;
    struct TNode *rightChild;
};

typedef struct TNode TNode;

struct SNode {
    TNode *tNode;
    struct SNode *next; 
} *stack = NULL;

typedef struct SNode SNode;


// Stack functions
SNode* createStackNode(TNode *t);
void pushToStack(SNode **top, TNode *t);
TNode* popFromStack(SNode **top);
TNode* peekOnStack(SNode *top);
int isEmptyStack(SNode *top);


// Tree create/insert functions
TNode* createTreeNode(int elem);
void insertTreeNode(TNode *root, int elem);

// Tree delete functions
TNode* deleteTreeNode(TNode *root, int elem);

// Tree display functions
void inOrderDisplay(TNode *root);
void preOrderDisplay(TNode *root);
void postOrderDisplay(TNode *root);

// Tree recursive display functions
void inOrderRecDisplay(TNode *root);
void preOrderRecDisplay(TNode *root);
void postOrderRecDisplay(TNode *root);

// Tree min/max elements
TNode* minElement(TNode *root);
TNode* maxElement(TNode *root);

int main() {
    TNode *bst = NULL;
    bst = createTreeNode(50);

    insertTreeNode(bst, 30); 
    insertTreeNode(bst, 20); 
    insertTreeNode(bst, 40);
    insertTreeNode(bst, 70);
    insertTreeNode(bst, 60);
    insertTreeNode(bst, 80);
    
    inOrderDisplay(bst);
    deleteTreeNode(bst, 40);
    inOrderDisplay(bst);

    maxElement(bst);
    minElement(bst);

    // preOrderDisplay(bst);
    // postOrderDisplay(bst);

    // inOrderRecDisplay(bst);
    // printf("\n");
    
    // preOrderRecDisplay(bst); 
    // printf("\n");
    // postOrderRecDisplay(bst);
    // printf("\n");

    return 0;
}


TNode* createTreeNode(int elem) {
    TNode *t = malloc(sizeof(TNode));
    t->data = elem;
    t->leftChild = NULL;
    t->rightChild = NULL;

    return t;
}

void insertTreeNode(TNode *root, int elem) {
    if (root == NULL) {
        root = createTreeNode(elem);
        return;
    } 

    while (root != NULL) {
        if (elem < root->data) {
            if (root->leftChild == NULL) {
                root->leftChild = createTreeNode(elem);
                break; // Important! I forgot break for infinite while
            }
            else 
                root = root->leftChild;
        }
        else if (elem > root->data) {
            if (root->rightChild == NULL) {
                root->rightChild = createTreeNode(elem);
                break;
            }
            else 
                root = root->rightChild;
        } 
        else
            break;     
    }
}

TNode* deleteTreeNode(TNode *root, int elem) {
    if (root == NULL) 
        return root;

    if (elem < root->data)
        root->leftChild = deleteTreeNode(root->leftChild, elem);

    else if (elem > root->data)
        root->rightChild = deleteTreeNode(root->rightChild, elem);

    else {
        if (root->leftChild == NULL) {
            TNode *temp = root->rightChild;
            free(root);
            return temp;
        }
        else if (root->rightChild == NULL) {
            TNode *temp = root->leftChild;
            free(root);
            return temp;
        }
        
        TNode *temp = minElement(root->rightChild);
        root->data = temp->data;
        root->rightChild = deleteTreeNode(root->rightChild, elem);
    }

    return root;
}

void inOrderDisplay(TNode *currentNode) {
    if (currentNode == NULL) 
        return;

    while (1) {
        if (currentNode != NULL) {
            pushToStack(&stack, currentNode);
            currentNode = currentNode->leftChild;
        }
        else {
            if (!isEmptyStack(stack)) {
                currentNode = popFromStack(&stack);
                printf("%d ", currentNode->data);
                currentNode = currentNode->rightChild;
            }
            else 
                break;
        }
    }

    printf("\n");
}

void preOrderDisplay(TNode *currentNode) {
    if (currentNode == NULL)
        return;

    pushToStack(&stack, currentNode);
    
    while (!isEmptyStack(stack)) {
        currentNode = popFromStack(&stack);   
        printf("%d ", currentNode->data);

        if (currentNode->rightChild)
            pushToStack(&stack, currentNode->rightChild);
        if (currentNode->leftChild) 
            pushToStack(&stack, currentNode->leftChild);
    }

    printf("\n");
}

void postOrderDisplay(TNode *currentNode) {
    if (currentNode == NULL)
        return;
    
    do {
        while (currentNode != NULL) {
            if (currentNode->rightChild)
                pushToStack(&stack, currentNode->rightChild);
            pushToStack(&stack, currentNode);

            currentNode = currentNode->leftChild;
        }

        currentNode = popFromStack(&stack);

        if (currentNode->rightChild && currentNode->rightChild == peekOnStack(stack)) {
            popFromStack(&stack);
            pushToStack(&stack, currentNode);
            currentNode = currentNode->rightChild;
        }
        else {
            printf("%d ", currentNode->data);
            currentNode = NULL;
        }


    } while (!isEmptyStack(stack));

    printf("\n");
}

void inOrderRecDisplay(TNode *root) {
    if (root == NULL) 
        return;
    
    inOrderRecDisplay(root->leftChild);
    printf("%d ", root->data);
    inOrderRecDisplay(root->rightChild);
}

void preOrderRecDisplay(TNode *root) {
    if (root == NULL)
        return;

    printf("%d ", root->data);
    inOrderRecDisplay(root->leftChild);
    inOrderRecDisplay(root->rightChild);
}

void postOrderRecDisplay(TNode *root) {
    if (root == NULL)   
        return;

    postOrderRecDisplay(root->leftChild);
    postOrderRecDisplay(root->rightChild);
    printf("%d ", root->data);
}

TNode* maxElement(TNode *root) {
    while (root->rightChild != NULL) {
        root = root->rightChild;
    }

    return root;
    // printf("%d \n", root->data);
}

TNode* minElement(TNode *root) {
    while (root->leftChild != NULL) {
        root = root->leftChild;
    }

    return root;
    // printf("%d \n", root->data);
}


SNode* createStackNode(TNode *t) {
    SNode *s = malloc(sizeof(SNode));
    s->tNode = t;
    s->next = NULL;

    return s;
}

void pushToStack(SNode **top, TNode *t) {
    if (*top == NULL) {
        *top = createStackNode(t);
        return;
    } 

    SNode *newStackNode = createStackNode(t);
    newStackNode->next = *top;

    *top = newStackNode;
}

TNode* popFromStack(SNode **top) {
    if (*top == NULL)
        return NULL;
    
    TNode *tNode = (*top)->tNode;

    SNode *temp = *top;
    *top = (*top)->next;
    free(temp);

    return tNode;
}

TNode* peekOnStack(SNode *top) {
    if (top != NULL)
        return top->tNode;
    else
        return NULL;
}

int isEmptyStack(SNode *top) {
    return top == NULL ? 1 : 0;
}