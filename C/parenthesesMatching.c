#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char ch;
    struct Node *next;
} *top = NULL;

typedef struct Node Node;


// Stack functions
void push(char ch);
char pop();
char peek();
int isEmpty();

// Main logic function
char* isBalancedExp(char *exp);


int main() {
    char *parenthesizedExp;

    printf("Enter a parenthesized expression : ");
    scanf("%s", parenthesizedExp);

    printf("Expression is %s \n", isBalancedExp(parenthesizedExp));

    return 0;
}


void push(char ch) {
    if (top == NULL) {
        top = malloc(sizeof(Node));
        top->ch = ch;
        top->next = NULL;
        return;
    }

    Node *t = malloc(sizeof(Node));
    t->ch = ch;
    t->next = top;

    top = t;
}

char pop() {
    if (top == NULL)
        return -1;

    Node *t = top;
    top = top->next;

    char ch = t->ch;
    free(t);

    return ch;
}

char peek() {
    if (top->ch)
        return top->ch;
    else 
        return '~';
}

int isEmpty() {
    if (top == NULL)
        return 1;
    else 
        return 0;
}

char* isBalancedExp(char *exp) {
    int i;
    for (i=0; exp[i] != '\0'; i++) {
        if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{' || exp[i] == '<') {
            push(exp[i]);
            continue;
        }

        if (isEmpty())
            return "unbalanced";
    
        switch(exp[i]) {
            case ')':   
                        if (peek() != '(')
                            return "unbalanced";
                        else {
                            pop();
                            break;
                        }
            case ']':   
                        if (peek() != '[')
                            return "unbalanced";
                        else {
                            pop();
                            break;
                        }
            case '}':   
                        if (peek() != '{')
                            return "unbalanced";
                        else {
                            pop();
                            break;
                        }
            case '>':   
                        if (peek() != '<')
                            return "unbalanced";
                        else {
                            pop();
                            break;
                        }
            default:    return "unbalanced";
        }
    }
    
    if (!isEmpty())
        return "unbalanced";
    else 
        return "balanced";
}