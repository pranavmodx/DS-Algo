#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

class singlyLL {
private:
    Node *head;

public:
    singlyLL() {
        head = NULL;
    };

    int countNodes();

    void insertAtBeg(int elem);
    void insertAtMid(int elem, int pos);
    void insertAtEnd(int elem);

    int deleteAtBeg();
    int deleteAtMid(int pos);
    int deleteAtEnd();

    void displayList();

    ~singlyLL();
};


int main() {
    singlyLL ll;

    int ch = 1, op;
    int elem, pos;

    while (ch) {
        cout << "\nSingly Linked List\n";
        cout << "\n1. Insert at start";
        cout << "\n2. Insert at mid";
        cout << "\n3. Insert at end";
        cout << "\n4. Delete at start";
        cout << "\n5. Delete at mid";
        cout << "\n6. Delete at end";
        cout << "\n7. Display list";
        cout << "\n8. Exit\n";

        cin >> op;

        switch (op) {
            case 1:
                    cout << "\nEnter element : ";
                    cin >> elem;
                    ll.insertAtBeg(elem);
                    break;
            case 2:
                    cout << "\nEnter element : ";
                    cin >> elem;
                    cout << "\nEnter position : ";
                    cin >> pos;
                    ll.insertAtMid(elem, pos);
                    break;
            case 3:
                    cout << "\nEnter element : ";
                    cin >> elem;
                    ll.insertAtEnd(elem);
                    break;
            case 4:
                    cout << ll.deleteAtBeg() << endl;
                    break;
            case 5:
                    cout << "\nEnter position : ";
                    cin >> pos;
                    cout << ll.deleteAtMid(pos) << endl;
                    break;
            case 6:
                    cout << ll.deleteAtEnd() << endl;
                    break;
            case 7:
                    ll.displayList();
                    break;
            case 8:
                    exit(0);
                    break;
            default:
                    cout << "Invalid choice" << endl;
                    break;
        }

        cout << "\nDo you wish to continue? (1/0) : ";
        cin >> ch;
    }

    return 0;
}


int singlyLL::countNodes() {
    Node *temp = head;

    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    delete temp;
    return count;
}

void singlyLL::displayList() {
    Node *temp = head;

    if (temp == NULL) {
        cout << "Empty list" << endl;
        return;
    }

    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    };

    delete temp;
    cout << endl;
}

void singlyLL::insertAtBeg(int elem) {
    Node *t = new Node;
    t->data = elem;

    if (head == NULL) {
        t->next = NULL;
        head = t;
    } else {
        t->next = head;
        head = t;
    }
}

void singlyLL::insertAtMid(int elem, int pos) {
    if (head == NULL) {
        insertAtBeg(elem);
        return;
    }

    if (pos < 0 || pos > countNodes()) {
        cout << "Please enter a valid position" << endl;
        return;
    } else if (pos == 0) {
        insertAtBeg(elem);
        return;
    } else if (pos == countNodes()) {
        insertAtEnd(elem);
        return;
    }

    Node *temp = head;

    int i=0;
    while (i < pos-1) {
        temp = temp->next;
        i++;
    }

    Node *t = new Node;
    t->data = elem;
    
    t->next = temp->next;
    temp->next = t;
}

void singlyLL::insertAtEnd(int elem) {
    if (head == NULL) {
        insertAtBeg(elem);
        return;
    }

    Node *temp = head;

    while (temp->next != NULL) 
        temp = temp->next;

    Node *t = new Node;
    t->data = elem;

    t->next = NULL;
    temp->next = t;
}

int singlyLL::deleteAtBeg() {
    if (head == NULL) 
        return -1;

    int elem;

    Node *temp = head;

    if (temp->next == NULL) {
        elem = temp->data;
        delete temp;
        temp = NULL;
        return elem;
    }
    
    head = head->next;

    elem = temp->data;
    delete temp;

    return elem;
}

int singlyLL::deleteAtMid(int pos) {
    int i = 0;
    if (head == NULL)
        return -1;

    if (pos < 0 || pos > countNodes()) {
        cout << "Please enter a valid position" << endl;
        return -1;
    } 
    else if (pos == 0 || head->next == NULL)
        return deleteAtBeg();    
    else if (pos == countNodes())
        return deleteAtEnd();

    if (head->next == NULL)
        return deleteAtBeg();

    int elem;

    Node *temp = head;

    while (i < pos - 1) {
        temp = temp->next;
        i++;
    }
    
    Node *t = temp->next;

    temp->next = temp->next->next;

    elem = t->data;
    delete t;

    return elem;
}

int singlyLL::deleteAtEnd() {
    int elem;

    if (head == NULL) {
        return -1;
    }

    if (head->next == NULL) {
        elem = head->data;
        delete head;
        head = NULL;
        return elem;
    }
    
    Node *temp = head;

    while (temp->next->next != NULL)
        temp = temp->next;

    Node *t = temp->next;
    temp->next = NULL;
    elem = t->data;
    delete t;

    return elem;
}

singlyLL::~singlyLL() {
    Node *temp = head;
    int i;
    for (i=0; i<countNodes(); i++) {
        head = head->next;
        delete temp;
    }
}