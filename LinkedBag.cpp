/** ADT bag: Link-based implementation.*/
#include "LinkedBag.h"
#include "Node.h"
#include <cstddef>

// TODO 1: Linked Bag implementation From Lab 2 Chapter 4.  Replace with your file.

/*
 * private:
 * returns either a pointer to the node containing a given target
 * or the nullptr if the target is not in the bag
 */
template<class ItemType>
Node<ItemType> *LinkedBag<ItemType>::getPointerTo(const ItemType &target) const {
    bool found = false;
    Node<ItemType>* currPtr = headPtr;

    while(!found && (currPtr != nullptr)) {
        if(target == currPtr->getItem()) {
            found = true;
        } else {
            currPtr = currPtr->getNext();
        }
    }

    return currPtr;
}

/*
 * default constructor
 * initializes headPtr = nullptr, itemCount to 0
 */
template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0) {
    // empty
}

/*
 * copy constructor
 */
template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType> &aBag) {
    itemCount = aBag.itemCount;
    Node<ItemType>* origChainPtr = aBag.headPtr;  // points to nodes in original link

    if (origChainPtr == nullptr)
        headPtr = nullptr;  // original bag is empty; so is copy
    else
    {
        // copy the first node
        headPtr = new Node<ItemType>();
        headPtr->setItem(origChainPtr->getItem());

        // copy the remaining nodes
        Node<ItemType>* newChainPtr = headPtr; // last-node pointer
        while (origChainPtr != nullptr)
        {
            origChainPtr = origChainPtr ->getNext(); // moves the pointer

            // gets next item from original link
            ItemType nextItem = origChainPtr->getItem();

            // creates a new node containing the next item
            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

            // links new node to end of new link
            newChainPtr->setNext(newNodePtr);

            // moves pointer to new last node
            newChainPtr = newChainPtr->getNext();
        }

        newChainPtr->setNext(nullptr); // flags end of new link
    }
}

/*
 * ~destructor
 */
template<class ItemType>
LinkedBag<ItemType>::~LinkedBag()  {
    clear();
}

/*
 * gets current size of the link
 */
template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const {
    return itemCount;
}

/*
 * checks if the chain is empty
 */
template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const {
    return itemCount == 0;
}

/*
 * adds a new entry to the beginning of the link
 * new node reference rest of the link
 * headPtr is null if chain is empty
 */
template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType &newEntry) {
    Node<ItemType>* nextNodePtr = new Node<ItemType>();
    nextNodePtr->setItem(newEntry);
    nextNodePtr->setNext(headPtr); // new node points to chain

    headPtr = nextNodePtr; // new node is now first node
    itemCount++;

    return true;
}

/*
 * removes an entry in the link
 * and resizes the link after deletion
 */
template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType &anEntry) {
    Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
    bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
    if (canRemoveItem)
    {
        // copy data from first node to located node
        entryNodePtr->setItem(headPtr->getItem());

        // delete first node
        Node<ItemType>* nodeToDeletePtr = headPtr;
        headPtr = headPtr->getNext();

        // return node to the system
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;

        itemCount--;
    }

    return canRemoveItem;
}

template<class ItemType>
void LinkedBag<ItemType>::clear() {
    Node<ItemType>* nodeToDeletePtr = headPtr;
    while (headPtr != nullptr)
    {
        headPtr = headPtr->getNext();

        // return node to the system
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;

        nodeToDeletePtr = headPtr;
    }
    // headPtr is nullptr; nodeToDeletePtr is nullptr

    itemCount = 0;
}

/*
 * checks if there is an entry in the link
 */
template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType &anEntry) const {
    return(getPointerTo(anEntry) != nullptr);
}

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType &anEntry) const {
    int freq, count =0;
    Node<ItemType>* curPtr = headPtr;
    while ((curPtr != nullptr) && (count < itemCount))
    {
        if (anEntry == curPtr->getItem())
        {
            freq++;
        }

        count++;
        curPtr = curPtr->getNext();
    }

    return freq;
}

template<class ItemType>
vector<ItemType> LinkedBag<ItemType>::toVector() const {
    vector<ItemType> bagContents;
    Node<ItemType>* curPtr = headPtr;
    int counter = 0;
    while ((curPtr != nullptr) && (counter < itemCount))
    {
        bagContents.push_back(curPtr->getItem());
        curPtr = curPtr->getNext();
        counter++;
    }

    return bagContents;
}
