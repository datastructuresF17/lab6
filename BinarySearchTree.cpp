#include "BinarySearchTree.h"
#include "BinaryNodeTree.h"
#include "BinaryNode.h"
#include <memory>
#include <iostream>
using namespace std;

template<class ItemType>
auto BinarySearchTree<ItemType>::placeNode(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                            shared_ptr<BinaryNode<ItemType>> newNode)
{
    shared_ptr<BinaryNode<ItemType>> tempPtr;

    if (subTreePtr == nullptr)                                                                      // If tree is empty
        return newNode;
    else if (subTreePtr->getItem() > newNode->getItem())
    {
        tempPtr = placeNode(subTreePtr->getLeftChildPtr(), newNode);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else
    {
        tempPtr = placeNode(subTreePtr->getRightChildPtr(), newNode);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                const ItemType target, bool& isSuccessful)
{
    shared_ptr<BinaryNode<ItemType>> tempPtr;

    if (subTreePtr == nullptr)
    {
        isSuccessful = false;
    }
    else if (subTreePtr->getItem() == target)
    {
        subTreePtr = removeNode(subTreePtr);
        isSuccessful = true;
    }
    else if (subTreePtr->getItem() > target)
    {
        auto tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else
    {
        auto tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

template<class ItemType>
auto BinarySearchTree<ItemType>::removeNode(shared_ptr<BinaryNode<ItemType>> nodePtr)
{
    // shared_ptr<BinaryNode<ItemType>> tempPtr;

    if (nodePtr->getLeftChildPtr() == nullptr || nodePtr->getRightChildPtr() == nullptr)
    {
        nodePtr = nullptr;
        return nodePtr;
    }
    else if ((nodePtr->getLeftChildPtr() != nullptr) != (nodePtr->getRightChildPtr() != nullptr))
    {
        shared_ptr<BinaryNode<ItemType>> nodeToConnectPtr = nullptr;

        if (nodePtr->getLeftChildPtr() != nullptr)
        {
            nodeToConnectPtr = nodePtr->getLeftChildPtr();
        }
        else
        {
            nodeToConnectPtr = nodePtr->getRightChildPtr();
        }
        return nodeToConnectPtr;
    }
    else
    {
        auto tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), nodePtr->getItem());
        nodePtr->setRightChildPtr(tempPtr);
        nodePtr->setItem(nodePtr->getItem());
        return nodePtr;
    }
}

template<class ItemType>
auto BinarySearchTree<ItemType>::removeLeftmostNode(shared_ptr<BinaryNode<ItemType>> subTreePtr, ItemType inorderSuccessor)
{
    // shared_ptr<BinaryNode<ItemType>> tempPtr;

    if (subTreePtr->getLeftChildPtr() == nullptr)          // Only has right child
    {
        inorderSuccessor = subTreePtr->getItem();
        return removeNode(subTreePtr);
    }
    else                                                // Only has left child
    {
        auto tempPtr = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
        subTreePtr->setLeftChildPtr(tempPtr);
        return subTreePtr;
    }
}

template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::findNode(shared_ptr<BinaryNode<ItemType>> treePtr,
                                          const ItemType& target, bool& isSuccessful) const
{
    if (treePtr == nullptr)                                                 // If nullptr, return nullptr
        return nullptr;
    else if (treePtr->getItem() == target)                                  // If found, return subTreePtr
    {
        isSuccessful = true;
        return treePtr;
    }
    else if (treePtr->getItem() > target)                                   // If target is smaller, search left
        return findNode(treePtr->getLeftChildPtr(), target, isSuccessful);
    else                                                                    // If target is bigger, search right
        return findNode(treePtr->getRightChildPtr(), target, isSuccessful);
}

//////////////////////// CONSTRUCTORS ///////////////////////////////

template<class ItemType>                                            // Default constructor
BinarySearchTree<ItemType>::BinarySearchTree() { }

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
                        :rootPtr(make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr)) { }


template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& tree)
{
    rootPtr = this->copyTree(tree.rootPtr);
}

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
    this->destroyTree(rootPtr);
}

////////////////// PUBLIC METHODS ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
    return rootPtr == nullptr;
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const
{
    return this->getHeightHelper(rootPtr);
}

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const
{
    return this->getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const throw(PrecondViolatedExcep)
{
    if (isEmpty())
        throw PrecondViolatedExcep("ERROR: getRootData() called while tree is empty");
    return this->rootPtr->getItem();
}

template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newData) const throw(PrecondViolatedExcep)
{
    if (isEmpty())
        this->rootPtr = make_shared<BinaryNode<ItemType>>(newData, nullptr, nullptr);
    else
        this->rootPtr->setItem(newData);
    //throw PrecondViolatedExcep("ERROR: Attempted change of root value in BST");
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newEntry)
{
    auto newNodePtr = make_shared<BinaryNode<ItemType>>(newEntry);
    rootPtr = placeNode(rootPtr, newNodePtr);
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target)
{
    bool isSuccessful = false;
    rootPtr = removeValue(rootPtr, target, isSuccessful);
    return isSuccessful;
}

template<class ItemType>
void BinarySearchTree<ItemType>::clear()
{
    this->destroyTree(rootPtr);
    this->rootPtr.reset();
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
    bool isSuccessful = false;
    auto binaryNodePtr = findNode(rootPtr, anEntry, isSuccessful);

    if (isSuccessful)
        return binaryNodePtr->getItem();
    else
        throw NotFoundException("Entry was not found in the tree");
}

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const
{
    bool isSuccessful = false;
    findNode(rootPtr, anEntry, isSuccessful);
    return isSuccessful;
}

template<class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
    this->preorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
    this->inorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
    this->postorder(visit, rootPtr);
}
