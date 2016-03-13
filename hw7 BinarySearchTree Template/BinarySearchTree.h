/**	@file BinarySearchTree.h
	@brief This file contains the declarations and definitions for the templated BinarySearchTree class
*/

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <functional>
#include "TreeNode.h"
#include "TreeIterator.h"

/**	@class BinarySearchTree
	@brief The BinarySearchTree class is designed to create a Binary Search Tree of T values

	The BinarySearchTree class contains a pointer to its root TreeNode object (which in turn contains pointers to its left, right and
	parent neighbors connecting all TreeNode objects within the system). Functions have been included that allow the insertion of new
	T values, the deletion of T values, determine whether a T value exists within the system and provide the smallest/largest T value
	in the BinarySearchTree object. The copy swap idiom has been implemented and a recursive destructor is included that cycles through
	the TreeNode objects calling delete. The BinarySearchTree class is templated as with the TreeIterator and TreeNode classes to deal 
	with data of type T and comparison parameters of type CMP (default std::less)
*/
template<typename T, typename CMP = std::less<T>>
class BinarySearchTree {
public:
	BinarySearchTree<T, CMP>();

	BinarySearchTree<T, CMP>(const BinarySearchTree<T, CMP>& copy);
	TreeNode<T, CMP>* node_copy(const TreeNode<T, CMP>* copy);
	void set_parent(TreeNode<T, CMP>* child);
	void swap(BinarySearchTree<T, CMP>& other);
	BinarySearchTree<T, CMP>& operator=(BinarySearchTree<T, CMP> copy);

	void insert(T data);
	void erase(T data);
	int count(T data) const;

	void print() const;
	T smallest();
	T largest();
	TreeIterator<T, CMP> begin();
	TreeIterator<T, CMP> end();

	void recursive_destructor(TreeNode<T, CMP>* node);
	/**	The BinarySearchTree destructor calls recursive_destructor on the root so that starting from the origin, it may cycle to all
		TreeNodes both to the left and right of the root calling delete. Virtual keyword included to enable future polymorphism
	*/
	virtual ~BinarySearchTree<T, CMP>() {
		recursive_destructor(root);
	}
private:
	TreeNode<T, CMP>* root;
	CMP isless;
};

/**	Default constructor sets root to nullptr
*/
template<typename T, typename CMP>
BinarySearchTree<T, CMP>::BinarySearchTree<T, CMP>() {
	root = nullptr;
}

/**	Overloaded copy constructor creates a deep copy of a BinarySearchTree object. Operates by calling on the root the recursive node_copy
	function which sets up its left/right children and the recursive set_parent function which then updates their node_parent pointers.
	Part of implementing copy swap idiom
	@param copy is a const reference to the BinarySearchTree object being copied
*/
template<typename T, typename CMP>
BinarySearchTree<T, CMP>::BinarySearchTree<T, CMP>(const BinarySearchTree<T, CMP>& copy) {
	root = node_copy(copy.root);
	root->node_parent = nullptr;
	set_parent(root);
}

/**	Creates a deep copy of a TreeNode object starting from the input pointer. Utilizes recursion to cycle through all left and right
	children to set them in the new TreeNode object
	@param copy is a const pointer to the TreeNode object being copied
	@return is a pointer to the TreeNode object with all left and right children copied that was created
*/
template<typename T, typename CMP>
TreeNode<T, CMP>* BinarySearchTree<T, CMP>::node_copy(const TreeNode<T, CMP>* copy) {
	//if input is nullptr cannot set left/right children and instead return nullptr
	if (copy == nullptr) {
		return nullptr;
	}
	TreeNode<T, CMP>* new_node = nullptr;
	//try to allocate heap memory safely
	try {
		new_node = new TreeNode<T, CMP>;
	}
	//if error occurs print statement and set pointer to nullptr
	catch (std::exception& e) {
		std::cerr << "BinarySearchTree<T, CMP>::node_copy(const TreeNode<T, CMP>* copy) failed to allocate memory" << std::endl;
		new_node = nullptr;
	}
	new_node->data = copy->data;
	//recursive calls to left and right children
	new_node->left = node_copy(copy->left);
	new_node->right = node_copy(copy->right);
	return new_node;
}

/**	Recursive function cycles through all left and right children setting their node_parent as the TreeNode before
	@param child is a pointer to the TreeNode object being cycled through and having its parent TreeNodes set
*/
template<typename T, typename CMP>
void BinarySearchTree<T, CMP>::set_parent(TreeNode<T, CMP>* child) {
	//if TreeNode pointer is nullptr cannot continue to set node_parent in that direction
	if (child == nullptr) {
		return;
	}
	//if left child is not nullptr continue in the left direction
	if (child->left != nullptr) {
		child->left->node_parent = child;
		set_parent(child->left);
	}
	//if right child is not nullptr continue in right direction
	if (child->right != nullptr) {
		child->right->node_parent = child;
		set_parent(child->right);
	}
}

