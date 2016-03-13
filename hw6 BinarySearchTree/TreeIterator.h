/**	@file treeiterator.h
	@brief This file contains the declarations for the TreeIterator class
*/

#ifndef TREEITERATOR_H
#define TREEITERATOR_H

#include "TreeNode.h"

/**	@class TreeIterator
	@brief The TreeIterator class is designed to create a bidirectional iterator for the BinarySearchTree class

	Each TreeIterator object contains a pointer to a TreeNode and the BinarySearchTree to which it belongs. In order to make it a
	bidirectional iterator, operator ++/-- (both prefix and postfix), ==, != and *(returns a reference) have been overloaded.
*/
class TreeIterator {
public:
	TreeIterator();
	void swap(TreeIterator& other);
	TreeIterator& operator=(TreeIterator copy);
	TreeIterator& operator++();
	TreeIterator operator++(int unused);
	TreeIterator& operator--();
	TreeIterator operator--(int unused);
	bool operator==(const TreeIterator& rhs);
	bool operator!=(const TreeIterator& rhs);
	int& operator*();
	/**	Default destructor. Virtual keyword included to enable future polymorphism
	*/
	virtual ~TreeIterator() {};
private:
	TreeNode* node_pointer;
	BinarySearchTree* container;
	friend class BinarySearchTree;
};

#endif
#pragma once
