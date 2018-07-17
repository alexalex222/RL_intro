//
// Created by Kuilin Chen on 2018-07-13.
//

#ifndef CHAPTER09_VALUE_FUNCTION_H
#define CHAPTER09_VALUE_FUNCTION_H


#include "random_walk.h"

// base class for value function
class ValueFunction {
public:
    RandomWalk p;

    ValueFunction();

    virtual ~ValueFunction();

    // get the state value
    virtual double value(int state) = 0;

    ///
    /// \param state : state of current sample
    /// \param delta : step size * (target - old estimation)
    virtual void update(int state, double delta) = 0;

};


#endif //CHAPTER09_VALUE_FUNCTION_H
