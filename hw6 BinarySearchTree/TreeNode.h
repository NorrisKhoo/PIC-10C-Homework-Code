/**	@file treenode.h
	@brief This file contains the declarations for the TreeNode class
*/

#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>

/**	@class TreeNode
	@brief The TreeNode class creates the individual nodes that eventually are linked together to form a BinarySearchTree

	Each TreeNode object contains an int data value and pointers to left child, right child and parent nodes. The insert_node,
	print_node and find functions all operate recursively to add a TreeNode to the Binary Search Tree system, print the TreeNodes
	of the system in numerical order and determine whether a TreeNode of particular int value exists within the system.
*/
class TreeNode {
public:
	void insert_node(TreeNode* new_node);
	void print_nodes() const;
	bool find(int value) const;
	/**	Default destructor. Virtual keyword included to enable future polymorphism
	*/
	~TreeNode() {};
private:
	int data;
	TreeNode* left;
	TreeNode* right;
	TreeNode* node_parent;
	friend class BinarySearchTree;
	friend class TreeIterator;
};

#endif
#pragma once
