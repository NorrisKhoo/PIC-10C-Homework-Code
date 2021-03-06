/**	@file treeiterator.cpp
	@brief This file contains the definitions for the TreeIterator class
*/

#include "TreeIterator.h"
#include "BinarySearchTree.h"
#include "TreeNode.h"

/**	Default constructor for TreeIterator class. Set node_pointer and container to nullptr
*/
TreeIterator::TreeIterator() {
	node_pointer = nullptr;
	container = nullptr;
}

/**	Swap function exchanges pointers between called TreeIterator object and other. Part of implementing copy swap idiom
	@param other is the TreeIterator object whose node_pointer and container pointers are being exchanged
*/
void TreeIterator::swap(TreeIterator& other) {
	std::swap(node_pointer, other.node_pointer);
	std::swap(container, other.container);
}

/**	Overloaded operator= utilizes swap on copy of TreeIterator input to ensure no memory leaks occur. Part of implementing
	copy swap idiom
	@param copy is a copy of the TreeIterator object being assigned
	@return is a reference to the TreeIterator object that was assigned (through swap) the values of copy
*/
TreeIterator& TreeIterator::operator=(TreeIterator copy) {
	copy.swap(*this);
	return *this;
}

/**	Overloaded prefix operator++ for TreeIterator. Returns a reference to the TreeIterator containing int data of next largest size
	@return a reference to the TreeIterator next in size of int data
*/
TreeIterator& TreeIterator::operator++() {	 
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
		TreeNode* storage = nullptr;
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
TreeIterator TreeIterator::operator++(int unused) {
	TreeIterator copy = *this;
	++(*this);
	return copy;
}

/**	Overloaded prefix operator-- for TreeIterator. Returns a reference to the TreeIterator containing int data of next smallest size
	@return a reference to the TreeIterator previous in size of int data
*/
TreeIterator& TreeIterator::operator--() {
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
		TreeNode* storage = nullptr;
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
TreeIterator TreeIterator::operator--(int unused) {
	TreeIterator copy = *this;
	--(*this);
	return copy;
}

/**	Comparison operator== overloaded to compare int values of two TreeIterators
	@param rhs is a const reference to the TreeIterator being compared
	@return a bool value determining whether int values of TreeIterators are ==
*/
bool TreeIterator::operator==(const TreeIterator& rhs) {
	return ((this->node_pointer) == (rhs.node_pointer));
}

/**	Comparison operator!= overloaded to compare int values of two TreeIterators
	@param rhs is a const reference to the TreeIterator being compared
	@return a bool value determining whether int values of TreeIterators are !=
*/
bool TreeIterator::operator!=(const TreeIterator& rhs) {
	return !(*this == rhs);
}

/**	Operator* has been overloaded to dereference TreeIterator
	@returns an int reference to the int data value of the node_pointer
*/
int& TreeIterator::operator*() {
	return (this->node_pointer->data);
}