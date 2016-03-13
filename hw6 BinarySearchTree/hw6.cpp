/**	@mainpage PIC 10C Homework 6 Binary Search Tree and Iterators
	@title PIC 10C Homework 6 Binary Search Tree and Iterators
        @author Norris Khoo
	@date 02-12-2016

	This assignment is intended to provide students experience working with and a better understanding of iterators. Starting
	with code provided by the book, I expanded provided classes to store an int data value and included functions to return the 
	int data value of the smallest and largest elements. I then implemented a bidirectional iterator containing begin(), end() 
	and appropriate overloaded operators. In order to facilitate the bidirectional iterator, I added a parent pointer to each 
	TreeNode and correspondingly updated insert and erase functions. I implemented destructors to ensure that my code does not
	create memory leaks
*/

/**	@file main.cpp
	@brief This file contains the code provided in the hw6 assignment pdf. main() tests the functionality of my BinarySearchTree,
	TreeIterator and TreeNode classes
*/

#include <iostream>
#include "TreeNode.h"
#include "BinarySearchTree.h"
//#include <vld.h>
//Visual Leaks confirmed that no memory leaks occur
//I commented it out just in case the grader's Visual Studio does not contain the program

int main() {
	//Create binary search tree give it values {2,3,5,11,13,17}
	BinarySearchTree bst;
	
	bst.insert(3);
	bst.insert(2);
	bst.insert(11);
	bst.insert(13);
	bst.insert(5);
	bst.insert(17);
	bst.insert(17);


	//Prints to the console: 2,3,5,11,13,17,
	for (auto x : bst) {
		std::cout << x << ",";
	}
	std::cout << std::endl;

	bst.erase(6); // {2,3,5,11,13,17} no effect
	bst.erase(11); // {2,3,5,13,17}

	auto start = std::begin(bst);
	auto stop = std::end(bst);

	int value = 17;
	bool keep_looking = true;

	//Find a 17 in the list
	while (start != stop && keep_looking) {
		if (*start++ == value) {
			keep_looking = false;
		}
	}
	--start;

	//Prints "17 is in the list."
	if (start != stop) {
		std::cout << *start << " is in the list." << std::endl;
	}
	
	//Constructs a deep copy of bst
	BinarySearchTree deep_copy(bst);
	deep_copy.insert(11);
	deep_copy.insert(7);
	
	//Prints to the console: 2,3,5,7,11,13,17
	for (auto x : deep_copy) {
		std::cout << x << ",";
	}
	std::cout << std::endl;
	
	return 0;
}
