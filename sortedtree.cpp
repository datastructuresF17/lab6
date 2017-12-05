// Author:   Chad Palmer
// Semester: Fall 2017
// Class:    Data Structures (COSC 2436-004)
// Lab: 6

#include<iostream>
#include<memory>
#include<cstdlib>       // srand and rand
#include<ctime>         // time "seed"
#include "BinarySearchTree.h"
using namespace std;

// Function prototypes
int fillList(shared_ptr<BinaryTreeInterface<int>> listPtr);
void displayList(shared_ptr<BinaryTreeInterface<int>> listPtr);

// Driver program
int main() {

    srand(time(0));
    shared_ptr<BinaryTreeInterface<int>> listPtr;
    listPtr = make_shared<BinarySearchTree<int>>();

    int lastEntry = fillList(listPtr);              // create list, return last entry

    displayList(listPtr);                           // display the list

    cout << "Last number added: "
         << listPtr->getEntry(lastEntry)
         << " at position " << lastEntry << endl;

    cout << "Deleting last entry added to list... ";
    listPtr->remove(lastEntry);                     // delete last entry
    cout << "done." << endl << endl;

    displayList(listPtr);                           // display list again

    return 0;
}

// Function definitions
void displayList(shared_ptr<BinaryTreeInterface<int>> listPtr)
{
	cout << "Contents of sorted list: " << endl;
   for (int i = 1; i <= listPtr->getNumberOfNodes(); i++)
   {
      cout << listPtr->getEntry(i) << "-";
   }
	cout << endl << endl;
}

int fillList(shared_ptr<BinaryTreeInterface<int>> listPtr)
{
    int randInt = 0;

    for (int i = 0; i < 21; i++) {
        randInt = rand() % 100 + 1;
        listPtr->add(randInt);
    }
    return listPtr->getNumberOfNodes(randInt);
}
