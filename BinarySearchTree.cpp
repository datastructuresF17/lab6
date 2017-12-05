#include "BinarySearchTree.h"
#include "BinaryNode.h"
#include <iostream>
using namespace std;

template<class ItemType>
auto BinarySearchTree<ItemType>::placeNode(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                            shared_ptr<BinaryNode<ItemType>> newNode);
{
    if (subTreePtr == nullptr)                                                                      // If tree is empty
        return newNodePtr;
    else
    {
        if (subTreePtr->getItem() > newNodePtr->getItem())                                          // If new node is greater
            subTreePtr->setLeftChildPtr(placeNode(subTreePtr->getLeftChildPtr(), newNodePtr));
        else                                                                                        // If new node is less than
        {
            subTreePtr->setRightChildPtr(placeNode(subTreePtr->getRightChildPtr(), newNodePtr));
            return subTreePtr;
        }
    }
}

template<class ItemType>
auto BinarySearchTree<ItemType>::removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                const ItemType target,
                                                bool& isSuccessful) override;
{
    if (subTreePtr == nullptr)
    {
        success = false;
        return nullptr;
    }
    if (subTreePtr->getItem() == target)
    {
        subTreePtr = removeNode(subTreePtr);
        success = true;
        return subTreePtr;
    }
    else
    {
        if (subTreePtr->getItem() > target)
            subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, success));
        else
        {
            subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, success));
            return subTreePtr;
        }
    }
}
