BinarySearchTree.cpp: In constructor ‘BinarySearchTree<ItemType>::BinarySearchTree(const ItemType&)’:
BinarySearchTree.cpp:97:25: error: missing template arguments before ‘(’ token
     rootPtr = BinaryNode(rootItem, nullptr, nullptr);
                         ^
BinarySearchTree.cpp: At global scope:
BinarySearchTree.cpp:201:1: error: invalid use of template-name ‘BinarySearchTree’ without an argument list
 BinarySearchTree& BinarySearchTree<ItemType>::operator=(const BinarySearchTree& rightHandSide)      //Defined right?
 ^
BinarySearchTree.h: In instantiation of ‘class BinarySearchTree<int>’:
/usr/include/c++/5/type_traits:1476:45:   recursively required by substitution of ‘template<class _To1> static void std::__is_convertible_helper<_From, _To, false>::__test_aux(_To1) [with _To1 = BinaryTreeInterface<int>*]’
/usr/include/c++/5/type_traits:1476:45:   required by substitution of ‘template<class _From1, class _To1, class> static std::true_type std::__is_convertible_helper<_From, _To, false>::__test(int) [with _From1 = BinarySearchTree<int>*; _To1 = BinaryTreeInterface<int>*; <template-parameter-1-3> = <missing>]’
/usr/include/c++/5/type_traits:1485:42:   required from ‘struct std::__is_convertible_helper<BinarySearchTree<int>*, BinaryTreeInterface<int>*, false>’
/usr/include/c++/5/type_traits:1491:12:   required from ‘struct std::is_convertible<BinarySearchTree<int>*, BinaryTreeInterface<int>*>’
/usr/include/c++/5/bits/shared_ptr.h:97:65:   required by substitution of ‘template<class _Tp> template<class _Ptr> using _Convertible = typename std::enable_if<std::is_convertible<_Ptr, _Tp*>::value>::type [with _Ptr = BinarySearchTree<int>*; _Tp = BinaryTreeInterface<int>]’
/usr/include/c++/5/bits/shared_ptr.h:220:31:   required by substitution of ‘template<class _Tp1, class> std::shared_ptr<_Tp>::shared_ptr(const std::shared_ptr<_Tp1>&) [with _Tp1 = BinarySearchTree<int>; <template-parameter-1-2> = <missing>]’
sortedtree.cpp:22:13:   required from here
BinarySearchTree.cpp:25:6: error: conflicting return type specified for ‘auto BinarySearchTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType> >, ItemType, bool&) [with ItemType = int]’
 auto BinarySearchTree<ItemType>::removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr,
      ^
In file included from BinaryNodeTree.h:104:0,
                 from BinarySearchTree.h:14,
                 from sortedtree.cpp:10:
BinaryNodeTree.cpp:98:39: error:   overriding ‘std::shared_ptr<BinaryNode<ItemType> > BinaryNodeTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType> >, ItemType, bool&) [with ItemType = int]’
 std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                       ^
sortedtree.cpp: In function ‘int fillList(std::shared_ptr<BinaryTreeInterface<int> >)’:
sortedtree.cpp:60:45: error: no matching function for call to ‘BinaryTreeInterface<int>::getNumberOfNodes(int&)’
     return listPtr->getNumberOfNodes(randInt);
                                             ^
In file included from BinarySearchTree.h:12:0,
                 from sortedtree.cpp:10:
BinaryTreeInterface.h:26:16: note: candidate: int BinaryTreeInterface<ItemType>::getNumberOfNodes() const [with ItemType = int]
    virtual int getNumberOfNodes() const = 0;
                ^
BinaryTreeInterface.h:26:16: note:   candidate expects 0 arguments, 1 provided
In file included from BinarySearchTree.h:96:0,
                 from sortedtree.cpp:10:
BinarySearchTree.cpp: In instantiation of ‘auto BinarySearchTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType> >, ItemType, bool&) [with ItemType = int]’:
sortedtree.cpp:61:1:   required from here
BinarySearchTree.cpp:37:16: error: inconsistent deduction for ‘auto’: ‘std::nullptr_t’ and then ‘std::shared_ptr<BinaryNode<int> >’
         return subTreePtr;
                ^
BinarySearchTree.cpp:45:12: error: inconsistent deduction for ‘auto’: ‘std::nullptr_t’ and then ‘std::shared_ptr<BinaryNode<int> >’
     return subTreePtr;
            ^
BinarySearchTree.cpp: In instantiation of ‘auto BinarySearchTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType> >, const ItemType&) const [with ItemType = int]’:
BinarySearchTree.cpp:179:20:   required from ‘bool BinarySearchTree<ItemType>::contains(const ItemType&) const [with ItemType = int]’
sortedtree.cpp:61:1:   required from here
BinarySearchTree.cpp:82:16: error: inconsistent deduction for ‘auto’: ‘std::nullptr_t’ and then ‘std::shared_ptr<BinaryNode<int> >’
         return treePtr;
                ^
BinarySearchTree.cpp: In instantiation of ‘bool BinarySearchTree<ItemType>::contains(const ItemType&) const [with ItemType = int]’:
sortedtree.cpp:61:1:   required from here
BinarySearchTree.cpp:179:20: error: converting to ‘bool’ from ‘std::nullptr_t’ requires direct-initialization [-fpermissive]
     return findNode(rootPtr, anEntry);
                    ^
Makefile:5: recipe for target 'sortedtree.o' failed
make: *** [sortedtree.o] Error 1
