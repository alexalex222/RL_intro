//
// Created by Kuilin Chen on 2018-07-19.
//

#include "interval.h"


Interval::Interval(double l, double r): right(r), left(l) {}


bool Interval::contain(double x) {
    if (x >= left && x < right) return true;
    else return false;
}

double Interval::size() {
    return right - left;
}