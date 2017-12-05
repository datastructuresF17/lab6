#include "BinarySearchTree.h"
#include "BinaryNode.h"
#include <memory>
#include <iostream>
using namespace std;

template<class ItemType>
auto BinarySearchTree<ItemType>::placeNode(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                            shared_ptr<BinaryNode<ItemType>> newNodePtr)
{
    if (subTreePtr == nullptr)                                                                      // If tree is empty
        return newNodePtr;
    else
    {
        if (subTreePtr->getItem() > newNodePtr->getItem())                                          // If new node is greater
            subTreePtr->setLeftChildPtr(placeNode(subTreePtr->getLeftChildPtr(), newNodePtr));
        else                                                                                        // If new node is less than
            subTreePtr->setRightChildPtr(placeNode(subTreePtr->getRightChildPtr(), newNodePtr));

    return subTreePtr;
    }
}

template<class ItemType>
auto BinarySearchTree<ItemType>::removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                const ItemType target, bool& isSuccessful)
{
    if (subTreePtr == nullptr)
    {
        isSuccessful = false;
        return nullptr;
    }
    if (subTreePtr->getItem() == target)
    {
        subTreePtr = removeNode(subTreePtr);
        isSuccessful = true;
        return subTreePtr;
    }
    else
    {
        if (subTreePtr->getItem() > target)
            subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful));
        else
            subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful));
    return subTreePtr;

    }
}

template<class ItemType>                                                                            // RETURN TO FINISH
auto BinarySearchTree<ItemType>::removeNode(shared_ptr<BinaryNode<ItemType>> nodePtr)
{
    /*
    if (nodePtr->isLeaf())
        return (nodePtr = nullptr);
    else if (nodePtr->getLeftChildPtr() == nullptr)
    */
}

template<class ItemType>
auto BinarySearchTree<ItemType>::removeLeftmostNode(shared_ptr<BinaryNode<ItemType>> subTreePtr, ItemType& inorderSuccessor)
{
    if (subTreePtr->getLeftChildPtr() == nullptr)          // Only has right child
    {
        inorderSuccessor = subTreePtr->getItem();
        return removeNode(subTreePtr);
    }
    else                                                // Only has left child
    {
        subTreePtr->setLeftChildPtr(removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor));
        return subTreePtr;
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
    // Define node
    // Check if node is nullptr
    // If it is null, throw NotFoundException "Entry not in the tree"
    // Else, return node->getItem()
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
