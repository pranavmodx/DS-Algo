class Node:
    def __init__(self, data):
        self.data = data
        self.next = None


class singlyLinkedList:
    def __init__(self):
        self.head = None

    def isEmptyList(self):
        if self.head is None:
            return True
        return False
    
    def createList(self):
        print('Enter the number of nodes in the list : ')
        n = int(input())
        for i in range(n):
            print(f"Enter element at position {i} or node {i+1}")
            inputNode = input()
            createNode = Node(inputNode)
            self.insertAtEnd(createNode)
        self.printList()

    def listLength(self):
        length = 0
        currentNode = self.head
        while currentNode is not None:
            length += 1
            currentNode = currentNode.next
        return length
    
    def search(self, sNode):
        # Referencing second last node -> if currentNode.next.next = None
        currentNode = self.head
        pos = 0
        while currentNode is not None:
            if currentNode.data == sNode:
                return pos
            pos += 1
            currentNode = currentNode.next
        else:
            print(f'{sNode} not found in the list.')

    def insertAtEnd(self, newNode):
        # If head is not present, ie, if list is empty, assign head to the new node inserted.
        if self.head is None:
            self.head = newNode
        else:  # If head is present iterate till the last node is reached and point last node's next pointer to the new node inserted.
            lastNode = self.head
            while True:
                if lastNode.next is None:
                    break
                lastNode = lastNode.next
            lastNode.next = newNode

    def insertAtStart(self, startNode):
        tempNode = self.head  # Head is stored safely in a temporary node.
        self.head = startNode  # The inserted node is made the new head.
        # Or self.head.next = tempNode ; The newly made head is made to point to the temp node containing previous head(now the 2nd node) to join the link.
        startNode.next = tempNode
        del tempNode  # The temporary node is no longer need, hence deleted.

    def insertAtMiddle(self, midNode, pos):
        # Corner cases -> pos : start, end and invalid.
        if pos == 0:
            self.insertAtStart(midNode)
            return
        if pos < 0 or pos > self.listLength():
            print('Invalid position!')
            return

        tempNode = self.head
        for i in range(pos-1):  # Traversing till the required node.
            tempNode = tempNode.next
        # Next pointer of midNode is made to point to the next pointer of previous node (tempNode - node prior to the upcoming midNode).
        midNode.next = tempNode.next
        # Next pointer of tempNode now points to the newly inserted midNode.
        tempNode.next = midNode

    def deleteAtEnd(self):
        currentNode = self.head
        len = self.listLength()

        # Hard coded stuff -> somehow works. Not the correct way.
        # for i in range(len):
        #     if i == len - 2:
        #         tempNode = currentNode
        #     currentNode = currentNode.next
        #     if i == len - 1:
        #         del currentNode
        # tempNode.next = None

        # Corner case
        if len == 1:
            self.head = None
            return

        lastNode = self.head
        while lastNode.next is not None:  # Traversing till the last node.
            # Safely keeping the previous node, as node once traversed through cannot be accessed later.
            previousNode = lastNode
            lastNode = lastNode.next
        # Pointing the last node to none. Gets dumped automatically without explicit deletion.
        previousNode.next = None

    def deleteAtStart(self):
        # Corner Case
        if self.isEmptyList():
            print('List is empty. Cannot perform deletion.')
        else:
            previousHead = self.head
            # Previous head is changed to new head (ie, next element).
            self.head = self.head.next
            previousHead.next = None  # Previous head is deleted in the same way as in deleteAtEnd() method.

    def deleteAtMiddle(self, pos):
        # Corner Cases -> pos : start, end and invalid.
        if pos == 0:
            self.deleteAtStart()
            return
        if pos < 0 and pos >= self.listLength():
            print('Invalid position')
            return
        if pos == self.listLength()-1:
            self.deleteAtEnd()
            return
        currentNode = self.head
        for i in range(pos): # Traversing till specified position.
            tempNode = currentNode # Safely storing the node before the specified node pos.
            currentNode = currentNode.next
        tempNode.next = currentNode.next # The next pointer of node prior to the outgoing midNode is made to point to the node after the midNode.
        currentNode.next = None # Deletion.

    def printList(self):
        print('The list elements are : ', end='')
        if self.isEmptyList():
            print('List is empty!')
        else:
            currentNode = self.head
            # pos = 0
            while True:
                if currentNode is None:
                    break
                print(currentNode.data, end = ' ')
                currentNode = currentNode.next
                # pos +=1
        print()

    def menu(self):

        print('Menu')
        print('_______________________')
        print('Choose any operation to perform : ')
        print('1. Search')
        print('2. Length of list')
        print('3. Insert at End')
        print('4. Insert at Start')
        print('5. Insert at Middle')
        print('6. Delete at End')
        print('7. Delete at Start')
        print('8. Delete at Middle')
        print('9. Exit')
        ch = int(input('Enter your choice : '))

        if ch == 1:
            print('Enter element to search : ')
            elem = input()
            print(f'Element found at index {self.search(elem)}')
        elif ch == 2:
            print(f'The length of list is : {self.listLength()}')
        elif ch == 3:
            elem = input('Enter element to insert at end : ')
            createNode = Node(elem)
            self.insertAtEnd(createNode)
        elif ch == 4:
            elem = input('Enter element to insert at start : ')
            createNode = Node(elem)
            self.insertAtStart(createNode)
        elif ch == 5:
            elem = input('Enter element to insert at middle : ')
            createNode = Node(elem)
            position = int(input('Enter position of element : '))
            self.insertAtMiddle(createNode, position)
        elif ch == 6:
            self.deleteAtEnd()
        elif ch == 7:
            self.deleteAtStart()
        elif ch == 8:
            position = int(input('Enter position of node to delete at middle : '))
            self.deleteAtMiddle(position)
        elif ch == 9:
            exit()
        else:
            print('Invalid choice!')
            exit()

        self.printList()

        print('Do you want to perform more operations? (Y/N) or (y/n)')
        re = input()

        if re in ('Y','y'):
            self.menu()
        

linkedList = singlyLinkedList()
linkedList.createList()
linkedList.menu()

