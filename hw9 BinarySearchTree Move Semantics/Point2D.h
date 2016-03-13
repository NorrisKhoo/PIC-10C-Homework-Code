/**	@file Point2D.h
	@brief This file contains the declarations and definitions for the Point2D class
*/

#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

/** @class Point2D
	@brief The Point2D class creates objects representing an ordered pair (x,y)

	The Point2D class stores its values as int. Functions are included to construct and print the objects. The virtual
	keyword is implemented to allow pointers of base or derived objects to call the correct form of functions
*/
class Point2D {
public:
	friend std::ostream& operator<<(std::ostream& out, const Point2D& points);

	/** Constructs the Point2D object with two int values
		@param input_x is the int value representing x in the ordered pair
		@param input_y is the int value representing y in the ordered pair
	*/
	Point2D(int input_x, int input_y) : x(input_x), y(input_y) { };

	/** Creates the default Point2D object as (0,0) using the previously defined constructor function
	*/
	Point2D() : Point2D(0, 0) { };

	/** Prints the Point2D object. Virtual keyword is added to permit the Point2D::print() function to be differentiated from
		the ColorPoint2D and WeightedPoint2D versions
	*/
	virtual void print() const {
		std::cout << "(" << x << "," << y << ")";
	}

	/** Deletes the Point2D object in the heap. Virtual keyword is added to prevent memory leaks as extra info contained in ColorPoint2D
		and WeightedPoint2D objects will be deleted also
	*/
	virtual ~Point2D() {}

	/** Returns int value denoting type of Point2D object user selected. Virtual keyword is added to permit the Point2D::rank() function
		to be differentiated from the ColorPoint2D and WeightedPoint2D versions
	*/
	virtual int rank() {
		return 1;
	}

	/**	Get function for Point2D object
		@return the int x value of Point2D object
	*/
	int get_x() const { return x; }
	
	/**	Get function for Point2D object
		@return the int y value of Point2D object
	*/
	int get_y() const { return y; }

	/**	operator== is overloaded to determine whether two Point2D objects have the same coordinates
		@param rhs is a const reference to the Point2D object whose values are being compared with the called Point2D object
		@return a bool value indicating whether the called object's coordinates == rhs coordinates
	*/
	bool operator==(const Point2D& rhs) {
		return ((this->get_x() == rhs.get_x()) && (this->get_y() == rhs.get_y()));
	}

private:
	int x;
	int y;
};

/**	Operator<< is overloaded to output coordinates when an ostream object is located to the left and a Point2D object is located
	to the right
	@param out is the ostream object denoting type of output
	@param p is the Point2D object being outputted
	@return a const reference to the ostream object that Point2D is output to
*/
std::ostream& operator<<(std::ostream& out, const Point2D& points) {
	out << "(" << points.x << "," << points.y << ")";
	return out;
}
#endif
#pragma once
