#include "BinarySearchTree.h"
#include "BinaryNode.h"
#include <memory>
#include <iostream>
using namespace std;

template<class ItemType>
auto BinarySearchTree<ItemType>::placeNode(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                            shared_ptr<BinaryNode<ItemType>> newNodePtr)
{
    shared_ptr<BinaryNode<ItemType>> tempPtr;

    if (subTreePtr == nullptr)                                                                      // If tree is empty
        return newNodePtr;
    else if (subTreePtr->getItem() > newNodePtr->getItem())
    {
        tempPtr = placeNode(subTreePtr->getLeftChildPtr(), newNodePtr);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else
    {
        tempPtr = placeNode(subTreePtr->getRightChildPtr(), newNodePtr);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

template<class ItemType>
auto BinarySearchTree<ItemType>::removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr,
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
        tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else
    {
        tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

template<class ItemType>                                                                            // RETURN TO FINISH
auto BinarySearchTree<ItemType>::removeNode(shared_ptr<BinaryNode<ItemType>> nodePtr)
{
    if (nodePtr->getLeftChildPtr() == nullptr && nodePtr->getRightChildPtr() == nullptr)
        return nodePtr;
    else if ((nodePtr->getLeftChildPtr() != nullptr) != (nodePtr->getRightChildPtr() != nullptr))
    {
        shared_ptr<BinaryNode<ItemType>> nodeToConnectPtr = nullptr;

        if (nodePtr->getLeftChildPtr() != nullptr)
            nodeToConnectPtr = nodePtr->getLeftChildPtr();
        else
            nodeToConnectPtr = nodePtr->getRightChildPtr();
        return nodeToConnectPtr;
    }
    else
    {
        tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), nodePtr->getItem());
        nodePtr->setRightChildPtr(tempPtr);
        nodePtr->setItem(nodePtr->getItem());
        return nodePtr;
    }
}

template<class ItemType>
auto BinarySearchTree<ItemType>::removeLeftmostNode(shared_ptr<BinaryNode<ItemType>> nodePtr, ItemType& inorderSuccessor)
{
    shared_ptr<BinaryNode<ItemType>> tempPtr;

    if (nodePtr->getLeftChildPtr() == nullptr)          // Only has right child
    {
        inorderSuccessor = nodePtr->getItem();
        return removeNode(nodePtr);
    }
    else                                                // Only has left child
    {
        tempPtr = removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor);
        nodePtr->setLeftChildPtr(tempPtr);
        return nodePtr;
    }
}

template<class ItemType>
auto BinarySearchTree<ItemType>::findNode(shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType& target) const
{
    if (treePtr == nullptr)                                      // If nullptr, return nullptr
        return nullptr;
    else if (treePtr->getItem() == target)                       // If found, return subTreePtr
        return treePtr;
    else if (treePtr->getItem() > target)                        // If target is smaller, search left
        return findNode(treePtr->getLeftChildPtr(), target);
    else                                                            // If target is bigger, search right
        return findNode(treePtr->getRightChildPtr(), target);
}

//////////////////////// CONSTRUCTORS ///////////////////////////////

template<class ItemType>                                            // Default constructor
BinarySearchTree<ItemType>::BinarySearchTree() { }

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
{
    rootPtr = BinaryNode(rootItem, nullptr, nullptr);
}

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
    return rootPtr->getItem();
}

template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newData) const throw(PrecondViolatedExcep)
{
    throw PrecondViolatedExcep("ERROR: Attempted change of root value in BST");
}

template<class ItemType>                                                        // RETURN TO COMPLETE
bool BinarySearchTree<ItemType>::add(const ItemType& newEntry)
{
    auto newNodePtr = make_shared<BinaryNode<ItemType>>(newEntry);
    balancedAdd(rootPtr, newNodePtr);
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
    rootPtr = nullptr;
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)   // CONTINUE WITH getEntry() DEFINITION HERE //
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
    return findNode(rootPtr, anEntry);
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

template<class ItemType>
BinarySearchTree& BinarySearchTree<ItemType>::operator=(const BinarySearchTree& rightHandSide)      //Defined right?
{
    if (!isEmpty())
        clear();
    this = copyTree(&rightHandSide);
    return *this;
}
