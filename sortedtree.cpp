// Author:   Chad Palmer
// Semester: Fall 2017
// Class:    Data Structures (COSC 2436-004)
// Lab: 6

#include<iostream>
#include<memory>
#include<cstdlib>       // srand and rand
#include<ctime>         // time "seed"
#include<vector>
#include "BinarySearchTree.h"
using namespace std;

vector<int> sortedTree;                 // Vector to store tree integers

// Function prototypes
void display(int& num);

// Driver program
int main() {

    srand(time(0));

    BinarySearchTree<int> tree;         // Create a tree object

    int num = 0;
    cout << "\nRandom numbers added to tree in this order: ";
    for (int index = 0; index < 22; index++) {
        num = rand() % 100 + 1;
        cout << num << ", ";
        tree.add(num);
    }
    cout << endl;




    cout << "Retrieving last number from tree: ";
    cout << tree.getEntry(num) << endl << endl;

    cout << "Removing last number from tree... ";
    tree.remove(num);
    cout << "done.\n\n";

    cout << "Displaying tree with inorderTraverse(): ";
    tree.inorderTraverse(display);
    cout << endl << endl;

    return 0;
}

// Function definitions
void display(int& num) {
    cout << num << ", ";
    sortedTree.push_back(num);
}
