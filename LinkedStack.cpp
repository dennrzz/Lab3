
#include <cassert>

#include "LinkedStack.h"  // Stack class specification file

//TODO 2: Linked Stack implementation from Chapter 7, week 3 Lecture 5. Replace with your file.

template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr) {
}

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack) {
    // Point to nodes in original chain
    Node<ItemType>* origChainPtr = aStack->topPtr;

    if (origChainPtr == nullptr)
        topPtr = nullptr;  // Original bag is empty
    else
    {
        // Copy first node
        topPtr = new Node<ItemType>();
        topPtr->setItem(origChainPtr->getItem());

        // Point to last node in new chain
        Node<ItemType>* newChainPtr = topPtr;

        // Copy remaining nodes
        while (origChainPtr != nullptr)
        {
            // Advance original-chain pointer
            origChainPtr = origChainPtr->getNext();

            // Get next item from original chain
            ItemType nextItem = origChainPtr->getItem();

            // Create a new node containing the next item
            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

            // Link new node to end of new chain
            newChainPtr->setNext(newNodePtr);

            // Advance pointer to new last node
            newChainPtr = newChainPtr->getNext();
        }  // end while

        newChainPtr->setNext(nullptr);           // Flag end of chain
    }  // end if
}

template<class ItemType>
LinkedStack<ItemType>::~LinkedStack() {
    // Pop until stack is empty
    while (!isEmpty())
        pop();
}  // end destructor

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const {
    return topPtr == nullptr;
}

template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem) {
    Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);
    topPtr = newNodePtr;
    newNodePtr = nullptr;

    return true;
}

template<class ItemType>
bool LinkedStack<ItemType>::pop() {
    bool result = false;
    if (!isEmpty())
    {
        // Stack is not empty; delete top
        Node<ItemType>* nodeToDeletePtr = topPtr;
        topPtr = topPtr->getNext();

        // Return deleted node to system
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;

        result = true;
    }  // end if

    return result;
}

template<class ItemType>
ItemType LinkedStack<ItemType>::peek() const {
    assert(!isEmpty());  // Enforce precondition

    // Stack is not empty; return top
    return topPtr->getItem();
}