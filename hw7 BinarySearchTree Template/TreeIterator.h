/**	@file TreeIterator.h
	@brief This file contains the declarations and definitions for the templated TreeIterator class
*/

#ifndef TREEITERATOR_H
#define TREEITERATOR_H

#include <functional>
#include "TreeNode.h"

/**	@class TreeIterator
	@brief The TreeIterator class is designed to create a bidirectional iterator for the BinarySearchTree class

	Each TreeIterator object contains a pointer to a TreeNode and the BinarySearchTree to which it belongs. In order to make
	the objects bidirectional iterators, operator ++/-- (both prefix and postfix), ==, !=, *(returns a T reference) and
	->(allows access of TreeNode member) have been overloaded. Per the requirements for a bidirectional iterator, the default
	constructor, copy constructor and assignment operator have also been defined. The TreeIterator class is templated as with
	the BinarySearchTree and TreeNode class to deal with data of type T and comparison parameters of type CMP (default std::less).
	The TreeIterator class grants friendship to the BinarySearchTree class allowing the latter to access its members particularly
	for the begin() and end() functions.
*/
template<typename T, typename CMP = std::less<T>>
class TreeIterator {
	template<typename T, typename CMP>
	friend class BinarySearchTree;
public:
	TreeIterator<T, CMP>();
	TreeIterator<T, CMP>(const TreeIterator<T, CMP>& copy);
	void swap(TreeIterator<T, CMP>& other);
	TreeIterator<T, CMP>& operator=(TreeIterator<T, CMP> copy);

	TreeIterator<T, CMP>& operator++();
	TreeIterator<T, CMP> operator++(int unused);
	TreeIterator<T, CMP>& operator--();
	TreeIterator<T, CMP> operator--(int unused);
	bool operator==(const TreeIterator<T, CMP>& rhs);
	bool operator!=(const TreeIterator<T, CMP>& rhs);
	T& operator*();
	TreeNode<T, CMP>* operator->();
	/**	Default destructor. Virtual keyword included to enable future polymorphism
	*/
	virtual ~TreeIterator<T, CMP>() {};
private:
	TreeNode<T, CMP>* node_pointer;
	BinarySearchTree<T, CMP>* container;
};

/**	Default constructor for TreeIterator class. Set node_pointer and container to nullptr
*/
template<typename T, typename CMP>
TreeIterator<T, CMP>::TreeIterator<T, CMP>() {
	node_pointer = nullptr;
	container = nullptr;
}

/**	Copy constructor for TreeIterator class. Creates a shallow copy
*/
template<typename T, typename CMP>
TreeIterator<T, CMP>::TreeIterator<T, CMP>(const TreeIterator<T, CMP>& copy) {
	node_pointer = copy.node_pointer;
	container = copy.container;
}

/**	Swap function exchanges pointers between called TreeIterator object and other. Part of implementing copy swap idiom
	@param other is the TreeIterator object whose node_pointer and container pointers are being exchanged
*/
template<typename T, typename CMP>
void TreeIterator<T, CMP>::swap(TreeIterator<T, CMP>& other) {
	std::swap(node_pointer, other.node_pointer);
	std::swap(container, other.container);
}

/**	Overloaded operator= utilizes swap on copy of TreeIterator input to ensure no memory leaks occur. Part of implementing
	copy swap idiom
	@param copy is a copy of the TreeIterator object being assigned
	@return is a reference to the TreeIterator object that was assigned (through swap) the values of copy
*/
template<typename T, typename CMP>
TreeIterator<T, CMP>& TreeIterator<T, CMP>::operator=(TreeIterator<T, CMP> copy) {
	copy.swap(*this);
	return *this;
}

