/**	@file binarysearchtree.h
	@brief This file contains the declarations for the BinarySearchTree class

	Functionality has been expanded from the default code provided by the book
*/

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include "TreeNode.h"
#include "TreeIterator.h"

/**	@class BinarySearchTree
	@brief The BinarySearchTree class is designed to create a Binary Seach Tree of int values

	The BinarySearchTree class contains a pointer to its root TreeNode object (which in turn contains pointers to its left, right and
	parent neighbors connecting all within the system). Functions have been included that allow the insertion of new int values, the 
	deletion of int values, determine whether an int value exists within the system and provide the smallest/largest int value of the
	BinarySearchTree object. The copy swap idiom has been implemented and a recursive destructor is included which cycles through
	the TreeNode objects. The BinarySearchTree class has friendship with the TreeIterator class allowing the prior to access its variables
	particularly for the begin() and end() functions
*/
class BinarySearchTree {
public:
	BinarySearchTree();
	
	BinarySearchTree(const BinarySearchTree& copy);
	TreeNode* node_copy(const TreeNode* copy);
	void set_parent(TreeNode* child);
	void swap(BinarySearchTree& other);
	BinarySearchTree& operator=(BinarySearchTree copy);

	void insert(int data);
	void erase(int data);
	int count(int data) const;
	void print() const;
	int smallest();
	int largest();
	TreeIterator begin();
	TreeIterator end();

	void recursive_destructor(TreeNode* node);
	/**	The BinarySearchTree destructor calls recursive_destructor on the root so that starting from the origin, it may cycle to all
		TreeNodes both to the left and right of the root calling delete. Virtual keyword included to enable future polymorphism
	*/
	virtual ~BinarySearchTree() {
		recursive_destructor(root);
	}
private:
	TreeNode* root;
	friend class TreeIterator;
};

#endif
#pragma once
