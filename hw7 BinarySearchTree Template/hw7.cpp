/**	@mainpage PIC 10C Homework 7 Templated Binary Search Tree and Iterators
	@title PIC 10C Homework 7 Templated Binary Search Tree and Iterators
        @author Norris Khoo
	@date 02-19-2016

	This assignment is intended to provide students experience working with and a better understanding of iterators. Starting
	with code provided by the book, I expanded provided classes to store a T data value and included functions to return the
	T data value of the smallest and largest elements. I then implemented a bidirectional iterator containing begin(), end(),
	appropriate overloaded operators and constructors. In order to facilitate the bidirectional iterator, I added a parent pointer 
	to each TreeNode and correspondingly updated insert and erase functions. I implemented destructors to ensure that my code does not
	create memory leaks

	The code has been updated to make BinarySearchTree, TreeIterator and TreeNode all templated classes. Objects of each type
	are created with two template parameters: T indicates data value and CMP indicates comparison parameters. In order to facilitate
	comparison of the custom Point2D class, I further created comparison classes with overloaded operator()
*/

/**	@file main.cpp
	@brief This file contains the code provided in the hw7 assignment pdf. main() tests the functionality of my templated
	BinarySearchTree, TreeIterator and TreeNode classes on different object and comparison types
*/

#include "BinarySearchTree.h"
#include "PointOrder.h"
#include <string>
//#include <vld.h>
//Visual Leaks confirmed that no memory leaks occur
//I commented it out just in case the grader's Visual Studio does not contain the program

int main() {
	//Create binary search tree, give it values {2,3,5,11,13,17}
	BinarySearchTree<int> bst;
	bst.insert(3);
	bst.insert(2);
	bst.insert(11);
	bst.insert(13);
	bst.insert(5);
	bst.insert(17);

	//Prints to the console: 2,3,5,11,13,17,
	for (auto x : bst) {
		std::cout << x << ",";
	}
	std::cout << std::endl;

	BinarySearchTree<Point2D, PointOrderx> points_by_x;
	points_by_x.insert(Point2D(1, 2));
	points_by_x.insert(Point2D(7, 3));
	points_by_x.insert(Point2D(2, 1));

	//Prints to the console: (1,2),(2,1),(7,3),
	for (auto x : points_by_x) {
		std::cout << x << ",";
	}
	std::cout << std::endl;

	BinarySearchTree<Point2D, PointOrdery> points_by_y;
	points_by_y.insert(Point2D(1, 2));
	points_by_y.insert(Point2D(7, 3));
	points_by_y.insert(Point2D(2, 1));

	//Prints to the console: (2,1),(1,2),(7,3),
	for (auto x : points_by_y) {
		std::cout << x << ",";
	}
	std::cout << std::endl;

	BinarySearchTree<std::string, std::greater<std::string>> names;
	names.insert("Luke");
	names.insert("Kanye");
	names.insert("Pentatonix");

	//Prints to the console: Pentatonix, Luke, Kanye
	for (auto x : names) {
		std::cout << x << ",";
	}
	std::cout << std::endl;

	return 0;
}
