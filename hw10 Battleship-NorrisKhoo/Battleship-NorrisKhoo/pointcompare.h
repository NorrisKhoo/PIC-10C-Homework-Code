/** @file pointcompare.h
 *  @brief This file contains the declarations and definitions for the PointCompare class
 *
 *  The PointCompare class compares QPoint objects based on their x and y coordinates
 */

#ifndef POINTCOMPARE_H
#define POINTCOMPARE_H

/**
 * @brief The PointCompare class
 * This class compares two QPoint objects based on their x values. If these values are the same, it
 * then compares the two QPoint objects based on their y values. operator() has been overloaded to
 * handle this comparison
 */
class PointCompare{
public:
    /**
     * @brief operator()
     * operator() has been overloaded to compare two QPoint objects. It first compares the size of their
     * x values and if these values are the same, utilizes their y values
     * @param left is a reference to a QPoint pointer being compared
     * @param right is a reference to a QPoint pointer being compared
     * @return a bool value indicating the result of x and then y comparisons
     */
    bool operator()(QPoint*& left, QPoint*& right){
        //if x values are not equal utilize operator< on x values
        if(left->rx()!=right->rx()){
            return (left->rx())<(right->rx());
        }
        //else if x values are equal utilize operator< on y values
        else{
            return (left->ry())<(right->ry());
        }
    }
};

#endif // POINTCOMPARE_H