/**	Overloaded prefix operator++ for TreeIterator. Returns a reference to the TreeIterator containing T data of next largest size 
	@return a reference to the TreeIterator next in size of T data
*/
template<typename T, typename CMP>
TreeIterator<T, CMP>& TreeIterator<T, CMP>::operator++() {
	//if there is TreeNode to the right continue in that direction
	if (node_pointer->right != nullptr) {
		node_pointer = node_pointer->right;
		//cycle node_pointer to the very left TreeNode
		while (node_pointer->left != nullptr) {
			node_pointer = node_pointer->left;
		}
	}
	//if there is TreeNode to the left must backtrack
	else {
		TreeNode<T, CMP>* storage = nullptr;
		storage = node_pointer->node_parent;
		//cycle until node_parent is nullptr or reach left child (node_pointer != storage->right)
		while (storage != nullptr && node_pointer == storage->right) {
			node_pointer = storage;
			storage = storage->node_parent;
		}
		node_pointer = storage;
	}
	return *this;
}

/**	Overloaded postfix operator++ for TreeIterator. Increments TreeIterator object and returns an unincremented copy
	@return a copy of the TreeIterator object ++ was called upon
*/
template<typename T, typename CMP>
TreeIterator<T, CMP> TreeIterator<T, CMP>::operator++(int unused) {
	TreeIterator<T, CMP> copy = *this;
	++(*this);
	return copy;
}

/**	Overloaded prefix operator-- for TreeIterator. Returns a reference to the TreeIterator containing T data of next smallest size
	@return a reference to the TreeIterator previous in size of T data
*/
template<typename T, typename CMP>
TreeIterator<T, CMP>& TreeIterator<T, CMP>::operator--() {
	//if node_pointer is nullptr are currently at one past the final TreeIterator
	if (node_pointer == nullptr) {
		node_pointer = container->root;
		//sets node_pointer to largest value
		while (node_pointer->right != nullptr) {
			node_pointer = node_pointer->right;
		}
		return *this;
	}
	//if there is TreeNode to the left continue in that direction
	if (node_pointer->left != nullptr) {
		node_pointer = node_pointer->left;
		//cycle node_pointer to the very right TreeNode
		while (node_pointer->right != nullptr) {
			node_pointer = node_pointer->right;
		}
	}
	//if there is TreeNode to the right must backtrack
	else {
		TreeNode<T, CMP>* storage = nullptr;
		storage = node_pointer->node_parent;
		//cycle until node_parent is nullptr or reach right child (node_pointer != storage->left)
		while (storage != nullptr && node_pointer == storage->left) {
			node_pointer = storage;
			storage = storage->node_parent;
		}
		node_pointer = storage;
	}
	return *this;
}

/**	Overloaded postfix operator-- for TreeIterator. Decrements TreeIterator object and returns an undecremented copy
	@return a copy of the TreeIterator object -- was called upon
*/
template<typename T, typename CMP>
TreeIterator<T, CMP> TreeIterator<T, CMP>::operator--(int unused) {
	TreeIterator<T, CMP> copy = *this;
	--(*this);
	return copy;
}

/**	Comparison operator== overloaded to compare two TreeIterators
	@param rhs is a const reference to the TreeIterator being compared
	@return a bool value determining whether TreeIterators are ==
*/
template<typename T, typename CMP>
bool TreeIterator<T, CMP>::operator==(const TreeIterator<T, CMP>& rhs) {
	return ((this->node_pointer) == (rhs.node_pointer));
}

/**	Comparison operator!= overloaded to compare two TreeIterators
	@param rhs is a const reference to the TreeIterator being compared
	@return a bool value determining whether TreeIterators are !=
*/
template<typename T, typename CMP>
bool TreeIterator<T, CMP>::operator!=(const TreeIterator<T, CMP>& rhs) {
	return !(*this == rhs);
}

/**	Operator* has been overloaded to dereference TreeIterator
	@returns an T reference to the T data value of the node_pointer
*/
template<typename T, typename CMP>
T& TreeIterator<T, CMP>::operator*() {
	return (this->node_pointer->data);
}

/**	Operator-> has been overloaded to allow access of TreeIterator node_pointer member
	@return a pointer to the TreeIterator node_pointer
*/
template<typename T, typename CMP>
TreeNode<T, CMP>* TreeIterator<T, CMP>::operator->() {
	return node_pointer;
}

#endif
#pragma once
