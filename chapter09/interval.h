//
// Created by Kuilin Chen on 2018-07-19.
//

#ifndef CHAPTER09_INTERVAL_H
#define CHAPTER09_INTERVAL_H


class Interval {
public:
    const double left;
    const double right;

    /// Parameter Constructor
    /// \param l : left
    /// \param r : right
    Interval(double l, double r);

    /// Copy constructor
    /// \param i : an reference to an object of Interval
    Interval(const Interval& i) = default;

    /// Check x is contained in interval
    /// \param x : a position
    /// \return : whether a point is in this interval
    bool contain(double x);

    /// size of the interval
    /// \return
    double size();

};


#endif //CHAPTER09_INTERVAL_H
