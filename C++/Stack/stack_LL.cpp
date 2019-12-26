#include <iostream>
using namespace std;


class Stack {
private:
    struct Node {
        int data;
        Node *next;
    } *top;

public:
    Stack() {
        top = NULL;
    }

    void push(int elem);
    int pop();
    void peek();

    ~Stack();
};


int main() {
    Stack s;

    int ch = 1, op;
    int elem;

    while (ch) {
        printf("\nStack using Linked List\n");
        printf("\n1. Push");
        printf("\n2. Pop");
        printf("\n3. Peek / Display");
        printf("\n4. Exit\n");

        scanf("%d", &op);

        switch (op) {
            case 1:
                    printf("\nEnter element : ");
                    scanf("%d", &elem);
                    s.push(elem);
                    break;
            case 2:
                    cout << s.pop();
                    break;
            case 3:
                    s.peek();
                    break;
            case 4:
                    exit(0);
                    break;
            default:
                    break;
        }

        printf("\nDo you wish to continue? (1/0) : ");
        scanf("%d", &ch);
    }

    return 0;
}


void Stack::push(int elem) {
    Node *t = (Node*) malloc(sizeof(Node));
    t->data = elem;
    if (top == NULL)
        t->next = NULL;
    else
        t->next = top;
    top = t;
}

int Stack::pop() {
    if (top == NULL) {
        printf("Stack underflow \n");
        return -1;
    }

    Node *t = top;
    int elem = t->data;
    top = top->next;
    free(t);
    
    return elem;
}

void Stack::peek() {
    if (top == NULL) {
        printf("Empty stack\n");
        return;
    }

    Node *temp = top;

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

Stack::~Stack() {
    Node *temp;

    while (top != NULL) {
        temp = top;
        top = top->next;
        delete temp;
    }
}