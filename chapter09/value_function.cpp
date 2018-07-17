//
// Created by Kuilin Chen on 2018-07-13.
//

#include "value_function.h"

// a wrapper class for aggregation value function
ValueFunction::ValueFunction() {
    p = RandomWalk(1000, -1, 1);
}

ValueFunction::~ValueFunction() {
    std::cout << "Destroy ValueFunction" << std::endl;
}

