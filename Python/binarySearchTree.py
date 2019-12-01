class Node:
    def __init__(self, value=None):
        self.value = value
        self.leftChild = None
        self.rightChild = None


class binarySearchTree:
    def __init__(self):
        self.root = None

    def insert(self, value):
        if self.root == None:
            self.root = Node(value)
        else:
            self._insert(self.root, value)

    def _insert(self, currentNode, value):
        if value < currentNode.value:
            if currentNode.leftChild == None:
                currentNode.leftChild = Node(value)
            else:
                self._insert(currentNode.leftChild, value)
        elif value > currentNode.value:
            if currentNode.rightChild == None:
                currentNode.rightChild = Node(value)
            else:
                self._insert(currentNode.rightChild, value)
        else:
            print('Value already exists! Please enter a non-existant one.')

    def createTree(self):
        print('Enter no. of tree elements : ')
        n = int(input())
        for i in range(n):
            print(f'Enter element {i}')
            ele = int(input())
            createNode = Node(ele)
            self.insert(createNode.value)

    def printTree(self):
        if self.root == None:
            print('\nThe Tree is empty.')
        else:
            print('\n')
            self._printTree(self.root)

    def _printTree(self, currentNode):
        if currentNode != None:
            self._printTree(currentNode.leftChild)
            print(currentNode.value)
            self._printTree(currentNode.rightChild)


tree = binarySearchTree()
tree.createTree()
tree.printTree()
