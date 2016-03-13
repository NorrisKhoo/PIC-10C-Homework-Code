/**	@file PointOrder.h
	@brief This file contains the declarations and definitions for the PointOrderx and PointOrdery comparison classes
*/

#ifndef POINTORDER_H
#define POINTORDER_H

#include "Point2D.h"

/**	@class PointOrderx
	@brief This class compares two Point2D objects based on their x values

	Operator() is overloaded to handle the comparison
*/
class PointOrderx {
public:
	/**	operator() has been overloaded to compare two Point2D objects by their x values
		@param lhs is a const reference to a Point2D object whose values are being compared with rhs
		@param rhs is a const reference to a Point2D object whose values are being compared with lhs
		@return a bool value indicating whether the x value of lhs < the x value of rhs
	*/
	bool operator()(const Point2D& lhs, const Point2D& rhs) const {
		return lhs.get_x() < rhs.get_x();
	}
};

/**	@class PointOrdery
	@brief This class compares two Point2D objects based on their y values

	Operator() is overloaded to handle to comparison
*/
class PointOrdery {
public:
	/**	operator() has been overloaded to compare two Point2D objects by their y values
		@param lhs is a const reference to a Point2D object whose values are being compared with rhs
		@param rhs is a const reference to a Point2D object whose values are being compared with lhs
		@return a bool value indicating whether the y value of lhs < the y value of rhs
	*/	
	bool operator()(const Point2D& lhs, const Point2D& rhs) const {
		return lhs.get_y() < rhs.get_y();
	}
};

#endif
#pragma once