/**	Swap function exchanges pointers between called BinarySearchTree object and other. Part of implementing copy swap idiom
	@param other is the BinarySearchTree object whose root pointer is being exchanged
*/
template<typename T, typename CMP>
void BinarySearchTree<T, CMP>::swap(BinarySearchTree<T, CMP>& other) {
	std::swap(root, other.root);
}

/**	Overloaded operator= utilizes swap on copy of BinarySearchTree input to ensure no memory leaks occur. Part of implementing
	copy swap idiom
	@param copy is a copy of the BinarySearchTree object being assigned
	@return is a reference to the BinarySearchTree object that was assigned (through swap) the values of copy
*/
template<typename T, typename CMP>
BinarySearchTree<T, CMP>& BinarySearchTree<T, CMP>::operator=(BinarySearchTree<T, CMP> copy) {
	copy.swap(*this);
	return *this;
}

/**	Inserts a new TreeNode containing input data into BinarySearchTree. Call insert_node(TreeNode<T, CMP>* new_node) TreeNode function
	with TreeNode pointer created to recursively determine appropriate location
	@param data is the T value of the new TreeNode being added
*/
template<typename T, typename CMP>
void BinarySearchTree<T, CMP>::insert(T data) {
	int in_tree = count(data);
	if (in_tree == 1) {
		return;
	}

	TreeNode<T, CMP>* new_node = nullptr;
	//try to allocate heap memory safely
	try {
		new_node = new TreeNode<T, CMP>;
	}
	//if error occurs print statement and set pointer to nullptr
	catch (std::exception& e) {
		std::cerr << "BinarySearchTree<T, CMP>::insert(T data) failed to allocate memory" << std::endl;
		new_node = nullptr;
	}
	new_node->data = data;
	new_node->left = nullptr;
	new_node->right = nullptr;
	new_node->node_parent = nullptr;

	//if the BinarySearchTree root is nullptr (therefore empty) automatically set new_node to root
	if (root == nullptr) {
		root = new_node;
	}
	//else call the recursive insert_node function on new_node to find appropriate location
	else {
		root->insert_node(new_node);
	}
}

/**	Provided that the input value exists within BinarySearchTree, erase(T data) removes TreeNode from BinarySearchTree by rerouting other
	pointers. For TreeNodes with two children, utilizes largest child of the left subtree. Updates node_parent appropriately
	@param data is the T value of the TreeNode to be removed
*/
template<typename T, typename CMP>
void BinarySearchTree<T, CMP>::erase(T data) {
	//find node to be removed
	TreeNode<T, CMP>* to_be_removed = root;
	TreeNode<T, CMP>* parent = nullptr;
	bool found = false;
	//loop cycles through BinarySearchTree as long as data has not been found and nullptr is not reached
	//TreeNode pointers updated to reflect position to be removed
	while ((!found) && (to_be_removed != nullptr)) {
		//if data to be found is larger update TreeNode pointers to continue to the right
		if (isless(to_be_removed->data, data)) {
			parent = to_be_removed;
			to_be_removed = to_be_removed->right;
		}
		//if data to be found is smaller update TreeNode pointers to continue to the left
		else if (isless(data, to_be_removed->data)) {
			parent = to_be_removed;
			to_be_removed = to_be_removed->left;
		}
		//else data to be found is equal size can set found to true
		else {
			found = true;
		}
	}

	if (!found) {
		return;
	}

	//to_be_removed contains data
	//if one of the children is empty, use the other
	if ((to_be_removed->left == nullptr) || (to_be_removed->right == nullptr)) {
		TreeNode<T, CMP>* new_child;
		//if left is nullptr and right is not children can only exist in the latter
		//set new_child to to_be_removed->right
		if ((to_be_removed->left == nullptr) && (to_be_removed->right != nullptr)) {
			new_child = to_be_removed->right;
			delete to_be_removed;
		}
		//if right is nullptr and left is not children can only exist in the latter
		//set new_child to to_be_removed->left
		else if ((to_be_removed->right == nullptr) && (to_be_removed->left != nullptr)) {
			new_child = to_be_removed->left;
			delete to_be_removed;
		}
		//else both left and right are nullptr to_be_removed is end TreeNode
		else {
			new_child = nullptr;
			//if left child of parent is being removed set it to nullptr
			if (parent->left == to_be_removed) {
				parent->left = new_child;
				delete to_be_removed;
			}
			//else right child of parent is being removed set it to nullptr
			else {
				parent->right = new_child;
				delete to_be_removed;
			}
			return;
		}
		//found in root
		if (parent == nullptr) {
			root = new_child;
		}
		//if left child of parent is being removed set it to new_child
		//update node_parent appropriately
		else if (parent->left == to_be_removed) {
			parent->left = new_child;
			parent->left->node_parent = parent;
		}
		//if right child of parent is being removed set it to new_child
		//update node_parent appropriately
		else {
			parent->right = new_child;
			parent->right->node_parent = parent;
		}
		return;
	}

	//neither subtree is empty
	//find largest element of left subtree
	TreeNode<T, CMP>* largest_parent = to_be_removed;
	TreeNode<T, CMP>* largest = to_be_removed->left;
	//cycle to the right to find largest value until reach nullptr
	while (largest->right != nullptr) {
		largest_parent = largest;
		largest = largest->right;
	}

	//largest contains largest child in left subtree
	//moves content unlink child
	to_be_removed->data = largest->data;
	//if largest parent is being removed set its left to largest->left
	if (largest_parent == to_be_removed) {
		largest_parent->left = largest->left;
		delete largest;
	}
	//if largest parent not being removed set its right to largest->left
	else {
		largest_parent->right = largest->left;
		delete largest;
	}
}

