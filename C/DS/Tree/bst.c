#include <stdio.h>
#include <stdlib.h>


struct TNode {
    int data;
    struct TNode *lChild;
    struct TNode *rChild;
};

typedef struct TNode TNode;

struct SNode {
    TNode *tNode;
    struct SNode *next; 
} *stack = NULL;

typedef struct SNode SNode;


// Stack functions
SNode* createSNode(TNode *t);
void push(SNode **top, TNode *t);
TNode* pop(SNode **top);
TNode* peek(SNode *top);
int isEmptyS(SNode *top);


// Tree create/insert functions
TNode* createTNode(int elem);
void insTNode(TNode *root, int elem);

// Tree delete functions
TNode* delTNode(TNode *root, int elem);

// Tree display functions
void inOrder(TNode *root);
void preOrder(TNode *root);
void postOrder(TNode *root);

// Tree recursive display functions
void inOrderRec(TNode *root);
void preOrderRec(TNode *root);
void postOrderRec(TNode *root);

// Tree min/max elements
TNode* minElem(TNode *root);
TNode* maxElem(TNode *root);

int main() {
    TNode *bst = NULL;
    bst = createTNode(50);

    insTNode(bst, 30); 
    insTNode(bst, 20); 
    insTNode(bst, 40);
    insTNode(bst, 70);
    insTNode(bst, 60);
    insTNode(bst, 80);
    
    inOrder(bst);
    delTNode(bst, 40);
    inOrder(bst);

    maxElem(bst);
    minElem(bst);

    // preOrder(bst);
    // postOrder(bst);

    // inOrderRec(bst);
    // printf("\n");
    
    // preOrderRec(bst); 
    // printf("\n");
    // postOrderRec(bst);
    // printf("\n");

    return 0;
}


TNode* createTNode(int elem) {
    TNode *t = malloc(sizeof(TNode));
    t->data = elem;
    t->lChild = NULL;
    t->rChild = NULL;

    return t;
}

void insTNode(TNode *root, int elem) {
    if (root == NULL) {
        root = createTNode(elem);
        return;
    } 

    while (root != NULL) {
        if (elem < root->data) {
            if (root->lChild == NULL) {
                root->lChild = createTNode(elem);
                break; // Important! I forgot break for infinite while
            }
            else 
                root = root->lChild;
        }
        else if (elem > root->data) {
            if (root->rChild == NULL) {
                root->rChild = createTNode(elem);
                break;
            }
            else 
                root = root->rChild;
        } 
        else
            break;     
    }
}

TNode* delTNode(TNode *root, int elem) {
    if (root == NULL) 
        return root;

    if (elem < root->data)
        root->lChild = delTNode(root->lChild, elem);

    else if (elem > root->data)
        root->rChild = delTNode(root->rChild, elem);

    else {
        if (root->lChild == NULL) {
            TNode *temp = root->rChild;
            free(root);
            return temp;
        }
        else if (root->rChild == NULL) {
            TNode *temp = root->lChild;
            free(root);
            return temp;
        }
        
        TNode *temp = minElem(root->rChild);
        root->data = temp->data;
        root->rChild = delTNode(root->rChild, elem);
    }

    return root;
}

void inOrder(TNode *currentNode) {
    if (currentNode == NULL) 
        return;

    while (1) {
        if (currentNode != NULL) {
            push(&stack, currentNode);
            currentNode = currentNode->lChild;
        }
        else {
            if (!isEmptyS(stack)) {
                currentNode = pop(&stack);
                printf("%d ", currentNode->data);
                currentNode = currentNode->rChild;
            }
            else 
                break;
        }
    }

    printf("\n");
}

void preOrder(TNode *currentNode) {
    if (currentNode == NULL)
        return;

    push(&stack, currentNode);
    
    while (!isEmptyS(stack)) {
        currentNode = pop(&stack);   
        printf("%d ", currentNode->data);

        if (currentNode->rChild)
            push(&stack, currentNode->rChild);
        if (currentNode->lChild) 
            push(&stack, currentNode->lChild);
    }

    printf("\n");
}

void postOrder(TNode *currentNode) {
    if (currentNode == NULL)
        return;
    
    do {
        while (currentNode != NULL) {
            if (currentNode->rChild)
                push(&stack, currentNode->rChild);
            push(&stack, currentNode);

            currentNode = currentNode->lChild;
        }

        currentNode = pop(&stack);

        if (currentNode->rChild && currentNode->rChild == peek(stack)) {
            pop(&stack);
            push(&stack, currentNode);
            currentNode = currentNode->rChild;
        }
        else {
            printf("%d ", currentNode->data);
            currentNode = NULL;
        }


    } while (!isEmptyS(stack));

    printf("\n");
}

void inOrderRec(TNode *root) {
    if (root == NULL) 
        return;
    
    inOrderRec(root->lChild);
    printf("%d ", root->data);
    inOrderRec(root->rChild);
}

void preOrderRec(TNode *root) {
    if (root == NULL)
        return;

    printf("%d ", root->data);
    inOrderRec(root->lChild);
    inOrderRec(root->rChild);
}

void postOrderRec(TNode *root) {
    if (root == NULL)   
        return;

    postOrderRec(root->lChild);
    postOrderRec(root->rChild);
    printf("%d ", root->data);
}

TNode* maxElem(TNode *root) {
    while (root->rChild != NULL) {
        root = root->rChild;
    }

    return root;
    // printf("%d \n", root->data);
}

TNode* minElem(TNode *root) {
    while (root->lChild != NULL) {
        root = root->lChild;
    }

    return root;
    // printf("%d \n", root->data);
}


SNode* createSNode(TNode *t) {
    SNode *s = malloc(sizeof(SNode));
    s->tNode = t;
    s->next = NULL;

    return s;
}

void push(SNode **top, TNode *t) {
    if (*top == NULL) {
        *top = createSNode(t);
        return;
    } 

    SNode *newStackNode = createSNode(t);
    newStackNode->next = *top;

    *top = newStackNode;
}

TNode* pop(SNode **top) {
    if (*top == NULL)
        return NULL;
    
    TNode *tNode = (*top)->tNode;

    SNode *temp = *top;
    *top = (*top)->next;
    free(temp);

    return tNode;
}

TNode* peek(SNode *top) {
    if (top != NULL)
        return top->tNode;
    else
        return NULL;
}

int isEmptyS(SNode *top) {
    return top == NULL ? 1 : 0;
}