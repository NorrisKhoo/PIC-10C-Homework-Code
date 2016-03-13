/**	@file treenode.cpp
	@brief This file contains the definitions for the TreeNode class
*/

#include "TreeNode.h"

/** Utilizing the constraints of a BinarySearchTree (left child must be smaller and right child must be larger), recursively determines
	appropriate location for input TreeNode pointer and adds to system
	@param new_node is a pointer to the TreeNode object being added to the system
*/
void TreeNode::insert_node(TreeNode* new_node) {
	//if new_node int data is smaller than current node data must continue to the left
	if (new_node->data < data) {
		//if left of current node is nullptr can set that location to new_node
		if (left == nullptr) {
			left = new_node;
			left->node_parent = this;
		}
		//call insert_node recursively to further cycle through BinarySearchTree system and find correct position
		else {
			left->insert_node(new_node);
		}
	}
	//if new_node int data is larger than current node data must continue to the right
	else if (data < new_node->data) {
		//if right of current node is nullptr can set that location to new_node
		if (right == nullptr) {
			right = new_node;
			right->node_parent = this;
		}
		//call insert_node recursively to further cycle through BinarySearchTree system and find correct position
		else {
			right->insert_node(new_node);
		}
	}
	//if TreeNode of same int data value already in system do not add
	else {
		return;
	}
}

/**	Utilizing the constraints of a BinarySearchTree (left child must be smaller and right child must be larger), recursively determines
	whether TreeNode of input int value exists in system.
	@return bool value 0 if TreeNode with input value not in system and 1 if TreeNode with input value is in system
*/
bool TreeNode::find(int value) const {
	//if input int value is smaller than current node data must continue to the left
	if (value < data) {
		//if left is nullptr cannot continue therefore return false
		if (left == nullptr) {
			return false;
		}
		//call find recursively to further cycle through BinarySearchTree system and search for TreeNode
		else {
			return left->find(value);
		}
	}
	//if input int value is larger than current node data must continue to the right
	else if (data < value) {
		//if right is nullptr cannot continue therefore return false
		if (right == nullptr) {
			return false;
		}
		//call find recursively to further cycle through BinarySearchTree system and search for TreeNode
		else {
			return right->find(value);
		}
	}
	//if data==value return true
	else {
		return true;
	}
}

/**	Recursively cycles through BinarySearchTree system to reach all nodes and print int data value
*/
void TreeNode::print_nodes() const {
	//if left is not nullptr continue in that direction
	if (left != nullptr) {
		left->print_nodes();
	}
	std::cout << data << std::endl;
	//if right is not nullptr continue in that direction
	if (right != nullptr) {
		right->print_nodes();
	}
}