/**	Counts the number of times the input data value appears in BinarySearchTree. Utilizes the recursive find(T value) TreeNode
	function to cycle through the BinarySearchTree
	@param data is the T value being checked for
	@return is an int 0 or 1 stating whether the input data has been found
*/
template<typename T, typename CMP>
int BinarySearchTree<T, CMP>::count(T data) const {
	//if root is nullptr (therefore empty) data is not in BinarySearchTree
	if (root == nullptr) {
		return 0;
	}
	//calls recursive find function to search whether data is in BinarySearchTree
	else if (root->find(data)) {
		return 1;
	}
	//data is not in BinarySearchTree
	else {
		return 0;
	}
}

/**	Provided print function calls recursive print_nodes() TreeNode function provided root is not nullptr
*/
template<typename T, typename CMP>
void BinarySearchTree<T, CMP>::print() const {
	//ensures that root is not nullptr so that print_nodes() may be called
	if (root != nullptr) {
		root->print_nodes();
	}
}

/**	Determines smallest T value stored in BinarySearchTree
	@return T is the value of the smallest data point in the system
*/
template<typename T, typename CMP>
T BinarySearchTree<T, CMP>::smallest() {
	TreeNode<T, CMP>* smallest_value = root;
	//cycles through BinarySearchTree moving left until reach smallest value
	while (smallest_value->left != nullptr) {
		smallest_value = smallest_value->left;
	}
	return smallest_value->data;
}

/**	Determines largest T value stored in BinarySearchTree
	@return T is the value of the largest data point in the system
*/
template<typename T, typename CMP>
T BinarySearchTree<T, CMP>::largest() {
	TreeNode<T, CMP>* largest_value = root;
	//cycles through BinarySearchTree moving right until reach largest value
	while (largest_value->right != nullptr) {
		largest_value = largest_value->right;
	}
	return largest_value->data;
}

/**	Creates a TreeIterator object pointing to the first (smallest valued) TreeNode in the BinarySearchTree
	@return is a TreeIterator object pointing to the first (smallest valued) TreeNode in the BinarySearchTree
*/
template<typename T, typename CMP>
TreeIterator<T, CMP> BinarySearchTree<T, CMP>::begin() {
	TreeIterator<T, CMP> begin;
	begin.container = this;
	TreeNode<T, CMP>* smallest_value = root;
	//cycles through BinarySearchTree moving left until reach smallest valued TreeNode
	while (smallest_value->left != nullptr) {
		smallest_value = smallest_value->left;
	}
	begin.node_pointer = smallest_value;
	return begin;
}

/**	Creates a TreeIterator object pointing to the last (one past the largest valued) TreeNode in the BinarySearchTree
	@return is a TreeIterator object point to the last (one past the largest valued) TreeNode in the BinarySearchTree
*/
template<typename T, typename CMP>
TreeIterator<T, CMP> BinarySearchTree<T, CMP>::end() {
	TreeIterator<T, CMP> end;
	end.container = this;
	TreeNode<T, CMP>* largest_value = root;
	//cycles through BinarySearchTree moving right until reach largest valued TreeNode
	while (largest_value->right != nullptr) {
		largest_value = largest_value->right;
	}
	largest_value = largest_value->right;
	end.node_pointer = largest_value;
	return end;
}

/**	Cycles through TreeNodes of a BinarySearchTree recursively to call delete. Utilized in BinarySearchTree destructor to eliminate
	memory leaks
	@param node is a pointer to the TreeNode whose children (through recursion) are being cycled through for deletion
*/
template<typename T, typename CMP>
void BinarySearchTree<T, CMP>::recursive_destructor(TreeNode<T, CMP>* node) {
	//if TreeNode pointer is nullptr cannot continue to recursive_destructor in that direction
	if (node == nullptr) {
		return;
	}
	recursive_destructor(node->left);
	recursive_destructor(node->right);
	delete node;
}

#endif
#pragma once
